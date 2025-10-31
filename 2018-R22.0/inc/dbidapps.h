//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2017 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// dbidapps.h
//
// DESCRIPTION:
//
// This file contains the inlined versions of the comparsion operators
// for the AcDbObjectId class, that are for use by adjacent applications.
// These operators call out to explicit functions, to allow behavioral
// modification of these operators between c4 and c5.  Presumably, the
// AutoCAD/adjacent app division of these operators will be collapsed back
// into dbid.h at a future date.
// 
// See dbid.cc for the body of the function calls.
// See dbid.h for further description of the AcDbObjectId types.
//
// Update (2jun2016): Inlines moved to dbid.h header. This file will be deleted soon..

#include "adesk.h"
#include "dbid.h"
#include "dbid_ops.h"
