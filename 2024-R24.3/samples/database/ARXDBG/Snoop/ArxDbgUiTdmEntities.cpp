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

