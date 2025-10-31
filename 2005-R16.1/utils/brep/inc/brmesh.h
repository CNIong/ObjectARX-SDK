#ifndef AC_BRMESH_H
#define AC_BRMESH_H 1
// (C) Copyright 1997-1999 by Autodesk, Inc.
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

