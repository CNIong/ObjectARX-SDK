//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
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

#ifndef _AD_DBID_OPS_H
#define _AD_DBID_OPS_H 1

#include "adesk.h"

class AcDbStub;

bool
c5ObjIdIsLessThan(const AcDbStub * lhs, const AcDbStub * rhs); 

bool
c5ObjIdIsGreaterThan(const AcDbStub * lhs, const AcDbStub * rhs); 

bool
c5ObjIdLessThanOrEqual(const AcDbStub * lhs, const AcDbStub * rhs); 

bool
c5ObjIdGreaterThanOrEqual(const AcDbStub * lhs, const AcDbStub * rhs); 

bool
c5ObjIdIsEqualTo(const AcDbStub * lhs, const AcDbStub * rhs); 

bool
c4ObjIdIsLessThan(Adesk::ULongPtr lhs, Adesk::ULongPtr rhs); 

bool
c4ObjIdIsGreaterThan(Adesk::ULongPtr lhs, Adesk::ULongPtr rhs); 

bool
c4ObjIdLessThanOrEqual(Adesk::ULongPtr lhs, Adesk::ULongPtr rhs); 

bool
c4ObjIdGreaterThanOrEqual(Adesk::ULongPtr lhs, Adesk::ULongPtr rhs); 

bool
c4ObjIdIsEqualTo(Adesk::ULongPtr lhs, Adesk::ULongPtr rhs); 

bool
c4ObjIdNotEqualTo(Adesk::ULongPtr lhs, Adesk::ULongPtr rhs); 

#endif

