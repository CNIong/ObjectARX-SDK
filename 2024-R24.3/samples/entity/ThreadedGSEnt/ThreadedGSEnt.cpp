//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#include "stdafx.h"
#include <memory>
#define _USE_MATH_DEFINES
#include <math.h>
#include <adslib.h>
#include <rxregsvc.h>
#include <dbmain.h>
#include <dbents.h>
#include <dbapserv.h>
#include <aced.h>
#include <rxregsvc.h>
#include <dbproxy.h>
#include <geassign.h>
#include <gept3dar.h>
#include <dbxutil.h>
#include <dbvisualstyle.h>
#include <acgiutil.h>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// helper functions

static void closeOrDeleteDbObj(AcDbObject *pObj)
{
    if (pObj->objectId().isNull())
        delete pObj;
    else
        pObj->close();
}

template <class T> struct unique_db_ptr : public unique_ptr<T, void(*)(AcDbObject*)>
{
    unique_db_ptr<T>(T* t) : unique_ptr<T,void(*)(AcDbObject*)>(t, closeOrDeleteDbObj) { }
};

static bool
addToDb(AcDbEntity *pEnt, AcDbDatabase *pDb)
{
    unique_db_ptr<AcDbEntity> ent(pEnt);
    AcDbBlockTable *pBt;
    if (Acad::eOk != pDb->getBlockTable(pBt, AcDb::kForRead))
        return false;
    unique_db_ptr<AcDbBlockTable> bt(pBt);
    AcDbBlockTableRecord *pMs;
    if (Acad::eOk != pBt->getAt(ACDB_MODEL_SPACE, pMs, AcDb::kForWrite))
        return false;
    return Acad::eOk == unique_db_ptr<AcDbBlockTableRecord>(pMs)->appendAcDbEntity(ent.get());
}


///////////////////////////////////////////////////////////////////////////////
// AcDbThreadedGSEntity
//
// Custom entity that demonstrates the new GS APIs to perform dynamic re-tessellations
// on a worker thread instead of the main thread.
// This way, any re-tessellations that happen during pan/zoom/orbit or other view changes
// will not block the main thread any longer. Users will have a smooth mouse movement
// experience during these operations; there won't be any re-tessellation-related lags
// any more.
//

class AcDbThreadedGSEntity : public AcDbEntity
{
public:
    friend class AcDbEntityParallelDrawPE_AcDbThreadedGSEntity;
    ACRX_DECLARE_MEMBERS(AcDbThreadedGSEntity);

    AcDbThreadedGSEntity()   {  }
    ~AcDbThreadedGSEntity()  {  }

    void              setParameters             (const AcGePoint3d& center, double radius);

    Acad::ErrorStatus dwgInFields               (AcDbDwgFiler* pFiler)        override;
    Acad::ErrorStatus dwgOutFields              (AcDbDwgFiler* pFiler)  const override;
    Acad::ErrorStatus dxfInFields               (AcDbDxfFiler* pFiler)        override;
    Acad::ErrorStatus dxfOutFields              (AcDbDxfFiler* pFiler)  const override;

protected:
    Adesk::Boolean    subWorldDraw              (AcGiWorldDraw* pWd)              override;
    Acad::ErrorStatus subTransformBy            (const AcGeMatrix3d& xform)       override;
    void              subList                   ()                          const override;
    Adesk::UInt32     subSetAttributes          (AcGiDrawableTraits* pTraits)     override;

private:
    void              getPoints                 (AcGePoint3dArray& ar, int numSides) const;
    AcDbObjectId      getOrCreateLayerIdByName  (const ACHAR* layerName)             const;
    AcDbObjectId      getContinuousLinetypeId   ()                                   const;

    AcGePoint3d mCenter;
    double      mRadius{ 0.0 };
};


ACRX_DXF_DEFINE_MEMBERS(AcDbThreadedGSEntity, AcDbEntity, AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,
    AcDbProxyEntity::kAllAllowedBits, ACDBTHREADEDGSENTITY, "AcDbThreadedGSEntity App");


// Protocol extension for prepareForParallelDraw().
//
// Custom entities that want to participate in threaded GS tessellation, but have to access acdb in
// their worldDraw/viewportDraw implementation will need to implement this protocol extension, to query
// and do the necessary acdb work in advance.
//
// prepareForParallelDraw will be called by GS on the main thread right before the threaded worldDraw
// callout.
//
// worldDraw/viewportDraw implementations will need to be "sanitized" from acdb access, as acdb itself
// is not thread-safe, and any calls into it from threads other than the main thread might lead to
// unexpected behaviors or crashes.
//
class AcDbEntityParallelDrawPE_AcDbThreadedGSEntity : public AcDbEntityParallelDrawPE
{
public:
    Adesk::Boolean prepareForParallelDraw(AcDbEntity* pEnt, AcDbDwgFiler* pFiler) const override;
};

Adesk::Boolean AcDbEntityParallelDrawPE_AcDbThreadedGSEntity::prepareForParallelDraw(AcDbEntity* pEnt, AcDbDwgFiler* pFiler) const
{
    // get or create our layer, and file out its object id, so we can retrieve this object id
    // later in the threaded worldDraw call from this filer, instead of reaching out to acdb to
    // get it.
    //
    pFiler->writeHardPointerId((AcDbHardPointerId)((AcDbThreadedGSEntity*)pEnt)->getOrCreateLayerIdByName(L"CUSTOMENTITYLAYER"));
    return Adesk::kTrue;
}


///////////////////////////////////////////////////////////////////////////////
// AcDbThreadedGSEntity member functions implementations
//

AcDbObjectId AcDbThreadedGSEntity::getOrCreateLayerIdByName(const ACHAR* layerName) const
{
    AcDbObjectId result = AcDbObjectId::kNull;

    AcDbDatabase *pDb = database();
    if (nullptr == pDb)
        pDb = acdbHostApplicationServices()->workingDatabase();
    if (nullptr == pDb)
        return result;

    AcDbLayerTable *pLt;
    if (Acad::eOk != pDb->getLayerTable(pLt))
        return result;

    unique_db_ptr<AcDbLayerTable> lt(pLt);
    if (Acad::eOk != lt->getAt(layerName, result)) {
        if (Acad::eOk != lt->upgradeOpen())
            return result;

        unique_db_ptr<AcDbLayerTableRecord> ltr(new AcDbLayerTableRecord);
        if (nullptr == ltr)
            return result;

        ltr->setName(layerName);
        ltr->setLinetypeObjectId(getContinuousLinetypeId());
        AcCmColor col;
        col.setColorIndex(1);
        ltr->setColor(col);
        if (Acad::eOk != lt->add(result, ltr.get()))
            result.setNull();
    }
    return result;
}

AcDbObjectId AcDbThreadedGSEntity::getContinuousLinetypeId() const
{
    AcDbObjectId result = AcDbObjectId::kNull;

    AcDbDatabase *pDb = database();
    if (nullptr == pDb)
        pDb = acdbHostApplicationServices()->workingDatabase();
    if (nullptr == pDb)
        return result;

    AcDbLinetypeTable *pLt;
    if (Acad::eOk != pDb->getLinetypeTable(pLt))
        return result;

    unique_db_ptr<AcDbLinetypeTable> lt(pLt);
    if (Acad::eOk != lt->getAt(L"CONTINUOUS", result))
        result.setNull();

    return result;
}

void AcDbThreadedGSEntity::setParameters(const AcGePoint3d& center, double radius)
{
    assertWriteEnabled();
    mCenter = center;
    mRadius = radius;
}

Acad::ErrorStatus AcDbThreadedGSEntity::dwgInFields(AcDbDwgFiler* pFiler)
{
    assertWriteEnabled();
    if (Acad::eOk != __super::dwgInFields(pFiler))
        return pFiler->filerStatus();

    pFiler->readPoint3d(&mCenter);
    pFiler->readDouble(&mRadius);
    return pFiler->filerStatus();
}

Acad::ErrorStatus AcDbThreadedGSEntity::dwgOutFields(AcDbDwgFiler* pFiler) const
{
    assertReadEnabled();
    if (Acad::eOk != __super::dwgOutFields(pFiler))
        return pFiler->filerStatus();

    pFiler->writePoint3d(mCenter);
    pFiler->writeDouble(mRadius);
    return pFiler->filerStatus();
}

Acad::ErrorStatus AcDbThreadedGSEntity::dxfInFields(AcDbDxfFiler* pFiler)
{
    assertWriteEnabled();
    if (Acad::eOk != __super::dxfInFields(pFiler) || !pFiler->atSubclassData(L"AcDbThreadedGSEntity"))
        return pFiler->filerStatus();

    resbuf rb;
    while (Acad::eOk == pFiler->readResBuf(&rb))
    {
        switch (rb.restype)
        {
        case AcDb::kDxfXCoord:
            mCenter = asPnt3d(rb.resval.rpoint);
            break;
        case AcDb::kDxfReal:
            mRadius = rb.resval.rreal;
            break;
        default:
            pFiler->pushBackItem();
            return Acad::eEndOfFile;
            break;
        }
    }

    return pFiler->filerStatus();
}

Acad::ErrorStatus AcDbThreadedGSEntity::dxfOutFields(AcDbDxfFiler* pFiler) const
{
    assertReadEnabled();
    if (Acad::eOk != __super::dxfOutFields(pFiler))
        return pFiler->filerStatus();

    pFiler->writeItem(AcDb::kDxfSubclass, L"AcDbThreadedGSEntity");
    pFiler->writePoint3d(AcDb::kDxfXCoord, mCenter);
    pFiler->writeDouble(AcDb::kDxfReal, mRadius);
    return pFiler->filerStatus();
}

Acad::ErrorStatus AcDbThreadedGSEntity::subTransformBy(const AcGeMatrix3d& xform)
{
    assertWriteEnabled();
    mCenter.transformBy(xform);
    mRadius *= xform.scale();
    return Acad::eOk;
}

// Sample code for a worldDraw implementation that is sanitized from making any
// acdb calls when called from the GS worker thread.
//
Adesk::Boolean AcDbThreadedGSEntity::subWorldDraw(AcGiWorldDraw* pWd)
{
    assertReadEnabled();
    if (mRadius != 0.0) {

        AcDbObjectId layerId;

        AcDbDwgFiler *pEntityData = nullptr;
        AcGiContextParallelDrawPE* pe = AcGiContextParallelDrawPE::cast(pWd->context()->isA()->queryX(AcGiContextParallelDrawPE::desc()));
        if (nullptr != pe)
            pEntityData = pe->entityDataFiler(pWd->context());

        if (nullptr != pEntityData) {
            // Retrieve the data that we've earlier stored/created, during the prepareForParallelDraw call (which gets called on the main thread)
            //
            // If the entityDataFiler() pointer is non-null, it means that we are currently executed
            // from the GS worker thread, and not from the AutoCAD main thread.
            // In this case, we can't reach out to acdb. Instead, everything acdb-related that we need,
            // has to be collected by the previous callout to prepareForParallelDraw.
            // 
            pEntityData->readHardPointerId((AcDbHardPointerId*)&layerId);
        }
        else {
            // We're not called by the GS worker thread, so it's safe to call into acdb.
            layerId = getOrCreateLayerIdByName(L"CUSTOMENTITYLAYER");
        }

        if (!layerId.isNull())
            pWd->subEntityTraits().setLayer(layerId);

        if (acdbIsGsWorkerThread()) {
            // For illustration purposes, draw geometry in a different
            // color when called from the GS worker thread.
            //
            pWd->subEntityTraits().setColor(2);
        }

        AcGePoint3dArray ar;
        // Querying the deviation makes this entity subject to dynamic tessellation
        // when zooming in/out.
        //
        double d = 0.01 / pWd->deviation(kAcGiMaxDevForCircle, mCenter) * mRadius;
        int numSides = (int)d;
        if (numSides < 5)
            numSides = 5;
        else if (numSides > 1000)
            numSides = 1000;
        getPoints(ar, numSides);

        pWd->geometry().polyline(ar.length(), &ar[0]);
    }
    return Adesk::kTrue;
}

void AcDbThreadedGSEntity::subList() const
{
    assertReadEnabled();
    __super::subList();
    acutPrintf(L"%18s%16s ", L"", L"Center:");
    acutPrintf(L"%-9.16q0 %-9.16q0 %-9.16q0\n",
        mCenter[0], mCenter[1], mCenter[2]);
    acutPrintf(L"%18s%16s %-9.16q0\n", L"", L"Radius:", mRadius);
}

Adesk::UInt32 AcDbThreadedGSEntity::subSetAttributes(AcGiDrawableTraits* pTraits)
{
    // Set the kThreadedWorldDrawViewportDraw flag to indicate that we
    // want to be called on a GS worker thread (and therefore not blocking
    // the AutoCAD main thread) for dynamic GS-retessellations.
    //
    return __super::subSetAttributes(pTraits) | AcGiDrawable::kThreadedWorldDrawViewportDraw;
}

void AcDbThreadedGSEntity::getPoints(AcGePoint3dArray& vertexArray, int numSides) const
{
    assertReadEnabled();

    AcGePoint3d startPoint = mCenter + AcGeVector3d(mRadius, 0.0, 0.0);

    vertexArray.append(startPoint);

    double rotateBy = 2.0 * M_PI / numSides;
    double increment = rotateBy;
    AcGeVector3d dir(startPoint - mCenter);
    double base = atan2(dir.y, dir.x);

    for (int i = 0; i < numSides; i++) {
        AcGePoint3d vertex{ mRadius * cos(rotateBy + base),
                            mRadius * sin(rotateBy + base),
                            0.0 };
        vertexArray.append(vertex + mCenter.asVector());
        rotateBy += increment;
    }
}

///////////////////////////////////////////////////////////////////////////////
// command implementation to create custom entity

static void
setToVisualStyle(const ACHAR* vsName)
{
    AcDbObjectId visualStyleId;
    AcDbDictionary *pVisualStyleDict = nullptr;
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    if (nullptr == pDb)
        return;

    Acad::ErrorStatus es = Acad::eOk;
    if (Acad::eOk == (es = pDb->getVisualStyleDictionary(pVisualStyleDict, AcDb::kForRead)))
    {
        unique_db_ptr<AcDbDictionary> vstyleDict(pVisualStyleDict);
        es = vstyleDict->getAt(vsName, visualStyleId);
    }

    if (Acad::eOk == es)
        acdbSetViewportVisualStyle(visualStyleId);
}

static void
addCustomEntity()
{
    ads_point center;
    if (RTNORM != acedGetPoint(nullptr, L"Enter center point: ", center))
        return;

    double radius = 0.0;
    if (RTNORM != acedGetDist(center, L"Enter radius: ", &radius)
        || radius == 0.0)
    {
        return;
    }

    AcDbThreadedGSEntity *pEnt = new AcDbThreadedGSEntity;
    if (nullptr != pEnt) {
        pEnt->setParameters(asPnt3d(center), radius);
        addToDb(pEnt, acdbHostApplicationServices()->workingDatabase());
        setToVisualStyle(L"CONCEPTUAL");
    }
}

///////////////////////////////////////////////////////////////////////////////
// ARX init code

static void
initClasses()
{
    AcDbThreadedGSEntity::rxInit();
    acrxBuildClassHierarchy();
    AcDbThreadedGSEntity::desc()->addX(AcDbEntityParallelDrawPE::desc(), new AcDbEntityParallelDrawPE_AcDbThreadedGSEntity());
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void *p)
{
    switch (msg)
    {
    case AcRx::kInitAppMsg:
        acedRegCmds->addCommand(L"MKR", L"ADDCUSTOMENTITY", L"ADDCUSTOMENTITY", ACRX_CMD_TRANSPARENT, addCustomEntity);
        initClasses();
        acrxRegisterAppMDIAware(p);
        acrxLockApplication(p);
        break;
    }
    return AcRx::kRetOK;
}

