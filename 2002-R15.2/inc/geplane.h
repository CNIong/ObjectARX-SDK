#ifndef AC_GEPLANE_H
#define AC_GEPLANE_H
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
// This file contains the class AcGePlane - A mathematical entity
// used to represent a plane in 3-space.

#include "geplanar.h"
#pragma pack (push, 8)

class AcGeBoundedPlane;
class AcGeLine3d;

class
GE_DLLEXPIMPORT
AcGePlane : public AcGePlanarEnt
{
public:
    // Global plane objects.
    //
    static const AcGePlane kXYPlane;
    static const AcGePlane kYZPlane;
    static const AcGePlane kZXPlane;

    AcGePlane();
    AcGePlane(const AcGePlane& src);
    AcGePlane(const AcGePoint3d& origin, const AcGeVector3d& normal);
    AcGePlane(const AcGePoint3d& pntU, const AcGePoint3d& or, const AcGePoint3d& pntV);
    AcGePlane(const AcGePoint3d& or, const AcGeVector3d& uAxis,
              const AcGeVector3d& vAxis);
    AcGePlane(double a, double b, double c, double d);

    // Signed distance from a point to a plane.
    //
    double         signedDistanceTo (const AcGePoint3d& pnt) const;

    // Intersection
    //
    Adesk::Boolean intersectWith    (const AcGeLinearEnt3d& linEnt, AcGePoint3d& resultPnt,
                                     const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean intersectWith    (const AcGePlane& otherPln, AcGeLine3d& resultLine,
                                     const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean intersectWith    (const AcGeBoundedPlane& bndPln, AcGeLineSeg3d& resultLineSeg,
                                     const AcGeTol& tol = AcGeContext::gTol) const;

    // Geometry redefinition.
    //
    AcGePlane&     set              (const AcGePoint3d& pnt, const AcGeVector3d& normal);
    AcGePlane&     set              (const AcGePoint3d& pntU, const AcGePoint3d& or,
                                     const AcGePoint3d& pntV);
    AcGePlane&     set              (double a, double b, double c, double d);
    AcGePlane&     set              (const AcGePoint3d& or,
                                     const AcGeVector3d& uAxis,
                                     const AcGeVector3d& vAxis);
    // Assignment operator.
    //
    AcGePlane&     operator =       (const AcGePlane& src);
};

#pragma pack (pop)
#endif
