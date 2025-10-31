#include "stdafx.h"
#include "stdarx.h"

AcDbObjectId SelectEntity (/*[in]*/const char *msg /*=NULL*/, /*[in]*/AcRxClass *pClass /*=NULL*/)
{
	//----- Description:
	//-----   Selects an entity in AutoCAD and returns its ObjectId
	//----- Note:
	//-----   The two arguments are:
	//-----   * msg:    message to display while selecting an entity
	//-----   * pClass: ARX class descriptor of the object we want to select
	//-----             I.e.   AcDbLine::desc () for a line entity
	AcDbObjectId id ;
#ifndef ACDBLIB
	//----- ObjectDBX does not have ADS functions and ADS error codes defined

	ads_name en ;
	ads_point pt ;
	if ( acedEntSel (msg, en, pt) != RTNORM )
		return (AcDbObjectId::kNull) ;
	if ( acdbGetObjectId (id, en) != Acad::eOk )
		return (AcDbObjectId::kNull) ;
	if ( pClass != NULL ) {
		AcDbEntity *pEnt ;
		if ( acdbOpenAcDbEntity (pEnt, id, AcDb::kForRead) != Acad::eOk )
			return (AcDbObjectId::kNull) ;
		if ( pEnt->isA () != pClass )
			id =AcDbObjectId::kNull ;
		pEnt->close () ;
	}
#endif
	return (id) ;
}

Acad::ErrorStatus postToDatabase (/*[in]*/AcDbDatabase *pDb /*=NULL*/, /*[in]*/AcDbEntity *pEnt, /*[out]*/AcDbObjectId &idObj)
{
	//----- Purpose:
	//----- Adds an entity to the MODEL_SPACE of the database givn in argument.
	//-----   * pDb:   pointer to the databse where to add teh entity,
	//-----            if NULL, then the curretn database is used.
	//-----   * pEnt:  pointer to an entity instance.
	//-----   * idObj: it will contain the assign ID to the object if successfully added to the database.
	//----- Note:
	//-----   The entity object is closed while we return from that function. Only the idObj can be used after.
	assert ( pEnt != NULL ) ;

	if ( pDb == NULL )
		pDb =acdbHostApplicationServices ()->workingDatabase () ;
	//----- Get a pointer to the current drawing
	//----- and get the drawing's block table. Open it for read.
	Acad::ErrorStatus es ;
	AcDbBlockTable *pBlockTable ;
	if ( (es =pDb->getBlockTable (pBlockTable, AcDb::kForRead)) == Acad::eOk ) {
		//----- Get the Model Space record and open it for write. This will be the owner of the new entity.
		AcDbBlockTableRecord *pSpaceRecord ;
		if ( (es =pBlockTable->getAt (ACDB_MODEL_SPACE, pSpaceRecord, AcDb::kForWrite)) == Acad::eOk ) {
			//----- Append pEnt to Model Space, then close it and the Model Space record.
			if ( (es =pSpaceRecord->appendAcDbEntity (idObj, pEnt)) == Acad::eOk )
				pEnt->close () ;
			pSpaceRecord->close () ;
		}
		pBlockTable->close () ;
	}
	//----- It is good programming practice to return an error status
	return (es) ;
}

Acad::ErrorStatus RTtoStatus (int rt)
{
#ifndef ACDBLIB
	//----- ObjectDBX does not have ADS functions and ADS error codes defined

	//----- Description:
	//-----   Maps an ADS return code to an Acad::ErrorStatus
	//----- Note:
	//-----   We don't mind about the performance hit that this
	//-----   extra function call introduces. ads_* functions, hopefully, can now
	//-----   be replaced by corresponding arx calls. Where they cannot be, they are
	//-----   usually in a user input context, therefore this performance penalty is 
	//-----   not an issue.
	//-----   The mapping here is completely arbitrary. Change it if you don't like it.
	switch ( rt ) {
		case RTNORM: //----- 5100 - Request succeeded
			return (Acad::eOk) ;
		case RTERROR: //----- -5001 - Some other error
			return (Acad::eUnrecoverableErrors) ;
		case RTCAN: //----- -5002 - User cancelled request -- Ctl-C
			return (Acad::eUserBreak) ;
		case RTREJ: //----- -5003 - AutoCAD rejected request -- invalid
			return (Acad::eInvalidInput) ;
		case RTFAIL: //----- -5004 - Link failure -- Lisp probably died
			return (Acad::eNotApplicable) ;
		default:
		//case RTKWORD: //----- -5005 - Keyword returned from getxxx() routine
			//----- this function only intended to be called 
			//----- in an error checking situation. See ADSOK.
			assert ( 0 ) ;
			return (Acad::eOk) ;
	}
#endif
	return (Acad::eOk) ;
}

AcDbObjectId GetNODCompanyDictionaryId (/*[in]*/AcDbDatabase *pDb /*=NULL*/, /*[in]*/const char *key, /*[in]*/bool bCreateIfNotPresent /*=true*/)
{
	//----- Description:
	//-----   Get the ObjectID of the company dictionary from the AutoCAD Named Object Dictionary
	//-----   This is to be ObjectARX Logo Compliant
	//----- Argument description:
	//-----   /*[in]*/AcDbDatabase *pDb /*=NULL*/
	//-----     The AcDbDatabase pointer on which we want to work. If NULL, the current database.
	//-----   /*[in]*/const char *key,
	//-----     The company dictionary key entry
	//-----   /*[in]*/bool bCreateIfNotPresent /*=true*/)
	//-----     If not present, should the function creates it?
	assert ( key == NULL || *key == '\0' ) ;

	if ( pDb == NULL )
		pDb =acdbHostApplicationServices ()->workingDatabase () ;

	AcDbDictionary *pNOD ;
	if ( pDb->getNamedObjectsDictionary (pNOD, AcDb::kForRead) != Acad::eOk )
		return (AcDbObjectId::kNull) ;

	AcDbObjectId id =AcDbObjectId::kNull ;
	if ( !pNOD->has (key) ) {
		if ( !bCreateIfNotPresent ) {
			pNOD->close () ;
			return (AcDbObjectId::kNull) ;
		}

		if ( pNOD->upgradeOpen () != Acad::eOk ) {
			pNOD->close () ;
			return (AcDbObjectId::kNull) ;
		}

		AcDbDictionary *pDict =new AcDbDictionary ;
		if ( pNOD->setAt (key, pDict, id) != Acad::eOk ) {
			delete pDict ;
			pNOD->close () ;
			return (AcDbObjectId::kNull) ;
		}

		pNOD->downgradeOpen () ;

	} else {
		if ( pNOD->getAt (key, id) != Acad::eOk ) {
			pNOD->close () ;
			return (AcDbObjectId::kNull) ;
		}

		AcDbObject *pObj ;
		if ( acdbOpenAcDbObject (pObj, id, AcDb::kForRead) != Acad::eOk ) {
			pNOD->close () ;
			return (AcDbObjectId::kNull) ;
		}

		if ( AcDbDictionary::cast (pObj) == NULL ) {
			pObj->close () ;
			pNOD->close () ;
			return (AcDbObjectId::kNull) ;
		}
		pObj->close () ;

	}
	pNOD->close () ;

	return (id) ;
}

Acad::ErrorStatus GetNODCompanyDictionary (/*[in]*/AcDbDatabase *pDb /*=NULL*/, /*[in]*/const char *key, /*[out]*/AcDbDictionary *&pDict, /*[in]*/AcDb::OpenMode mode /*=AcDb::kForRead*/, /*[in]*/bool bCreateIfNotPresent /*=true*/)
{
	//----- Description:
	//-----   Open a company dictionary from the AutoCAD Named Object Dictionary
	//-----   This is to be ObjectARX Logo Compliant
	//----- Argument description:
	//-----   /*[in]*/AcDbDatabase *pDb /*=NULL*/
	//-----     The AcDbDatabase pointer on which we want to work. If NULL, the current database.
	//-----   /*[in]*/const char *key,
	//-----     The company dictionary key entry
	//-----   /*[out]*/AcDbDictionary *&pDict,
	//-----     The returned pointer if the dictioney gets opened properly
	//-----   /*[in]*/AcDb::OpenMode mode /*=AcDb::kForRead*/,
	//-----     The open mode for the dictionary
	//-----   /*[in]*/bool bCreateIfNotPresent /*=true*/)
	//-----     If not present, should the function creates it?
	Acad::ErrorStatus es ;
	assert ( key == NULL || *key == '\0' ) ;

	if ( pDb == NULL )
		pDb =acdbHostApplicationServices ()->workingDatabase () ;

	AcDbDictionary *pNOD ;
	if ( (es =pDb->getNamedObjectsDictionary (pNOD, AcDb::kForRead)) != Acad::eOk )
		return (es) ;

	AcDbObjectId id ;
	if ( !pNOD->has (key) ) {
		if ( !bCreateIfNotPresent ) {
			pNOD->close () ;
			return (Acad::eKeyNotFound) ;
		}

		if ( (es =pNOD->upgradeOpen ()) != Acad::eOk ) {
			pNOD->close () ;
			return (es) ;
		}

		pDict =new AcDbDictionary ;
		if ( (es =pNOD->setAt (key, pDict, id)) != Acad::eOk ) {
			delete pDict ;
			pNOD->close () ;
			return (es) ;
		}

		pNOD->downgradeOpen () ;

		//----- We should close and reopen the company dictionary to make sure
		//----- UNDO will get new entries properly. And luckly, it will give us a
		//----- chance to reopen teh object in teh right mode...
		pDict->close () ;
		acdbOpenAcDbObject ((AcDbObject *&)pDict, id, mode) ;

	} else {
		AcDbObject *pObj ;
		if ( (es =pNOD->getAt (key, pObj, mode)) != Acad::eOk ) {
			pNOD->close () ;
			return (es) ;
		}

		pDict =AcDbDictionary::cast (pObj) ;
		if ( pDict == NULL ) {
			pObj->close () ;
			pNOD->close () ;
			return (Acad::eNotThatKindOfClass) ;
		}
	}
	pNOD->close () ;

	return (Acad::eOk) ;
}

Acad::ErrorStatus GetObjectExtCompanyDictionary (/*[in]*/AcDbObject *pObj, /*[in]*/const char *key, /*[out]*/AcDbDictionary *&pDict, /*[in]*/AcDb::OpenMode mode /*=AcDb::kForRead*/, /*[in]*/bool bCreateIfNotPresent /*=true*/)
{
	//----- Description:
	//-----   Open a company dictionary from the AutoCAD Named Object Dictionary
	//-----   This is to be ObjectARX Logo Compliant
	//----- Argument description:
	//-----   /*[in]*/AcDbObject *pObj
	//-----     The AcDbObject pointer on which we want to work.
	//-----   /*[in]*/const char *key,
	//-----     The company dictionary key entry
	//-----   /*[out]*/AcDbDictionary *&pDict,
	//-----     The returned pointer if the dictioney gets opened properly
	//-----   /*[in]*/AcDb::OpenMode mode /*=AcDb::kForRead*/,
	//-----     The open mode for the dictionary
	//-----   /*[in]*/bool bCreateIfNotPresent /*=true*/)
	//-----     If not present, should the function creates it?
	Acad::ErrorStatus es ;
	assert ( pObj != NULL && pObj->isKindOf (AcDbObject::desc ()) ) ;
	assert ( key == NULL || *key == '\0' ) ;

	AcDbObjectId id ;
	AcDbDictionary *pExt ;
	if ( (id =pObj->extensionDictionary ()) == AcDbObjectId::kNull ) {
		if ( !bCreateIfNotPresent )
			return (Acad::eKeyNotFound) ;

		bool bWasOpenForRead =false ;
		if ( !pObj->isWriteEnabled () ) {
			bWasOpenForRead =true ;
			if ( (es =pObj->upgradeOpen ()) != Acad::eOk )
				return (es) ;
		}

		if ( (es =pObj->createExtensionDictionary ()) != Acad::eOk ) {
			if ( bWasOpenForRead )
				pObj->downgradeOpen () ;
			return (es) ;
		}

		id =pObj->extensionDictionary () ;

		if ( (es =acdbOpenAcDbObject ((AcDbObject *&)pExt, id, AcDb::kForWrite, Adesk::kTrue)) != Acad::eOk )
			return (es) ;

		pDict =new AcDbDictionary ;
		if ( (es =pExt->setAt (key, pDict, id)) != Acad::eOk ) {
			delete pDict ;
			pExt->close () ;
			return (es) ;
		}

		pExt->close () ;

		//----- We should close and reopen the company dictionary to make sure
		//----- UNDO will get new entries properly. And luckly, it will give us a
		//----- chance to reopen teh object in teh right mode...
		pDict->close () ;
		acdbOpenAcDbObject ((AcDbObject *&)pDict, id, mode) ;
	} else {
		if ( (es =acdbOpenAcDbObject ((AcDbObject *&)pExt, id, AcDb::kForWrite, Adesk::kTrue)) != Acad::eOk )
			return (es) ;

		//----- Unerase the ext. dictionary if it was erased
		if ( pExt->isErased () ) {
			if ( !bCreateIfNotPresent ) {
				pExt->close () ;
				return (Acad::eWasErased) ;
			}
			pExt->erase (Adesk::kFalse) ;
		}

		if ( pExt->has (key) ) {
			AcDbObject *pTempObj ;
			if ( (es =pExt->getAt (key, pTempObj, mode)) != Acad::eOk ) {
				pExt->close () ;
				return (es) ;
			}

			pDict =AcDbDictionary::cast (pTempObj) ;
			if ( pDict == NULL ) {
				pTempObj->close () ;
				pExt->close () ;
				return (Acad::eNotThatKindOfClass) ;
			}
		} else if ( bCreateIfNotPresent ) {

			pDict =new AcDbDictionary ;
			if ( (es =pExt->setAt (key, pDict, id)) != Acad::eOk ) {
				delete pDict ;
				pExt->close () ;
				return (es) ;
			}
			//----- We should close and reopen the company dictionary to make sure
			//----- UNDO will get new entries properly. And luckly, it will give us a
			//----- chance to reopen teh object in teh right mode...
			pDict->close () ;
			acdbOpenAcDbObject ((AcDbObject *&)pDict, id, mode) ;
		}

		pExt->close () ;
	}

	return (Acad::eOk) ;
}

AcDbObjectId GetObjectExtCompanyDictionaryId (/*[in]*/AcDbObject *pObj, /*[in]*/const char *key, /*[in]*/bool bCreateIfNotPresent /*=true*/)
{
	//----- Description:
	//-----   Get the ObjectID of the company dictionary from the AutoCAD Named Object Dictionary
	//-----   This is to be ObjectARX Logo Compliant
	//----- Argument description:
	//-----   /*[in]*/AcDbObject *pObj
	//-----     The AcDbObject pointer on which we want to work.
	//-----   /*[in]*/const char *key,
	//-----     The company dictionary key entry
	//-----   /*[in]*/bool bCreateIfNotPresent /*=true*/)
	//-----     If not present, should the function creates it?
	assert ( pObj != NULL && pObj->isKindOf (AcDbObject::desc ()) ) ;
	assert ( key == NULL || *key == '\0' ) ;

	AcDbObjectId id ;
	AcDbDictionary *pExt, *pDict ;
	if ( (id =pObj->extensionDictionary ()) == AcDbObjectId::kNull ) {
		if ( !bCreateIfNotPresent )
			return (AcDbObjectId::kNull) ;

		bool bWasOpenForRead =false ;
		if ( !pObj->isWriteEnabled () ) {
			bWasOpenForRead =true ;
			if ( pObj->upgradeOpen () != Acad::eOk )
				return (AcDbObjectId::kNull) ;
		}

		if ( pObj->createExtensionDictionary () != Acad::eOk ) {
			if ( bWasOpenForRead )
				pObj->downgradeOpen () ;
			return (AcDbObjectId::kNull) ;
		}

		id =pObj->extensionDictionary () ;

		if ( acdbOpenAcDbObject ((AcDbObject *&)pExt, id, AcDb::kForWrite, Adesk::kTrue) != Acad::eOk )
			return (AcDbObjectId::kNull) ;

		pDict =new AcDbDictionary ;
		if ( pExt->setAt (key, pDict, id) != Acad::eOk ) {
			delete pDict ;
			pExt->close () ;
			return (AcDbObjectId::kNull) ;
		}

	} else {
		if ( acdbOpenAcDbObject ((AcDbObject *&)pExt, id, AcDb::kForWrite, Adesk::kTrue) != Acad::eOk )
			return (AcDbObjectId::kNull) ;

		//----- Unerase the ext. dictionary if it was erased
		if ( pExt->isErased () ) {
			if ( !bCreateIfNotPresent ) {
				pExt->close () ;
				return (AcDbObjectId::kNull) ;
			}
			pExt->erase (Adesk::kFalse) ;
		}

		if ( pExt->has (key) ) {
			AcDbObject *pTempObj ;
			if ( pExt->getAt (key, pTempObj, AcDb::kForRead) != Acad::eOk ) {
				pExt->close () ;
				return (AcDbObjectId::kNull) ;
			}

			pDict =AcDbDictionary::cast (pTempObj) ;
			if ( pDict == NULL ) {
				pTempObj->close () ;
				pExt->close () ;
				return (AcDbObjectId::kNull) ;
			}
		} else if ( bCreateIfNotPresent ) {
			pDict =new AcDbDictionary ;
			if ( pExt->setAt (key, pDict, id) != Acad::eOk ) {
				delete pDict ;
				pExt->close () ;
				return (AcDbObjectId::kNull) ;
			}
		}
	}

	pDict->close () ;
	pExt->close () ;
	return (id) ;
}

