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
//
// DESCRIPTION:
//
// This file contains the class AcGeKnotVector - a dynamic array used
// to represent the knot sequence of a spline.  Refer to
// AcGeDoubleArray for details concerning the dynamic array
// behavior.

#ifndef AC_GEKVEC_H
#define AC_GEKVEC_H

#include "gegbl.h"
#include "gedblar.h"
#pragma pack (push, 8)

class AcGeInterval;

class
GE_DLLEXPIMPORT
AcGeKnotVector
{
public:
    // By default it is 1.0e-9. It could be changed by API user.
    static double globalKnotTolerance;
    AcGeKnotVector(double eps = globalKnotTolerance);
    AcGeKnotVector(int size, int growSize, double eps = globalKnotTolerance);
    AcGeKnotVector(int size, const double [], double eps = globalKnotTolerance);
	// Elevates multiplicity of each DISTINCT knot by plusMult;
	// Contract: plusMul >= 0;
    AcGeKnotVector(int plusMult, const AcGeKnotVector& src);
    AcGeKnotVector(const AcGeKnotVector& src);
    AcGeKnotVector(const AcGeDoubleArray& src, double eps = globalKnotTolerance);

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
    int                 multiplicityAt     (double param) const;
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

    AcGeKnotVector&     set (int size, const double [], double eps = globalKnotTolerance);

protected:
    AcGeDoubleArray    mData;
    double             mTolerance;

    Adesk::Boolean     isValid (int) const;
};

// Inline methods.
//
inline double
AcGeKnotVector::tolerance() const
{ return mTolerance;}

inline AcGeKnotVector&
AcGeKnotVector::setTolerance(double eps)
{ mTolerance = eps;	return *this;}

inline Adesk::Boolean
AcGeKnotVector::isValid(int i) const
{ return i >= 0 && i < mData.logicalLength(); }

inline double&
AcGeKnotVector::operator [] (int i)
{ assert(isValid(i)); return mData[i]; }

inline const double
AcGeKnotVector::operator [] (int i) const
{ assert(isValid(i)); return mData[i]; }

inline const double*
AcGeKnotVector::asArrayPtr() const
{ return mData.asArrayPtr(); }

inline double*
AcGeKnotVector::asArrayPtr()
{ return mData.asArrayPtr(); }

#pragma pack (pop)
#endif
