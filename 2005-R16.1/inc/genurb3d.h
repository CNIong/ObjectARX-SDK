#ifndef AC_GENURB3D_H
#define AC_GENURB3D_H
//
// (C) Copyright 1993-1999 by Autodesk, Inc.
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
// DESCRIPTION:
//
// This file contains the class AcGeNurbCurve3d - A mathematical entity
// used to represent a different types of spline curves in 3-space.

#include "gecurv3d.h"
#include "geintrvl.h"
#include "gekvec.h"
#include "gept3dar.h"
#include "gevec3d.h"
#include "gepnt3d.h"
#include "gesent3d.h"
#include "geplin3d.h"
#include "gedblar.h"
#include "gept3dar.h"
#include "gevc3dar.h"
#pragma pack (push, 8)

class AcGeEllipArc3d;
class AcGeLineSeg3d;

class 
GE_DLLEXPIMPORT
AcGeNurbCurve3d : public AcGeSplineEnt3d
{
public:
    // Construct spline from control points.
	//
    AcGeNurbCurve3d ();
    AcGeNurbCurve3d (const AcGeNurbCurve3d& src );
    AcGeNurbCurve3d (int degree, const AcGeKnotVector& knots,
                     const AcGePoint3dArray& cntrlPnts, 
                     Adesk::Boolean isPeriodic = Adesk::kFalse );
    AcGeNurbCurve3d (int degree, const AcGeKnotVector& knots,
                     const AcGePoint3dArray& cntrlPnts, 
                     const AcGeDoubleArray&  weights,
                     Adesk::Boolean isPeriodic = Adesk::kFalse );

    // Construct spline from interpolation data.
    //
    AcGeNurbCurve3d (int degree, const AcGePolyline3d& fitPolyline,
                     Adesk::Boolean isPeriodic = Adesk::kFalse );
    AcGeNurbCurve3d (const AcGePoint3dArray& fitPoints, 
				     const AcGeVector3d& startTangent, 
				     const AcGeVector3d& endTangent,
				     Adesk::Boolean startTangentDefined = Adesk::kTrue,
					 Adesk::Boolean endTangentDefined   = Adesk::kTrue,
				     const AcGeTol& fitTolerance = AcGeContext::gTol);
    AcGeNurbCurve3d (const AcGePoint3dArray& fitPoints, 
				     const AcGeTol& fitTolerance = AcGeContext::gTol);
    AcGeNurbCurve3d (const AcGePoint3dArray& fitPoints, 
                     const AcGeVector3dArray& fitTangents,
				     const AcGeTol& fitTolerance = AcGeContext::gTol,
				     Adesk::Boolean isPeriodic = Adesk::kFalse);

    // Spline representation of ellipse
	//
	AcGeNurbCurve3d (const AcGeEllipArc3d&  ellipse);

    // Spline representation of line segment
	//
	AcGeNurbCurve3d (const AcGeLineSeg3d& linSeg);

	// Query methods.
	//
    int             numFitPoints      () const;
    Adesk::Boolean  getFitPointAt     (int index, AcGePoint3d& point) const;
    Adesk::Boolean  getFitTolerance   (AcGeTol& fitTolerance) const;
    Adesk::Boolean  getFitTangents    (AcGeVector3d& startTangent, 
				                       AcGeVector3d& endTangent) const;
    Adesk::Boolean  getFitTangents    (AcGeVector3d& startTangent, 
                                       AcGeVector3d& endTangent,
                                       Adesk::Boolean& startTangentDefined,
                                       Adesk::Boolean& endTangentDefined) const;
    Adesk::Boolean  getFitData        (AcGePoint3dArray& fitPoints,
		                               AcGeTol& fitTolerance,
				                       Adesk::Boolean& tangentsExist,
				                       AcGeVector3d& startTangent, 
				                       AcGeVector3d& endTangent) const;
    void            getDefinitionData (int& degree, Adesk::Boolean& rational,
								       Adesk::Boolean& periodic,
			                           AcGeKnotVector& knots,
			                           AcGePoint3dArray& controlPoints,
			                           AcGeDoubleArray& weights) const;
    int             numWeights        () const;
    double          weightAt          (int idx) const;
    Adesk::Boolean  evalMode          () const;        
	Adesk::Boolean  getParamsOfC1Discontinuity (AcGeDoubleArray& params,
				                                const AcGeTol& tol 
					                            = AcGeContext::gTol) const;
	Adesk::Boolean	getParamsOfG1Discontinuity (AcGeDoubleArray& params,
					                            const AcGeTol& tol 
					                            = AcGeContext::gTol) const;

	// Modification methods.
	//
    Adesk::Boolean   setFitPointAt    (int index, const AcGePoint3d& point);
    Adesk::Boolean   addFitPointAt    (int index, const AcGePoint3d& point);
    Adesk::Boolean   deleteFitPointAt (int index);
    Adesk::Boolean   setFitTolerance  (const AcGeTol& fitTol=AcGeContext::gTol);
    Adesk::Boolean   setFitTangents   (const AcGeVector3d& startTangent, 
	                        	       const AcGeVector3d& endTangent);
    Adesk::Boolean   setFitTangents   (const AcGeVector3d& startTangent, 
                                       const AcGeVector3d& endTangent,
                                       Adesk::Boolean startTangentDefined,
                                       Adesk::Boolean endTangentDefined) const;
    AcGeNurbCurve3d& setFitData       (const AcGePoint3dArray& fitPoints,                                             
				                       const AcGeVector3d& startTangent, 
				                       const AcGeVector3d& endTangent,
				                       const AcGeTol& fitTol=AcGeContext::gTol);
    AcGeNurbCurve3d& setFitData       (const AcGeKnotVector& fitKnots,
		                               const AcGePoint3dArray& fitPoints,
				                       const AcGeVector3d& startTangent, 
				                       const AcGeVector3d& endTangent,										 
                        			   const AcGeTol& fitTol=AcGeContext::gTol,
				                       Adesk::Boolean isPeriodic=Adesk::kFalse);
    AcGeNurbCurve3d&  setFitData      (int degree, 
                                       const AcGePoint3dArray& fitPoints,
				                       const AcGeTol& fitTol=AcGeContext::gTol);
    Adesk::Boolean    purgeFitData    ();
    AcGeNurbCurve3d&  addKnot         (double newKnot);
    AcGeNurbCurve3d&  insertKnot      (double newKnot);
    AcGeSplineEnt3d&  setWeightAt     (int idx, double val);
    AcGeNurbCurve3d&  setEvalMode     (Adesk::Boolean evalMode=Adesk::kFalse );
	AcGeNurbCurve3d&  joinWith        (const AcGeNurbCurve3d& curve);
	AcGeNurbCurve3d&  hardTrimByParams(double newStartParam, 
		                               double newEndParam);
    AcGeNurbCurve3d&  makeRational    (double weight = 1.0);
    AcGeNurbCurve3d&  makeClosed      ();
    AcGeNurbCurve3d&  makePeriodic    ();
    AcGeNurbCurve3d&  makeNonPeriodic ();
    AcGeNurbCurve3d&  makeOpen        ();
    AcGeNurbCurve3d&  elevateDegree   (int plusDegree);

    // Assignment operator.
    //
    AcGeNurbCurve3d&  operator =      (const AcGeNurbCurve3d& spline);
};

#pragma pack (pop)
#endif
