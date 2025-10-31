// (C) Copyright 1996-2006 by Autodesk, Inc. 
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
//  arxutils.cpp

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "acdb.h"             // acdb definitions
#include "adslib.h"           // ads defs
#include "dbents.h"           // "old" entities
#include "aced.h"             // aced stuff
#include "dbdict.h"           // dictionaries
#include "dbsymtb.h"          // symboltables
#include "dbapserv.h"
#include "arxutils.h"
#include "tchar.h"



// append - append an opened entity to model space in the database:
//
Adesk::Boolean
append( AcDbEntity* pEntity, AcDbObjectId& objId )
{
    if (NULL == pEntity)
        return Adesk::kFalse;

	AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
	AcDbBlockTable* pBlockTable = NULL;
	AcDbBlockTableRecord* pBlockRec = NULL;

	if( pDb == NULL ) {
		acedAlert( _T("No database!") );
		return Adesk::kFalse;
	}
	if( pDb->getSymbolTable( pBlockTable, AcDb::kForRead ) != Acad::eOk ) {
		acedAlert( _T("Failed to get block table!") );
		return Adesk::kFalse;
	}
	if( pBlockTable->getAt( ACDB_MODEL_SPACE, pBlockRec, AcDb::kForWrite )
		!= Acad::eOk )
	{
		acedAlert( _T("Failed to get block table record!") );
		pBlockTable->close();
		return Adesk::kFalse;
	}
	if( pBlockRec->appendAcDbEntity( objId, pEntity ) != Acad::eOk ) {
		acedAlert( _T("Failed to append entity!") );
		pBlockTable->close();
		pBlockRec->close();
		return Adesk::kFalse;
	}
	pBlockRec->close();
	pBlockTable->close();
	return Adesk::kTrue;
}

// append - append an opened entity to model space in the database:
//
Adesk::Boolean
append( AcDbEntity* pEntity )
{
	AcDbObjectId objId;
	return append( pEntity, objId );
}

AcDbDictionary*
getDict( const TCHAR *dictName, AcDb::OpenMode mode, AcDbDatabase *pDb, bool bCreateIfNotFound)
{
    if (NULL == pDb) pDb = acdbHostApplicationServices()->workingDatabase();

    if( pDb == NULL ) {
		acedAlert( _T("No database!") );
		return NULL;
	}

	AcDbDictionary *pNOD;
    AcDb::OpenMode nodMode = (NULL == dictName) ? mode : AcDb::kForRead;

    if (Acad::eOk != pDb->getNamedObjectsDictionary( pNOD, nodMode )) {
        acedAlert( _T("Can't access Named Objects Dictionary") );
        return NULL;
    }
    if (NULL == dictName)
        return pNOD;

    AcDbObject *pObj;
    AcDbDictionary *pDict;
    Acad::ErrorStatus es =
        pNOD->getAt( dictName, pObj, mode );

    if (Acad::eOk == es) {
        pDict = AcDbDictionary::cast( pObj );
        if (NULL == pDict) {
            pNOD->close();
            pObj->close();
            acedAlert( _T("Entry is not a Dictionary") );
            return NULL;
        }
        pNOD->close();
        return pDict;
    }

    if (Acad::eKeyNotFound != es) {
        pNOD->close();
        acedAlert( _T("Error while accessing Named Objects Dictionary") );
        return NULL;
    }
	if (!bCreateIfNotFound)	{
        pNOD->close();
        return NULL;
    }
    if (Acad::eOk != pNOD->upgradeOpen()) {
        pNOD->close();
        acedAlert( _T("Can't open Named Objects Dictionary for write") );
        return NULL;
    }

    if (NULL == (pDict = new AcDbDictionary)) {
        pNOD->close();
        acedAlert( _T("Can't create User Dictionary") );
        return NULL;
    }

    AcDbObjectId tmpId;
    es = pNOD->setAt( dictName, pDict, tmpId );
    pNOD->close();

    if (Acad::eOk == es)
        return pDict;

    delete pDict;
    acedAlert( _T("Can't add entry in Named Objects Dictionary") );
    return NULL;
}

AcDbObjectId
getDictId( const TCHAR *dictName, AcDbDatabase *pDb , bool bCreateIfNotFound)
{
    if (NULL == pDb) pDb = acdbHostApplicationServices()->workingDatabase();

    if( pDb == NULL ) {
		acedAlert( _T("No database!") );
		return AcDbObjectId( 0 );
	}

    if (NULL == dictName)
        return pDb->namedObjectsDictionaryId();

	AcDbDictionary *pNOD;
    if (Acad::eOk != pDb->getNamedObjectsDictionary( pNOD, AcDb::kForRead )) {
        acedAlert( _T("Can't access Named Objects Dictionary") );
        return AcDbObjectId( 0 );
    }

    AcDbObjectId resId;
    Acad::ErrorStatus es =
        pNOD->getAt( dictName, resId );

    if (Acad::eOk == es) {
        pNOD->close();
        return resId;
    }

    if (Acad::eKeyNotFound != es) {
        pNOD->close();
        acedAlert( _T("Error while accessing Named Objects Dictionary") );
        return AcDbObjectId( 0 );
    }
	if (!bCreateIfNotFound)	{
        pNOD->close();
        return AcDbObjectId( 0 );
    }

    if (Acad::eOk != pNOD->upgradeOpen()) {
        pNOD->close();
        acedAlert( _T("Can't open Named Objects Dictionary for write") );
        return AcDbObjectId( 0 );
    }

    AcDbDictionary *pDict;
    if (NULL == (pDict = new AcDbDictionary)) {
        pNOD->close();
        acedAlert( _T("Can't create User Dictionary") );
        return AcDbObjectId( 0 );
    }

    es = pNOD->setAt( dictName, pDict, resId );
    pNOD->close();

    if (Acad::eOk != es) {
        delete pDict;
        return AcDbObjectId( 0 );
    }

    pDict->close();
    return resId;
}

AcDbDictionary*
getExtDict( AcDbObject *pObj, const TCHAR *dictName,
                            AcDb::OpenMode mode, bool bCreateIfNotFound )
{
    if (NULL == pObj)
        return NULL;

    int upgrade = 0;
    AcDbObjectId eId = pObj->extensionDictionary();
    if (eId == 0) {
		if (!bCreateIfNotFound)
			return NULL;
        if (!pObj->isWriteEnabled()) {
            if (Acad::eOk != pObj->upgradeOpen())
                return NULL;
            upgrade = 1;
        }
        Acad::ErrorStatus es = pObj->createExtensionDictionary();
        if (upgrade)
            pObj->downgradeOpen();
        
        if (Acad::eOk != es)
            return NULL;

        eId = pObj->extensionDictionary();
        if (eId == 0)
            return NULL;
    }

    AcDb::OpenMode nodMode = (NULL == dictName) ? mode : AcDb::kForRead;

    AcDbDictionary *pEXD;
    if (Acad::eOk != acdbOpenObject( pEXD, eId, nodMode )) {
        acedAlert( _T("Can't access Extension Dictionary") );
        return NULL;
    }
    if (NULL == dictName)
        return pEXD;

    AcDbObject *pObj2;
    AcDbDictionary *pDict;
    Acad::ErrorStatus es =
        pEXD->getAt( dictName, pObj2, mode );

    if (Acad::eOk == es) {
        pDict = AcDbDictionary::cast( pObj2 );
        if (NULL == pDict) {
            pEXD->close();
            pObj2->close();
            acedAlert( _T("Entry is not a Dictionary") );
            return NULL;
        }
        pEXD->close();
        return pDict;
    }

    if (Acad::eKeyNotFound != es) {
        pEXD->close();
        acedAlert( _T("Error while accessing Extension Dictionary") );
        return NULL;
    }

    if (Acad::eOk != pEXD->upgradeOpen()) {
        pEXD->close();
        acedAlert( _T("Can't open Named Objects Dictionary for write") );
        return NULL;
    }

    if (NULL == (pDict = new AcDbDictionary)) {
        pEXD->close();
        acedAlert( _T("Can't create User Dictionary") );
        return NULL;
    }

    AcDbObjectId tmpId;
    es = pEXD->setAt( dictName, pDict, tmpId );
    pEXD->close();

    if (Acad::eOk == es)
        return pDict;

    delete pDict;
    acedAlert( _T("Can't add entry in Named Objects Dictionary") );
    return NULL;
}

AcDbObjectId
getExtDictId( AcDbObject *pObj, const TCHAR *dictName , bool bCreateIfNotFound)
{
    if (NULL == pObj)
        return AcDbObjectId( 0 );

    int upgrade = 0;
    AcDbObjectId eId = pObj->extensionDictionary();
    if (eId == 0) {
		if (!bCreateIfNotFound)
			return NULL;
        if (!pObj->isWriteEnabled()) {
            if (Acad::eOk != pObj->upgradeOpen())
                return AcDbObjectId( 0 );
            upgrade = 1;
        }
        Acad::ErrorStatus es = pObj->createExtensionDictionary();
        if (upgrade)
            pObj->downgradeOpen();
        
        if (Acad::eOk != es)
            return AcDbObjectId( 0 );

        eId = pObj->extensionDictionary();
    }

    if (NULL == dictName || eId == 0)
        return eId;

    AcDbDictionary *pEXD;
    if (Acad::eOk != acdbOpenObject( pEXD, eId, AcDb::kForRead )) {
        acedAlert( _T("Can't access Extension Dictionary") );
        return AcDbObjectId( 0 );
    }
    
    AcDbObjectId resId;
    Acad::ErrorStatus es =
        pEXD->getAt( dictName, resId );

    if (Acad::eOk == es) {
        pEXD->close();
        return resId;
    }

    if (Acad::eKeyNotFound != es) {
        pEXD->close();
        acedAlert( _T("Error while accessing Extension Dictionary") );
        return AcDbObjectId( 0 );
    }

    if (Acad::eOk != pEXD->upgradeOpen()) {
        pEXD->close();
        acedAlert( _T("Can't open Extension Dictionary for write") );
        return AcDbObjectId( 0 );
    }

    AcDbDictionary *pDict;
    if (NULL == (pDict = new AcDbDictionary)) {
        pEXD->close();
        acedAlert( _T("Can't create User Dictionary") );
        return AcDbObjectId( 0 );
    }

    es = pEXD->setAt( dictName, pDict, resId );
    pEXD->close();

    if (Acad::eOk != es) {
        delete pDict;
        return AcDbObjectId( 0 );
    }

    pDict->close();
    return resId;
}


AcDbObject*
cloneFromId( AcDbObjectId& id )
{
    if (id == 0)
        return NULL;

    AcDbObject *pObj;
    if (Acad::eOk != acdbOpenObject( pObj, id, AcDb::kForRead ))
        return NULL;
    AcDbObject *pRet = (AcDbObject*)pObj->clone();
    pObj->close();
    return pRet;
}
