// 
// (C) Copyright 1993-1999 by Autodesk, Inc. 
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
//

#include "stdafx.h"
#include "MFCTempl.h"
#include "AcExtensionModule.h"
#include "rxtemplt.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern "C" HWND adsw_acadMainWnd();
static HWND hWndACAD = NULL;


static bool openFlag = false;    // Flag for checking whether the Open button was clicked.
static bool newFlag = false;     // Flag for checking whether the New button was clicked.
static bool showDlg = true;      // Flag for checking whether to show Dialog.


AC_IMPLEMENT_EXTENSION_MODULE(theArxDLL);

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
        theArxDLL.AttachInstance(hInstance);
	else if (dwReason == DLL_PROCESS_DETACH)
        theArxDLL.DetachInstance();  
	
	return 1;   // ok
}


void InitMFC()
{
    hWndACAD = /* GetActiveWindow() */ adsw_acadMainWnd();
}


void EndMFC()
{
}


void openFile()
{
	    openFlag = false;
	    acDocManager->openDocument();
}


void newFile()
{
	    newFlag = false;
	    acDocManager->newDocument();
}


void MFCTest()
{

    // When resource from this ARX app is needed, just
    // instantiate a local CAcModuleResourceOverride
	if (showDlg)
	{
		{
			CAcModuleResourceOverride resOverride;
  
			CDiaTest Diatest(CWnd::FromHandle(hWndACAD));
			Diatest.DoModal();
		}

		// Check to see if the Open button was clicked

		if (openFlag)
			openFile ();
		if (newFlag)
			newFile ();

	}

	
}


void MFCTest0()
{

	showDlg = true;
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
	DDX_Control(pDX, IDC_LIST1, m_ShowText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDiaTest, CDialog)
	//{{AFX_MSG_MAP(CDiaTest)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// END CODE APPEARING IN SDK DOCUMENT.


void CDiaTest::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}

void CDiaTest::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDiaTest::OnButton1() 
{
	// Set flag to invoke file dialog
	openFlag = true;
	OnOK();

}

void CDiaTest::OnCheck1() 
{
	// TODO: Add your control notification handler code here
    showDlg = !showDlg;
	
}

void CDiaTest::OnButton2() 
{
	// Set flag to invoke file dialog
	newFlag = true;
	OnOK();
	
}


void CDiaTest::OnButton4() 
{
	// TODO: Add your control notification handler code here
	m_ShowText.ShowWindow(SW_SHOW);
	m_ShowText.ResetContent();

	m_ShowText.AddString("Help:");
	m_ShowText.AddString("");
	m_ShowText.AddString("To start a new");
	m_ShowText.AddString("drawing, click New.");
	m_ShowText.AddString("To open a drawing,");
	m_ShowText.AddString("click Open.");
	m_ShowText.AddString("If you check the Hide");
	m_ShowText.AddString("box, use ShowWiz to");
	m_ShowText.AddString("display the dialog.");

}
