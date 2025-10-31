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

#include "ArxDbgUiTdmDatabase.h"
#include "ArxDbgUiTdcSymTbl.h"
#include "ArxDbgUiTdcDict.h"
#include "ArxDbgUiTdcDatabase.h"
#include "ArxDbgApp.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**	ArxDbgUiTdmDatabase::ArxDbgUiTdmDatabase
**
**	**jma
**
*************************************/

ArxDbgUiTdmDatabase::ArxDbgUiTdmDatabase(AcDbDatabase* db, CWnd* parent, const TCHAR* winTitle)
:   CAcUiTabMainDialog(ArxDbgUiTdmDatabase::IDD, parent, ArxDbgApp::getApp()->dllInstance()),
	m_db(db)
{
	SetDialogName(_T("ArxDbg-Database"));

	ASSERT(db != NULL);

	if (winTitle != NULL)
		m_winTitle = winTitle;

	m_tdcSymTbl = new ArxDbgUiTdcSymTbl(db);
	m_tdcDicts = new ArxDbgUiTdcDict(db->namedObjectsDictionaryId(), false);
	m_tdcDb = new ArxDbgUiTdcDatabase(db);

    //{{AFX_DATA_INIT(ArxDbgUiTdmDatabase)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**	ArxDbgUiTdmDatabase::ArxDbgUiTdmDatabase
**
**	**jma
**
*************************************/

ArxDbgUiTdmDatabase::ArxDbgUiTdmDatabase(const AcDbObjectId& dictId, CWnd* parent, const TCHAR* winTitle)
:   CAcUiTabMainDialog(ArxDbgUiTdmDatabase::IDD, parent, ArxDbgApp::getApp()->dllInstance()),
	m_db(dictId.database())
{
	SetDialogName(_T("ArxDbg-Database"));

	if (winTitle != NULL)
		m_winTitle = winTitle;

	m_tdcSymTbl = NULL;
	m_tdcDicts = new ArxDbgUiTdcDict(dictId, true);
	m_tdcDb = NULL;

    //{{AFX_DATA_INIT(ArxDbgUiTdmDatabase)
    //}}AFX_DATA_INIT
}


/****************************************************************************
**
**	ArxDbgUiTdmDatabase::~ArxDbgUiTdmDatabase
**
**	**jma
**
*************************************/

ArxDbgUiTdmDatabase::~ArxDbgUiTdmDatabase()
{
	delete m_tdcSymTbl;
	delete m_tdcDicts;
	delete m_tdcDb;
}

/****************************************************************************
**
**  ArxDbgUiTdmDatabase::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdmDatabase::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabMainDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdmDatabase)
    DDX_Control(pDX, ARXDBG_TAB_1, m_tabCtrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdmDatabase message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdmDatabase, CAcUiTabMainDialog)
    //{{AFX_MSG_MAP(ArxDbgUiTdmDatabase)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdmDatabase message handlers

/****************************************************************************
**
**  ArxDbgUiTdmDatabase::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdmDatabase::OnInitDialog() 
{
    CAcUiTabMainDialog::OnInitDialog();

	if (m_winTitle.IsEmpty() == FALSE)
		SetWindowText(m_winTitle);

	SetAcadTabPointer(&m_tabCtrl);

	int i = 0;

	if (m_tdcSymTbl)
		AddTab(i++, _T("Symbol Tables"),  ArxDbgUiTdcSymTbl::IDD,   m_tdcSymTbl);

	if (m_tdcDicts)
		AddTab(i++, _T("Dictionaries"),   ArxDbgUiTdcDict::IDD,     m_tdcDicts);

	if (m_tdcDb)
		AddTab(i++, _T("Database"),       ArxDbgUiTdcDatabase::IDD, m_tdcDb);
    
    return TRUE;
}

