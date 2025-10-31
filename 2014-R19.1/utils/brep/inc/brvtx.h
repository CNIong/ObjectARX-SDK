//
#ifndef AC_BRVTX_H
#define AC_BRVTX_H 1
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
// The AcBrVertex class is the interface class for brep vertices.
// All the functionality supported by this class is implemented by
// the class AcBrImpVertex.
//
// This class defines the functions that are pertinent to the vertex
// level of a brep topology adjacency hierarchy, and thus serves as
// a mapping between an AutoCAD vertex subentity and AcBr. It is
// also used to set the vertex owner of a vertex edge list in
// AcBrVertexEdgeTraverser, or the vertex-loop in
// AcBrVertexLoopTraverser.
//
// Vertices are primary brep elements and thus have associated geometry
// (i.e., points). This class provides an indirect link between AcGe
// and AcDb3dSolid, AcDbSurface, AcDbRegion and AcDbBody.
//
// The default constructor instantiates an empty object. The function
// isNull() returns kTrue on an object created this way. To set an
// AcBrVertex, call set() with a subentity path that contains the object
// ID for an AutoCAD solid, surface, region or body along with its chain of
// transforms (using nested AcDbBlockReferences) and a vertex subentity.
// Singularities cannot be used to directly set an AcBrVertex object,
// as they are represented in AutoCAD as an edge subentity; use AcBrEdge
// instead. They may, however, be queried using an AcBrLoopVertexTraverser.
//
// The getPoint() model space point query is deprecated in favour of the
// efficient new getPoint() query which sets an already-instantiated point.
//
// The getPointRelationToVertex() and getCurveRelationToVertex()
// set-membership classifications are deprecated in favour of
// getPointContainment() and getLineContainment().
//
// The getPoint() model space point query returns this vertex' underlying
// point as an AcGePoint3d, with the entire chain of transforms from the
// subentity path applied. The point is instantiated by the caller and
// passed by reference pointer for getPoint() to set. If this vertex
// object is uninitialised, eUninitialisedObject is returned. If the
// associated AutoCAD object has been modified since the subentity path
// was last set, eBrepChanged is returned. If the point geometry is
// missing, Acad::eDegenerateGeometry is returned. In the event of an
// error, the point reference argument's value is unchanged.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brent.h"


// forward class declarations
class AcGePoint3d;
class AcGeCurve3d;


class AcBrVertex : public AcBrEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcBrVertex);
    AcBrVertex();
    AcBrVertex(const AcBrVertex& src);
    ~AcBrVertex();

    // Assignment operator
    AcBrVertex&         operator =      (const AcBrVertex& src);

    // Geometry (Note: deprecated function)
    AcBr::ErrorStatus   getPoint        (AcGePoint3d*& point) const;

	// Set-Membership Classification (Note: deprecated functions)
    AcBr::ErrorStatus   getPointRelationToVertex(const AcGePoint3d& point, AcBr::Relation& relation) const;
    AcBr::ErrorStatus   getCurveRelationToVertex(const AcGeCurve3d& curve, AcBr::Relation& relation) const;

    // Geometry
    AcBr::ErrorStatus   getPoint        (AcGePoint3d& point) const;
};


#endif

