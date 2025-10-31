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

#include "ArxDbgUiTdmEntities.h"
#include "ArxDbgUiTdcEntities.h"
#include "ArxDbgApp.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**	ArxDbgUiTdmEntities::ArxDbgUiTdmEntities
**
**	**jma
**
*************************************/

ArxDbgUiTdmEntities::ArxDbgUiTdmEntities(const AcDbObjectIdArray& ents, bool isBlkDef, CWnd* parent, const TCHAR* winTitle)
:   CAcUiTabMainDialog(ArxDbgUiTdmEntities::IDD, parent, ArxDbgApp::getApp()->dllInstance())
{
	SetDialogName(_T("ArxDbg-Entities"));

	if (winTitle != NULL)
		m_winTitle = winTitle;

	m_tdcEnts = new ArxDbgUiTdcEntities(ents, isBlkDef);

    //{{AFX_DATA_INIT(ArxDbgUiTdmEntities)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**	ArxDbgUiTdmEntities::~ArxDbgUiTdmEntities
**
**	**jma
**
*************************************/

ArxDbgUiTdmEntities::~ArxDbgUiTdmEntities()
{
	delete m_tdcEnts;
}

/****************************************************************************
**
**  ArxDbgUiTdmEntities::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdmEntities::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabMainDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdmEntities)
    DDX_Control(pDX, ARXDBG_TAB_1, m_tabCtrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdmEntities message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdmEntities, CAcUiTabMainDialog)
    //{{AFX_MSG_MAP(ArxDbgUiTdmEntities)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdmEntities message handlers

/****************************************************************************
**
**  ArxDbgUiTdmEntities::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdmEntities::OnInitDialog() 
{
    CAcUiTabMainDialog::OnInitDialog();

	if (m_winTitle.IsEmpty() == FALSE)
		SetWindowText(m_winTitle);

	SetAcadTabPointer(&m_tabCtrl);

	AddTab(0, _T("Entities"),  ArxDbgUiTdcEntities::IDD,   m_tdcEnts);

    return TRUE;
}

