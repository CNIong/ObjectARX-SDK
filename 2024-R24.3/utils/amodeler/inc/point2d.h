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
// Declaration of class Point3d, keeping a point in 2D space. The coordinates
// of the point are accessed via public data members 'x' and 'y' or via 
// the subscript operator, index 0 being the x-coordinate, index 1 being the 
// y-coordinate.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_POINT2D_H
#define AMODELER_INC_POINT2D_H


#include <math.h>
#include "vector2d.h"

class AcGePoint2d;

AMODELER_NAMESPACE_BEGIN


class DllImpExp Point2d
{
public:

    Point2d() {}  // Note: No default constructor
    Point2d(double xx, double yy) : x(xx), y(yy) {}

    Point2d  operator  +(Point2d  p) const { return Point2d (x+p.x, y+p.y); }
    Point2d  operator  +(Vector2d v) const { return Point2d (x+v.x, y+v.y); }
    Vector2d operator  -(Point2d  p) const { return Vector2d(x-p.x, y-p.y); }
    Point2d  operator  -(Vector2d v) const { return Point2d (x-v.x, y-v.y); }
    Point2d  operator  -()           const { return Point2d(-x, -y);        }

    Point2d  operator  *(double scalar) const { return Point2d(x*scalar, y*scalar); }
    Point2d  operator  /(double scalar) const { return Point2d(x/scalar, y/scalar); }

    double   operator  %(Vector2d v) const { return x*v.x+y*v.y;     }
    
    double   operator [](int index) const  { return (&x)[index];     }
    double&  operator [](int index)        { return (&x)[index];     }

    double   length     ()          const  { return sqrt(x*x+y*y);   }
    double   lengthSqrd ()          const  { return x*x+y*y;         }
    double   lengthRect ()          const  { return fabs(x)+fabs(y); }

    double   dist       (Point2d p) const  { return sqrt(sqr(x-p.x)+sqr(y-p.y)); }
    double   distSqrd   (Point2d p) const  { return sqr(x-p.x)+sqr(y-p.y);       }
    double   distRect   (Point2d p) const  { return fabs(x-p.x)+fabs(y-p.y);     }

    bool     isEqual    (Point2d p, double epsSqrd = epsAbsSqrd()) const { return (distSqrd(p) <= epsSqrd); }
    bool     isEqualRect(Point2d p, double epsRect = epsAbs    ()) const { return (distRect(p) <= epsRect); }

    void     operator +=(Point2d  p)       { x += p.x; y += p.y;       }
    void     operator +=(Vector2d v)       { x += v.x; y += v.y;       }
    void     operator -=(Point2d  p)       { x -= p.x; y -= p.y;       }
    void     operator -=(Vector2d v)       { x -= v.x; y -= v.y;       }
    void     operator *=(double scalar)    { x *= scalar; y *= scalar; }
    void     operator /=(double scalar)    { x /= scalar; y /= scalar; }
        
    bool     isValid() const { return fabs(x) < kMaxReal && fabs(y) < kMaxReal; }

    Vector2d toVector2d () const { return *(Vector2d*)this; }

    // Casts from AModeler::Point2d to AcGePoint2d
    //
    operator       AcGePoint2d& ()       { return *((AcGePoint2d*)this);       }
    operator const AcGePoint2d& () const { return *((const AcGePoint2d*)this); }

    // Cast from l-value AcGePoint2d to l-value AModeler::Point2d. This 
    // explicit cast function needs to be used only for l-values, e.g. when 
    // AModeler returns a Point2d as an output argument but we want to capture 
    // it in an AcGePoint2d. For non-l-values, the Point2d(const AcGePoint2d&) 
    // constructor will perform the cast automatically.
    //
    static Point2d& cast(AcGePoint2d& p) { return *(Point2d*)&p; }

    Point2d(const AcGePoint2d& p)        { *this = *(Point2d*)&p; }

    // Public data members
    //
    double x, y;

    static const Point2d kNull;

}; // class Point2d



inline Point2d operator *(double scalar, Point2d p) 
{ 
    return Point2d(scalar*p.x, scalar*p.y); 
}


inline double det(Point2d a, Point2d b)
{
    return (a.x * b.y - a.y * b.x);
} 


// intersection of two 2d lines (p1,v1) and (p2,v2) 
//
DllImpExp Point2d intersect(const Point2d& p1, const Vector2d v1, 
                            const Point2d& p2, const Vector2d v2,
                            bool& succeeded);


// Retuns true if the two line segments (p1,p2) and (q1,q2) intersect or 
// overlap, false otherwise. It handles special cases.
//
DllImpExp bool doIntersect(const Point2d& p1, 
                           const Point2d& p2, 
                           const Point2d& q1, 
                           const Point2d& q2);


// Project point p on line (lpoint, lvector)
//
Point2d projectPointOnLine(Point2d p, Point2d lpoint, Vector2d lvector);


AMODELER_NAMESPACE_END
#endif
