//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#ifndef _CTESTDIALOG_H
#define _CTESTDIALOG_H

//
//
//
#include "resource.h"

//
// CSampDialog 
//
class CSampDialog : public CDialog
{
public:
	CSampDialog( CWnd* pParent = NULL );

	// Dialog Data
	//{{AFX_DATA(CSampDialog)
	enum { IDD = ID_SAMPDIALOG };
	CButton	m_undoBtn;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	// Generated message map functions
	//{{AFX_MSG(CSampDialog)
	afx_msg void OnClose();
	afx_msg LRESULT onAcadKeepFocus(WPARAM, LPARAM);
	virtual void OnCancel();
	afx_msg void OnUndo();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // _CTESTDIALOG_H
