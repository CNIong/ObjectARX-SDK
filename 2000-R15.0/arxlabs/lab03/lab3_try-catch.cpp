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
#include <aced.h>
#include <dbsymtb.h>
#include <dbents.h>
#include <gepnt3d.h>
#include <acestext.h>
#include <dbapserv.h>
#include <migrtion.h>
#include "lab3utils.h"


// This file: lab3Main try-catch.cpp is very similar to lab3main.cpp
// it simply introduces the use of try and catch blocks to facilite
// error handeling in the createBlockRecord function.
// This version also introduces the ARXOK macro that, in conjunction with
// try and catch blocks, reduces significantly the code necessary 
// for Error checking.
// Note that this macro is just an example of what is possible, and
// does not pretend to be the only and best solution. The usage fo smart
// pointers, for example, could also contribute greatly to simplify the code.
//

#define ARXOK(what) if ((what)!=Acad::eOk) throw (what);

Acad::ErrorStatus createBlockRecord(/*[in]*/const char* name);
void setInsertLayer();

void create()
{
	Acad::ErrorStatus es;
	AcDbObjectId layerId;

	// create a new layer named "USER"
	// createLayer returns the object ID of the newly created layer
	// This is good ARX programming practice, though it is not used
	// subsequently in this lab

	es = createLayer("USER", layerId);
	if (es != Acad::eOk)
	{
		acutPrintf("\nERROR:  %s\nCouldn't create layer record.", acadErrorStatusText(es));
	}

	es = createBlockRecord("EMPLOYEE");
	if (es != Acad::eOk)
	{
		if(es == Acad::eDuplicateKey)
			acutPrintf("Block already defined.\n");
		else
			acutPrintf("\nERROR:  %s\nCouldn't create block record.", acadErrorStatusText(es));
	}
	else
	{
		acutPrintf("\nBlock EMPLOYEE successfully created.");
	}
}

void setInsertLayer()
{
	// Iterate through Model Space to find every instance of the EMPLOYEE block
	// When found, change its layer to "USER"
	
	Acad::ErrorStatus es;
	AcDbBlockTable* pBlockTbl;
	AcDbBlockTableRecord* pMS;

	if ((es = acdbCurDwg()->getBlockTable(pBlockTbl, AcDb::kForRead)) == Acad::eOk)
	{
	//Get the Model Space record and open it for read.
        if ((es = pBlockTbl->getAt(ACDB_MODEL_SPACE, pMS, AcDb::kForWrite)) != Acad::eOk)
		{
			acrx_abort("\nCouldn't get Model Space! Drawing corrupt.\n");
		}
	    pBlockTbl->close();
    }

	// declare the appropriate iterator
	// get the iterator from the object to be iterated through

	// in this case, the Model Space block table record will provide the iterator
	// start at the beginning of the record and skip deleted entities

	AcDbBlockTableRecordIterator* pBtrIter;
	if ((es = pMS->newIterator(pBtrIter)) != Acad::eOk)
	{
		acutPrintf("\nCouldn't create Model Space iterator: %s", acadErrorStatusText(es));
		return;
	}

	char* blockName;  
	AcDbEntity* pEnt;
	AcDbBlockTableRecord* pCurEntBlock;
	AcDbObjectId blockId;

	for (pBtrIter->start(); !pBtrIter->done(); pBtrIter->step())
	{
		// first open each entity for read, just to check its class
		// if it's what we want, we can upgrade open later
		// Don't bother with erased entities
		if ((es = pBtrIter->getEntity(pEnt, AcDb::kForRead)) != Acad::eOk)
		{
			acutPrintf("\nCouldn't open entity:  %s", acadErrorStatusText(es));
			continue;
		}

		// check isf the entity is an instance of type AcDbBlockReference
		if (pEnt->isA() != AcDbBlockReference::desc())
		{
			pEnt->close();
			continue;
		}
		
		// get the insert's block table record and compare its name
		// to make sure we've got the right block.  If so, set the layer
		blockId = (AcDbBlockReference::cast(pEnt))->blockTableRecord();
		if (acdbOpenObject((AcDbObject*&)pCurEntBlock, blockId, AcDb::kForRead) == Acad::eOk)
		{
			pCurEntBlock->getName(blockName);
			if (strcmp(blockName, "EMPLOYEE") == 0)
			{
				if (pEnt->upgradeOpen() == Acad::eOk)
					// setLayer also has an overload that takes a layer ID
					// but to avoid global variables we specify the layer name
					pEnt->setLayer("USER");
			}
			pCurEntBlock->close();
			acdbFree ( blockName );
		}
		pEnt->close();
	}

	// delete, rather than close, the iterator object
	delete pBtrIter;
    pMS->close();
	return;

}


Acad::ErrorStatus createBlockRecord(/*[in]*/const char* name)
{
	AcDbCircle* pFace = NULL;
	AcDbCircle* pLeftEye = NULL;
	AcDbCircle* pRightEye = NULL;
	AcDbArc* pMouth = NULL;
	AcDbBlockTable* pBlockTable = NULL;
	AcDbBlockTableRecord* pBlockTableRecord = NULL;

	try
	{
		// First, check if a block of the same name already exists
		// by verifying in the current database block table.
		//
		// Open the block table for read
		//
		ARXOK(acdbCurDwg()->getBlockTable(pBlockTable, AcDb::kForRead));

		if (pBlockTable->has(name) == Adesk::kTrue)
		{
			pBlockTable->close();
			return Acad::eDuplicateKey;
		}

		// Now we know the block does not exist, so we create it
		// using the name passed in.
		//
		pBlockTableRecord = new AcDbBlockTableRecord();
		if (!pBlockTableRecord)
			throw Acad::eOutOfMemory;

		pBlockTableRecord->setName(name);

		// To keep it simple, we use the origin for the insertion point
		//
		pBlockTableRecord->setOrigin(AcGePoint3d::kOrigin);

		// Open the block table for write
		// since we are adding a new block definition
		//
		ARXOK(pBlockTable->upgradeOpen());

		// Add the new block table record to the block table.
		// For now, the block table record is empty.
		//
		ARXOK(pBlockTable->add(pBlockTableRecord));
		pBlockTable->close();
		pBlockTable = NULL;

		// Now the block table record is in the database, but is empty
		// (has no sub-entity).
		// Note that after having been added to the database, an object or an entity
		// is implicitely opened for write.
		//
		// So we create the sub entities to append to the block
		// which will represent a "happy face":
		// the block should consist of a round yellow face (circle)
		// two blue eyes (circles) and a red mouth (arc)
		//
		pFace = new AcDbCircle(AcGePoint3d::kOrigin, AcGeVector3d::kZAxis, 1.0);
		pLeftEye = new AcDbCircle(AcGePoint3d(0.33, 0.25, 0.0), AcGeVector3d::kZAxis, 0.1);
		pRightEye = new AcDbCircle(AcGePoint3d(-0.33, 0.25, 0.0), AcGeVector3d::kZAxis, 0.1);
		pMouth = new AcDbArc(AcGePoint3d(0, 0.5, 0), 1.0, PI + (PI * 0.3), PI + (PI * 0.7));
		if (!pFace || !pLeftEye || !pRightEye || !pMouth)
		{
			delete pFace;
			delete pLeftEye;
			delete pRightEye;
			delete pMouth;
			throw Acad::eOutOfMemory;
		}

		// Set the color property.
		//
		pFace->setColorIndex(2);
		pLeftEye->setColorIndex(5);
		pRightEye->setColorIndex(5);
		pMouth->setColorIndex(1);

		ARXOK(pBlockTableRecord->appendAcDbEntity(pFace));
		ARXOK(pBlockTableRecord->appendAcDbEntity(pLeftEye));
		ARXOK(pBlockTableRecord->appendAcDbEntity(pRightEye));
		ARXOK(pBlockTableRecord->appendAcDbEntity(pMouth));

		pFace->close();
		pLeftEye->close();
		pRightEye->close();
		pMouth->close();

		pBlockTableRecord->close();
		return Acad::eOk;
	}

	catch(const Acad::ErrorStatus es)
	{

		if(pBlockTable)
			pBlockTable->close();

		if(pBlockTableRecord)
			// if the id is NULL, it means that the object
			// is not in the database and that we can sefely delete it
			if(pBlockTableRecord->objectId() == AcDbObjectId::kNull)
				delete pBlockTableRecord;
			else
			{
				pBlockTableRecord->erase();
				pBlockTableRecord->close();
			}
		
		if(pFace)
			if(pFace->objectId() == AcDbObjectId::kNull)
				delete pFace;
			else
				pFace->close();
		if(pLeftEye)
			if(pLeftEye->objectId() == AcDbObjectId::kNull)
				delete pLeftEye;
			else
				pLeftEye->close();
		if(pRightEye)
			if(pRightEye->objectId() == AcDbObjectId::kNull)
				delete pRightEye;
			else
				pRightEye->close();
		if(pMouth)
			if(pMouth->objectId() == AcDbObjectId::kNull)
				delete pMouth;
			else
				pMouth->close();

		return es;
	}

}

//This is the entry point that makes a simple DLL an ARX.
//This entry point must be exported either by means of a def file
//or by the means of _declspec
extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt) 
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        //An ARX application is locked to memory by default.
        //You must make the following function call to unlock
        //it.
        acrxDynamicLinker->unlockApplication(pkt); 
		//support MDI
		acrxDynamicLinker->registerAppMDIAware(pkt);
        //register the command
        acedRegCmds->addCommand("OARX_LAB3", "create", "create", ACRX_CMD_MODAL, create);
        acedRegCmds->addCommand("OARX_LAB3", "setLayer", "setLayer", ACRX_CMD_MODAL, setInsertLayer);
        break;
    case AcRx::kUnloadAppMsg:
        //remove the command group so that AutoCAD won't call us
        //when we are not here.
        acedRegCmds->removeGroup("OARX_LAB3");
        break;
    }
    return AcRx::kRetOK;
}