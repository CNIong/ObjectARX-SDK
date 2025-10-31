#ifndef AC_GEARC2D_H
#define AC_GEARC2D_H
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
// This file contains the class AcGeCircArc2d - A mathematical entity
// used to represent a circular arc in 2-space.

#include "gecurv2d.h"
#include "gepnt2d.h"
#include "gevec2d.h"
#pragma pack (push, 8)

class AcGeLine2d;
class AcGeLinearEnt2d;

class
GE_DLLEXPIMPORT
AcGeCircArc2d : public AcGeCurve2d
{
public:
    AcGeCircArc2d();
    AcGeCircArc2d(const AcGeCircArc2d& arc);
    AcGeCircArc2d(const AcGePoint2d& cent, double radius);
    AcGeCircArc2d(const AcGePoint2d& cent, double radius,
                  double startAngle, double endAngle,
                  const AcGeVector2d& refVec = AcGeVector2d::kXAxis,
                  Adesk::Boolean isClockWise = Adesk::kFalse);
    AcGeCircArc2d(const AcGePoint2d& startPoint, const AcGePoint2d& point, 
                  const AcGePoint2d& endPoint);

	// If bulgeFlag is kTrue, then bulge is interpreted to be the maximum
	// distance between the arc and the chord between the two input points.
	// If bulgeFlag is kFalse, then bulge is interpreted to be tan(ang/4),
	// where ang is the angle of the arc segment between the two input points.
    AcGeCircArc2d(const AcGePoint2d& startPoint, const AcGePoint2d& endPoint, double bulge, 
                  Adesk::Boolean bulgeFlag = Adesk::kTrue);


    // Intersection with other geometric objects.
    //
    Adesk::Boolean intersectWith  (const AcGeLinearEnt2d& line, int& intn,
                                   AcGePoint2d& p1, AcGePoint2d& p2,
                                   const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean intersectWith  (const AcGeCircArc2d& arc, int& intn,
                                   AcGePoint2d& p1, AcGePoint2d& p2,
                                   const AcGeTol& tol = AcGeContext::gTol) const;

    // Tangent line to the circular arc at given point.
    //
    Adesk::Boolean tangent        (const AcGePoint2d& pnt, AcGeLine2d& line,
                                   const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean tangent        (const AcGePoint2d& pnt, AcGeLine2d& line,
                                   const AcGeTol& tol, AcGeError& error) const;
		 // Possible error conditions:  kArg1TooBig, kArg1InsideThis, 
		 // kArg1OnThis
     

    // Test if point is inside circle.
    //
    Adesk::Boolean isInside       (const AcGePoint2d& pnt,
                                   const AcGeTol& tol = AcGeContext::gTol) const;

    // Definition of circular arc
    //
    AcGePoint2d    center         () const;
    double         radius         () const;
    double         startAng       () const;
    double         endAng         () const;
    Adesk::Boolean isClockWise    () const;
    AcGeVector2d   refVec         () const;
    AcGePoint2d    startPoint     () const;
    AcGePoint2d    endPoint       () const;

    AcGeCircArc2d& setCenter      (const AcGePoint2d& cent);
    AcGeCircArc2d& setRadius      (double radius);
    AcGeCircArc2d& setAngles      (double startAng, double endAng);
    AcGeCircArc2d& setToComplement();
    AcGeCircArc2d& setRefVec      (const AcGeVector2d& vec);
    AcGeCircArc2d& set            (const AcGePoint2d& cent, double radius);
    AcGeCircArc2d& set            (const AcGePoint2d& cent, double radius,
                                   double ang1, double ang2,
                                   const AcGeVector2d& refVec =
                                   AcGeVector2d::kXAxis,
                                   Adesk::Boolean isClockWise = Adesk::kFalse);
    AcGeCircArc2d& set            (const AcGePoint2d& startPoint, const AcGePoint2d& pnt,
                                   const AcGePoint2d& endPoint);
    AcGeCircArc2d& set            (const AcGePoint2d& startPoint, const AcGePoint2d& pnt,
                                   const AcGePoint2d& endPoint, AcGeError& error);
		 // Possible errors:  kEqualArg1Arg2, kEqualArg1Arg3, kEqualArg2Arg3, 
		 // kLinearlyDependentArg1Arg2Arg3.
		 // Degenerate results: none.
		 // On error, the object is unchanged.

	// If bulgeFlag is kTrue, then bulge is interpreted to be the maximum
	// distance between the arc and the chord between the two input points.
	// If bulgeFlag is kFalse, then bulge is interpreted to be tan(ang/4),
	// where ang is the angle of the arc segment between the two input points.
    AcGeCircArc2d& set            (const AcGePoint2d& startPoint, 
                                   const AcGePoint2d& endPoint,
                                   double bulge, Adesk::Boolean bulgeFlag = Adesk::kTrue);
    AcGeCircArc2d& set            (const AcGeCurve2d& curve1,
                                   const AcGeCurve2d& curve2,
                                   double radius, double& param1, double& param2,
								   Adesk::Boolean& success);
		// On success, this arc becomes the fillet of the given radius between the two curves,
	    // whose points of tangency are nearest param1 and param2 respectively.
    AcGeCircArc2d& set            (const AcGeCurve2d& curve1,
                                   const AcGeCurve2d& curve2,
                                   const AcGeCurve2d& curve3,
                                   double& param1, double& param2, double& param3,
								   Adesk::Boolean& success);
    // Assignment operator.
    //
    AcGeCircArc2d& operator =     (const AcGeCircArc2d& arc);
};

#pragma pack (pop)
#endif
