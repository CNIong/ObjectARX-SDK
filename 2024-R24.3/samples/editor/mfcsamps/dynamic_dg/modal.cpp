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
// modal.cpp : Defines the initialization routines for the DLL.
#include "StdAfx.h"
//
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "AcExtensionModule.h"



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern "C" HWND adsw_acadMainWnd();

void MFCTest()
{
    // When resource from this ARX app is needed, just
    // instantiate a local CAcModuleResourceOverride
    CAcModuleResourceOverride resOverride;
    
    CDiaTest Diatest(CWnd::FromHandle(adsw_acadMainWnd()));
    Diatest.DoModal();
}


void rxTest()
{
    MFCTest();
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


/////////////////////////////////////////////////////////////////////////////
// CDiaTest message handlers
