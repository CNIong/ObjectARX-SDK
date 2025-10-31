#ifndef AC_GEAPLN3D_H
#define AC_GEAPLN3D_H
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
// This file contains the class AcGeAugPolyline3d - A mathematical entity
// used to represent a different types of spline curves in 3-space.

#include "gecurv3d.h"
#include "gekvec.h"
#include "gept3dar.h"
#include "gevc3dar.h"
#include "gevec3d.h"
#include "gepnt3d.h"
#include "geplin3d.h"

#pragma pack (push, 8)

class 
GE_DLLEXPIMPORT
AcGeAugPolyline3d : public AcGePolyline3d
{
public:
    AcGeAugPolyline3d();
    AcGeAugPolyline3d(const AcGeAugPolyline3d& apline);
    AcGeAugPolyline3d(const AcGeKnotVector& knots,
                      const AcGePoint3dArray& cntrlPnts,
                      const AcGeVector3dArray& vecBundle);
    AcGeAugPolyline3d(const AcGePoint3dArray& cntrlPnts,
                      const AcGeVector3dArray& vecBundle);

    // Approximation constructor
    //
    AcGeAugPolyline3d(const AcGeCurve3d& curve,
                      double fromParam, double toParam, 
		              double apprEps);

    // Assignment operator.
    //
    AcGeAugPolyline3d& operator = (const AcGeAugPolyline3d& apline);

    // Points
    //
    AcGePoint3d           getPoint(int idx) const;
    AcGeAugPolyline3d&    setPoint(int idx, AcGePoint3d pnt);
    void                  getPoints(AcGePoint3dArray& pnts) const;

    // Tangent bundle 
    //
    AcGeVector3d          getVector(int idx) const;
    AcGeAugPolyline3d&    setVector(int idx, AcGeVector3d pnt);
    void                  getD1Vectors(AcGeVector3dArray& tangents) const;

    // D2 Tangent bundle 
    //
    AcGeVector3d          getD2Vector(int idx) const;
    AcGeAugPolyline3d&    setD2Vector(int idx, AcGeVector3d pnt);
    void                  getD2Vectors(AcGeVector3dArray& d2Vectors) const;

	// Approximation tolerance
	//
	double                approxTol      () const;
    AcGeAugPolyline3d&    setApproxTol   (double approxTol);

};

#pragma pack (pop)
#endif
