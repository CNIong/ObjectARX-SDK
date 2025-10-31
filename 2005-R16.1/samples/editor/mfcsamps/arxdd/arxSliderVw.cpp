// (C) Copyright 1996 by Autodesk, Inc. 
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
// ArxSliderVw.cpp : implementation file
//
#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// CArxSliderVw

IMPLEMENT_DYNCREATE(CArxSliderVw, CFormView)

CArxSliderVw::CArxSliderVw()
	: CFormView(CArxSliderVw::IDD)
{
	//{{AFX_DATA_INIT(CArxSliderVw)
	//}}AFX_DATA_INIT
}

CArxSliderVw::~CArxSliderVw()
{
}

void CArxSliderVw::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArxSliderVw)
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArxSliderVw, CFormView)
	//{{AFX_MSG_MAP(CArxSliderVw)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArxSliderVw diagnostics

#if defined(_DEBUG ) && defined(DEBUG_AUTOCAD)
void CArxSliderVw::AssertValid() const
{
	CFormView::AssertValid();
}

void CArxSliderVw::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG && DEBUG_AUTOCAD

/////////////////////////////////////////////////////////////////////////////
// CArxSliderVw message handlers

BOOL CArxSliderVw::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style = WS_VISIBLE | WS_DLGFRAME | WS_CHILD;

        return CFormView::PreCreateWindow(cs);
}


void CArxSliderVw::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

        CSliderCtrl* pSlide = (CSliderCtrl*) pScrollBar;
        
        m_pCirView->m_sliderVal = pSlide->GetPos();
	m_pCirView->Invalidate(0);
	//CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CArxSliderVw::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	m_slider.SetRange(1,10);
        m_slider.SetPos(1);
	// TODO: Add your specialized code here and/or call the base class
	
}
