//
// (C) Copyright 2002-2006 by Autodesk, Inc. 
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

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "dbproxy.h"
#include "dbtrans.h"
#include "AsdkMaterial.h"



ACRX_DXF_DEFINE_MEMBERS(AsdkMaterial, AcDbEntity,
                        AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,
                        AcDbProxyEntity::kAllAllowedBits,
                        ASDKMATERIAL, AsdkMaterialDb|Product: ObjectDBX Enabler for Material Entity|Company: Autodesk Developer Consulting Group|Website: www.autodesk.com/adn/devhelp
                        );

MAKE_ACDBOPENOBJECT_FUNCTION(AsdkMaterial);

AsdkMaterial::AsdkMaterial()
{
    assertWriteEnabled();
    mTransform.setToIdentity();
    setColorIndex(0); // white/black
}

AsdkMaterial::~AsdkMaterial()
{
}

// AsdkMaterial protocol
//

AcGePoint3d AsdkMaterial::center() const
{
    assertReadEnabled();
    return mTransform * AcGePoint3d(0.0, 0.0, 0.0);
}

double AsdkMaterial::width() const
{
    assertReadEnabled();
    AcGeVector3d widthVec = mTransform * AcGeVector3d(2.0, 0.0, 0.0);
    return widthVec.length();
}

double AsdkMaterial::height() const
{
    assertReadEnabled();
    AcGeVector3d heightVec = mTransform * AcGeVector3d(0.0, 2.0, 0.0);
    return heightVec.length();
}

AcDbHardPointerId AsdkMaterial::materialId(void) const
{
    assertReadEnabled();
    return mMaterialId;
}

Acad::ErrorStatus AsdkMaterial::setMaterialId(const AcDbHardPointerId &materialId)
{
    assertWriteEnabled();
    mMaterialId = materialId;
    if (mMaterialId.isEffectivelyErased())
        mMaterialId = AcDbObjectId::kNull;
    return Acad::eOk;
}

Acad::ErrorStatus AsdkMaterial::setTransform(const AcGeMatrix3d& xform)
{
    assertWriteEnabled();
    mTransform = xform;
    recordGraphicsModified();
    return Acad::eOk;
}

// Geometry helper functions
//

inline AcGePoint3d AsdkMaterial::left(void) const
{
    return mTransform * AcGePoint3d(-1.0, 0.0, 0.0);
}

inline AcGePoint3d AsdkMaterial::right(void) const
{
    return mTransform * AcGePoint3d(1.0, 0.0, 0.0);
}

inline AcGePoint3d AsdkMaterial::top(void) const
{
    return mTransform * AcGePoint3d(0.0, 1.0, 0.0);
}

inline AcGePoint3d AsdkMaterial::bottom(void) const
{
    return mTransform * AcGePoint3d(0.0, -1.0, 0.0);
}

inline void AsdkMaterial::getRectPts(AcGePoint3d rectPts[5], const AcGeMatrix3d &mat) const
{
    rectPts[0] = mat * AcGePoint3d(-1.0, -1.0, 0.0);
    rectPts[1] = mat * AcGePoint3d(-1.0,  1.0, 0.0);
    rectPts[2] = mat * AcGePoint3d( 1.0,  1.0, 0.0);
    rectPts[3] = mat * AcGePoint3d( 1.0, -1.0, 0.0);
    rectPts[4] = mat * AcGePoint3d(-1.0, -1.0, 0.0);
}

void AsdkMaterial::getAllRectPts(AcGePoint3d allRectPts[kRectRows][kRectCols][5]) const
{
    double scaleX = 1.0 / kRectCols;
    double scaleY = 1.0 / kRectRows;
    AcGeMatrix3d scaleMat;
    AcGeScale3d(scaleX, scaleY, 1.0).getMatrix(scaleMat);

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
            AcGeMatrix3d translateMat;
            translateMat.setToTranslation(AcGeVector3d(translateX, translateY, 0.0));
            getRectPts(allRectPts[i][j], mTransform * translateMat * scaleMat);
        }
        
    }
}

// Osnap helper functions
//
Acad::ErrorStatus AsdkMaterial::osnapNear(const AcGePoint3d& pickPoint,
                                          AcGePoint3dArray& snapPoints) const
{
    // Osnap near to the entity's quad points
    return osnapQuad(pickPoint, snapPoints);
}

Acad::ErrorStatus AsdkMaterial::osnapCen(const AcGePoint3d& pickPoint,
                                         AcGePoint3dArray& snapPoints) const
{
    // Osnap center to the entity center
    snapPoints.append(center());
    return Acad::eOk;
}

Acad::ErrorStatus AsdkMaterial::osnapQuad(const AcGePoint3d& pickPoint,
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

Acad::ErrorStatus AsdkMaterial::transformBy(const AcGeMatrix3d& xform)
{
    assertWriteEnabled();
    mTransform.preMultBy(xform);
    recordGraphicsModified();
    return Acad::eOk;
}

Acad::ErrorStatus AsdkMaterial::getGeomExtents(AcDbExtents& extents) const
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


Acad::ErrorStatus AsdkMaterial::getOsnapPoints(
    AcDb::OsnapMode     osnapMode,
    int                 gsSelectionMark,
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

Acad::ErrorStatus AsdkMaterial::getGripPoints(AcGePoint3dArray& gripPoints,
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

void AsdkMaterial::stretchGrip (const AcGePoint3d &gripPt, 
                                const AcGeVector3d &offset,
                                bool bHorizontal)
{
    AcGeMatrix3d scaleMat;
    AcGeVector3d scaleVec, gripVec, gripOffsetVec;
    double &scale = bHorizontal ? scaleVec.x : scaleVec.y;

    scaleVec = AcGeVector3d(1.0, 1.0, 1.0);
    gripVec = gripPt - center();
    gripOffsetVec = gripVec + offset;

    if (!gripVec.isZeroLength() && !gripOffsetVec.isZeroLength())
        scale *= gripOffsetVec.length() / gripVec.length();
    AcGeScale3d(scaleVec.x, scaleVec.y, scaleVec.z).getMatrix(scaleMat);

    setTransform(mTransform * scaleMat);
}

Acad::ErrorStatus AsdkMaterial::moveGripPointsAt(const AcDbIntArray& indices,
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

Acad::ErrorStatus AsdkMaterial::getStretchPoints(AcGePoint3dArray& stretchPoints) const
{
    assertReadEnabled();
    AcDbIntArray osnapModes;
    AcDbIntArray geomIds;
    return getGripPoints(stretchPoints, osnapModes, geomIds);
}

Acad::ErrorStatus AsdkMaterial::moveStretchPointsAt(
    const AcDbIntArray& indices,
    const AcGeVector3d& offset)
{
    assertWriteEnabled();
    return moveGripPointsAt(indices, offset);
}

Acad::ErrorStatus AsdkMaterial::explode(AcDbVoidPtrArray& entities) const
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

void AsdkMaterial::saveAs(AcGiWorldDraw *wd, AcDb::SaveType saveType)
{
    AcGiRegenType rtype = wd->regenType();

    if(AcDb::kR12Save == saveType)
        wd->subEntityTraits().setFillType(kAcGiFillNever);
    else if(AcDb::kR13Save == saveType) // proxy graphics save
        wd->subEntityTraits().setFillType(kAcGiFillAlways);

    worldDraw(wd);
}

void AsdkMaterial::list() const
{
    assertReadEnabled();
    AcDbEntity::list();

    AcGePoint3d cen(center());
    acutPrintf(_T("%12s center point,"),_T(" "));
    acutPrintf(_T("X=%9.16q0  Y=%9.16q0  Z=%9.16q0\n"), cen[X], cen[Y], cen[Z]);
}

// AcDbObject protocol
//
Acad::ErrorStatus AsdkMaterial::dwgInFields(AcDbDwgFiler *filer)
{
    assertWriteEnabled();

    // Read base entity
    AcDbEntity::dwgInFields(filer);

    // Read version
    double version;
    filer->readItem(&version);

    if (version > kCurrentVersionNumber){
        acutPrintf(_T("\nNew version of AsdkMaterial object found (version %.1f found, version %.1f supported): upgrade your Material.dbx to enable these objects."), version, kCurrentVersionNumber);
        return Acad::eMakeMeProxy;
    }

    // Read transform
    int i, j;
    for (i = 0; i < 4; ++i)
        for (j = 0; j < 4; ++j)
            filer->readItem(&mTransform.entry[i][j]);

    // Read material id (hard pointer)
    filer->readItem(&mMaterialId);

    return filer->filerStatus();
}

Acad::ErrorStatus AsdkMaterial::dwgOutFields(AcDbDwgFiler *filer) const
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

    // Write material id
    if (mMaterialId.isEffectivelyErased())
        filer->writeItem((AcDbHardPointerId)(AcDbObjectId::kNull));
    else 
        filer->writeItem(mMaterialId);
   
    return filer->filerStatus();
}

Acad::ErrorStatus AsdkMaterial::dxfInFields(AcDbDxfFiler *filer)
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
        acutPrintf(_T("\nNo version information found in object definition."));
        return Acad::eMakeMeProxy;
    }
    if (rb.resval.rreal > kCurrentVersionNumber) {
        acutPrintf(_T("\nNew version of AsdkMaterial object found (version %.1f): upgrade your Material.dbx to enable these objects."), rb.resval.rreal);
        return Acad::eMakeMeProxy;
    }

    // Read transform, material id
    double matEntry;
    int i = 0, j = 0;
    while(es == Acad::eOk) {
        if((es = filer->readItem(&rb)) == Acad::eOk) {
            switch(rb.restype) {
            case AcDb::kDxfReal+1:
                matEntry = rb.resval.rreal;
                mTransform.entry[i][j] = matEntry;
                if (++j > 3) {
                    j = 0;
                    ++i;
                }
                break;
            case AcDb::kDxfHardPointerId:
                acdbGetObjectId(mMaterialId, rb.resval.rlname);
            default:
                break;
            }
        }
    }

    return filer->filerStatus();
}

Acad::ErrorStatus AsdkMaterial::dxfOutFields(AcDbDxfFiler *filer) const
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

    // Write material id
    if (mMaterialId != AcDbObjectId::kNull && !mMaterialId.isEffectivelyErased())
        filer->writeItem(AcDb::kDxfHardPointerId, mMaterialId);

    return filer->filerStatus();
}

// Drawing helper function
//
void AsdkMaterial::subEntityAttributeDraw (AcGiWorldDraw *pWorldDraw, int rectNum)
{
    AcGiMapper mapper;
    AcGeMatrix3d translateMat, scaleMat, rotateMat;
    translateMat.setToTranslation(AcGeVector3d(-0.4, 1.2, 0.0));
    AcGeScale3d(0.4, -1.4, 1.0).getMatrix(scaleMat);
    rotateMat.setToRotation(3.14/6.0, AcGeVector3d(0.0, 0.0, 1.0));
    mapper.setTransform(translateMat * scaleMat * rotateMat);

    switch (rectNum) {
    case 1:
    case 7:
        // no material, red color
        pWorldDraw->subEntityTraits().setColor(1);
        break;

    case 2:
        pWorldDraw->subEntityTraits().setMapper(&mapper);
    case 8:
        // material with default mapper, by block color
        pWorldDraw->subEntityTraits().setColor(0);
        pWorldDraw->subEntityTraits().setMaterial(mMaterialId);
        break;

    case 3:
    case 9:
        // turn off any materials, orange color
        pWorldDraw->subEntityTraits().setColor(30);
        pWorldDraw->subEntityTraits().setMaterial(AcDbObjectId::kNull);
        pWorldDraw->subEntityTraits().setMapper(&AcGiMapper::kIdentity);
        break;

    default:
        // otherwise, use entity color
        pWorldDraw->subEntityTraits().setColor(colorIndex());
        break;
    }
}


// AcGiDrawable protocol
//
Adesk::UInt32 AsdkMaterial::setAttributes (AcGiDrawableTraits* pTraits)
{
    return AcDbEntity::setAttributes(pTraits);
}

Adesk::Boolean AsdkMaterial::worldDraw(AcGiWorldDraw *pWorldDraw)
{
    assertReadEnabled();

    AcGePoint3d allRectPts[kRectRows][kRectCols][5];
    getAllRectPts(allRectPts);

    int i, j;
    for (i = 0; i < kRectRows; ++i)
        for (j = 0; j < kRectCols; ++j)
        {
            // Draw different materials/mappers depending on rectangle
            int rectNum = i * kRectCols + j + 1;
            subEntityAttributeDraw(pWorldDraw, rectNum);

            // Draw rectangle
            pWorldDraw->geometry().polygon(5, allRectPts[i][j]);
        }

    return Adesk::kTrue;
}


