//////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1994-2008 by Autodesk, Inc.
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

#include "AdUiTheme.h"  // INTERNAL USE ONLY

class CAdUiOwnerDrawButton;
class CAdUiTrackButtonDraw;

class CAdUiODButtonThemeModReactor : public CAdUiThemeModifiedReactor  // INTERNAL USE ONLY
{
public:
    CAdUiODButtonThemeModReactor(CAdUiOwnerDrawButton* pBtn);  // INTERNAL USE ONLY
    virtual void ThemeModified(const CAdUiTheme * pTheme, AdUiThemeElement element);  // INTERNAL USE ONLY

private:
    CAdUiOwnerDrawButton * m_pBtn;
};


/////////////////////////////////////////////////////////////////////////////
// CAdUiOwnerDrawButton
#pragma warning(push)
#pragma warning(disable : 4275)
class ADUI_PORT CAdUiOwnerDrawButton : public CButton {
    friend class CAdUiODButtonThemeModReactor;  // INTERNAL USE ONLY

    DECLARE_DYNAMIC(CAdUiOwnerDrawButton)

public:
                CAdUiOwnerDrawButton ();
virtual         ~CAdUiOwnerDrawButton ();

protected:
        CPoint  m_lastMousePoint;
        CRect   m_tipRect;
        CAdUiTheme * m_pTheme;  // INTERNAL USE ONLY

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

virtual void    SetTracking(BOOL b) { m_bIsTrackButton = b; };
virtual CAdUiTheme * SetTheme(CAdUiTheme *pTheme);  // INTERNAL USE ONLY

// Owner Draw routines
protected:
static const UINT_PTR m_timerEvent;
        BOOL    m_bEnableDragDrop   : 1;
        BOOL    m_bEnableFastDraw   : 1;
        BOOL    m_bEnablePointedAt  : 1;
        BOOL    m_bIsPointedAt      : 1;
        BOOL    m_bIsStatic         : 1;
        BOOL    m_bIsToolButton     : 1;
        BOOL    m_bIsTrackButton    : 1;
        UINT_PTR  m_timerId;

        // members added for XP look and feel
        int     m_nPartId;
        int     m_nStateId;
        UINT    m_uEdge;
        BOOL    m_bMouseHover;

virtual void    DrawBorder(CDC *pDC,CRect &r,COLORREF cr);
virtual void    DrawHotBorder();
virtual void    DrawButton(
                    CDC& dc, int w, int h,
                    BOOL isDefault,
                    BOOL isDisabled,
                    BOOL isSelected,
                    BOOL isFocused
                );
virtual void    DrawPushButtonBorder (
                    CDC& dc, CRect& rButton, BOOL isDefault, BOOL isSelected
                );
virtual void    DrawToolButtonBorder (
                    CDC& dc, CRect& rButton, BOOL isSelected, BOOL isFocused
                );
        void    DrawTransparentBitmap (
                    CDC& dc,
                    CBitmap& bmp,
                    int x, int y, int w, int h,
                    BOOL isDisabled
                );
        void    DrawContentText (
                    CDC& dc,
                    CString sText,
                    CRect& rcText,
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

        
virtual void ThemeModified(AdUiThemeElement element);  // INTERNAL USE ONLY
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
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiOwnerDrawButton)
    afx_msg LRESULT OnAdUiMessage (WPARAM wParam, LPARAM lParam);
    afx_msg void OnDropFiles(HDROP hDropInfo);
    afx_msg UINT OnGetDlgCode();
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg LRESULT OnMouseLeave(WPARAM, LPARAM);
    afx_msg void OnNcDestroy();
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnDestroy( );
    afx_msg LRESULT OnThemeChanged(WPARAM wParam, LPARAM lParam);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
protected:
	HANDLE GetVisualStylesTheme() {return m_hVS;}
private:
    CAdUiODButtonThemeModReactor* m_pThemeModReactor;  // INTERNAL USE ONLY
	HANDLE    m_hVS;               // INTERNAL USE ONLY
};
#pragma warning(pop)
/////////////////////////////////////////////////////////////////////////////
// CAdUiBitmapButton

class ADUI_PORT CAdUiBitmapButton : public CAdUiOwnerDrawButton {
    DECLARE_DYNAMIC(CAdUiBitmapButton)

    friend class CAdUiImpBitmapButton;
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
// CAdUiTrackButton

class ADUI_PORT CAdUiTrackButton : public CAdUiOwnerDrawButton {
    DECLARE_DYNAMIC(CAdUiTrackButton)

public:
                CAdUiTrackButton();
                CAdUiTrackButton(const CAdUiTrackButtonDraw & pDraw);
virtual         ~CAdUiTrackButton();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiTrackButton)
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    //}}AFX_VIRTUAL

virtual CAdUiTheme * GetTheme() const;
virtual CAdUiTheme * SetTheme(CAdUiTheme *pTheme);  // INTERNAL USE ONLY

static  CAdUiTrackButtonDraw * SetDefaultDraw(CAdUiTrackButtonDraw * pDraw);
        CAdUiTrackButtonDraw * SetDraw(CAdUiTrackButtonDraw * pDraw);

virtual void    SetTracking(BOOL b);

protected:
virtual void    DrawButton(
                    CDC& dc, int w, int h,
                    BOOL isDefault,
                    BOOL isDisabled,
                    BOOL isSelected,
                    BOOL isFocused
                );
virtual void    DrawBorder(CDC *pDC,CRect &r,COLORREF cr);
virtual void    DrawHotBorder();
virtual void    DrawPushButtonBorder (CDC& dc, CRect& rButton, BOOL isDefault, BOOL isSelected);
virtual void    DrawToolButtonBorder (CDC& dc, CRect& rButton, BOOL isSelected, BOOL isFocused);

virtual ADUI_REPLY OnGetTipSupport (CPoint& p);

    //{{AFX_MSG(CAdUiTrackButton)
    afx_msg void OnNcPaint();
    afx_msg void OnPaint();
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

    virtual void releaseDraw();

// Implementation
private:
    static CAdUiTrackButtonDraw * s_pDefaultDraw;
    CAdUiTrackButtonDraw * m_pDraw;

};

class ADUI_PORT CAdUiBitmapTextButton : public CAdUiBitmapButton // Internal Use!
{
    friend class CAdUiImpBitmapButton;
    DECLARE_DYNAMIC(CAdUiBitmapTextButton)
public:
    enum ButtonType
    {
        kBitmap = 0x1,
        kText = 0x2,
    };

    enum BitmapLocation
    {
        kLeft = 0x1,
        kTop = 0x2,
        kRight = 0x4,
        kBottom = 0x8,
    };

	enum ButtonStyle
	{
		kButtonStyleNone  = 0,
		kButtonStyleFlat  = 0x1,
		kButtonStyleCheck = 0x2,

		kButtonHCenter     = 0x00000300,
		kButtonVCenter    = 0x00000C00,
	};
 
public:
    CAdUiBitmapTextButton();
    virtual ~CAdUiBitmapTextButton();

    // Owner Draw routines
protected:
    virtual void DrawButton(
        CDC& dc, int w, int h,
        BOOL isDefault,
        BOOL isDisabled,
        BOOL isSelected,
        BOOL isFocused
        );
    virtual BOOL OnAutoLoad ();
    virtual BOOL OnReload (LPCTSTR strResId);
    virtual BOOL OnLoadBitmap (LPCTSTR strResId);

public:
    BOOL                GetAutoSizeToContent ();
    void                SetAutoSizeToContent (BOOL autoSizeToContent);
    void                SizeToContent ();
    void                SetContentOffsets(int nBorderOffset, 
                                                    int nFocusRectOffset);
    UINT                GetButtonType();
    UINT                GetBitmapLocation();
    UINT                SetButtonType(UINT btnType);
    UINT                SetBitmapLocation(UINT imgPos);
	
	ButtonStyle			GetBitmapTextButtonStyle() const;
	void				SetBitmapTextButtonStyle(ButtonStyle nBtnStyle);

    DECLARE_MESSAGE_MAP()
public:
    BOOL				GetAutoSizeToBitmap ();
    void				SetAutoSizeToBitmap (BOOL autoSizeToBitmap);
    void				SizeToBitmap ();
    void				SetBitmapOffsets(int nBorderOffset, int nFocusRectOffset);
	
	void				SetBkColor(COLORREF);
	void				SetBorderColor(COLORREF);

	void				SetCheck(int nCheck);
	int					GetCheck();

	HICON				SetIcon(HICON hIcon, BOOL bRedraw = TRUE);
	HICON				GetIcon() const;
	HBITMAP				SetBitmap(HBITMAP hBitmap, BOOL bRedraw = TRUE);
	HBITMAP				GetBitmap() const;
private:
    void*               mpImpObj;
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

//////////////////////////////////////////////////////////////////////////////
