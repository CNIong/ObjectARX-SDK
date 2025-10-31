#ifndef AC_GEPLIN2D_H
#define AC_GEPLIN2D_H
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
// This file contains the class AcGePolyline2d - A mathematical entity
// used to represent a different types of spline curves in 3-space.

#include "gecurv2d.h"
#include "gekvec.h"
#include "gept2dar.h"
#include "gevec2d.h"
#include "gepnt2d.h"
#include "gesent2d.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGePolyline2d : public AcGeSplineEnt2d
{
public:
    AcGePolyline2d();
    AcGePolyline2d(const AcGePolyline2d& src);
    AcGePolyline2d(const AcGePoint2dArray&);
    AcGePolyline2d(const AcGeKnotVector& knots,
                   const AcGePoint2dArray& points);

    // Approximate curve with polyline
    //
    AcGePolyline2d(const AcGeCurve2d& crv, double apprEps);

    // Interpolation data
    //
    int              numFitPoints () const;
    AcGePoint2d      fitPointAt   (int idx) const;
    AcGeSplineEnt2d& setFitPointAt(int idx, const AcGePoint2d& point);

    // Assignment operator.
    //
    AcGePolyline2d& operator =     (const AcGePolyline2d& pline);
};

#pragma pack (pop)
#endif
