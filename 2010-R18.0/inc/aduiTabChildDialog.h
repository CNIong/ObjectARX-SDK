//////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1994-2006 by Autodesk, Inc.
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

#ifndef _aduiTabChildDialog_h
#define _aduiTabChildDialog_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////////////

class ADUI_PORT CAdUiTabChildDialog : public CAdUiDialog {
friend class CAdUiTab;

    DECLARE_DYNAMIC(CAdUiTabChildDialog);

public:
                CAdUiTabChildDialog (
                    CWnd *pParent=NULL,
                    HINSTANCE hDialogResource=NULL
                );

// Tab Child Dialog
private:
        BOOL    m_bDirty;
        HWND    m_hWndFocus;
        CAdUiTab *m_pAcadTab;

        void    SetAcadTabPointer (CAdUiTab *pAcadTab);
        BOOL    TranslateTabKey ();
public:
        CAdUiTab *GetAcadTabPointer ();
        CAdUiTabMainDialog *GetMainDialog ();
        int     GetTabIndex ();
        BOOL    IsDirty ();
virtual void    OnTabActivation (BOOL bActivate);
virtual BOOL    OnTabChanging ();
        void    SetAcadTabChildFocus (HWND hWndFocus);

        // Call this if you've changed your contents and might need saving...
        void    SetDirty (BOOL bDirty=TRUE);

        void    SetValidationInfo (CDataExchange *pDX);

// Elasticity
protected:
virtual void    OnInitDialogBegin ();
virtual void    OnInitDialogFinish ();

// ClassWizard-controlled
public:
    //{{AFX_DATA(CAdUiTabChildDialog)
    enum { IDD = 0 };
    //}}AFX_DATA

    //{{AFX_VIRTUAL(CAdUiTabChildDialog)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual void OnMainDialogCancel();
    virtual void OnMainDialogOK();
    virtual BOOL OnMainDialogHelp();     
    virtual void OnMainDialogApply();
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiTabChildDialog)
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    afx_msg LRESULT OnResizePage(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

//////////////////////////////////////////////////////////////////////////////
