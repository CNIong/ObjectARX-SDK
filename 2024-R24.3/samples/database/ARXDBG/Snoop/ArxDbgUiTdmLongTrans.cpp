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

#include "ArxDbgUiTdmLongTrans.h"
#include "ArxDbgUiTdcLongTrans.h"
#include "ArxDbgApp.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**	ArxDbgUiTdmLongTrans::ArxDbgUiTdmLongTrans
**
**	**jma
**
*************************************/

ArxDbgUiTdmLongTrans::ArxDbgUiTdmLongTrans(AcDbLongTransaction* lt, CWnd* parent, const TCHAR* winTitle)
:   CAcUiTabMainDialog(ArxDbgUiTdmLongTrans::IDD, parent, ArxDbgApp::getApp()->dllInstance())
{
	SetDialogName(_T("ArxDbg-LongTrans"));

	ASSERT(lt != NULL);

	if (winTitle != NULL)
		m_winTitle = winTitle;

	m_tdcLongTrans = new ArxDbgUiTdcLongTrans(lt);

    //{{AFX_DATA_INIT(ArxDbgUiTdmLongTrans)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**	ArxDbgUiTdmLongTrans::~ArxDbgUiTdmLongTrans
**
**	**jma
**
*************************************/

ArxDbgUiTdmLongTrans::~ArxDbgUiTdmLongTrans()
{
	delete m_tdcLongTrans;
}

/****************************************************************************
**
**  ArxDbgUiTdmLongTrans::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdmLongTrans::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabMainDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdmLongTrans)
    DDX_Control(pDX, ARXDBG_TAB_1, m_tabCtrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdmLongTrans message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdmLongTrans, CAcUiTabMainDialog)
    //{{AFX_MSG_MAP(ArxDbgUiTdmLongTrans)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdmLongTrans message handlers

/****************************************************************************
**
**  ArxDbgUiTdmLongTrans::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdmLongTrans::OnInitDialog() 
{
    CAcUiTabMainDialog::OnInitDialog();

	if (m_winTitle.IsEmpty() == FALSE)
		SetWindowText(m_winTitle);

	SetAcadTabPointer(&m_tabCtrl);

	AddTab(0, _T("Long Transaction"),  ArxDbgUiTdcLongTrans::IDD,   m_tdcLongTrans);
    
    return TRUE;
}

