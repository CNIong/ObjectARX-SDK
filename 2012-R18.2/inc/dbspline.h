//
// (C) Copyright 1993-2011 by Autodesk, Inc.
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
// DESCRIPTION: Exported class for Spline - AcDbSpline.

#ifndef ACDB_DBSPLINE_H
#define ACDB_DBSPLINE_H

#include "gegbl.h"
#include "dbmain.h"
#include "dbcurve.h"

#pragma pack (push, 8)

static const unsigned int kPlineVerticesThrehold = 10000;

class AcDb2dPolyline;

enum SplineType {kFitPoints = 0, kControlPoints = 1};

class AcDbSpline: public AcDbCurve
{
public:
    ACDB_DECLARE_MEMBERS(AcDbSpline);
    AcDbSpline();
    virtual ~AcDbSpline();

    // the following four constructors take in fit points.
    // Order = degree + 1.
    AcDbSpline(const AcGePoint3dArray& fitPoints,
               int                     order = 4, 
               double                  fitTolerance = 0.0);

    AcDbSpline(const AcGePoint3dArray& fitPoints,
               const AcGeVector3d&     startTangent,
               const AcGeVector3d&     endTangent,
               int                     order = 4, 
               double                  fitTolerance = 0.0);

    ACDB_PORT
    AcDbSpline(const AcGePoint3dArray& fitPoints,
               bool                    periodic, 
               AcGe::KnotParameterization  knotParam = AcGe::kUniform,
               int                     degree = 3, 
               double                  fitTolerance = 0.0);

    ACDB_PORT
    AcDbSpline(const AcGePoint3dArray& fitPoints,
               AcGe::KnotParameterization    knotParam,
               int                     degree = 3, 
               double                  fitTolerance = 0.0);

    ACDB_PORT
    AcDbSpline(const AcGePoint3dArray& fitPoints,
               const AcGeVector3d&     startTangent,
               const AcGeVector3d&     endTangent,
               AcGe::KnotParameterization    knotParam, 
               int                     degree = 3, 
               double                  fitTolerance = 0.0);

    // the constructor takes in control points.
    AcDbSpline(int                     degree, 
               Adesk::Boolean          rational, 
               Adesk::Boolean          closed, 
               Adesk::Boolean          periodic,
               const AcGePoint3dArray& controlPoints, 
               const AcGeDoubleArray&  knots, 
               const AcGeDoubleArray&  weights,
               double                  controlPtTol = 0.0, 
               double                  knotTol = 0.0);

    AcDbSpline(const AcGePoint3d&      center,
               const AcGeVector3d&     unitNormal,
               const AcGeVector3d&     majorAxis,
               double                  radiusRatio,
               double                  startAngle = 0.0,
               double                  endAngle = 6.28318530717958647692);

    // methods
    //
    Adesk::Boolean    isNull() const;

    Adesk::Boolean    isRational() const;

    int               degree() const;
    Acad::ErrorStatus elevateDegree(int newDegree);

    int               numControlPoints() const;
    Acad::ErrorStatus getControlPointAt(int index, AcGePoint3d& point) const;
    Acad::ErrorStatus setControlPointAt(int index, const AcGePoint3d& point);

    int               numFitPoints() const;
    Acad::ErrorStatus getFitPointAt(int index, AcGePoint3d& point) const;
    Acad::ErrorStatus setFitPointAt(int index, const AcGePoint3d& point);

    Acad::ErrorStatus insertFitPointAt(int index, const AcGePoint3d& point);
    Acad::ErrorStatus removeFitPointAt(int index);

    double            fitTolerance() const;
    Acad::ErrorStatus setFitTol(double tol);

    Acad::ErrorStatus getFitTangents(AcGeVector3d& startTangent, 
                                     AcGeVector3d& endTangent) const;
    Acad::ErrorStatus setFitTangents(const AcGeVector3d& startTangent, 
                                     const AcGeVector3d& endTangent);

    Adesk::Boolean    hasFitData() const;

    Acad::ErrorStatus getFitData(AcGePoint3dArray&  fitPoints, 
                                 int&               degree, 
                                 double&            fitTolerance, 
                                 Adesk::Boolean&    tangentsExist,
                                 AcGeVector3d&      startTangent, 
                                 AcGeVector3d&      endTangent) const;

    Acad::ErrorStatus setFitData(const AcGePoint3dArray&  fitPoints, 
                                 int                   degree, 
                                 double                fitTolerance,
                                 const AcGeVector3d&   startTangent, 
                                 const AcGeVector3d&   endTangent);

    ACDB_PORT 
    Acad::ErrorStatus getFitData(AcGePoint3dArray&  fitPoints, 
                                 Adesk::Boolean&    tangentsExist,
                                 AcGeVector3d&      startTangent,
                                 AcGeVector3d&      endTangent,
                                 AcGe::KnotParameterization&  knotParam,
                                 int&               degree, 
                                 double&            fitTolerance) const;

    ACDB_PORT
    Acad::ErrorStatus setFitData(const AcGePoint3dArray&  fitPoints, 
                                 const AcGeVector3d&   startTangent, 
                                 const AcGeVector3d&   endTangent,
                                 AcGe::KnotParameterization  knotParam,
                                 int                   degree = 3, 
                                 double                fitTolerance = 0.0); 

    ACDB_PORT
    Acad::ErrorStatus setFitData(const AcGePoint3dArray&  fitPoints, 
                                 bool                     isPeriodic,
                                 AcGe::KnotParameterization  knotParam,
                                 int                   degree = 3, 
                                 double                fitTolerance = 0.0); 

    Acad::ErrorStatus purgeFitData();
    Acad::ErrorStatus updateFitData();

    Acad::ErrorStatus getNurbsData(int&              degree, 
                                   Adesk::Boolean&   rational, 
                                   Adesk::Boolean&   closed, 
                                   Adesk::Boolean&   periodic,
                                   AcGePoint3dArray& controlPoints, 
                                   AcGeDoubleArray&  knots, 
                                   AcGeDoubleArray&  weights,
                                   double&           controlPtTol,
                                   double&           knotTol) const;

    Acad::ErrorStatus setNurbsData(int                  degree, 
                                   Adesk::Boolean       rational, 
                                   Adesk::Boolean       closed, 
                                   Adesk::Boolean       periodic,
                                   const AcGePoint3dArray& controlPoints, 
                                   const AcGeDoubleArray& knots, 
                                   const AcGeDoubleArray& weights,
                                   double               controlPtTol,
                                   double               knotTol);

    double            weightAt(int index) const;
    Acad::ErrorStatus setWeightAt(int index, double weight);

    Acad::ErrorStatus insertKnot(double param);

    DBCURVE_METHODS

    Acad::ErrorStatus getOffsetCurvesGivenPlaneNormal(
                        const AcGeVector3d& normal, double offsetDist,
                        AcDbVoidPtrArray& offsetCurves) const;

    Acad::ErrorStatus toPolyline(AcDbCurve*& pCurve, int precision = 10,
                             int* maxSuggestedPrecision = NULL,
           unsigned int numOfVerticesThreshold = kPlineVerticesThrehold) const;

    // The following two methods are adding/removing control points on the spline.
    
    // 1. add a control point to the spline at the given knot parameter.
    ACDB_PORT Acad::ErrorStatus insertControlPointAt(double knotParam, const AcGePoint3d& ctrlPt, double weight = 1.0);

    // 2. remove a control point at the given index.
    ACDB_PORT Acad::ErrorStatus removeControlPointAt(int index);

    // get/set the spline Method (either by fit points or by control points)
    ACDB_PORT SplineType        type() const;
    ACDB_PORT Acad::ErrorStatus setType(SplineType type);

    // rebuild
    ACDB_PORT Acad::ErrorStatus rebuild(int degree, int numCtrlPts);

    // edit
    ACDB_PORT Acad::ErrorStatus modifyPositionAndTangent(double param, const AcGePoint3d& point, const AcGeVector3d* deriv);

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const;
};

#pragma pack (pop)

#endif