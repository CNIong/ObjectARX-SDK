#ifndef AC_BRBVTRAV_H
#define AC_BRBVTRAV_H 1
// (C) Copyright 1997-1999 by Autodesk, Inc.
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
// The AcBrBrepVertexTraverser class is the interface class for brep
// vertex traversers. All the functionality supported by this class
// is implemented by the class AcBrImpBrepVertexTraverser.
//
// This class defines the functions that are pertinent to a vertex
// in the global context of a brep. It is used to traverse all of
// the unique vertices in a brep.
//
// The default constructor instantiates an uninitialised object. The
// function isNull() returns kTrue on an object created this way. To set
// an AcBrBrepVertexTraverser, call setBrep() and/or setVertex() using
// valid, previously instantiated brep and vertex objects.
//
// The setBrepAndVertex() list initialiser is used to set this traverser
// to a specific brep vertex list and starting position. This initialises
// a traverser instantiated with the default constructor, and resets
// the criteria for the eBrepChanged error as well as the criteria
// for next() and done(). It also sets the validation level to match
// that of the vertex. The brep list owner is inferred from the vertex,
// as it is unique. If the vertex reference object is uninitialised, or
// if the associated AutoCAD object has been modified since the vertex
// reference object was last set, Acad::eInvalidInput is returned. In
// the event of an error, this traverser's brep vertex list is unchanged.
//
// The setBrep() list owner initialiser is used to set this traverser 
// to a specific brep vertex list, starting at the first vertex in the
// list. This initialises a traverser instantiated with the default
// constructor, and resets the criteria for the eBrepChanged error
// as well as the criteria for next() and done(). It also sets the
// validation level to match that of the brep. If the brep reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the brep reference object was last set,
// Acad::eInvalidInput is returned. If the brep is not vertex-bounded
// (e.g., a wireframe or an empty/deleted/unsurfaced model),
// eDegenerateTopology is returned. In the event of an error, this
// traverser's brep vertex list is unchanged.
//
// The getBrep() list owner query returns the brep owner of the vertex
// list. The brep object is instantiated by the caller and passed
// by reference for getBrep() to set. If this traverser object is
// uninitialised, eUninitialisedObject is returned. If the associated
// AutoCAD object has been modified since the traverser was last
// set, eBrepChanged is returned. In the event of an error, the
// brep reference object is unchanged and is thus likely to be
// uninitialised.
//
// The setVertex() list position initialiser is used to set this
// traverser's starting position to a specific vertex in the brep vertex
// list, which resets the criteria for next() and done(). If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the vertex reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the vertex reference object was last set, Acad::
// eInvalidInput is returned. If the vertex is not in the brep edge
// list or is associated with a different AutoCAD object or revision,
// Acad::eWrongDatabase is returned. In the event of an error, this
// traverser's brep vertex list is unchanged.
//
// The getVertex() list position query returns the vertex at the current
// position in the brep vertex list. The vertex object is instantiated by
// the caller and passed by reference for getVertex() to set. If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the vertex is missing or
// fails to map to a valid subentity ID, Acad::eNotInDatabase is returned.
// In the event of an error, the vertex reference object is unchanged
// and is thus likely to be uninitialised.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brtrav.h"


// forward class declarations
class AcBrBrep;
class AcBrVertex;


class AcBrBrepVertexTraverser : public AcBrTraverser
{
public:
    ACRX_DECLARE_MEMBERS(AcBrBrepVertexTraverser);
    AcBrBrepVertexTraverser();
    AcBrBrepVertexTraverser(const AcBrBrepVertexTraverser& src);
    ~AcBrBrepVertexTraverser();

    // Assignment operator
    AcBrBrepVertexTraverser& operator =	(const AcBrBrepVertexTraverser& src);

    // Queries & Initialisers
    AcBr::ErrorStatus   setBrepAndVertex(const AcBrVertex& vertex);
    AcBr::ErrorStatus   setBrep         (const AcBrBrep& brep);
    AcBr::ErrorStatus   getBrep         (AcBrBrep& brep) const;
    AcBr::ErrorStatus   setVertex       (const AcBrVertex& vertex);
    AcBr::ErrorStatus   getVertex       (AcBrVertex& vertex) const;
};


#endif

