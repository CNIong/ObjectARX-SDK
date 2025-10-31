//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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
// Tab4.h: interface for the CTab2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TAB2_H__4F728C08_C8C9_11D1_8B78_0060B0B5E114__INCLUDED_)
#define AFX_TAB2_H__4F728C08_C8C9_11D1_8B78_0060B0B5E114__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <adui.h>
#include <acui.h>
#include "resource.h"

#endif // !defined(AFX_TAB4_H__4F728C08_C8C9_11D1_8B78_0060B0B5E114__INCLUDED_)
/////////////////////////////////////////////////////////////////////////////
// CTab4 dialog

class CTab2 : public CAcUiTabChildDialog
{
// Construction
public:
	CTab2(CWnd* pParent = NULL);   // standard constructor
	
	virtual BOOL OnMainDialogHelp(); 
	
// Dialog Data
	//{{AFX_DATA(CTab4)
	enum { IDD = IDD_TAB2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTab4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTab2)
	afx_msg void OnButton();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
