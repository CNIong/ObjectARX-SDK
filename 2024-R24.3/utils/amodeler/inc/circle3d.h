///////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form. 
//
// DESCRIPTION:
//
// The parameters of the Circle3d class are accessed via public data members
// 'axis' and 'radius', axis.point being the center of the circle, axis.vector
// being the normal of the plane the circle lies in.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_CIRCLE3D_H
#define AMODELER_INC_CIRCLE3D_H


#include "line3d.h"

AMODELER_NAMESPACE_BEGIN


class DllImpExp Circle3d
{
public:
    Circle3d() : radius(0) {}
    Circle3d(Line3d ax, double rad) : axis(ax), radius(rad) {}

    Circle3d(const Point3d&  p1,
             const Point3d&  p2,
             const Vector3d& norm, 
             double          rad,
             bool            isCenterLeft);

    Circle3d(const Point3d& p1,
             const Point3d& p2,
             const Point3d& p3,
             double         rad); 
    
    void operator *=(const Transf3d&);

    Vector3d tangentAt(const Point3d& pointOnCircle) const;

    bool isValid() const { return radius != 0 && axis.isValid(); }

    bool isEqual(const Circle3d&) const;

    int tessellate(int            approx,
                   bool           goCcw,
                   const Point3d  startPoint, 
                   const Point3d  endPoint, 
                   Point3d*       ptsArray); // The length of ptsArray must be >= approx+2

    // Public data members
    //
    Line3d axis;
    double radius;

};  // class Circle3d


AMODELER_NAMESPACE_END
#endif

