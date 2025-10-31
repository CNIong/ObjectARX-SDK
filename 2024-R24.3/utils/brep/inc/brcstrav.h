#ifndef AC_BRCSTRAV_H
#define AC_BRCSTRAV_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrComplexShellTraverser class is the interface class for complex
// shell traversers. All the functionality supported by this class is
// implemented by the class AcBrImpComplexShellTraverser.
//
// This class defines the functions that are pertinent to a shell
// in the context of a complex. It is used to get access to downward
// hierarchical topological adjacencies, such as to traverse
// faces through their complex/shell uses.
//
// The default constructor instantiates an uninitialised object. The
// function isNull() returns kTrue on an object created this way. To set
// an AcBrComplexShellTraverser, call setComplex() and/or setShell() using
// valid, previously instantiated complex and shell objects.
//
// The setComplexAndShell() list initialiser is used to set this traverser
// to a specific complex shell list and starting position. This initialises
// a traverser instantiated with the default constructor, and resets
// the criteria for the eBrepChanged error as well as the criteria
// for next() and done(). It also sets the validation level to match
// that of the shell. The complex list owner is inferred from the shell,
// as it is unique. If the shell reference object is uninitialised, or
// if the associated AutoCAD object has been modified since the shell
// reference object was last set, Acad::eInvalidInput is returned. In
// the event of an error, this traverser's complex shell list is unchanged.
//
// The setComplex() list owner initialiser is used to set this traverser
// to a specific complex shell list, starting at the first shell in the list.
// This initialises a traverser instantiated with the default constructor,
// and resets the criteria for the eBrepChanged error as well as the
// criteria for next() and done(). It also sets the validation level to
// match that of the brep complex traverser. If the brep-complex traverser
// reference object is uninitialised, or if the associated AutoCAD object
// has been modified since the brep-complex traverser reference object was
// last set, Acad::eInvalidInput is returned. If the complex is not shell-
// bounded, eDegenerateTopology is returned. In the event of an error,
// this traverser's complex shell list is unchanged.
//
// The setComplex() list owner initialiser(1) is used to set this traverser 
// to a specific complex shell list, starting at the first shell in the
// list. This initialises a traverser instantiated with the default
// constructor, and resets the criteria for the eBrepChanged error
// as well as the criteria for next() and done(). It also sets the
// validation level to match that of the complex. If the complex reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the complex reference object was last set,
// Acad::eInvalidInput is returned. If the complex is not shell-bounded,
// eDegenerateTopology is returned. In the event of an error, this 
// traverser's complex shell list is unchanged.
//
// The getComplex() list owner query returns the complex owner of the shell
// list. The complex object is instantiated by the caller and passed
// by reference for getComplex() to set. If this traverser object is
// uninitialised, eUninitialisedObject is returned. If the associated
// AutoCAD object has been modified since the traverser was last
// set, eBrepChanged is returned. In the event of an error, the
// complex reference object is unchanged and is thus likely to be
// uninitialised.
//
// The setShell() list position initialiser is used to set this
// traverser's starting position to a specific shell in the complex 
// shell list, which resets the criteria for next() and done(). If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the shell reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the shell reference object was last set, Acad::
// eInvalidInput is returned. If the shell is not in the complex shell
// list or is associated with a different AutoCAD object or revision,
// Acad::eWrongDatabase is returned. In the event of an error, this
// traverser's complex shell list is unchanged.
//
// The getShell() list position query returns the shell at the current
// position in the complex shell list. The shell object is instantiated
// by the caller and passed by reference for getShell() to set. If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the shell is missing, Acad::
// eNotInDatabase is returned. In the event of an error, the shell
// reference object is unchanged and is thus likely to be uninitialised.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brtrav.h"


// forward class declarations
class AcBrComplex;
class AcBrShell;
class AcBrBrepComplexTraverser;


class AcBrComplexShellTraverser : public AcBrTraverser
{
public:
    ACRX_DECLARE_MEMBERS(AcBrComplexShellTraverser);
    AcBrComplexShellTraverser();
    AcBrComplexShellTraverser(const AcBrComplexShellTraverser& src);
    ~AcBrComplexShellTraverser();

    // Assignment operator
    AcBrComplexShellTraverser& operator =(const AcBrComplexShellTraverser& src);

    // Queries & Initialisers
    AcBr::ErrorStatus   setComplexAndShell(const AcBrShell& shell);
    AcBr::ErrorStatus   setComplex      (const AcBrBrepComplexTraverser& 						brepcompshell);
    AcBr::ErrorStatus   setComplex	(const AcBrComplex& complex);
    AcBr::ErrorStatus   getComplex      (AcBrComplex& complex) const;
    AcBr::ErrorStatus   setShell        (const AcBrShell& shell);
    AcBr::ErrorStatus   getShell        (AcBrShell& shell) const;
};


#endif

