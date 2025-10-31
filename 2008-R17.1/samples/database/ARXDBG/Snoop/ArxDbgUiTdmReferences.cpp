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

#include "ArxDbgUiTdmReferences.h"
#include "ArxDbgUiTdcReferences.h"
#include "ArxDbgApp.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**	ArxDbgUiTdmReferences::ArxDbgUiTdmReferences
**
**	**jma
**
*************************************/

ArxDbgUiTdmReferences::ArxDbgUiTdmReferences(const AcDbObjectIdArray& hardPointerIds,
											 const AcDbObjectIdArray& softPointerIds,
											 const AcDbObjectIdArray& hardOwnershipIds,
											 const AcDbObjectIdArray& softOwnershipIds,
											 CWnd* parent, const TCHAR* winTitle)
:   CAcUiTabMainDialog(ArxDbgUiTdmReferences::IDD, parent, ArxDbgApp::getApp()->dllInstance())
{
	SetDialogName(_T("ArxDbg-References"));

	if (winTitle != NULL)
		m_winTitle = winTitle;

	m_tdcRefs = new ArxDbgUiTdcReferences(hardPointerIds, softPointerIds, hardOwnershipIds, softOwnershipIds);

    //{{AFX_DATA_INIT(ArxDbgUiTdmReferences)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**	ArxDbgUiTdmReferences::~ArxDbgUiTdmReferences
**
**	**jma
**
*************************************/

ArxDbgUiTdmReferences::~ArxDbgUiTdmReferences()
{
	delete m_tdcRefs;
}

/****************************************************************************
**
**  ArxDbgUiTdmReferences::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdmReferences::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabMainDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdmReferences)
    DDX_Control(pDX, ARXDBG_TAB_1, m_tabCtrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdmReferences message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdmReferences, CAcUiTabMainDialog)
    //{{AFX_MSG_MAP(ArxDbgUiTdmReferences)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdmReferences message handlers

/****************************************************************************
**
**  ArxDbgUiTdmReferences::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdmReferences::OnInitDialog() 
{
    CAcUiTabMainDialog::OnInitDialog();

	if (m_winTitle.IsEmpty() == FALSE)
		SetWindowText(m_winTitle);

	SetAcadTabPointer(&m_tabCtrl);

	AddTab(0, _T("References"),  ArxDbgUiTdcReferences::IDD,   m_tdcRefs);

    return TRUE;
}

