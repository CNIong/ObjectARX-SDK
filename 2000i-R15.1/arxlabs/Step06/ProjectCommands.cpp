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

// This is command 'ADDENTRY'
void asdkaddentry()
{
	// TODO: Implement the command

	//  When this command invoked at the first time
	//  it creates two objects: an AcDbDictionary object in the named
	//  objects dictionary (NOD) and an empty AcDbXrecord object to represent
	//  an individual entry. The XRecord will be replaced in a later lab by a
	//  custom object AsdkEmployeeDetails.
	//  Later invokations of the command just adds new XRecords to this
	//  dictionary.
	//  Storing these entries in the NOD will enable us to query all
	//  employees in the db quickly without iterating through all
	//  AcDbBlockTableRecords in the database.

	// Prompt the use for the an id
	char strID [133] ;
	if ( acedGetString (0, "Enter employee name: ", strID) != RTNORM )
		return ;

	// Get the named object dictionary
	AcDbDictionary *pNOD ;
	if ( acdbHostApplicationServices()->workingDatabase ()->getNamedObjectsDictionary (pNOD, AcDb::kForRead) != Acad::eOk ) {
		acutPrintf ("\nUnable to open the NOD! Aborting...") ;
		return ;
	}

	// See if our dictionary is already there
	AcDbObjectId idO ;
	AcDbDictionary *pEmployeeDict =NULL ;
	if ( pNOD->getAt ("ASDK_EMPLOYEE_DICTIONARY", idO) == Acad::eKeyNotFound ) {
		// Create it if not
		if ( pNOD->upgradeOpen () != Acad::eOk ) {
			acutPrintf ("\nCannot open NOD for Write!") ;
			pNOD->close () ;
			return ;
		}
		pEmployeeDict =new AcDbDictionary ;
		// Add it to the NOD
		if ( pNOD->setAt ("ASDK_EMPLOYEE_DICTIONARY", pEmployeeDict, idO) != Acad::eOk ) {
			// We are really unlucky
			acutPrintf ("\nCannot add our dictionary in the AutoCAD NOD!") ;
			// Clean-up memory and abort
			delete pEmployeeDict ;
			pNOD->close () ;
			return ;
		}
	} else {
		// Get it for write if it is already there
		AcDbObject *pO ;
		if ( acdbOpenAcDbObject (pO, idO, AcDb::kForWrite) != Acad::eOk ) {
			acutPrintf ("\nCannot open the object for write.") ;
			pNOD->close () ;
			return ;
		}
		// Check if someone has else has created an entry with our name
		// that is not a dictionary. This should never happen as long as
		// I use the registered developer RDS prefix.
		if ( (pEmployeeDict =AcDbDictionary::cast (pO)) == NULL ) {
			acutPrintf ("\nEntry found in the NOD, but it is not a dictionary.") ;
			pO->close () ;
			pNOD->close () ;
			return ;
		}
	}
	pNOD->close () ;
	// Check if a record with this key is already there
	if ( pEmployeeDict->getAt (strID, idO) == Acad::eOk ) {
		acutPrintf ("\nThis employee is already registered.") ;
		pEmployeeDict->close () ;
		return ;
	}
	// Let's add the new record. Append an empty xrecord.
	AcDbXrecord *pEmployeeEntry =new AcDbXrecord ;
	if ( pEmployeeDict->setAt (strID, pEmployeeEntry, idO) != Acad::eOk ) {
		acutPrintf ("\nFailed to add the new employee in the dictionary.") ;
		delete pEmployeeEntry ;
		pEmployeeDict->close () ;
		return ;
	}
	pEmployeeEntry->close () ;
	pEmployeeDict->close () ;
}

// This is command 'REMOVEENTRY'
void asdkremoveentry()
{
	// TODO: Implement the command

	// Prompt the user for the an employee name
	char strID [133] ;
	if ( acedGetString (0, "Enter employee name: ", strID) != RTNORM )
		return ;
	// Get the named object dictionary
	AcDbDictionary *pNOD ;
	if ( acdbHostApplicationServices()->workingDatabase ()->getNamedObjectsDictionary (pNOD, AcDb::kForRead) != Acad::eOk ) {
		acutPrintf ("\nUnable to open the NOD! Aborting...") ;
		return ;
	}
	// See if our dictionary is already there
	AcDbObjectId idO ;
	AcDbObject* pO;
	if ( pNOD->getAt ("ASDK_EMPLOYEE_DICTIONARY", idO) != Acad::eOk ) {
		acutPrintf ("\nNo dictionary, no entry to remove...") ;
		pNOD->close () ;
		return ;
	}
	// Get employee dictionary for read
	if ( acdbOpenAcDbObject (pO, idO, AcDb::kForRead) != Acad::eOk ) {
		acutPrintf ("\nCannot open the object for write.") ;
		pNOD->close () ;
		return ;
	}
	// Check if someone has else has created an entry with our name
	// that is not a dictionary. This should never happen as long as
	// I use the registered developer RDS prefix.
	AcDbDictionary *pEmployeeDict ;
	if ( (pEmployeeDict =AcDbDictionary::cast (pO)) == NULL ) {
		acutPrintf ("\nEntry found in the NOD, but it is not a dictionary.") ;
		pO->close () ;
		pNOD->close () ;
		return ;
	}
	pNOD->close () ;
	// Check if a record with this key is there
	if ( pEmployeeDict->getAt (strID, idO) != Acad::eOk ) {
		acutPrintf ("\nEntry not found.") ;
		pEmployeeDict->close () ;
		return ;
	}
	pEmployeeDict->close () ;
	// Get it for write 
	if ( acdbOpenAcDbObject (pO, idO, AcDb::kForWrite) != Acad::eOk ) {
		acutPrintf ("\nEntry cannot be opened for write.") ;
		return ;
	}
	// And erase it
	pO->erase () ;
	pO->close () ;
}

// This is command 'LISTENTRIES'
void asdklistentries()
{
	// TODO: Implement the command

	// Get the named object dictionary
	AcDbDictionary *pNOD ;
	if ( acdbHostApplicationServices()->workingDatabase ()->getNamedObjectsDictionary (pNOD, AcDb::kForRead) != Acad::eOk ) {
		acutPrintf ("\nUnable to open the NOD! Aborting...") ;
		return ;
	}
	// See if our dictionary is already there
	AcDbObjectId idO ;
	AcDbObject* pO;
	if ( pNOD->getAt ("ASDK_EMPLOYEE_DICTIONARY", idO) != Acad::eOk ) {
		acutPrintf ("\nNo dictionary, no entry to remove...") ;
		pNOD->close () ;
		return ;
	}
	// Get employee dictionary for read
	if ( acdbOpenAcDbObject (pO, idO, AcDb::kForRead) != Acad::eOk ) {
		acutPrintf ("\nCannot open the object for write.") ;
		pNOD->close () ;
		return ;
	}
	// Check if someone has else has created an entry with our name
	// that is not a dictionary. This should never happen as long as
	// I use the registered developer RDS prefix.
	AcDbDictionary *pEmployeeDict ;
	if ( (pEmployeeDict =AcDbDictionary::cast (pO)) == NULL ) {
		acutPrintf ("\nEntry found in the NOD, but it is not a dictionary.") ;
		pO->close () ;
		pNOD->close () ;
		return ;
	}
	pNOD->close () ;

	AcDbDictionaryIterator *pIter ;
	if ( (pIter =pEmployeeDict->newIterator (AcRx::kDictCollated)) != NULL ) {
		for ( ; !pIter->done () ;pIter->next () ) {
			// Print name
			acutPrintf ("*Employee: %s\n", pIter->name ()) ;
		}
		delete pIter ;
	}

	pEmployeeDict->close () ;
}

// This is command 'ADDDETAIL'
void asdkadddetail()
{
	// TODO: Implement the command

	// Prompt the user for the employee details
	ads_name ename ;
	ads_point pt ;
	// Get the data from the user
	if ( acedEntSel ("Select employee: ", ename, pt) != RTNORM )
		return ;
	// Do a quick check
	// a more comprehensive check could include 
	// whether we already have the detail object on this candidate
	AcDbObjectId idO ;
	if ( acdbGetObjectId (idO, ename) != Acad::eOk )
		return ;
	AcDbObject *pO ;
	if ( acdbOpenAcDbObject (pO, idO, AcDb::kForWrite) != Acad::eOk )
		return ;
	if ( !pO->isKindOf (AcDbBlockReference::desc ()) ) {
		acutPrintf ("\nThis is not a block reference.") ;
		pO->close () ;
		return ;
	}
	// Get user input
	int id, cubeNumber ;
	char strFirstName [133] ;
	char strLastName [133] ;
	if (   acedGetInt ("Enter employee ID: ", &id) != RTNORM
		|| acedGetInt ("Enter cube number: ", &cubeNumber) != RTNORM
		|| acedGetString (0, "Enter employee first name: ", strFirstName) != RTNORM
		|| acedGetString (0, "Enter employee last name: ", strLastName) != RTNORM
	) {
		pO->close () ;
		return ;
	}
	// Get the extension dictionary
	if ( (idO =pO->extensionDictionary ()) == AcDbObjectId::kNull ) {
		if ( pO->createExtensionDictionary () != Acad::eOk ) {
			pO->close () ;
			acutPrintf ("\nFailed to create ext. dictionary.") ;
			return ;
		}
		idO =pO->extensionDictionary () ;
	}
	// We do not need the block reference object anymore.
	pO->close () ;
	// Make sure you open erased extension dictionaries
	// you may need to unerase them
	AcDbDictionary *pExtDict ;
	if ( acdbOpenAcDbObject ((AcDbObject *&)pExtDict, idO, AcDb::kForWrite, Adesk::kTrue) != Acad::eOk ) {
		acutPrintf ("\nFailed to open ext. dictionary.") ;
		return ;
	}
	// Unerase the ext. dictionary if it was erased
	if ( pExtDict->isErased () )
		pExtDict->erase (Adesk::kFalse) ;
	// See if our dictionary is already there
	AcDbDictionary *pEmployeeDict ;
	if ( pExtDict->getAt ("ASDK_EMPLOYEE_DICTIONARY", idO) == Acad::eKeyNotFound ) {
		// Create it if not
		pEmployeeDict =new AcDbDictionary ;
		Acad::ErrorStatus es ;
		if ( (es =pExtDict->setAt ("ASDK_EMPLOYEE_DICTIONARY", pEmployeeDict, idO)) != Acad::eOk ) {
			pExtDict->close () ;
			acutPrintf ("\nFailed to create the 'Employee' dictionary.") ;
			return ;
		}
	} else {
		// Open our dictionary for write if it is already there
		if ( acdbOpenAcDbObject (pO, idO, AcDb::kForWrite) != Acad::eOk ) {
			pExtDict->close () ;
			acutPrintf ("\nFailed to open the 'Employee' dictionary.") ;
			return ;
		}
		// Check if someone has else has created an entry with our name
		// that is not a dictionary.
		if ( (pEmployeeDict =AcDbDictionary::cast (pO)) == NULL ) {
			pO->close () ;
			pExtDict->close () ;
			acutPrintf ("\nThe entry is not a dictionary") ;
			return ;
		}
	}
	// We do not need the ext. dictionary object anymore
	pExtDict->close () ;
	// Check if a record with this key is already there
	if ( pEmployeeDict->getAt ("DETAILS", idO) == Acad::eOk ) {
		pEmployeeDict->close () ;
		acutPrintf ("\nDetails already assign to that 'Employee' object.") ;
		return ;
	}
	// Create an EmployeeDetails object and set its fields
	AsdkEmployeeDetails *pEmployeeDetails =new AsdkEmployeeDetails ;
	pEmployeeDetails->setID (id) ;
	pEmployeeDetails->setCube (cubeNumber) ;
	pEmployeeDetails->setFirstName (strFirstName) ;
	pEmployeeDetails->setLastName (strLastName) ;
	// Add it to the dictionary
	if ( pEmployeeDict->setAt ("DETAILS", pEmployeeDetails, idO) != Acad::eOk ) {
		delete pEmployeeDetails ;
		acutPrintf ("\nFailed to add details to that object.") ;
		pEmployeeDict->close () ;
		return ;

	}
	// Done
	acutPrintf ("\nDetails successfully added!") ;
	pEmployeeDict->close () ;
	pEmployeeDetails->close () ;
}

// This is command 'REMOVEDETAIL'
void asdkremovedetail()
{
	// TODO: Implement the command

	ads_name ename ;
	ads_point pt ;
	// Get the data from the user
	if ( acedEntSel ("Select employee: ", ename, pt) != RTNORM )
		return ;
	// Do a quick check
	// a more comprehensive check could include 
	// whether we already have the detail object on this candidate
	AcDbObjectId idO ;
	if ( acdbGetObjectId (idO, ename) != Acad::eOk )
		return ;
	AcDbObject *pO ;
	if ( acdbOpenAcDbObject (pO, idO, AcDb::kForRead) != Acad::eOk )
		return ;
	if ( !pO->isKindOf (AcDbBlockReference::desc ()) ) {
		acutPrintf ("\nThis is not a block reference.") ;
		pO->close () ;
		return ;
	}
	// Get the Ext. Dictionary
    if ( (idO =pO->extensionDictionary ()) == AcDbObjectId::kNull ) {
		// Nothing to do
		pO->close () ;
		return ;
	}
	// We do not need the block reference object anymore.
	pO->close () ;
    // If erased, nothing to do
	AcDbDictionary *pExtDict ;
	if ( acdbOpenAcDbObject ((AcDbObject *&)pExtDict, idO, AcDb::kForWrite, Adesk::kFalse) != Acad::eOk ) {
		acutPrintf ("\nFailed to open ext. dictionary.") ;
		return ;
	}
	// See if our dictionary is already there
	AcDbDictionary *pEmployeeDict ;
	if ( pExtDict->getAt ("ASDK_EMPLOYEE_DICTIONARY", idO) == Acad::eKeyNotFound ) {
		// Nothing to do if not
		pExtDict->close () ;
		return ;
	} else {
		// Open the dictionary for write if it is already there
		if ( acdbOpenAcDbObject (pO, idO, AcDb::kForWrite) != Acad::eOk ) {
			pExtDict->close () ;
			acutPrintf ("\nFailed to open the 'Employee' dictionary.") ;
			return ;
		}
		// Check if someone has else has created an entry with our name
		// that is not a dictionary.
		if ( (pEmployeeDict =AcDbDictionary::cast (pO)) == NULL ) {
			pO->close () ;
			pExtDict->close () ;
			acutPrintf ("\nThe entry is not a dictionary") ;
			return ;
		}
	}
	// Check if a record with this key is already there
	if ( pEmployeeDict->getAt ("DETAILS", idO) != Acad::eOk ) {
		pEmployeeDict->close () ;
		pExtDict->close () ;
		acutPrintf ("\nNo details assigned to that 'Employee' object.") ;
		return ;
	}
	// Open the object for write 
	if ( acdbOpenAcDbObject (pO, idO, AcDb::kForWrite) != Acad::eOk ) {
		pEmployeeDict->close () ;
		pExtDict->close () ;
		acutPrintf ("\nFailed to open the object detail.") ;
		return ;
	}
	// And erase it
	pO->erase () ;
	pO->close () ;
	// Erase dictionary if it has no more entries
	if ( pEmployeeDict->numEntries () == 0 )
		pEmployeeDict->erase () ;
	pEmployeeDict->close () ;
	// Erase ext. dictionary if it has no more entries
	if ( pExtDict->numEntries () == 0 )
		pExtDict->erase () ;
	pExtDict->close () ;
}

// This is command 'LISTDETAILS'
void asdklistdetails()
{
	// TODO: Implement the command

	ads_name ename ;
	ads_point pt ;
	// Get the data from the user
	if ( acedEntSel ("Select employee: ", ename, pt) != RTNORM )
		return ;
	// Do a quick check
	// a more comprehensive check could include 
	// whether we already have the detail object on this candidate
	AcDbObjectId idO ;
	if ( acdbGetObjectId (idO, ename) != Acad::eOk )
		return ;
	AcDbObject *pO ;
	if ( acdbOpenAcDbObject (pO, idO, AcDb::kForRead) != Acad::eOk )
		return ;
	if ( !pO->isKindOf (AcDbBlockReference::desc ()) ) {
		acutPrintf ("\nThis is not a block reference.") ;
		pO->close () ;
		return ;
	}
	// Get the Ext. Dictionary
    if ( (idO =pO->extensionDictionary ()) == AcDbObjectId::kNull ) {
		// Nothing to do
		pO->close () ;
		return ;
	}
	// We do not need the block reference object anymore.
	pO->close () ;
    // If erased, nothing to do
	AcDbDictionary *pExtDict ;
	if ( acdbOpenAcDbObject ((AcDbObject *&)pExtDict, idO, AcDb::kForRead, Adesk::kFalse) != Acad::eOk ) {
		acutPrintf ("\nFailed to open ext. dictionary.") ;
		return ;
	}
	// See if our dictionary is already there
	AcDbDictionary *pEmployeeDict ;
	if ( pExtDict->getAt ("ASDK_EMPLOYEE_DICTIONARY", idO) == Acad::eKeyNotFound ) {
		// Nothing to do if not
		pExtDict->close () ;
		return ;
	} else {
		// Open dictionary for write if it is already there
		if ( acdbOpenAcDbObject (pO, idO, AcDb::kForRead) != Acad::eOk ) {
			pExtDict->close () ;
			acutPrintf ("\nFailed to open the 'Employee' dictionary.") ;
			return ;
		}
		// Check if someone has else has created an entry with our name
		// that is not a dictionary. 
		if ( (pEmployeeDict =AcDbDictionary::cast (pO)) == NULL ) {
			pO->close () ;
			pExtDict->close () ;
			acutPrintf ("\nThe entry is not a dictionary") ;
			return ;
		}
	}
	// Check if a record with this key is already there
	if ( pEmployeeDict->getAt ("DETAILS", idO) != Acad::eOk ) {
		// Nothing to do
		pEmployeeDict->close () ;
		pExtDict->close () ;
		return ;
	}
	// Open the object for write 
	if ( acdbOpenAcDbObject (pO, idO, AcDb::kForRead) != Acad::eOk ) {
		pEmployeeDict->close () ;
		pExtDict->close () ;
		acutPrintf ("\nFailed to open the object detail.") ;
		return ;
	}
	// Check it is a AsdkEmployeeDetails object
	AsdkEmployeeDetails *pEmployeeDetails =AsdkEmployeeDetails::cast (pO) ;
	if ( pEmployeeDetails == NULL ) {
		acutPrintf ("\nNo details found!.") ;
		pO->close () ;
		pEmployeeDict->close () ;
		pExtDict->close () ;
		return ;
	}
	// And display details
	Adesk::Int32 i ;
	pEmployeeDetails->iD (i) ;
	acutPrintf ("*Employee's ID: %d\n", i) ;
	pEmployeeDetails->cube (i) ;
	acutPrintf ("*Employee's cube number: %d\n", i) ;
	char *st =NULL ;
	pEmployeeDetails->firstName (st) ;
	acutPrintf ("*Employee's first name: %s\n", st) ;
	delete [] st ;
	pEmployeeDetails->lastName (st) ;
	acutPrintf ("*Employee's last name: %s\n", st) ;
	delete [] st ;

	pO->close () ;
	pEmployeeDict->close () ;
	pExtDict->close () ;
}

