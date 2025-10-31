#ifndef AC_BRBFTRAV_H
#define AC_BRBFTRAV_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrBrepFaceTraverser class is the interface class for brep
// face traversers. All the functionality supported by this class
// is implemented by the class AcBrImpBrepFaceTraverser.
//
// This class defines the functions that are pertinent to a face
// in the global context of a brep. It is used to seed a downward
// hierarchical traversal of the brep portion of an AutoCAD solid, surface,
// region or body, or to traverse all of the unique faces in a brep.
//
// The default constructor instantiates an uninitialised object. The
// function isNull() returns kTrue on an object created this way. To set
// an AcBrBrepFaceTraverser, call setBrep() and/or setFace() using valid,
// previously instantiated brep and face objects.
//
// The setBrep() list owner initialiser is used to set this traverser 
// to a specific brep face list, starting at the first face in the
// list. This initialises a traverser instantiated with the default
// constructor, and resets the criteria for the eBrepChanged error
// as well as the criteria for next() and done(). It also sets the
// validation level to match that of the brep. If the brep reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the brep reference object was last set,
// Acad::eInvalidInput is returned. If the brep is not face-bounded
// (e.g., a wireframe or an empty/deleted/unsurfaced model),
// eDegenerateTopology is returned. In the event of an error, this
// traverser's brep face list is unchanged.
//
// The getBrep() list owner query returns the brep owner of the face
// list. The brep object is instantiated by the caller and passed
// by reference for getBrep() to set. If this traverser object is
// uninitialised, eUninitialisedObject is returned. If the associated
// AutoCAD object has been modified since the traverser was last
// set, eBrepChanged is returned. In the event of an error, the
// brep reference object is unchanged and is thus likely to be
// uninitialised.
//
// The setFace() list position initialiser is used to set this
// traverser's starting position to a specific face in the brep face
// list, which resets the criteria for next() and done(). If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the face reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the face reference object was last set, Acad::
// eInvalidInput is returned. If the face is not in the brep face
// list or is associated with a different AutoCAD object or revision,
// Acad::eWrongDatabase is returned. In the event of an error, this
// traverser's brep face list is unchanged.
//
// The getFace() list position query returns the face at the current
// position in the brep face list. The face object is instantiated by
// the caller and passed by reference for getFace() to set. If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the face is missing or
// fails to map to a valid subentity ID, Acad::eNotInDatabase is returned.
// In the event of an error, the face reference object is unchanged 
// and is thus likely to be uninitialised.
//
// The setBrepAndFace() list initialiser is used to set this traverser
// to a specific brep face list and starting position. This initialises
// a traverser instantiated with the default constructor, and resets
// the criteria for the eBrepChanged error as well as the criteria
// for next() and done(). It also sets the validation level to match
// that of the face. The brep list owner is inferred from the face, 
// as it is unique. If the face reference object is uninitialised, or
// if the associated AutoCAD object has been modified since the face
// reference object was last set, Acad::eInvalidInput is returned. In
// the event of an error, this traverser's brep face list is unchanged.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brtrav.h"


// forward class declarations
class AcBrBrep;
class AcBrFace;


class AcBrBrepFaceTraverser : public AcBrTraverser
{
public:
    ACRX_DECLARE_MEMBERS(AcBrBrepFaceTraverser);
    AcBrBrepFaceTraverser();
    AcBrBrepFaceTraverser(const AcBrBrepFaceTraverser& src);
    ~AcBrBrepFaceTraverser();

    // Assignment operator
    AcBrBrepFaceTraverser& operator =   (const AcBrBrepFaceTraverser& src);

    // Queries & Initialisers
    AcBr::ErrorStatus   setBrep         (AcBrBrep& brep);
    AcBr::ErrorStatus   getBrep         (AcBrBrep& brep) const;
    AcBr::ErrorStatus   setFace         (AcBrFace& face);
    AcBr::ErrorStatus   getFace         (AcBrFace& face) const;
    AcBr::ErrorStatus   setBrepAndFace  (const AcBrFace& face);
    AcBr::ErrorStatus   setBrep         (const AcBrBrep& brep);
    AcBr::ErrorStatus   setFace         (const AcBrFace& face);
};


#endif

