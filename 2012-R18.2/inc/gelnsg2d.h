#ifndef AC_GELNSG2D_H
#define AC_GELNSG2D_H
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
// This file contains the class AcGeLinSeg2d - A mathematical entity
// used to represent a 2d line segment

#include "geline2d.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGeLineSeg2d : public AcGeLinearEnt2d
{
public:
    AcGeLineSeg2d();
    AcGeLineSeg2d(const AcGeLineSeg2d& line);
    AcGeLineSeg2d(const AcGePoint2d& pnt1, const AcGePoint2d& pnt2);
    AcGeLineSeg2d(const AcGePoint2d& pnt, const AcGeVector2d& vec);

    // Set methods.
    //
    AcGeLineSeg2d& set(const AcGePoint2d& pnt, const AcGeVector2d& vec);
    AcGeLineSeg2d& set(const AcGePoint2d& pnt1, const AcGePoint2d& pnt2);
    AcGeLineSeg2d& set(const AcGeCurve2d& curve1,
                       const AcGeCurve2d& curve2,
                       double& param1, double& param2,
                       Adesk::Boolean& success);
    AcGeLineSeg2d& set(const AcGeCurve2d& curve, const AcGePoint2d& point,
                       double& param, Adesk::Boolean& success);


    // Bisector.
    //
    void           getBisector(AcGeLine2d& line) const;

    // Barycentric combination of end points.
    //
    AcGePoint2d    baryComb   (double blendCoeff) const;

    // Definition of linear segment
    //
    AcGePoint2d    startPoint   () const;
    AcGePoint2d    midPoint     () const;
    AcGePoint2d    endPoint     () const;
    double         length       () const;
    double         length       (double fromParam, double toParam,
                                 double tol = AcGeContext::gTol.equalPoint())
                                const;
    // Assignment operator.
    //
    AcGeLineSeg2d& operator =  (const AcGeLineSeg2d& line);
};

#pragma pack (pop)
#endif
