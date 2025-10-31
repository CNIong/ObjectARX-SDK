#ifndef AC_BRELEM_H
#define AC_BRELEM_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrElement class is the interface base class for mesh elements.
// All the functionality supported by this class is implemented by the
// class AcBrImpElement.
//
// This class defines the functions that are common to all dimensions
// of mesh elements, and cannot be directly set by the user as the
// initialisation requirements are only available internally at the
// time of a call to AcBrMesh::generate().
//
// An element is a minimal closed, ordered subset of connected nodes 
// in a mesh.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brment.h"


// forward class declarations
class AcBrMeshEntity;


class AcBrElement : public AcBrMeshEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcBrElement);
    virtual ~AcBrElement();
    
protected:
    AcBrElement();
    AcBrElement(const AcBrElement& src);
    AcBrElement&		operator =      (const AcBrElement& src);
};


#endif

