#ifndef AC_GESPNT2d_H
#define AC_GESPNT2d_H
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
// This file contains the class AcGeSplineEnt2d - A mathematical entity
// used to represent a different types of spline curves in 3-space.

#include "gecurv2d.h"
#include "gekvec.h"
#include "gept2dar.h"
#include "gevec2d.h"
#include "gepnt2d.h"
#include "gept2dar.h"
#pragma pack (push, 8)

class AcGeKnotVector;

class 
GE_DLLEXPIMPORT
AcGeSplineEnt2d : public AcGeCurve2d
{
public:

    // Definition of spline
    //
    Adesk::Boolean    isRational            () const;
    int               degree                () const;
    int               order                 () const;
    int               numKnots              () const;
    const
    AcGeKnotVector&   knots                 () const;
    int               numControlPoints      () const;
    int               continuityAtKnot      (int idx, const AcGeTol& tol =
                                             AcGeContext::gTol) const;

    double            startParam            () const;
    double            endParam              () const;
    AcGePoint2d       startPoint            () const;
    AcGePoint2d       endPoint              () const;

    // Interpolation data
    //
    Adesk::Boolean    hasFitData            () const;

    // Editting
    //
    double            knotAt                (int idx) const;
    AcGeSplineEnt2d&  setKnotAt             (int idx, double val);

    AcGePoint2d       controlPointAt        (int idx) const;
    AcGeSplineEnt2d&  setControlPointAt     (int idx, const AcGePoint2d& pnt);

    // Assignment operator.
    //
    AcGeSplineEnt2d&  operator =            (const AcGeSplineEnt2d& spline);

protected:
    AcGeSplineEnt2d ();
    AcGeSplineEnt2d (const AcGeSplineEnt2d&);
};

#pragma pack (pop)
#endif

