///////////////////////////////////////////////////////////////////////////////
//
// © Autodesk, Inc. 1998-2010. All rights reserved.
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

