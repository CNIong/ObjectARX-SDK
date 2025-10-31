#ifndef AC_GENURB2d_H
#define AC_GENURB2d_H
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
// This file contains the class AcGeNurbCurve2d - A mathematical entity
// used to represent a different types of spline curves in 2-space.

#include "gecurv2d.h"
#include "geintrvl.h"
#include "gekvec.h"
#include "gept2dar.h"
#include "gevec2d.h"
#include "gepnt2d.h"
#include "gesent2d.h"
#include "geplin2d.h"
#include "gedblar.h"
#include "gept2dar.h"
#include "gevc2dar.h"
#pragma pack (push, 8)

class AcGeEllipArc2d;
class AcGeLineSeg2d;

class 
GE_DLLEXPIMPORT
AcGeNurbCurve2d : public AcGeSplineEnt2d
{
public:
    // Construct spline from control points.
	//
    AcGeNurbCurve2d ();
    AcGeNurbCurve2d (const AcGeNurbCurve2d& src );
    AcGeNurbCurve2d (int degree, const AcGeKnotVector& knots,
                     const AcGePoint2dArray& cntrlPnts, 
                     Adesk::Boolean isPeriodic = Adesk::kFalse );
    AcGeNurbCurve2d (int degree, const AcGeKnotVector& knots,
                     const AcGePoint2dArray& cntrlPnts, 
                     const AcGeDoubleArray&  weights,
                     Adesk::Boolean isPeriodic = Adesk::kFalse );

    // Construct spline from interpolation data.
    //
    AcGeNurbCurve2d (int degree, const AcGePolyline2d& fitPolyline,
                     Adesk::Boolean isPeriodic = Adesk::kFalse );
    AcGeNurbCurve2d (const AcGePoint2dArray& fitPoints, 
				     const AcGeVector2d& startTangent, 
				     const AcGeVector2d& endTangent,
				     Adesk::Boolean startTangentDefined = Adesk::kTrue,
					 Adesk::Boolean endTangentDefined   = Adesk::kTrue,
				     const AcGeTol& fitTolerance = AcGeContext::gTol);
    AcGeNurbCurve2d (const AcGePoint2dArray& fitPoints, 
				     const AcGeTol& fitTolerance = AcGeContext::gTol);
    AcGeNurbCurve2d (const AcGePoint2dArray& fitPoints, 
                     const AcGeVector2dArray& fitTangents,
				     const AcGeTol& fitTolerance = AcGeContext::gTol,
				     Adesk::Boolean isPeriodic = Adesk::kFalse);

    // Spline representation of ellipse
	//
	AcGeNurbCurve2d (const AcGeEllipArc2d&  ellipse);

    // Spline representation of line segment
	//
	AcGeNurbCurve2d (const AcGeLineSeg2d& linSeg);

	// Query methods.
	//
    int             numFitPoints      () const;
    Adesk::Boolean  getFitPointAt     (int index, AcGePoint2d& point) const;
    Adesk::Boolean  getFitTolerance   (AcGeTol& fitTolerance) const;
    Adesk::Boolean  getFitTangents    (AcGeVector2d& startTangent, 
				                       AcGeVector2d& endTangent) const;
    Adesk::Boolean  getFitData        (AcGePoint2dArray& fitPoints,
		                               AcGeTol& fitTolerance,
				                       Adesk::Boolean& tangentsExist,
				                       AcGeVector2d& startTangent, 
				                       AcGeVector2d& endTangent) const;
    void            getDefinitionData (int& degree, Adesk::Boolean& rational,
								       Adesk::Boolean& periodic,
			                           AcGeKnotVector& knots,
			                           AcGePoint2dArray& controlPoints,
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
    Adesk::Boolean   setFitPointAt    (int index, const AcGePoint2d& point);
    Adesk::Boolean   addFitPointAt    (int index, const AcGePoint2d& point);
    Adesk::Boolean   deleteFitPointAt (int index);
    Adesk::Boolean   setFitTolerance  (const AcGeTol& fitTol=AcGeContext::gTol);
    Adesk::Boolean   setFitTangents   (const AcGeVector2d& startTangent, 
	                        	       const AcGeVector2d& endTangent);
    AcGeNurbCurve2d& setFitData       (const AcGePoint2dArray& fitPoints,                                             
				                       const AcGeVector2d& startTangent, 
				                       const AcGeVector2d& endTangent,
				                       const AcGeTol& fitTol=AcGeContext::gTol);
    AcGeNurbCurve2d& setFitData       (const AcGeKnotVector& fitKnots,
		                               const AcGePoint2dArray& fitPoints,
				                       const AcGeVector2d& startTangent, 
				                       const AcGeVector2d& endTangent,										 
                        			   const AcGeTol& fitTol=AcGeContext::gTol,
				                       Adesk::Boolean isPeriodic=Adesk::kFalse);
    AcGeNurbCurve2d&  setFitData      (int degree, 
                                       const AcGePoint2dArray& fitPoints,
				                       const AcGeTol& fitTol=AcGeContext::gTol);
    Adesk::Boolean    purgeFitData    ();
    AcGeNurbCurve2d&  addKnot         (double newKnot);
    AcGeNurbCurve2d&  insertKnot      (double newKnot);
    AcGeSplineEnt2d&  setWeightAt     (int idx, double val);
    AcGeNurbCurve2d&  setEvalMode     (Adesk::Boolean evalMode=Adesk::kFalse );
	AcGeNurbCurve2d&  joinWith        (const AcGeNurbCurve2d& curve);
	AcGeNurbCurve2d&  hardTrimByParams(double newStartParam, 
		                               double newEndParam);
    AcGeNurbCurve2d&  makeRational    (double weight = 1.0);
    AcGeNurbCurve2d&  makeClosed      ();
    AcGeNurbCurve2d&  makePeriodic    ();
    AcGeNurbCurve2d&  makeNonPeriodic ();
    AcGeNurbCurve2d&  makeOpen        ();
    AcGeNurbCurve2d&  elevateDegree   (int plusDegree);

    // Assignment operator.
    //
    AcGeNurbCurve2d&  operator =      (const AcGeNurbCurve2d& spline);
};

#pragma pack (pop)
#endif
