//
// (C) Copyright 2002-2008 by Autodesk, Inc. 
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

// AsdkMaterial custom object.

#pragma once
#pragma warning(disable: 4275 4251)

#include "tchar.h"

#ifdef _MATERIALDB_
#define DLLIMPEXP __declspec(dllexport)
#else
#define DLLIMPEXP 
#endif

#ifndef ASDKMATERIALDB_DBXSERVICE
#define ASDKMATERIALDB_DBXSERVICE _T("ASDKMATERIALDB_DBXSERVICE")
#endif

#include <math.h>

#include "dbents.h"
#include "acgi.h"
#include "objbase.h"
#include "dbmaterial.h"
#include "tchar.h"

const TCHAR   kClassName[]          = _T("AsdkMaterial");
const double kCurrentVersionNumber = 1.0;
const int    kRectCols             = 3;
const int    kRectRows             = 3;
const int    kMeshCols             = kRectCols + 1;
const int    kMeshRows             = kRectRows + 1;

class DLLIMPEXP AsdkMaterial : public AcDbEntity
{
public:

    ACRX_DECLARE_MEMBERS(AsdkMaterial);

    AsdkMaterial();
    virtual ~AsdkMaterial();

    // AsdkMaterial protocol
    //
    AcGePoint3d center (void) const;
    double      width  (void) const;
    double      height (void) const;

    Acad::ErrorStatus setMaterialId(const AcDbHardPointerId &ownedId);
    AcDbHardPointerId materialId(void) const;

    Acad::ErrorStatus setTransform(const AcGeMatrix3d& xform);

    // AcDbEntity protocol
    //
    virtual Acad::ErrorStatus transformBy(const AcGeMatrix3d& xform);

    virtual Acad::ErrorStatus getGeomExtents(AcDbExtents& extents) const;

    virtual Acad::ErrorStatus getOsnapPoints(AcDb::OsnapMode osnapMode,
                                             Adesk::GsMarker gsSelectionMark,
                                             const AcGePoint3d& pickPoint,
                                             const AcGePoint3d& lastPoint,
                                             const AcGeMatrix3d& viewXform,
                                             AcGePoint3dArray& snapPoints,
                                             AcDbIntArray& geomIds) const;

    virtual Acad::ErrorStatus getGripPoints(AcGePoint3dArray& gripPoints,
                                            AcDbIntArray& osnapModes,
                                            AcDbIntArray& geomIds) const;
    virtual Acad::ErrorStatus moveGripPointsAt(const AcDbIntArray& indices,
                                               const AcGeVector3d& offset);

    virtual Acad::ErrorStatus getStretchPoints(AcGePoint3dArray& stretchPoints) const;
    virtual Acad::ErrorStatus moveStretchPointsAt(const AcDbIntArray& indices,
                                                  const AcGeVector3d& offset);

    virtual Acad::ErrorStatus explode(AcDbVoidPtrArray& entitySet) const;
    virtual void saveAs(AcGiWorldDraw* mode, AcDb::SaveType st);
    virtual void list() const;

    // AcDbObject protocol
    //
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;

    // AcGiDrawable protocol
    //
    virtual Adesk::UInt32  setAttributes(AcGiDrawableTraits* pTraits);
    virtual Adesk::Boolean worldDraw     (AcGiWorldDraw* pWorldDraw);
    virtual void           viewportDraw  (AcGiViewportDraw* pVpDraw);

private:
    AcGeMatrix3d      mTransform;
    AcDbHardPointerId mMaterialId; 
    bool              mbIsLandscape;

    // Geometry helper functions
    //
    AcGePoint3d left   (void) const;
    AcGePoint3d right  (void) const;
    AcGePoint3d top    (void) const;
    AcGePoint3d bottom (void) const;

    void getRectPts    (AcGePoint3d rectPts[5], const AcGeMatrix3d & mat) const;
    void getAllRectPts (AcGePoint3d allRectPts[kRectRows][kRectCols][5]) const;
    void getMeshPts    (AcGePoint3d meshPts[kMeshRows][kMeshCols]) const;

    // Grip helper function
    //
    void stretchGrip (const AcGePoint3d &gripPt, 
                      const AcGeVector3d &offset,
                      bool bHorizontal);

    // Osnap helper functions
    //
    Acad::ErrorStatus osnapNear (const AcGePoint3d&  pickPoint,
                                 AcGePoint3dArray&   snapPoints) const;
    Acad::ErrorStatus osnapCen  (const AcGePoint3d&  pickPoint,
                                 AcGePoint3dArray&   snapPoints) const;
    Acad::ErrorStatus osnapQuad (const AcGePoint3d&  pickPoint,
                                 AcGePoint3dArray&   snapPoints) const;

    // Draw helper functions
    //
    void subEntityAttributeDraw (AcGiWorldDraw *pWorldDraw, int rectNum);
    bool isLandscape            (void);

    // New/delete overrides
    //
    void *operator new[](size_t nSize) { return 0; }
    void operator delete[](void *p) {};
    void *operator new[](size_t nSize, const TCHAR *file, int line) { return 0; }
};
