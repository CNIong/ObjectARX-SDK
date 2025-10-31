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
