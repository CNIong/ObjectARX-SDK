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
// arxdrawView.h : interface of the CArxdrawView class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef _ARXDRAWVIEW_H___
#define _ARXDRAWVIEW_H___


class CDropSource;
class CDropTarget;
class CArxdrawDoc;
class CDummyDropTarget;

class CArxdrawView : public CView
{
public:
    	CArxdrawView();

protected: // create from serialization only
	DECLARE_DYNCREATE(CArxdrawView)

    void MoveTracker(CPoint point);
    COleDataSource* generateDataSource(int, const CRect&);

// Attributes
public:
    CDummyDropTarget m_DummyDropTarget;
    CPoint m_lastPoint;
    CRect m_tracker;
    
    int m_sliderVal;

// Operations
public:

//	void Remove(CDrawObj* pObj);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArxdrawView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CArxdrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CArxdrawView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////////////////
#endif // _ARXDRAWVIEW_H___