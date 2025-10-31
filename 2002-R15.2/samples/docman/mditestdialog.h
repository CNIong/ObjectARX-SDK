// (C) Copyright 1998 by Autodesk, Inc.
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
// MDITestDialog.h : dialog definition
//

#ifndef _MDITESTDIALOG_H_
#define _MDITESTDIALOG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CMDITestDialog dialog

class CMDITestDialog : public CDialog
{
// Construction
public:
	CMDITestDialog(CWnd* pParent = NULL);   // standard constructor
	BOOL Create( CWnd* pParent = NULL );

// Dialog Data
	//{{AFX_DATA(CMDITestDialog)
	enum { IDD = IDD_TEST_DIALOG };
	CStatic	m_staticActDocMyLockStatus;
	CStatic	m_staticCurrentDoc;
	CStatic	m_staticCurDocLockStatus;
	CStatic	m_staticCurDocMyLockStatus;
	CStatic	m_staticActDocLockStatus;
	CComboBox	m_lockCombo;
	CStatic	m_staticActiveDoc;
	CStatic	m_staticToBeCurrDoc;
	CButton	m_activationCheck;
	CStatic	m_staticDocNum;
	CListBox	m_docListBox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDITestDialog)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void RebuildListBox( void );
	afx_msg LONG onAcadKeepFocus ( UINT, LONG );
	afx_msg void onAcadUpdateDialog ( UINT, LONG );
	afx_msg void onAcadCreateDoc ( UINT, LONG );
	afx_msg void onAcadDestroyDoc ( UINT, LONG );
	afx_msg void onAcadLockModeChanged ( UINT, LONG );
	afx_msg void onAcadLockModeWillChange ( UINT, LONG );
	afx_msg void onAcadCurrDoc ( UINT, LONG );
	afx_msg void onAcadActivateDoc ( UINT, LONG );
	afx_msg void onAcadDeactivateDoc ( UINT, LONG );
    afx_msg void onAcadActModifiedDoc ( UINT, LONG );
	void cleanUpUI( void );
	CString getDocCount( void );
	CString makeStringFromPtr( LONG pCh );
	bool getDocFromFilename(CString csFileName, AcApDocument* &pNewDocument);
	AcApDocument* getSelectedDocument( void );
	AcAp::DocLockMode getSelectedLockMode( void );

	// Generated message map functions
	//{{AFX_MSG(CMDITestDialog)
	afx_msg void OnNewdocButton();
	afx_msg void OnAppnewdocButton();
	afx_msg void OnAppopendocButton();
	afx_msg void OnActivationCheck();
	afx_msg void OnSendstringButton();
	afx_msg void OnOpendocButton();
	afx_msg void OnIsquiescentButton();
	afx_msg void OnClosedocButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnActivatedocButton();
	afx_msg void OnSetcurrentdocButton();
	afx_msg void OnRefreshButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif 
