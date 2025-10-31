//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
#if !defined(AFX_DWGSETNGTAB1_H__6C66D660_6E51_11D2_A2F3_0080C7D122A2__INCLUDED_)
#define AFX_DWGSETNGTAB1_H__6C66D660_6E51_11D2_A2F3_0080C7D122A2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DwgSetngTab1.h : header file
//
#include <adui.h>
#include <acui.h>
#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// CDwgSetngTab1 dialog

class CDwgSetngTab1 : public CAcUiTabChildDialog
{
// Construction
public:
	CDwgSetngTab1(CWnd* pParent = NULL);   // standard constructor

	CString m_strXPt;
	CString m_strYPt;
	CString m_strZPt;

	void DisplayPoint();
	bool ValidatePoint();

	virtual void OnMainDialogCancel();
    virtual void OnMainDialogOK();
    virtual BOOL OnMainDialogHelp();    


// Dialog Data
	//{{AFX_DATA(CDwgSetngTab1)
	enum { IDD = IDD_TAB1 };
	CAcUiNumericEdit	m_ctrlXPtEdit;
	CAcUiNumericEdit	m_ctrlYPtEdit;
	CAcUiNumericEdit	m_ctrlZPtEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDwgSetngTab1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDwgSetngTab1)
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusEditXpt();
	afx_msg void OnKillfocusEditYpt();
	afx_msg void OnKillfocusEditZpt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DWGSETNGTAB1_H__6C66D660_6E51_11D2_A2F3_0080C7D122A2__INCLUDED_)
