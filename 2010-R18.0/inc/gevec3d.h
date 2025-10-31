//
#ifndef AC_GEVEC3D_H
#define AC_GEVEC3D_H
//
// (C) Copyright 1993-2009 by Autodesk, Inc.
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
// This file contains the class AcGeVector3d - a mathematical entity
// used to represent a direction and magnitude in 3-space, or
// alternatively to represent a linear translation in 3-space.

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
__forceinline
AcGeVector3d::AcGeVector3d() : x(0.0), y(0.0), z(0.0)
{
}

__forceinline
AcGeVector3d::AcGeVector3d(const AcGeVector3d& src) : x(src.x),y(src.y),z(src.z)
{
}

// Creates a vector intialized to ( xx, yy, zz ).
//
__forceinline
AcGeVector3d::AcGeVector3d(double xx, double yy, double zz) : x(xx),y(yy),z(zz)
{
}

__forceinline bool
AcGeVector3d::operator == (const AcGeVector3d& v) const
{
    return this->isEqualTo(v);
}

// This operator is the logical negation of the `==' operator.
//
__forceinline bool
AcGeVector3d::operator != (const AcGeVector3d& v) const
{
    return !this->isEqualTo(v);
}

// Returns a vector that is formed from adding the components of
// this vector with `v'.
//
__forceinline AcGeVector3d
AcGeVector3d::operator + (const AcGeVector3d& v) const
{
    return AcGeVector3d (x + v.x, y + v.y, z + v.z);
}

// This is equivalent to the statement `thisVec = thisVec + v;'
//
__forceinline AcGeVector3d&
AcGeVector3d::operator += (const AcGeVector3d& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

// Using this operator is equivalent to using `thisVec + (-v);'
//
__forceinline AcGeVector3d
AcGeVector3d::operator - (const AcGeVector3d& v) const
{
    return AcGeVector3d (x - v.x, y - v.y, z - v.z);
}

// This is equivalent to the statement `thisVec = thisVec - v;'
//
__forceinline AcGeVector3d&
AcGeVector3d::operator -= (const AcGeVector3d& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

__forceinline AcGeVector3d&
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
__forceinline AcGeVector3d
AcGeVector3d::operator - () const
{
    return AcGeVector3d (-x, -y, -z);
}

// `v.negate()' is equivalent to the statement `v = -v;'
//
__forceinline AcGeVector3d&
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
__forceinline AcGeVector3d
AcGeVector3d::operator * (double s) const
{
    return AcGeVector3d (x * s, y * s, z * s);
}

// This is equivalent to the statement `v = v * s'.
//
__forceinline AcGeVector3d&
AcGeVector3d::operator *= (double s)
{
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

__forceinline AcGeVector3d&
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
__forceinline AcGeVector3d
AcGeVector3d::operator / (double val) const
{
    return AcGeVector3d (x/val, y/val, z/val);
}

// This is equivalent to the statement `v = v / val;'
// Each coordinate of this vector is divided by val.
//
__forceinline AcGeVector3d&
AcGeVector3d::operator /= (double val)
{
    x /= val;
    y /= val;
    z /= val;
    return *this;
}

// Returns the square of the Euclidean length of this vector.
//
__forceinline double
AcGeVector3d::lengthSqrd() const
{
    return x*x + y*y + z*z;
}

// Returns the dot product of this vector and `v'.
//
__forceinline double
AcGeVector3d::dotProduct(const AcGeVector3d& v) const
{
    return x * v.x + y * v.y + z * v.z;
}

// Sets the vector to ( xx, yy, zz ).
//
__forceinline AcGeVector3d&
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
__forceinline double
AcGeVector3d::operator [] (unsigned int i) const
{
    return *(&x+i);
}

__forceinline double& AcGeVector3d::operator [] (unsigned int i)
{
    return *(&x+i);
}
#define ADSK_ACGEVECTOR3D_DEFINED
#include "acarrayhelper.h"

#pragma pack (pop)
#endif
