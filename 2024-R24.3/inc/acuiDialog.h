//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//      arxsdk/acuiDialog.h
//

#pragma once
#include "acui_port.h"
#include "aduiFileDialog.h"
#include "aduiTabChildDialog.h"
#include "aduiTabMainDialog.h"

#pragma pack (push, 8)
/////////////////////////////////////////////////////////////////////////////
// Basic Dialog

class ACUI_PORT CAcUiDialog : public CAdUiDialog {
    DECLARE_DYNAMIC(CAcUiDialog);

public:
                CAcUiDialog (
                    UINT idd,
                    CWnd *pParent=NULL,
                    HINSTANCE hDialogResource=NULL
                );
                ~CAcUiDialog ();

// Context help
protected:
        BOOL    FindContextHelpFullPath (LPCTSTR fileName, CString& fullPath) override;

// Misc.
public:
        CWnd    *AppMainWindow () override;
        HINSTANCE AppResourceInstance () override;
        LPCTSTR AppRootKey () override;
        void    EnableFloatingWindows (BOOL allow) override;
        int IsMultiDocumentActivationEnabled() override;
        int EnableMultiDocumentActivation(BOOL bEnable) override;

        void    OnDialogHelp() override;

        BOOL    OnInitDialog() override;

// ClassWizard-controlled
public:
    //{{AFX_DATA(CAcUiDialog)
    enum { IDD = 0 };
    //}}AFX_DATA

    //{{AFX_VIRTUAL(CAcUiDialog)
    protected:
    void OnOK() override;
    void OnCancel() override;
    void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiDialog)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// Common File Dialog

class ACUI_PORT CAcUiFileDialog : public CAdUiFileDialog {
    DECLARE_DYNAMIC(CAcUiFileDialog);

public:
                CAcUiFileDialog (
                    BOOL bOpenFileDialog,
                    LPCTSTR lpszDefExt=NULL,
                    LPCTSTR lpszFileName=NULL,
                    DWORD dwFlags=OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                    LPCTSTR lpszFilter=NULL,
                    CWnd *pParentWnd=NULL
                );
                ~CAcUiFileDialog ();

// Misc.
public:
        CWnd    *AppMainWindow () override;
        HINSTANCE AppResourceInstance () override;
        LPCTSTR AppRootKey () override;
        void    EnableFloatingWindows (BOOL allow) override;
        void    OnDialogHelp() override; 
// ClassWizard-controlled
public:
    //{{AFX_DATA(CAcUiFileDialog)
    enum { IDD = 0 };
    //}}AFX_DATA

    //{{AFX_VIRTUAL(CAcUiFileDialog)
    protected:
    void OnOK() override;
    void OnCancel() override;
    void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiFileDialog)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Child Tab Dialog

class ACUI_PORT CAcUiTabChildDialog : public CAdUiTabChildDialog {
    DECLARE_DYNAMIC(CAcUiTabChildDialog);

public:
                CAcUiTabChildDialog (
                    CWnd *pParent=NULL,
                    HINSTANCE hDialogResource=NULL
                );
                ~CAcUiTabChildDialog ();

// Misc.
public:
        CWnd    *AppMainWindow () override;
        HINSTANCE AppResourceInstance () override;
        LPCTSTR AppRootKey () override;
        void    EnableFloatingWindows (BOOL allow) override;
        BOOL OnMainDialogHelp() override;
        void    OnDialogHelp() override;

// ClassWizard-controlled
public:
    //{{AFX_DATA(CAcUiTabChildDialog)
    enum { IDD = 0 };
    //}}AFX_DATA

    //{{AFX_VIRTUAL(CAcUiTabChildDialog)
    protected:
    void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiTabChildDialog)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Main Tab Dialog

class ACUI_PORT CAcUiTabMainDialog : public CAdUiTabMainDialog {
    DECLARE_DYNAMIC(CAcUiTabMainDialog);

public:
                  CAcUiTabMainDialog (
                    UINT idd,
                    CWnd *pParent=NULL,
                    HINSTANCE hDialogResource=NULL
                );
                ~CAcUiTabMainDialog ();

// Misc.
public:
        CWnd    *AppMainWindow () override;
        HINSTANCE AppResourceInstance () override;
        LPCTSTR AppRootKey () override;
        void    EnableFloatingWindows (BOOL allow) override;
        void    OnDialogHelp() override;
        int IsMultiDocumentActivationEnabled() override;
        int EnableMultiDocumentActivation(BOOL bEnable) override;


// Tab Extensions
public:
        BOOL    AddApplicationTabs (LPCTSTR pszAppName) override;

// ClassWizard-controlled
public:
    //{{AFX_DATA(CAcUiTabMainDialog)
    enum { IDD = 0 };
    //}}AFX_DATA

    //{{AFX_VIRTUAL(CAcUiTabMainDialog)
    protected:
    void OnOK() override;
    void OnCancel() override;
    void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiTabMainDialog)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)

/////////////////////////////////////////////////////////////////////////////
