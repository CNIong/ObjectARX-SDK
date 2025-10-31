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
// This file contains the class AcGeMatrix2d - a matrix used to
// represent general purpose 2d transformations in homogeneous
// co-ordinate space.

#ifndef AC_GEMAT2D_H
#define AC_GEMAT2D_H

#include "gegbl.h"
#include "gepnt2d.h"
#pragma pack (push, 8)

class AcGeVector2d;
class AcGeLine2d;
class AcGeTol;

class 
GE_DLLEXPIMPORT
AcGeMatrix2d
{
public:
    AcGeMatrix2d();
    AcGeMatrix2d(const AcGeMatrix2d& src);

    // The multiplicative identity.
    //
    static const   AcGeMatrix2d   kIdentity;

    // Reset matrix.
    //
    AcGeMatrix2d&  setToIdentity();

    // Multiplication.
    //
    AcGeMatrix2d   operator *   (const AcGeMatrix2d& mat) const;
    AcGeMatrix2d&  operator *=  (const AcGeMatrix2d& mat);
    AcGeMatrix2d&  preMultBy    (const AcGeMatrix2d& leftSide);
    AcGeMatrix2d&  postMultBy   (const AcGeMatrix2d& rightSide);
    AcGeMatrix2d&  setToProduct (const AcGeMatrix2d& mat1, const AcGeMatrix2d& mat2);

    // Multiplicative inverse.
    //
    AcGeMatrix2d&  invert       ();
    AcGeMatrix2d   inverse      () const;

    // Test if it is a singular matrix. A singular matrix is not invertable.
    //
    Adesk::Boolean isSingular   (const AcGeTol& tol = AcGeContext::gTol) const;

    // Matrix transposition.
    //
    AcGeMatrix2d&  transposeIt  ();
    AcGeMatrix2d   transpose    () const;

    // Tests for equivalence using the infinity norm.
    //
    bool operator ==  (const AcGeMatrix2d& mat) const;
    bool operator !=  (const AcGeMatrix2d& mat) const;
    bool isEqualTo    (const AcGeMatrix2d& mat,
                       const AcGeTol& tol = AcGeContext::gTol) const;

    // Test scaling effects of matrix
    //
    Adesk::Boolean isUniScaledOrtho(const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean isScaledOrtho(const AcGeTol& tol = AcGeContext::gTol) const;
	double		   scale(void);

    // Determinant
    //
    double         det          () const;

    // Set/retrieve translation.
    //
    AcGeMatrix2d&  setTranslation(const AcGeVector2d& vec);
    AcGeVector2d   translation  () const;

    // Retrieve scaling, rotation, mirror components
    //
    Adesk::Boolean isConformal (double& scale, double& angle,
                                Adesk::Boolean& isMirror, AcGeVector2d& reflex) const;


    // Set/get coordinate system
    //
    AcGeMatrix2d&  setCoordSystem(const AcGePoint2d& origin,
                                 const AcGeVector2d& e0,
                                 const AcGeVector2d& e1);
    void           getCoordSystem(AcGePoint2d& origin,
                                 AcGeVector2d& e0,
                                 AcGeVector2d& e1) const;

    // Set the matrix to be a specified transformation
    //
    AcGeMatrix2d& setToTranslation(const AcGeVector2d& vec);
    AcGeMatrix2d& setToRotation (double angle,
                                 const AcGePoint2d& center
				 = AcGePoint2d::kOrigin);
    AcGeMatrix2d& setToScaling  (double scaleAll,
                                 const AcGePoint2d& center
				 = AcGePoint2d::kOrigin);
    AcGeMatrix2d& setToMirroring(const AcGePoint2d& pnt);
    AcGeMatrix2d& setToMirroring(const AcGeLine2d& line);
    AcGeMatrix2d& setToAlignCoordSys(const AcGePoint2d&  fromOrigin,
                                 const AcGeVector2d& fromE0,
                                 const AcGeVector2d& fromE1,
                                 const AcGePoint2d&  toOrigin,
                                 const AcGeVector2d& toE0,
                                 const AcGeVector2d& toE1);

    // Functions that make a 2d transformation matrix using various approaches
    //
    static
    AcGeMatrix2d translation    (const AcGeVector2d& vec);
    static
    AcGeMatrix2d rotation       (double angle, const AcGePoint2d& center
				 = AcGePoint2d::kOrigin);
    static
    AcGeMatrix2d scaling        (double scaleAll, const AcGePoint2d& center
				 = AcGePoint2d::kOrigin);
    static
    AcGeMatrix2d mirroring      (const AcGePoint2d& pnt);
    static
    AcGeMatrix2d mirroring      (const AcGeLine2d& line);
    static
    AcGeMatrix2d alignCoordSys  (const AcGePoint2d& fromOrigin,
                                 const AcGeVector2d& fromE0,
                                 const AcGeVector2d& fromE1,
                                 const AcGePoint2d&  toOrigin,
                                 const AcGeVector2d& toE0,
                                 const AcGeVector2d& toE1);

    // For convenient access to the data.
    //
    double         operator ()  (unsigned int, unsigned int) const;
    double&        operator ()  (unsigned int, unsigned int);

    // The components of the matrix.
    //
    double         entry[3][3]; // [row][column]
};

inline bool
AcGeMatrix2d::operator == (const AcGeMatrix2d& otherMatrix) const
{
    return this->isEqualTo(otherMatrix);
}

// This operator is the logical negation of the `==' operator.
//
inline bool
AcGeMatrix2d::operator != (const AcGeMatrix2d& otherMatrix) const
{
    return !this->isEqualTo(otherMatrix);
}

// Return a reference to the element in position [row][column]
// of the `entry' array.
//
inline double
AcGeMatrix2d::operator () (
    unsigned int row,
    unsigned int column) const
{
    return entry[row][column];
}

inline double&
AcGeMatrix2d::operator () (
    unsigned int row,
    unsigned int column)
{
    return entry[row][column];
}

#pragma pack (pop)
#endif
