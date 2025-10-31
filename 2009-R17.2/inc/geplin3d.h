#ifndef AC_GEPLIN3D_H
#define AC_GEPLIN3D_H
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
// This file contains the class AcGePolyline3d - A mathematical entity
// used to represent a different types of spline curves in 3-space.

#include "gecurv3d.h"
#include "gekvec.h"
#include "gept3dar.h"
#include "gevec3d.h"
#include "gepnt3d.h"
#include "gesent3d.h"
#pragma pack (push, 8)


class
GE_DLLEXPIMPORT
AcGePolyline3d : public AcGeSplineEnt3d
{
public:

    AcGePolyline3d();
    AcGePolyline3d( const AcGePolyline3d& src );
    AcGePolyline3d( const AcGePoint3dArray& points);
    AcGePolyline3d( const AcGeKnotVector& knots,
                    const AcGePoint3dArray& cntrlPnts );

    // Approximate curve with polyline
    //
    AcGePolyline3d( const AcGeCurve3d& crv, double apprEps );

    // Interpolation data
    //
    int              numFitPoints () const;
    AcGePoint3d      fitPointAt   (int idx) const;
    AcGeSplineEnt3d& setFitPointAt(int idx, const AcGePoint3d& point);

    // Assignment operator.
    //
    AcGePolyline3d& operator =     (const AcGePolyline3d& pline);
};

#pragma pack (pop)
#endif

