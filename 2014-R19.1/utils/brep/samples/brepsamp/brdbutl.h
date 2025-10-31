#ifndef AC_BRDBUTL_H
#define AC_BRDBUTL_H 1
// (C) Copyright 1996-1999 by Autodesk, Inc. 
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
// DESCRIPTION:
//
// Function prototype definitions for brdbutl.cpp.


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
