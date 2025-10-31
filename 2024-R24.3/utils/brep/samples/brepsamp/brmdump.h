//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Function prototype definitions for brmdump.cpp.

#ifndef AC_BRMDUMP_H
#define AC_BRMDUMP_H 1

#include "adesk.h"
#include "brgbl.h"
#include "brmesh2d.h"


// forward class declarations
class AcBrMesh2d;


AcBr::ErrorStatus   meshDump			(const AcBrMesh2d&);
AcBr::ErrorStatus   meshDisplay         (const AcBrMesh2d&);
 

#endif
