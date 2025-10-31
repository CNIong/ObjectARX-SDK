#ifndef AC_BRCPLX_H
#define AC_BRCPLX_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
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
