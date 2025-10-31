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

#include "ArxDbgUiTdcObjReactorsBase.h"
#include "ArxDbgUiDlgObjState.h"
#include "ArxDbgUtils.h"
#include "ArxDbgApp.h"
#include "ArxDbgUiTdmREactors.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
**
**  ArxDbgUiTdcObjReactorsBase::ArxDbgUiTdcObjReactorsBase
**
**  **jma
**
*************************************/

ArxDbgUiTdcObjReactorsBase::ArxDbgUiTdcObjReactorsBase()
:   CAcUiTabChildDialog(NULL, ArxDbgApp::getApp()->dllInstance())
{
    //{{AFX_DATA_INIT(ArxDbgUiTdcObjReactorsBase)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiTdcObjReactorsBase::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcObjReactorsBase::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabChildDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdcObjReactorsBase)
	DDX_Control(pDX, ARXDBG_BN_ATTACH_ENT, m_attachEntButton);
	DDX_Control(pDX, ARXDBG_BN_DETACH_ENT, m_detachEntButton);
	DDX_Control(pDX, ARXDBG_BN_DETACH_SEL_ENTS, m_detachSelectedEntsButton);
	DDX_Control(pDX, ARXDBG_BN_DETACH_SEL_OBJS, m_detachSelectedObjsButton);
	DDX_Control(pDX, ARXDBG_LB_OBJS, m_lbObjList);
	DDX_Control(pDX, ARXDBG_LB_ENTS, m_lbEntList);
    DDX_Control(pDX, ARXDBG_EB_HANDLE, m_ebHandle);
    //}}AFX_DATA_MAP
}


/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcObjReactorsBase message handlers

BEGIN_MESSAGE_MAP(ArxDbgUiTdcObjReactorsBase, CAcUiTabChildDialog)
    //{{AFX_MSG_MAP(ArxDbgUiTdcObjReactorsBase)
    ON_BN_CLICKED(ARXDBG_BN_ATTACH_OBJ, OnObjAttach)
    ON_BN_CLICKED(ARXDBG_BN_ATTACH_ENT, OnEntAttach)
    ON_BN_CLICKED(ARXDBG_BN_DETACH_ENT, OnEntDetach)
    ON_BN_CLICKED(ARXDBG_BN_DETACH_SEL_ENTS, OnEntDetachSelected)
    ON_BN_CLICKED(ARXDBG_BN_DETACH_SEL_OBJS, OnObjDetachSelected)
    ON_LBN_SELCHANGE(ARXDBG_LB_OBJS, setButtonModes)
    ON_LBN_SELCHANGE(ARXDBG_LB_ENTS, setButtonModes)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcObjReactorsBase message handlers


/****************************************************************************
**
**  ArxDbgUiTdcObjReactorsBase::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdcObjReactorsBase::OnInitDialog() 
{
	CAcUiTabChildDialog::OnInitDialog();

    m_attachEntButton.AutoLoad();
    m_detachEntButton.AutoLoad();
    m_detachSelectedEntsButton.AutoLoad();
    m_detachSelectedObjsButton.AutoLoad();

	displayObjList();
	displayEntList();

	return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiTdcObjReactorsBase::PreTranslateMessage
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdcObjReactorsBase::PreTranslateMessage(MSG* pMsg) 
{
    if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN)) {
        CWnd *pWnd = GetFocus();
        if (pWnd != NULL) {
            UINT nID = pWnd->GetDlgCtrlID();
            if (nID == ARXDBG_BN_ATTACH_ENT) {
                ::PostMessage(m_attachEntButton.m_hWnd, BM_CLICK, 0, 0);
                return TRUE;
            }
            if (nID == ARXDBG_BN_DETACH_ENT) {
                ::PostMessage(m_detachEntButton.m_hWnd, BM_CLICK, 0, 0);
                return TRUE;
            }
            if (nID == ARXDBG_BN_DETACH_SEL_ENTS) {
                ::PostMessage(m_detachSelectedEntsButton.m_hWnd, BM_CLICK, 0, 0);
                return TRUE;
            }
            if (nID == ARXDBG_BN_DETACH_SEL_OBJS) {
                ::PostMessage(m_detachSelectedObjsButton.m_hWnd, BM_CLICK, 0, 0);
                return TRUE;
            }
        }
    }
	
	return CAcUiTabChildDialog::PreTranslateMessage(pMsg);
}

/****************************************************************************
**
**  ArxDbgUiTdcObjReactorsBase::displayObjList
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcObjReactorsBase::displayObjList() 
{
	m_objsAttached.setLogicalLength(0);
	m_lbObjList.ResetContent();

	getAttachedObjects(m_objsAttached);

	CString str;
	Acad::ErrorStatus es;
	AcDbObject* obj;

    int len = m_objsAttached.length();
    for (int i=0; i<len; i++) {
		es = acdbOpenAcDbObject(obj, m_objsAttached[i], AcDb::kForRead, true);
		if (es == Acad::eOk) {
			ArxDbgUtils::objToClassAndHandleStr(obj, str);
			if (obj->isErased())
				str += _T("  (erased)");

			m_lbObjList.AddString(str);

			obj->close();
		}
    }

	setButtonModes();
}

/****************************************************************************
**
**  ArxDbgUiTdcObjReactorsBase::displayEntList
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcObjReactorsBase::displayEntList() 
{
	m_entsAttached.setLogicalLength(0);
	m_lbEntList.ResetContent();

	getAttachedEntities(m_entsAttached);

	CString str;
	Acad::ErrorStatus es;
	AcDbObject* obj;

    int len = m_entsAttached.length();
    for (int i=0; i<len; i++) {
		es = acdbOpenAcDbObject(obj, m_entsAttached[i], AcDb::kForRead, true);
		if (es == Acad::eOk) {
			ArxDbgUtils::objToClassAndHandleStr(obj, str);

			if (obj->isErased())
				str += _T("  (erased)");

			m_lbEntList.AddString(str);

			obj->close();
		}
    }

	setButtonModes();
}

/****************************************************************************
**
**  ArxDbgUiTdcObjReactorsBase::setButtonModes
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcObjReactorsBase::setButtonModes()
{
	m_detachSelectedObjsButton.EnableWindow((m_lbObjList.GetSelCount() > 0));
    m_detachSelectedEntsButton.EnableWindow((m_lbEntList.GetSelCount() > 0));

	m_detachEntButton.EnableWindow((m_entsAttached.isEmpty() != true));
}

/****************************************************************************
**
**  ArxDbgUiTdcObjReactorsBase::OnObjAttach
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcObjReactorsBase::OnObjAttach() 
{
    CString newHandle, str;
    AcDbObjectId objId;

        // see if specified handle is valid
    m_ebHandle.GetWindowText(newHandle);
    if (ArxDbgUtils::handleStrToObjId(acdbHostApplicationServices()->workingDatabase(),
					newHandle, objId, false) != Acad::eOk) {
        str.Format(_T("\"%s\" is not a valid handle."), newHandle);
        ArxDbgUtils::alertBox(str);
        m_ebHandle.SetSel(0, -1); // reset to select all
        m_ebHandle.SetFocus();
        return;
    }

	AcDbObjectIdArray newObjIds;
	newObjIds.append(objId);

	attachObjReactors(newObjIds);

    m_ebHandle.SetWindowText(_T(""));    // reset edit box to be empty for new handle

	displayObjList();
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::OnEntAttach
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcObjReactorsBase::OnEntAttach()
{
	attachEntReactors();
	displayEntList();
}

/****************************************************************************
**
**  ArxDbgUiTdcObjReactorsBase::OnEntDetach
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcObjReactorsBase::OnEntDetach()
{
	detachEntReactors();
	displayEntList();
}

/****************************************************************************
**
**  ArxDbgUiTdcObjReactorsBase::OnEntDetachSelected
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcObjReactorsBase::OnEntDetachSelected() 
{
	AcDbObjectIdArray selObjIds;

    int count = m_lbEntList.GetSelCount();
    if (count > 0) {
        int* intArray = new int[count];
        if (m_lbEntList.GetSelItems(count, intArray) != LB_ERR) {
            for (int i=0; i<count; i++) {
                selObjIds.append(m_entsAttached[intArray[i]]);
            }
        }
        delete [] intArray;
	}

	detachSelectedEnts(selObjIds);
	displayEntList();
}

/****************************************************************************
**
**  ArxDbgUiTdcObjReactorsBase::OnObjDetachSelected
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcObjReactorsBase::OnObjDetachSelected() 
{
	AcDbObjectIdArray selObjIds;

    int count = m_lbObjList.GetSelCount();
    if (count > 0) {
        int* intArray = new int[count];
        if (m_lbObjList.GetSelItems(count, intArray) != LB_ERR) {
            for (int i=0; i<count; i++) {
                selObjIds.append(m_objsAttached[intArray[i]]);
            }
        }
        delete [] intArray;
	}

	detachSelectedObjs(selObjIds);
	displayObjList();
}


/****************************************************************************
**
**  ArxDbgUiTdcObjReactorsBase::doStateDbox
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcObjReactorsBase::doStateDbox(const AcDbObject* obj, LPCTSTR dboxTitle)
{
        // purposely throw away const for testing purposes
    ArxDbgUiDlgObjState dbox(acedGetAcadDwgView(), const_cast<AcDbObject*>(obj), dboxTitle);
    dbox.DoModal();
}

/****************************************************************************
**
**  ArxDbgUiTdcObjReactorsBase::doStateDbox
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcObjReactorsBase::doStateDbox(const AcDbObjectId& objId, LPCTSTR dboxTitle)
{
    ArxDbgUiDlgObjState dbox(acedGetAcadDwgView(), objId, dboxTitle);
    dbox.DoModal();
}

