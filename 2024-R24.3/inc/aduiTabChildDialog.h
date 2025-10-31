//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//      arxsdk/aduiTabChildDialog.h
//

#pragma once
#include "aduiDialog.h"

#pragma pack (push, 8)

#ifndef _ADESK_MAC_
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
        void    OnInitDialogBegin () override;
        void    OnInitDialogFinish () override;

// ClassWizard-controlled
public:
    //{{AFX_DATA(CAdUiTabChildDialog)
    enum { IDD = 0 };
    //}}AFX_DATA

    //{{AFX_VIRTUAL(CAdUiTabChildDialog)
public:
    BOOL PreTranslateMessage(MSG* pMsg) override;
    virtual void OnMainDialogCancel();
    virtual void OnMainDialogOK();
    virtual BOOL OnMainDialogHelp();     
    virtual void OnMainDialogApply();
protected:
    void DoDataExchange(CDataExchange* pDX) override;   // DDX/DDV support
    void OnCancel() override;
    void OnOK() override;
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiTabChildDialog)
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    afx_msg LRESULT OnResizePage(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()
};

#endif //_ADESK_MAC_
//////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)

//////////////////////////////////////////////////////////////////////////////
