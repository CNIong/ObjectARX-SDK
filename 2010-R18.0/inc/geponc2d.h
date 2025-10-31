#ifndef AC_GEPONC2D_H
#define AC_GEPONC2D_H
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
// This file contains:
// The AcGePointOnCurve2d class which is used to keep information of a point
// belonging to a 2d curve

#include "gepent2d.h"
#pragma pack (push, 8)

class AcGeCurve2d;

class
GE_DLLEXPIMPORT
AcGePointOnCurve2d : public AcGePointEnt2d
{
public:
    AcGePointOnCurve2d  ();
    AcGePointOnCurve2d  (const AcGeCurve2d& crv);
    AcGePointOnCurve2d  (const AcGeCurve2d& crv, double param);
    AcGePointOnCurve2d  (const AcGePointOnCurve2d& src);

    // Assignment operator.
    //
    AcGePointOnCurve2d& operator =     (const AcGePointOnCurve2d& src);

    // Query functions.
    //
    const AcGeCurve2d*  curve          () const;
    double              parameter      () const;

    // Functions to evaluate a point.
    //
    AcGePoint2d         point          () const;
    AcGePoint2d         point          (double param);
    AcGePoint2d         point          (const AcGeCurve2d& crv, double param);

    // Functions to evaluate the derivatives.
    //
    AcGeVector2d        deriv          (int order) const;
    AcGeVector2d        deriv          (int order, double param);
    AcGeVector2d        deriv          (int order, const AcGeCurve2d& crv,
                                        double param);
    // Singularity
    //
    Adesk::Boolean      isSingular     (const AcGeTol&  tol =
                                        AcGeContext::gTol) const;
    Adesk::Boolean      curvature      (double& res);
    Adesk::Boolean      curvature      (double param, double& res);
    // Set functions.
    //
    AcGePointOnCurve2d& setCurve       (const AcGeCurve2d& crv);
    AcGePointOnCurve2d& setParameter   (double param);
};

#pragma pack (pop)
#endif

