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
// Declaration of a class Plane, keeping a definition of an oriented plane in 
// 3D. The plane is defined by its (unit) normal vector and parameter 'd', 
// which is the signed distance of the plane from the origin of the coordinate 
// system.
//
// For all points on the plane holds:
//
//   normal * point + d = 0
//
// The plane parameters are accessed via public data members 'normal' and 'd'.
//
// If the plane is invalid (cannot be constructed), the plane normal is set to 
// a null vector.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_PLANE_H
#define AMODELER_INC_PLANE_H


#include "point3d.h"

AMODELER_NAMESPACE_BEGIN


class DllImpExp Plane
{
public:

    Plane()                                 : normal(Vector3d::kNull), d(0) {}
    Plane(Vector3d nn, double dd)           : normal(nn), d(dd)             {}
    Plane(Point3d, Vector3d); 
    Plane(const Point3d&, const Point3d&,  const Point3d&);
    Plane(const Point3d&, const Vector3d&, const Vector3d&);

    // Create plane from a polygon of vertices (n >=3). All polygon vertices
    // are used to calculate the plane coefficients to make the formula
    // symetrical.
    //
    Plane(const Point3d plg[], int n);

    // The plane normal is given, just calculate the 'd' parameter from all 
    // polygon vertices.
    //
    Plane(const Point3d plg[], int n, const Vector3d& normal);

    // Create a plane from the given set of coplanar points. Returns a null 
    // plane if the points do not define a plane. Unlike the Plane constructor
    // that takes a closed polygon, the set of points here is just any set of
    // points and the method tries to do some kind of a best fit plane from 
    // them
    //
    static Plane fromPoints(const Point3d pts[], int pointCount, bool checkPlanarity);

    Plane    operator -()                const { return Plane(-normal, -d); }
    double   dist      (Point3d p)       const { return p % normal + d; }
    Point3d  project   (const Point3d& ) const;
    Vector3d project   (const Vector3d&) const;
    Line3d   project   (const Line3d&  ) const;

    Line3d   operator* (const Plane&   ) const;
    Point3d  operator* (const Line3d&  ) const;

    bool     isValid   () const { return fabs(normal.length() - 1) < epsNor(); }

    bool     isEqual   (Plane) const;

    void     orthoPlane(int& i1, int& i2)          const;
    void     orthoPlane(int& i1, int& i2, int& i3) const;

    // Public data members
    //    
    Vector3d normal;
    double   d;

}; // class Plane



inline Plane::Plane(Point3d p, Vector3d norm)
  : normal(norm)
{
    normal = normal.normalize();
    d = -p % normal;
}


inline bool Plane::isEqual(Plane pla) const 
{ 
    return normal.isEqual(pla.normal) && fabs(d-pla.d) <= epsAbs(); 
}


AMODELER_NAMESPACE_END
#endif
