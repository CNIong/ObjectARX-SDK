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

#include "ArxDbgDocLockWrite.h"
#include "ArxDbgUtils.h"



/****************************************************************************
**
**  ArxDbgDocLockWrite::ArxDbgDocLockWrite
**
**  **jma
**
*************************************/

ArxDbgDocLockWrite::ArxDbgDocLockWrite()
:   m_didLock(false),
    m_didSwitch(false),
    m_db(NULL),
	m_doc(NULL)
{
    m_curDocWhenStarted = acDocManager->curDocument();
    ASSERT(m_curDocWhenStarted != NULL);
}

/****************************************************************************
**
**  ArxDbgDocLockWrite::ArxDbgDocLockWrite
**
**  **jma
**
*************************************/

ArxDbgDocLockWrite::ArxDbgDocLockWrite(AcDbDatabase* db)
:   m_didLock(false),
    m_didSwitch(false),
    m_db(db)
{
	ASSERT(db != NULL);

    m_curDocWhenStarted = acDocManager->curDocument();
    ASSERT(m_curDocWhenStarted != NULL);

    m_doc = acDocManager->document(db);
}

/****************************************************************************
**
**  ArxDbgDocLockWrite::~ArxDbgDocLockWrite
**
**  **jma
**
*************************************/

ArxDbgDocLockWrite::~ArxDbgDocLockWrite()
{
    Acad::ErrorStatus es;

    if (m_didLock) {
		ASSERT(m_doc != NULL);

		es = acDocManager->unlockDocument(m_doc);
		ASSERT(es == Acad::eOk);
    }

    if (m_didSwitch) {
        ASSERT(m_curDocWhenStarted != NULL);
		ASSERT(m_doc != NULL);

        es = acDocManager->setCurDocument(m_curDocWhenStarted);
        ASSERT(es == Acad::eOk);
    }
}

/****************************************************************************
**
**  ArxDbgDocLockWrite::lock
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDocLockWrite::lock()
{
	if (m_doc == NULL)
		return Acad::eOk;	// this wasn't associated with a document

	Acad::ErrorStatus es;

	if ((m_doc->myLockMode() & AcAp::kWrite) == false) {
		es = acDocManager->lockDocument(m_doc, AcAp::kWrite);
		if (es == Acad::eOk)
			m_didLock = true;
		else {
			ASSERT(0);
			ArxDbgUtils::rxErrorAlert(es);
			return es;
		}
	}

	return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDocLockWrite::lockAndSetCurrent
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDocLockWrite::lockAndSetCurrent()
{
	if (m_doc == NULL)
		return Acad::eOk;	// this wasn't associated with a document

		// if this is already current, don't force it to be current
		// again, just lock it.
	if (acDocManager->curDocument() == m_doc)
		return lock();

	Acad::ErrorStatus es;

	if ((m_doc->myLockMode() & AcAp::kWrite) == false) {
		es = acDocManager->lockDocument(m_doc, AcAp::kWrite);
		if (es == Acad::eOk)
			m_didLock = true;
		else
			return es;
	}

	es = acDocManager->setCurDocument(m_doc, AcAp::kNone, false);
	if (es == Acad::eOk)
		m_didSwitch = true;
	else
		return es;

	return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDocLockWrite::lock
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDocLockWrite::lock(AcDbDatabase* nextDb)
{
	ASSERT(nextDb != NULL);

		// if its the same database, nothing to update
	if (m_db == nextDb)
		return lock();

		// unlock existing document/database
	Acad::ErrorStatus es = unlock();
	if (es != Acad::eOk)
		return es;

	m_didLock = false;
	m_db = nextDb;
    m_doc = acDocManager->document(m_db);

	return lock();
}

/****************************************************************************
**
**  ArxDbgDocLockWrite::lockAndSetCurrent
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDocLockWrite::lockAndSetCurrent(AcDbDatabase* nextDb)
{
	ASSERT(nextDb != NULL);

		// if its the same database, nothing to update
	if (m_db == nextDb)
		return lockAndSetCurrent();

		// unlock existing document/database
	Acad::ErrorStatus es = unlock();
	if (es != Acad::eOk)
		return es;

	m_didLock = false;
	m_db = nextDb;
    m_doc = acDocManager->document(m_db);

	return lockAndSetCurrent();
}

/****************************************************************************
**
**  ArxDbgDocLockWrite::unlock
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDocLockWrite::unlock()
{
	if ((m_doc == NULL) || (m_didLock == false))
		return Acad::eOk;	// this wasn't associated with a document

	Acad::ErrorStatus es;

	es = acDocManager->unlockDocument(m_doc);
	if (es == Acad::eOk)
		m_didLock = false;
	else {
		ASSERT(0);
		ArxDbgUtils::rxErrorAlert(es);
	}

	return es;
}

/****************************************************************************
**
**  ArxDbgDocLockWrite::unlockAndRestoreCurrent
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDocLockWrite::unlockAndRestoreCurrent()
{
	if (m_doc == NULL)
		return Acad::eOk;	// this wasn't associated with a document

	Acad::ErrorStatus es;

	if (m_didLock) {
		es = unlock();
		if (es != Acad::eOk) {
			return es;
		}
	}

	if (m_didSwitch) {
		es = acDocManager->setCurDocument(m_curDocWhenStarted);
		if (es == Acad::eOk)
			m_didSwitch = false;
		else {
			ASSERT(0);
			ArxDbgUtils::rxErrorAlert(es);
			return es;
		}
	}

	return Acad::eOk;
}
