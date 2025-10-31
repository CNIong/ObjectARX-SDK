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

#include "ArxDbgUiTdmObjects.h"
#include "ArxDbgUiTdcObjects.h"
#include "ArxDbgApp.h"
#include "ArxDbgSelSet.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**	ArxDbgUiTdmObjects::ArxDbgUiTdmObjects
**
**	**jma
**
*************************************/

ArxDbgUiTdmObjects::ArxDbgUiTdmObjects(const AcDbObjectIdArray& objIds, CWnd* parent, const TCHAR* winTitle)
:   CAcUiTabMainDialog(ArxDbgUiTdmObjects::IDD, parent, ArxDbgApp::getApp()->dllInstance())
{
	SetDialogName(_T("ArxDbg-Objects"));

	if (winTitle != NULL)
		m_winTitle = winTitle;

	m_tdcObjs = new ArxDbgUiTdcObjects(objIds);

    //{{AFX_DATA_INIT(ArxDbgUiTdmObjects)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**	ArxDbgUiTdmObjects::~ArxDbgUiTdmObjects
**
**	**jma
**
*************************************/

ArxDbgUiTdmObjects::~ArxDbgUiTdmObjects()
{
	delete m_tdcObjs;
}

/****************************************************************************
**
**  ArxDbgUiTdmObjects::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdmObjects::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabMainDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdmObjects)
    DDX_Control(pDX, ARXDBG_TAB_1, m_tabCtrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdmObjects message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdmObjects, CAcUiTabMainDialog)
    //{{AFX_MSG_MAP(ArxDbgUiTdmObjects)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdmObjects message handlers

/****************************************************************************
**
**  ArxDbgUiTdmObjects::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdmObjects::OnInitDialog() 
{
    CAcUiTabMainDialog::OnInitDialog();

	if (m_winTitle.IsEmpty() == FALSE)
		SetWindowText(m_winTitle);

	SetAcadTabPointer(&m_tabCtrl);

	AddTab(0, _T("Objects"),  ArxDbgUiTdcObjects::IDD, m_tdcObjs);

    return TRUE;
}

