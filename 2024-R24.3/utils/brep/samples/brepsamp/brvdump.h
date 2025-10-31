//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Function prototype definitions for brvdump.cpp.

#ifndef AC_BRVDUMP_H
#define AC_BRVDUMP_H 1

#include "adesk.h"
#include "brgbl.h"
#include "brvtx.h"


// forward class declarations
class AcBrVertex;


AcBr::ErrorStatus   vertexDump      		(const AcBrVertex&);


#endif
