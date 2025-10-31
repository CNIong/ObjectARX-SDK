#ifndef AC_GESPNT3D_H
#define AC_GESPNT3D_H
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
// This file contains the class AcGeSplineEnt3d - A mathematical entity
// used to represent a different types of spline curves in 3-space.

#include "gecurv3d.h"
#include "gekvec.h"
#include "gept3dar.h"
#include "gevec3d.h"
#include "gepnt3d.h"
#include "gept3dar.h"
#pragma pack (push, 8)

class AcGeKnotVector;

class
GE_DLLEXPIMPORT
AcGeSplineEnt3d : public AcGeCurve3d
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
                                             AcGeContext::gTol ) const;

    double            startParam            () const;
    double            endParam              () const;
    AcGePoint3d       startPoint            () const;
    AcGePoint3d       endPoint              () const;

    // Interpolation data
    //
    Adesk::Boolean    hasFitData            () const;

    // Editting
    //
    double            knotAt                (int idx) const;
    AcGeSplineEnt3d&  setKnotAt             (int idx, double val);

    AcGePoint3d       controlPointAt        (int idx) const;
    AcGeSplineEnt3d&  setControlPointAt     (int idx, const AcGePoint3d& pnt);


    // Assignment operator.
    //
    AcGeSplineEnt3d&  operator =            (const AcGeSplineEnt3d& spline);

protected:
    AcGeSplineEnt3d ();
    AcGeSplineEnt3d (const AcGeSplineEnt3d&);
};

#pragma pack (pop)
#endif

