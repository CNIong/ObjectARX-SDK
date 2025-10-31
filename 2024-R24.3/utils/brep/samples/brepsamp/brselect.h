//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Function prototype definitions for brselect.cpp.

#ifndef AC_BRSELECT_H
#define AC_BRSELECT_H 1

#include "adesk.h"
#include "acdb.h"
#include "brgbl.h"


// forward class declarations
class AcBrEntity;


AcBr::ErrorStatus	selectEntityByType(AcBrEntity*&      pEnt,
									   AcDb::SubentType& subType);


#endif
