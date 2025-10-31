#ifndef AC_BRLETRAV_H
#define AC_BRLETRAV_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrLoopEdgeTraverser class is the interface class for loop
// edge traversers. All the functionality supported by this class
// is implemented by the class AcBrImpLoopEdgeTraverser.
//
// This class defines the functions that are pertinent to an edge
// in the context of a face/loop. It is used to get access to
// downward hierarchical topological adjacencies; such as to
// traverse vertices through their edge uses, or to get access to
// edge-bound data that requires the context of a specific face/loop
// usage; such as parameter space curves.
// 
// The default constructor instantiates an uninitialised object. The
// function isNull() returns kTrue on an object created this way. To
// set an AcBrLoopEdgeTraverser, call setLoopAndEdge() or setLoop()
// using valid, previously instantiated edge-loop traverser and loop
// objects.
//
// The setLoopAndEdge() list initialiser is used to set this traverser
// to a specific loop edge list and starting position. This initialises
// a traverser instantiated with the default constructor, and resets
// the criteria for the eBrepChanged error as well as the criteria
// for next() and done(). It also sets the validation level to match
// that of the edge loop traverser. If the edge-loop traverser reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the edge-loop traverser reference object was 
// last set, Acad::eInvalidInput is returned. In the event of an
// error, this traverser's loop edge list is unchanged.
//
// The setLoop() list owner initialiser(1) is used to set this traverser
// to a specific loop edge list, starting at the first edge in the list.
// This initialises a traverser instantiated with the default constructor,
// and resets the criteria for the eBrepChanged error as well as the
// criteria for next() and done(). It also sets the validation level to
// match that of the face loop traverser. If the face-loop traverser
// reference object is uninitialised, or if the associated AutoCAD object
// has been modified since the face-loop traverser reference object was
// last set, Acad::eInvalidInput is returned. If the loop represents a
// singularity (such as at the apex of a cone), eDegenerateTopology
// is returned; use the loop to set an AcBrLoopVertexTraverser instead.
// In the event of an error, this traverser's loop edge list is unchanged.
//
// The getLoop() list owner query returns the loop owner of the edge
// list. The loop object is instantiated by the caller and passed
// by reference for getLoop() to set. If this traverser object is
// uninitialised, eUninitialisedObject is returned. If the associated
// AutoCAD object has been modified since the traverser was last
// set, eBrepChanged is returned. In the event of an error, the
// loop reference object is unchanged and is thus likely to be
// uninitialised.
//
// The setEdge() list position initialiser is used to set this
// traverser's starting position to a specific edge in the loop edge
// list, which resets the criteria for next() and done(). If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the edge reference object
// is uninitialised, or if the associated AutoCAD object has been
// modified since the edge reference object was last set, Acad::
// eInvalidInput is returned. If the edge is not in the loop edge
// list or is associated with a different AutoCAD object or revision,
// Acad::eWrongDatabase is returned. In the event of an error, this
// traverser's loop edge list is unchanged.
//
// The getEdge() list position query returns the edge at the current
// position in the loop edge list. The edge object is instantiated by
// the caller and passed by reference for getEdge() to set. If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the edge is missing or
// fails to map to a valid subentity ID, Acad::eNotInDatabase is returned.
// In the event of an error, the edge reference object is unchanged and
// is thus likely to be uninitialised.
//
// The getEdgeOrientToLoop() orientation query returns a simple Boolean
// indicating whether the natural orientation of the current edge in
// the loop edge list from vertex1 to vertex2 is in the direction of
// the loop (kTrue) or in the opposite direction (kFalse). If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since this traverser
// was last set, eBrepChanged is returned. In the event of an error,
// the orientation reference argument's value is unchanged and is thus
// meaningless.
//
// The getParamCurve() parameter space curve query returns the current
// edge in the loop edge list's underlying parameter curve as an
// oriented, subset AcGeExternalCurve2d (cast to the AcGeCurve2d base
// class), with the entire chain of transforms from the edge's
// subentity path ignored as they are only pertinent to model space.
// The parameter curve represents the current edge's model space curve
// projected onto the uv parameter space grid of the surface associated 
// with the face that is bounded by the loop owner of the edge list
// (always unique). The curve is subset, in its orientation with
// respect to the loop, to the edge's bounding vertices (i.e., the
// edge and loop-edge orientations are XOR'ed and used to determine
// the order of parameterisation). The curve is passed as a null
// AcGeCurve2d base class reference pointer for getParamCurve()
// to instantiate. If this traverser object is uninitialised,
// eUninitialisedObject is returned. If the associated AutoCAD object
// has been modified since this traverser was last set, eBrepChanged
// is returned. If the parameter curve is missing (such as may
// sometimes happen if the edge crosses an artefact seam, or if the
// edge represents a singularity or a wire edge), Acad::eDegenerateGeometry
// is returned. If the AcGeCurve2d allocation comes back null,
// Acad::eOutOfMemory is returned. In the event of an error, the
// parameter curve reference pointer is unchanged and thus likely
// points to a null object.
//
// The getOrientedCurve() model space curve query returns the current
// edge in the loop edge list's underlying curve as an oriented,
// subset AcGeExternalCurve3d (cast to the AcGeCurve3d base class),
// with the entire chain of transforms from the edge's subentity path
// applied. The oriented model space curve represents the current
// edge's associated curve oriented to flow in the direction of
// the loop. This is equivalent to taking the 3d curve returned by 
// AcBrEdge::getCurve() and conditionally applying the XOR'ed edge
// and loop-edge orientations using AcGeCurve3d::reverseParam().
// The curve is passed as a null AcGeCurve3d base class reference
// pointer for getOrientedCurve() to instantiate. If this traverser
// object is uninitialised, eUninitialisedObject is returned. If the
// associated AutoCAD object has been modified since this traverser
// was last set, eBrepChanged is returned. If the curve geometry 
// is missing, Acad::eDegenerateGeometry is returned. If the AcGeCurve3d
// allocation comes back null, Acad::eOutOfMemory is returned. If the
// transform has non-uniform scaling, Acad::eCannotScaleNonUniformly
// is returned as a warning message, along with the untransformed 
// curve. In the event of an error, the curve reference pointer is
// unchanged and thus likely points to a null object.
//
// The setLoop() list owner initialiser(2) is used to set this traverser
// to a specific loop edge list, starting at the first edge in the list.
// This initialises a traverser instantiated with the default constructor,
// and resets the criteria for the eBrepChanged error as well as the
// criteria for next() and done(). It also sets the validation level to
// match that of the loop. If the loop reference object is uninitialised,
// or if the associated AutoCAD object has been modified since the loop
// reference object was last set, Acad::eInvalidInput is returned. If
// the loop represents a singularity (such as at the apex of a cone),
// eDegenerateTopology is returned; use the loop to set an
// AcBrLoopVertexTraverser instead. In the event of an error,
// this traverser's loop edge list is unchanged.
//
// The getParamCurveAsNurb() parameter space curve query returns the
// current edge in the loop edge list's underlying parameter curve as an
// oriented, subset AcGeNurbCurve2d, with the entire chain of transforms
// from the edge's subentity path ignored as they are only pertinent to
// model space. The parameter curve represents the current edge's model
// space curve projected onto the uv parameter space grid of the surface
// associated with the face that is bounded by the loop owner of the edge
// list (always unique). The fit tolerance is currently ignored, as the
// internal modeler stores all parameter curves as NURBS, so we do not
// request a new one to be computed. The curve is subset, in its orientation
// with respect to the loop, to the edge's bounding vertices (i.e., the edge
// and loop-edge orientations are XOR'ed and used to determine the order
// of parameterisation). The achieved fit tolerance (if supplied) is returned
// as a double. The curve is instantiated by the user and passed by reference 
// for getParamCurveAsNurb() to set. If this traverser object is uninitialised,
// eUninitialisedObject is returned. If the associated AutoCAD object has
// been modified since this traverser was last set, eBrepChanged is returned.
// If a negative fit tolerance is supplied, Acad::eOutOfRange is returned.
// If the parameter curve is missing (such as may sometimes happen if the
// edge crosses an artefact seam, or if the edge represents a singularity
// or a wire edge), Acad::eDegenerateGeometry is returned. In the event of
// an error, the parameter curve and fit tolerance reference arguments are
// unchanged.
//
// The getOrientedCurveAsNurb() model space curve query returns the
// current edge in the loop edge list's underlying curve as an oriented,
// subset AcGeNurbCurve3d, with the entire chain of transforms from the
// edge's subentity path applied. The curve is converted to a NURB (if
// necessary) using the supplied fit tolerance (adjusted by the inverse
// scale factor from the nested transforms, in order to be in the same
// evaluation space as thi current edge). The oriented model space curve
// represents the current edge's associated curve as a NURB oriented to
// flow in the direction of the loop. This is equivalent to taking the
// 3d NURB curve returned by AcBrEdge::getCurveAsNurb() and conditionally
// applying the XOR'ed edge and loop-edge orientations using AcGeCurve3d::
// reverseParam(). The achieved fit tolerance (if supplied) is returned
// as a double, with the maximum scale factor applied from the nested
// transforms. The curve is instantiated by the user and passed by
// reference for getOrientedCurveAsNurb() to set. If this traverser
// object is uninitialised, eUninitialisedObject is returned. If the
// associated AutoCAD object has been modified since this traverser was
// last set, eBrepChanged is returned. If the fitTolRequired argument is
// not supplied or is set to zero, the default fit tolerance is used. If
// a negative value is supplied, Acad::eOutOfRange is returned. If the
// curve geometry is missing, Acad::eDegenerateGeometry is returned. In
// the event of an error, the curve and fit tolerance reference arguments
// are unchanged.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brtrav.h"


// forward class declarations
class AcGeCurve2d;
class AcGeCurve3d;
class AcGeNurbCurve2d;
class AcGeNurbCurve3d;
class AcBrLoop;
class AcBrEdge;
class AcBrFaceLoopTraverser;
class AcBrEdgeLoopTraverser;


class AcBrLoopEdgeTraverser : public AcBrTraverser
{
public:
    ACRX_DECLARE_MEMBERS(AcBrLoopEdgeTraverser);
    AcBrLoopEdgeTraverser();
    AcBrLoopEdgeTraverser(const AcBrLoopEdgeTraverser& src);
    ~AcBrLoopEdgeTraverser();

    // Assignment operator
    AcBrLoopEdgeTraverser& operator =   (const AcBrLoopEdgeTraverser& src);

    // Queries & Initialisers
    AcBr::ErrorStatus   setLoopAndEdge  (AcBrEdgeLoopTraverser& edgeLoop);
    AcBr::ErrorStatus   setLoop         (AcBrFaceLoopTraverser& loop);
    AcBr::ErrorStatus   getLoop         (AcBrLoop& loop) const;
    AcBr::ErrorStatus   setEdge         (AcBrEdge& edge);
    AcBr::ErrorStatus   getEdge         (AcBrEdge& edge) const;

    // Downward links
    // Edge usage by loop (n::1)
    AcBr::ErrorStatus   getEdgeOrientToLoop(Adesk::Boolean& orient) const;
    AcBr::ErrorStatus   getParamCurve   (AcGeCurve2d*& pcurve) const;
	AcBr::ErrorStatus	getOrientedCurve(AcGeCurve3d*& curve) const;
    AcBr::ErrorStatus   getParamCurveAsNurb(AcGeNurbCurve2d& nurb,
		                                 const double&    fitTolRequired = *(double*)NULL,
										 double&          fitTolAchieved = *(double*)NULL) const;
	AcBr::ErrorStatus	getOrientedCurveAsNurb(AcGeNurbCurve3d& nurb,
		                                 const double&    fitTolRequired = *(double*)NULL,
										 double&          fitTolAchieved = *(double*)NULL) const;

    // Queries & Initialisers
    AcBr::ErrorStatus   setLoopAndEdge  (const AcBrEdgeLoopTraverser& edgeLoop);
    AcBr::ErrorStatus   setLoop         (const AcBrFaceLoopTraverser& faceLoop);
    AcBr::ErrorStatus   setLoop         (const AcBrLoop& loop);
    AcBr::ErrorStatus   setEdge         (const AcBrEdge& edge);
};


#endif
