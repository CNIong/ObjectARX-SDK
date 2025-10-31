#ifndef _AD_DBID_OPS_H
#define _AD_DBID_OPS_H 1
//
// (C) Copyright 1995-2007 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
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

