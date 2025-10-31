#ifndef AC_GEPOS3D_H
#define AC_GEPOS3D_H
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
// This file contains the class AcGePosition3d - A 3d point entity.

#include "adesk.h"
#include "gepent3d.h"
#include "gepnt3d.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGePosition3d : public AcGePointEnt3d
{
public:
    AcGePosition3d ();
    AcGePosition3d (const AcGePoint3d& pnt);
    AcGePosition3d (double x, double y, double z);
    AcGePosition3d (const AcGePosition3d& pos);

    // Set point coordinates.
    //
    AcGePosition3d&  set        (const AcGePoint3d&);
    AcGePosition3d&  set        (double x, double y, double z );

    // Assignment operator.
    //
    AcGePosition3d& operator =  (const AcGePosition3d& pos);
};

#pragma pack (pop)
#endif
