//////////////////////////////////////////////////////////////////////////////
//
//             (C) Copyright 1994-2008 by Autodesk, Inc.
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
//////////////////////////////////////////////////////////////////////////////

#ifndef _aduiEdit_h
#define _aduiEdit_h
#pragma pack (push, 8)

#pragma once

////////////////////////////////////////////////////////////////////////////
// CAdUiEdit window
#pragma warning(push)
#pragma warning(disable : 4275)
class ADUI_PORT CAdUiEdit : public CEdit {
    DECLARE_DYNAMIC(CAdUiEdit)

public:
                CAdUiEdit ();
virtual         ~CAdUiEdit ();

// Misc.
protected:
        CPoint  m_lastMousePoint;
        CRect   m_tipRect;

public:
virtual void    GetContentExtent (LPCTSTR text, int& width, int& height);
        void    GetTextExtent (LPCTSTR text, int& width, int& height);

// Validation style
public:
        DWORD   m_styleMask;            // style bits (application-defined)

virtual void    SetStyleMask (DWORD);   // define behavior
        DWORD   GetStyleMask ();        // fetch the style
        BOOL    IsStyleMaskSet (DWORD); // verify styles

// AdUi message handlers
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

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiEdit)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiEdit)
    afx_msg LRESULT OnAdUiMessage (WPARAM wParam, LPARAM lParam);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

class    CAdUiSearchBoxEditor;
class    CAdUiSearchBoxSearchButton;
class    CAdUiSearchBoxClearButton;

////////////////////////////////////////////////////////////////////////////
// CAdUiSearchBox window
class ADUI_PORT CAdUiSearchBox : public CAdUiEdit{
    DECLARE_DYNAMIC(CAdUiSearchBox)

public:
                CAdUiSearchBox ();
virtual         ~CAdUiSearchBox ();
virtual BOOL    Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
virtual void    PreSubclassWindow();
        void    SetDefaultText(LPCTSTR pszText);
        void    SetNotification(LPCTSTR pszText);
        void    ClearEditor();
        bool    IsEditEmpty();

public: //Override methods
virtual void    EditChanged();
virtual void    ClearButtonClicked();
virtual void    SearchButtonClicked();

protected:
virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    //{{AFX_MSG(CAdUiComboBox)
    virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
    afx_msg void OnClearButton();
    afx_msg void OnSearchButton();
    afx_msg void SetEditFocus();
    afx_msg void KillEditFocus();
    afx_msg void OnEditChange();
	afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    BOOL    CreateControls();
    BOOL    DestroyControls();
    void    UpdateSearchBox();
    void    UpdateButton();
    void    GetControlRect(CRect &editRect, CRect &buttonRect);

private:
    bool                    m_bIsControlsCreated;
    CAdUiSearchBoxEditor*    m_pEditor;
    CAdUiSearchBoxSearchButton*      m_pBtnSearch;
    CAdUiSearchBoxClearButton*   m_pBtnClear;

    CString                 m_strNotification;
    CString                 m_strDefaultText;
};
#pragma warning(pop)
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

/////////////////////////////////////////////////////////////////////////////
