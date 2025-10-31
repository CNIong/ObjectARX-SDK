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

