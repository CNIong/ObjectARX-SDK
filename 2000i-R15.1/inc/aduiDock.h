//////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1994-1999 by Autodesk, Inc.
//
// The information contained herein is confidential, proprietary to Autodesk,
// Inc., and considered a trade secret as defined in section 499C of the
// penal code of the State of California.  Use of this information by anyone
// other than authorized employees of Autodesk, Inc. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
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
//////////////////////////////////////////////////////////////////////////////

#ifndef _aduiDock_h
#define _aduiDock_h

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxpriv.h>                    // For CDockBar and CMiniDockFrameWnd
#pragma pack (push, 8)

class CAdUiDockFrame;

//////////////////////////////////////////////////////////////////////////////

#define ADUI_DOCK_POSITION_TOOL_KEY "DockedTools"
#define ADUI_DOCK_STARTUP_TOOL_KEY  "RestartTools"

#define ID_ADUI_ALLOWDOCK           0x1001
#define ID_ADUI_HIDEBAR             0x1002

#define ADUI_DOCK_CS_DESTROY_ON_CLOSE  0x01    // closing the floating window closes the control bar
#define ADUI_DOCK_CS_STDMOUSECLICKS    0x02    // standard mouse handling for the menu

#define ADUI_DOCK_NF_SIZECHANGED       0x01
#define ADUI_DOCK_NF_STATECHANGED      0x02

//////////////////////////////////////////////////////////////////////////////

class ADUI_PORT CAdUiDockControlBar : public CControlBar
{
    friend class CAdUiDockFrame;
    friend class CAdUiDockDragContext;
    friend class CAdUiDockBar;

// Attributes
private:
	static CObArray * m_paBars;				    // array of dynamically allocated bars
	CSize             m_FloatSize;              // size when docked
   	CSize			  m_HorzDockSize;			// size when docked horizontal
	CSize			  m_VertDockSize;			// size when docked vertical
    CPoint			  m_FloatingPosition;		// floating position
	DWORD			  m_dwAllowDockingState;    // saved enable style for allow docking on/off
    int               m_Style;                  // style flags
    CSize             m_PrevSize;
    BOOL              m_bPrevFloating;
	CAdUiBitmapButton m_closeBtn;
    CLSID             m_ID;

    static int        m_nLastBarID;

private:
	void SetDockFlag (DWORD dwStyle);
	void Resized (int cx, int cy, BOOL bFloating, int flags);
	LONG AddMenuItems (UINT wParam, LPARAM lParam);
	static void RemoveBars ();
    CSize CalcFixedLayout (BOOL bStretch, BOOL bHorz);
    void OnUpdateCmdUI (CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	void PaintBar (CDC *pDC);
	void Draw3DRect (CDC *pDC, LPRECT lpRect, CPen *pPenGray);
    LRESULT WindowProc (UINT nMsg, WPARAM wParam, LPARAM lParam);

// Construction
public:
    CAdUiDockControlBar (int nStyle = ADUI_DOCK_CS_STDMOUSECLICKS);

// Operations
	BOOL Create (CWnd * pParent, LPCTSTR lpszTitle, UINT nID,
                 DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,
                 const RECT & rect = CFrameWnd::rectDefault);
	// CWnd-style create
	BOOL Create (LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
	     	     DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
    void EnableDocking (DWORD dwDockStyle);
    void TileInRow ();
	BOOL IsFloating ();
    void DockControlBar (UINT nOrientation, RECT *pRect);
    void RestoreControlBar (UINT nPreferredOrientation = AFX_IDW_DOCKBAR_LEFT,
                            CRect *pSizeFloating = NULL);
    void InitFloatingPosition (CRect *pSizeFloating);
    void GetFloatingRect (CRect *pFloatingPos);
#ifdef _DEBUG
    void AssertValid() const;
#endif
    void SetToolID (CLSID* pCLSID);
    CLSID* GetToolID () { return &m_ID; }
    DWORD GetDockStyle () { return m_dwDockStyle; }

    // Called in response to the application's query to take the focus back.
    // Default implementation returns false, keeping the focus in the tool window.
    virtual bool CanFrameworkTakeFocus () { return false; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdUiDockControlBar)
	protected:
	virtual BOOL OnCommand (WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CAdUiDockControlBar();

    // Generated message map functions

protected:
	enum {
		btnWidth = 12,
		btnHeight = 12,
		idCloseBtn = 10001
	};

protected:
    // windows message handlers
    //{{AFX_MSG(CAdUiDockControlBar)
    afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnAllowDock ();
	afx_msg void OnHideBar ();
    afx_msg void OnContextMenu (CWnd* pWnd, CPoint point);
	afx_msg int OnCreate (LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnPaint ();
	//afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG


protected:
    void GetUsedRect (CRect& rect);

    // Overridable functions
    virtual void PaintControlBar (CDC *pDC);
    virtual BOOL CreateControlBar (LPCREATESTRUCT lpCreateStruct);
    virtual void SizeChanged (CRect *lpRect, BOOL bFloating, int flags) {}
    virtual bool OnClosing ();
    virtual void GetFloatingMinSize (long *pnMinWidth, long *pnMinHeight);
    virtual BOOL AddCustomMenuItems(LPARAM hMenu); 
    virtual void OnUserSizing (UINT nSide, LPRECT pRect) { }
	
    DECLARE_DYNAMIC (CAdUiDockControlBar)
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAdUiDockFrame window

class ADUI_PORT CAdUiDockFrame : public CMiniDockFrameWnd   // INTERNAL USE ONLY 
{
    DECLARE_DYNCREATE (CAdUiDockFrame)

public:
                CAdUiDockFrame ();

// Docking frame
public:
        enum ContainedBarType { Unknown, Standard, AdskBar } ;

        enum ContainedBarType GetContainedBarType ();
protected:
        enum ContainedBarType m_nContainedBarType;	
        bool m_bZOrderChanged;

        bool CanFrameworkTakeFocus ();
        void ForceChildRepaint ();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiDockFrame)
    protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    //}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAdUiDockFrame)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnClose();
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint pt);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnWindowPosChanging (WINDOWPOS* lpwndpos);
	afx_msg void OnPaint ();
    afx_msg void OnGetMinMaxInfo (MINMAXINFO FAR* lpMMI);
    afx_msg void OnSizing (UINT nSide, LPRECT pRect);
    //}}AFX_MSG

	bool CanAutoCADTakeFocus ();

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

void ADUI_PORT AdUiSaveDockingToolPositions ();                         // INTERNAL USE ONLY 
bool ADUI_PORT AdUiRegisterDockingTool (                                // INTERNAL USE ONLY 
    LPCSTR lpszToolName, LPCSTR lpszCommand, UINT nToolbarID
);
bool ADUI_PORT AdUiRegisterTool (
    LPCSTR lpszToolName, LPCSTR lpszCommand, CLSID* pID
);

void ADUI_PORT AdUiEnableDocking (                                      // INTERNAL USE ONLY 
    CFrameWnd *pFrame, DWORD dwDockStyle, LPCSTR lpszRegKey
);
bool ADUI_PORT CanStealFocusFromDockedWindow ();                        // INTERNAL USE ONLY 

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif
