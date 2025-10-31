#ifndef AC_BRGBL_H
#define AC_BRGBL_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBr struct contains enumerated types that are unique to the 
// AcBr library and which are used as return codes or on the argument 
// list of local class functions. Abbreviations and aliases (e.g.,
// for obsoletised values) are exported in brgblabb.h.
//
// The ErrorStatus enum is returned by all non Boolean valued functions.
// The error code may be either a global AutoCAD error code (as listed 
// in the Acad::ErrorStatus enum), cast to the local AcBr::ErrorStatus 
// enum, or a local boundary representation library error code. The 
// local error codes are defined using a starting base of 3000, so 
// as not to conflict with the AutoCAD, Mechanical API or Autodesk 
// Mechanical Desktop error codes.
//
// The Relation enum captures the relation of geometry objects
// (i.e., points and curves) to bounded geometry subsets of a solid
// (e.g., the relation of a point to a solid, or the relation of
// a curve to a face in which it may be partially or completely
// embedded). The kInside and kOutside values are relative to the
// geometric bounds of the queried topology object, as determined
// by the direction of the normals along the object's boundary.
//
// The Element2dShape enum controls the shape of elements generated 
// by a 2d mesh. It is only relevant to the mesh filter. A 1d mesh 
// (corresponding to the discretization of the boundary curves of 
// the original face) can be emulated by specifying kAllPolygons.
//
// The LoopType enum classifies a loop as interior/exterior/etc.
// Peripheral loops are kLoopExterior, and there is only one such 
// loop per face (by industry convention). Holes are returned as 
// kLoopInterior, and there may be several per face (providing there 
// is also an exterior loop). Cones and cylinders (whether with an 
// elliptical or circular base) have at least two base loops (if 
// they are complete in both u and v), which are returned as 
// kLoopWinding vs. kLoopExterior due to the restriction of there 
// being just one exterior loop (along with the fact that neither 
// base loop is a hole). Singularities (such as the apex of a cone) 
// are returned as kLoopUnclassified. All loops on spheric and toric 
// surfaces, as well as closed periodic nurbs, return kLoopUnclassified.
//
// The ValidationLevel enum sets the level of validation for an AcBr* 
// object. If kFullValidation (the default upon object instantiation) 
// is specified, every function that accesses the brep topology 
// (directly or indirectly) first checks the associated AutoCAD 
// database object to see if it has been modified since the AcBr* 
// object was last set This is an expensive operation, but guarantees 
// all brep data is within scope. If kNoValidation is specified, the 
// database is not checked unless it is critical to the completion of
// the function's tasks. This is more efficient, but does not guarantee 
// the brep data is within scope. Setting the validation level on an
// object by object basis prevents any collsions between multiply 
// loaded apps.
//
// The ShellType enum classifies a shell as interior/exterior/etc.
// Peripheral shells are returned as kShellExterior, and there is only 
// one such shell per brep or region (by industry convention). Voids
// are returned as kShellInterior, and there may be several per brep 
// or complex (providing there is also an exterior shell).


#include "adesk.h"
#include "acadstrc.h"


struct AcBr
{
    enum ErrorStatus    { eOk                   = 0,	// status OK; no errors

                          eNotImplementedYet    = Acad::eNotImplementedYet, 
                          eNotApplicable        = Acad::eNotApplicable, 
                          eInvalidInput         = Acad::eInvalidInput, 
                          eOutOfMemory          = Acad::eOutOfMemory, 
                          eNullObjectPointer    = Acad::eUnrecoverableErrors, 
                          eWrongObjectType      = Acad::eWrongObjectType, 
                          eWrongSubentityType   = Acad::eWrongSubentityType,
                          eNullObjectId         = Acad::eNullObjectId, 
                          eNullSubentityId      = Acad::eInvalidIndex, 
                          eObjectIdMismatch     = Acad::eWrongDatabase, 
                          eTopologyMismatch     = Acad::eWrongDatabase, 
                          eUnsuitableGeometry   = Acad::eAmbiguousOutput, 
                          eMissingGeometry      = Acad::eDegenerateGeometry, 
						  eMissingSubentity		= Acad::eNotInDatabase, 
						  eInvalidObject		= Acad::eUnrecoverableErrors, 
						  eAmbiguousOutput		= Acad::eAmbiguousOutput, 
						  
                          eBrepChanged          = 3008,	// Associated AutoCAD object has been modified since
														//   the AcBr* object was last set
                          eUnsuitableTopology   = 3013,	// topology is unsuitable for this class or function
						  eDegenerateTopology	= 3020,	// topology hierarchy is incomplete
						  eUninitialisedObject  = 3021	// AcBr* object is uninitialised
	};

    enum Relation       { kUnknown              = 0,	// point or curve containment cannot be determined, or
														//   curve is partially inside and partially outside
                          kOutside              = 1,	// point or curve is outside geometry bounds
                          kInside               = 2,	// point is inside geometry bounds, or curve is fully
														//   inside or on geometry bounds
                          kBoundary             = 3,	// point is on geometry bounds
                          kCoincident           = 4,	// obsolete; now returns kInside
                          kTangent              = 5,	// obsolete; now returns kUnknown
                          kIntersect            = 6		// obsolete; now returns kUnknown
                        };

    enum Element2dShape	{ kDefault              = 0,	// use system defaults (i.e., by surface type)
						  kAllPolygons			= 1,	// attempt to only produce ngons, where n>4                  
						  kAllQuadrilaterals    = 2,	// attempt to only produce 4gons (complete quadrangles)
                          kAllTriangles         = 3		// attempt to only produce 3gons (approx. equilateral)
	                    };

	enum LoopType		{ kUnclassified		    = 0,	// obsolete; now returns kLoopUnclassified
		                  kExterior             = 1,	// obsolete; now returns kLoopExterior
						  kInterior				= 2,	// obsolete; now returns kLoopInterior
						  kWinding				= 3,	// obsolete; now returns kLoopWinding
						  kLoopUnclassified		= kUnclassified,
														// loop type cannot be determined at this time, or
														//   is ambiguous (such as for loops embedded in
														//   spherical, toroidal or periodic nurb surfaces)
		                  kLoopExterior         = kExterior,
														// loop is on peripheral boundary (there is exactly
														//   one, unless the loop is on a conic surface; in
														//   which case there are winding loops instead)
						  kLoopInterior			= kInterior,
														// loop is a hole in the interior of a face (there
														//   may be more than one interior loop per surface)
						  kLoopWinding			= kWinding
														// loop is winding on a conic surface (there is one
														//   winding loop for each non-degenerate base)
						};

	enum ValidationLevel { kFullValidation		= 0,	// validate the brep on every query (default)
		                   kNoValidation		= 1		// never validate the brep (NOTE: potentially unsafe)
	                     };

	enum ShellType		{ kShellUnclassified	= 0,	// shell type cannot be determined at this time
		                  kShellExterior        = 1,	// shell is on peripheral boundary of region or brep
						  kShellInterior		= 2		// shell is a void in the interior of a region or brep
														//   (there may be more than one interior shell per solid)
						};
};


#endif

