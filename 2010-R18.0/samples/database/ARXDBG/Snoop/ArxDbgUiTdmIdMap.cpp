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

