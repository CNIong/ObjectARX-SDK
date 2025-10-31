/////////////////////////////////////////////
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"

// This is command 'MYINPUT'
void asdkmyinput()
{
	// TODO: Implement the command
	int stat, iValue ;
	double rValue ;
	char kWord [133] ;

	acedInitGet (RSG_NONEG | RSG_NOZERO, "") ;

	if ( acedGetInt ("\nEnter an integer value: ", &iValue) != RTNORM )
		return ;

	rValue =12.0 ;
	acedInitGet (RSG_NOZERO, "PI A B C") ;
	stat =acedGetReal ("\nEnter a real value [PI/A/B/C] <C>: ", &rValue) ;
	switch (stat) {
		case RTCAN: // User termination
			return ;
		case RTKWORD: // Got a keyword
			if ( acedGetInput (kWord) != RTNORM )
				return ;
			if ( !strcmp ("PI", kWord) )
				rValue =3.14 ;
			else if ( !strcmp ("A", kWord) )
				rValue =10 ;
			else if ( !strcmp ("B", kWord) )
				rValue =11 ;
			else if ( !strcmp ("C", kWord) )
				rValue =12 ;
			break ;
		case RTNONE:
			acutPrintf ("\nTake default rValue %lf", rValue) ;
			break ;
		case RTNORM:
			break ;
		default:
			return ;
	}

	acutPrintf ("\nInteger : %d", iValue) ;
	acutPrintf ("\nReal    : %lf", rValue) ;
}

// This is command 'MYSELECT'
void asdkmyselect()
{
	// TODO: Implement the command
	ads_name en ;
	ads_point pt ;

	if ( acedEntSel (NULL, en, pt) != RTNORM )
		return ;

	acutPrintf ("\nYou selected entity ID: %ld", en [0]) ;
}

Acad::ErrorStatus createLayer (const char *layerName, AcDbObjectId &layerId) {
	Acad::ErrorStatus es ;
	AcDbLayerTable *pTable ;

	layerId =AcDbObjectId::kNull ;
	if ( (es =acdbHostApplicationServices ()->workingDatabase ()->getLayerTable (pTable, AcDb::kForRead)) == Acad::eOk ) {
		// Use the overload of AcDbLayerTable::getAt() that returns the id
		if ( (es =pTable->getAt (layerName, layerId, Adesk::kFalse)) != Acad::eOk ) {
			// Create a new layer table record using the layer name passed in
			AcDbLayerTableRecord *pLTRec =new AcDbLayerTableRecord ;
			pLTRec->setName (layerName) ;
			// Set other properties - color, linetype, state - if desired
			// this will require more input than this simple example provides
			if ( (es =pTable->upgradeOpen ()) == Acad::eOk ) {
				es =pTable->add (layerId, pLTRec) ;
				// Since the new layer was successfully added to the database,
				// close it - DON'T delete it
				pLTRec->close () ;
			} else {
				// The object is not part of the database, therefore we should
				// delete it to avoid a memory leak
				delete pLTRec ;
			}
		}
		pTable->close () ;
	}
	return (es) ;
}

Acad::ErrorStatus createBlockRecord (const char *name) {
	// First, check if a block of the same name already exists
	// by verifying in the current database block table.
	AcDbBlockTable *pBlockTable ;
	// Open the block table for read
	Acad::ErrorStatus es ;
	if ( (es =acdbHostApplicationServices ()->workingDatabase ()->getBlockTable (pBlockTable, AcDb::kForRead)) != Acad::eOk )
		return (es) ;

	if ( pBlockTable->has (name) == Adesk::kTrue ) {
		pBlockTable->close () ;
		return (Acad::eDuplicateKey) ;
	}
	// Now we know the block does not exist, so we create it
	// using the name passed in.
	AcDbBlockTableRecord *pBlockTableRecord =new AcDbBlockTableRecord ;
	pBlockTableRecord->setName (name) ;
	// To keep it simple, we use the origin for the insertion point
	pBlockTableRecord->setOrigin (AcGePoint3d::kOrigin) ;
	// Open the block table for write
	// since we are adding a new block definition
	if ( (es =pBlockTable->upgradeOpen ()) != Acad::eOk ) {
		delete pBlockTableRecord ;
		pBlockTable->close () ;
		return (es) ;
	}
	// Add the new block table record to the block table.
	// For now, the block table record is empty.
	if ( (es =pBlockTable->add (pBlockTableRecord)) != Acad::eOk ) {
		// The block table record has not been added
		// to the block table, so we have to delete it.
		pBlockTable->close();
		delete pBlockTableRecord;
		return (es) ;
	}
	pBlockTable->close () ;
	// Now the block table record is in the database, but is empty
	// (has no sub-entity).
	// Note that after having been added to the database, an object or an entity
	// is implicitely opened for write.
	//
	// So we create the sub entities to append to the block
	// which will represent a "happy face":
	// the block should consist of a round yellow face (circle)
	// two blue eyes (circles) and a red mouth (arc)
	AcDbCircle *pFace =new AcDbCircle (AcGePoint3d::kOrigin, AcGeVector3d::kZAxis, 1.0) ;
	AcDbCircle *pLeftEye =new AcDbCircle (AcGePoint3d (0.33, 0.25, 0.0), AcGeVector3d::kZAxis, 0.1) ;
	AcDbCircle *pRightEye =new AcDbCircle (AcGePoint3d (-0.33, 0.25, 0.0), AcGeVector3d::kZAxis, 0.1) ;
	AcDbArc *pMouth =new AcDbArc (AcGePoint3d (0, 0.5, 0), 1.0, 3.141592 + (3.141592 * 0.3), 3.141592 + (3.141592 * 0.7)) ;
	// Set the color property.
	pFace->setColorIndex (2) ;
	pLeftEye->setColorIndex (5) ;
	pRightEye->setColorIndex (5) ;
	pMouth->setColorIndex (1) ;
	// add the entities to the new block table record
	if ( (es =pBlockTableRecord->appendAcDbEntity (pFace)) != Acad::eOk ) {
		delete pFace ;
		delete pLeftEye ;
		delete pRightEye ;
		delete pMouth ;
		pBlockTableRecord->erase () ;
		pBlockTableRecord->close () ;
		return (es) ;
	}
	pFace->close () ;

	if ( (es =pBlockTableRecord->appendAcDbEntity (pLeftEye)) != Acad::eOk ) {
		delete pLeftEye ;
		delete pRightEye ;
		delete pMouth ;
		pBlockTableRecord->erase () ;
		pBlockTableRecord->close () ;
		return (es) ;
	}
	pLeftEye->close () ;

	if ( (es =pBlockTableRecord->appendAcDbEntity (pRightEye)) != Acad::eOk ) {
		delete pRightEye ;
		delete pMouth ;
		pBlockTableRecord->erase () ;
		pBlockTableRecord->close () ;
		return (es) ;
	}
	pRightEye->close () ;

	if ( (es =pBlockTableRecord->appendAcDbEntity (pMouth)) != Acad::eOk ) {
		delete pMouth ;
		pBlockTableRecord->erase () ;
		pBlockTableRecord->close () ;
		return (es) ;
	}
	pMouth->close () ;

	pBlockTableRecord->close () ;

	return (Acad::eOk) ;
}

// This is command 'CREATE'
void asdkcreate()
{
	// TODO: Implement the command

	// Create a new layer named "USER"
	// createLayer returns the object ID of the newly created layer
	AcDbObjectId layerId ;
	if ( createLayer ("USER", layerId) != Acad::eOk ) {
		acutPrintf ("\nERROR: Couldn't create layer record.") ;
		return ;
	}
	// This is not always needed, but a call to 'applyCurDwgLayerTableChanges()'
	// will synchronize the newly created layer table change with the 
	// rest of the current DWG database.
	applyCurDwgLayerTableChanges () ;

	acutPrintf ("\nLayer USER successfully created.") ;

	// Create a new block definition named "EMPLOYEE"
	if ( createBlockRecord ("EMPLOYEE") != Acad::eOk )
		acutPrintf ("\nERROR: Couldn't create block record.") ;
	else
		acutPrintf ("\nBlock EMPLOYEE successfully created.") ;

}

// This is command 'SETLAYER'
void asdksetlayer()
{
	// TODO: Implement the command

	// Iterate through Model Space to find every instance of the EMPLOYEE block
	// When found, change its layer to "USER"
	Acad::ErrorStatus es ;
	AcDbBlockTable *pBlockTbl ;
	AcDbBlockTableRecord *pMS ;

	// Get the block table
	if ( (es =acdbHostApplicationServices ()->workingDatabase ()->getBlockTable (pBlockTbl, AcDb::kForRead)) != Acad::eOk ) {
		acutPrintf ("\nCouldn't open the block table!") ;
		return ;
	}
	// Get the Model Space record and open it for read.
	if ( (es =pBlockTbl->getAt (ACDB_MODEL_SPACE, pMS, AcDb::kForWrite)) != Acad::eOk ) {
		acutPrintf ("\nCouldn't get Model Space! Drawing corrupt.\n") ;
		pBlockTbl->close () ;
		return ;
	}
	pBlockTbl->close () ;

	// Declare the appropriate iterator type
	// Get the iterator from the object to be iterated through

	// In this case, the Model Space block table record will provide the iterator
	// start at the beginning of the record and skip deleted entities
	AcDbBlockTableRecordIterator *pBtrIter ;
	if ( (es =pMS->newIterator (pBtrIter) ) != Acad::eOk ) {
		acutPrintf ("\nCouldn't create Model Space iterator.") ;
		pMS->close () ;
		return ;
	}

	char *blockName ;
	AcDbEntity *pEnt ;
	AcDbBlockTableRecord *pCurEntBlock ;
	AcDbObjectId blockId ;

	for ( pBtrIter->start (); !pBtrIter->done () ; pBtrIter->step () ) {
		// First open each entity for read, just to check its class
		// if it's what we want, we can upgrade open later
		// Don't bother with erased entities
		if ( (es =pBtrIter->getEntity (pEnt, AcDb::kForRead)) != Acad::eOk ) {
			acutPrintf ("\nCouldn't open entity.");
			continue ;
		}
		if ( pEnt->isA() != AcDbBlockReference::desc () ) {
			pEnt->close () ;
			continue ;
		}
		// Get the insert's block table record and compare its name
		// to make sure we've got the right block.  If so, set the layer
		blockId =(AcDbBlockReference::cast (pEnt))->blockTableRecord () ;
		if ( acdbOpenObject ((AcDbObject *&)pCurEntBlock, blockId, AcDb::kForRead) == Acad::eOk ) {
			pCurEntBlock->getName(blockName); 
			if ( strcmp (blockName, "EMPLOYEE") == 0 ) {
				if ( pEnt->upgradeOpen () == Acad::eOk )
					// setLayer also has an overload that takes a layer ID
					// but to avoid global variables we specify the layer name
					pEnt->setLayer ("USER") ;
			}
			pCurEntBlock->close () ;
			acdbFree (blockName) ;
		}
		pEnt->close () ;
	}

	// delete, rather than close, the iterator object
	delete pBtrIter ;
	pMS->close () ;
}

