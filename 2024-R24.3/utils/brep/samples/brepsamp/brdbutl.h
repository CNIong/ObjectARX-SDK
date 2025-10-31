//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Function prototype definitions for brdbutl.cpp.

#ifndef AC_BRDBUTL_H
#define AC_BRDBUTL_H 1

#include "adesk.h"
#include "acdb.h"
#include "dbsubeid.h"


// forward class declarations
class AcDbEntity;
class AcDbObjectId;
class AcDbFullSubentPath;


Acad::ErrorStatus   createEntity	(AcDbEntity*& pEntity);
Acad::ErrorStatus   selectEntity	(const AcDb::SubentType& subType,
									 AcDbFullSubentPath&     subPath);

Acad::ErrorStatus   addToDatabase	(AcDbEntity* pEnt, AcDbObjectId& objId);

Acad::ErrorStatus	dbOpenTransaction(Adesk::Boolean& ownTransaction);
Acad::ErrorStatus	dbCloseTransaction(Adesk::Boolean& ownTransaction);
Acad::ErrorStatus	dbAbortTransaction(Adesk::Boolean& ownTransaction);


#endif
