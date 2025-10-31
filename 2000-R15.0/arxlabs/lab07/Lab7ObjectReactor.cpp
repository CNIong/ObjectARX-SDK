//
// (C) Copyright 1999 by Autodesk, Inc. 
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
#include "acdb.h"
#include "adslib.h"
#include "dbents.h"
#include "aced.h"
#include "dbmain.h"
#include "dbdict.h"
#include "dbsymtb.h"
#include "Lab7ObjectReactor.h"
#include "lab7Utils.h"
#include <string.h>

#include "Lab7PerDocData.h"

/////////////////////////////////////////////////////
//object reactor notifications

void AsdkLab7ObjectReactor::openedForModify(const AcDbObject* dbObj)
{
    if (!chEmployeesInfo.EditCommand || chEmployeesInfo.NoObjReactor)
        return;

    // dbObj should be of kind AcDbBlockReference
	// and of name "employee", The check is not abosultely necessary:
	// since our application is adding the reactor to employee objects
	// only, we know this notificatin can only come from such an object.
	// However, since we will need to cast to an AcDbBlockReference
	// pointer anyway to get the position, we will use our utility
	// function as defined in lab7Utils.cpp.
	// This functoin checks if the passed object is a a reference of the
	// employee block, and will return a pointer to this reference.
	//
    AcDbBlockReference *pInsert;
	
	if(!isAnInsertOfEmployee(dbObj, pInsert))
		return;

    //store the objectID and the position
	chEmployeesInfo.ChangedIds.append(pInsert->objectId());
	chEmployeesInfo.EmployeePositions.append(pInsert->position());
}
