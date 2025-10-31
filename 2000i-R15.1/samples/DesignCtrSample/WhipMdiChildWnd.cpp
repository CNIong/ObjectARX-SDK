//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
// WhipMdiChildWnd.cpp : implementation file
//

#include "stdafx.h"
#include "DesignCtrSample.h"
#include "WhipMdiChildWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWhipMdiChildWnd

IMPLEMENT_DYNCREATE(CWhipMdiChildWnd, CMDIChildWnd)

CWhipMdiChildWnd::CWhipMdiChildWnd() : CMDIChildWnd()
{
	m_pWhip = new CWhip;
}

CWhipMdiChildWnd::~CWhipMdiChildWnd()
{
	if(m_pWhip)
		delete m_pWhip;
}


BEGIN_MESSAGE_MAP(CWhipMdiChildWnd, CMDIChildWnd)
	//{{AFX_MSG_MAP(CWhipMdiChildWnd)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWhipMdiChildWnd message handlers

BOOL CWhipMdiChildWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, 
							  DWORD dwStyle, const RECT& rect, 
							  CMDIFrameWnd* pParentWnd, CCreateContext* pContext) 
{
	BOOL bRet = CMDIChildWnd::Create(lpszClassName, lpszWindowName, 
		dwStyle, rect, pParentWnd, pContext);
	if(bRet)
	{
		CRect rect;
		GetClientRect(&rect);
		ASSERT(!rect.IsRectEmpty());

		BOOL b = m_pWhip->Create(NULL, WS_CHILD | WS_VISIBLE | WS_MAXIMIZE, 
			rect, this, 0L);
		ASSERT(b);

		m_pWhip->SetUserInterfaceEnabled(true);
		m_pWhip->SetStreamName(m_csDwfFileName);
	}

	return bRet;
}

void CWhipMdiChildWnd::OnSize(UINT nType, int cx, int cy) 
{
	CMDIChildWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!m_pWhip->m_hWnd)
		return;
	CRect rect;
	GetWindowRect(rect) ;
	ScreenToClient (rect) ;
	rect.right = cx - rect.left;
	rect.bottom = cy - rect.left;
	m_pWhip->MoveWindow(rect, TRUE);	
}
