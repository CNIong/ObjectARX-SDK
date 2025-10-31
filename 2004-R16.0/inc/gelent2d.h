#ifndef AC_GELENT2D_H
#define AC_GELENT2D_H
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
// This file contains the class AcGeLinearEnt2d - A mathematical entity
// used to represent a line in 2-space.

#include "gecurv2d.h"
#include "gepnt2d.h"
#include "gevec2d.h"
#pragma pack (push, 8)

class AcGeCircArc2d;

class
GE_DLLEXPIMPORT
AcGeLinearEnt2d : public AcGeCurve2d
{
public:
    // Intersection with other geometric objects.
    //
    Adesk::Boolean   intersectWith  (const AcGeLinearEnt2d& line, AcGePoint2d& intPnt,
                                     const AcGeTol& tol = AcGeContext::gTol) const;

    // Find the overlap with other AcGeLinearEnt object
    //
    Adesk::Boolean   overlap        (const AcGeLinearEnt2d& line,
                                     AcGeLinearEnt2d*& overlap,
                                     const AcGeTol& tol = AcGeContext::gTol) const;
    // Direction tests.
    //
    Adesk::Boolean   isParallelTo   (const AcGeLinearEnt2d& line,
                                     const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean   isPerpendicularTo(const AcGeLinearEnt2d& line,
                                      const AcGeTol& tol = AcGeContext::gTol) const;
    // Test if two lines are colinear.
    //
    Adesk::Boolean   isColinearTo   (const AcGeLinearEnt2d& line,
                                     const AcGeTol& tol = AcGeContext::gTol) const;
    // Perpendicular through a given point
    //
    void             getPerpLine    (const AcGePoint2d& pnt, AcGeLine2d& perpLine) const;

    // Definition of line.
    //
    AcGePoint2d      pointOnLine    () const;
    AcGeVector2d     direction      () const;
    void             getLine        (AcGeLine2d& line) const;

    // Assignment operator.
    //
    AcGeLinearEnt2d& operator =     (const AcGeLinearEnt2d& line);

protected:
    AcGeLinearEnt2d ();
    AcGeLinearEnt2d (const AcGeLinearEnt2d&);
};

#pragma pack (pop)
#endif
