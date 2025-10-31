#ifndef AC_GEPOS2D_H
#define AC_GEPOS2D_H
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
// This file contains the class AcGePosition2d - A 2d point entity.

#include "adesk.h"
#include "gepent2d.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGePosition2d : public AcGePointEnt2d
{
public:
    AcGePosition2d ();
    AcGePosition2d (const AcGePoint2d& pnt);
    AcGePosition2d (double x, double y);
    AcGePosition2d (const AcGePosition2d& pos);

    // Set point coordinates.
    //
    AcGePosition2d&  set        (const AcGePoint2d&);
    AcGePosition2d&  set        (double x, double y );

    // Assignment operator.
    //
    AcGePosition2d& operator =  (const AcGePosition2d& pos);
};

#pragma pack (pop)
#endif
