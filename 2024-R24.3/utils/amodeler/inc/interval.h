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
// Declaration of classes Interval1d, Interval2d, Interval3d and IntInterval3d.
// These classes keep an interval of values in 1D, 2D, 3D or 3D integer 
// spaces. 
//
// The Interval3d class corresponds to the well known "Bounding Box" concept. 
// We have made the classes look uniform accross 1,2 and 3 dimensions.
//
// The bounds of the interval can be accessed via public data members:
//
//   lower   ... Lower bound of the interval.
//   upper   ... Upper bound of the interval.
//
// The interval classes contain operators:
// 
//   +=    ... Extend the interval to cover the given value.
//   +=    ... Union this interval with another interval.
//   *=    ... Intersect this interval with another interval.
//   *     ... Intersect two intervals and return the result.
//   &&    ... A predicate, returns true iff the two intervals overlap
//   &&    ... A predicate, returns true iff the interval contains given value
//
// The meaning of the remaining methods is obvious.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_INTERVAL_H
#define AMODELER_INC_INTERVAL_H


#include <limits.h>
#include "plane.h"
#include "ipoint2d.h"

AMODELER_NAMESPACE_BEGIN


class DllImpExp Interval1d
{
public:

    Interval1d(                  ) : lower(kMaxReal), upper(kMinReal) {}
    Interval1d(double         val) : lower(val),  upper(val)          {}
    Interval1d(double a, double b)        
    {
        if (a < b) { lower = a; upper = b; } else { lower = b; upper = a; } 
    }
    
    Interval1d(double a, double b, int /*valuesAlreadyOrdered*/) : lower(a), upper(b) {}

    void operator +=(double val)
    {
        if (val < lower) lower = val;
        if (val > upper) upper = val;
    }
    
    void operator +=(const Interval1d interv)
    {
        if (interv.lower < lower) lower = interv.lower;
        if (interv.upper > upper) upper = interv.upper;
    }

    void operator *=(const Interval1d interv)
    {
        if (interv.lower > lower) lower = interv.lower;
        if (interv.upper < upper) upper = interv.upper;
    }
    
    Interval1d operator *(const Interval1d interv) const
    {
        return Interval1d(__max(lower, interv.lower), __min(upper, interv.upper));
    }

    Interval1d operator +(Interval1d interv) const
    {
        Interval1d tmp = *this;
        tmp += interv;
        return tmp;
    }

    // Do the two intervals overlap ?
    //
    bool operator &&(const Interval1d interv) const
    {
        return lower <= interv.upper && upper >= interv.lower;
    }

    // a <= b means a is subinterval of b
    //
    bool operator <=(const Interval1d interv) const
    {
        if (isNull())
        {
            return true;
        }
        else
        {
            return lower >= interv.lower && upper <= interv.upper;
        }
    }

    bool operator &&(double val) const
    {
        return lower <= val && val <= upper;
    }
        
    void   enlarge(double howMuch = 10*epsAbs());

    double length () const { return upper - lower;         }
    double mid    () const { return (upper + lower) * 0.5; }
    bool   isNull () const { return lower > upper;         }
    void   init   ()       { *this = kNull;                }

    static const Interval1d kNull;

    // Public data members
    //
    double lower;
    double upper;

};  // class Interval1d


inline bool operator &&(double val, Interval1d interv) 
{
    return interv.lower <= val && val <= interv.upper;
}



class DllImpExp Interval2d
{
public:

    Interval2d() : lower(kMaxReal, kMaxReal), upper(kMinReal, kMinReal) {}
    Interval2d(int /*doNotIntialize*/)                                  {}
    Interval2d(Point2d p) : lower(p), upper(p)                          {}
    Interval2d(Point2d a, const Point2d b) 
    {
        if (a.x < b.x) { lower.x = a.x; upper.x = b.x; } else { lower.x = b.x; upper.x = a.x; }
        if (a.y < b.y) { lower.y = a.y; upper.y = b.y; } else { lower.y = b.y; upper.y = a.y; }
    }

    Interval2d(Point2d center, double halfSize)
    {
        lower.x = center.x - halfSize;
        upper.x = center.x + halfSize;
        lower.y = center.y - halfSize;
        upper.y = center.y + halfSize;
    }

    Interval2d(Point2d a, Point2d b, int /*valuesAlreadyOrdered*/) : lower(a), upper(b) {}

    void operator +=(Point2d p)
    {
        if (p.x < lower.x) lower.x = p.x;
        if (p.x > upper.x) upper.x = p.x;

        if (p.y < lower.y) lower.y = p.y;
        if (p.y > upper.y) upper.y = p.y;
    }

    void operator +=(Interval2d interv)
    {
        if (interv.lower.x < lower.x) lower.x = interv.lower.x;
        if (interv.upper.x > upper.x) upper.x = interv.upper.x;
        if (interv.lower.y < lower.y) lower.y = interv.lower.y;
        if (interv.upper.y > upper.y) upper.y = interv.upper.y;
    }

    void operator *=(Interval2d interv)
    {
        if (interv.lower.x > lower.x) lower.x = interv.lower.x;
        if (interv.upper.x < upper.x) upper.x = interv.upper.x;
        if (interv.lower.y > lower.y) lower.y = interv.lower.y;
        if (interv.upper.y < upper.y) upper.y = interv.upper.y;
    }

    Interval2d operator *(Interval2d interv) const
    {
        Interval2d result;

        result.lower.x = __max(lower.x, interv.lower.x);
        result.upper.x = __min(upper.x, interv.upper.x);
        result.lower.y = __max(lower.y, interv.lower.y);
        result.upper.y = __min(upper.y, interv.upper.y);
        return result;
    }

    Interval2d operator +(Interval2d interv) const
    {
        Interval2d tmp = *this;
        tmp += interv;
        return tmp;
    }

    bool operator &&(Interval2d interv) const
    {
        return lower.x <= interv.upper.x && upper.x >= interv.lower.x &&
               lower.y <= interv.upper.y && upper.y >= interv.lower.y;
    }

    bool operator &&(Point2d p) const
    {
        return lower.x <= p.x && p.x <= upper.x &&
               lower.y <= p.y && p.y <= upper.y;
    }

    // a <= b means a is subinterval of b
    //
    bool operator <=(const Interval2d interv) const
    {
        if (isNull())
        {
            return true;
        }
        else
        {
            return lower.x >= interv.lower.x && upper.x <= interv.upper.x &&
                   lower.y >= interv.lower.y && upper.y <= interv.upper.y;
        }
    }

    bool    isNull ()      const { return lower.x > upper.x || lower.y > upper.y; }
    Point2d mid    ()      const { return (lower + upper) * 0.5;           }
    double  length ()      const { return lower.dist(upper);               }
    double  length (int i) const { return upper[i] - lower[i];             }
    void    init   ()            { *this = kNull;                          }
    void    enlarge(double howMuch = 10*epsAbs());

    static const Interval2d kNull;

    // Public data members
    //
    Point2d lower;
    Point2d upper;

};  // class Interval2d


inline bool operator &&(const Point2d p, Interval2d interv) 
{
    return interv.lower.x <= p.x && p.x <= interv.upper.x &&
           interv.lower.y <= p.y && p.y <= interv.upper.y;
}



class DllImpExp Interval3d
{
public:

    Interval3d() { lower.x = lower.y = lower.z = kMaxReal; upper.x = upper.y = upper.z = kMinReal; }
    Interval3d(int /*doNotIntialize*/)                      {}
    Interval3d(Point3d p)              : lower(p), upper(p) {}
    Interval3d(Point3d a, Point3d b) 
    {
        if (a.x < b.x) { lower.x = a.x; upper.x = b.x; } else { lower.x = b.x; upper.x = a.x; }
        if (a.y < b.y) { lower.y = a.y; upper.y = b.y; } else { lower.y = b.y; upper.y = a.y; }
        if (a.z < b.z) { lower.z = a.z; upper.z = b.z; } else { lower.z = b.z; upper.z = a.z; }
    }

    Interval3d(Point3d a, Point3d b, int /*valuesAlreadyOrdered*/) : lower(a), upper(b) {}

    Interval3d(Point3d center, double halfSize)
    {
        lower.x = center.x - halfSize;
        upper.x = center.x + halfSize;
        lower.y = center.y - halfSize;
        upper.y = center.y + halfSize;
        lower.z = center.z - halfSize;
        upper.z = center.z + halfSize;
    }

    void operator +=(Point3d p)
    {
        if (p.x < lower.x) lower.x = p.x;
        if (p.x > upper.x) upper.x = p.x;
        if (p.y < lower.y) lower.y = p.y;
        if (p.y > upper.y) upper.y = p.y;
        if (p.z < lower.z) lower.z = p.z;
        if (p.z > upper.z) upper.z = p.z;
    }

    void operator +=(Interval3d interv)
    {
        if (interv.lower.x < lower.x) lower.x = interv.lower.x;
        if (interv.upper.x > upper.x) upper.x = interv.upper.x;
        if (interv.lower.y < lower.y) lower.y = interv.lower.y;
        if (interv.upper.y > upper.y) upper.y = interv.upper.y;
        if (interv.lower.z < lower.z) lower.z = interv.lower.z;
        if (interv.upper.z > upper.z) upper.z = interv.upper.z;
    }

    Interval3d operator +(Interval3d interv) const
    {
        Interval3d tmp = *this;
        tmp += interv;
        return tmp;
    }

    void operator *=(Interval3d interv)
    {
        if (interv.lower.x > lower.x) lower.x = interv.lower.x;
        if (interv.upper.x < upper.x) upper.x = interv.upper.x;
        if (interv.lower.y > lower.y) lower.y = interv.lower.y;
        if (interv.upper.y < upper.y) upper.y = interv.upper.y;
        if (interv.lower.z > lower.z) lower.z = interv.lower.z;
        if (interv.upper.z < upper.z) upper.z = interv.upper.z;
    }

    Interval3d operator *(Interval3d interv) const
    {
        Interval3d result;

        result.lower.x = __max(lower.x, interv.lower.x);
        result.upper.x = __min(upper.x, interv.upper.x);
        result.lower.y = __max(lower.y, interv.lower.y);
        result.upper.y = __min(upper.y, interv.upper.y);
        result.lower.z = __max(lower.z, interv.lower.z);
        result.upper.z = __min(upper.z, interv.upper.z);
        return result;
    }

    Interval3d operator *(const Line3d& ray) const;

    bool operator &&(Interval3d interv) const
    {
        return lower.x <= interv.upper.x && upper.x >= interv.lower.x &&
               lower.y <= interv.upper.y && upper.y >= interv.lower.y &&
               lower.z <= interv.upper.z && upper.z >= interv.lower.z;
    }

    bool operator &&(Point3d p) const
    {
        return lower.x <= p.x && p.x <= upper.x &&
               lower.y <= p.y && p.y <= upper.y &&
               lower.z <= p.z && p.z <= upper.z;
    }

    // a <= b means a is subinterval of b
    //
    bool operator <=(Interval3d interv) const
    {
        if (isNull())
        {
            return true;
        }
        else 
        {
            return lower.x >= interv.lower.x && upper.x <= interv.upper.x &&
                   lower.y >= interv.lower.y && upper.y <= interv.upper.y &&
                   lower.z >= interv.lower.z && upper.z <= interv.upper.z;
        }
    }

    Interval2d toInterval2d(int dropCoord) const
    {
        switch (dropCoord)
        {
        case 0:
            return Interval2d(Point2d(lower.y, lower.z), Point2d(upper.y, upper.z));
        case 1:
            return Interval2d(Point2d(lower.z, lower.x), Point2d(upper.z, upper.x));
        default:
            return Interval2d(Point2d(lower.x, lower.y), Point2d(upper.x, upper.y));
        }
    }

    bool    isNull ()      const { return lower.x > upper.x || lower.y > upper.y || lower.z > upper.z; }
    Point3d mid    ()      const { return (lower + upper) * 0.5; }
    double  length ()      const { return lower.dist(upper); }
    double  length (int i) const { return upper[i] - lower[i]; }
    void    init   ()            { *this = kNull; }
    void    enlarge(double howMuch = 10*epsAbs());

    Point3d lowerInDirection(const Vector3d& direction) const
    {
        return Point3d(direction.x >= 0.0 ? lower.x : upper.x,
                       direction.y >= 0.0 ? lower.y : upper.y,
                       direction.z >= 0.0 ? lower.z : upper.z);
    }

    Point3d upperInDirection(const Vector3d& direction) const
    {
        return Point3d(direction.x >= 0.0 ? upper.x : lower.x,
                       direction.y >= 0.0 ? upper.y : lower.y,
                       direction.z >= 0.0 ? upper.z : lower.z);
    }
 
    bool intersectsPlane( const Plane& plane) const
    {
        return plane.dist(lowerInDirection(plane.normal)) <=  epsAbs() &&
               plane.dist(upperInDirection(plane.normal)) >= -epsAbs();
    }

    static const Interval3d kNull;

    // Public data members
    //
    Point3d lower;
    Point3d upper;

};  // class Interval3d



inline bool operator &&(Point3d p, Interval3d interv) 
{
    return interv.lower.x <= p.x && p.x <= interv.upper.x &&
           interv.lower.y <= p.y && p.y <= interv.upper.y &&
           interv.lower.z <= p.z && p.z <= interv.upper.z;
}



class DllImpExp IntInterval1d
{
public:

    IntInterval1d()         : lower(INT_MAX), upper(INT_MIN) {}
#ifdef _BullseyeCoverage
    explicit 
#endif
    IntInterval1d(int val ) : lower(val), upper(val)         {}
    IntInterval1d(int a, int b)
    {
        if (a < b) { lower = a; upper = b; } else { lower = b; upper = a; }
    }

    IntInterval1d(int a, int b, int /*valuesAlreadyOrdered*/) : lower(a), upper(b) {}

    void operator +=(int val)
    {
        if (val < lower) lower = val;
        if (val > upper) upper = val;
    }

    void operator +=(IntInterval1d interv)
    {
        if (interv.lower < lower) lower = interv.lower;
        if (interv.upper > upper) upper = interv.upper;
    }

    void operator *=(IntInterval1d interv)
    {
        if (interv.lower > lower) lower = interv.lower;
        if (interv.upper < upper) upper = interv.upper;
    }

    IntInterval1d operator *(IntInterval1d interv) const
    {
        IntInterval1d result;

        result.lower = __max(lower, interv.lower);
        result.upper = __min(upper, interv.upper);
        return result;
    }

    IntInterval1d operator +(IntInterval1d interv) const
    {
        IntInterval1d tmp = *this;
        tmp += interv;
        return tmp;
    }

    bool operator &&(IntInterval1d interv) const
    {
        return lower <= interv.upper && upper >= interv.lower;
    }

    bool operator &&(int val) const
    {
        return lower <= val && val <= upper;
    }

    // a <= b means a is subinterval of b
    //
    bool operator <=(IntInterval1d interv) const
    {
        if (isNull())
        {
            return true;
        }
        else
        {
            return lower >= interv.lower && upper <= interv.upper;
        }
    }

    int        length() const { return upper - lower;       }
    bool       isNull() const { return lower > upper;       }
    int        mid   () const { return (upper + lower) / 2; }
    void       init  ()       { *this = kNull;              }

    void enlarge(int howMuch = 1)
    {
        lower -= howMuch;
        upper += howMuch;
    }

    static const IntInterval1d kNull;

    // Public data members
    //
    int lower;
    int upper;

};  // class IntInterval1d



inline bool operator &&(int val, IntInterval1d interv) 
{
    return interv.lower <= val && val <= interv.upper;
}



class DllImpExp IntInterval2d
{
public:

    IntInterval2d()                    : lower(INT_MAX, INT_MAX), upper(INT_MIN, INT_MIN) {}
    IntInterval2d(IntPoint2d p)        : lower(p), upper(p)                               {}
    IntInterval2d(IntPoint2d a, IntPoint2d b) 
    {
        if (a.x < b.x) { lower.x = a.x; upper.x = b.x; } else { lower.x = b.x; upper.x = a.x; }
        if (a.y < b.y) { lower.y = a.y; upper.y = b.y; } else { lower.y = b.y; upper.y = a.y; }
    }

    IntInterval2d(IntPoint2d a, IntPoint2d b, int /*valuesAlreadyOrdered*/) : lower(a), upper(b) {}

    void operator +=(IntPoint2d p)
    {
        if (p.x < lower.x) lower.x = p.x;
        if (p.x > upper.x) upper.x = p.x;
        if (p.y < lower.y) lower.y = p.y;
        if (p.y > upper.y) upper.y = p.y;
    }

    void operator +=(IntInterval2d interv)
    {
        if (interv.lower.x < lower.x) lower.x = interv.lower.x;
        if (interv.upper.x > upper.x) upper.x = interv.upper.x;
        if (interv.lower.y < lower.y) lower.y = interv.lower.y;
        if (interv.upper.y > upper.y) upper.y = interv.upper.y;
    }

    void operator *=(IntInterval2d interv)
    {
        if (interv.lower.x > lower.x) lower.x = interv.lower.x;
        if (interv.upper.x < upper.x) upper.x = interv.upper.x;
        if (interv.lower.y > lower.y) lower.y = interv.lower.y;
        if (interv.upper.y < upper.y) upper.y = interv.upper.y;
    }

    IntInterval2d operator *(IntInterval2d interv) const
    {
        IntInterval2d result;

        result.lower.x = __max(lower.x, interv.lower.x);
        result.upper.x = __min(upper.x, interv.upper.x);
        result.lower.y = __max(lower.y, interv.lower.y);
        result.upper.y = __min(upper.y, interv.upper.y);
        return result;
    }

    IntInterval2d operator +(IntInterval2d interv) const
    {
        IntInterval2d tmp = *this;
        tmp += interv;
        return tmp;
    }

    bool operator &&(IntInterval2d interv) const
    {
        return lower.x <= interv.upper.x && upper.x >= interv.lower.x &&
               lower.y <= interv.upper.y && upper.y >= interv.lower.y;
    }

    bool operator &&(IntPoint2d p) const
    {
        return lower.x <= p.x && p.x <= upper.x &&
               lower.y <= p.y && p.y <= upper.y;
    }

    // a <= b means a is subinterval of b
    //
    bool operator <=(Interval2d interv) const
    {
        if (isNull())
        {
            return true;
        }
        else
        {
            return lower.x >= interv.lower.x && upper.x <= interv.upper.x &&
                   lower.y >= interv.lower.y && upper.y <= interv.upper.y;
        }
    }

    IntInterval1d project(int i) const
    {
        return IntInterval1d(lower[i], upper[i]);
    }

    int        length(int i) const { return upper[i] - lower[i]; }

    bool       isNull() const { return lower.x > upper.x || lower.y > upper.y; }
    IntPoint2d mid   () const { return IntPoint2d((upper.x + lower.x) / 2,
                                                  (upper.y + lower.y) / 2); }
    void       init  ()       { *this = kNull; }

    void enlarge(int howMuch = 1)
    {
        lower.x -= howMuch;
        lower.y -= howMuch;
        upper.x += howMuch;
        upper.y += howMuch;
    }
    static const IntInterval2d kNull;

    // Public data members
    //
    IntPoint2d lower;
    IntPoint2d upper;

};  // class IntInterval2d


inline bool operator &&(IntPoint2d p, IntInterval2d interv) 
{
    return interv.lower.x <= p.x && p.x <= interv.upper.x &&
           interv.lower.y <= p.y && p.y <= interv.upper.y;
}





class DllImpExp IntInterval3d
{
public:

    IntInterval3d() : lower(INT_MAX, INT_MAX, INT_MAX), upper(INT_MIN, INT_MIN, INT_MIN) {}
    IntInterval3d(IntPoint3d p) : lower( p), upper( p)                            {}
    IntInterval3d(IntPoint3d a, const IntPoint3d b) 
    {
        if (a.x < b.x) { lower.x = a.x; upper.x = b.x; } else { lower.x = b.x; upper.x = a.x; }
        if (a.y < b.y) { lower.y = a.y; upper.y = b.y; } else { lower.y = b.y; upper.y = a.y; }
        if (a.z < b.z) { lower.z = a.z; upper.z = b.z; } else { lower.z = b.z; upper.z = a.z; }
    }

    IntInterval3d(IntPoint3d a, IntPoint3d b, int /*valuesAlreadyOrdered*/) : lower(a), upper(b) {}

    void operator +=(IntPoint3d p)
    {
        if (p.x < lower.x) lower.x = p.x;
        if (p.x > upper.x) upper.x = p.x;
        if (p.y < lower.y) lower.y = p.y;
        if (p.y > upper.y) upper.y = p.y;
        if (p.z < lower.z) lower.z = p.z;
        if (p.z > upper.z) upper.z = p.z;
    }

    void operator +=(IntInterval3d interv)
    {
        if (interv.lower.x < lower.x) lower.x = interv.lower.x;
        if (interv.upper.x > upper.x) upper.x = interv.upper.x;
        if (interv.lower.y < lower.y) lower.y = interv.lower.y;
        if (interv.upper.y > upper.y) upper.y = interv.upper.y;
        if (interv.lower.z < lower.z) lower.z = interv.lower.z;
        if (interv.upper.z > upper.z) upper.z = interv.upper.z;
    }

    void operator *=(IntInterval3d interv)
    {
        if (interv.lower.x > lower.x) lower.x = interv.lower.x;
        if (interv.upper.x < upper.x) upper.x = interv.upper.x;
        if (interv.lower.y > lower.y) lower.y = interv.lower.y;
        if (interv.upper.y < upper.y) upper.y = interv.upper.y;
        if (interv.lower.z > lower.z) lower.z = interv.lower.z;
        if (interv.upper.z < upper.z) upper.z = interv.upper.z;
    }

    IntInterval3d operator *(IntInterval3d interv) const
    {
        IntInterval3d result;

        result.lower.x = __max(lower.x, interv.lower.x);
        result.upper.x = __min(upper.x, interv.upper.x);
        result.lower.y = __max(lower.y, interv.lower.y);
        result.upper.y = __min(upper.y, interv.upper.y);
        result.lower.z = __max(lower.z, interv.lower.z);
        result.upper.z = __min(upper.z, interv.upper.z);
        return result;
    }

    IntInterval3d operator +(IntInterval3d interv) const
    {
        IntInterval3d tmp = *this;
        tmp += interv;
        return tmp;
    }

    bool operator &&(IntInterval3d interv) const
    {
        return lower.x <= interv.upper.x && upper.x >= interv.lower.x &&
               lower.y <= interv.upper.y && upper.y >= interv.lower.y &&
               lower.z <= interv.upper.z && upper.z >= interv.lower.z;
    }

    bool operator &&(IntPoint3d p) const
    {
        return lower.x <= p.x && p.x <= upper.x &&
               lower.y <= p.y && p.y <= upper.y &&
               lower.z <= p.z && p.z <= upper.z;
    }

    // a <= b means a is subinterval of b
    //
    bool operator <=(IntInterval3d interv) const
    {
        if (isNull())
        {
            return true;
        }
        else
        {
            return lower.x >= interv.lower.x && upper.x <= interv.upper.x &&
                   lower.y >= interv.lower.y && upper.y <= interv.upper.y &&
                   lower.z >= interv.lower.z && upper.z <= interv.upper.z;
        }
    }

    IntInterval1d project(int i) const
    {
        return IntInterval1d(lower[i], upper[i]);
    }

    int        length(int i) const { return upper[i] - lower[i]; }

    bool       isNull() const { return lower.x > upper.x || lower.y > upper.y || lower.z > upper.z; }
    IntPoint3d mid   () const { return IntPoint3d((upper.x + lower.x) / 2,
                                                  (upper.y + lower.y) / 2,
                                                  (upper.z + lower.z) / 2); }
    void enlarge(int howMuch = 1)
    {
        lower.x -= howMuch;
        lower.y -= howMuch;
        lower.z -= howMuch;
        upper.x += howMuch;
        upper.y += howMuch;
        upper.z += howMuch;
    }

    void       init  ()       { *this = kNull; }

    static const IntInterval3d kNull;

    // Public data members
    //
    IntPoint3d lower;
    IntPoint3d upper;

};  // class IntInterval3d


inline bool operator &&(IntPoint3d p, IntInterval3d interv) 
{
    return interv.lower.x <= p.x && p.x <= interv.upper.x &&
           interv.lower.y <= p.y && p.y <= interv.upper.y &&
           interv.lower.z <= p.z && p.z <= interv.upper.z;
}


template<class I>
bool overlap(I i1, I i2)
{
    return i1.operator &&(i2);
}

inline bool point_inside(Interval2d const &i, Point2d const& p)
{
    return i.operator &&(p);
}

inline bool point_inside(Interval3d const &i, Point3d const& p)
{
    return i.operator &&(p);
}

inline bool point_inside(IntInterval2d const &i, IntPoint2d const& p)
{
    return i.operator &&(p);
}

inline bool point_inside(IntInterval3d const &i, IntPoint3d const& p)
{
    return i.operator &&(p);
}

inline bool point_inside(Interval1d i, double d)
{
    return operator &&(d, i);
}

inline bool point_inside(IntInterval1d i, int n)
{
    return operator &&(n, i);
}

AMODELER_NAMESPACE_END
#endif
