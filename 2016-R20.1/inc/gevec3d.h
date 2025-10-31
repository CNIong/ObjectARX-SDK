//
//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION:
//
// This file contains the class AcGeVector3d - a mathematical entity
// used to represent a direction and magnitude in 3-space, or
// alternatively to represent a linear translation in 3-space.

#ifndef AC_GEVEC3D_H
#define AC_GEVEC3D_H

#include "adesk.h"
#include "gegbl.h"
#include "gegblabb.h"
#pragma pack (push, 8)

class AcGeMatrix3d;
class AcGeVector2d;
class AcGePlane;
class AcGePlanarEnt;

class 
GE_DLLEXPIMPORT
AcGeVector3d
{
public:
    AcGeVector3d();
    AcGeVector3d(const AcGeVector3d& vec);
    AcGeVector3d(double x, double y, double z);
    AcGeVector3d(const AcGePlanarEnt&, const AcGeVector2d&);

    // The additive identity, x-axis, y-axis, and z-axis.
    //
    static const   AcGeVector3d kIdentity;
    static const   AcGeVector3d kXAxis;
    static const   AcGeVector3d kYAxis;
    static const   AcGeVector3d kZAxis;

    // Multiplication with matrices.
    //
    friend
GE_DLLEXPIMPORT
    AcGeVector3d   operator *  (const AcGeMatrix3d& mat, const AcGeVector3d& vec);
    AcGeVector3d&  setToProduct(const AcGeMatrix3d& mat, const AcGeVector3d& vec);

    AcGeVector3d&  transformBy (const AcGeMatrix3d& leftSide);
    AcGeVector3d&  rotateBy    (double ang , const AcGeVector3d& axis );
    AcGeVector3d&  mirror      (const AcGeVector3d& normalToPlane);
    AcGeVector2d   convert2d   (const AcGePlanarEnt& pln) const;

    // Multiplication by scalar.
    //
    AcGeVector3d   operator *  (double scl) const;
    friend
GE_DLLEXPIMPORT
    AcGeVector3d   operator *  (double scl, const AcGeVector3d& vec);
    AcGeVector3d&  operator *= (double scl);
    AcGeVector3d&  setToProduct(const AcGeVector3d& vec, double scl);
    AcGeVector3d   operator /  (double scl) const;
    AcGeVector3d&  operator /= (double scl);

    // Addition and subtraction of vectors.
    //
    AcGeVector3d   operator +  (const AcGeVector3d& vec) const;
    AcGeVector3d&  operator += (const AcGeVector3d& vec);
    AcGeVector3d   operator -  (const AcGeVector3d& vec) const;
    AcGeVector3d&  operator -= (const AcGeVector3d& vec);
    AcGeVector3d&  setToSum    (const AcGeVector3d& vec1, const AcGeVector3d& vec2);
    AcGeVector3d   operator -  () const;
    AcGeVector3d&  negate      ();

    // Perpendicular vector
    //
    AcGeVector3d   perpVector  () const;

    // Angle argument.
    //
    double         angleTo     (const AcGeVector3d& vec) const;
    double         angleTo     (const AcGeVector3d& vec,
                                const AcGeVector3d& refVec) const;
    double         angleOnPlane(const AcGePlanarEnt& pln) const;

    // Vector length operations.
    //
    AcGeVector3d   normal      (const AcGeTol& tol = AcGeContext::gTol) const;
    AcGeVector3d&  normalize   (const AcGeTol& tol = AcGeContext::gTol);
    AcGeVector3d&  normalize   (const AcGeTol& tol, AcGeError& flag);
        // Possible errors:  k0This.  Returns object unchanged on error. 
    double         length      () const;
    double         lengthSqrd  () const;
    Adesk::Boolean isUnitLength(const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean isZeroLength(const AcGeTol& tol = AcGeContext::gTol) const;

    // Direction tests.
    //
    Adesk::Boolean isParallelTo(const AcGeVector3d& vec,
                                const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean isParallelTo(const AcGeVector3d& vec,
                                const AcGeTol& tol, AcGeError& flag) const;
        // Possible errors:  k0This, k0Arg1. 
        // Returns kFalse on error.
    Adesk::Boolean isCodirectionalTo(const AcGeVector3d& vec,
                                     const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean isCodirectionalTo(const AcGeVector3d& vec,
                                     const AcGeTol& tol, AcGeError& flag) const;
        // Possible errors: k0Arg1, k0Arg2, kPerpendicularArg1Arg2. 
        // Returns copy of unchanged object on error.
    Adesk::Boolean isPerpendicularTo(const AcGeVector3d& vec,
                                     const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean isPerpendicularTo(const AcGeVector3d& vec,
                                     const AcGeTol& tol, AcGeError& flag) const;
        // Possible errors: k0Arg1, k0Arg2, kPerpendicularArg1Arg2. 
        // Returns copy of unchanged object on error.

    // Dot and Cross product.
    //
    double         dotProduct  (const AcGeVector3d& vec) const;
    AcGeVector3d   crossProduct(const AcGeVector3d& vec) const;

    // Calculate rotation.
    //
    AcGeMatrix3d   rotateTo    (const AcGeVector3d& vec, const AcGeVector3d& axis
                                = AcGeVector3d::kIdentity) const;

    // Projection on plane
    //
    AcGeVector3d   project      (const AcGeVector3d& planeNormal,
                                 const AcGeVector3d& projectDirection) const;
    AcGeVector3d   project      (const AcGeVector3d& planeNormal,
                                 const AcGeVector3d& projectDirection,  
                                 const AcGeTol& tol, AcGeError& flag) const;
        // Possible errors: k0Arg1, k0Arg2, kPerpendicularArg1Arg2. 
        // Returns copy of unchanged object on error.
    AcGeVector3d   orthoProject (const AcGeVector3d& planeNormal) const;
    AcGeVector3d   orthoProject (const AcGeVector3d& planeNormal, 
                                 const AcGeTol& tol, AcGeError& flag) const;
        // Possible errors:  k0Arg1.
        // Returns a copy of unchanged object on error. 

    // Tests for equivalence using the Euclidean norm.
    //
    bool operator == (const AcGeVector3d& vec) const;
    bool operator != (const AcGeVector3d& vec) const;
    bool isEqualTo   (const AcGeVector3d& vec,
                      const AcGeTol& tol = AcGeContext::gTol) const;

    // For convenient access to the data.
    //
    double         operator [] (unsigned int i) const;
    double&        operator [] (unsigned int i);
    unsigned int   largestElement() const;
    AcGeVector3d&  set         (double x, double y, double z);
    AcGeVector3d&  set         (const AcGePlanarEnt& pln, const AcGeVector2d& vec);

    // Convert to the matrix of translation.
    //
    operator       AcGeMatrix3d() const;

    // Co-ordinates.
    //
    double         x, y, z;
};

// Creates the identity vector.
//
inline
AcGeVector3d::AcGeVector3d() : x(0.0), y(0.0), z(0.0)
{
}

inline
AcGeVector3d::AcGeVector3d(const AcGeVector3d& src) : x(src.x),y(src.y),z(src.z)
{
}

// Creates a vector intialized to ( xx, yy, zz ).
//
inline
AcGeVector3d::AcGeVector3d(double xx, double yy, double zz) : x(xx),y(yy),z(zz)
{
}

inline bool
AcGeVector3d::operator == (const AcGeVector3d& v) const
{
    return this->isEqualTo(v);
}

// This operator is the logical negation of the `==' operator.
//
inline bool
AcGeVector3d::operator != (const AcGeVector3d& v) const
{
    return !this->isEqualTo(v);
}

// Returns a vector that is formed from adding the components of
// this vector with `v'.
//
inline AcGeVector3d
AcGeVector3d::operator + (const AcGeVector3d& v) const
{
    return AcGeVector3d (x + v.x, y + v.y, z + v.z);
}

// This is equivalent to the statement `thisVec = thisVec + v;'
//
inline AcGeVector3d&
AcGeVector3d::operator += (const AcGeVector3d& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

// Using this operator is equivalent to using `thisVec + (-v);'
//
inline AcGeVector3d
AcGeVector3d::operator - (const AcGeVector3d& v) const
{
    return AcGeVector3d (x - v.x, y - v.y, z - v.z);
}

// This is equivalent to the statement `thisVec = thisVec - v;'
//
inline AcGeVector3d&
AcGeVector3d::operator -= (const AcGeVector3d& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

inline AcGeVector3d&
AcGeVector3d::setToSum(const AcGeVector3d& v1, const AcGeVector3d& v2)
{
    x = v1.x + v2.x;
    y = v1.y + v2.y;
    z = v1.z + v2.z;
    return *this;
}

// Returns a vector that is formed by negating each of the components
// of this vector.
//
inline AcGeVector3d
AcGeVector3d::operator - () const
{
    return AcGeVector3d (-x, -y, -z);
}

// `v.negate()' is equivalent to the statement `v = -v;'
//
inline AcGeVector3d&
AcGeVector3d::negate()
{
    x = -x;
    y = -y;
    z = -z;
    return *this;
}

// This operator returns a vector that is the scalar product of
// `s' and this vector.
//
inline AcGeVector3d
AcGeVector3d::operator * (double s) const
{
    return AcGeVector3d (x * s, y * s, z * s);
}

// This is equivalent to the statement `v = v * s'.
//
inline AcGeVector3d&
AcGeVector3d::operator *= (double s)
{
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

inline AcGeVector3d&
AcGeVector3d::setToProduct(const AcGeVector3d& v, double s)
{
    x = s * v.x;
    y = s * v.y;
    z = s * v.z;
    return *this;
}

// Returns a vector such that each of the coordinates of this vector
// have been divided by val.
//
inline AcGeVector3d
AcGeVector3d::operator / (double val) const
{
    return AcGeVector3d (x/val, y/val, z/val);
}

// This is equivalent to the statement `v = v / val;'
// Each coordinate of this vector is divided by val.
//
inline AcGeVector3d&
AcGeVector3d::operator /= (double val)
{
    x /= val;
    y /= val;
    z /= val;
    return *this;
}

// Returns the square of the Euclidean length of this vector.
//
inline double
AcGeVector3d::lengthSqrd() const
{
    return x*x + y*y + z*z;
}

// Returns the dot product of this vector and `v'.
//
inline double
AcGeVector3d::dotProduct(const AcGeVector3d& v) const
{
    return x * v.x + y * v.y + z * v.z;
}

// Sets the vector to ( xx, yy, zz ).
//
inline AcGeVector3d&
AcGeVector3d::set(double xx, double yy, double zz)
{
    x = xx;
    y = yy;
    z = zz;
    return *this;
}

// Indexes the vector as if it were an array.  `x' is index `0',
// `y' is index `1' and `z' is index `2'.
//
inline double
AcGeVector3d::operator [] (unsigned int i) const
{
    return *(&x+i);
}

inline double& AcGeVector3d::operator [] (unsigned int i)
{
    return *(&x+i);
}
#define ADSK_ACGEVECTOR3D_DEFINED
#include "acarrayhelper.h"

#pragma pack (pop)
#endif
