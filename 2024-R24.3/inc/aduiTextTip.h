//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//      arxsdk/aduiTextTip.h
//

#pragma once

#include "adui_port.h"

#pragma pack (push, 8)
#ifndef _ADESK_MAC_
/////////////////////////////////////////////////////////////////////////////
// CAdUiTipWindow
#pragma warning(push)
#pragma warning(disable : 4275) // exported class derives from non-exported class
class ADUI_PORT CAdUiTipWindow : public CWnd {
    DECLARE_DYNAMIC(CAdUiTipWindow)

public:
                CAdUiTipWindow ();
                ~CAdUiTipWindow ();

// Tip Window
private:
        void    ForwardClickMessage (UINT msg, UINT nFlags, CPoint& point, BOOL focus);
protected:
static  LPCTSTR m_className;                // Registered class name
static const UINT_PTR m_timerEvent;

        BOOL    m_bUseText;                 // Draw as text vs. owner-draw.
        CWnd    *m_control;                 // Related control
        CWnd    *m_owner;                   // Owner (dialog, etc.)
        UINT_PTR m_timerId;

virtual void    DrawBorder (CDC& dc, CRect& rExterior, CRect& rInterior);
virtual void    DrawContent (CDC& dc, CRect& rInterior);
        void    StartTimer (DWORD ms=50);
        void    StopTimer ();
public:
virtual BOOL    Create (CWnd *owner);
        CWnd    *GetControl ();
        void    GetTextExtent (LPCTSTR text, int& width, int& height);
        BOOL    GetUseText ();
virtual void    Hide ();
        CWnd    *Owner ();
        void    SetControl (CWnd *control);
        void    SetUseText (BOOL useText);
virtual void    Show ();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiTipWindow)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiTipWindow)
    afx_msg void OnActivateApp(BOOL bActive, DWORD hTask);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnNcDestroy();
    afx_msg void OnPaint();
    afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
#pragma warning(pop)
/////////////////////////////////////////////////////////////////////////////
// CAdUiBalloonTip window - INTERNAL USE ONLY

class ADUI_PORT CAdUiBalloonTip : public CAdUiTipWindow {
    DECLARE_DYNAMIC(CAdUiBalloonTip)

public:
                CAdUiBalloonTip ();
                ~CAdUiBalloonTip ();

// Text Tip
protected:
        CPoint  m_initialCursorPos;

        void    DrawBorder (CDC& dc, CRect& rExterior, CRect& rInterior) override;
        void    DrawContent (CDC& dc, CRect& rInterior) override;

public:
        void    Hide () override;
        void    Show () override;

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiBalloonTip)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiBalloonTip)
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAdUiTextTip window

class ADUI_PORT CAdUiTextTip : public CAdUiTipWindow {
    DECLARE_DYNAMIC(CAdUiTextTip)

public:
                CAdUiTextTip ();
                ~CAdUiTextTip ();

// Text Tip
protected:
        void    DrawBorder (CDC& dc, CRect& rExterior, CRect& rInterior) override;
        void    DrawContent (CDC& dc, CRect& rInterior) override;
public:
        void    Hide () override;
        void    Update (CWnd *control, BOOL useText);
        void    UpdateIfNecessary (CWnd *control, BOOL useText);

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiTextTip)
    BOOL PreCreateWindow(CREATESTRUCT& cs) override;
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiTextTip)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAdToolTipCtrl: for INTERNAL USE ONLY.

class AdToolTip;

#pragma warning(push)
#pragma warning(disable : 4275)
class ADUI_PORT CAdToolTipCtrl : public CToolTipCtrl{

    DECLARE_MESSAGE_MAP()
public:
    CAdToolTipCtrl();
    ~CAdToolTipCtrl ();
    
    BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult) override;
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    static void SetToolTipsFlag(BOOL bToolTipsFlag);
    static void SetDeaultDelayTime(int nDelay);

    /// <summary>
    /// Override of the non-virtual base class method. Registers a tool with the
    /// tooltip control.  See MFC help for more documentation.
    /// </summary>
    /// <param name="pWnd">Pointer to the window containing the tool.</param>
    /// <param name="nIDText">ID of string resource containing tool text.</param>
    /// <param name="lpRectTool">Bounding box relative to pWnd's upper left.</param>
    /// <param name="nIDTool">ID of the tool.</param>
    /// <remarks>Just passes through to the base class method, as you can see.</remarks>
    //
    BOOL AddTool(_In_ CWnd* pWnd, _In_ UINT nIDText,
                 _In_opt_ LPCRECT lpRectTool = nullptr, _In_ UINT_PTR nIDTool = 0) {
        return CToolTipCtrl::AddTool(pWnd, nIDText, lpRectTool, nIDTool);
    }

    /// <summary>
    /// Override of the non-virtual base class method. Registers a tool with the
    /// tooltip control.  See MFC help for more documentation.
    /// </summary>
    /// <param name="pWnd">Pointer to the window containing the tool.</param>
    /// <param name="lpszText">Text for the tool.</param>
    /// <param name="lpRectTool">Bounding box relative to pWnd's upper left.</param>
    /// <param name="nIDTool">ID of the tool.</param>
    /// <remarks>Uses a shortened version of lpszText if it exceeds MFC's internal
    ///          tooltip length limit of 1024. Clients should consider shortening
    ///          long strings themselves, to make the tooltip more readable.</remarks>
    //
    BOOL AddTool(_In_ CWnd* pWnd, _In_z_ LPCTSTR lpszText = LPSTR_TEXTCALLBACK,
                 _In_opt_ LPCRECT lpRectTool = nullptr, _In_ UINT_PTR nIDTool = 0);

    /// <summary>
    /// Override of the non-virtual base class method.
    /// Updates the tooltip text for this control's tools.
    /// </summary>
    /// <param name="nIDText">ID of string resource containing tool text.</param>
    /// <param name="pWnd">Pointer to the window containing the tool.</param>
    /// <param name="nIDTool">ID of the tool.</param>
    /// <remarks>Just passes through to the base class method, as you can see.</remarks>
    //
    void UpdateTipText(_In_ UINT nIDText, _In_ CWnd* pWnd, _In_ UINT_PTR nIDTool = 0) {
        return CToolTipCtrl::UpdateTipText(nIDText, pWnd, nIDTool);
    }

    /// <summary>
    /// Override of the non-virtual base class method.
    /// Updates the tooltip text for this control's tools.
    /// </summary>
    /// <param name="lpszText">Text for the tool.</param>
    /// <param name="pWnd">Pointer to the window containing the tool.</param>
    /// <param name="nIDTool">ID of the tool.</param>
    /// <remarks>Uses a shortened version of lpszText if it exceeds MFC's internal
    ///          tooltip length limit of 1024. Clients should consider shortening
    ///          long strings themselves, to make the tooltip more readable.</remarks>
    //
    void UpdateTipText(_In_z_ LPCTSTR lpszText, _In_ CWnd* pWnd, _In_ UINT_PTR nIDTool = 0);

protected:
    virtual AdToolTip * CreateAdToolTipInstance();
    AdToolTip* m_pToolTip { nullptr };
    BOOL m_bActivate { true };
    UINT m_nDelayTime { 0 };

private:
    static BOOL m_bToolTipHasCreated;
    static BOOL m_bToolTipsFlag;
    static UINT m_nDefaultDealyTime;
};
#pragma warning(pop)

/////////////////////////////////////////////////////////////////////////////
// CAdWthToolTipCtrl, used for What's this help: for INTERNAL USE ONLY.

class AdWthToolTip;

class ADUI_PORT CAdWthToolTipCtrl : public CAdToolTipCtrl
{
    DECLARE_MESSAGE_MAP()
public:
    AdWthToolTip* GetWthToolTip();
protected:
    AdToolTip * CreateAdToolTipInstance() override;
};

/////////////////////////////////////////////////////////////////////////////
// These functions are all for INTERNAL USE ONLY.

void ADUI_PORT AdUiHideBalloonTip (CWnd *control);
BOOL ADUI_PORT AdUiShowBalloonTip (
    CWnd *owner, CWnd *control, LPCTSTR text, BOOL beep
);
BOOL ADUI_PORT AdUiShowBalloonTip (
    CWnd *owner, CWnd *control, CRect& rect, LPCTSTR text, BOOL beep
);

#endif // _ADESK_MAC_
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)

//////////////////////////////////////////////////////////////////////////////
