#ifndef AC_BRFLTRAV_H
#define AC_BRFLTRAV_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrFaceLoopTraverser class is the interface class for face
// loop traversers. All the functionality supported by this class
// is implemented by the class AcBrImpFaceLoopTraverser.
//
// This class defines the functions that are pertinent to a loop
// in the context of a face. It is used to get access to downward
// hierarchical topological adjacencies, such as to traverse
// edges through their face/loop uses.
//
// The default constructor instantiates an uninitialised object. The
// function isNull() returns kTrue on an object created this way. To set
// an AcBrFaceLoopTraverser, call setFace() and/or setLoop() using valid,
// previously instantiated face and loop objects.
//
// The setFace() list owner initialiser is used to set this traverser 
// to a specific face loop list, starting at the first loop in the
// list. This initialises a traverser instantiated with the default
// constructor, and resets the criteria for the eBrepChanged error
// as well as the criteria for next() and done(). It also sets the
// validation level to match that of the face. If the face reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the face reference object was last set,
// Acad::eInvalidInput is returned. If the face is neither edge-
// bounded nor vertex-bounded (e.g., a sphere or a true torus, which
// have neither loops nor boundary curve geometry), eDegenerateTopology
// is returned. In the event of an error, this traverser's face loop
// list is unchanged.
//
// The getFace() list owner query returns the face owner of the loop
// list. The face object is instantiated by the caller and passed
// by reference for getFace() to set. If this traverser object is
// uninitialised, eUninitialisedObject is returned. If the associated
// AutoCAD object has been modified since the traverser was last
// set, eBrepChanged is returned. In the event of an error, the
// face reference object is unchanged and is thus likely to be
// uninitialised.
//
// The setLoop() list position initialiser is used to set this
// traverser's starting position to a specific loop in the face loop
// list, which resets the criteria for next() and done(). If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the loop reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the loop reference object was last set, Acad::
// eInvalidInput is returned. If the loop is not in the face loop
// list or is associated with a different AutoCAD object or revision,
// Acad::eWrongDatabase is returned. In the event of an error, this
// traverser's face loop list is unchanged.
//
// The getLoop() list position query returns the loop at the current
// position in the face loop list. The loop object is instantiated by
// the caller and passed by reference for getLoop() to set. If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the loop is missing, Acad::
// eNotInDatabase is returned. In the event of an error, the loop
// reference object is unchanged and is thus likely to be uninitialised.
//
// The setFaceAndLoop() list initialiser is used to set this traverser
// to a specific face loop list and starting position. This initialises
// a traverser instantiated with the default constructor, and resets
// the criteria for the eBrepChanged error as well as the criteria
// for next() and done(). It also sets the validation level to match
// that of the loop. The face list owner is inferred from the loop,
// as it is unique. If the loop reference object is uninitialised, or
// if the associated AutoCAD object has been modified since the loop
// reference object was last set, Acad::eInvalidInput is returned. In
// the event of an error, this traverser's face loop list is unchanged.
//
// The setFace() list owner initialiser(1) is used to set this traverser
// to a specific face loop list, starting at the first loop in the list.
// This initialises a traverser instantiated with the default constructor,
// and resets the criteria for the eBrepChanged error as well as the
// criteria for next() and done(). It also sets the validation level to
// match that of the shell face traverser. If the shell-face traverser
// reference object is uninitialised, or if the associated AutoCAD object
// has been modified since the shell-face traverser reference object was
// last set, Acad::eInvalidInput is returned. If the face is neither edge-
// bounded nor vertex-bounded (e.g., a sphere or a true torus, which
// have neither loops nor boundary curve geometry), eDegenerateTopology
// is returned. In the event of an error, this traverser's face loop 
// list is unchanged.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brtrav.h"


// forward class declarations
class AcBrFace;
class AcBrLoop;
class AcBrShellFaceTraverser;


class AcBrFaceLoopTraverser : public AcBrTraverser
{
public:
    ACRX_DECLARE_MEMBERS(AcBrFaceLoopTraverser);
    AcBrFaceLoopTraverser();
    AcBrFaceLoopTraverser(const AcBrFaceLoopTraverser& src);
    ~AcBrFaceLoopTraverser();

    // Assignment operator
    AcBrFaceLoopTraverser& operator =   (const AcBrFaceLoopTraverser& src);

    // Queries & Initialisers
    AcBr::ErrorStatus   setFace         (AcBrFace& face);
    AcBr::ErrorStatus   getFace         (AcBrFace& face) const;
    AcBr::ErrorStatus   setLoop         (AcBrLoop& loop);
    AcBr::ErrorStatus   getLoop         (AcBrLoop& loop) const;
    AcBr::ErrorStatus   setFaceAndLoop	(const AcBrLoop& loop);
    AcBr::ErrorStatus   setFace         (const AcBrFace& face);
    AcBr::ErrorStatus   setLoop         (const AcBrLoop& loop);
    AcBr::ErrorStatus   setFace         (const AcBrShellFaceTraverser& shellFaceTrav);
};


#endif

