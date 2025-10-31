#ifndef AC_GEINTRVL_H
#define AC_GEINTRVL_H
//
// (C) Copyright 1993-1999 by Autodesk, Inc.
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
// This file contains the class AcGeInterval - a representation
// for an interval on the real line.  The following kinds of intervals
// are supported.
// . Open intervals where the bounds are not finite.
// . Closed intervals with finite bounds.
// . Half intervals such that one end is open and not finite,
//   and the other is closed and finite.
//
// Where applicable, all evaluations are performed within the
// tolerance stored within this class.

#include "gegbl.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGeInterval
{
public:
    AcGeInterval(double tol = 1.e-12);
    AcGeInterval(const AcGeInterval& src);
    AcGeInterval(double lower, double upper, double tol = 1.e-12);
    AcGeInterval(Adesk::Boolean boundedBelow, double bound,
                 double tol = 1.e-12);
    ~AcGeInterval();

    // Assignment operator.
    //
    AcGeInterval&  operator =       (const AcGeInterval& otherInterval);

    // Get/set methods.
    //
    double         lowerBound       () const;
    double         upperBound       () const;
    double         element          () const;
    void           getBounds        (double& lower, double& upper) const;
    double         length           () const;
    double         tolerance        () const;

    AcGeInterval&  set              (double lower, double upper);
    AcGeInterval&  set              (Adesk::Boolean boundedBelow, double bound);
    AcGeInterval&  set              ();
    AcGeInterval&  setUpper         (double upper);
    AcGeInterval&  setLower         (double lower);
    AcGeInterval&  setTolerance     (double tol);

    // Interval editing.
    //
    void           getMerge         (const AcGeInterval& otherInterval, AcGeInterval& result) const;
    int            subtract         (const AcGeInterval& otherInterval,
                                     AcGeInterval& lInterval,
                                     AcGeInterval& rInterval) const;
    Adesk::Boolean intersectWith    (const AcGeInterval& otherInterval, AcGeInterval& result) const;

    // Interval characterization.
    //
    Adesk::Boolean isBounded        () const;
    Adesk::Boolean isBoundedAbove   () const;
    Adesk::Boolean isBoundedBelow   () const;
    Adesk::Boolean isUnBounded      () const;
    Adesk::Boolean isSingleton      () const;

    // Relation to other intervals.
    //
    Adesk::Boolean isDisjoint       (const AcGeInterval& otherInterval) const;
    Adesk::Boolean contains         (const AcGeInterval& otherInterval) const;
    Adesk::Boolean contains         (double val) const;

    // Continuity
    //
    Adesk::Boolean isContinuousAtUpper (const AcGeInterval& otherInterval) const;
    Adesk::Boolean isOverlapAtUpper    (const AcGeInterval& otherInterval,
                                        AcGeInterval& overlap) const;
    // Equality
    //
    Adesk::Boolean operator ==      (const AcGeInterval& otherInterval) const;
    Adesk::Boolean operator !=      (const AcGeInterval& otherInterval) const;
    Adesk::Boolean isEqualAtUpper   (const AcGeInterval& otherInterval) const;
    Adesk::Boolean isEqualAtUpper   (double value) const;
    Adesk::Boolean isEqualAtLower   (const AcGeInterval& otherInterval) const;
    Adesk::Boolean isEqualAtLower   (double value) const;

    // To be used with periodic curves
    //
    Adesk::Boolean isPeriodicallyOn (double period, double& val);

    // Comparisons.
    //
    friend
    GE_DLLEXPIMPORT
    Adesk::Boolean operator >       (double val, const AcGeInterval& intrvl);
    Adesk::Boolean operator >       (double val) const;
    Adesk::Boolean operator >       (const AcGeInterval& otherInterval) const;
    friend
    GE_DLLEXPIMPORT
    Adesk::Boolean operator >=      (double val, const AcGeInterval& intrvl);
    Adesk::Boolean operator >=      (double val) const;
    Adesk::Boolean operator >=      (const AcGeInterval& otherInterval) const;
    friend
    GE_DLLEXPIMPORT
    Adesk::Boolean operator <       (double val, const AcGeInterval& intrvl);
    Adesk::Boolean operator <       (double val) const;
    Adesk::Boolean operator <       (const AcGeInterval& otherInterval) const;
    friend
    GE_DLLEXPIMPORT
    Adesk::Boolean operator <=      (double val, const AcGeInterval& intrvl);
    Adesk::Boolean operator <=      (double val) const;
    Adesk::Boolean operator <=      (const AcGeInterval& otherInterval) const;

protected:
    friend class AcGeImpInterval;

    AcGeImpInterval  *mpImpInt;

    // Construct object from its corresponding implementation object.
    AcGeInterval (AcGeImpInterval&, int);

private:
    int              mDelInt;
};

#pragma pack (pop)
#endif
