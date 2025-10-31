#ifndef AC_BRSFTRAV_H
#define AC_BRSFTRAV_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrShellFaceTraverser class is the interface class for shell
// face traversers. All the functionality supported by this class is
// implemented by the class AcBrImpShellFaceTraverser.
//
// This class defines the functions that are pertinent to a face
// in the context of a shell. It is used to get access to downward
// hierarchical topological adjacencies, such as to traverse
// faces through their shell/face uses.
//
// The default constructor instantiates an uninitialised object. The
// function isNull() returns kTrue on an object created this way. To set
// an AcBrShellFaceTraverser, call setShell() and/or setFace() using
// valid, previously instantiated shell and face objects.
//
// The setShellAndFace() list initialiser is used to set this traverser
// to a specific shell face list and starting position. This initialises
// a traverser instantiated with the default constructor, and resets
// the criteria for the eBrepChanged error as well as the criteria
// for next() and done(). It also sets the validation level to match
// that of the face. The shell list owner is inferred from the face,
// as it is unique. If the face reference object is uninitialised, or
// if the associated AutoCAD object has been modified since the face
// reference object was last set, Acad::eInvalidInput is returned. In
// the event of an error, this traverser's shell face list is unchanged.
//
// The setShell() list owner initialiser is used to set this traverser
// to a specific shell face list, starting at the first face in the list.
// This initialises a traverser instantiated with the default constructor,
// and resets the criteria for the eBrepChanged error as well as the
// criteria for next() and done(). It also sets the validation level to
// match that of the complex shell traverser. If the complex-shell traverser
// reference object is uninitialised, or if the associated AutoCAD object
// has been modified since the complex-shell traverser reference object was
// last set, Acad::eInvalidInput is returned. If the shell is not face-
// bounded, eDegenerateTopology is returned. In the event of an error,
// this traverser's shell face list is unchanged.
//
// The setShell() list owner initialiser(1) is used to set this traverser 
// to a specific shell face list, starting at the first face in the
// list. This initialises a traverser instantiated with the default
// constructor, and resets the criteria for the eBrepChanged error
// as well as the criteria for next() and done(). It also sets the
// validation level to match that of the shell. If the shell reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the shell reference object was last set,
// Acad::eInvalidInput is returned. If the shell is not face-bounded,
// eDegenerateTopology is returned. In the event of an error, this 
// traverser's shell face list is unchanged.
//
// The getShell() list owner query returns the shell owner of the face
// list. The shell object is instantiated by the caller and passed
// by reference for getShell() to set. If this traverser object is
// uninitialised, eUninitialisedObject is returned. If the associated
// AutoCAD object has been modified since the traverser was last
// set, eBrepChanged is returned. In the event of an error, the
// shell reference object is unchanged and is thus likely to be
// uninitialised.
//
// The setFace() list position initialiser is used to set this
// traverser's starting position to a specific face in the shell 
// face list, which resets the criteria for next() and done(). If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the face reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the face reference object was last set, Acad::
// eInvalidInput is returned. If the face is not in the shell face
// list or is associated with a different AutoCAD object or revision,
// Acad::eWrongDatabase is returned. In the event of an error, this
// traverser's shell face list is unchanged.
//
// The getFace() list position query returns the face at the current
// position in the shell face list. The face object is instantiated
// by the caller and passed by reference for getFace() to set. If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the face is missing, Acad::
// eNotInDatabase is returned. In the event of an error, the face
// reference object is unchanged and is thus likely to be uninitialised.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brtrav.h"


// forward class declarations
class AcBrShell;
class AcBrFace;
class AcBrComplexShellTraverser;


class AcBrShellFaceTraverser : public AcBrTraverser
{
public:
    ACRX_DECLARE_MEMBERS(AcBrShellFaceTraverser);
    AcBrShellFaceTraverser();
    AcBrShellFaceTraverser(const AcBrShellFaceTraverser& src);
    ~AcBrShellFaceTraverser();

    // Assignment operator
    AcBrShellFaceTraverser& operator =  (const AcBrShellFaceTraverser& src);

    // Queries & Initialisers
    AcBr::ErrorStatus   setShellAndFace	(const AcBrFace& face);
    AcBr::ErrorStatus   setShell        (const AcBrComplexShellTraverser& complexShellTraverser);
    AcBr::ErrorStatus   setShell        (const AcBrShell& shell);
    AcBr::ErrorStatus   getShell        (AcBrShell& shell) const;
    AcBr::ErrorStatus   setFace         (const AcBrFace& face);
    AcBr::ErrorStatus   getFace         (AcBrFace& face) const;
};


#endif

