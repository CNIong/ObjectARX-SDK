//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Function prototype definitions for brfmesh.cpp.

#ifndef AC_BRFMESH_H
#define AC_BRFMESH_H 1

#include "adesk.h"
#include "brgbl.h"
#include "brface.h"


// forward class declarations
class AcBrFace;


AcBr::ErrorStatus   faceMesh		(const AcBrFace&, Adesk::Boolean displayElements);


#endif
