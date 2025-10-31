// (C) Copyright 1996,1998 by Autodesk, Inc. 
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
// arxdrawView.cpp : implementation of the CArxdrawView class
//
#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// CArxdrawView

IMPLEMENT_DYNCREATE(CArxdrawView, CView)

BEGIN_MESSAGE_MAP(CArxdrawView, CView)
	//{{AFX_MSG_MAP(CArxdrawView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL acedStartOverrideDropTarget(COleDropTarget* pTarget);
BOOL acedEndOverrideDropTarget(COleDropTarget* pTarget);
BOOL acedAddDropTarget(COleDropTarget* pTarget);
BOOL acedRemoveDropTarget(COleDropTarget* pTarget);

/////////////////////////////////////////////////////////////////////////////
// CArxdrawView construction/destruction

CArxdrawView::CArxdrawView() :
m_sliderVal(1)
{
	// TODO: add construction code here
}

CArxdrawView::~CArxdrawView()
{
}

BOOL CArxdrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CArxdrawView drawing

void CArxdrawView::OnDraw(CDC* pDC)
{
	// TODO: add draw code for native data here
    CRect rect;
	GetClientRect(rect);
    CPoint centerPt = rect.CenterPoint();

	CString szStr;
    szStr.Format(" Size: %d ", m_sliderVal);	
    
    pDC->MoveTo(rect.Width()/2,0);
    pDC->LineTo(rect.Width()/2,rect.Height()-25);
    pDC->MoveTo(0,(rect.Height()/2)-10);
    pDC->LineTo(rect.Width(),(rect.Height()/2)-10);

    pDC->MoveTo(0, rect.Height()-25 );
    pDC->LineTo(rect.Width(),rect.Height()-25);

    pDC->Ellipse(CRect(CPoint(12,5), CSize(35, 35)));

    POINT square[] = { {13,50}, {13, 80}, {43, 80}, {43,50}, {13,50}};
    pDC->Polyline(square, 5);

    POINT triag[] = { {95, 5}, {80,37}, {110,37}, {95,5}};
    pDC->Polyline(triag, 4);

    POINT triag2[] = {{95, 80}, {80,50}, {110,50}, {95,80}};
    pDC->Polyline(triag2, 4);

    pDC->DrawText(szStr, szStr.GetLength(),rect, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);

}

/////////////////////////////////////////////////////////////////////////////
// CArxdrawView diagnostics

#if defined(_DEBUG) && defined(DEBUG_AUTOCAD)
void CArxdrawView::AssertValid() const
{
	CView::AssertValid();
}

void CArxdrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

#endif //_DEBUG && DEBUG_AUTOCAD



/////////////////////////////////////////////////////////////////////////////
// CArxdrawView message handlers


void CArxdrawView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

    CPoint local = point;
    m_lastPoint = local;

    // find out which object is selected
    // 0 = circle
    // 1 - square
    // 2 - up triangle
    // 3 - down triangle
    int objType = -1;

    if (point.x < 65)
    { // circle or square
      if (point.y < 45)
        objType = 0;
      else
        objType = 1;
    }
    else
    {
      if (point.y < 45)
        objType = 2;
      else
        objType = 3;
    }
    
    COleDataSource *pSource = generateDataSource(objType, CRect(CPoint(0,0), CSize(m_sliderVal, m_sliderVal )));
    CMyOverrideDropTarget myDT;
    CDropSource myDS;
    
    // Start overriding AutoCAD's Droptarget
    if (!acedStartOverrideDropTarget(&myDT))
        TRACE("Error in overriding Custom drop target!\n");
    
   
    DROPEFFECT dwEffect = pSource->DoDragDrop( DROPEFFECT_NONE |DROPEFFECT_MOVE | DROPEFFECT_COPY, NULL, &myDS);

    // End overriding AutoCAD default droptarget
    if (!acedEndOverrideDropTarget(&myDT))
        TRACE("Error in ending override drop target\n");

    delete pSource;
}

void CArxdrawView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CView::OnLButtonUp(nFlags, point);
}

COleDataSource* CArxdrawView::generateDataSource(int objType, const CRect& rect)
{
    COleDataSource* pSource = new COleDataSource();
    char buf[50];

    sprintf(buf,"%d %d %d %d %d", objType,
                               rect.left,
                               rect.top,
                               rect.right,
                               rect.bottom);

    HGLOBAL temp = GlobalAlloc(GHND, strlen(buf)+1);
    char *data = (char*) GlobalLock(temp);
    strcpy(data, buf);
    GlobalUnlock(temp);
    pSource->CacheGlobalData(CF_TEXT, temp);
    
    return pSource;                               
}

void CArxdrawView::MoveTracker(CPoint point)
{
    CClientDC dc(this);
    OnPrepareDC(&dc);

    CPoint pt = point;
    
    if (pt.x == m_lastPoint.x && pt.y == m_lastPoint.y)
        return;
    int newleft = pt.x - 50 ;
    int newtop = pt.y + 50 ;
    int newright = pt.x + 50;
    int newbottom = pt.y - 50 ;

    CRect rect;
    rect.SetRect(newleft, newtop, newright, newbottom) ;

    dc.DrawFocusRect(m_tracker);
    dc.DrawFocusRect(rect);

    m_tracker = rect;
    m_lastPoint = pt;
}

void CArxdrawView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CView::OnMouseMove(nFlags, point);
}


////////////////////////////////////////////////////////////////////////////

void CArxdrawView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

    if (FAILED(OleInitialize(NULL)))
        TRACE("OUCH!! Can't initialize ole\n");

	// TODO: Add your specialized code here and/or call the base class
    m_DummyDropTarget.Register(this);
	
}

void CArxdrawView::OnDestroy() 
{
	CView::OnDestroy();
    m_DummyDropTarget.Revoke();
    OleUninitialize();
}

void CArxdrawView::PostNcDestroy() 
{
	CView::PostNcDestroy();
}
