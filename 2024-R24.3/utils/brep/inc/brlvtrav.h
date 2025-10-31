#ifndef AC_BRLVTRAV_H
#define AC_BRLVTRAV_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrLoopVertexTraverser class is the interface class for loop
// vertex traversers. All the functionality supported by this class
// is implemented by the class AcBrImpLoopVertexTraverser.
//
// This class defines the functions that are pertinent to a vertex
// in the context of a face/loop. It is used to get access to
// vertex-bound data that requires the context of a specific
// face/loop, such as parameter space points; or to get vertices
// that represent isolated points in a model (i.e., singularities,
// such as the apex of a cone).
//
// The default constructor instantiates an uninitialised object. The
// function isNull() returns kTrue on an object created this way. To
// set an AcBrLoopVertexTraverser, call setLoopAndVertex() or setLoop()
// using valid, previously instantiated loop-vertex traversers and
// loop objects.
//
// The setLoop() list owner initialiser(1) is used to set this traverser 
// to a specific loop vertex list, starting at the first vertex in the
// list. This initialises a traverser instantiated with the default
// constructor, and resets the criteria for the eBrepChanged error
// as well as the criteria for next() and done(). It also sets the
// validation level to match that of the face-loop. If the face-loop
// traverser reference object is uninitialised, or if the associated
// AutoCAD object has been modified since the face-loop traverser
// reference object was last set, Acad::eInvalidInput is returned. In
// the event of an error, this traverser's loop vertex list is unchanged.
//
// The getLoop() list owner query returns the loop owner of the vertex
// list. The loop object is instantiated by the caller and passed
// by reference for getLoop() to set. If this traverser object is
// uninitialised, eUninitialisedObject is returned. If the associated
// AutoCAD object has been modified since the traverser was last
// set, eBrepChanged is returned. In the event of an error, the
// loop reference object is unchanged and is thus likely to be
// uninitialised.
//
// The getVertex() list position query returns the vertex at the current
// position in the loop vertex list. The vertex object is instantiated
// by the caller and passed by reference for getVertex() to set. If this
// traverser object is uninitialised, eUninitialisedObject is returned. 
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the vertex is missing or
// fails to map to a valid subentity ID, Acad::eNotInDatabase is returned.
// In the event of an error, the vertex reference object is unchanged
// and is thus likely to be uninitialised.
//
// The getParamPoint() parameter space point query is deprecated in
// favour of the efficient new getParamPoint() query which sets an
// already-instantiated point.
//
// The getParamPoint() parameter space point query returns the
// loop-vertex' underlying parameter point as an AcGePoint2d, with
// the entire chain of transforms from the vertex' subentity path
// ignored as they are only pertinent to model space. The parameter
// point represents the loop-vertex' model space point projected
// onto the uv parameter space grid of the surface associated with
// the face that is bounded by the loop owner of the loop-vertex,
// but may also represent a degenerate parameter space curve for
// a singularity. A 2d point is a convenient way to represent a
// u,v parameter pair. The parameter point is instantiated by the
// user and passed by reference for getParamPoint() to set. If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since this
// traverser was last set, eBrepChanged is returned. If either the
// point geometry or surface geometry is missing, Acad::eDegenerateGeometry
// is returned. In the event of an error, the parameter point
// reference argument's value is unchanged.
//
// The setLoopAndVertex() list initialiser is used to set this traverser 
// to a specific loop vertex list and starting position. This initialises
// a traverser instantiated with the default constructor, and resets
// the criteria for the eBrepChanged error as well as the criteria
// for next() and done(). It also sets the validation level to match
// that of the vertex. The loop list owner is inferred from the vertex,
// as it is unique. If the vertex reference object is uninitialised, or
// if the associated AutoCAD object has been modified since the vertex
// reference object was last set, Acad::eInvalidInput is returned. In
// the event of an error, this traverser's loop vertex list is unchanged.
//
// The setLoop() list owner initialiser(2) is used to set this traverser 
// to a specific loop vertex list, starting at the first vertex in the
// list. This initialises a traverser instantiated with the default
// constructor, and resets the criteria for the eBrepChanged error
// as well as the criteria for next() and done(). It also sets the
// validation level to match that of the loop. If the loop reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the loop reference object was last set,
// Acad::eInvalidInput is returned. If the loop is not vertex-bounded
// eDegenerateTopology is returned. In the event of an error, this
// traverser's loop vertex list is unchanged.
//
// The setVertex() list position initialiser is used to set this
// traverser's starting position to a specific vertex in the loop vertex
// list, which resets the criteria for next() and done(). If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the vertex reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the vertex reference object was last set, Acad::
// eInvalidInput is returned. If the vertex is not in the loop edge
// list or is associated with a different AutoCAD object or revision,
// Acad::eWrongDatabase is returned. In the event of an error, this
// traverser's loop vertex list is unchanged.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brtrav.h"


// forward class declarations
class AcGePoint2d;
class AcBrLoop;
class AcBrVertex;
class AcBrFaceLoopTraverser;
class AcBrVertexLoopTraverser;


class AcBrLoopVertexTraverser : public AcBrTraverser
{
public:
    ACRX_DECLARE_MEMBERS(AcBrLoopVertexTraverser);
    AcBrLoopVertexTraverser();
    AcBrLoopVertexTraverser(const AcBrLoopVertexTraverser& src);
    ~AcBrLoopVertexTraverser();

    // Assignment operator
    AcBrLoopVertexTraverser& operator = (const AcBrLoopVertexTraverser& src);

    // Queries & Initialisers
    AcBr::ErrorStatus   setLoop         (AcBrFaceLoopTraverser& faceLoop);
    AcBr::ErrorStatus   getLoop         (AcBrLoop& loop) const;
    AcBr::ErrorStatus   getVertex       (AcBrVertex& vertex) const;

    // Downward links
    // Vertex usage by loop (n::1)
    AcBr::ErrorStatus   getParamPoint	(AcGePoint2d*& ppoint) const;
    AcBr::ErrorStatus   getParamPoint	(AcGePoint2d& ppoint) const;

    // Queries & Initialisers
	AcBr::ErrorStatus	setLoopAndVertex(const AcBrVertexLoopTraverser& vertexLoop);
    AcBr::ErrorStatus   setLoop         (const AcBrFaceLoopTraverser& faceLoop);
	AcBr::ErrorStatus   setLoop         (const AcBrLoop& loop);
    AcBr::ErrorStatus   setVertex       (const AcBrVertex& vertex);
};


#endif
