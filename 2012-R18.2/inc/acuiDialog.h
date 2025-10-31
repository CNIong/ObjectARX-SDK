//////////////////////////////////////////////////////////////////////////////
//
//                 (C) Copyright 1988-2008 by Autodesk, Inc.
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

#ifndef _acuiDialog_h
#define _acuiDialog_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

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
virtual         ~CAcUiDialog ();

// Context help
protected:
virtual BOOL    FindContextHelpFullPath (LPCTSTR fileName, CString& fullPath);

// Misc.
public:
virtual CWnd    *AppMainWindow ();
virtual HINSTANCE AppResourceInstance ();
virtual LPCTSTR AppRootKey ();
virtual void    EnableFloatingWindows (BOOL allow);
virtual int IsMultiDocumentActivationEnabled();
virtual int EnableMultiDocumentActivation(BOOL bEnable);

virtual void    OnDialogHelp();

virtual BOOL    OnInitDialog();

// ClassWizard-controlled
public:
    //{{AFX_DATA(CAcUiDialog)
    enum { IDD = 0 };
    //}}AFX_DATA

    //{{AFX_VIRTUAL(CAcUiDialog)
	protected:
    virtual void OnOK();
	virtual void OnCancel();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiDialog)
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Dialog Bar
// Note: This class is now obsolete and is slated for removal.

class ACUI_PORT CAcUiDialogBar : public CAdUiDialogBar {
    DECLARE_DYNAMIC(CAcUiDialogBar);

public:
                CAcUiDialogBar ();
virtual         ~CAcUiDialogBar ();

// Misc.
public:
virtual CWnd    *AppMainWindow ();
virtual HINSTANCE AppResourceInstance ();
virtual LPCTSTR AppRootKey ();

// ClassWizard-controlled
public:
    //{{AFX_DATA(CAcUiDialogBar)
    enum { IDD = 0 };
    //}}AFX_DATA

    //{{AFX_VIRTUAL(CAcUiDialogBar)
	protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiDialogBar)
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
virtual         ~CAcUiFileDialog ();

// Misc.
public:
virtual CWnd    *AppMainWindow ();
virtual HINSTANCE AppResourceInstance ();
virtual LPCTSTR AppRootKey ();
virtual void    EnableFloatingWindows (BOOL allow);
virtual void    OnDialogHelp(); 
// ClassWizard-controlled
public:
    //{{AFX_DATA(CAcUiFileDialog)
    enum { IDD = 0 };
    //}}AFX_DATA

    //{{AFX_VIRTUAL(CAcUiFileDialog)
	protected:
    virtual void OnOK();
	virtual void OnCancel();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
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
virtual         ~CAcUiTabChildDialog ();

// Misc.
public:
virtual CWnd    *AppMainWindow ();
virtual HINSTANCE AppResourceInstance ();
virtual LPCTSTR AppRootKey ();
virtual void    EnableFloatingWindows (BOOL allow);
virtual BOOL OnMainDialogHelp();
virtual void    OnDialogHelp();

// ClassWizard-controlled
public:
    //{{AFX_DATA(CAcUiTabChildDialog)
    enum { IDD = 0 };
    //}}AFX_DATA

    //{{AFX_VIRTUAL(CAcUiTabChildDialog)
	protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
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
virtual         ~CAcUiTabMainDialog ();

// Misc.
public:
virtual CWnd    *AppMainWindow ();
virtual HINSTANCE AppResourceInstance ();
virtual LPCTSTR AppRootKey ();
virtual void    EnableFloatingWindows (BOOL allow);
virtual void    OnDialogHelp();
virtual int IsMultiDocumentActivationEnabled();
virtual int EnableMultiDocumentActivation(BOOL bEnable);


// Tab Extensions
public:
virtual BOOL    AddApplicationTabs (LPCTSTR pszAppName);

// ClassWizard-controlled
public:
	//{{AFX_DATA(CAcUiTabMainDialog)
	enum { IDD = 0 };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CAcUiTabMainDialog)
	protected:
    virtual void OnOK();
	virtual void OnCancel();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
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
#endif

/////////////////////////////////////////////////////////////////////////////
