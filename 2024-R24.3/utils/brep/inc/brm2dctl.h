#ifndef AC_BRM2DCTL_H
#define AC_BRM2DCTL_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrMesh2dControl class is the interface class for 2d mesh
// controls. All the functionality supported by this class is
// implemented by the class AcBrImpMesh2dControl.
//
// This class defines the functions that are specific to setting
// controls for the generation of 2d meshes. 2d mesh controls affect
// how a mesh grid is overlayed on the true surface and are applied
// at a later stage of standard textbook mesh generation algorithms
// than the global dimension-neutral controls in the base class, so
// they are treated more as hints to the mesh generator than as exact
// quantisations.
//
// An instantiated 2d mesh control object defaults to a complete set
// of valid controls. It is not necessary to invoke any member functions
// on this class or the base class unless a specific control or set
// of controls needs fine-tuning. All controls default to "off", which
// is the same as setting them with no argument supplied.
//
// Switch a control on by setting it to a legal value, and switch it
// off by setting with no argument supplied.
//
// The setMaxAspectRatio() control initialiser sets the maximum aspect
// ratio of width to height for a 2d mesh element. Values between zero
// and one invert the aspect ratio relationship to a height to width ratio.
// If the maxAspectRatio argument is not supplied or is set to zero, the
// default behaviour is to minimise the number of elements required to
// meet the curvature based criteria (i.e., maxAngTol and maxDistTol) (e.g.,
// generate long, shallow elements along the length of a cone surface).
// If a negative value is supplied, Acad::eOutOfRange is returned.
//
// The getMaxAspectRatio() control query returns the maximum aspect 
// ratio as a double.
//
// The setElementShape() control initialiser sets the element shape
// criteria. A request for all quadrilateral elements may generate some 
// triangles along the original edge boundaries due to node sharing 
// constraints for adjacent elements on neighbouring faces. A request
// for all polygonal elements will produce one element per face, with
// nodes and element edges corresponding to the discretisation of the
// boundary curves of the original face. If the elementShape argument 
// is not supplied or is set to AcBr::kDefault, the element shape
// defaults to one level of triangles along the original edges, with
// quadrilaterals used for the interior mesh (if there is one).
//
// The getElementShape() control query returns the element shape
// criteria as a dedicated AcBr::Element2dShape enum.

#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brmctl.h"


// forward class declarations
class AcBrMeshControl;


class AcBrMesh2dControl : public AcBrMeshControl
{
public:
    ACRX_DECLARE_MEMBERS(AcBrMesh2dControl);
    AcBrMesh2dControl();
    AcBrMesh2dControl(const AcBrMesh2dControl& src);
    ~AcBrMesh2dControl();
    
    // Assignment operator
    AcBrMesh2dControl&	operator =      (const AcBrMesh2dControl& src);

    // Queries & Initialisers
    AcBr::ErrorStatus   setMaxAspectRatio(const double& maxAspectRatio = *(double*)NULL);
    AcBr::ErrorStatus   getMaxAspectRatio(double& maxAspectRatio) const;
    AcBr::ErrorStatus   setElementShape	(const AcBr::Element2dShape& elementShape = *(AcBr::Element2dShape*)NULL);
    AcBr::ErrorStatus   getElementShape	(AcBr::Element2dShape& elementShape) const;
};


#endif