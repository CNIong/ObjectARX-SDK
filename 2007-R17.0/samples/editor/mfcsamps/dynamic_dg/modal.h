//
// (C) Copyright 1999-2006 by Autodesk, Inc.
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

// MFCTemplate.h : main header file for the MFCTEMPLATE DLL
//

#ifndef __AFXWIN_H__
	#error include _T('stdafx.h') before including this file for PCH
#endif

#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CMFCTemplateApp
// See MFCTemplate.cpp for the implementation of this class
//

class CMFCTemplateApp : public CWinApp
{
public:
	CMFCTemplateApp();
	virtual ~CMFCTemplateApp();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCTemplateApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMFCTemplateApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CDiaTest dialog

class CDiaTest : public CDialog
{
public:
	CDiaTest(CWnd* pParent = NULL);
	enum { IDD = IDD_TEST };

	// Dialog Data
	//{{AFX_DATA(CDiaTest)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


protected:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiaTest)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CDiaTest)
	// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
