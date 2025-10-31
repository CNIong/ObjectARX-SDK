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

#include "ArxDbgUiTdmIdMap.h"
#include "ArxDbgUiTdcIdMap.h"
#include "ArxDbgApp.h"
#include "ArxDbgSelSet.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**	ArxDbgUiTdmIdMap::ArxDbgUiTdmIdMap
**
**	**jma
**
*************************************/

ArxDbgUiTdmIdMap::ArxDbgUiTdmIdMap(AcDbIdMapping* idMap, CWnd* parent, const TCHAR* winTitle)
:   CAcUiTabMainDialog(ArxDbgUiTdmIdMap::IDD, parent, ArxDbgApp::getApp()->dllInstance())
{
	SetDialogName(_T("ArxDbg-IdMap"));

	if (winTitle != NULL)
		m_winTitle = winTitle;

	m_tdcIdMap = new ArxDbgUiTdcIdMap(idMap);

    //{{AFX_DATA_INIT(ArxDbgUiTdmIdMap)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**	ArxDbgUiTdmIdMap::~ArxDbgUiTdmIdMap
**
**	**jma
**
*************************************/

ArxDbgUiTdmIdMap::~ArxDbgUiTdmIdMap()
{
	delete m_tdcIdMap;
}

/****************************************************************************
**
**  ArxDbgUiTdmIdMap::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdmIdMap::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabMainDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdmIdMap)
    DDX_Control(pDX, ARXDBG_TAB_1, m_tabCtrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdmIdMap message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdmIdMap, CAcUiTabMainDialog)
    //{{AFX_MSG_MAP(ArxDbgUiTdmIdMap)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdmIdMap message handlers

/****************************************************************************
**
**  ArxDbgUiTdmIdMap::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdmIdMap::OnInitDialog() 
{
    CAcUiTabMainDialog::OnInitDialog();

	if (m_winTitle.IsEmpty() == FALSE)
		SetWindowText(m_winTitle);

	SetAcadTabPointer(&m_tabCtrl);

	AddTab(0, _T("Id Mapping"), ArxDbgUiTdcIdMap::IDD, m_tdcIdMap);

    return TRUE;
}

