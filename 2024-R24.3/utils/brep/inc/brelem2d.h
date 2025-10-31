#ifndef AC_BRELEM2D_H
#define AC_BRELEM2D_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrElement2d class is the interface class for linear, first-
// order two-dimensional elements in a mesh. All the functionality
// supported by this class is implemented by the class AcBrImpElement2d.
//
// This class defines the functions that are pertinent to the 2d
// element level of a mesh, and cannot be directly set by the user
// as the initialisation requirements are only available internally
// at the time of a call to AcBrMesh2d::generate().
//
// A 2d element is a planar approximation of a subset of a bounded
// surface and thus has no directly associated geometry. It represents
// a polygonal (i.e., closed) set of at least three co-planar nodes in
// a mesh (Note that the associated node coordinates can be used to
// instantiate an AcGePlane). A mapping back to the original brep
// topology is provided in the form of a backpointer to the face which
// generated this element (cf. AcBrMeshEntity::getEntityAssociated()).
//
// This class generally is accessed by the user via a mesh element 
// traverser. The only way to delete the element referenced by this class
// from the mesh data cache is to delete the mesh object that owns it,
// or to regenerate the mesh.
//
// The set() element data initialiser is for internal use only. It is used
// to set this mesh element's internal data using an unexported type.
//
// The get() element data query is for internal use only. It retrieves
// this mesh element's internal data using an unexported type.
//
// The getNormal() element normal query returns the normalised model
// space normal vector computed on the plane defined by the element 
// nodes traversed in a clockwise direction. The normal vector is 
// returned as an AcGeVector3d, with the entire chain of transforms 
// from the original face applied. The vector is instantiated by the 
// caller and passed by reference for getNormal() to set. If this mesh 
// element object is uninitialised, eUninitialisedObject is returned. 
// If there are fewer than three nodes in the element, or if the nodes
// are colinear (as measured to within a tolerance of 1.0e-10 on the
// dot products of the vectors from one node to the next), Acad::
// eDegenerateGeometry is returned. In the event of an error, the 
// normal vector reference argument's value is unchanged.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brelem.h"


// forward class declarations
class AcGeVector3d;
class AcBrElement;
class AcBrElement2dData;


class AcBrElement2d : public AcBrElement
{
public:
    ACRX_DECLARE_MEMBERS(AcBrElement2d);
    AcBrElement2d();
    AcBrElement2d(const AcBrElement2d& src);
    ~AcBrElement2d();
    
    // Assignment operator
    AcBrElement2d&		operator =      (const AcBrElement2d& src);

    // Queries & Initialisers
    AcBr::ErrorStatus   set				(AcBrElement2dData* data);
	AcBr::ErrorStatus	get				(AcBrElement2dData*& data) const;

    // Geometry (for stereolithography support)
    AcBr::ErrorStatus   getNormal		(AcGeVector3d& normal) const;
};


#endif

