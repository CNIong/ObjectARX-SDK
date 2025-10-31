#ifndef AC_BRFACE_H
#define AC_BRFACE_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrFace class is the interface class for brep faces. All the
// functionality supported by this class is implemented by the class
// AcBrImpFace.
//
// This class defines the functions that are pertinent to the face
// level of a brep topology adjacency hierarchy, and thus serves as
// a mapping between an AutoCAD face subentity and AcBr. It is also
// used to set the first face of a global AcBrBrepFaceTraverser or
// the face owner of a loop list in AcBrFaceLoopTraverser.
//
// Faces are primary brep elements and thus have associated geometry
// (i.e., surfaces). This class provides an indirect link between AcGe
// and AcDb3dSolid, AcDbSurface, AcDbRegion and AcDbBody.
//
// The default constructor instantiates an empty object. The function
// isNull() returns kTrue on an object created this way. To set an
// AcBrFace, call set() with a subentity path that contains the object
// ID for an AutoCAD solid, surface, region or body along with its chain of
// transforms (using nested AcDbBlockReferences) and a face subentity.
//
// The getSurfaceType() surface type query is used to determine the best
// match between this face's underlying surface and the surface types
// supported in AcGe. The returned enum should match the surface type
// returned by the convertor function AcGeExternalSurface::isNativeSurface()
// (as invoked on the external surface extracted from the external
// bounded surface returned by AcBrFace::getSurface()), and thus enables
// efficient filtration of surfaces by type. If the surface type is not
// supported as a native type, AcGe::kExternalBoundedSurface is returned.
// If this face object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the subentity
// path was last set, eBrepChanged is returned. If the surface geometry
// is missing, Acad::eDegenerateGeometry is returned. In the event of an
// error, the surface type reference argument's value is unchanged and is
// thus meaningless.
//
// The getSurface() model space surface query returns this face's
// underlying surface as a subset AcGeExternalBoundedSurface (cast to
// the AcGeSurface base class), with the entire chain of transforms
// from the subentity path applied. The surface is subset to the
// uv range that results from projecting the face's model space
// bounding box onto the uv parameter space grid of the surface.
// Due to AcGe and underlying modeler restrictions, the subset
// may not be honoured on all surface types (particularly analytic,
// periodic surfaces). The surface is passed as a null AcGeSurface
// base class reference pointer for getSurface() to instantiate. If
// this face object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the
// subentity path was last set, eBrepChanged is returned. If the
// surface geometry is missing, Acad::eDegenerateGeometry is returned.
// If the AcGeSurface allocation comes back null, Acad::eOutOfMemory
// is returned. If the transform has non-uniform scaling,
// Acad::eCannotScaleNonUniformly is returned as a warning message,
// along with the untransformed surface. In the event of an error, 
// the surface reference pointer is unchanged and thus likely
// points to a null object.
//
// The getOrientToSurface() orientation query returns a simple Boolean
// indicating whether the outside of this face is in the direction of
// the surface normal (kTrue) or in the opposite direction (kFalse),
// at any position on the surface. If this face object is uninitialised, 
// eUninitialisedObject is returned. If the associated AutoCAD object 
// has been modified since the subentity path was last set, eBrepChanged
// is returned. If the surface geometry is missing, Acad::eDegenerateGeometry
// is returned. In the event of an error, the orientation reference
// argument's value is unchanged and is thus meaningless.
//
// The getPointRelationToFace() and getCurveRelationToFace()
// set-membership classifications are deprecated in favour of
// getPointContainment() and getLineContainment().
//
// The getSurfaceAsNurb() model space surface query returns this
// face's underlying surface as a subset AcGeNurbSurface, with the
// entire chain of transforms from the subentity path applied. The
// surface is converted to a NURB (if necessary) using the supplied
// fit tolerance (adjusted by the inverse scale factor from the nested
// transforms, in order to be in the same evaluation space as this
// face) and is subset to the uv range that results from projecting
// the face's model space bounding box onto the uv parameter space grid
// of the surface. The achieved fit tolerance (if supplied) is returned
// as a double, with the maximum scale factor applied from the nested
// transforms. The surface is instantiated by the user and passed by
// reference for getSurfaceAsNurb() to set. If this face object is
// uninitialised, eUninitialisedObject is returned. If the associated
// AutoCAD object has been modified since the subentity path was last
// set, eBrepChanged is returned. If the fitTolRequired argument is not
// supplied or is set to zero, the default fit tolerance is used. If a
// negative value is supplied, Acad::eOutOfRange is returned. If the
// surface geometry is missing, Acad::eDegenerateGeometry is returned. 
// If the transform has non-uniform scaling, Acad::eCannotScaleNonUniformly 
// is returned as a warning message, along with the untransformed surface.
// In the event of an error, the surface and fit tolerance reference
// arguments are unchanged.
//
// The getSurfaceAsTrimmedNurbs() model space trimmed surface query
// converts this face's underlying surface to a trimmed representation,
// and returns this as an array of AcGeExternalBoundedSurface pointers
// (along with the array size, as numNurbs), with the entire chain of
// transforms from the subentity path applied. The surface is converted
// to a NURB (if necessary) and split along its seams (if crossed by
// the face boundaries). The surface array is passed as a null
// AcBrExternalBoundedSurface reference pointer for
// getSurfaceAsTrimmedNurbs() to instantiate. It is the user's
// responsibility to delete[] the returned array of surfaces. If this
// face object is uninitialised, eUninitialisedObject is returned. If
// the associated AutoCAD object has been modified since the subentity
// path was last set, eBrepChanged is returned. If the surface geometry
// is missing, eMissingGeometry is returned. In the event of an error,
// the surface array reference pointer is unchanged and thus likely
// points to a null array, and the number of nurbs is zero.
//
// The getShell() upward adjacency query returns the shell that is
// bounded by this face (always unique). The shell is instantiated by 
// the caller and passed by reference for getShell() to set. If this
// face object is uninitialised, eUninitialisedObject is returned. If 
// the associated AutoCAD object has been modified since the subentity
// path was last set, eBrepChanged is returned. If the shell is missing,
// Acad::eNotInDatabase is returned. In the event of an error, the shell
// reference object is unchanged and is thus likely to be uninitialised.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "gegbl.h"
#include "brgbl.h"
#include "brent.h"


// forward class declarations
class AcGeSurface;
class AcGeNurbSurface;
class AcGeExternalBoundedSurface;
class AcGeCurve3d;
class AcGePoint3d;
class AcBrShell;


class AcBrFace : public AcBrEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcBrFace);
    AcBrFace();
    AcBrFace(const AcBrFace& src);
    ~AcBrFace();

    // Assignment operator
    AcBrFace&           operator =      (const AcBrFace& src);

    // Geometry
    AcBr::ErrorStatus   getSurfaceType  (AcGe::EntityId& type) const;
    AcBr::ErrorStatus   getSurface      (AcGeSurface*& surface) const;
    AcBr::ErrorStatus   getOrientToSurface(Adesk::Boolean& bOrientToSurface) const;
    AcBr::ErrorStatus	getArea			(double&       area, 
                                         const double *tolRequired = NULL,
                                         double       *tolAchieved = NULL) const;

    // Set-Membership Classification Note: deprecated functions)
    AcBr::ErrorStatus   getPointRelationToFace(const AcGePoint3d& point, AcBr::Relation& relation) const;
    AcBr::ErrorStatus   getCurveRelationToFace(const AcGeCurve3d& curve, AcBr::Relation& relation) const;

    // Geometry
    AcBr::ErrorStatus   getSurfaceAsNurb(AcGeNurbSurface& nurb,
                                         const double    *fitTolRequired = NULL,
                                         double          *fitTolAchieved = NULL) const;
    AcBr::ErrorStatus   getSurfaceAsTrimmedNurbs(Adesk::UInt32&                numNurbs,
                                                 AcGeExternalBoundedSurface**& ppNurbs) const;

    // Upward links
    // Shell usage of face (1::1)
    AcBr::ErrorStatus   getShell        (AcBrShell& shell) const;
};


#endif

