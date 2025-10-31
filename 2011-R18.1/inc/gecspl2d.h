#ifndef AC_GECSPL2D_H
#define AC_GECSPL2D_H
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
// Description:
//
// This file contains the class AcGeCubicSplineCurve2d - A mathematic
// entity used to represent a 2d interpolation cubic-spline curve.
//
class AcGePointOnCurve2d;
class AcGeCurve2dIntersection;
class AcGeInterval;
class AcGePlane;

#include "gesent2d.h"
#include "gept2dar.h"
#include "gevc2dar.h"
#include "gevec2d.h"
#include "gekvec.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGeCubicSplineCurve2d : public AcGeSplineEnt2d
{
public:

    AcGeCubicSplineCurve2d();
    AcGeCubicSplineCurve2d(const AcGeCubicSplineCurve2d& spline);

    // Construct a periodic cubic spline curve
    // Contract: the first fit point must be equal to the last fit point
    //
    AcGeCubicSplineCurve2d(const AcGePoint2dArray& fitPnts,
			   const AcGeTol& tol = AcGeContext::gTol);

    // Construct a cubic spline curve with clamped end condition
    //
    AcGeCubicSplineCurve2d(const AcGePoint2dArray& fitPnts,
			   const AcGeVector2d& startDeriv,
			   const AcGeVector2d& endDeriv,
                           const AcGeTol& tol = AcGeContext::gTol);

    // Construct a cubic spline approximating the curve
    //
    AcGeCubicSplineCurve2d(const AcGeCurve2d& curve,
                           double epsilon = AcGeContext::gTol.equalPoint());

    // Construct a cubic spline curve with given fit points and 1st derivatives
    //
	AcGeCubicSplineCurve2d(const AcGeKnotVector& knots,
	                       const AcGePoint2dArray& fitPnts,
			       const AcGeVector2dArray& firstDerivs,
	                       Adesk::Boolean isPeriodic = Adesk::kFalse );

    // Definition of spline
    //
    int                     numFitPoints   ()        const;
    AcGePoint2d             fitPointAt     (int idx) const;
    AcGeCubicSplineCurve2d& setFitPointAt  (int idx, const AcGePoint2d& point);
    AcGeVector2d            firstDerivAt   (int idx) const;
    AcGeCubicSplineCurve2d& setFirstDerivAt(int idx, const AcGeVector2d& deriv);

    // Assignment operator.
    //
    AcGeCubicSplineCurve2d&  operator = (const AcGeCubicSplineCurve2d& spline);
};

#pragma pack (pop)
#endif
