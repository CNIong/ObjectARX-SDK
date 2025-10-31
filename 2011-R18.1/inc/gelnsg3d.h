#ifndef AC_GELNSG3D_H
#define AC_GELNSG3D_H
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
// This file contains the class AcGeLineSeg3d - A mathematical entity
// used to represent linear segment in 3d space.

#include "geline3d.h"
#include "geplane.h"
#pragma pack (push, 8)

class AcGeLineSeg2d;

class 
GE_DLLEXPIMPORT
AcGeLineSeg3d : public AcGeLinearEnt3d
{
public:
    AcGeLineSeg3d();
    AcGeLineSeg3d(const AcGeLineSeg3d& line);
    AcGeLineSeg3d(const AcGePoint3d& pnt, const AcGeVector3d& vec);
    AcGeLineSeg3d(const AcGePoint3d& pnt1, const AcGePoint3d& pnt2);

    // Bisector.
    //
    void           getBisector  (AcGePlane& plane) const;

    // Barycentric combination of end points.
    //
    AcGePoint3d    baryComb     (double blendCoeff) const;

    // Definition of linear segment
    //
    AcGePoint3d    startPoint   () const;
    AcGePoint3d    midPoint     () const;
    AcGePoint3d    endPoint     () const;
    double         length       () const;
    double         length       (double fromParam, double toParam,
                                 double tol = AcGeContext::gTol.equalPoint()) const;
    // Set methods.
    //
    AcGeLineSeg3d& set          (const AcGePoint3d& pnt, const AcGeVector3d& vec);
    AcGeLineSeg3d& set          (const AcGePoint3d& pnt1, const AcGePoint3d& pnt2);
   	AcGeLineSeg3d& set          (const AcGeCurve3d& curve1,
                                 const AcGeCurve3d& curve2,
                                 double& param1, double& param2,
                                 Adesk::Boolean& success);
  	AcGeLineSeg3d& set          (const AcGeCurve3d& curve,
                                 const AcGePoint3d& point, double& param,
                                 Adesk::Boolean& success);


    // Assignment operator.
    //
    AcGeLineSeg3d& operator =   (const AcGeLineSeg3d& line);
};

#pragma pack (pop)
#endif
