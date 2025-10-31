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

#include "ArxDbgUiTdmReactors.h"
#include "ArxDbgUiTdcSysReactors.h"
#include "ArxDbgUiTdcTransientReactors.h"
#include "ArxDbgUiTdcPersistentReactors.h"
#include "ArxDbgApp.h"
#include "ArxDbgTransientEntReactor.h"
#include "ArxDbgPersistentEntReactor.h"
#include "ArxDbgUtils.h"
#include "ArxDbgSelSet.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**	ArxDbgUiTdmReactors::ArxDbgUiTdmReactors
**
**	**jma
**
*************************************/

ArxDbgUiTdmReactors::ArxDbgUiTdmReactors(CWnd* parent)
:   CAcUiTabMainDialog(ArxDbgUiTdmReactors::IDD, parent, ArxDbgApp::getApp()->dllInstance())
{
	SetDialogName(_T("ArxDbg-Reactors"));

	m_tdcSysReactors = new ArxDbgUiTdcSysReactors;
	m_tdcTransientReactors = new ArxDbgUiTdcTransientReactors;
	m_tdcPersistentReactors = new ArxDbgUiTdcPersistentReactors;

    //{{AFX_DATA_INIT(ArxDbgUiTdmReactors)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**	ArxDbgUiTdmReactors::~ArxDbgUiTdmReactors
**
**	**jma
**
*************************************/

ArxDbgUiTdmReactors::~ArxDbgUiTdmReactors()
{
	delete m_tdcSysReactors;
	delete m_tdcTransientReactors;
	delete m_tdcPersistentReactors;
}

/****************************************************************************
**
**  ArxDbgUiTdmReactors::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdmReactors::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabMainDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdmReactors)
    DDX_Control(pDX, ARXDBG_TAB_1, m_tabCtrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdmReactors message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdmReactors, CAcUiTabMainDialog)
    //{{AFX_MSG_MAP(ArxDbgUiTdmReactors)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdmReactors message handlers

/****************************************************************************
**
**  ArxDbgUiTdmReactors::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdmReactors::OnInitDialog() 
{
    CAcUiTabMainDialog::OnInitDialog();

	SetAcadTabPointer(&m_tabCtrl);

	ASSERT(m_tdcSysReactors != NULL);

	AddTab(0, _T("System"), ArxDbgUiTdcSysReactors::IDD, m_tdcSysReactors);
	AddTab(1, _T("Transient Obj/Ent"), ArxDbgUiTdcTransientReactors::IDD, m_tdcTransientReactors);
	AddTab(2, _T("Persistent Obj/Ent"), ArxDbgUiTdcPersistentReactors::IDD, m_tdcPersistentReactors);
    
    return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiTdmReactors::attachEntTransientReactor
**
**  **jma
**
*************************************/

void
ArxDbgUiTdmReactors::attachEntTransientReactor(ArxDbgTransientEntReactor* entReactor)
{
	BeginEditorCommand();

	ArxDbgSelSet ss;
	if (ss.userSelect() != ArxDbgSelSet::kSelected) {
		CompleteEditorCommand();
		return;
	}

	Acad::ErrorStatus es;
	AcDbEntity* ent;
	long alreadyAttachedCount = 0;

	AcDbObjectIdArray objIds;
	ss.asArray(objIds);

	int len = objIds.length();
	for (int i=0; i<len; i++) {
		es = acdbOpenAcDbEntity(ent, objIds[i], AcDb::kForWrite);
		if (es == Acad::eOk) {
			if (entReactor->addToObject(ent) == FALSE)
				alreadyAttachedCount++;
			else {
				CString str;
				acutPrintf(_T("\nAttached to %s"), ArxDbgUtils::objToClassAndHandleStr(ent, str));
			}
			ent->close();
		}
		else
			ArxDbgUtils::rxErrorMsg(es);
	}

	if (alreadyAttachedCount > 0)
		acutPrintf(_T("\n%ld entities already had the reactor attached."), alreadyAttachedCount);

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiTdmReactors::detachEntTransientReactor
**
**  **jma
**
*************************************/

void
ArxDbgUiTdmReactors::detachEntTransientReactor(ArxDbgTransientEntReactor* entReactor)
{
	BeginEditorCommand();

	ArxDbgSelSet ss;
	if (ss.userSelect() != ArxDbgSelSet::kSelected) {
		CompleteEditorCommand();
		return;
	}

	Acad::ErrorStatus es;
	AcDbEntity* ent;
	long notAttachedCount = 0;

	AcDbObjectIdArray objIds;
	ss.asArray(objIds);

	int len = objIds.length();
	for (int i=0; i<len; i++) {
		es = acdbOpenAcDbEntity(ent, objIds[i], AcDb::kForWrite);
		if (es == Acad::eOk) {
			if (entReactor->delFromObject(ent) == FALSE)
				notAttachedCount++;
			else {
				CString str;
				acutPrintf(_T("\nDetached from %s"), ArxDbgUtils::objToClassAndHandleStr(ent, str));
			}
			ent->close();
		}
		else
			ArxDbgUtils::rxErrorMsg(es);
	}

	if (notAttachedCount > 0)
		acutPrintf(_T("\n%ld entities did not have the reactor attached."), notAttachedCount);

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiTdmReactors::attachEntPersistentReactor
**
**  **jma
**
*************************************/

void
ArxDbgUiTdmReactors::attachEntPersistentReactor()
{
	BeginEditorCommand();

	ArxDbgSelSet ss;
	if (ss.userSelect() != ArxDbgSelSet::kSelected) {
		CompleteEditorCommand();
		return;
	}

	Acad::ErrorStatus es;
	AcDbEntity* ent;
	ArxDbgPersistentEntReactor* peReactor;
	long alreadyAttachedCount = 0;

	AcDbObjectIdArray objIds;
	ss.asArray(objIds);

		// find the persistent reactor that goes with this database
	AcDbObjectId persistentId;
	if (objIds.isEmpty() == false)
		persistentId = ArxDbgUiTdcPersistentReactors::getPersistentEntReactor(objIds.first().database(), true);

	int len = objIds.length();
	for (int i=0; i<len; i++) {
		es = acdbOpenAcDbEntity(ent, objIds[i], AcDb::kForWrite);
		if (es == Acad::eOk) {
			if (hasPersistentReactor(ent, persistentId))
				alreadyAttachedCount++;
			else {
				ent->addPersistentReactor(persistentId);
				CString str;
				acutPrintf(_T("\nAttached to %s"), ArxDbgUtils::objToClassAndHandleStr(ent, str));

				es = acdbOpenObject(peReactor, persistentId, AcDb::kForWrite);
				if (es == Acad::eOk) {
					peReactor->attachTo(ent->objectId());
					peReactor->close();
				}
				else {
					acutPrintf(_T("\nERROR: Could not update backward reference in reactor: (%s)"), ArxDbgUtils::rxErrorStr(es));
				}
			}

			ent->close();
        }
		else
			ArxDbgUtils::rxErrorMsg(es);
	}

	if (alreadyAttachedCount > 0)
		acutPrintf(_T("\n%ld entities already had the reactor attached."), alreadyAttachedCount);

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiTdmReactors::detachEntPersistentReactor
**
**  **jma
**
*************************************/

void
ArxDbgUiTdmReactors::detachEntPersistentReactor()
{
	BeginEditorCommand();

	ArxDbgSelSet ss;
	if (ss.userSelect() != ArxDbgSelSet::kSelected) {
		CompleteEditorCommand();
		return;
	}

	Acad::ErrorStatus es;
	AcDbEntity* ent;
	ArxDbgPersistentEntReactor* peReactor;
	long notAttachedCount = 0;

	AcDbObjectIdArray objIds;
	ss.asArray(objIds);

		// find the persistent reactor that goes with this database
	AcDbObjectId persistentId;
	if (objIds.isEmpty() == false)
		persistentId = ArxDbgUiTdcPersistentReactors::getPersistentEntReactor(objIds.first().database(), true);

	int len = objIds.length();
	for (int i=0; i<len; i++) {
		es = acdbOpenAcDbEntity(ent, objIds[i], AcDb::kForWrite);
		if (es == Acad::eOk) {
			if (!hasPersistentReactor(ent, persistentId))
				notAttachedCount++;
			else {
				ent->removePersistentReactor(persistentId);
				CString str;
				acutPrintf(_T("\nDetached from %s"), ArxDbgUtils::objToClassAndHandleStr(ent, str));

				es = acdbOpenObject(peReactor, persistentId, AcDb::kForWrite);
				if (es == Acad::eOk) {
					peReactor->detachFrom(ent->objectId());
					peReactor->close();
				}
				else {
					acutPrintf(_T("\nERROR: Could not update backward reference in reactor: (%s)"), ArxDbgUtils::rxErrorStr(es));
				}
			}

			ent->close();
        }
		else
			ArxDbgUtils::rxErrorMsg(es);
	}

	if (notAttachedCount > 0)
		acutPrintf(_T("\n%ld entities did not have the reactor attached."), notAttachedCount);

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiTdmReactors::hasPersistentReactor
**
**  **jma
**
*************************************/

bool
ArxDbgUiTdmReactors::hasPersistentReactor(AcDbObject* obj, const AcDbObjectId& reactorId)
{
	void* pSomething;

    AcDbVoidPtrArray* reactors = obj->reactors();
    if (reactors != NULL) {
        for (int i=0; i<reactors->length(); i++) {
            pSomething = reactors->at(i);
			if (acdbPersistentReactorObjectId(pSomething) == reactorId)
                return true;
        }
    }
    return false;
}

/****************************************************************************
**
**  ArxDbgUiTdmReactors::cleanUpReactors
**		static function to allow app to clean up global pointers to reactors
**
**  **jma
**
*************************************/

void
ArxDbgUiTdmReactors::cleanUpReactors() 
{
	ArxDbgUiTdcSysReactors::cleanUpReactors();
	ArxDbgUiTdcTransientReactors::cleanUpReactors();
}

