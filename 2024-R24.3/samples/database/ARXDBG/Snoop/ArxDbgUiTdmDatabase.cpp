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

