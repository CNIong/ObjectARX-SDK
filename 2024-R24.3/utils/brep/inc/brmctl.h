#ifndef AC_BRMCTL_H
#define AC_BRMCTL_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrMeshControl class is the interface base class for mesh
// controls. All the functionality supported by this class is
// implemented by the class AcBrImpMeshControl.
//
// This class defines the functions that are common to all mesh
// control derived classes, and cannot be instantiated as it has
// no meaning on its own. It is derived from AcRxObject in order
// to provide full service run-time type-checking, etc.
//
// Mesh controls affect the quantisation and shape of element
// generation in a mesh. Mesh controls are inexact and may possibly
// conflict, so are listed in the order in which they are applied
// by standard textbook mesh generation algorithms. Granularity
// controls (i.e., maximum initial subdivisions and maximum node
// spacing) are fairly coarse and only affect the initial
// discretisation steps. Except for cases of extreme curvature
// in NURB surfaces, element density in the interior mesh should
// fairly accurately reflect the control settings; whereas the
// density of elements along the surface boundaries may be much
// higher than requested due to node sharing with adjacent faces.
//
// Depending on the type of surface(s), it generally is necessary
// to set only one control. Distance tolerance has the largest impact
// on the mesh, and is especially useful for effecting high element
// density in areas of tight curvature. Angle tolerance is most useful
// for complex surfaces w/ knobs, whereas node spacing is mostly used
// for planar surfaces as it is the only way to guarantee that the
// surface is subdivided into more than one element.
//
// Switch a control on by setting it to a legal value, and switch it
// off by setting with no argument supplied.
//
// The AcRxObject::isEqualTo() equivalence function is redefined to
// check content equality between two mesh control objects. kTrue is
// returned when the object is valid and has been equated to another
// valid mesh control object of the same subclass. Equivalence is
// defined as having the same control settings.
//
// The setMaxSubdivisions() control initialiser sets the maximum number
// of subdivisions in any one dimension (equivalent to the number of
// internal uv grid lines), which is imposed by the mesh grid overlay on
// the original geometry. This control is very inexact in this release
// due to the underlying modeler's algorithm (which applies subdivisions
// recursively). As a result, the actual maximum resulting subdivisions
// in either u or v will be somewhere between the two adjacent powers
// of two surrounding the specified number of subdivisions. If the
// maxSubdivisions argument is not supplied or is set to zero, the
// default behaviour is based on mesh dimension and surface type (e.g.,
// for a planar face in a 2d mesh, no interior nodes are inserted). 
//
// The getMaxSubdivisions() control query returns the maximum number 
// of subdivisions as an unsigned 32-bit integer.
//
// The setMaxNodeSpacing() control initialiser sets the maximum node
// spacing in world coordinates. Dimension-specific controls that are
// applied later in the mesh generation algorithm may also alter the
// node spacing; especially near the boundaries of the original
// geometry. Node spacing directly affects the size of the generated
// elements. The proper value to set is dependent on model size. If
// the maxNodeSpacing argument is not supplied or is set to zero, the
// default behaviour is to ignore distance and defer to curvature based
// node spacing (cf. setMaxAngTol and setMaxDistTol). If a negative
// value is supplied, Acad::eOutOfRange is returned.
//
// The getMaxNodeSpacing() control query returns the maximum node
// spacing as a double.
//
// The setAngTol() control initialiser sets the maximum angle tolerance
// (measured in radians) between the normals evaluated at any two nodes
// in a mesh element. In most cases, values between 15 and 25 degrees
// give acceptable results. The proper value to set is generally
// independent of model size. Angle tolerance, in conjunction with
// distance tolerance, effects curvature based node spacing. If the
// angTol argument is not supplied or is set to zero, the default
// behaviour is to use a value that will generate a rather coarse mesh.
// If a negative value is supplied, Acad::eOutOfRange is returned.
//
// The getAngTol() control query returns the maximum angle tolerance
// as a double.
//
// The setDistTol() control initialiser sets the maximum allowable
// distance in world coordinates between a mesh element and the original
// geometry (as measured at the mid-edges and centroid of each element).
// In a 2d mesh, this is the same as the distance in world coordinates
// from a point on the true surface to the closest point on any of its
// approximating 2d elements. The proper value to set is dependent on
// model size. Distance tolerance, in conjunction with angle tolerance,
// effects curvature based node spacing. If the distTol argument is
// not supplied or is set to zero, the default behaviour is to set it
// to 5% of the maximum extent of the bounding box, or (in the case of
// non-zero maxNodeSpacing) to ignore this control entirely. If a
// negative value is supplied, Acad::eOutOfRange is returned.
//
// The getDistTol() control query returns the maximum distance tolerance
// as a double.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"


// forward class declarations
class AcBrImpMeshControl;


class AcBrMeshControl : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcBrMeshControl);
    virtual ~AcBrMeshControl();

    // Equivalence                    
    Adesk::Boolean      isEqualTo       (const AcRxObject* other) const;
    
    // Queries & Initialisers

    // Maximum number of grid lines on a face in each direction.
    // 0 means the default maximum 512.
    AcBr::ErrorStatus   setMaxSubdivisions(const Adesk::UInt32& maxSubs = *(Adesk::UInt32*)NULL); 
	AcBr::ErrorStatus   getMaxSubdivisions(Adesk::UInt32& maxSubs) const;
    AcBr::ErrorStatus   setMaxNodeSpacing(const double& maxNodeSpace = *(double*)NULL);
    AcBr::ErrorStatus   getMaxNodeSpacing(double& maxNodeSpace) const;
    AcBr::ErrorStatus   setAngTol		(const double& angTol = *(double*)NULL);
    AcBr::ErrorStatus   getAngTol		(double& angTol) const;
    AcBr::ErrorStatus   setDistTol		(const double& distTol = *(double*)NULL);
    AcBr::ErrorStatus   getDistTol		(double& distTol) const;

protected:
    AcBrMeshControl();
    AcBrMeshControl(const AcBrMeshControl& src);
    AcBrMeshControl&	operator =      (const AcBrMeshControl& src);

    AcBrImpMeshControl*	mpImp;
};


#endif