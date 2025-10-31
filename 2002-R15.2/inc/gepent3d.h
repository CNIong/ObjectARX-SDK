#ifndef AC_GEPENT3D_H
#define AC_GEPENT3D_H
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
// This file contains the class AcGePointEnt3d - An abstract base
// class to represent point entities.

#include "adesk.h"
#include "geent3d.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGePointEnt3d : public AcGeEntity3d
{
public:
    // Return point coordinates.
    //
    AcGePoint3d     point3d     () const;

    // Conversion operator to convert to AcGePoint3d.
    //
    operator        AcGePoint3d () const;

    // Assignment operator.
    //
    AcGePointEnt3d& operator =  (const AcGePointEnt3d& pnt);

protected:
    AcGePointEnt3d ();
    AcGePointEnt3d (const AcGePointEnt3d&);
};

#pragma pack (pop)
#endif
