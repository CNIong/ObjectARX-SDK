#ifndef AC_GECSPL3D_H
#define AC_GECSPL3D_H
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
// This file contains the class AcGeCubicSplineCurve3d - A mathematic
// entity used to represent a 3d interpolation cubic-spline curve.

class AcGePointOnCurve3d;
class AcGeCurve3dIntersection;
class AcGeInterval;
class AcGePlane;

#include "gesent3d.h"
#include "gept3dar.h"
#include "gevc3dar.h"
#include "gevec3d.h"
#include "gekvec.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGeCubicSplineCurve3d : public AcGeSplineEnt3d
{
public:

    AcGeCubicSplineCurve3d();
    AcGeCubicSplineCurve3d(const AcGeCubicSplineCurve3d& spline);

    // Construct a periodic cubic spline curve
    // Contract: the first fit point must be equal to the last fit point
    //
    AcGeCubicSplineCurve3d(const AcGePoint3dArray& fitPnts,
			   const AcGeTol& tol = AcGeContext::gTol);

    // Construct a cubic spline curve with clamped end condition
    //
    AcGeCubicSplineCurve3d(const AcGePoint3dArray& fitPnts,
			   const AcGeVector3d& startDeriv,
			   const AcGeVector3d& endDeriv,
                           const AcGeTol& tol = AcGeContext::gTol);

    // Construct a cubic spline approximating the curve
    //
    AcGeCubicSplineCurve3d(const AcGeCurve3d& curve,
                           double epsilon = AcGeContext::gTol.equalPoint());

    // Construct a cubic spline curve with given fit points and 1st derivatives
    //
    AcGeCubicSplineCurve3d(const AcGeKnotVector& knots,
	                   const AcGePoint3dArray& fitPnts,
			   const AcGeVector3dArray& firstDerivs,
	                   Adesk::Boolean isPeriodic = Adesk::kFalse);

    // Definition of spline
    //
    int                     numFitPoints   ()        const;
    AcGePoint3d             fitPointAt     (int idx) const;
    AcGeCubicSplineCurve3d& setFitPointAt  (int idx, const AcGePoint3d& point);
    AcGeVector3d            firstDerivAt   (int idx) const;
    AcGeCubicSplineCurve3d& setFirstDerivAt(int idx, const AcGeVector3d& deriv);

    // Assignment operator.
    //
    AcGeCubicSplineCurve3d&  operator = (const AcGeCubicSplineCurve3d& spline);
};

#pragma pack (pop)
#endif
