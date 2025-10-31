// (C) Copyright 1996-2006 by Autodesk, Inc. 
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
// MainFrm.cpp : implementation of the CMainFrame class
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <acdocman.h>



static HWND hWndACAD = NULL;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame() //: m_pManager(NULL)
{
	// TODO: add member initialization code here
//    m_pManager = curDoc()->inputPointManager();
//	m_pManager->disableSystemCursorGraphics();
}

CMainFrame::~CMainFrame()
{
//	m_pManager->enableSystemCursorGraphics();
}

BOOL CMainFrame::Create(LPCTSTR szTitle, LONG style /* = 0 */,
	const RECT& rect /* = rectDefault */,
	CWnd* parent /* = NULL */)
{

	// Register a custom WndClass and create a window.
	// This must be done because CBounceWnd has a custom cursor, and
	//  no icon.
	const TCHAR* pszTreeListClass =
        AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW ,
			LoadCursor(NULL, IDC_ARROW),
			(HBRUSH)(COLOR_WINDOW+1),
			NULL);
	return CFrameWnd::Create(pszTreeListClass, szTitle, style, rect, acedGetAcadFrame());
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
 	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#if defined(_DEBUG ) && defined(DEBUG_AUTOCAD)
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG && DEBUG_AUTOCAD

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class 
	if (!m_wndSplitter.CreateStatic(this, 2, 1))
	{
		TRACE(_T("Failed to CreateStaticSplitter\n"));
		return FALSE;
	}

	// add the first splitter pane - the default view in column 0
	if (!m_wndSplitter.CreateView(0, 0,
		RUNTIME_CLASS(CArxdrawView), CSize(110, 110), pContext))
	{
		TRACE(_T("Failed to create first pane\n"));
		return FALSE;
	}

	// add the second splitter pane - an input view in column 1
	if (!m_wndSplitter.CreateView(1, 0,
		RUNTIME_CLASS(CArxSliderVw), CSize(50, 15), pContext))
	{
		TRACE(_T("Failed to create second pane\n"));
		return FALSE;
	}

	// activate the input view
        CArxSliderVw *pView = (CArxSliderVw *) m_wndSplitter.GetPane(1,0);
        CArxdrawView *pDrawVw = (CArxdrawView *) m_wndSplitter.GetPane(0,0);
           
        pView->m_pCirView = pDrawVw;
        CenterWindow();

        return TRUE;

}

BOOL CMainFrame::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	return CFrameWnd::DestroyWindow();
}
