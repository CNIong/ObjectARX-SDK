#ifndef AC_GEOFFSF_H
#define AC_GEOFFSF_H
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
// Description:
//
// This file contains the class AcGeOffsetSurface, a
// representation for an offset surface
//

#include "gegbl.h"
#include "gepnt3d.h"
#include "gesurf.h"
#pragma pack (push, 8)

class AcGePlane;
class AcGeBoundedPlane;
class AcGeCylinder;
class AcGeCone;
class AcGeSphere;
class AcGeTorus;

class
GX_DLLEXPIMPORT
AcGeOffsetSurface : public AcGeSurface
{
public:
    AcGeOffsetSurface();
    AcGeOffsetSurface(AcGeSurface* baseSurface,
                      double offsetDist,
                      Adesk::Boolean makeCopy = Adesk::kTrue);
    AcGeOffsetSurface(const AcGeOffsetSurface& offset);

    // Test whether this offset surface can be converted to a simple surface
    //
    Adesk::Boolean    isPlane        () const;
    Adesk::Boolean    isBoundedPlane () const;
    Adesk::Boolean    isSphere       () const;
    Adesk::Boolean    isCylinder     () const;
    Adesk::Boolean    isCone         () const;
    Adesk::Boolean    isTorus        () const;

    // Convert this offset surface to a simple surface
    //
        Adesk::Boolean    getSurface(AcGeSurface*&) const;

    // Get a copy of the construction surface.
    //
    void              getConstructionSurface (AcGeSurface*& base) const;

    double            offsetDist     () const;

    // Reset surface
    //
    AcGeOffsetSurface& set        (AcGeSurface*, double offsetDist,
                                    Adesk::Boolean makeCopy = Adesk::kTrue);

    // Assignment operator.
    //
    AcGeOffsetSurface& operator =  (const AcGeOffsetSurface& offset);
};

#pragma pack (pop)
#endif
