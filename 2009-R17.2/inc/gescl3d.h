//
#ifndef AC_GESCL3D_H
#define AC_GESCL3D_H
//
// (C) Copyright 1993-2007 by Autodesk, Inc.
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
// This file contains the class AcGeScale3d - a mathematical entity used to
// represents scaling transformations in 3-space.
// Contract:  The scale vector components must never be set to zero
// (or near zero within floating point tolerances).

#include "adesk.h"
#include "gegbl.h"
#pragma pack (push, 8)

class AcGeMatrix3d;

class 
GE_DLLEXPIMPORT
AcGeScale3d
{
public:
    AcGeScale3d();
    AcGeScale3d(const AcGeScale3d& src);
    AcGeScale3d(double factor);
    AcGeScale3d(double xFact, double yFact, double zFact);

    // The identity scaling operation.
    //
    static const   AcGeScale3d kIdentity;

    // Multiplication.
    //
    AcGeScale3d    operator *  (const AcGeScale3d& sclVec) const;
    AcGeScale3d&   operator *= (const AcGeScale3d& scl);
    AcGeScale3d&   preMultBy   (const AcGeScale3d& leftSide);
    AcGeScale3d&   postMultBy  (const AcGeScale3d& rightSide);
    AcGeScale3d&   setToProduct(const AcGeScale3d& sclVec1, const AcGeScale3d& sclVec2);
    AcGeScale3d    operator *  (double s) const;
    AcGeScale3d&   operator *= (double s);
    AcGeScale3d&   setToProduct(const AcGeScale3d& sclVec, double s);
    friend
GE_DLLEXPIMPORT
    AcGeScale3d    operator *  (double, const AcGeScale3d& scl);

    // Multiplicative inverse.
    //
    AcGeScale3d    inverse        () const;
    AcGeScale3d&   invert         ();

    Adesk::Boolean isProportional(const AcGeTol& tol = AcGeContext::gTol) const;

    // Tests for equivalence using the infinity norm.
    //
    bool operator == (const AcGeScale3d& sclVec) const;
    bool operator != (const AcGeScale3d& sclVec) const;
    bool isEqualTo   (const AcGeScale3d& scaleVec,
                      const AcGeTol& tol = AcGeContext::gTol) const;

    // For convenient access to the data.
    //
    double         operator [] (unsigned int i) const;
    double&        operator [] (unsigned int i);
    AcGeScale3d&   set         (double sc0, double sc1, double sc2);

    // Conversion to/from matrix form.
    //
    operator       AcGeMatrix3d   () const;
    void getMatrix(AcGeMatrix3d& mat) const;
    AcGeScale3d&   extractScale   ( const AcGeMatrix3d& mat );
    AcGeScale3d&   removeScale    ( AcGeMatrix3d& mat );

    // The scale components in x, y and z.
    //
    double         sx, sy, sz;
};

__forceinline bool
AcGeScale3d::operator == (const AcGeScale3d& s) const
{
    return this->isEqualTo(s);
}

// This operator is the logical negation of the `==' operator.
//
__forceinline bool
AcGeScale3d::operator != (const AcGeScale3d& s) const
{
    return !(this->isEqualTo(s));
}

// Indexes the scale vector as if it were an array.  `sx' is index `0',
// `sy' is index `1' and `sz' is index `2'.
//
__forceinline double
AcGeScale3d::operator [] (unsigned int i) const
{
    return *(&sx+i);
}

__forceinline double&
AcGeScale3d::operator [] (unsigned int i)
{
    return *(&sx+i);
}

#pragma pack (pop)
#endif
