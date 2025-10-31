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
#include <adscodes.h>
#include <aced.h>

#include <acdocman.h>

#include <dbsymtb.h>
#include <dbents.h>
#include <gepnt3d.h>
#include <acestext.h>
#include <migrtion.h>
#include "lab3utils.h"

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
		return;
	}

	es = createBlockRecord("EMPLOYEE");
	if (es != Acad::eOk)
	{
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

	// First, check if a block of the same name already exists
	// by verifying in the current database block table.
	//
	AcDbBlockTable* pBlockTable;
	// Open the block table for read
	//
	Acad::ErrorStatus es;
	es = acdbCurDwg()->getBlockTable(pBlockTable, AcDb::kForRead);
	if(es != Acad::eOk)
		return es;

	if (pBlockTable->has(name) == Adesk::kTrue)
	{
		pBlockTable->close();
		return Acad::eDuplicateKey;
	}

	// Now we know the block does not exist, so we create it
	// using the name passed in.
	//
	AcDbBlockTableRecord* pBlockTableRecord = new AcDbBlockTableRecord();
	if (!pBlockTableRecord)
	{
		pBlockTable->close();
		return Acad::eOutOfMemory;
	}
	pBlockTableRecord->setName(name);

	// To keep it simple, we use the origin for the insertion point
	//
	pBlockTableRecord->setOrigin(AcGePoint3d::kOrigin);

	// Open the block table for write
	// since we are adding a new block definition
	//
	es = pBlockTable->upgradeOpen();
	if(es != Acad::eOk)
	{
		delete pBlockTableRecord;
		pBlockTable->close();
		return es;
	}

	// Add the new block table record to the block table.
	// For now, the block table record is empty.
	//
	es = pBlockTable->add(pBlockTableRecord);
	pBlockTable->close();
	if(es != Acad::eOk)
	{
		// The block table record has not been added
		// to the block table, so we have to delete it.
		//
		delete pBlockTableRecord;
		return es ;
	}

	// Now the block table record is in the database, but is empty
	// (has no sub-entity).
	// Note that after having been added to the database, an object or an entity
	// is implicitely opened for write.
	//
	// So we create the sub entities to append to the block
	// which will represent a "happy face":
	// the block should consist of a round yellow face (circle)
	// two blue eyes (circles) and a red mouth (arc)

	AcDbCircle* pFace = new AcDbCircle(AcGePoint3d::kOrigin, AcGeVector3d::kZAxis, 1.0);
	AcDbCircle* pLeftEye = new AcDbCircle(AcGePoint3d(0.33, 0.25, 0.0), AcGeVector3d::kZAxis, 0.1);
	AcDbCircle* pRightEye = new AcDbCircle(AcGePoint3d(-0.33, 0.25, 0.0), AcGeVector3d::kZAxis, 0.1);
	AcDbArc* pMouth = new AcDbArc(AcGePoint3d(0, 0.5, 0), 1.0, PI + (PI * 0.3), PI + (PI * 0.7));
	if (!pFace || !pLeftEye || !pRightEye || !pMouth)
	{
		delete pFace;
		delete pLeftEye;
		delete pRightEye;
		delete pMouth;
		// We do not want to keep an empty block definition,
		// so we erase it
		//
		pBlockTableRecord->erase();
		// and we close it, because we witll have some hope to exit
		// properly.
		//
		pBlockTableRecord->close();
		return Acad::eOutOfMemory;
	}

	// Set the color property.
	//
	pFace->setColorIndex(2);
	pLeftEye->setColorIndex(5);
	pRightEye->setColorIndex(5);
	pMouth->setColorIndex(1);


	// add the entities to the new block table record
	if((es = pBlockTableRecord->appendAcDbEntity(pFace)) != Acad::eOk)
	{
		delete pFace;
		delete pLeftEye;
		delete pRightEye;
		delete pMouth;
		pBlockTableRecord->erase();
		pBlockTableRecord->close();
		return es;
	}
	pFace->close();

	if((es = pBlockTableRecord->appendAcDbEntity(pLeftEye)) != Acad::eOk)
	{
		delete pLeftEye;
		delete pRightEye;
		delete pMouth;
		pBlockTableRecord->erase();
		pBlockTableRecord->close();
		return es;
	}
	pLeftEye->close();

	if((es = pBlockTableRecord->appendAcDbEntity(pRightEye)) != Acad::eOk)
	{
		delete pRightEye;
		delete pMouth;
		pBlockTableRecord->erase();
		pBlockTableRecord->close();
		return es;
	}
	pRightEye->close();

	if((es = pBlockTableRecord->appendAcDbEntity(pMouth)) != Acad::eOk)
	{
		delete pMouth;
		pBlockTableRecord->erase();
		pBlockTableRecord->close();
		return es;
	}
	pMouth->close();

	pBlockTableRecord->close();

	return Acad::eOk;
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
//        acedRegCmds->addCommand("OARX_LAB3", "create", "create", ACRX_CMD_MODAL, create);
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