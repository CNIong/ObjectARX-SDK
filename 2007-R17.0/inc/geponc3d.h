#ifndef AC_GEPONC3D_H
#define AC_GEPONC3D_H
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
// The class AcGePointOnCurve3d which is used to keep information of
// a point belonging to a 3d curve

#include "gepent3d.h"
#pragma pack (push, 8)

class AcGeCurve3d;

class
GE_DLLEXPIMPORT
AcGePointOnCurve3d : public AcGePointEnt3d
{
public:
    AcGePointOnCurve3d();
    AcGePointOnCurve3d(const AcGeCurve3d& crv);
    AcGePointOnCurve3d(const AcGeCurve3d& crv, double param);
    AcGePointOnCurve3d(const AcGePointOnCurve3d& src);

    // Assignment operator.
    //
    AcGePointOnCurve3d& operator =     (const AcGePointOnCurve3d& src);

    // Query functions.
    //
    const AcGeCurve3d*  curve          () const;
    double              parameter      () const;

    // Functions to evaluate a point.
    //
    AcGePoint3d         point          () const;
    AcGePoint3d         point          (double param);
    AcGePoint3d         point          (const AcGeCurve3d& crv, double param);

    // Functions to evaluate the derivatives.
    //
    AcGeVector3d        deriv          (int order) const;
    AcGeVector3d        deriv          (int order, double param);
    AcGeVector3d        deriv          (int order, const AcGeCurve3d& crv,
                                        double param);
    // Singularity
    //
    Adesk::Boolean      isSingular     (const AcGeTol& tol =
	                                AcGeContext::gTol) const;
    Adesk::Boolean     	curvature      (double& res);
    Adesk::Boolean     	curvature      (double param, double& res);

    // Set functions.
    //
    AcGePointOnCurve3d& setCurve       (const AcGeCurve3d& crv);
    AcGePointOnCurve3d& setParameter   (double param);
};

#pragma pack (pop)
#endif

