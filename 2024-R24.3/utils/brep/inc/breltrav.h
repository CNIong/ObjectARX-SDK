#ifndef AC_BRELTRAV_H
#define AC_BRELTRAV_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrEdgeLoopTraverser class is the interface class for edge
// loop traversers. All the functionality supported by this class
// is implemented by the class AcBrImpEdgeLoopTraverser.
//
// This class defines the functions that are pertinent to a loop
// in the context of a radial traversal of edge uses. It is used
// to get access to upward hierarchical topological adjacencies,
// such as to radially traverse the faces sharing a common edge
// through its loop boundaries.
//
// The default constructor instantiates an uninitialised object. The
// function isNull() returns kTrue on an object created this way. To
// set an AcBrEdgeLoopTraverser, call setEdgeAndLoop() or setEdge()
// using valid, previously instantiated loop-edge traversers and edge
// objects.
//
// The setEdgeAndLoop() list initialiser is used to set this traverser 
// to a specific edge loop list and starting position. This initialises
// a traverser instantiated with the default constructor, and resets
// the criteria for the eBrepChanged error as well as the criteria for
// next() and done(). It also sets the validation level to match that
// of the loop-edge. If the loop-edge traverser reference object is
// uninitialised, or if the associated AutoCAD object has been modified
// since the loop-edge traverser reference object was last set,
// Acad::eInvalidInput is returned. In the event of an error, this
// traverser's edge loop list is unchanged.
//
// The setEdge() list owner initialiser(1) is used to set this traverser
// to a specific edge loop list, starting at the first loop in the
// list. This initialises a traverser instantiated with the default
// constructor, and resets the criteria for the eBrepChanged error
// as well as the criteria for next() and done(). It also sets the
// validation level to match that of the edge. If the edge reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the edge reference object was last set,
// Acad::eInvalidInput is returned. In the event of an error, this
// traverser's edge loop list is unchanged.
//
// The getEdge() list owner query returns the edge owner of the loop
// list. The edge object is instantiated by the caller and passed
// by reference for getEdge() to set. If this traverser object is
// uninitialised, eUninitialisedObject is returned. If the associated
// AutoCAD object has been modified since the traverser was last
// set, eBrepChanged is returned. In the event of an error, the 
// edge reference object is unchanged and is thus likely to be
// uninitialised.
//
// The setLoop() list position initialiser is used to set this
// traverser's starting position to a specific loop in the edge loop
// list, which resets the criteria for next() and done(). If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the loop reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the loop reference object was last set, Acad::
// eInvalidInput is returned. If the loop is not in the edge loop
// list or is associated with a different AutoCAD object or revision,
// Acad::eWrongDatabase is returned. In the event of an error, this
// traverser's edge loop list is unchanged.
//
// The getLoop() list position query returns the loop at the current
// position in the edge loop list. The loop object is instantiated by
// the caller and passed by reference for getLoop() to set. If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the loop is missing, Acad::
// eNotInDatabase is returned. In the event of an error, the loop
// reference object is unchanged and is thus likely to be uninitialised.
//
// The setEdge() list owner initialiser(2) is used to set this traverser
// to a specific edge loop list, starting at the first loop in the
// list. This initialises a traverser instantiated with the default
// constructor, and resets the criteria for the eBrepChanged error
// as well as the criteria for next() and done(). It also sets the
// validation level to match that of the edge. If the vertex edge
// traverser reference object is uninitialised, or if the associated
// AutoCAD object has been modified since the vertex edge traverser
// reference object was last set, Acad::eInvalidInput is returned.
// In the event of an error, this traverser's edge loop list is unchanged.
//
// The setLoop() list position initialiser is used to set this
// traverser's starting position to a specific loop in the edge loop
// list, which resets the criteria for next() and done(). If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the loop reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the loop reference object was last set, Acad::
// eInvalidInput is returned. If the loop is not in the edge loop
// list or is associated with a different AutoCAD object or revision,
// Acad::eWrongDatabase is returned. In the event of an error, this
// traverser's edge loop list is unchanged.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brtrav.h"


// forward class declarations
class AcBrLoop;
class AcBrEdge;
class AcBrLoopEdgeTraverser;
class AcBrVertexEdgeTraverser;


class AcBrEdgeLoopTraverser : public AcBrTraverser
{
public:
    ACRX_DECLARE_MEMBERS(AcBrEdgeLoopTraverser);
    AcBrEdgeLoopTraverser();
    AcBrEdgeLoopTraverser(const AcBrEdgeLoopTraverser& src);
    ~AcBrEdgeLoopTraverser();

    // Assignment operator
    AcBrEdgeLoopTraverser& operator =   (const AcBrEdgeLoopTraverser& src);

    // Queries & Initialisers
    AcBr::ErrorStatus   setEdgeAndLoop  (AcBrLoopEdgeTraverser& loopEdge);
    AcBr::ErrorStatus   setEdge         (AcBrEdge& edge);
    AcBr::ErrorStatus   getEdge         (AcBrEdge& edge) const;
    AcBr::ErrorStatus   getLoop         (AcBrLoop& loop) const;
    AcBr::ErrorStatus   setEdgeAndLoop  (const AcBrLoopEdgeTraverser& loopEdge);
    AcBr::ErrorStatus   setEdge         (const AcBrVertexEdgeTraverser& vertexEdge);
    AcBr::ErrorStatus   setEdge         (const AcBrEdge& edge);
    AcBr::ErrorStatus   setLoop         (const AcBrLoop& loop);
};


#endif

