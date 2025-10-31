//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Function prototype definitions for brbdump.cpp.

#ifndef AC_BRBDUMP_H
#define AC_BRBDUMP_H 1

#include "brgbl.h"
#include "brbrep.h"


// forward class declarations
class AcBrBrep;


AcBr::ErrorStatus   brepDump       		(const AcBrBrep&);
 

#endif
