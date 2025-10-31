#ifndef AC_BRBSTRAV_H
#define AC_BRBSTRAV_H 1
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
// The AcBrBrepShellTraverser class is the interface class for brep
// shell traversers. All the functionality supported by this class
// is implemented by the class AcBrImpBrepShellTraverser.
//
// This class defines the functions that are pertinent to a shell
// in the global context of a brep. It is used to traverse all of
// the unique shells in a brep.
//
// The default constructor instantiates an uninitialised object. The
// function isNull() returns kTrue on an object created this way. To
// set an AcBrBrepShellTraverser, call setBrep() and/or setShell()
// using valid, previously instantiated brep and shell objects.
//
// The setBrepAndShell() list initialiser is used to set this 
// traverser to a specific brep shell list and starting position.
// This initialises a traverser instantiated with the default constructor, 
// and resets the criteria for the eBrepChanged error as well as the
// criteria for next() and done(). It also sets the validation level 
// to match that of the shell. The brep list owner is inferred from
// the shell, as it is unique. If the shell reference object is 
// uninitialised, or if the associated AutoCAD object has been modified
// since the shell reference object was last set, Acad::eInvalidInput 
// is returned. In the event of an error, this traverser's brep shell 
// list is unchanged.
//
// The setBrep() list owner initialiser is used to set this traverser 
// to a specific brep shell list, starting at the first shell in
// the list. This initialises a traverser instantiated with the default
// constructor, and resets the criteria for the eBrepChanged error
// as well as the criteria for next() and done(). It also sets the
// validation level to match that of the brep. If the brep reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the brep reference object was last set, Acad::
// eInvalidInput is returned. If the brep is not shell-bounded (e.g.,
// a wireframe or an empty/deleted/unsurfaced model), eDegenerateTopology 
// is returned. In the event of an error, this traverser's brep shell 
// list is unchanged.
//
// The getBrep() list owner query returns the brep owner of the
// shell list. The brep object is instantiated by the caller and
// passed by reference for getBrep() to set. If this traverser object
// is uninitialised, eUninitialisedObject is returned. If the associated
// AutoCAD object has been modified since the traverser was last
// set, eBrepChanged is returned. In the event of an error, the
// brep reference object is unchanged and is thus likely to be
// uninitialised.
//
// The setShell() list position initialiser is used to set this
// traverser's starting position to a specific shell in the brep
// shell list, which resets the criteria for next() and done(). If 
// this traverser object is uninitialised, eUninitialisedObject is
// returned. If the associated AutoCAD object has been modified since
// the traverser was last set, eBrepChanged is returned. If the shell
// reference object is uninitialised, or if the associated AutoCAD
// object has been modified since the shell reference object was last
// set, Acad::eInvalidInput is returned. If the shell is not in the
// brep shell list or is associated with a different AutoCAD object
// or revision, Acad::eWrongDatabase is returned. In the event of
// an error, this traverser's brep shell list is unchanged.
//
// The getShell() list position query returns the shell at the current
// position in the brep shell list. The shell object is instantiated
// by the caller and passed by reference for getShell() to set. If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the shell is missing,
// Acad::eWrongDatabase is returned. In the event of an error, the shell
// reference object is unchanged and is thus likely to be uninitialised.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brtrav.h"


// forward class declarations
class AcBrBrep;
class AcBrShell;


class AcBrBrepShellTraverser : public AcBrTraverser
{
public:
    ACRX_DECLARE_MEMBERS(AcBrBrepShellTraverser);
    AcBrBrepShellTraverser();
    AcBrBrepShellTraverser(const AcBrBrepShellTraverser& src);
    ~AcBrBrepShellTraverser();

    // Assignment operator
    AcBrBrepShellTraverser& operator =(const AcBrBrepShellTraverser& src);

    // Queries & Initialisers
    AcBr::ErrorStatus   setBrepAndShell	(const AcBrShell& shell);
    AcBr::ErrorStatus   setBrep			(const AcBrBrep& brep);
    AcBr::ErrorStatus   getBrep			(AcBrBrep& brep) const;
    AcBr::ErrorStatus   setShell		(const AcBrShell& shell);
    AcBr::ErrorStatus   getShell		(AcBrShell& shell) const;
};


#endif

