//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Function prototype definitions for brbmesh.cpp.

#ifndef AC_BRBMESH_H
#define AC_BRBMESH_H 1

//#include "adesk.h"
#include "brgbl.h"
#include "brbrep.h"


// forward class declarations
class AcBrBrep;


AcBr::ErrorStatus   brepMesh		(const AcBrBrep&, Adesk::Boolean displayElements);
 

#endif
