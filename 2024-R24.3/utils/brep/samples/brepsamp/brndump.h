//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Function prototype definitions for brndump.cpp.

#ifndef AC_BRNDUMP_H
#define AC_BRNDUMP_H 1

#include "adesk.h"
#include "brgbl.h"
#include "brnode.h"
#include "gept3dar.h"


// forward class declarations
class AcBrNode;


AcBr::ErrorStatus   nodeDump			(const AcBrNode&);
AcBr::ErrorStatus   nodeDisplay         (const AcBrNode&, AcGePoint3dArray&);


#endif
