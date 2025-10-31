#ifndef AMODELER_INC_LINE3D_H
#define AMODELER_INC_LINE3D_H


///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 1996 by Autodesk, Inc.
//
// The information contained herein is confidential, proprietary
// to Autodesk,  Inc.,  and considered a trade secret as defined
// in section 499C of the penal code of the State of California.
// Use of  this information  by  anyone  other  than  authorized
// employees of Autodesk, Inc.  is granted  only under a written
// non-disclosure agreement,  expressly  prescribing  the  scope
// and manner of such use.
//
// CREATED BY:  Jiri Kripac                     January-1-1996
//
// DESCRIPTION:
//
// Declaration of class Line3d keeping a definition of an oriented line and/or 
// an axis. The Line3d class keeps a Point3d and a Vector3d. For the Line3d 
// object to be valid, the vector must not be null.
//
// The parameters of the Line3d class are accessed via public data members
// 'point' and 'vector'.
//
///////////////////////////////////////////////////////////////////////////////

#include "point3d.h"

AMODELER_NAMESPACE_BEGIN


class DllImpExp Line3d
{
public:
    Line3d()                                     : point (Point3d::kNull), 
                                                   vector(Vector3d::kNull)  {}
    Line3d(const Point3d&  p, const Vector3d& v) : point( p), vector(v)     {}
    Line3d(const Point3d& p1, const Point3d& p2) : point(p1), vector(p2-p1) {}

    double  dist   (const Point3d&) const;
    Point3d project(const Point3d&) const;

    void operator *=(const Transf3d&);

    bool isValid() const                          { return !vector.isNull(); }

    // Public data members
    //
    Point3d  point;
    Vector3d vector;

    static const Line3d kNull;
    static const Line3d kXAxis;
    static const Line3d kYAxis;
    static const Line3d kZAxis;

};  // class Line3d


AMODELER_NAMESPACE_END
#endif

