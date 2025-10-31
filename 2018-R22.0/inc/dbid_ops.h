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
// dbid_ops.h
//
// DESCRIPTION:
//
// This file declares functions called by the app versions of the comparison
// operators of class AcDbObjectId.  This file currently contains the c4 
// versions of these functions and will be updated to contain c5 versions
// of these functions.  Adjacent apps that compile against c4 will thus not
// experience behavioral changes when c5 AutoCAD ships.  However, by 
// recompiling against c5, adjacent apps can pick up the modified behavior 
// of these operators, as the operators themselves will be modified to
// call the new functions in the header dbidapps.h
//
// Presumably, this file will be eliminated, and these functions will be
// collapsed back into dbid.h as inlines, at a later date.
//
// For further description of the AcDbObjectId types, see dbid.h
//
// Update (2jun2016): old c4ObjIdXXX() c5ObjIdXXX() methods are removed. This file
// will be deleted soon..

#ifndef _AD_DBID_OPS_H
#define _AD_DBID_OPS_H 1

#include "adesk.h"
#include "AcDbCore2dDefs.h"

#endif

