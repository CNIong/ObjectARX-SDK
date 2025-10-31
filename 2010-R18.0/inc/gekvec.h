#ifndef AC_GEKVEC_H
#define AC_GEKVEC_H
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
//
// DESCRIPTION:
//
// This file contains the class AcGeKnotVector - a dynamic array used
// to represent the knot sequence of a spline.  Refer to
// AcGeDoubleArray for details concerning the dynamic array
// behavior.

#include "gegbl.h"
#include "gedblar.h"
#pragma pack (push, 8)

class AcGeInterval;

class
GE_DLLEXPIMPORT
AcGeKnotVector
{
public:
    AcGeKnotVector(double eps = 1.e-9);
    AcGeKnotVector(int size, int growSize, double eps = 1.e-9);
    AcGeKnotVector(int size, const double [], double eps = 1.e-9);
	// Elevates multiplicity of each DISTINCT knot by plusMult;
	// Contract: plusMul >= 0;
    AcGeKnotVector(int plusMult, const AcGeKnotVector& src);
    AcGeKnotVector(const AcGeKnotVector& src);
    AcGeKnotVector(const AcGeDoubleArray& src, double eps = 1.e-9);

    ~AcGeKnotVector();

    // Copy operator.
    //
    AcGeKnotVector&     operator =  (const AcGeKnotVector& src);
    AcGeKnotVector&     operator =  (const AcGeDoubleArray& src);


    // Indexing into the knot vector.
    //
    double&             operator [] (int);
    const double        operator [] (int) const;

    // Equality test
    //
    Adesk::Boolean      isEqualTo (const AcGeKnotVector& other) const;

    // Inquiry functions
    //
    double              startParam         () const;
    double              endParam           () const;
    int                 multiplicityAt     (int i) const;
    int                 numIntervals       () const;

    // Evaluate funtions
    //
    int                 getInterval        (int ord, double par,
                                            AcGeInterval& interval ) const;
    void                getDistinctKnots   (AcGeDoubleArray& knots) const;
    Adesk::Boolean      contains           (double param) const;
    Adesk::Boolean      isOn               (double knot) const;

    // Edit function
    //
    AcGeKnotVector&     reverse            ();
    AcGeKnotVector&     removeAt           (int);
    AcGeKnotVector&     removeSubVector    (int startIndex, int endIndex);

    AcGeKnotVector&     insertAt           (int indx, double u,
                                            int multiplicity = 1);
    AcGeKnotVector&     insert             (double u);
    int                 append             (double val);
    AcGeKnotVector&     append             (AcGeKnotVector& tail,
                                            double knotRatio = 0.);
    int                 split              (double par,
                                            AcGeKnotVector* pKnot1,
                                            int multLast,
                                            AcGeKnotVector* pKnot2,
                                            int multFirst ) const;


    AcGeKnotVector&     setRange           (double lower, double upper);

    double              tolerance          () const;
    AcGeKnotVector&     setTolerance       (double tol);

    // Array length.
    //
    int                 length             () const; // Logical length.
    Adesk::Boolean      isEmpty            () const;
    int                 logicalLength      () const;
    AcGeKnotVector&     setLogicalLength   (int);
    int                 physicalLength     () const;
    AcGeKnotVector&     setPhysicalLength  (int);

    // Automatic resizing.
    //
    int                 growLength  () const;
    AcGeKnotVector&     setGrowLength(int);

    // Treat as simple array of double.
    //
    const double*       asArrayPtr  () const;
    double*             asArrayPtr  ();

    AcGeKnotVector&     set (int size, const double [], double eps = 1.e-9);

protected:
    AcGeDoubleArray    mData;
    double             mTolerance;

    Adesk::Boolean     isValid (int) const;
};

// Inline methods.
//
__forceinline double
AcGeKnotVector::tolerance() const
{ return mTolerance;}

__forceinline AcGeKnotVector&
AcGeKnotVector::setTolerance(double eps)
{ mTolerance = eps;	return *this;}

__forceinline Adesk::Boolean
AcGeKnotVector::isValid(int i) const
{ return i >= 0 && i < mData.logicalLength(); }

__forceinline double&
AcGeKnotVector::operator [] (int i)
{ assert(isValid(i)); return mData[i]; }

__forceinline const double
AcGeKnotVector::operator [] (int i) const
{ assert(isValid(i)); return mData[i]; }

__forceinline const double*
AcGeKnotVector::asArrayPtr() const
{ return mData.asArrayPtr(); }

__forceinline double*
AcGeKnotVector::asArrayPtr()
{ return mData.asArrayPtr(); }

#pragma pack (pop)
#endif
