#ifndef AC_BRMESH_H
#define AC_BRMESH_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrMesh class is the interface base class for meshes. All
// the functionality supported by this class is implemented by
// the class AcBrImpMesh.
//
// This class defines the functions that are common to all dimensions
// of meshes, and cannot be instantiated as it has no meaning on
// its own.
//
// A mesh is a network of nodal approximations to curves, surfaces and
// volumes in a brep object (or subobject), and thus has associated
// geometry. The geometry, however, is stored at the individual
// elements and nodes, as are the mappings back to the original brep
// topology. Each supported dimension of meshing has its own associated
// class. General faceting is exposed through the AcBrMesh2d subclass.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brment.h"


// forward class declarations
class AcBrMeshEntity;


class AcBrMesh : public AcBrMeshEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcBrMesh);
    virtual ~AcBrMesh();

protected:
    AcBrMesh();
    AcBrMesh(const AcBrMesh&);
    AcBrMesh&           operator =      (const AcBrMesh&);
};


#endif

