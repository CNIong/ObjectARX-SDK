#ifndef AC_BREDGE_H
#define AC_BREDGE_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrEdge class is the interface class for brep edges. All the
// functionality supported by this class is implemented by the class
// AcBrImpEdge.
//
// This class defines the functions that are pertinent to the edge
// level of a brep topology adjacency hierarchy, and thus serves as
// a mapping between an AutoCAD edge subentity and AcBr. It is also
// used to set the first edge of an edge list in AcBrLoopEdgeTraverser
// or the edge owner of a loop list in AcBrEdgeLoopTraverser.
//
// Edges are primary brep elements and thus have associated geometry
// (i.e., curves). This class provides an indirect link between AcGe
// and AcDb3dSolid, AcDbSurface, AcDbRegion and AcDbBody.
//
// The default constructor instantiates an empty object. The function
// isNull() returns kTrue on an object created this way. To set an
// AcBrEdge, call set() with a subentity path that contains the object
// ID for an AutoCAD solid, surface, region or body along with its chain of
// transforms (using nested AcDbBlockReferences) and an edge subentity.
// If the edge is free or otherwise unembedded (such as a wire edge),
// eUnsuitableTopology is returned by set().
//
// The getCurveType() curve type query is used to determine the best
// match between this edge's underlying curve and the curve types
// supported in AcGe. The returned enum should match the curve type
// returned by the convertor function AcGeExternalCurve3d::isNativeCurve()
// (as invoked on the curve returned by AcBrEdge::getCurve()), and
// thus enables efficient filtration of curves by type. If the curve
// type is not supported as a native type, AcGe::kExternalCurve3d is
// returned. If this edge object is uninitialised, eUninitialisedObject 
// is returned. If the associated AutoCAD object has been modified since
// the subentity path was last set, eBrepChanged is returned. If the
// curve geometry is missing, Acad::eDegenerateGeometry is returned. In
// the event of an error, the curve type reference argument's value is
// unchanged and is thus meaningless.
//
// The getCurve() model space curve query returns this edge's
// underlying curve as an unoriented, subset AcGeExternalCurve3d
// (cast to the AcGeCurve3d base class), with the entire chain of
// transforms from the subentity path applied. The curve is subset,
// in its natural orientation, to the edge's bounding vertices
// (i.e., the edge's orientation with respect to the curve is not
// applied to the curve parameterisation). The curve is passed as
// a null AcGeCurve3d base class reference pointer for getCurve()
// to instantiate. If this edge object is uninitialised,
// eUninitialisedObject is returned. If the associated AutoCAD 
// object has been modified since the subentity path was last set,
// eBrepChanged is returned. If the curve geometry is missing,
// Acad::eDegenerateGeometry is returned. If the AcGeCurve3d allocation
// comes back null, Acad::eOutOfMemory is returned. If the transform
// has non-uniform scaling, Acad::eCannotScaleNonUniformly is returned
// as a warning message, along with the untransformed curve. In the
// event of an error, the curve reference pointer is unchanged and 
// thus likely points to a null object.
//
// The getOrientToCurve() orientation query returns a simple Boolean
// indicating whether the natural orientation of this edge from vertex1
// to vertex2 is in the direction of the curve parameterisation (kTrue)
// or in the opposite direction (kFalse). The orientation may be directly
// applied to the underlying curve using AcGeCurve3d::reverseParam().
// If this edge object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the subentity
// path was last set, eBrepChanged is returned. If the curve geometry
// is missing, Acad::eDegenerateGeometry is returned. In the event of an
// error, the orientation reference argument's value is unchanged and is 
// thus meaningless.
//
// The getVertex1() downward adjacency query returns the start vertex
// of this edge in its natural orientation from vertex1 to vertex2.
// The vertex is instantiated by the caller and passed by reference 
// for getVertex1() to set. If this edge object is uninitialised,
// eUninitialisedObject is returned. If the associated AutoCAD object
// has been modified since the subentity path was last set, eBrepChanged
// is returned. Null vertices represent specialised rather than missing
// topology, so eDegenerateTopology is returned. If the vertex fails to
// map to a valid subentity ID, Acad::eNotInDatabase is returned. In the
// event of an error, the vertex reference object is unchanged and
// is thus likely to be uninitialised.
//
// The getVertex2() downward adjacency query returns the end vertex
// of this edge in its natural orientation from vertex1 to vertex2.
// The vertex is instantiated by the caller and passed by reference 
// for getVertex2() to set. If this edge object is uninitialised,
// eUninitialisedObject is returned. If the associated AutoCAD object
// has been modified since the subentity path was last set, eBrepChanged
// is returned. Null vertices represent specialised rather than missing
// topology, so eDegenerateTopology is returned. If the vertex fails to
// map to a valid subentity ID, Acad::eNotInDatabase is returned. In the
// event of an error, the vertex reference object is unchanged and
// is thus likely to be uninitialised.
//
// The getPointRelationToEdge() and getCurveRelationToEdge()
// set-membership classifications are deprecated in favour of
// getPointContainment() and getLineContainment().
//
// The getCurveAsNurb() model space curve query returns this edge's
// underlying curve as an unoriented, subset AcGeNurbCurve3d, with
// the entire chain of transforms from the subentity path applied.
// The curve is converted to a NURB (if necessary) using the supplied
// fit tolerance (adjusted by the inverse scale factor from the nested
// transforms, in order to be in the same evaluation space as this
// edge) and is subset, in its natural orientation, to the edge's
// bounding vertices (i.e., the edge's orientation with respect to
// the curve is not applied to the curve parameterisation). The 
// achieved fit tolerance (if supplied) is returned as a double, with
// the maximum scale factor applied from the nested transforms. The
// curve is instantiated by the user and passed by reference pointer
// for getCurveAsNurb() to set. If this edge object is uninitialised,
// eUninitialisedObject is returned. If the associated AutoCAD
// object has been modified since the subentity path was last set,
// eBrepChanged is returned. If the fitTolRequired argument is not
// supplied or is set to zero, the default fit tolerance is used.
// If a negative value is supplied, Acad::eOutOfRange is returned.
// If the curve geometry is missing, Acad::eDegenerateGeometry is
// returned. In the event of an error, the curve and fit tolerance
// reference arguments are unchanged.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "gegbl.h"
#include "brgbl.h"
#include "brent.h"


// forward class declarations
class AcGePoint3d;
class AcGeCurve3d;
class AcGeNurbCurve3d;
class AcBrVertex;


class AcBrEdge : public AcBrEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcBrEdge);
    AcBrEdge();
    AcBrEdge(const AcBrEdge& src);
    ~AcBrEdge();

    // Assignment operator
    AcBrEdge&           operator =      (const AcBrEdge& src);

    // Geometry
    AcBr::ErrorStatus   getCurveType    (AcGe::EntityId& type) const;
    AcBr::ErrorStatus   getCurve        (AcGeCurve3d*& curve) const;
    AcBr::ErrorStatus   getOrientToCurve(Adesk::Boolean& bOrientToCurve) const;

    // Downward links
    // Vertex usage by edge (2::1, 1::1 or 0::1)
    AcBr::ErrorStatus   getVertex1      (AcBrVertex& vertex) const;
    AcBr::ErrorStatus   getVertex2      (AcBrVertex& vertex) const;

	// Set-Membership Classification (Note: deprecated functions)
    AcBr::ErrorStatus   getPointRelationToEdge(const AcGePoint3d& point, AcBr::Relation& relation) const;
    AcBr::ErrorStatus   getCurveRelationToEdge(const AcGeCurve3d& curve, AcBr::Relation& relation) const;

    // Geometry
    AcBr::ErrorStatus   getCurveAsNurb	(AcGeNurbCurve3d& nurb,
                                         const double    *fitTolRequired = NULL,
                                         double          *fitTolAchieved = NULL) const;
};


#endif

