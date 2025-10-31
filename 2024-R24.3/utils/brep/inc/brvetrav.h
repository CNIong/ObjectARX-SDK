#ifndef AC_BRVETRAV_H
#define AC_BRVETRAV_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrVertexEdgeTraverser class is the interface class for
// vertex edge traversers. All the functionality supported by this
// class is implemented by the class AcBrImpVertexEdgeTraverser.
//
// This class defines the functions that are pertinent to an edge
// in the context of a radial traversal of vertex uses. It is used
// to get access to upward hierarchical topological adjacencies,
// such as to radially traverse the faces sharing a common vertex
// through its edge boundaries.
//
// The default constructor instantiates an uninitialised object. The
// function isNull() returns kTrue on an object created this way. To
// set an AcBrVertexEdgeTraverser, call setVertex() and setEdge()
// using valid, previously instantiated vertex and edge objects.
//
// The setVertex() list owner initialiser is used to set this traverser
// to a specific vertex edge list, starting at the first edge in the
// list. This initialises a traverser instantiated with the default
// constructor, and resets the criteria for the eBrepChanged error
// as well as the criteria for next() and done(). It also sets the
// validation level to match that of the vertex. If the vertex reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the vertex reference object was last set,
// Acad::eInvalidInput is returned. If the vertex represents a
// singularity (such as at the apex of a cone), eDegenerateTopology
// is returned; use the vertex to set an AcBrVertexLoopTraverser
// instead. In the event of an error, this traverser's vertex edge
// list is unchanged.
//
// The getVertex() list owner query returns the vertex owner of the
// edge list. The vertex object is instantiated by the caller and
// passed by reference for getVertex() to set. If this traverser
// object is uninitialised, eUninitialisedObject is returned. If the
// associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. In the event of an error,
// the vertex reference object is unchanged and is thus likely to be
// uninitialised.
//
// The setEdge() list position initialiser is used to set this
// traverser's starting position to a specific edge in the vertex edge
// list, which resets the criteria for next() and done(). If this
// traverser object is uninitialised, eUninitialisedObject is returned. 
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the edge reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the edge reference object was last set, Acad::
// eInvalidInput is returned. If the edge is not in the vertex edge
// list or is associated with a different AutoCAD object or revision,
// Acad::eWrongDatabase is returned. In the event of an error, this
// traverser's vertex edge list is unchanged.
//
// The getEdge() list position query returns the edge at the current
// position in the vertex edge list. The edge object is instantiated by
// the caller and passed by reference for getEdge() to set. If this
// traverser object is uninitialised, eUninitialisedObject is returned. 
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the edge is missing or 
// fails to map to a valid subentity ID, Acad::eNotInDatabase is returned.
// In the event of an error, the edge reference object is unchanged and
// is thus likely to be uninitialised.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brtrav.h"


// forward class declarations
class AcBrEdge;
class AcBrVertex;


class AcBrVertexEdgeTraverser : public AcBrTraverser
{
public:
    ACRX_DECLARE_MEMBERS(AcBrVertexEdgeTraverser);
    AcBrVertexEdgeTraverser();
    AcBrVertexEdgeTraverser(const AcBrVertexEdgeTraverser& src);
    ~AcBrVertexEdgeTraverser();

    // Assignment operator
    AcBrVertexEdgeTraverser& operator =	(const AcBrVertexEdgeTraverser& src);

    // Queries & Initialisers
    AcBr::ErrorStatus   setVertex		(const AcBrVertex& vertex);
    AcBr::ErrorStatus   getVertex       (AcBrVertex& vertex) const;
    AcBr::ErrorStatus   setEdge         (const AcBrEdge& edge);
    AcBr::ErrorStatus   getEdge         (AcBrEdge& edge) const;
};


#endif

