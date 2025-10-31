//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxDbgCloneSet.h"
#include "ArxDbgUtils.h"



/****************************************************************************
**
**  ArxDbgCloneSet::ArxDbgCloneSet
**
**  **jma
**
*************************************/

ArxDbgCloneSet::ArxDbgCloneSet()
{
		// set up an inital place for each database to store
		// a set of objects to clone.
	AcDbVoidPtrArray dbPtrs;
	ArxDbgUtils::getAllDatabases(dbPtrs);

	AcDbDatabase* tmpDb;
	AcDbObjectIdArray* objIds;

	int len = dbPtrs.length();
	for (int i=0; i<len; i++) {
		tmpDb = static_cast<AcDbDatabase*>(dbPtrs[i]);
		if (m_dbMap.Lookup(tmpDb, (void*&)(objIds)) == FALSE) {
			objIds = new AcDbObjectIdArray;
			m_dbMap.SetAt(tmpDb, objIds);
		}
	}
}

/****************************************************************************
**
**  ArxDbgCloneSet::~ArxDbgCloneSet
**
**  **jma
**
*************************************/

ArxDbgCloneSet::~ArxDbgCloneSet()
{
    POSITION pos;
    AcDbDatabase* tmpDb = NULL;
    AcDbObjectIdArray* objIds = NULL;

    for (pos = m_dbMap.GetStartPosition(); pos != NULL;) {
        m_dbMap.GetNextAssoc(pos, (void*&)tmpDb, (void*&)objIds);
        delete objIds;
    }

    m_dbMap.RemoveAll();
}

/****************************************************************************
**
**  ArxDbgCloneSet::getAllDatabases
**
**  **jma
**
*************************************/

void
ArxDbgCloneSet::getAllDatabases(AcDbVoidPtrArray& dbPtrs)
{
    POSITION pos;
    AcDbDatabase* tmpDb = NULL;
    AcDbObjectIdArray* objIds = NULL;

    for (pos = m_dbMap.GetStartPosition(); pos != NULL;) {
        m_dbMap.GetNextAssoc(pos, (void*&)tmpDb, (void*&)objIds);
		dbPtrs.append(tmpDb);
    }
}

/****************************************************************************
**
**  ArxDbgCloneSet::getObjectsForDatabase
**		given a database, get the set of objects that the use has setup as
**	a "clone set".
**
**  **jma
**
*************************************/

bool
ArxDbgCloneSet::getObjectsForDatabase(AcDbDatabase* db, AcDbObjectIdArray& objIds)
{
	AcDbObjectIdArray* cloneSet = NULL;

	if (m_dbMap.Lookup(db, (void*&)(cloneSet)) == FALSE) {
		ASSERT(0);
		return false;
	}
	else {
		ASSERT(cloneSet != NULL);
		objIds = *cloneSet;
		return true;
	}
}

/****************************************************************************
**
**  ArxDbgCloneSet::databaseConstructed
**		need to make a new node in our map
**
**  **jma
**
*************************************/

void
ArxDbgCloneSet::databaseConstructed(AcDbDatabase* db)
{
	AcDbObjectIdArray* cloneSet = NULL;

	if (m_dbMap.Lookup(db, (void*&)(cloneSet)) == FALSE) {
		cloneSet = new AcDbObjectIdArray;
		m_dbMap.SetAt(db, cloneSet);
	}
	else {
		ASSERT(0);
	}
}

/****************************************************************************
**
**  ArxDbgCloneSet::databaseDestroyed
**		need to remove this node from our map
**
**  **jma
**
*************************************/

void
ArxDbgCloneSet::databaseDestroyed(AcDbDatabase* db)
{
	AcDbObjectIdArray* cloneSet = NULL;

	if (m_dbMap.Lookup(db, (void*&)(cloneSet)) == TRUE) {
		delete cloneSet;
		m_dbMap.RemoveKey(db);
	}
	else {
		ASSERT(0);
	}
}

/****************************************************************************
**
**  ArxDbgCloneSet::addObject
**
**  **jma
**
*************************************/

void
ArxDbgCloneSet::addObject(const AcDbObjectId& objId)
{
	if (objId.isNull())
		return;

	AcDbObjectIdArray* cloneSet = NULL;

	if (m_dbMap.Lookup(objId.database(), (void*&)(cloneSet)) == FALSE) {
		ASSERT(0);
	}
	else {
		ASSERT(cloneSet != NULL);
		if (cloneSet->contains(objId) == false)
			cloneSet->append(objId);
	}
}

/****************************************************************************
**
**  ArxDbgCloneSet::addObjects
**
**  **jma
**
*************************************/

void
ArxDbgCloneSet::addObjects(const AcDbObjectIdArray& objIds)
{
	int len = objIds.length();
	for (int i=0; i<len; i++)
		addObject(objIds[i]);
}

/****************************************************************************
**
**  ArxDbgCloneSet::removeObject
**
**  **jma
**
*************************************/

void
ArxDbgCloneSet::removeObject(const AcDbObjectId& objId)
{
	if (objId.isNull())
		return;

	AcDbObjectIdArray* cloneSet = NULL;

	if (m_dbMap.Lookup(objId.database(), (void*&)(cloneSet)) == FALSE) {
		ASSERT(0);
	}
	else {
		ASSERT(cloneSet != NULL);
		cloneSet->remove(objId);
	}
}

/****************************************************************************
**
**  ArxDbgCloneSet::removeObjects
**
**  **jma
**
*************************************/

void
ArxDbgCloneSet::removeObjects(const AcDbObjectIdArray& objIds)
{
	int len = objIds.length();
	for (int i=0; i<len; i++)
		removeObject(objIds[i]);
}

/****************************************************************************
**
**  ArxDbgCloneSet::removeAll
**
**  **jma
**
*************************************/

void
ArxDbgCloneSet::removeAll(AcDbDatabase* db)
{
	AcDbObjectIdArray* cloneSet = NULL;

	if (m_dbMap.Lookup(db, (void*&)(cloneSet)) == FALSE) {
		ASSERT(0);
	}
	else {
		ASSERT(cloneSet != NULL);
		cloneSet->setLogicalLength(0);
	}
}
