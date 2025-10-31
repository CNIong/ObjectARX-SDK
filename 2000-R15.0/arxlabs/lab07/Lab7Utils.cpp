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
#include <dbapserv.h>
#include <dbents.h>
#include <dbsymtb.h>
#include <adscodes.h>
#include <acdb.h>
#include <dbents.h>
#include <actrans.h>
#include "Lab7ObjectReactor.h"
#include "lab7Utils.h"

//global variables
extern AsdkLab7ObjectReactor* pAsdkLab7ObjectReactor;

#define DICT "OARXLABS_EMPLOYEE_DICT"
#define DETAILS "DETAILS"

//get the extension dictionary of object pObj,
//where the EmployeeDetails object is stored.
Acad::ErrorStatus getExtDictEmpOfObj(AcDbDictionary*& pExtDictEmp, AcDbObject* pObj)
{
    Acad::ErrorStatus es;

    //get object id of extension dictionary
    AcDbObjectId idO;
    if ((idO = pObj->extensionDictionary()) == AcDbObjectId::kNull)
        return Acad::eNullObjectId;

    //open the extension dictionary read only
    AcDbObject* pO;
    if ((es = acdbOpenAcDbObject(pO, idO, AcDb::kForRead)) != Acad::eOk)
        return es;

    AcDbDictionary* pExtDict = AcDbDictionary::cast(pO);
    if (!pExtDict) {
        //should never happen
        pO->close();
        return Acad::eNotApplicable;
    }

    //get DICT dictionary
    if ((es = pExtDict->getAt(DICT, (AcDbObject*&)pExtDictEmp, AcDb::kForRead))
                                  != Acad::eOk) {
        pExtDict->close();
        return es;
    }
    pExtDict->close();

    return Acad::eOk;
}

Adesk::Boolean isAnInsertOfEmployee( /*[in]*/const AcDbObject * pObj, 
									/*[ou]*/AcDbBlockReference*& pInsert)
{
	pInsert = AcDbBlockReference::cast(pObj);
	if(!pInsert)
		return Adesk::kFalse;

	AcDbObjectId blockId = pInsert->blockTableRecord();
	AcDbBlockTableRecord* pBlock;
	Acad::ErrorStatus es;
	es = acdbOpenAcDbObject((AcDbObject* &)pBlock, blockId, AcDb::kForRead);
	if(es != Acad::eOk)
		  acrx_abort("!%s@%d: %s", __FILE__, __LINE__, acadErrorStatusText(es));

    char *blockName;
    pBlock->getName(blockName);
    pBlock->close();

	if (stricmp(blockName, "employee")) {
		acdbFree ( blockName );
        return Adesk::kFalse;   //not an employee
	}
	acdbFree ( blockName );
	return Adesk::kTrue;

}

// This function looks for all block references 
// of the block "employee" in Model Space.
// If the insert has not been attached our object reactor,
// we attach it.
//
Acad::ErrorStatus 
attachReactorToAllEmployee(bool attach)
{
	Acad::ErrorStatus es;
	AcDbBlockTable* pBlockTable;
	// get the block table of the current database
	//
	es = acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);
	if(es != Acad::eOk)
		 return es;

	AcDbBlockTableRecord* pModelSpace;
	// get Model Space for read.
	//
	es = pBlockTable->getAt(ACDB_MODEL_SPACE, pModelSpace, AcDb::kForRead);
	pBlockTable->close();
	if(es != Acad::eOk)
		return es;
	AcDbBlockTableRecordIterator *pIterator;
	es = pModelSpace->newIterator(pIterator);
	if(es != Acad::eOk)
	{
		pModelSpace->close();
		return es;
	}

	AcDbEntity *pEnt;
	// To satisfy our isAnInsertOfEmployee() function,
	// we will not use this pointer.
	//
	AcDbBlockReference *pInsert;
	for( ; !pIterator->done(); pIterator->step())
	{
		// the entity does not need to be open for write to
		// add or remove a transient reactor
		//
		es = pIterator->getEntity(pEnt, AcDb::kForRead);
		if(!isAnInsertOfEmployee(pEnt, pInsert))
		{
			pEnt->close();
			continue;
		}
		if(attach)
			pEnt->addReactor(pAsdkLab7ObjectReactor);
		else
			pEnt->removeReactor(pAsdkLab7ObjectReactor);
		pEnt->close();
	}
	delete pIterator;
	pModelSpace->close();
	return Acad::eOk;
}


