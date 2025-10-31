///////////////////////////////////////////////////////////////////////////////
//
// © Autodesk, Inc. 1998-2010. All rights reserved.
//
// The information contained herein is confidential, proprietary
// to Autodesk,  Inc.,  and considered a trade secret as defined
// in section 499C of the penal code of the State of California.
// Use of  this information  by  anyone  other  than  authorized
// employees of Autodesk, Inc.  is granted  only under a written
// non-disclosure agreement,  expressly  prescribing  the  scope
// and manner of such use.
//
// DESCRIPTION:
//
// Declaration of class Vector2d, keeping a vector in 2D space. The coordinates
// of the vector are accessed via public data members 'x' and 'y' or via 
// the subscript operator, index 0 being the x-coordinate, index 1 being the 
// y-coordinate.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_VECTOR2D_H
#define AMODELER_INC_VECTOR2D_H


#include <math.h>
#include "global.h"

class AcGeVector2d;

AMODELER_NAMESPACE_BEGIN


class DllImpExp Vector2d
{
public:

    Vector2d() {} // Warning: No default constructor
    Vector2d(double xx, double yy) : x(xx), y(yy) {}

    Vector2d operator + (Vector2d  v)   const { return Vector2d(x+v.x, y+v.y); }
    Vector2d operator - (Vector2d  v)   const { return Vector2d(x-v.x, y-v.y); }
    double   operator % (Vector2d  v)   const { return x*v.x+y*v.y;            }
    Vector2d operator - ()              const { return Vector2d(-x, -y);       }

    Vector2d operator  *(double scalar) const { return Vector2d(x*scalar, y*scalar); }
    Vector2d operator  /(double scalar) const { return Vector2d(x/scalar, y/scalar); }

    double   operator [](int index)     const { return (&x)[index];     }
    double&  operator [](int index)           { return (&x)[index];     }

    double   length     ()              const { return sqrt(x*x+y*y);   }
    double   lengthSqrd ()              const { return x*x+y*y;         }
    double   lengthRect ()              const { return fabs(x)+fabs(y); }

    Vector2d normalize  () const;

    double   dist       (Vector2d v) const { return (*this-v).length();     }
    double   distSqrd   (Vector2d v) const { return (*this-v).lengthSqrd(); }
    double   distRect   (Vector2d v) const { return (*this-v).lengthRect(); }

    bool     isEqual    (Vector2d v, double epsSqrd = epsNorSqrd()) const { return (distSqrd(v) <= epsSqrd); }
    bool     isEqualRect(Vector2d v, double epsRect = epsNor()    ) const { return (distRect(v) <= epsRect); }
    bool     isExactNull()         const { return x == 0 && y == 0; }
    bool     isParallel (const Vector2d&) const;
    bool     isPerpend  (const Vector2d&) const;
    
    void     operator +=(Vector2d v)        { x += v.x; y += v.y;       }
    void     operator -=(Vector2d v)        { x -= v.x; y -= v.y;       }
    void     operator *=(double scalar)     { x *= scalar; y *= scalar; }
    void     operator /=(double scalar)     { x /= scalar; y /= scalar; }

    Vector2d perpend    () const            { return Vector2d(-y, x);   }

    double   angle      (const Vector2d&) const;
    bool     isNull     (double epsSqrd = epsNorSqrd()) const { return lengthSqrd() <= epsSqrd; }

    // Casts from AModeler::Vector2d to AcGeVector2d
    //
    operator       AcGeVector2d& ()       { return *((AcGeVector2d*)this);       }
    operator const AcGeVector2d& () const { return *((const AcGeVector2d*)this); }

    // Cast from l-value AcGeVector2d to l-value AModeler::Vector2d. This 
    // explicit cast function needs to be used only for l-values, e.g. 
    // when AModeler returns a Vector2d as an output argument but we want 
    // to capture it in an AcGeVector2d. For non-l-values, the 
    // Vector2d(const AcGeVector2d&) constructor will perform the cast 
    // automatically.
    //
    static Vector2d& cast(AcGeVector2d& v) { return *(Vector2d*)&v; }

    Vector2d(const AcGeVector2d& v)        { *this = *(Vector2d*)&v; }

    // Public data members
    //
    double x, y;

    static const Vector2d kNull;
    static const Vector2d kXDir;
    static const Vector2d kYDir;

}; // class Vector2d



// Inlines (do not look beyond this point)


inline Vector2d Vector2d::normalize() const 
{ 
    const double l = length(); 
    return (l > kEpsZero ? Vector2d(x/l, y/l) : Vector2d(0,0));
}



inline double det(Vector2d v1, Vector2d v2)
{
    return (v1.x * v2.y - v1.y * v2.x);
}


AMODELER_NAMESPACE_END
#endif
