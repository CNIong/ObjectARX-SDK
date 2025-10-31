#ifndef AC_GEPLANAR_H
#define AC_GEPLANAR_H
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
// This file contains the class AcGePlanarEnt. It is an abstract class
// representing an oriented plane in 3-space.

#include "gesurf.h"
#include "gevec3d.h"
#pragma pack (push, 8)

class AcGeLineSeg3d;
class AcGeLinearEnt3d;
class AcGeCircArc3d;

class
GE_DLLEXPIMPORT
AcGePlanarEnt : public AcGeSurface
{
public:
    // Intersection
    //
    Adesk::Boolean  intersectWith    (const AcGeLinearEnt3d& linEnt, AcGePoint3d& pnt,
                                      const AcGeTol& tol = AcGeContext::gTol) const;
    // Closest point
    //
    AcGePoint3d     closestPointToLinearEnt (const AcGeLinearEnt3d& line,
                                             AcGePoint3d& pointOnLine,
                                             const AcGeTol& tol
                                               = AcGeContext::gTol) const;
    AcGePoint3d     closestPointToPlanarEnt (const AcGePlanarEnt& otherPln,
                                             AcGePoint3d& pointOnOtherPln,
                                             const AcGeTol& tol
                                               = AcGeContext::gTol) const;
    // Direction tests.
    //
    Adesk::Boolean isParallelTo      (const AcGeLinearEnt3d& linEnt,
                                      const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean isParallelTo      (const AcGePlanarEnt& otherPlnEnt,
                                      const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean isPerpendicularTo (const AcGeLinearEnt3d& linEnt,
                                      const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean isPerpendicularTo (const AcGePlanarEnt& linEnt,
                                      const AcGeTol& tol = AcGeContext::gTol) const;

    // Point set equality.
    //
    Adesk::Boolean isCoplanarTo      (const AcGePlanarEnt& otherPlnEnt,
                                      const AcGeTol& tol = AcGeContext::gTol) const;

    // Get methods.
    //
    void              get            (AcGePoint3d&, AcGeVector3d& uVec,
                                      AcGeVector3d& vVec) const;
    void              get            (AcGePoint3d&, AcGePoint3d& origin,
                                      AcGePoint3d&) const;

    // Geometric properties.
    //
    AcGePoint3d    pointOnPlane      () const;
    AcGeVector3d   normal            () const;
    void           getCoefficients(double& a, double& b, double& c, double& d) const;
    void           getCoordSystem(AcGePoint3d& origin, AcGeVector3d& axis1,
                                  AcGeVector3d& axis2) const;
    // Assignment operator.
    //
    AcGePlanarEnt& operator =        (const AcGePlanarEnt& src);

protected:
    AcGePlanarEnt ();
    AcGePlanarEnt (const AcGePlanarEnt&);
};

#pragma pack (pop)
#endif
