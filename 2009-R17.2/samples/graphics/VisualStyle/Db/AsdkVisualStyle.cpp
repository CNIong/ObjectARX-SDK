//
// (C) Copyright 2005-2008 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(_FULLDEBUG_)
#define _DEBUG_WAS_DEFINED
#pragma message ("       Compiling MFC /STL /ATL header files in release mode.")
#undef _DEBUG
#endif

#include "dbproxy.h"
#include "dbtrans.h"
#include "dbxutil.h"
#include "dbsol3d.h"
#include "AsdkVisualStyle.h"

#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif

ACRX_DXF_DEFINE_MEMBERS(AsdkVisualStyle, AcDbEntity,
                        AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,
                        AcDbProxyEntity::kAllAllowedBits,
                        ASDKVISUALSTYLE, AsdkVisualStyleDb|Product: ObjectDBX Enabler for Visual Style Entity|Company: Autodesk Developer Consulting Group|Website: www.autodesk.com/adn/devhelp
                        );

MAKE_ACDBOPENOBJECT_FUNCTION(AsdkVisualStyle);

AsdkVisualStyle::AsdkVisualStyle()
{
    assertWriteEnabled();
    mTransform.setToIdentity();
    setColorIndex(0); // white/black
}

AsdkVisualStyle::~AsdkVisualStyle()
{
}

// AsdkVisualStyle protocol
//

AcGePoint3d AsdkVisualStyle::center() const
{
    assertReadEnabled();
    return mTransform * AcGePoint3d(0.0, 0.0, 0.0);
}

double AsdkVisualStyle::width() const
{
    assertReadEnabled();
    AcGeVector3d widthVec = mTransform * AcGeVector3d(2.0, 0.0, 0.0);
    return widthVec.length();
}

double AsdkVisualStyle::height() const
{
    assertReadEnabled();
    AcGeVector3d heightVec = mTransform * AcGeVector3d(0.0, 2.0, 0.0);
    return heightVec.length();
}

AcDbHardPointerId AsdkVisualStyle::visualStyleId(void) const
{
    assertReadEnabled();
    return mVisualStyleId;
}

Acad::ErrorStatus AsdkVisualStyle::setVisualStyleId(const AcDbHardPointerId &visualStyleId)
{
    assertWriteEnabled();
    mVisualStyleId = visualStyleId;
    if (mVisualStyleId.isEffectivelyErased())
        mVisualStyleId = AcDbObjectId::kNull;
    return Acad::eOk;
}

Acad::ErrorStatus AsdkVisualStyle::setTransform(const AcGeMatrix3d& xform)
{
    assertWriteEnabled();
    mTransform = xform;
    recordGraphicsModified();
    return Acad::eOk;
}

// Geometry helper functions
//

inline AcGePoint3d AsdkVisualStyle::left(void) const
{
    return mTransform * AcGePoint3d(-1.0, 0.0, 0.0);
}

inline AcGePoint3d AsdkVisualStyle::right(void) const
{
    return mTransform * AcGePoint3d(1.0, 0.0, 0.0);
}

inline AcGePoint3d AsdkVisualStyle::top(void) const
{
    return mTransform * AcGePoint3d(0.0, 1.0, 0.0);
}

inline AcGePoint3d AsdkVisualStyle::bottom(void) const
{
    return mTransform * AcGePoint3d(0.0, -1.0, 0.0);
}

inline void AsdkVisualStyle::getRectPts(AcGePoint3d rectPts[5], const AcGeMatrix3d &vstyle) const
{
    rectPts[0] = vstyle * AcGePoint3d(-1.0, -1.0, 0.0);
    rectPts[1] = vstyle * AcGePoint3d(-1.0,  1.0, 0.0);
    rectPts[2] = vstyle * AcGePoint3d( 1.0,  1.0, 0.0);
    rectPts[3] = vstyle * AcGePoint3d( 1.0, -1.0, 0.0);
    rectPts[4] = vstyle * AcGePoint3d(-1.0, -1.0, 0.0);
}

void AsdkVisualStyle::getAllRectPts(AcGePoint3d allRectPts[kRectRows][kRectCols][5]) const
{
    double scaleX = 1.0 / kRectCols;
    double scaleY = 1.0 / kRectRows;
    AcGeMatrix3d scaleVStyle;
    AcGeScale3d(scaleX, scaleY, 1.0).getMatrix(scaleVStyle);

    int i, j;
    double translateX, translateY;

    for (i = 0, translateY = scaleY - 1.0; 
         i < kRectRows; 
         ++i, translateY += scaleY * 2.0) 
    {
        for (j = 0, translateX = scaleX - 1.0; 
             j < kRectCols; 
             ++j, translateX += scaleX * 2.0) 
        {
            AcGeMatrix3d translateVStyle;
            translateVStyle.setToTranslation(AcGeVector3d(translateX, translateY, 0.0));
            getRectPts(allRectPts[i][j], mTransform * translateVStyle * scaleVStyle);
        }
        
    }
}

void AsdkVisualStyle::getAllSpherePts(AcGePoint3d allSpherePts[kRectRows][kRectCols]) const
{
    double scaleX = 1.0 / kRectCols;
    double scaleY = 1.0 / kRectRows;
    AcGeMatrix3d scaleVStyle, vstyleMat;
    AcGeScale3d(scaleX, scaleY, 1.0).getMatrix(scaleVStyle);

    int i, j;
    double translateX, translateY;

    for (i = 0, translateY = scaleY - 1.0; 
         i < kRectRows; 
         ++i, translateY += scaleY * 2.0) 
    {
        for (j = 0, translateX = scaleX - 1.0; 
             j < kRectCols; 
             ++j, translateX += scaleX * 2.0) 
        {
            AcGeMatrix3d translateVStyle;
            translateVStyle.setToTranslation(AcGeVector3d(translateX, translateY, 0.0));
            vstyleMat = mTransform * translateVStyle * scaleVStyle;
            allSpherePts[i][j] = vstyleMat * AcGePoint3d(0.0, 0.0, 0.0);
        }
        
    }
}

// Osnap helper functions
//
Acad::ErrorStatus AsdkVisualStyle::osnapNear(const AcGePoint3d& pickPoint,
                                          AcGePoint3dArray& snapPoints) const
{
    // Osnap near to the entity's quad points
    return osnapQuad(pickPoint, snapPoints);
}

Acad::ErrorStatus AsdkVisualStyle::osnapCen(const AcGePoint3d& pickPoint,
                                         AcGePoint3dArray& snapPoints) const
{
    // Osnap center to the entity center
    snapPoints.append(center());
    return Acad::eOk;
}

Acad::ErrorStatus AsdkVisualStyle::osnapQuad(const AcGePoint3d& pickPoint,
                                          AcGePoint3dArray& snapPoints) const
{
    // Osnap quad to the entity's quad points
    snapPoints.append(right());
    snapPoints.append(top());
    snapPoints.append(left());
    snapPoints.append(bottom());
    
    return Acad::eOk;
}

// AcDbEntity protocol
//

Acad::ErrorStatus AsdkVisualStyle::transformBy(const AcGeMatrix3d& xform)
{
    assertWriteEnabled();
    mTransform.preMultBy(xform);
    recordGraphicsModified();
    return Acad::eOk;
}

Acad::ErrorStatus AsdkVisualStyle::getGeomExtents(AcDbExtents& extents) const
{
	assertReadEnabled();

    // Get geometry
    AcGePoint3d allRectPts[kRectRows][kRectCols][5];
    getAllRectPts(allRectPts);

    // Set extents to encompass all geometry
    int i, j, k;
    extents = AcDbExtents();
    for (i = 0; i < kRectRows; ++i)
        for (j = 0; j < kRectCols; ++j)
            for (k = 0; k < 5; ++k)
                extents.addPoint(allRectPts[i][j][k]);

    return Acad::eOk;
}


Acad::ErrorStatus AsdkVisualStyle::getOsnapPoints(
    AcDb::OsnapMode     osnapMode,
    Adesk::GsMarker      gsSelectionMark,
    const AcGePoint3d&  pickPoint,
    const AcGePoint3d&  lastPoint,
    const AcGeMatrix3d& viewXform,
    AcGePoint3dArray&   snapPoints,
    AcDbIntArray&       geomIds) const
{
    assertReadEnabled();

    switch(osnapMode) {
    case AcDb::kOsModeNear:
        return osnapNear(pickPoint, snapPoints);
    case AcDb::kOsModeCen:
        return osnapCen(pickPoint, snapPoints);
    case AcDb::kOsModeQuad:
        return osnapQuad(pickPoint, snapPoints);
    }

    return Acad::eInvalidInput;
}

Acad::ErrorStatus AsdkVisualStyle::getGripPoints(AcGePoint3dArray& gripPoints,
                                              AcDbIntArray& osnapMasks,
                                              AcDbIntArray& geomIds) const
{
    // Grip points are center plus quad points
    assertReadEnabled();

    gripPoints.append(center());
    gripPoints.append(right());
    gripPoints.append(top());
    gripPoints.append(left());
    gripPoints.append(bottom());

    return Acad::eOk;
}

void AsdkVisualStyle::stretchGrip (const AcGePoint3d &gripPt, 
                                const AcGeVector3d &offset,
                                bool bHorizontal)
{
    AcGeMatrix3d scaleVStyle;
    AcGeVector3d scaleVec, gripVec, gripOffsetVec;
    double &scale = bHorizontal ? scaleVec.x : scaleVec.y;

    scaleVec = AcGeVector3d(1.0, 1.0, 1.0);
    gripVec = gripPt - center();
    gripOffsetVec = gripVec + offset;

    if (!gripVec.isZeroLength() && !gripOffsetVec.isZeroLength())
        scale *= gripOffsetVec.length() / gripVec.length();
    AcGeScale3d(scaleVec.x, scaleVec.y, scaleVec.z).getMatrix(scaleVStyle);

    setTransform(mTransform * scaleVStyle);
}

Acad::ErrorStatus AsdkVisualStyle::moveGripPointsAt(const AcDbIntArray& indices,
                                                 const AcGeVector3d& offset)
{
    assertWriteEnabled();

    for(int i = 0; i < indices.length(); i++) {
        int idx = indices[i];
        switch(idx) {

        // Stretch center grip
        case 0: transformBy(AcGeMatrix3d::translation(offset));
            break;

        // Stretch right grip
        case 1: stretchGrip(right(), offset, true);  
            break;

        // Stretch top grip
        case 2: stretchGrip(top(), offset, false);
            break;

        // Stretch left grip
        case 3: stretchGrip(left(), offset, true);
            break;

        // Stretch bottom grip
        case 4: stretchGrip(bottom(), offset, false);
            break;
        }
    }

    return Acad::eOk;
}

Acad::ErrorStatus AsdkVisualStyle::getStretchPoints(AcGePoint3dArray& stretchPoints) const
{
    assertReadEnabled();
    AcDbIntArray osnapModes;
    AcDbIntArray geomIds;
    return getGripPoints(stretchPoints, osnapModes, geomIds);
}

Acad::ErrorStatus AsdkVisualStyle::moveStretchPointsAt(
    const AcDbIntArray& indices,
    const AcGeVector3d& offset)
{
    assertWriteEnabled();
    return moveGripPointsAt(indices, offset);
}

Acad::ErrorStatus AsdkVisualStyle::explode(AcDbVoidPtrArray& entities) const
{
    assertReadEnabled();

    AcDbExtents extents;
    getGeomExtents(extents);

    AcGePoint3d pts[4];
    pts[0] = extents.minPoint();
    pts[1] = AcGePoint3d(extents.minPoint().x, extents.maxPoint().y, 0.0);
    pts[2] = extents.maxPoint();
    pts[3] = AcGePoint3d(extents.maxPoint().x, extents.minPoint().y, 0.0);

    AcDbFace *pFace = new AcDbFace(pts[0], pts[1], pts[2], pts[3], 
                                   true, true, true, true);
    entities.append(pFace);
    return Acad::eOk;
}

void AsdkVisualStyle::saveAs(AcGiWorldDraw *wd, AcDb::SaveType saveType)
{
    AcGiRegenType rtype = wd->regenType();

    if(AcDb::kR12Save == saveType)
        wd->subEntityTraits().setFillType(kAcGiFillNever);
    else if(AcDb::kR13Save == saveType) // proxy graphics save
        wd->subEntityTraits().setFillType(kAcGiFillAlways);

    worldDraw(wd);
}

void AsdkVisualStyle::list() const
{
    assertReadEnabled();
    AcDbEntity::list();

    AcGePoint3d cen(center());
    acutPrintf(ACRX_T("%12s center point,"),ACRX_T(" "));
    acutPrintf(ACRX_T("X=%9.16q0  Y=%9.16q0  Z=%9.16q0\n"), cen[X], cen[Y], cen[Z]);
}

// AcDbObject protocol
//
Acad::ErrorStatus AsdkVisualStyle::dwgInFields(AcDbDwgFiler *filer)
{
    assertWriteEnabled();

    // Read base entity
    AcDbEntity::dwgInFields(filer);

    // Read version
    double version;
    filer->readItem(&version);

    if (version > kCurrentVersionNumber){
        acutPrintf(ACRX_T("\nNew version of AsdkVisualStyle object found (version %.1f found, version %.1f supported): upgrade your VisualStyle.dbx to enable these objects."), version, kCurrentVersionNumber);
        return Acad::eMakeMeProxy;
    }

    // Read transform
    int i, j;
    for (i = 0; i < 4; ++i)
        for (j = 0; j < 4; ++j)
            filer->readItem(&mTransform.entry[i][j]);

    // Read visual style id (hard pointer)
    filer->readItem(&mVisualStyleId);

    return filer->filerStatus();
}

Acad::ErrorStatus AsdkVisualStyle::dwgOutFields(AcDbDwgFiler *filer) const
{
    assertReadEnabled();

    // Write base entity
    AcDbEntity::dwgOutFields(filer);

    // Write version
    filer->writeItem(kCurrentVersionNumber);

    // Write transform
    int i, j;
    for (i = 0; i < 4; ++i)
        for (j = 0; j < 4; ++j)
            filer->writeItem(mTransform.entry[i][j]);

    // Write visual style id
    if (mVisualStyleId.isEffectivelyErased())
        filer->writeItem((AcDbHardPointerId)(AcDbObjectId::kNull));
    else 
        filer->writeItem(mVisualStyleId);
   
    return filer->filerStatus();
}

Acad::ErrorStatus AsdkVisualStyle::dxfInFields(AcDbDxfFiler *filer)
{
    assertWriteEnabled();

    // Read entity
    Acad::ErrorStatus es = AcDbEntity::dxfInFields(filer);
    if (es != Acad::eOk)
        return es;

    // Read our data
    if(!filer->atSubclassData(kClassName))
        return Acad::eBadDxfSequence;
    struct resbuf rb;
    if ((es = filer->readItem(&rb)) != Acad::eOk)
        return es;

    // Read version
    if (AcDb::kDxfReal != rb.restype) {
        acutPrintf(ACRX_T("\nNo version information found in object definition."));
        return Acad::eMakeMeProxy;
    }
    if (rb.resval.rreal > kCurrentVersionNumber) {
        acutPrintf(ACRX_T("\nNew version of AsdkVisualStyle object found (version %.1f): upgrade your VisualStyle.dbx to enable these objects."), rb.resval.rreal);
        return Acad::eMakeMeProxy;
    }

    // Read transform, visual style id
    double vstyleEntry;
    int i = 0, j = 0;
    while(es == Acad::eOk) {
        if((es = filer->readItem(&rb)) == Acad::eOk) {
            switch(rb.restype) {
            case AcDb::kDxfReal+1:
                vstyleEntry = rb.resval.rreal;
                mTransform.entry[i][j] = vstyleEntry;
                if (++j > 3) {
                    j = 0;
                    ++i;
                }
                break;
            case AcDb::kDxfHardPointerId:
                acdbGetObjectId(mVisualStyleId, rb.resval.rlname);
            default:
                break;
            }
        }
    }

    return filer->filerStatus();
}

Acad::ErrorStatus AsdkVisualStyle::dxfOutFields(AcDbDxfFiler *filer) const
{
    assertReadEnabled();

    // Write entity
    AcDbEntity::dxfOutFields(filer);

    // Write our data
    filer->writeItem(AcDb::kDxfSubclass, kClassName);

    // Write version number
    filer->writeItem(AcDb::kDxfReal, kCurrentVersionNumber);

    // Write transform
    int i, j;
    for (i = 0; i < 4; ++i)
        for (j = 0; j < 4; ++j)
            filer->writeItem(AcDb::kDxfReal+1, mTransform.entry[i][j]);

    // Write visual style id
    if (mVisualStyleId != AcDbObjectId::kNull && !mVisualStyleId.isEffectivelyErased())
        filer->writeItem(AcDb::kDxfHardPointerId, mVisualStyleId);

    return filer->filerStatus();
}

// Drawing helper function
//
void AsdkVisualStyle::subEntityAttributeDraw (AcGiWorldDraw *pWorldDraw, int sphereNum)
{
    pWorldDraw->subEntityTraits().setColor(sphereNum);

    switch (sphereNum) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
        pWorldDraw->subEntityTraits().setVisualStyle(mVisualStyleId);
        break;
    case 2:
    case 4:
    case 6:
    case 8:
        pWorldDraw->subEntityTraits().setVisualStyle(AcDbObjectId::kNull);
        break;
    }
}

// AcGiDrawable protocol
//
Adesk::UInt32 AsdkVisualStyle::setAttributes (AcGiDrawableTraits* pTraits)
{
    Adesk::UInt32 status = AcDbEntity::setAttributes(pTraits);
    pTraits->setVisualStyle(mVisualStyleId);
    return status;
}

Adesk::Boolean AsdkVisualStyle::worldDraw(AcGiWorldDraw *pWorldDraw)
{
    assertReadEnabled();

    AcGePoint3d allRectPts[kRectRows][kRectCols][5];
    getAllRectPts(allRectPts);

    AcGePoint3d allSpherePts[kRectRows][kRectCols];
    getAllSpherePts(allSpherePts);

    int i, j;
    for (i = 0; i < kRectRows; ++i)
        for (j = 0; j < kRectCols; ++j)
        {
            // Draw different colors and visual styles depending on sphere
            int sphereNum = i * kRectCols + j + 1;
            subEntityAttributeDraw(pWorldDraw, sphereNum);

            AcGePoint3d center = allSpherePts[i][j];
            double radius = (allRectPts[i][j][2].x - allRectPts[i][j][1].x) / 2;

            // Draw sphere
            AcDb3dSolid* pSolid = new AcDb3dSolid;
            pSolid->setColorIndex(0);
            pSolid->createSphere(radius);
            pSolid->transformBy( transform(center) );
            pWorldDraw->geometry().draw(pSolid);
        }

    return Adesk::kTrue;
}

AcGeMatrix3d AsdkVisualStyle::transform(AcGePoint3d center)
{
    AcGeMatrix3d transMat;
    transMat.setToTranslation(center.asVector());
    AcGeMatrix3d ucsToWcsMat;
    acdbUcsMatrix(ucsToWcsMat);
    return ucsToWcsMat * transMat;
}