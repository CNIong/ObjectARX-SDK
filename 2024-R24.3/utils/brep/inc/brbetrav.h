#ifndef AC_BRBETRAV_H
#define AC_BRBETRAV_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrBrepEdgeTraverser class is the interface class for brep
// edge traversers. All the functionality supported by this class
// is implemented by the class AcBrImpBrepEdgeTraverser.
//
// This class defines the functions that are pertinent to an edge
// in the global context of a brep. It is used to traverse all of
// the unique edges in a brep.
//
// The default constructor instantiates an uninitialised object. The
// function isNull() returns kTrue on an object created this way. To set
// an AcBrBrepEdgeTraverser, call setBrep() and/or setEdge() using valid,
// previously instantiated brep and edge objects.
//
// The setBrepAndEdge() list initialiser is used to set this traverser
// to a specific brep edge list and starting position. This initialises
// a traverser instantiated with the default constructor, and resets
// the criteria for the eBrepChanged error as well as the criteria
// for next() and done(). It also sets the validation level to match
// that of the edge. The brep list owner is inferred from the edge,
// as it is unique. If the edge reference object is uninitialised, or
// if the associated AutoCAD object has been modified since the edge
// reference object was last set, Acad::eInvalidInput is returned. In
// the event of an error, this traverser's brep edge list is unchanged.
//
// The setBrep() list owner initialiser is used to set this traverser 
// to a specific brep edge list, starting at the first edge in the
// list. This initialises a traverser instantiated with the default
// constructor, and resets the criteria for the eBrepChanged error
// as well as the criteria for next() and done(). It also sets the
// validation level to match that of the brep. If the brep reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the brep reference object was last set,
// Acad::eInvalidInput is returned. If the brep is not edge-bounded
// (e.g., a wireframe or an empty/deleted/unsurfaced model),
// eDegenerateTopology is returned. In the event of an error, this
// traverser's brep edge list is unchanged.
//
// The getBrep() list owner query returns the brep owner of the edge
// list. The brep object is instantiated by the caller and passed
// by reference for getBrep() to set. If this traverser object is
// uninitialised, eUninitialisedObject is returned. If the associated
// AutoCAD object has been modified since the traverser was last
// set, eBrepChanged is returned. In the event of an error, the
// brep reference object is unchanged and is thus likely to be
// uninitialised.
//
// The setEdge() list position initialiser is used to set this
// traverser's starting position to a specific edge in the brep edge
// list, which resets the criteria for next() and done(). If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the
// traverser was last set, eBrepChanged is returned. If the edge
// reference object is uninitialised, or if the associated AutoCAD
// object has been modified since the edge reference object was last
// set, Acad::eInvalidInput is returned. If the edge is not in the
// brep edge list or is associated with a different AutoCAD object
// or revision, Acad::eWrongDatabase is returned. In the event of
// an error, this traverser's brep edge list is unchanged.
//
// The getEdge() list position query returns the edge at the current
// position in the brep edge list. The edge object is instantiated by
// the caller and passed by reference for getEdge() to set. If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the edge is missing,
// Acad::eWrongDatabase is returned. If the edge fails to map to a valid
// subentity ID, Acad::eNotInDatabase is returned. In the event of an
// error, the edge reference object is unchanged and is thus likely
// to be uninitialised.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brtrav.h"


// forward class declarations
class AcBrBrep;
class AcBrEdge;


class AcBrBrepEdgeTraverser : public AcBrTraverser
{
public:
    ACRX_DECLARE_MEMBERS(AcBrBrepEdgeTraverser);
    AcBrBrepEdgeTraverser();
    AcBrBrepEdgeTraverser(const AcBrBrepEdgeTraverser& src);
    ~AcBrBrepEdgeTraverser();

    // Assignment operator
    AcBrBrepEdgeTraverser& operator =   (const AcBrBrepEdgeTraverser& src);

    // Queries & Initialisers
    AcBr::ErrorStatus   setBrepAndEdge  (const AcBrEdge& edge);
    AcBr::ErrorStatus   setBrep         (const AcBrBrep& brep);
    AcBr::ErrorStatus   getBrep         (AcBrBrep& brep) const;
    AcBr::ErrorStatus   setEdge         (const AcBrEdge& edge);
    AcBr::ErrorStatus   getEdge         (AcBrEdge& edge) const;
};


#endif

