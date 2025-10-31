//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Function prototype definitions for brfdump.cpp.

#ifndef AC_BRFDUMP_H
#define AC_BRFDUMP_H 1

#include "adesk.h"
#include "brgbl.h"
#include "brface.h"


// forward class declarations
class AcBrFace;


AcBr::ErrorStatus   faceDump        		(const AcBrFace&);


#endif
