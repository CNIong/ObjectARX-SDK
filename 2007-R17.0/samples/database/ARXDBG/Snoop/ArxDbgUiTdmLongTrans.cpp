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

