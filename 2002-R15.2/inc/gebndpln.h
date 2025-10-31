#ifndef AC_GEBNDPLN_H
#define AC_GEBNDPLN_H
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
// This file contains the class AcGeBoundedPlane - A mathematical entity
// used to represent a 4-side bounded plane in 3-space.

#include "geplanar.h"
#include "geplane.h"
#pragma pack (push, 8)

class AcGePlane;
class AcGeVector3d;
class AcGePoint3d;
class AcGePoint2d;
class AcGeLineSeg3d;

class
GE_DLLEXPIMPORT
AcGeBoundedPlane : public AcGePlanarEnt
{
public:
    AcGeBoundedPlane();
    AcGeBoundedPlane(const AcGeBoundedPlane& plane);
    AcGeBoundedPlane(const AcGePoint3d& origin, const AcGeVector3d& uVec,
                     const AcGeVector3d& vVec);
    AcGeBoundedPlane(const AcGePoint3d& p1, const AcGePoint3d& origin,
                     const AcGePoint3d& p2);

    // Intersection.
    //
    Adesk::Boolean    intersectWith (const AcGeLinearEnt3d& linEnt, AcGePoint3d& point,
                                     const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean    intersectWith (const AcGePlane& plane, AcGeLineSeg3d& results,
                                     const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean    intersectWith (const AcGeBoundedPlane& plane, AcGeLineSeg3d& result,
                                     const AcGeTol& tol = AcGeContext::gTol) const;

    // Set methods.
    //
    AcGeBoundedPlane& set           (const AcGePoint3d& origin,
                                     const AcGeVector3d& uVec,
                                     const AcGeVector3d& vVec);
    AcGeBoundedPlane& set           (const AcGePoint3d& p1,
                                     const AcGePoint3d& origin,
                                     const AcGePoint3d& p2);
    // Assignment operator.
    //
    AcGeBoundedPlane& operator =    (const AcGeBoundedPlane& bplane);
};

#pragma pack (pop)
#endif
