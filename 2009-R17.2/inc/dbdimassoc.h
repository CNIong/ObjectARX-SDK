
// (C) Copyright 2000-2008 by Autodesk, Inc.
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
// FILE: dimassoc.h
//
// DESCRIPTION: Declaration for Dimension Associativity API 
//              and AcDbDimAssoc class.

#ifndef AD_DBDIMASSOC_H
#define AD_DBDIMASSOC_H

class AcDbPointRef;
class AcDbLeader;
class AcDbMLeader;

// Exported AcDbDimAssoc class and some global APIs for external use.

// Class declaration for AcDbDimAssoc
//
class AcDbDimAssoc : public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbDimAssoc);
    //ACRX_DECLARE_MEMBERS(AcDbDimAssoc);

    enum { kMaxPointRefs = 4 };

    enum PointType {
        kXline1Point      = 0,
        kXline2Point      = 1,
        kOriginPoint      = 0,
        kDefiningPoint    = 1,
        kXline1Start      = 0,
        kXline1End        = 1,
        kXline2Start      = 2,
        kXline2End        = 3,
        kVertexPoint      = 2,
        kChordPoint       = 0,
        kCenterPoint      = 1,
        kFarChordPoint    = 1,
        kOverrideCenterPoint   = 2,
        kAngLineStart     = 2,
        kJogPoint         = 3,
        kAngLineEnd       = 3,
        kLeaderPoint      = 0
    };

    enum AssocFlags {
        kFirstPointRef     = 1,
        kSecondPointRef    = 2,
        kThirdPointRef     = 4,
        kFourthPointRef    = 8
    };

    enum RotatedDimType {
        kUnknown       = 0,
        kParallel      = 1,
        kPerpendicular = 2
    };

    AcDbDimAssoc();
    virtual ~AcDbDimAssoc();
    AcDbObjectId dimObjId() const;
    Acad::ErrorStatus setDimObjId(const AcDbObjectId& dimId);
    Acad::ErrorStatus setAssocFlag(int ptType, bool value);
    void setAssocFlag(int assocFlg);
    bool assocFlag(int ptType) const;
    int assocFlag(void);
    Acad::ErrorStatus setPointRef(int ptType, AcDbPointRef* ptRef);
    const AcDbPointRef *pointRef(int ptType) const;
    Acad::ErrorStatus setRotatedDimType(RotatedDimType dimType);
    RotatedDimType    rotatedDimType() const;
    Acad::ErrorStatus addToPointRefReactor();
    Acad::ErrorStatus addToDimensionReactor(bool isAdd = true);
    Acad::ErrorStatus removePointRef(int ptType);
    Acad::ErrorStatus updateDimension(bool update = true, bool skipReactors = false);
    Acad::ErrorStatus removeAssociativity(bool force = true);
    bool              isTransSpatial() const;
    Acad::ErrorStatus setTransSpatial(bool value);
    Acad::ErrorStatus startCmdWatcher();

    Acad::ErrorStatus startOopsWatcher(bool bAddAll = true);
    void              removeOopsWatcher(void);
    Acad::ErrorStatus restoreAssocFromOopsWatcher(void);
    bool              hasOopsWatcher(void) const;
    Acad::ErrorStatus post(AcDbObjectId dimId, 
                           AcDbObjectId& dimAssocId, 
                           bool isActive = true);
    Acad::ErrorStatus getDimAssocGeomIds(AcDbObjectIdArray& geomIds) const;
    bool              isAllGeomErased() const;

    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler*);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*) const;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler*);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*) const;
    virtual void modifiedGraphics(const AcDbEntity* pObj);

    virtual Acad::ErrorStatus swapReferences (const AcDbIdMapping& idMap);


    Acad::ErrorStatus updateFillet(const AcDbObjectIdArray& ids);
    Acad::ErrorStatus updateAssociativity(const AcDbObjectIdArray& ids);
    Acad::ErrorStatus updateXrefSubentPath();
    Acad::ErrorStatus updateSubentPath(AcDbIdMapping& idMap);
    void updateDueToMirror(bool wasInMirror);

protected:
    Acad::ErrorStatus   setPointRefReactor  (int ptType, 
                                             bool isAdd = true);
    Acad::ErrorStatus   removeDimExtDict    (void);
    bool                isPointBetweenRays  (const AcGePoint3d& vertex, 
                                             const AcGePoint3d& firstPt, 
                                             const AcGePoint3d& secondPt, 
                                             const AcGePoint3d& angPt,
                                             const AcGeVector3d& normal);
    Acad::ErrorStatus   updateDimension     (AcDbRotatedDimension* pRotDim, 
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimension     (AcDbAlignedDimension* pAlnDim, 
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimension     (AcDbRadialDimension* pRadDim, 
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimension     (AcDbRadialDimensionLarge* pRadDimLarge, 
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimension     (AcDbDiametricDimension* pDiaDim, 
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimension     (AcDb2LineAngularDimension* pA2Dim, 
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimension     (AcDb3PointAngularDimension* pA3Dim,
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimension     (AcDbOrdinateDimension* pOrdDim, 
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimension     (AcDbArcDimension* pArcDim, 
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimension     (AcDbLeader* pLeader, 
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimension     (AcDbMLeader* pMLeader, 
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimLineAndTextLocation(AcDbRotatedDimension* pAlnDim, 
                                             const AcGePoint3d* kpOldPts, 
                                             const AcGePoint3d* kpNewPts);
    Acad::ErrorStatus   updateDimLineAndTextLocation(AcDbAlignedDimension* pAlnDim, 
                                             const AcGePoint3d* pOldPts, 
                                             const AcGePoint3d* pNewPts);
    Acad::ErrorStatus   updateDimLineAndTextLocation(AcDb2LineAngularDimension* pA2Dim, 
                                             const AcGePoint3d* pOldPts, 
                                             const AcGePoint3d* pNewPts);
    Acad::ErrorStatus   updateDimLineAndTextLocation(AcDb3PointAngularDimension* pA3Dim, 
                                             const AcGePoint3d* pOldPts, 
                                             const AcGePoint3d* pNewPts);
    Acad::ErrorStatus   updateDimLineAndTextLocation(AcDbArcDimension* pArcDim, 
                                             const AcGePoint3d* kpOldPts, 
                                             const AcGePoint3d* kpNewPts);
    Acad::ErrorStatus   calculate3PointAngDimArcLocation(const AcGePoint3d* kpOldPts, 
                                             const AcGePoint3d& kOldArcPt, 
                                             const AcGePoint3d& kOldTextPt, 
                                             const AcGePoint3d* kpNewPts, 
                                             const AcGeVector3d& normal, 
                                             AcGePoint3d& newArcPt, 
                                             AcGePoint3d& newTextPt);
    Acad::ErrorStatus   calculate2LineAngDimArcLocation(const AcGePoint3d* kpOldPts, 
                                             const AcGePoint3d& kOldArcPt, 
                                             const AcGePoint3d& kOldTextPt, 
                                             const AcGePoint3d* kpNewPts, 
                                             const AcGeVector3d& kNormal, 
                                             AcGePoint3d& newArcPt, 
                                             AcGePoint3d& newTextPt);
};

// Post pDimAssoc object to database in the extension 
// dictionary of the given dimension.
//
Acad::ErrorStatus
acdbPostDimAssoc(AcDbObjectId dimId, AcDbDimAssoc* pDimAssoc, 
                 AcDbObjectId& dimAssocId, bool isActive = true);

// Perform forced update for the given associative dimension.
// 
Acad::ErrorStatus
acdbUpdateDimension(AcDbObjectId dimId);

// Perform forced update for the all dimensions in the database (DIMREGEN)
// 
Acad::ErrorStatus
acdbUpdateAllDimensions(AcDbDatabase* pDb);

// Get the AcDbDimAssoc objectId from the given dimension.
//
Acad::ErrorStatus
acdbGetDimAssocId(AcDbObjectId dimId, AcDbObjectId& dimAssocId);

// Get the AcDbDimAssoc objectId from the geometry in 
// AcDbPointRef object.
//
Acad::ErrorStatus
acdbGetDimAssocIds(AcDbObjectId entId, AcDbObjectIdArray& dimAssocIds);

// Verify whether the given idPath is a trans-spatial path
//
bool
acdbIsTransSpatial(const AcDbFullSubentPath& idPath);

#endif  //  AD_DBDIMASSOC_H
