#ifndef AC_BRSHELL_H
#define AC_BRSHELL_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrShell class is the interface class for brep shells. All the
// functionality supported by this class is implemented by the class
// AcBrImpShell.
//
// This class defines the functions that are pertinent to the shell
// level of a brep topology adjacency hierarchy, which is not exposed
// as a subentity type in AutoCAD and thus cannot be directly set by
// the user; it is set indirectly by the traversers. It is also used
// to set the first shell of a shell list in AcBrBrepShellTraverser. 
//
// Shells are secondary brep elements and thus have no associated
// geometry. Conceptually, a shell corresponds to a set of neighbouring
// surfaces on a solid. 
//
// The default constructor instantiates an empty object. The function
// isNull() returns kTrue on an object created this way. To set an
// AcBrShell, call AcBrBrepShellTraverser::getShell() or AcBrFace::
// getShell() using this shell object as input.
//
// The getComplex() upward adjacency query returns the complex that is
// bounded by this shell (always unique). The complex is instantiated by 
// the caller and passed by reference for getComplex() to set. If this
// shell object is uninitialised, eUninitialisedObject is returned. If 
// the associated AutoCAD object has been modified since the subentity
// path was last set, eBrepChanged is returned. If the complex is missing,
// Acad::eNotInDatabase is returned. In the event of an error, the complex
// reference object is unchanged and is thus likely to be uninitialised.
//
// The getType() shell type query returns a dedicated ShellType enum which
// identifies this shell as being either kShellExterior or kShellInterior.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brent.h"


// forward class declarations
class AcBrComplex;


class AcBrShell : public AcBrEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcBrShell);
    AcBrShell();
    AcBrShell(const AcBrShell& src);
    ~AcBrShell();

    // Assignment operator
    AcBrShell&          operator =      (const AcBrShell& src);

    // Upward links
    // Complex usage of shell (1::1)
    AcBr::ErrorStatus   getComplex		(AcBrComplex& complex) const;

	// Shell type (e.g., exterior vs. interior)
	AcBr::ErrorStatus   getType			(AcBr::ShellType& shellType) const;
};


#endif
