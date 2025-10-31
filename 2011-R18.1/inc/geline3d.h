#ifndef AC_GELINE3D_H
#define AC_GELINE3D_H
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
// This file contains the class AcGeLinearEnt3d - A mathematical entity
// used to represent a line in 3-space.

#include "gelent3d.h"
#pragma pack (push, 8)

class AcGeLine2d;

class
GE_DLLEXPIMPORT
AcGeLine3d : public AcGeLinearEnt3d
{
public:
    AcGeLine3d();
    AcGeLine3d(const AcGeLine3d& line);
    AcGeLine3d(const AcGePoint3d& pnt, const AcGeVector3d& vec);
    AcGeLine3d(const AcGePoint3d& pnt1, const AcGePoint3d& pnt2);

    // The x-axis, y-axis, and z-axis lines.
    //
    static const AcGeLine3d kXAxis;
    static const AcGeLine3d kYAxis;
    static const AcGeLine3d kZAxis;

    // Set methods.
    //
    AcGeLine3d& set(const AcGePoint3d& pnt, const AcGeVector3d& vec);
    AcGeLine3d& set(const AcGePoint3d& pnt1, const AcGePoint3d& pnt2);

    // Assignment operator.
    //
    AcGeLine3d& operator = (const AcGeLine3d& line);
};

#pragma pack (pop)
#endif
