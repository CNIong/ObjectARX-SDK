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
// This file contains the class AcGeScale2d - a mathematical entity used
// to represent scaling transformations in 2-space.
// Contract:  The scale vector components must never be set to zero
// (or near zero within floating point tolerances).

#ifndef AC_GESCL2D_H
#define AC_GESCL2D_H

#include "adesk.h"
#include "gegbl.h"
#pragma pack (push, 8)

class AcGeMatrix2d;
class AcGeScale3d;

class 
GE_DLLEXPIMPORT
AcGeScale2d
{
public:
    AcGeScale2d();
    AcGeScale2d(const AcGeScale2d& src);
    AcGeScale2d(double factor);
    AcGeScale2d(double xFactor, double yFactor);

    // The identity scaling operation.
    //
    static const   AcGeScale2d kIdentity;

    // Multiplication.
    //
    AcGeScale2d    operator *  (const AcGeScale2d& sclVec) const;
    AcGeScale2d&   operator *= (const AcGeScale2d& scl);
    AcGeScale2d&   preMultBy   (const AcGeScale2d& leftSide);
    AcGeScale2d&   postMultBy  (const AcGeScale2d& rightSide);
    AcGeScale2d&   setToProduct(const AcGeScale2d& sclVec1, const AcGeScale2d& sclVec2);
    AcGeScale2d    operator *  (double s) const;
    AcGeScale2d&   operator *= (double s);
    AcGeScale2d&   setToProduct(const AcGeScale2d& sclVec, double s);
    friend
GE_DLLEXPIMPORT
    AcGeScale2d    operator *  (double, const AcGeScale2d& scl);

    // Multiplicative inverse.
    //
    AcGeScale2d    inverse        () const;
    AcGeScale2d&   invert         ();

    Adesk::Boolean isProportional(const AcGeTol& tol = AcGeContext::gTol) const;

    // Tests for equivalence using the infinity norm.
    //
    bool operator == (const AcGeScale2d& sclVec) const;
    bool operator != (const AcGeScale2d& sclVec) const;
    bool isEqualTo   (const AcGeScale2d& scaleVec,
                      const AcGeTol& tol = AcGeContext::gTol) const;

     // For convenient access to the data.
    //
    double         operator [] (unsigned int i) const;
    double&        operator [] (unsigned int i);
    AcGeScale2d&   set         (double sc0, double sc1);

    // Conversion to/from matrix form.
    //
    operator       AcGeMatrix2d   () const;
    void           getMatrix      (AcGeMatrix2d& mat) const;
    AcGeScale2d&   extractScale   ( const AcGeMatrix2d& mat );
    AcGeScale2d&   removeScale    ( AcGeMatrix2d& mat );

    // Cast up to 3d scale.
    //
    operator       AcGeScale3d    () const;

    // The scale components in x and y.
    //
    double         sx, sy;
};

inline double
AcGeScale2d::operator [] (unsigned int i) const
{
    return *(&sx+i);
}

inline double&
AcGeScale2d::operator [] (unsigned int i)
{
    return *(&sx+i);
}

inline bool
AcGeScale2d::operator == (const AcGeScale2d& s) const
{
    return this->isEqualTo(s);
}

// This operator is the logical negation of the `==' operator.
//
inline bool
AcGeScale2d::operator != (const AcGeScale2d& s) const
{
    return !this->isEqualTo(s);
}

#pragma pack (pop)
#endif
