//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//      arxsdk/aduiBaseDialog.h
//

#pragma once

#include "adui_port.h"
#pragma pack (push, 8)

#ifndef kDialogOptionNone
#define kDialogOptionNone       0
#endif

#ifndef kDialogOptionUseTips
#define kDialogOptionUseTips       1
#endif

#ifndef kDialogOptionUseTipsForContextHelp
#define kDialogOptionUseTipsForContextHelp       2
#endif

#ifndef _ADESK_MAC_
#pragma warning(push)
#pragma warning(disable : 4275)     // exported class derives from non-exported class

class CAdUiTextTip;

class ADUI_PORT CAdUiBaseDialog : public CDialog {
    DECLARE_DYNAMIC(CAdUiBaseDialog);

public:
                CAdUiBaseDialog (
                    UINT idd,
                    CWnd *pParent=NULL,
                    HINSTANCE hDialogResource=NULL
                );
                ~CAdUiBaseDialog ();

// AdUi message handlers
protected:
virtual ADUI_REPLY DoAdUiMessage (
                    ADUI_NOTIFY notifyCode, UINT controlId, LPARAM lParam
                );
virtual ADUI_REPLY OnNotifyControlChange (UINT controlId, LPARAM lParam);
virtual ADUI_REPLY OnNotifyControlValid (UINT controlId, BOOL isValid);
virtual ADUI_REPLY OnNotifyGeneric (UINT controlId, LPARAM lParam);
virtual ADUI_REPLY OnNotifyUpdateTip (CWnd *control);

// Drawing Editor Interaction
private:
        HINSTANCE m_commandResourceInstance;
        BOOL    m_commandWindowWasEnabled;
        HWND    m_commandWindowWithFocus;

protected:
        ADUI_COMMAND_STATE m_commandState;

        void    BeginEditorCommand ();
        void    CancelEditorCommand ();
        void    CompleteEditorCommand (BOOL restoreDialogs=TRUE);
        void    MakeDialogsVisible (BOOL visible);
public:
        BOOL    EditorCommandCancelled ();

// Context help
protected:
        CString m_contextHelpFileName;
        CString m_contextHelpFullPathName;
        CString m_contextHelpPrefix;    // Must be 4 ASCII characters.
        CString m_contextHelpMapFileName;

virtual BOOL    FindContextHelpFullPath (LPCTSTR fileName, CString& fullPath);
public:
        LPCTSTR GetContextHelpFileName ();    
        void    SetContextHelpFileName (LPCTSTR pFileName);
        LPCTSTR GetContextHelpFullPathName ();    
        void    SetContextHelpFullPathName (LPCTSTR pFullPathName);
        LPCTSTR GetContextHelpPrefix ();   
        void    SetContextHelpPrefix (LPCTSTR pPrefix);
        LPCTSTR GetContextHelpMapFileName ();    
        void    SetContextHelpMapFileName (LPCTSTR pFileName);
        
        CToolTipCtrl* GetToolTipCtrl();        
// Misc.
private:
        BOOL    m_bRunningModal;
        HINSTANCE m_hDialogResourceSaved;

        // Substitute font used when charset isn't supported in the default font
        CFont   m_substFont;

protected:
        int    m_bUseTips;
        HINSTANCE m_hDialogResource;
        HICON   m_hIcon;
        CAdUiTextTip *m_pTextTip;
        CToolTipCtrl *m_pToolTip;
        CString m_rootKey;

        friend class CAdUiAssist;
        static CAdUiAssist* m_pUIAssist;

protected:
virtual void    OnInitDialogBegin ();
virtual void    OnInitDialogFinish ();
public:
virtual CWnd    *AppMainWindow ();
virtual HINSTANCE AppResourceInstance ();
virtual LPCTSTR AppRootKey ();
        void    SetAppRootKey (LPCTSTR key);

        // Modeless dialogs should be created using one of the following
        // Create() methods (as per the MFC documentation). These are
        // provided to handle resource switching (like the new DoModal()).
        // ** Note: These methods are NOT declared virtual, yet duplicate
        //          the signature of the inherited methods.
        BOOL Create (LPCTSTR lpszTemplateName, CWnd* pParentWnd=NULL);
        BOOL Create (UINT nIDTemplate, CWnd* pParentWnd=NULL);

virtual void    EnableFloatingWindows (BOOL allow);     // INTERNAL USE ONLY
virtual int IsMultiDocumentActivationEnabled();         // INTERNAL USE ONLY
virtual int EnableMultiDocumentActivation(BOOL bEnable);// INTERNAL USE ONLY
virtual BOOL DoDialogHelp();                            // INTERNAL USE ONLY


        int    GetUseTips ();
        void    SetUseTips (int useTips);

        HICON   GetDialogIcon();
        void    SetDialogIcon(HICON hIcon);        

// Data Exchange methods
public:
        BOOL    DisplayData ();
virtual BOOL    ExchangeData (BOOL bSaveAndValidate);
        BOOL    ValidateData ();

// ClassWizard-controlled
public:
    //{{AFX_DATA(CAdUiBaseDialog)
    enum { IDD = 0 };
    //}}AFX_DATA

    //{{AFX_VIRTUAL(CAdUiBaseDialog)
public:
    BOOL PreTranslateMessage(MSG* pMsg) override;       // INTERNAL USE ONLY
    INT_PTR DoModal() override;                         // INTERNAL USE ONLY
protected:
    void DoDataExchange(CDataExchange* pDX) override;   // DDX/DDV support
    void PostNcDestroy() override;                      // INTERNAL USE ONLY
    BOOL PreCreateWindow(CREATESTRUCT& cs) override;    // INTERNAL USE ONLY
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiBaseDialog)
    BOOL OnInitDialog() override;
    afx_msg LRESULT OnAdUiMessage (WPARAM wParam, LPARAM lParam);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);// INTERNAL USE ONLY
    afx_msg BOOL OnHelpInfo(HELPINFO* lpHelpInfo);
    afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
    afx_msg void OnAdUiTimer(UINT_PTR nIDEvent);
    //}}AFX_MSG
    afx_msg BOOL OnNotify_ToolTipText(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
    DECLARE_MESSAGE_MAP()
};
#pragma warning(pop)

#endif // _ADESK_MAC_
#pragma pack (pop)
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.
/////////////////////////////////////////////////////////////////////////////
