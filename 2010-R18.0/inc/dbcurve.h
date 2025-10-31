#ifndef AD_DBCURVE_H
#define AD_DBCURVE_H
//
// (C) Copyright 1993-2009 by Autodesk, Inc.
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
// DESCRIPTION: API Abstract class for "Curve" entities.

#include "dbmain.h"
#include "gept3dar.h"
#include "gedblar.h"
#include "geplane.h"
#include "dbptrar.h"

class AcDbSpline;

#pragma pack(push, 8)

class ADESK_NO_VTABLE AcDbCurve: public AcDbEntity
{
public:
    ACDB_DECLARE_MEMBERS(AcDbCurve);

    virtual ~AcDbCurve();

    // Curve property tests.
    //
    virtual Adesk::Boolean    isClosed     () const;      
    virtual Adesk::Boolean    isPeriodic   () const;      

    // Get planar and start/end geometric properties.
    //
    virtual Acad::ErrorStatus getStartParam(double&) const;
    virtual Acad::ErrorStatus getEndParam  (double&) const;
    virtual Acad::ErrorStatus getStartPoint(AcGePoint3d&) const;
    virtual Acad::ErrorStatus getEndPoint  (AcGePoint3d&) const;

    // Conversions to/from parametric/world/distance.
    //
    virtual Acad::ErrorStatus getPointAtParam(double, AcGePoint3d&) const;
    virtual Acad::ErrorStatus getParamAtPoint(const AcGePoint3d&, double&)const;
    virtual Acad::ErrorStatus getDistAtParam (double param, double& dist) const;
    virtual Acad::ErrorStatus getParamAtDist (double dist, double& param) const;
    virtual Acad::ErrorStatus getDistAtPoint (const AcGePoint3d&, double&)const;
    virtual Acad::ErrorStatus getPointAtDist (double, AcGePoint3d&) const;

    // Derivative information.
    //
    virtual Acad::ErrorStatus getFirstDeriv  (double param,
                                              AcGeVector3d& firstDeriv) const;
    virtual Acad::ErrorStatus getFirstDeriv  (const AcGePoint3d&,
                                              AcGeVector3d& firstDeriv) const;
    virtual Acad::ErrorStatus getSecondDeriv (double param,
                                              AcGeVector3d& secDeriv) const;
    virtual Acad::ErrorStatus getSecondDeriv (const AcGePoint3d&,
                                              AcGeVector3d& secDeriv) const;

    // Closest point on curve.
    //
    virtual Acad::ErrorStatus getClosestPointTo(const AcGePoint3d& givenPnt,
                                                AcGePoint3d& pointOnCurve,
                                                Adesk::Boolean extend
                                                = Adesk::kFalse) const;
    virtual Acad::ErrorStatus getClosestPointTo(const AcGePoint3d& givenPnt,
                                                const AcGeVector3d& direction,
                                                AcGePoint3d& pointOnCurve,
                                                Adesk::Boolean extend
                                                = Adesk::kFalse) const;

    // Get a projected copy of the curve.
    //
    virtual Acad::ErrorStatus getOrthoProjectedCurve(const AcGePlane&,
                                                AcDbCurve*& projCrv) const;
    virtual Acad::ErrorStatus getProjectedCurve(const AcGePlane&,
                                                const AcGeVector3d& projDir,
                                                AcDbCurve*& projCrv) const;

    // Get offset, spline and split copies of the curve.
    //
    virtual Acad::ErrorStatus getOffsetCurves(double offsetDist,
                                          AcDbVoidPtrArray& offsetCurves) const;
    virtual Acad::ErrorStatus getOffsetCurvesGivenPlaneNormal(
        const AcGeVector3d& normal, double offsetDist,
        AcDbVoidPtrArray& offsetCurves) const;
    virtual Acad::ErrorStatus getSpline      (AcDbSpline*& spline) const;
    virtual Acad::ErrorStatus getSplitCurves (const AcGeDoubleArray& params,
                                         AcDbVoidPtrArray& curveSegments) const;
    virtual Acad::ErrorStatus getSplitCurves (const AcGePoint3dArray& points,
                                         AcDbVoidPtrArray& curveSegments) const;

    // Extend the curve.
    //
    virtual Acad::ErrorStatus extend(double newParam);
    virtual Acad::ErrorStatus extend(Adesk::Boolean extendStart,
                                     const AcGePoint3d& toPoint);

    // Area calculation.
    //
    virtual Acad::ErrorStatus getArea(double&) const;

    // Reverse the curve.
    //
    virtual Acad::ErrorStatus reverseCurve();

protected:
    AcDbCurve();
};

// Protocols of AcDbCurve available in macro from.

#define DBCURVE_METHODS \
virtual Adesk::Boolean isClosed() const; \
virtual Adesk::Boolean isPeriodic() const; \
virtual Adesk::Boolean isPlanar() const; \
virtual Acad::ErrorStatus getPlane(AcGePlane&, AcDb::Planarity&) const; \
virtual Acad::ErrorStatus getStartParam(double&) const; \
virtual Acad::ErrorStatus getEndParam(double&) const; \
virtual Acad::ErrorStatus getStartPoint(AcGePoint3d&) const; \
virtual Acad::ErrorStatus getEndPoint(AcGePoint3d&) const; \
virtual Acad::ErrorStatus getPointAtParam(double, AcGePoint3d&) const; \
virtual Acad::ErrorStatus getParamAtPoint(const AcGePoint3d&, double&) const; \
virtual Acad::ErrorStatus getDistAtParam(double, double&) const; \
virtual Acad::ErrorStatus getParamAtDist(double, double&) const; \
virtual Acad::ErrorStatus getDistAtPoint(const AcGePoint3d&, double&) const; \
virtual Acad::ErrorStatus getPointAtDist(double, AcGePoint3d&) const; \
virtual Acad::ErrorStatus getFirstDeriv(double, AcGeVector3d&) const; \
virtual Acad::ErrorStatus getFirstDeriv(const AcGePoint3d&,AcGeVector3d&)const;\
virtual Acad::ErrorStatus getSecondDeriv(double, AcGeVector3d&) const; \
virtual Acad::ErrorStatus getSecondDeriv(const AcGePoint3d&, \
                              AcGeVector3d&) const; \
virtual Acad::ErrorStatus getClosestPointTo(const AcGePoint3d&, AcGePoint3d&, \
                              Adesk::Boolean = Adesk::kFalse) const; \
virtual Acad::ErrorStatus getClosestPointTo(const AcGePoint3d&, \
                              const AcGeVector3d&, AcGePoint3d&, \
                              Adesk::Boolean = Adesk::kFalse) const; \
virtual Acad::ErrorStatus getOrthoProjectedCurve(const AcGePlane&, \
                              AcDbCurve*&) const; \
virtual Acad::ErrorStatus getProjectedCurve(const AcGePlane&, \
                              const AcGeVector3d&, AcDbCurve*&) const; \
virtual Acad::ErrorStatus getOffsetCurves(double, AcDbVoidPtrArray&) const; \
virtual Acad::ErrorStatus getSpline(AcDbSpline*&) const; \
virtual Acad::ErrorStatus getSplitCurves(const AcGeDoubleArray&, \
                              AcDbVoidPtrArray& curveSegments) const; \
virtual Acad::ErrorStatus getSplitCurves(const AcGePoint3dArray&, \
                              AcDbVoidPtrArray&) const; \
virtual Acad::ErrorStatus extend(double); \
virtual Acad::ErrorStatus extend(Adesk::Boolean, const AcGePoint3d&); \
virtual Acad::ErrorStatus getArea(double&) const; \
virtual Acad::ErrorStatus reverseCurve();

#pragma pack(pop)

#endif
