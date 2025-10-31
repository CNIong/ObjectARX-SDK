#ifndef AC_BRVLTRAV_H
#define AC_BRVLTRAV_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrVertexLoopTraverser class is the interface class for
// vertex loop traversers. All the functionality supported by this
// class is implemented by the class AcBrImpVertexLoopTraverser.
//
// This class defines the functions that are pertinent to a loop
// in the context of a radial traversal of vertex uses. It is used
// to get access to upward hierarchical topological adjacencies,
// such as to radially traverse the faces sharing a common vertex
// through its loop boundaries.
//
// The default constructor instantiates an uninitialised object. The
// function isNull() returns kTrue on an object created this way. To
// set an AcBrVertexLoopTraverser, call setVertexAndLoop() or
// setVertex() using valid, previously instantiated loop-vertex
// traversers and vertex objects.
//
// The setVertexAndLoop() list initialiser is used to set this traverser 
// to a specific vertex loop list and starting position. This initialises
// a traverser instantiated with the default constructor, and resets
// the criteria for the eBrepChanged error as well as the criteria for
// next() and done(). It also sets the validation level to match that
// of the loop-vertex. If the loop-vertex traverser reference object is
// uninitialised, or if the associated AutoCAD object has been modified
// since the loop-vertex traverser reference object was last set,
// Acad::eInvalidInput is returned. In the event of an error, this
// traverser's vertex loop list is unchanged.
//
// The setVertex() list owner initialiser is used to set this traverser 
// to a specific vertex loop list, starting at the first loop in the
// list. This initialises a traverser instantiated with the default
// constructor, and resets the criteria for the eBrepChanged error
// as well as the criteria for next() and done(). It also sets the
// validation level to match that of the vertex. If the vertex reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the vertex reference object was last set,
// Acad::eInvalidInput is returned. If the vertex is not loop-bounded
// eDegenerateTopology is returned. In the event of an error, this
// traverser's vertex loop list is unchanged.
//
// The getVertex() list owner query returns the vertex owner of the
// loop list. The vertex object is instantiated by the caller and
// passed by reference for getVertex() to set. If this traverser
// object is uninitialised, eUninitialisedObject is returned. If the
// associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. In the event of an error,
// the vertex reference object is unchanged and is thus likely to be
// uninitialised.
//
// The setLoop() list position initialiser is used to set this
// traverser's starting position to a specific loop in the vertex loop
// list, which resets the criteria for next() and done(). If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the loop reference object
// is uninitialised, or if the associated AutoCAD object has been
// modified since the loop reference object was last set, Acad::
// eInvalidInput is returned. If the loop is not in the vertex loop
// list or is associated with a different AutoCAD object or revision,
// Acad::eWrongDatabase is returned. In the event of an error, this
// traverser's vertex loop list is unchanged.
//
// The getLoop() list position query returns the loop at the current
// position in the vertex loop list. The loop object is instantiated by
// the caller and passed by reference for getLoop() to set. If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the loop is missing, Acad::
// eNotInDatabase is returned. In the event of an error, the loop
// reference object is unchanged and is thus likely to be uninitialised.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brtrav.h"


// forward class declarations
class AcBrLoop;
class AcBrVertex;
class AcBrLoopVertexTraverser;


class AcBrVertexLoopTraverser : public AcBrTraverser
{
public:
    ACRX_DECLARE_MEMBERS(AcBrVertexLoopTraverser);
    AcBrVertexLoopTraverser();
    AcBrVertexLoopTraverser(const AcBrVertexLoopTraverser& src);
    ~AcBrVertexLoopTraverser();

    // Assignment operator
    AcBrVertexLoopTraverser& operator =	(const AcBrVertexLoopTraverser& src);

    // Queries & Initialisers
    AcBr::ErrorStatus   setVertexAndLoop(const AcBrLoopVertexTraverser& LoopVertexTraverser);
    AcBr::ErrorStatus   setVertex       (const AcBrVertex& vertex);
    AcBr::ErrorStatus   getVertex       (AcBrVertex& vertex) const;
    AcBr::ErrorStatus   setLoop         (const AcBrLoop& loop);
    AcBr::ErrorStatus   getLoop         (AcBrLoop& loop) const;
};


#endif

