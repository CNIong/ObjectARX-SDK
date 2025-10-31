#ifndef AD_DBPL_H
#define AD_DBPL_H 1
//
// (C) Copyright 1996-1999 by Autodesk, Inc.
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
// DESCRIPTION:  Lightweight polyline API header file.
//

#include "dbmain.h"
#include "dbcurve.h"

#include "gelnsg2d.h"
#include "gelnsg3d.h"
#include "gearc2d.h"
#include "gearc3d.h"
#include "gept2dar.h"
#include "dbboiler.h"

#pragma pack(push, 8)

class AcDb2dPolyline;

class AcDbPolyline : public AcDbCurve
{

public:
                      AcDbPolyline();
                      AcDbPolyline(unsigned int num_verts);
    virtual          ~AcDbPolyline();


    ACDB_DECLARE_MEMBERS(AcDbPolyline);


    //**********************************************************************
    // AcDbPolyline methods.
    //**********************************************************************

    Acad::ErrorStatus convertFrom(AcDbEntity*& pPline, 
                                  Adesk::Boolean transferId = Adesk::kTrue);
    Acad::ErrorStatus convertTo(AcDb2dPolyline*&  pPline,
                                Adesk::Boolean transferId = Adesk::kTrue) const;

    Acad::ErrorStatus getPointAt(unsigned int, AcGePoint3d& pt) const;

    enum SegType {
        kLine,
        kArc,
        kCoincident,
        kPoint,
        kEmpty
    };

    SegType           segType           (unsigned int index) const;

    Acad::ErrorStatus getLineSegAt      (unsigned int index,
                                         AcGeLineSeg2d& ln) const;
    Acad::ErrorStatus getLineSegAt      (unsigned int index,
                                         AcGeLineSeg3d& ln) const;
    Acad::ErrorStatus getArcSegAt       (unsigned int index,
                                         AcGeCircArc2d& arc) const;
    Acad::ErrorStatus getArcSegAt       (unsigned int index,
                                         AcGeCircArc3d& arc) const;
    virtual Adesk::Boolean onSegAt      (unsigned int index, const AcGePoint2d& pt2d,
                                         double& param) const;

    //**********************************************************************
    // AcDbPolyline methods.
    //**********************************************************************
   
    void              setClosed       (Adesk::Boolean);
    void              setPlinegen     (Adesk::Boolean);
    void              setElevation    (double);
    void              setThickness    (double);
    Acad::ErrorStatus setConstantWidth(double);
    Acad::ErrorStatus setNormal       (const AcGeVector3d&);

    Adesk::Boolean    isClosed        ()                        const;      
    Adesk::Boolean    isOnlyLines     ()                        const;
    Adesk::Boolean    hasPlinegen     ()                        const;
    double            elevation       ()                        const;
    double            thickness       ()                        const;
    Acad::ErrorStatus getConstantWidth(double&)                 const;
    AcGeVector3d      normal          ()                        const;

    Acad::ErrorStatus addVertexAt     (unsigned int index,
                                       const AcGePoint2d& pt,
                                       double bulge = 0.,
                                       double startWidth = -1.,
                                       double endWidth = -1);

    Acad::ErrorStatus removeVertexAt  (unsigned int index);

    unsigned int      numVerts        ()                        const;

    Acad::ErrorStatus getPointAt        (unsigned int index,
                                       AcGePoint2d& pt)         const;
    Acad::ErrorStatus getBulgeAt      (unsigned int index,
                                       double&      bulge)      const;
    Acad::ErrorStatus getWidthsAt     (unsigned int index,
                                       double&      startWidth,
                                       double&      endWidth)   const;

    Acad::ErrorStatus setPointAt      (unsigned int index,
                                       const AcGePoint2d& pt);
    Acad::ErrorStatus setBulgeAt      (unsigned int index,
                                       double       bulge);
    Acad::ErrorStatus setWidthsAt     (unsigned int index,
                                       double       startWidth,
                                       double       endWidth);

    Acad::ErrorStatus minimizeMemory  ();
    Acad::ErrorStatus maximizeMemory  ();

    void              reset           (Adesk::Boolean reuse,
                                       unsigned int numVerts);


    Adesk::Boolean     hasBulges       ()        const;
    Adesk::Boolean     hasWidth        ()        const;

    //**********************************************************************
    // AcDbCurve methods.
    //**********************************************************************

    virtual Adesk::Boolean    isPeriodic   () const;      
    virtual Adesk::Boolean    isPlanar     () const;

    virtual Acad::ErrorStatus getPlane       (AcGePlane&         plane, 
                                              AcDb::Planarity&   type) const; 

    virtual Acad::ErrorStatus getStartParam  (double&      startParam) const;
    virtual Acad::ErrorStatus getEndParam    (double&      endParam)   const;
    virtual Acad::ErrorStatus getStartPoint  (AcGePoint3d& startPoint) const;
    virtual Acad::ErrorStatus getEndPoint    (AcGePoint3d& endPoint)   const; 

    virtual Acad::ErrorStatus getPointAtParam(double             param, 
                                              AcGePoint3d&       point) const;
    virtual Acad::ErrorStatus getParamAtPoint(const AcGePoint3d& point,
                                              double&            param) const;
    virtual Acad::ErrorStatus getDistAtParam (double             param,
                                              double&            dist)  const;
    virtual Acad::ErrorStatus getParamAtDist (double             dist,
                                              double&            param) const; 
    virtual Acad::ErrorStatus getDistAtPoint (const AcGePoint3d& point,
                                              double&            dist)  const;
    virtual Acad::ErrorStatus getPointAtDist (double             dist,
                                              AcGePoint3d&       point) const;


    virtual Acad::ErrorStatus getFirstDeriv (double             param, 
                                          AcGeVector3d&      firstDeriv) const;
    virtual Acad::ErrorStatus getFirstDeriv (const AcGePoint3d& point, 
                                          AcGeVector3d&      firstDeriv) const;
    virtual Acad::ErrorStatus getSecondDeriv(double             param, 
                                          AcGeVector3d&      secondDeriv)const;
    virtual Acad::ErrorStatus getSecondDeriv(const AcGePoint3d& point, 
                                          AcGeVector3d&      secondDeriv)const;


    virtual Acad::ErrorStatus getClosestPointTo(const AcGePoint3d& givenPoint,
                                          AcGePoint3d&       pointOnCurve,
                                          Adesk::Boolean     extend = 
                                                               Adesk::kFalse) 
                                                               const;

    virtual Acad::ErrorStatus getClosestPointTo(const AcGePoint3d&  givenPoint,
                                          const AcGeVector3d& normal,
                                          AcGePoint3d&        pointOnCurve,
                                          Adesk::Boolean      extend = 
                                                                Adesk::kFalse) 
                                                                      const;

    virtual Acad::ErrorStatus getOrthoProjectedCurve(const AcGePlane&  plane,
                                          AcDbCurve*&       projectedCurve) 
                                                                      const;

    virtual Acad::ErrorStatus getProjectedCurve(const AcGePlane&    plane,
                                  const AcGeVector3d& projDir,
                                  AcDbCurve*&       projectedCurve) const;

    virtual Acad::ErrorStatus getOffsetCurves(double offsetDist,
                                  AcDbVoidPtrArray&  offsetCurves)  const;

    virtual Acad::ErrorStatus getSpline(AcDbSpline*& spline) const; 

    virtual Acad::ErrorStatus getSplitCurves(
                                  const AcGeDoubleArray& parameters,
                                  AcDbVoidPtrArray&  curveSegments) const;

    virtual Acad::ErrorStatus getSplitCurves(
                                  const AcGePoint3dArray& points,
                                  AcDbVoidPtrArray&       curveSegments) const;

    virtual Acad::ErrorStatus extend(double          newParam);

    virtual Acad::ErrorStatus extend(Adesk::Boolean     extendStart,
                                     const AcGePoint3d& toPoint);

    virtual Acad::ErrorStatus getArea(double& area) const; 


    //*************************************************************************
    // Overridden methods from AcDEntity
    //*************************************************************************

    virtual Acad::ErrorStatus getOsnapPoints(AcDb::OsnapMode osnapMode,
                                             int   gsSelectionMark,
                                             const AcGePoint3d&  pickPoint,
                                             const AcGePoint3d&  lastPoint,
                                             const AcGeMatrix3d& viewXform,
                                             AcGePoint3dArray&      snapPoints,
                                             AcDbIntArray&   geomIds)
                                             const;

    virtual Acad::ErrorStatus getGripPoints(AcGePoint3dArray&    gripPoints,
                                            AcDbIntArray& osnapMasks,
                                            AcDbIntArray& geomIds)
                                            const;

    virtual Acad::ErrorStatus moveGripPointsAt(const AcDbIntArray& indices,  
                                               const AcGeVector3d& offset);

    virtual Acad::ErrorStatus intersectWith(const AcDbEntity* ent,
                                            AcDb::Intersect intType,
                                            AcGePoint3dArray& points,
                                            int thisGsMarker  = 0,
                                            int otherGsMarker = 0)
                                            const;

    virtual Acad::ErrorStatus intersectWith(const AcDbEntity* ent,
                                             AcDb::Intersect intType,
                                             const AcGePlane& projPlane,
                                             AcGePoint3dArray& points,
                                             int thisGsMarker  = 0,
                                             int otherGsMarker = 0)
                                             const;

    virtual Acad::ErrorStatus getStretchPoints(AcGePoint3dArray&  stretchPoints)
                                               const;

    virtual Acad::ErrorStatus moveStretchPointsAt(const AcDbIntArray& 
                                                 indices,
                                                 const AcGeVector3d& offset);

    virtual Acad::ErrorStatus transformBy(const AcGeMatrix3d& xform);

    virtual Acad::ErrorStatus getTransformedCopy(const AcGeMatrix3d& xform,
                                                 AcDbEntity*& ent) const;

    virtual void              getEcs(AcGeMatrix3d& retVal) const;

    virtual Acad::ErrorStatus getGeomExtents(AcDbExtents& extents) const;

    virtual AcDbEntity*       subentPtr(const AcDbFullSubentPath& id) const;
    virtual Acad::ErrorStatus getSubentPathsAtGsMarker(
                                 AcDb::SubentType     type, 
                                 int                  gsMark,
                                 const AcGePoint3d&   pickPoint,
                                 const AcGeMatrix3d&  viewXform,
                                 int&                 numIds, 
                                 AcDbFullSubentPath*& subentIds,
                                 int                  numInserts,
                                 AcDbObjectId*        entAndInsertStack)
                                                                     const;

    virtual Acad::ErrorStatus explode(AcDbVoidPtrArray& entitySet) const;

    virtual Adesk::Boolean    worldDraw   (AcGiWorldDraw* mode);
    virtual void              viewportDraw(AcGiViewportDraw* mode);

    virtual Acad::ErrorStatus applyPartialUndo(AcDbDwgFiler* filer,
                                               AcRxClass*    classobj);


    //*************************************************************************
    // Overridden methods from AcDbObject
    //*************************************************************************

    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;

    virtual void              saveAs(AcGiWorldDraw* mode,
                                     AcDb::SaveType st);

    virtual Acad::ErrorStatus getClassID(CLSID* pClsid) const;
};


inline Adesk::Boolean AcDbPolyline::isPlanar() const
{
    return Adesk::kTrue;
}

inline Acad::ErrorStatus AcDbPolyline::getStartParam(double& startParam) const
{
    startParam = 0.;
    return Acad::eOk;
}

inline Acad::ErrorStatus AcDbPolyline::getSpline(AcDbSpline*& spline) const
{
    return Acad::eNotApplicable;
}

#pragma pack(pop)

#endif /*AD_DBPL_H*/
