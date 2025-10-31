#ifndef AC_GEPENT2D_H
#define AC_GEPENT2D_H
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
// This file contains the class AcGePointEnt2d - An abstract base
// class to represent point entities.

#include "adesk.h"
#include "geent2d.h"
#include "gepnt2d.h"
#pragma pack (push, 8)

class 
GE_DLLEXPIMPORT
AcGePointEnt2d : public AcGeEntity2d
{
public:

    // Return point coordinates.
    //
    AcGePoint2d     point2d     () const;

    // Conversion operator to convert to AcGePoint2d.
    //
    operator        AcGePoint2d () const;
    
    // Assignment operator.
    //
    AcGePointEnt2d& operator =  (const AcGePointEnt2d& pnt);

protected:

    // Private constructors so that no object of this class can be instantiated.
    AcGePointEnt2d ();
    AcGePointEnt2d (const AcGePointEnt2d&);
};

#pragma pack (pop)
#endif
