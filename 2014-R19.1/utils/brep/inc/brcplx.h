#ifndef AC_BRCPLX_H
#define AC_BRCPLX_H 1
// (C) Copyright 1998-1999 by Autodesk, Inc.
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
// The AcBrComplex class is the interface class for brep complexes.
// All the functionality supported by this class is implemented by
// the class AcBrImpComplex.
//
// This class defines the functions that are pertinent to the complex
// level of a brep topology adjacency hierarchy, which is not exposed
// as a subentity type in AutoCAD and thus cannot be directly set by
// the user; it is set indirectly by the traversers. It is also used
// to set the first complex of a complex list in AcBrBrepComplexTraverser. 
//
// Complexes are primary brep elements but have no associated geometry
// as there is no geometric primitive above the level of a surface.
// Conceptually, a complex corresponds to a connected region of points
// in three-space, which may define a volume or an area (degenerate).
// A complex may be comprised of one or more connected shell boundaries.
//
// The default constructor instantiates an empty object. The function
// isNull() returns kTrue on an object created this way. To set an
// AcBrComplex, call AcBrBrepComplexTraverser::getComplex() or 
// AcBrShell::getComplex() using this complex object as input.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brent.h"


class AcBrComplex : public AcBrEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcBrComplex);
    AcBrComplex();
    AcBrComplex(const AcBrComplex& src);
    ~AcBrComplex();

    // Assignment operator
    AcBrComplex&	operator =      (const AcBrComplex& src);
};


#endif
