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

#include "ArxDbgUiTdmTransDbClones.h"
#include "ArxDbgUiTdcCloneSet.h"
#include "ArxDbgUiTdcWblockClone.h"
#include "ArxDbgUiTdcInsert.h"
#include "ArxDbgApp.h"
#include "ArxDbgSelSet.h"
#include "ArxDbgUiPrompts.h"
#include "ArxDbgUtils.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**	ArxDbgUiTdmTransDbClones::ArxDbgUiTdmTransDbClones
**
**	**jma
**
*************************************/

ArxDbgUiTdmTransDbClones::ArxDbgUiTdmTransDbClones(CWnd* parent, const TCHAR* winTitle)
:   CAcUiTabMainDialog(ArxDbgUiTdmTransDbClones::IDD, parent, ArxDbgApp::getApp()->dllInstance())
{
	SetDialogName(_T("ArxDbg-TransDbClones"));

	if (winTitle != NULL)
		m_winTitle = winTitle;

	m_tdcCloneSet = new ArxDbgUiTdcCloneSet;
	m_tdcWblockClone = new ArxDbgUiTdcWblockClone;
	m_tdcInsert = new ArxDbgUiTdcInsert;

    //{{AFX_DATA_INIT(ArxDbgUiTdmTransDbClones)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**	ArxDbgUiTdmTransDbClones::~ArxDbgUiTdmTransDbClones
**
**	**jma
**
*************************************/

ArxDbgUiTdmTransDbClones::~ArxDbgUiTdmTransDbClones()
{
	delete m_tdcCloneSet;
	delete m_tdcWblockClone;
	delete m_tdcInsert;
}

/****************************************************************************
**
**  ArxDbgUiTdmTransDbClones::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdmTransDbClones::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabMainDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdmTransDbClones)
    DDX_Control(pDX, ARXDBG_TAB_1, m_tabCtrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdmTransDbClones message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdmTransDbClones, CAcUiTabMainDialog)
    //{{AFX_MSG_MAP(ArxDbgUiTdmTransDbClones)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdmTransDbClones message handlers

/****************************************************************************
**
**  ArxDbgUiTdmTransDbClones::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdmTransDbClones::OnInitDialog() 
{
    CAcUiTabMainDialog::OnInitDialog();

	if (m_winTitle.IsEmpty() == FALSE)
		SetWindowText(m_winTitle);

	SetAcadTabPointer(&m_tabCtrl);

	AddTab(0, _T("Clone Set"),     ArxDbgUiTdcCloneSet::IDD,    m_tdcCloneSet);
	AddTab(1, _T("Wblock Clone"),  ArxDbgUiTdcWblockClone::IDD, m_tdcWblockClone);
	AddTab(2, _T("Insert"),        ArxDbgUiTdcInsert::IDD,      m_tdcInsert);
    
    return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiTdmTransDbClones::addToCloneSet
**
**  **jma
**
*************************************/

void
ArxDbgUiTdmTransDbClones::addToCloneSet(ArxDbgCloneSet& cloneSet)
{
	BeginEditorCommand();

	ArxDbgSelSet ss;
	if (ss.userSelect() != ArxDbgSelSet::kSelected) {
		CompleteEditorCommand();
		return;
	}

	AcDbObjectIdArray objIds;
	ss.asArray(objIds);

	cloneSet.addObjects(objIds);

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiTdmTransDbClones::getBasePoint
**
**  **jma
**
*************************************/

void
ArxDbgUiTdmTransDbClones::getBasePoint(AcGePoint3d& basePt)
{
	BeginEditorCommand();

	ArxDbgUiPrPoint prPt(_T("Base point"), NULL);
	if (prPt.go() == ArxDbgUiPrPoint::kOk)
		basePt = ArxDbgUtils::ucsToWcs(prPt.value());

	CompleteEditorCommand();
}

