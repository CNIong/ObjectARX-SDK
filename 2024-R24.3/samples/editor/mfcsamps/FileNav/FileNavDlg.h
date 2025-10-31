//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#ifndef __FileNavDlg_H__
#define __FileNavDlg_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileNavDlg : public CAcUiNavDialog {
    DECLARE_DYNAMIC(CFileNavDlg)

public:
                	CFileNavDlg				(CNavDataArray& dataArray, 
											 CNavFilterArray& filterArray, 
											 UINT idd=0, 
											 CWnd *pParent=NULL,
											 HINSTANCE hDialogResource=NULL);

public:

// ClassWizard-controlled
public:
	BOOL    PreTranslateMessage(MSG* pMsg);
    //{{AFX_DATA(CFileNavDlg)
    enum { IDD = 0 };
    //}}AFX_DATA

    //{{AFX_VIRTUAL(CFileNavDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CFileNavDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnToolsTestMenu();
	afx_msg void OnViewTestMenu();
	afx_msg void OnOkTestMenu();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

public:
	virtual BOOL GetRecentDirectory(CString& strRecent);
	virtual BOOL FindInSearchPath(LPCTSTR sBase, CString* pFullPath);
	virtual void GetDefaultBrowserStartURL(CString& strStartPage);
	virtual BOOL GetProductName(CString& strProduct);
	virtual BOOL BeginDownloadFiles(CStringArray& strURLs, CDWordArray& dwActionCodes);

protected:
	virtual void OnFolderItemChange();
    virtual void OnFilterChange();
    virtual BOOL OnFileNameOK ();
	virtual void OnFileNameChange ();
	virtual void PrepareOkMenu(CMenu* pMenu);
	virtual void PrepareViewsMenu(CMenu* pMenu);
	virtual void PrepareToolsMenu(CMenu* pMenu);
	virtual void OnURLDownloadSuccess(CString& strURL);

public:
	};

#endif //__FileNavDlg_H__
