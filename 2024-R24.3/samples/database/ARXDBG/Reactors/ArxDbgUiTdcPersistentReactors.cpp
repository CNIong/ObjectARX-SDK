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

#include "ArxDbgUiTdcPersistentReactors.h"
#include "ArxDbgUiDlgObjState.h"
#include "ArxDbgUtils.h"
#include "ArxDbgApp.h"
#include "ArxDbgUiTdmREactors.h"
#include "ArxDbgDocLockWrite.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

    // static state variables for showing state of notifying object
BOOL    ArxDbgUiTdcPersistentReactors::m_doStateModified = FALSE;
BOOL    ArxDbgUiTdcPersistentReactors::m_doStateCancelled = FALSE;
BOOL    ArxDbgUiTdcPersistentReactors::m_doStateErased = FALSE;
BOOL    ArxDbgUiTdcPersistentReactors::m_doStateCopied = FALSE;
BOOL    ArxDbgUiTdcPersistentReactors::m_doStateGoodbye = FALSE;
BOOL    ArxDbgUiTdcPersistentReactors::m_doStateOpenMod = FALSE;
BOOL    ArxDbgUiTdcPersistentReactors::m_doStateSubObjMod = FALSE;
BOOL    ArxDbgUiTdcPersistentReactors::m_doStateModUndone = FALSE;
BOOL    ArxDbgUiTdcPersistentReactors::m_doStateModXdata = FALSE;
BOOL    ArxDbgUiTdcPersistentReactors::m_doStateModGraphics = FALSE;
BOOL    ArxDbgUiTdcPersistentReactors::m_doStateUnappended = FALSE;
BOOL    ArxDbgUiTdcPersistentReactors::m_doStateReappended = FALSE;
BOOL    ArxDbgUiTdcPersistentReactors::m_doStateClosed = FALSE;


// These statics are all MDI aware
ArxDbgPersistentObjReactor*	ArxDbgUiTdcPersistentReactors::m_objReactor = nullptr;
ArxDbgPersistentEntReactor*	ArxDbgUiTdcPersistentReactors::m_entReactor = nullptr;

    // names of our dictionaries for reactor storage
LPCTSTR ArxDbgUiTdcPersistentReactors::m_dictName = _T("ARXDBG_PERSISTENT_REACTORS");


/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::ArxDbgUiTdcPersistentReactors
**
**  **jma
**
*************************************/

ArxDbgUiTdcPersistentReactors::ArxDbgUiTdcPersistentReactors()
:   ArxDbgUiTdcObjReactorsBase()
{
    //{{AFX_DATA_INIT(ArxDbgUiTdcPersistentReactors)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::DoDataExchange(CDataExchange* pDX)
{
    ArxDbgUiTdcObjReactorsBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdcPersistentReactors)
    DDX_Check(pDX, ARXDBG_CB_STATE_MODIFIED, m_doStateModified);
    DDX_Check(pDX, ARXDBG_CB_STATE_CANCELLED, m_doStateCancelled);
    DDX_Check(pDX, ARXDBG_CB_STATE_ERASED, m_doStateErased);
    DDX_Check(pDX, ARXDBG_CB_STATE_COPIED, m_doStateCopied);
    DDX_Check(pDX, ARXDBG_CB_STATE_GOODBYE, m_doStateGoodbye);
    DDX_Check(pDX, ARXDBG_CB_STATE_OPENMOD, m_doStateOpenMod);
    DDX_Check(pDX, ARXDBG_CB_STATE_SUBOBJMOD, m_doStateSubObjMod);
    DDX_Check(pDX, ARXDBG_CB_STATE_MODUNDONE, m_doStateModUndone);
    DDX_Check(pDX, ARXDBG_CB_STATE_MODXDATA, m_doStateModXdata);
    DDX_Check(pDX, ARXDBG_CB_STATE_MODGRAPHICS, m_doStateModGraphics);
    DDX_Check(pDX, ARXDBG_CB_STATE_UNAPPENDED, m_doStateUnappended);
    DDX_Check(pDX, ARXDBG_CB_STATE_REAPPENDED, m_doStateReappended);
    DDX_Check(pDX, ARXDBG_CB_STATE_CLOSED, m_doStateClosed);
    //}}AFX_DATA_MAP
}


/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcPersistentReactors message handlers

BEGIN_MESSAGE_MAP(ArxDbgUiTdcPersistentReactors, ArxDbgUiTdcObjReactorsBase)
    //{{AFX_MSG_MAP(ArxDbgUiTdcPersistentReactors)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcPersistentReactors message handlers


/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdcPersistentReactors::OnInitDialog() 
{
	ArxDbgUiTdcObjReactorsBase::OnInitDialog();

	return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::getPersistentObjReactor
**
**  **jma
**
*************************************/

AcDbObjectId
ArxDbgUiTdcPersistentReactors::getPersistentObjReactor(AcDbDatabase* db, bool createIfNotFound)
{
	static LPCTSTR dictEntryName = _T("ARXDBG_PERSISTENT_OBJ_REACTOR");

	AcDbObjectId prId;
    AcDbDictionary* prDict;

		// first see if its already there without "disturbing" anyone by opening them
		// for write.
    prDict = ArxDbgUtils::openDictionaryForRead(m_dictName, db);
    if (prDict != nullptr) {
		if (prDict->getAt(dictEntryName, prId) == Acad::eOk) {
			prDict->close();
			return prId;
		}
		prDict->close();
	}

		// couldn't find it, bail if we aren't supposed to create it.
	if (createIfNotFound == false)
		return AcDbObjectId::kNull;

		// not here yet, so make an entry
    prDict = ArxDbgUtils::openDictionaryForWrite(m_dictName, true, db);
    if (prDict == nullptr)
        return AcDbObjectId::kNull;

    Acad::ErrorStatus es;
    ArxDbgPersistentObjReactor* pr = new ArxDbgPersistentObjReactor;

    es = prDict->setAt(dictEntryName, pr, prId);
    if (es != Acad::eOk) {
        ArxDbgUtils::rxErrorMsg(es);
        ArxDbgUtils::alertBox(_T("ERROR: Could not add entry to dictionary."));
        delete pr;

		prDict->close();
		return AcDbObjectId::kNull;
    }
    else {
		pr->close();
		prDict->close();
		return prId;
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::getPersistentEntReactor
**
**  **jma
**
*************************************/

AcDbObjectId
ArxDbgUiTdcPersistentReactors::getPersistentEntReactor(AcDbDatabase* db, bool createIfNotFound)
{
	static LPCTSTR dictEntryName = _T("ARXDBG_PERSISTENT_ENT_REACTOR");

	AcDbObjectId prId;
    AcDbDictionary* prDict;

		// first see if its already there without "disturbing" anyone by opening them
		// for write.
    prDict = ArxDbgUtils::openDictionaryForRead(m_dictName, db);
    if (prDict != nullptr) {
		if (prDict->getAt(dictEntryName, prId) == Acad::eOk) {
			prDict->close();
			return prId;
		}
		prDict->close();
	}

		// couldn't find it, bail if we aren't supposed to create it.
	if (createIfNotFound == false)
		return AcDbObjectId::kNull;

		// not here yet, so make an entry
    prDict = ArxDbgUtils::openDictionaryForWrite(m_dictName, true, db);
    if (prDict == nullptr)
        return AcDbObjectId::kNull;

    Acad::ErrorStatus es;
    ArxDbgPersistentEntReactor* pr = new ArxDbgPersistentEntReactor;

    es = prDict->setAt(dictEntryName, pr, prId);
    if (es != Acad::eOk) {
        ArxDbgUtils::rxErrorMsg(es);
        ArxDbgUtils::alertBox(_T("ERROR: Could not add entry to dictionary."));
        delete pr;

		prDict->close();
		return AcDbObjectId::kNull;
    }
    else {
		pr->close();
		prDict->close();
		return prId;
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::getAttachedObjects
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::getAttachedObjects(AcDbObjectIdArray& objIds)
{
    auto dbPtrs = acdbActiveDatabaseArray();

    ArxDbgPersistentObjReactor* peReactor;
    Acad::ErrorStatus es;
    AcDbObjectIdArray tmpIds;

    for (auto&& pDb : dbPtrs) {
        const AcDbObjectId prId = getPersistentObjReactor(pDb, false);

		es = acdbOpenObject(peReactor, prId, AcDb::kForRead);
		if (es == Acad::eOk) {
			tmpIds.setLogicalLength(0);	// reusing array for each database

			peReactor->getAttachedToObjs(tmpIds);
			peReactor->close();

			objIds.append(tmpIds);
		}
	}
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::getAttachedEntities
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::getAttachedEntities(AcDbObjectIdArray& objIds)
{
    auto dbPtrs = acdbActiveDatabaseArray();

    ArxDbgPersistentEntReactor* peReactor;
    Acad::ErrorStatus es;
    AcDbObjectIdArray tmpIds;

    for (auto&& pDb : dbPtrs) {
        const AcDbObjectId prId = getPersistentEntReactor(pDb, false);

        es = acdbOpenObject(peReactor, prId, AcDb::kForRead);
        if (es == Acad::eOk) {
            tmpIds.setLogicalLength(0);	// reusing array for each database

            peReactor->getAttachedToObjs(tmpIds);
            peReactor->close();

            objIds.append(tmpIds);
        }
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::detachSelectedEnts
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::detachSelectedEnts(const AcDbObjectIdArray& objIds) 
{
	Acad::ErrorStatus es;
	ArxDbgPersistentEntReactor* peReactor;

	ArxDbgDocLockWrite docLock;	// these potentially came from other documents

    for (AcDbObjectId id : objIds) {
        es = docLock.lock(id.database());   // lock the document associated with this database
        if (es == Acad::eOk) {
            AcDbEntity* ent;
            es = acdbOpenAcDbEntity(ent, id, AcDb::kForWrite, true);
            if (es == Acad::eOk) {
                const AcDbObjectId prId = getPersistentEntReactor(id.database(), true);

				ent->removePersistentReactor(prId);

				es = acdbOpenObject(peReactor, prId, AcDb::kForWrite);
				if (es == Acad::eOk) {
					peReactor->detachFrom(ent->objectId());
					peReactor->close();
				}
				else {
					CString str;
					str.Format(_T("ERROR: Could not update backward reference in reactor: (%s)"), ArxDbgUtils::rxErrorStr(es));
					ArxDbgUtils::stopAlertBox(str);
				}

				ent->close();
			}
			else {
				ArxDbgUtils::rxErrorAlert(es);
			}
		}
		else {
			ArxDbgUtils::rxErrorAlert(es);
		}
	}
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::detachSelectedObjs
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::detachSelectedObjs(const AcDbObjectIdArray& objIds) 
{
	Acad::ErrorStatus es;
	AcDbEntity* ent;
	ArxDbgPersistentObjReactor* peReactor;

	ArxDbgDocLockWrite docLock;	// these potentially came from other documents

    for (AcDbObjectId id : objIds) {
        es = docLock.lock(id.database());   // lock the document associated with this database
        if (es == Acad::eOk) {
            es = acdbOpenAcDbEntity(ent, id, AcDb::kForWrite, true);
            if (es == Acad::eOk) {
                const AcDbObjectId prId = getPersistentObjReactor(id.database(), true);

				ent->removePersistentReactor(prId);

				es = acdbOpenObject(peReactor, prId, AcDb::kForWrite);
				if (es == Acad::eOk) {
					peReactor->detachFrom(ent->objectId());
					peReactor->close();
				}
				else {
					CString str;
					str.Format(_T("ERROR: Could not update backward reference in reactor: (%s)"), ArxDbgUtils::rxErrorStr(es));
					ArxDbgUtils::stopAlertBox(str);
				}

				ent->close();
			}
			else {
				ArxDbgUtils::rxErrorAlert(es);
			}
		}
		else {
			ArxDbgUtils::rxErrorAlert(es);
		}
	}
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::attachObjReactors
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::attachObjReactors(const AcDbObjectIdArray& objIds)
{
	Acad::ErrorStatus es;
	AcDbObject* obj;
	ArxDbgPersistentObjReactor* peReactor;

	ArxDbgDocLockWrite docLock;	// these potentially came from other documents

    for (AcDbObjectId id : objIds) {
        es = docLock.lock(id.database());   // lock the document associated with this database
        if (es == Acad::eOk) {
            es = acdbOpenAcDbObject(obj, id, AcDb::kForWrite, true);
            if (es == Acad::eOk) {
                const AcDbObjectId prId = getPersistentObjReactor(id.database(), true);

				if (ArxDbgUiTdmReactors::hasPersistentReactor(obj, prId)) {
					ArxDbgUtils::alertBox(_T("That object already has the reactor attached."));
				}
				else {
					obj->addPersistentReactor(prId);

					es = acdbOpenObject(peReactor, prId, AcDb::kForWrite);
					if (es == Acad::eOk) {
						peReactor->attachTo(obj->objectId());
						peReactor->close();
					}
					else {
						CString str;
						str.Format(_T("ERROR: Could not update backward reference in reactor: (%s)"), ArxDbgUtils::rxErrorStr(es));
						ArxDbgUtils::stopAlertBox(str);
					}
				}

				obj->close();
			}
			else {
				ArxDbgUtils::rxErrorMsg(es);
			}
		}
		else {
			ArxDbgUtils::rxErrorAlert(es);
		}
	}
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::attachEntReactors
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::attachEntReactors()
{
		// unfortunately, this structure for making this page know about the main
		// dialog means that we could never use this page within another main dialog
		// container.  Oh well...
	ArxDbgUiTdmReactors* tdmReactors = static_cast<ArxDbgUiTdmReactors*>(GetMainDialog());
	tdmReactors->attachEntPersistentReactor();
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::detachEntReactors
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::detachEntReactors()
{
		// unfortunately, this structure for making this page know about the main
		// dialog means that we could never use this page within another main dialog
		// container.  Oh well...
	ArxDbgUiTdmReactors* tdmReactors = static_cast<ArxDbgUiTdmReactors*>(GetMainDialog());
	tdmReactors->detachEntPersistentReactor();
}


/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::doStateDboxCacelled
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::doStateDboxCacelled(const AcDbObject* obj)
{
    if (ArxDbgUiTdcPersistentReactors::m_doStateCancelled)
        ArxDbgUiTdcPersistentReactors::doStateDbox(obj, _T("Cancelled"));
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::doStateDboxCopied
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::doStateDboxCopied(const AcDbObject* obj, const AcDbObject* newObject)
{
    if (ArxDbgUiTdcPersistentReactors::m_doStateCopied) {
        ArxDbgUiTdcPersistentReactors::doStateDbox(obj, _T("Copied (source object)"));
        ArxDbgUiTdcPersistentReactors::doStateDbox(obj, _T("Copied (new object)"));
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::doStateDboxErased
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::doStateDboxErased(const AcDbObject* obj, Adesk::Boolean isErasing)
{
    if (ArxDbgUiTdcPersistentReactors::m_doStateErased) {
        if (isErasing)
            ArxDbgUiTdcPersistentReactors::doStateDbox(obj, _T("Erase"));
        else
            ArxDbgUiTdcPersistentReactors::doStateDbox(obj, _T("Un-erase"));
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::doStateDboxGoodbye
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::doStateDboxGoodbye(const AcDbObject* obj)
{
    if (ArxDbgUiTdcPersistentReactors::m_doStateGoodbye)
        ArxDbgUiTdcPersistentReactors::doStateDbox(obj, _T("Goodbye"));
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::doStateDboxOpenedModify
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::doStateDboxOpenedModify(const AcDbObject* obj)
{
    if (ArxDbgUiTdcPersistentReactors::m_doStateOpenMod)
        ArxDbgUiTdcPersistentReactors::doStateDbox(obj, _T("Open For Modify"));
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::doStateDboxModified
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::doStateDboxModified(const AcDbObject* obj)
{
    if (ArxDbgUiTdcPersistentReactors::m_doStateModified)
        ArxDbgUiTdcPersistentReactors::doStateDbox(obj, _T("Modified"));
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::doStateDboxSubObjModified
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::doStateDboxSubObjModified(const AcDbObject* obj, const AcDbObject* subObj)
{
    if (ArxDbgUiTdcPersistentReactors::m_doStateSubObjMod) {
        ArxDbgUiTdcPersistentReactors::doStateDbox(obj, _T("SubObject Modified (main object)"));
        ArxDbgUiTdcPersistentReactors::doStateDbox(subObj, _T("SubObject Modified (sub-object)"));
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::doStateDboxModifyUndone
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::doStateDboxModifyUndone(const AcDbObject* obj)
{
    if (ArxDbgUiTdcPersistentReactors::m_doStateModUndone)
        ArxDbgUiTdcPersistentReactors::doStateDbox(obj, _T("Modify Undone"));
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::doStateDboxModifiedXdata
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::doStateDboxModifiedXdata(const AcDbObject* obj)
{
    if (ArxDbgUiTdcPersistentReactors::m_doStateModXdata)
        ArxDbgUiTdcPersistentReactors::doStateDbox(obj, _T("Modified Xdata"));
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::doStateDboxModifiedGraphics
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::doStateDboxModifiedGraphics(const AcDbObject* obj)
{
    if (ArxDbgUiTdcPersistentReactors::m_doStateModGraphics)
        ArxDbgUiTdcPersistentReactors::doStateDbox(obj, _T("Modified Graphics"));
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::doStateDboxUnappended
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::doStateDboxUnappended(const AcDbObject* obj)
{
    if (ArxDbgUiTdcPersistentReactors::m_doStateUnappended)
        ArxDbgUiTdcPersistentReactors::doStateDbox(obj, _T("Un-appended"));
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::doStateDboxReappended
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::doStateDboxReappended(const AcDbObject* obj)
{
    if (ArxDbgUiTdcPersistentReactors::m_doStateReappended)
        ArxDbgUiTdcPersistentReactors::doStateDbox(obj, _T("Re-appended"));
}

/****************************************************************************
**
**  ArxDbgUiTdcPersistentReactors::doStateDboxClosed
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcPersistentReactors::doStateDboxClosed(const AcDbObjectId& objId)
{
    if (ArxDbgUiTdcPersistentReactors::m_doStateClosed)
        ArxDbgUiTdcPersistentReactors::doStateDbox(objId, _T("Object Closed"));
}




