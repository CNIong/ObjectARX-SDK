//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
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
    auto dbPtrs = acdbActiveDatabaseArray();

    AcDbDatabase* tmpDb;
    AcDbObjectIdArray* objIds;

    int len = dbPtrs.length();
    for (int i = 0; i < len; i++) {
        tmpDb = dbPtrs[i];
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
