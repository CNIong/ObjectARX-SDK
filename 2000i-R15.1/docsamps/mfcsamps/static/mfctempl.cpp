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
// MFCTempl.cpp : Defines the initialization routines for the DLL.
//

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

#include "stdafx.h"
#include "MFCTempl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern "C" HWND adsw_acadMainWnd();
static HWND hWndACAD = NULL;

void MFCTest()
{

  CDiaTest Diatest(CWnd::FromHandle(adsw_acadMainWnd()));
  Diatest.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMFCTemplateApp

BEGIN_MESSAGE_MAP(CMFCTemplateApp, CWinApp)
	//{{AFX_MSG_MAP(CMFCTemplateApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCTemplateApp construction

CMFCTemplateApp::CMFCTemplateApp()
{
}

CMFCTemplateApp::~CMFCTemplateApp()
{
}
/////////////////////////////////////////////////////////////////////////////
// The one and only CMFCTemplateApp object

CMFCTemplateApp theApp;

BOOL CMFCTemplateApp::InitInstance() 
{
	TRACE("Init	Instance MFCTemplate\n");
	return CWinApp::InitInstance();
}

int CMFCTemplateApp::ExitInstance() 
{
	TRACE("Exit	Instance MFCTemplate\n");
	return CWinApp::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// CDiaTest dialog


CDiaTest::CDiaTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDiaTest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDiaTest)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDiaTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiaTest)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDiaTest, CDialog)
	//{{AFX_MSG_MAP(CDiaTest)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// END CODE APPEARING IN SDK DOCUMENT.

