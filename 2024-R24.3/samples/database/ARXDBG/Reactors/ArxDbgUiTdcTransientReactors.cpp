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

#include "ArxDbgUiTdcTransientReactors.h"
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
BOOL    ArxDbgUiTdcTransientReactors::m_doStateModified = FALSE;
BOOL    ArxDbgUiTdcTransientReactors::m_doStateCancelled = FALSE;
BOOL    ArxDbgUiTdcTransientReactors::m_doStateErased = FALSE;
BOOL    ArxDbgUiTdcTransientReactors::m_doStateCopied = FALSE;
BOOL    ArxDbgUiTdcTransientReactors::m_doStateGoodbye = FALSE;
BOOL    ArxDbgUiTdcTransientReactors::m_doStateOpenMod = FALSE;
BOOL    ArxDbgUiTdcTransientReactors::m_doStateSubObjMod = FALSE;
BOOL    ArxDbgUiTdcTransientReactors::m_doStateModUndone = FALSE;
BOOL    ArxDbgUiTdcTransientReactors::m_doStateModXdata = FALSE;
BOOL    ArxDbgUiTdcTransientReactors::m_doStateModGraphics = FALSE;
BOOL    ArxDbgUiTdcTransientReactors::m_doStateUnappended = FALSE;
BOOL    ArxDbgUiTdcTransientReactors::m_doStateReappended = FALSE;
BOOL    ArxDbgUiTdcTransientReactors::m_doStateClosed = FALSE;


// These statics are all MDI aware
ArxDbgTransientObjReactor*	ArxDbgUiTdcTransientReactors::m_objReactor = NULL;
ArxDbgTransientEntReactor*	ArxDbgUiTdcTransientReactors::m_entReactor = NULL;


/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::ArxDbgUiTdcTransientReactors
**
**  **jma
**
*************************************/

ArxDbgUiTdcTransientReactors::ArxDbgUiTdcTransientReactors()
:   ArxDbgUiTdcObjReactorsBase()
{
    //{{AFX_DATA_INIT(ArxDbgUiTdcTransientReactors)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::cleanUpReactors
**      static function to clean up any left over reactors if
**  app exits and they are still turned on.
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::cleanUpReactors()
{
    delete m_objReactor;
    delete m_entReactor;

    m_objReactor = NULL;
    m_entReactor = NULL;
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::DoDataExchange(CDataExchange* pDX)
{
    ArxDbgUiTdcObjReactorsBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdcTransientReactors)
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
// ArxDbgUiTdcTransientReactors message handlers

BEGIN_MESSAGE_MAP(ArxDbgUiTdcTransientReactors, ArxDbgUiTdcObjReactorsBase)
    //{{AFX_MSG_MAP(ArxDbgUiTdcTransientReactors)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcTransientReactors message handlers


/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdcTransientReactors::OnInitDialog() 
{
	ArxDbgUiTdcObjReactorsBase::OnInitDialog();

	return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::getAttachedObjects
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::getAttachedObjects(AcDbObjectIdArray& objIds)
{
	if (m_objReactor)
		objIds = m_objReactor->m_objList;
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::getAttachedEntities
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::getAttachedEntities(AcDbObjectIdArray& objIds)
{
	if (m_entReactor)
		objIds = m_entReactor->m_objList;
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::detachSelectedEnts
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::detachSelectedEnts(const AcDbObjectIdArray& objIds) 
{
	if (m_entReactor != NULL) {
		Acad::ErrorStatus es;
		AcDbEntity* ent;

		ArxDbgDocLockWrite docLock;	// these potentially came from other documents

		int len = objIds.length();
		for (int i=0; i<len; i++) {
			es = docLock.lock(objIds[i].database());	// lock the document associated with this database
			if (es == Acad::eOk) {
				es = acdbOpenAcDbEntity(ent, objIds[i], AcDb::kForWrite, true);
				if (es == Acad::eOk) {
					m_entReactor->delFromObject(ent);
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
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::detachSelectedObjs
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::detachSelectedObjs(const AcDbObjectIdArray& objIds) 
{
	if (m_objReactor != NULL) {
		Acad::ErrorStatus es;
		AcDbObject* obj;

		ArxDbgDocLockWrite docLock;	// these potentially came from other documents

		int len = objIds.length();
		for (int i=0; i<len; i++) {
			es = docLock.lock(objIds[i].database());	// lock the document associated with this database
			if (es == Acad::eOk) {
				es = acdbOpenAcDbObject(obj, objIds[i], AcDb::kForWrite, true);
				if (es == Acad::eOk) {
					m_objReactor->delFromObject(obj);
					obj->close();
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
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::attachObjReactors
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::attachObjReactors(const AcDbObjectIdArray& objIds)
{
        // re-use same reactor if it is already allocated
    if (m_objReactor == NULL) {
        acutPrintf(_T("\nAllocating new ObjectReactor..."));
        m_objReactor = new ArxDbgTransientObjReactor;
    }

	Acad::ErrorStatus es;
	AcDbObject* obj;

	ArxDbgDocLockWrite docLock;	// these potentially came from other documents

	int len = objIds.length();
	for (int i=0; i<len; i++) {
		es = docLock.lock(objIds[i].database());	// lock the document associated with this database
		if (es == Acad::eOk) {
			es = acdbOpenAcDbObject(obj, objIds[i], AcDb::kForWrite, true);
			if (es == Acad::eOk) {
				m_objReactor->addToObject(obj);
				obj->close();
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
**  ArxDbgUiTdcTransientReactors::attachEntReactors
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::attachEntReactors()
{
        // re-use same reactor if it is already allocated
    if (m_entReactor == NULL) {
        acutPrintf(_T("\nAllocating new EntityReactor..."));
        m_entReactor = new ArxDbgTransientEntReactor;
    }

		// unfortunately, this structure for making this page know about the main
		// dialog means that we could never use this page within another main dialog
		// container.  So, cast to our known type of owning Main Dialog
	ArxDbgUiTdmReactors* tdmReactors = static_cast<ArxDbgUiTdmReactors*>(GetMainDialog());
	tdmReactors->attachEntTransientReactor(m_entReactor);
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::detachEntReactors
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::detachEntReactors()
{
		// unfortunately, this structure for making this page know about the main
		// dialog means that we could never use this page within another main dialog
		// container.  So, cast to our known type of owning Main Dialog
	ArxDbgUiTdmReactors* tdmReactors = static_cast<ArxDbgUiTdmReactors*>(GetMainDialog());
	tdmReactors->detachEntTransientReactor(m_entReactor);
}


/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::doStateDboxCacelled
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::doStateDboxCacelled(const AcDbObject* obj)
{
    if (ArxDbgUiTdcTransientReactors::m_doStateCancelled)
        ArxDbgUiTdcTransientReactors::doStateDbox(obj, _T("Cancelled"));
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::doStateDboxCopied
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::doStateDboxCopied(const AcDbObject* obj, const AcDbObject* newObject)
{
    if (ArxDbgUiTdcTransientReactors::m_doStateCopied) {
        ArxDbgUiTdcTransientReactors::doStateDbox(obj, _T("Copied (source object)"));
        ArxDbgUiTdcTransientReactors::doStateDbox(obj, _T("Copied (new object)"));
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::doStateDboxErased
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::doStateDboxErased(const AcDbObject* obj, Adesk::Boolean isErasing)
{
    if (ArxDbgUiTdcTransientReactors::m_doStateErased) {
        if (isErasing)
            ArxDbgUiTdcTransientReactors::doStateDbox(obj, _T("Erase"));
        else
            ArxDbgUiTdcTransientReactors::doStateDbox(obj, _T("Un-erase"));
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::doStateDboxGoodbye
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::doStateDboxGoodbye(const AcDbObject* obj)
{
    if (ArxDbgUiTdcTransientReactors::m_doStateGoodbye)
        ArxDbgUiTdcTransientReactors::doStateDbox(obj, _T("Goodbye"));
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::doStateDboxOpenedModify
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::doStateDboxOpenedModify(const AcDbObject* obj)
{
    if (ArxDbgUiTdcTransientReactors::m_doStateOpenMod)
        ArxDbgUiTdcTransientReactors::doStateDbox(obj, _T("Open For Modify"));
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::doStateDboxModified
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::doStateDboxModified(const AcDbObject* obj)
{
    if (ArxDbgUiTdcTransientReactors::m_doStateModified)
        ArxDbgUiTdcTransientReactors::doStateDbox(obj, _T("Modified"));
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::doStateDboxSubObjModified
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::doStateDboxSubObjModified(const AcDbObject* obj, const AcDbObject* subObj)
{
    if (ArxDbgUiTdcTransientReactors::m_doStateSubObjMod) {
        ArxDbgUiTdcTransientReactors::doStateDbox(obj, _T("SubObject Modified (main object)"));
        ArxDbgUiTdcTransientReactors::doStateDbox(subObj, _T("SubObject Modified (sub-object)"));
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::doStateDboxModifyUndone
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::doStateDboxModifyUndone(const AcDbObject* obj)
{
    if (ArxDbgUiTdcTransientReactors::m_doStateModUndone)
        ArxDbgUiTdcTransientReactors::doStateDbox(obj, _T("Modify Undone"));
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::doStateDboxModifiedXdata
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::doStateDboxModifiedXdata(const AcDbObject* obj)
{
    if (ArxDbgUiTdcTransientReactors::m_doStateModXdata)
        ArxDbgUiTdcTransientReactors::doStateDbox(obj, _T("Modified Xdata"));
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::doStateDboxModifiedGraphics
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::doStateDboxModifiedGraphics(const AcDbObject* obj)
{
    if (ArxDbgUiTdcTransientReactors::m_doStateModGraphics)
        ArxDbgUiTdcTransientReactors::doStateDbox(obj, _T("Modified Graphics"));
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::doStateDboxUnappended
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::doStateDboxUnappended(const AcDbObject* obj)
{
    if (ArxDbgUiTdcTransientReactors::m_doStateUnappended)
        ArxDbgUiTdcTransientReactors::doStateDbox(obj, _T("Un-appended"));
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::doStateDboxReappended
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::doStateDboxReappended(const AcDbObject* obj)
{
    if (ArxDbgUiTdcTransientReactors::m_doStateReappended)
        ArxDbgUiTdcTransientReactors::doStateDbox(obj, _T("Re-appended"));
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::doStateDboxClosed
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcTransientReactors::doStateDboxClosed(const AcDbObjectId& objId)
{
    if (ArxDbgUiTdcTransientReactors::m_doStateClosed)
        ArxDbgUiTdcTransientReactors::doStateDbox(objId, _T("Object Closed"));
}




