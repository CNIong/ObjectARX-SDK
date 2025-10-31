//
#ifndef AC_BRBFTRAV_H
#define AC_BRBFTRAV_H 1
// (C) Copyright 1995-1999, 2010 by Autodesk, Inc.
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

