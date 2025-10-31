#ifndef AC_GERAY3D_H
#define AC_GERAY3D_H
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
// This file contains the class AcGeRay3d - A mathematical entity
// used to represent a ray (half line) in 3-space.

#include "gelent3d.h"
#pragma pack (push, 8)

class AcGeRay2d;

class
GE_DLLEXPIMPORT
AcGeRay3d : public AcGeLinearEnt3d
{
public:
    AcGeRay3d();
    AcGeRay3d(const AcGeRay3d& line);
    AcGeRay3d(const AcGePoint3d& pnt, const AcGeVector3d& vec);
    AcGeRay3d(const AcGePoint3d& pnt1, const AcGePoint3d& pnt2);

    // Set methods.
    //
    AcGeRay3d&     set         (const AcGePoint3d& pnt, const AcGeVector3d& vec);
    AcGeRay3d&     set         (const AcGePoint3d& pnt1, const AcGePoint3d& pnt2);

    // Assignment operator.
    //
    AcGeRay3d&     operator =  (const AcGeRay3d& line);
};

#pragma pack (pop)
#endif
