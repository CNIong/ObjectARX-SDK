//////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1994-1999 by Autodesk, Inc.
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
// DESCRIPTION:
//
//   Declarations for various button classes:
//
// CAdUiOwnerDrawButton
//     - A basic owner-draw button.
//   CAdUiBitmapButton
//       - A simple bitmap button.
//     CAdUiBitmapStatic
//         - A bitmap button that defaults to behaving like a static.
//       CAdUiDropSite
//           - A static bitmap that enables Drag&Drop by default.
//     CAdUiToolButton
//         - A bitmap button that enables tool button display by default.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _aduiButton_h
#define _aduiButton_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CAdUiOwnerDrawButton

class ADUI_PORT CAdUiOwnerDrawButton : public CButton {
	DECLARE_DYNAMIC(CAdUiOwnerDrawButton)

public:
                CAdUiOwnerDrawButton ();
virtual         ~CAdUiOwnerDrawButton ();

protected:
        CPoint  m_lastMousePoint;
        CRect   m_tipRect;

// AdUi message handler
protected:
        CWnd    *m_aduiParent;

virtual ADUI_REPLY DoAdUiMessage (
                    ADUI_NOTIFY notifyCode, UINT controlId, LPARAM lParam
                );
virtual void    OnDrawTip (CDC& dc);
virtual BOOL    OnDrawTipText (CAdUiDrawTipText& dtt);
virtual ADUI_REPLY OnGetTipSupport (CPoint& p);
virtual BOOL    OnGetTipRect (CRect& r);
virtual BOOL    OnGetTipText (CString& text);
virtual BOOL    OnHitTipRect (CPoint& p);
public:
        CWnd    *GetAdUiParent ();
        void    SetAdUiParent (CWnd *w);

// Owner Draw routines
protected:
static const UINT m_timerEvent;
        BOOL    m_bEnableDragDrop   : 1;
        BOOL    m_bEnableFastDraw   : 1;
        BOOL    m_bEnablePointedAt  : 1;
        BOOL    m_bIsPointedAt      : 1;
        BOOL    m_bIsStatic         : 1;
        BOOL    m_bIsToolButton     : 1;
        UINT    m_timerId;

virtual void    DrawButton(
                    CDC& dc, int w, int h,
	                BOOL isDefault,
	                BOOL isDisabled,
                    BOOL isSelected,
	                BOOL isFocused
                );
        void    DrawPushButtonBorder (
                    CDC& dc, CRect& rButton, BOOL isDefault, BOOL isSelected
                );
        void    DrawToolButtonBorder (
                    CDC& dc, CRect& rButton, BOOL isSelected, BOOL isFocused
                );
        void    DrawTransparentBitmap (
                    CDC& dc,
                    CBitmap& bmp,
                    int x, int y, int w, int h,
                    BOOL isDisabled
                );
        BOOL    GetIsPointedAt ();
        void    SetIsPointedAt (BOOL isPointedAt);
virtual BOOL    OnAutoLoad ();
virtual void    OnDragDrop (HDROP hDropInfo);
virtual void    OnPointedAt (BOOL isPointedAt);
virtual BOOL    OnReload (LPCTSTR strResId);
        void    StartTimer (DWORD ms=50);
        void    StopTimer ();
public:
        BOOL    AutoLoad ();
        BOOL    GetEnableDragDrop ();
        void    SetEnableDragDrop (BOOL allow);
        BOOL    GetEnableFastDraw ();
        void    SetEnableFastDraw (BOOL allow);
        BOOL    GetEnablePointedAt ();
        void    SetEnablePointedAt (BOOL allow);
        BOOL    GetIsStatic ();
        void    SetIsStatic (BOOL isStatic);
        BOOL    GetIsToolButton ();
        void    SetIsToolButton (BOOL isToolButton);
        BOOL    Reload (LPCTSTR strResId);

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAdUiOwnerDrawButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAdUiOwnerDrawButton)
    afx_msg LONG OnAdUiMessage (WPARAM wParam, LPARAM lParam);
    afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg UINT OnGetDlgCode();
    afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNcDestroy();
    afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAdUiBitmapButton

class ADUI_PORT CAdUiBitmapButton : public CAdUiOwnerDrawButton {
	DECLARE_DYNAMIC(CAdUiBitmapButton)

public:
                CAdUiBitmapButton ();
virtual         ~CAdUiBitmapButton ();

// Owner Draw routines
protected:
virtual void    DrawButton(
                    CDC& dc, int w, int h,
	                BOOL isDefault,
	                BOOL isDisabled,
                    BOOL isSelected,
	                BOOL isFocused
                );
virtual BOOL    OnAutoLoad ();
virtual BOOL    OnReload (LPCTSTR strResId);

// Bitmap Button routines
protected:
        BOOL    m_bAutoSizeToBitmap;
	    CBitmap m_bmp;
        CString m_bmpResId;
	    int     m_bmpHeight;
	    int     m_bmpWidth;
        int     m_bmpX;
        int     m_bmpY;
        int     m_focusRectOffset;

        void    CalcBitmapSize ();
        BOOL    LoadBitmap (LPCTSTR strResId);
        BOOL    LoadBitmapResource (
                    LPCTSTR strResId, CBitmap& bmp, HINSTANCE hInst
                );
virtual BOOL    OnLoadBitmap (LPCTSTR strResId);
public:
        BOOL    GetAutoSizeToBitmap ();
        void    SetAutoSizeToBitmap (BOOL autoSizeToBitmap);
        void    SizeToBitmap ();
        void    SetBitmapOffsets(int nBorderOffset, int nFocusRectOffset);

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAdUiBitmapButton)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAdUiBitmapButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAdUiBitmapStatic

class ADUI_PORT CAdUiBitmapStatic : public CAdUiBitmapButton {
	DECLARE_DYNAMIC(CAdUiBitmapStatic)

public:
	            CAdUiBitmapStatic ();
virtual         ~CAdUiBitmapStatic ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAdUiBitmapStatic)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAdUiBitmapStatic)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAdUiDropSite

class ADUI_PORT CAdUiDropSite : public CAdUiBitmapStatic {
	DECLARE_DYNAMIC(CAdUiDropSite)

public:
	            CAdUiDropSite ();
virtual         ~CAdUiDropSite ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAdUiDropSite)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAdUiDropSite)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAdUiToolButton

class ADUI_PORT CAdUiToolButton : public CAdUiBitmapButton {
	DECLARE_DYNAMIC(CAdUiToolButton)

public:
	            CAdUiToolButton ();
virtual         ~CAdUiToolButton ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAdUiToolButton)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAdUiToolButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

//////////////////////////////////////////////////////////////////////////////
