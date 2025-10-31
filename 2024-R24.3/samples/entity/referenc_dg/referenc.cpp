//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//  referenc.cpp



#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)

#error _DEBUG should not be defined except in internal Adesk debug builds

#endif

#include <adslib.h>

#include <dbelipse.h>

#include <gemat3d.h>

#include <dbsymtb.h>

#include <dbapserv.h>

#include <aced.h>

#include <actrans.h>

#include <dbidmap.h>

#include <acestext.h>

#include "tchar.h"







// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.



class AsdkEllipse : public AcDbEllipse



// This class extends AcDbEllipse by adding in functionality

// to store a dynamic array of hard pointer object IDs.

//

// The subErase() member function has been overridden and

// implemented, so when an object of this class is

// erased, the objects pointed to by the hard pointer IDs

// stored within the object will also be erased.

//

{

public:



    ACRX_DECLARE_MEMBERS(AsdkEllipse);

    AsdkEllipse() {};

    AsdkEllipse(const AcDbObjectIdArray& ellipses)

        : mEllipseIds(ellipses) {};

    AsdkEllipse(const AcGePoint3d&  center,

        const AcGeVector3d& unitNormal,

        const AcGeVector3d& majorAxis,

        double radiusRatio,

        double startAngle = 0.0,

        double endAngle = 6.28318530717958647692);

    AsdkEllipse(const AcDbObjectIdArray&  ellipses,

        const AcGePoint3d&  center,

        const AcGeVector3d& unitNormal,

        const AcGeVector3d& majorAxis,

        double radiusRatio,

        double startAngle = 0.0,

        double endAngle   = 6.28318530717958647692);

    AcDbObjectId ellipseId(unsigned short which);

    Acad::ErrorStatus setEllipseId(

        const AcDbObjectId& objId, unsigned short which);

    Acad::ErrorStatus setEllipseIds(

        const AcDbObjectIdArray& Ids);

    Acad::ErrorStatus appendId(const AcDbObjectId& objId);

    Acad::ErrorStatus appendIds(

        const AcDbObjectIdArray& objIds);

    inline Adesk::Boolean removeId(

        const AcDbObjectId& objId);



    // AcDbObject overrides.

    //

    virtual Acad::ErrorStatus subErase(

        Adesk::Boolean pErasing);

    virtual Acad::ErrorStatus dwgInFields(

        AcDbDwgFiler* filer);

    virtual Acad::ErrorStatus dwgOutFields(

        AcDbDwgFiler* filer) const;

    virtual Acad::ErrorStatus dxfInFields(

        AcDbDxfFiler* filer);

    virtual Acad::ErrorStatus dxfOutFields(

        AcDbDxfFiler* filer) const;

protected:

    virtual Acad::ErrorStatus subWblockClone(

        AcRxObject* pOwnerObject,

        AcDbObject*& pClonedObject,

        AcDbIdMapping& idMap,

        Adesk::Boolean isPrimary = Adesk::kTrue) const;



    // AcDbEntity overrides.

    //

    virtual void subList() const;



private:

    AcDbObjectIdArray mEllipseIds;

    static int mInFlux;  // == 1 when first object's

                         //    subErase is erasing.

};



ACRX_DXF_DEFINE_MEMBERS(AsdkEllipse, AcDbEllipse,

AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,

0,\

    ASDKELLIPSE, REFERENC);



// Static class data member definition.

//

int AsdkEllipse::mInFlux = Adesk::kFalse;





AsdkEllipse::AsdkEllipse(const AcGePoint3d&  center,

    const AcGeVector3d& unitNormal,

    const AcGeVector3d& majorAxis,

    double              radiusRatio,

    double              startAngle,

    double              endAngle) :



    AcDbEllipse(center, unitNormal, majorAxis, radiusRatio,

    startAngle, endAngle)

{	}



AsdkEllipse::AsdkEllipse(const AcDbObjectIdArray&  ellipses,

    const AcGePoint3d&  center,

    const AcGeVector3d& unitNormal,

    const AcGeVector3d& majorAxis,

    double              radiusRatio,

    double              startAngle,

    double              endAngle) :



    AcDbEllipse(center, unitNormal, majorAxis, radiusRatio,

    startAngle, endAngle), mEllipseIds(ellipses)

{ 	}



AcDbObjectId

AsdkEllipse::ellipseId(unsigned short which)

{

    assertReadEnabled();

    if  (which > mEllipseIds.length())

        return AcDbObjectId::kNull;

    return mEllipseIds[which];

}



Acad::ErrorStatus

AsdkEllipse::setEllipseId(const AcDbObjectId& objId,

    unsigned short which)

{

    assertWriteEnabled();

    if  (which > mEllipseIds.length())

        return Acad::eInvalidIndex;

    mEllipseIds[which] = objId;

    return Acad::eOk;

}



Acad::ErrorStatus

AsdkEllipse::setEllipseIds(const AcDbObjectIdArray& objIds)

{

    assertWriteEnabled();

    if (objIds.length() == 0)

        return Acad::eNullObjectId;

    mEllipseIds = objIds;

    return Acad::eOk;

}



Acad::ErrorStatus

AsdkEllipse::appendId(const AcDbObjectId& objId)

{

    assertWriteEnabled();

    if  (objId == AcDbObjectId::kNull)

        return Acad::eNullObjectId;

    mEllipseIds.append(objId);

    return Acad::eOk;

}



Acad::ErrorStatus

AsdkEllipse::appendIds(const AcDbObjectIdArray& objIds)

{

    assertWriteEnabled();

    if  (objIds.length() == 0)

        return Acad::eNullObjectId;

    mEllipseIds.append(objIds);

    return Acad::eOk;

}



inline Adesk::Boolean

AsdkEllipse::removeId(const AcDbObjectId& objId)

{

    assertWriteEnabled();

    return mEllipseIds.remove(objId);

}



// This implementation of subErase opens and erases all

// objects that this entity has hard pointer references

// to.  The effect is that when one AsdkEllipse is erased,

// all the others it has hard pointers to also erase as

// a "group".

//

Acad::ErrorStatus

AsdkEllipse::subErase(Adesk::Boolean pErasing)

{

    Acad::ErrorStatus es = AcDbEllipse::subErase(pErasing);

    if (es != Acad::eOk)

        return es;



    if (mInFlux == Adesk::kFalse) {

        mInFlux = Adesk::kTrue;

        AsdkEllipse *pEllipse;

        int es;

        for (int i = 0; i < mEllipseIds.length(); i++) {

            es = acdbOpenObject(pEllipse, mEllipseIds[i],

                AcDb::kForWrite, Adesk::kTrue);

            if (es != Acad::eOk)

                continue;



			pEllipse->erase(pErasing);

            pEllipse->close();

        }

        mInFlux = Adesk::kFalse;

    }

    return Acad::eOk;

}



Acad::ErrorStatus

AsdkEllipse::dwgInFields(AcDbDwgFiler* filer)

{

    assertWriteEnabled();



    AcDbEllipse::dwgInFields(filer);



    mEllipseIds.setLogicalLength(0);



    Adesk::Int32 idCount;

    filer->readInt32(&idCount);



    AcDbHardPointerId objId;

    for (int i = 0; i < idCount; i++) {

        filer->readItem(&objId);

        mEllipseIds.append(objId);

    }

    return filer->filerStatus();

}



Acad::ErrorStatus

AsdkEllipse::dwgOutFields(AcDbDwgFiler* filer) const

{

    assertReadEnabled();



    AcDbEllipse::dwgOutFields(filer);



    filer->writeInt32(mEllipseIds.length());



    for (int i = 0; i < mEllipseIds.length(); i++) {

        filer->writeHardPointerId(mEllipseIds[i]);

    }

    return filer->filerStatus();

}



Acad::ErrorStatus

AsdkEllipse::dxfInFields(AcDbDxfFiler* filer)

{

    assertWriteEnabled();



    Acad::ErrorStatus es = AcDbEllipse::dxfInFields(filer);

    if (es != Acad::eOk) {

        return es;

    }



    // Check to see if we're at the right subclass data

    // marker.

    //

    if (!filer->atSubclassData(_T("AsdkEllipse"))) {

        return Acad::eBadDxfSequence;

    }



    struct resbuf inbuf;

    AcDbObjectId objId;

    int idCount;

    filer->readItem(&inbuf);

    if (inbuf.restype == AcDb::kDxfInt32) {

        idCount = inbuf.resval.rint;

    } else {

        filer->pushBackItem();

        filer->setError(Acad::eInvalidDxfCode,

            _T("\nError: expected group code %d"),

             AcDb::kDxfInt32);

        return filer->filerStatus();

    }



    for (int i = 0; i < idCount; i++) {

        es = filer->readItem(&inbuf);

        if (es != Acad::eOk) {

            filer->setError(Acad::eMissingDxfField,

                _T("\nError: expected more group code %d's"),

                AcDb::kDxfHardPointerId);

            return filer->filerStatus();

        }

        if (inbuf.restype == AcDb::kDxfHardPointerId) {

            acdbGetObjectId(objId, inbuf.resval.rlname);

            mEllipseIds.append(objId);

        } else {

            filer->pushBackItem();

            filer->setError(Acad::eInvalidDxfCode,

                _T("\nError: expected group code %d"),

                AcDb::kDxfHardPointerId);

            return filer->filerStatus();

        }

    }

    return filer->filerStatus();

}



Acad::ErrorStatus

AsdkEllipse::dxfOutFields(AcDbDxfFiler* filer) const

{

    assertReadEnabled();



    AcDbEllipse::dxfOutFields(filer);

    filer->writeItem(AcDb::kDxfSubclass, _T("AsdkEllipse"));

    filer->writeInt32(AcDb::kDxfInt32,

        mEllipseIds.length());



    for (int i = 0; i < mEllipseIds.length(); i++) {

        filer->writeObjectId(AcDb::kDxfHardPointerId,

            mEllipseIds[i]);

    }

    return filer->filerStatus();

}





void

AsdkEllipse::subList() const

{

    assertReadEnabled();

    AcDbEllipse::subList();

    acutPrintf(_T("\nClass:\t%s"), isA()->name());

    for (int i = 0; i < mEllipseIds.length(); i++) {

        acutPrintf(_T("\nReferenceId[%d]:\t%ld"), i,

            (mEllipseIds[i]).asOldId());

    }

}





Acad::ErrorStatus

AsdkEllipse::subWblockClone(AcRxObject*    pOwnerObject,

                         AcDbObject*&   pClonedObject,

                         AcDbIdMapping& idMap,

                         Adesk::Boolean isPrimary) const

{

    assertReadEnabled();

    static AcDbObjectId btr, pspace = AcDbObjectId::kNull;

    AcTransaction *pTrans = NULL;

    pClonedObject = NULL;

    if (pspace == AcDbObjectId::kNull) {

        AcDbBlockTable *pTable;

        database()->getSymbolTable(pTable, AcDb::kForRead);

        pTable->getAt(ACDB_PAPER_SPACE, pspace);

        pTable->close();

    }



    if (   idMap.deepCloneContext() == AcDb::kDcXrefBind

        && ownerId() == pspace)

        return Acad::eOk;



    // Have we already done this entity ?

    //

    AcDbIdPair idPair(objectId(), (AcDbObjectId)NULL,

        Adesk::kTrue);

    if (idMap.compute(idPair) == TRUE && idPair.value()

        != NULL)

    {

        pClonedObject = NULL;

        return Acad::eOk;

    }



    AcDbBlockTableRecord *pBTR

        = AcDbBlockTableRecord::cast(pOwnerObject);



    if (pBTR != NULL) {

        if (isPrimary == Adesk::kTrue)

            btr = pBTR->objectId();

        else

            btr = AcDbObjectId::kNull;



    } else if (btr != AcDbObjectId::kNull) {

        pTrans = actrTransactionManager->startTransaction();

        pTrans->getObject((AcDbObject*&)pBTR, btr,

            AcDb::kForWrite);

        pOwnerObject = pBTR;

    }



    Acad::ErrorStatus es

        = AcDbEllipse::wblockClone(pOwnerObject,

        pClonedObject, idMap, btr != AcDbObjectId::kNull);



	if (pTrans)

		actrTransactionManager->endTransaction();



    acutPrintf(_T("\nWblockClone error status: %s"), acadErrorStatusText(es) );

    return Acad::eOk;

}





void

createEllipses()

{

    const int ellipseCount = 10;



    AsdkEllipse *pEllipse;

    pEllipse = new AsdkEllipse(AcGePoint3d(4.0, 4.0, 0.0),

        AcGeVector3d(0.0, 0.0, 1.0),

        AcGeVector3d(2.0, 0.0, 0.0),

        0.5);



    AcDbVoidPtrArray ellipses;

    ellipses.append(pEllipse);



    // Now use the getTransformedCopy() function with a

    // scaling matrix (in X & Y only) to create new

    // AsdkEllipses, each 0.5 units larger than the last in

    // the X & Y direction,  but identical in the Z

    // direction.  This would be similar to the

    // getOffsetCurves() function,  but that function

    // returns AcDbSpline entities instead of AcDbEllipses.

    //

    double j = 1.1;

    AcGeMatrix3d scale;

    for (int i = 0; i < ellipseCount; i++, j += 0.1) {

        scale.setToScaling(j, pEllipse->center());

        scale.entry[2][2] = 1.0;  // Z scaling == 1



        // getTransformed copy uses this->clone() to create

        // a new object, which the ent pointer is assigned

        // to point to. Therefore, ent should NOT point to an

        // existing entity or there will be a memory leak!

        //

        // Since this->clone() is used, the AsdkEllipse class

        // must override this member function to

        // be sure that an AsdkEllipse is created instead

        // of just an AcDbEllipse.

	//



        AsdkEllipse *pNextEllipse;

        ((AsdkEllipse*)ellipses[0])->getTransformedCopy(

            scale, (AcDbEntity*&)pNextEllipse);



        ellipses.append(pNextEllipse);

    }



    AcDbBlockTable *pBlockTable;

    acdbHostApplicationServices()->workingDatabase()

        ->getSymbolTable(pBlockTable, AcDb::kForRead);



    AcDbBlockTableRecord *pBlockTableRecord;

    pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,

        AcDb::kForWrite);

    pBlockTable->close();



    AcDbObjectIdArray ellipseIds;

    AcDbObjectId tempId;

    for (int i = 0; i < ellipses.length(); i++) {

        pBlockTableRecord->appendAcDbEntity(tempId,

            (AsdkEllipse*)ellipses[i]);

        ellipseIds.append(tempId);

    }

    pBlockTableRecord->close();



    // Set up the hard pointers and close the ellipses.

    //

    for (int i = 0; i < ellipses.length(); i++) {

        // Add in all the IDs.

        //

        ((AsdkEllipse*)ellipses[i])

            ->setEllipseIds(ellipseIds);



        // Now remove the object ID of the "*this" ellipse

        // so it doesn't reference itself.

        //

        ((AsdkEllipse*)ellipses[i])->removeId(

            ((AsdkEllipse*)ellipses[i])->objectId());



        ((AsdkEllipse*)ellipses[i])->close();

    }

}



void

initApp()

{

    acedRegCmds->addCommand(_T("ASDK_ELLIPSES"),

        _T("ASDK_ELLIPSES"), _T("ELLIPSES"),

        ACRX_CMD_MODAL, createEllipses);



    AsdkEllipse::rxInit();

    acrxBuildClassHierarchy();

}



void

unloadApp()

{

    acedRegCmds->removeGroup(_T("ASDK_ELLIPSES"));



    // Remove the AsdkEllipse class from the ACRX runtime

    // class hierarchy. If this is done while the database is

    // still active, it should cause all objects of class

    // AsdkEllipse to be turned into proxies.

    //

    deleteAcRxClass(AsdkEllipse::desc());

}



extern "C" AcRx::AppRetCode

acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)

{

    switch (msg) {

    case AcRx::kInitAppMsg:

        acrxDynamicLinker->unlockApplication(appId);

		acrxDynamicLinker->registerAppMDIAware(appId);

        initApp();

        break;

    case AcRx::kUnloadAppMsg:

        unloadApp();

    }

    return AcRx::kRetOK;

}



// END CODE APPEARING IN SDK DOCUMENT.

