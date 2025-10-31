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
// DESCRIPTION:
//
// This file contains the class AcGePlane - A mathematical entity
// used to represent a plane in 3-space.

#ifndef AC_GEPLANE_H
#define AC_GEPLANE_H

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
    AcGePlane(const AcGePoint3d& pntU, const AcGePoint3d& org, const AcGePoint3d& pntV);
    AcGePlane(const AcGePoint3d& org, const AcGeVector3d& uAxis,
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
    AcGePlane&     set              (const AcGePoint3d& pntU, const AcGePoint3d& org,
                                     const AcGePoint3d& pntV);
    AcGePlane&     set              (double a, double b, double c, double d);
    AcGePlane&     set              (const AcGePoint3d& org,
                                     const AcGeVector3d& uAxis,
                                     const AcGeVector3d& vAxis);
    // Assignment operator.
    //
    AcGePlane&     operator =       (const AcGePlane& src);
};

#pragma pack (pop)
#endif
