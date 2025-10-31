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

#include "ArxDbgUiTdmEditor.h"
#include "ArxDbgUiTdcDocs.h"
#include "ArxDbgUiTdcClasses.h"
#include "ArxDbgUiTdcCmds.h"
#include "ArxDbgUiTdcHostAppSrv.h"
#include "ArxDbgApp.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**	ArxDbgUiTdmEditor::ArxDbgUiTdmEditor
**
**	**jma
**
*************************************/

ArxDbgUiTdmEditor::ArxDbgUiTdmEditor(CWnd* parent)
:   CAcUiTabMainDialog(ArxDbgUiTdmEditor::IDD, parent, ArxDbgApp::getApp()->dllInstance())
{
	SetDialogName(_T("ArxDbg-Editor"));

	m_tdcDocs = new ArxDbgUiTdcDocs;
	m_tdcClasses = new ArxDbgUiTdcClasses;
	m_tdcCommands = new ArxDbgUiTdcCmds;
	m_tdcHostAppSrv = new ArxDbgUiTdcHostAppSrv;

    //{{AFX_DATA_INIT(ArxDbgUiTdmEditor)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**	ArxDbgUiTdmEditor::ArxDbgUiTdmEditor
**
**	**jma
**
*************************************/

ArxDbgUiTdmEditor::ArxDbgUiTdmEditor(CWnd* parent, AcApDocument* doc)
:   CAcUiTabMainDialog(ArxDbgUiTdmEditor::IDD, parent, ArxDbgApp::getApp()->dllInstance())
{
	SetDialogName(_T("ArxDbg-Editor"));

	ASSERT(doc != NULL);

	m_tdcDocs = new ArxDbgUiTdcDocs(doc);
	m_tdcClasses = NULL;
	m_tdcCommands = NULL;
	m_tdcHostAppSrv = NULL;

    //{{AFX_DATA_INIT(ArxDbgUiTdmEditor)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**	ArxDbgUiTdmEditor::~ArxDbgUiTdmEditor
**
**	**jma
**
*************************************/

ArxDbgUiTdmEditor::~ArxDbgUiTdmEditor()
{
	delete m_tdcDocs;
	delete m_tdcClasses;
	delete m_tdcCommands;
	delete m_tdcHostAppSrv;
}

/****************************************************************************
**
**  ArxDbgUiTdmEditor::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdmEditor::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabMainDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdmEditor)
    DDX_Control(pDX, ARXDBG_TAB_1, m_tabCtrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdmEditor message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdmEditor, CAcUiTabMainDialog)
    //{{AFX_MSG_MAP(ArxDbgUiTdmEditor)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdmEditor message handlers

/****************************************************************************
**
**  ArxDbgUiTdmEditor::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdmEditor::OnInitDialog() 
{
    CAcUiTabMainDialog::OnInitDialog();

	SetAcadTabPointer(&m_tabCtrl);

	ASSERT(m_tdcDocs != NULL);
	int i = 0;

	AddTab(i++, _T("Documents"), ArxDbgUiTdcDocs::IDD,     m_tdcDocs);

		// if constructor with Docs only called, we don't add these two pages
	if (m_tdcClasses)
		AddTab(i++, _T("Classes"),   ArxDbgUiTdcClasses::IDD, m_tdcClasses);

	if (m_tdcCommands)
		AddTab(i++, _T("Commands"),  ArxDbgUiTdcCmds::IDD, m_tdcCommands);

	if (m_tdcHostAppSrv)
		AddTab(i++, _T("Host App Services"),  ArxDbgUiTdcHostAppSrv::IDD, m_tdcHostAppSrv);

    return TRUE;
}

