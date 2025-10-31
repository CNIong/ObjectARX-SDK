#ifndef AC_GEELL3D_H
#define AC_GEELL3D_H
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
// This file contains the class AcGeEllipArc3d - A mathematical entity
// used to represent an ellipse arc in 3-space.

#include "gecurv3d.h"
#include "gevec3d.h"
#include "gepnt3d.h"
#include "geintrvl.h"
#include "geponc3d.h"
#include "geplane.h"
#pragma pack (push, 8)

class AcGeEllipArc2d;
class AcGeCircArc3d;
class AcGeLineEnt3d;
class AcGePlanarEnt;


class
GE_DLLEXPIMPORT
AcGeEllipArc3d : public AcGeCurve3d
{
public:

    AcGeEllipArc3d();
    AcGeEllipArc3d(const AcGeEllipArc3d& ell);
    AcGeEllipArc3d(const AcGeCircArc3d& arc);
    AcGeEllipArc3d(const AcGePoint3d& cent, const AcGeVector3d& majorAxis,
                   const AcGeVector3d& minorAxis, double majorRadius,
                   double minorRadius);
    AcGeEllipArc3d(const AcGePoint3d& cent, const AcGeVector3d& majorAxis,
                   const AcGeVector3d& minorAxis, double majorRadius,
                   double minorRadius, double ang1, double ang2);
                                         
    // Return the point on this object that is closest to the other object.
    //
    AcGePoint3d    closestPointToPlane(const AcGePlanarEnt& plane,
                                  AcGePoint3d& pointOnPlane,
                                  const AcGeTol& = AcGeContext::gTol) const;

    // Intersection with other geometric objects.
    // 
    Adesk::Boolean intersectWith (const AcGeLinearEnt3d& line, int& intn,
                                  AcGePoint3d& p1, AcGePoint3d& p2,
                                  const AcGeTol& tol = AcGeContext::gTol) const;  
    Adesk::Boolean intersectWith (const AcGePlanarEnt& plane, int& numOfIntersect,
                                  AcGePoint3d& p1, AcGePoint3d& p2,
                                  const AcGeTol& tol = AcGeContext::gTol) const;
 
    // Projection-intersection with other geometric objects.
    //
    Adesk::Boolean projIntersectWith(const AcGeLinearEnt3d& line,
                                  const AcGeVector3d& projDir, int &numInt,
                                  AcGePoint3d& pntOnEllipse1,
                                  AcGePoint3d& pntOnEllipse2,
                                  AcGePoint3d& pntOnLine1,
                                  AcGePoint3d& pntOnLine2,
                                  const AcGeTol& tol = AcGeContext::gTol) const;
    // Plane of the ellipse
    //
    void           getPlane      (AcGePlane& plane) const;

    // Inquiry Methods
    //
    Adesk::Boolean isCircular    (const AcGeTol& tol = AcGeContext::gTol) const;

    // Test if point is inside full ellipse
    //
    Adesk::Boolean isInside      (const AcGePoint3d& pnt,
                                  const AcGeTol& tol = AcGeContext::gTol) const;

    // Definition of ellipse
    //
    AcGePoint3d    center        () const;
    double         minorRadius   () const;
    double         majorRadius   () const;
    AcGeVector3d   minorAxis     () const;
    AcGeVector3d   majorAxis     () const;
    AcGeVector3d   normal        () const; 
    double         startAng      () const;
    double         endAng        () const;
    AcGePoint3d    startPoint    () const;
    AcGePoint3d    endPoint      () const;

    AcGeEllipArc3d& setCenter     (const AcGePoint3d& cent);
    AcGeEllipArc3d& setMinorRadius(double rad);
    AcGeEllipArc3d& setMajorRadius(double rad);
    AcGeEllipArc3d& setAxes       (const AcGeVector3d& majorAxis, const AcGeVector3d& minorAxis);
    AcGeEllipArc3d& setAngles     (double startAngle, double endAngle);
    AcGeEllipArc3d& set           (const AcGePoint3d& cent,
                                   const AcGeVector3d& majorAxis,
                                   const AcGeVector3d& minorAxis,
                                   double majorRadius, double minorRadius);
    AcGeEllipArc3d& set           (const AcGePoint3d& cent,
                                   const AcGeVector3d& majorAxis,
                                   const AcGeVector3d& minorAxis,
                                   double majorRadius, double minorRadius,
                                   double startAngle, double endAngle);
    AcGeEllipArc3d& set           (const AcGeCircArc3d&);

    // Assignment operator.
    //
    AcGeEllipArc3d& operator =    (const AcGeEllipArc3d& ell);
};

#pragma pack (pop)
#endif
