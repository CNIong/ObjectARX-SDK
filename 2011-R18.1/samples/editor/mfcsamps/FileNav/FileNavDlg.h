// (C) Copyright 1990-2002 by Autodesk, Inc. 
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
