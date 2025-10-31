#ifndef AC_GEEXTSF_H
#define AC_GEEXTSF_H
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
// This file implements the class AcGeExternalSurface, a
// representation for a surface that has its definition external
// to gelib.
//

#include "gegbl.h"
#include "gesurf.h"
#pragma pack (push, 8)

class AcGePlane;
class AcGeCylinder;
class AcGeCone;
class AcGeSphere;
class AcGeTorus;
class AcGeNurbSurface;
class surface;

class
GX_DLLEXPIMPORT
AcGeExternalSurface : public AcGeSurface
{
public:
   AcGeExternalSurface();
   AcGeExternalSurface(void* surfaceDef, AcGe::ExternalEntityKind surfaceKind,
                       Adesk::Boolean makeCopy = Adesk::kTrue);
   AcGeExternalSurface(const AcGeExternalSurface&);

   // Defining surface.
   //
   void getExternalSurface(void*& surfaceDef) const;

   // Type of the external surface.
   //
   AcGe::ExternalEntityKind  externalSurfaceKind() const;

   Adesk::Boolean    isPlane      () const;
   Adesk::Boolean    isSphere     () const;
   Adesk::Boolean    isCylinder   () const;
   Adesk::Boolean    isCone       () const;
   Adesk::Boolean    isTorus      () const;
   Adesk::Boolean    isNurbSurface() const;
   Adesk::Boolean    isDefined    () const;

   // Conversion to gelib entity
   //
   Adesk::Boolean isNativeSurface(AcGeSurface*& nativeSurface) const;

   // Assignment operator.
   //
   AcGeExternalSurface& operator = (const AcGeExternalSurface& src);

   // Reset surface
   //
   AcGeExternalSurface& set(void* surfaceDef,
                            AcGe::ExternalEntityKind surfaceKind,
                            Adesk::Boolean makeCopy = Adesk::kTrue);
   // Ownership of surface.
   //
   Adesk::Boolean       isOwnerOfSurface    () const;
   AcGeExternalSurface& setToOwnSurface     ();
};

#pragma pack (pop)
#endif
