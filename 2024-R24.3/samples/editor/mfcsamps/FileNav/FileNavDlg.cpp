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
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "FileNavDlg.h"
#include "resource.h"





#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_FILENAME_COMBO         13006

//I have assigned following the IDS to the user defined menu items.
#define ID_TOOL_TEST_MENU			1021
#define ID_OK_TEST_MENU				1022
#define ID_VIEW_TEST_MENU			1023

// How do i get the resource id ? : Open anavRes.dll in VC7 with File-->OPEN in resource mode.
//and click on the dialog id with 131 and click on file Name combo

IMPLEMENT_DYNAMIC(CFileNavDlg, CAcUiNavDialog);

CFileNavDlg::CFileNavDlg(CNavDataArray& dataArray, 
				   CNavFilterArray& filterArray, 
				   UINT idd, 
				   CWnd *pParent,
				   HINSTANCE hDialogResource)
				:  CAcUiNavDialog(dataArray, filterArray)
{
    //{{AFX_DATA_INIT(CFileNavDlg)
    //}}AFX_DATA_INIT

    // Set an application name to enable persistency and resizing.
    SetAppRootKey(_T("FILENAVROOT"));
    SetDialogName(_T("FILENAVDIALOG"));
    SetPersistency(TRUE);

}

void CFileNavDlg::DoDataExchange (CDataExchange *pDX)
{
    CAcUiNavDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CFileNavDlg)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileNavDlg, CAcUiNavDialog)
    //{{AFX_MSG_MAP(CFileNavDlg)
	ON_COMMAND(ID_TOOL_TEST_MENU, OnToolsTestMenu)
	ON_COMMAND(ID_VIEW_TEST_MENU, OnViewTestMenu)
	ON_COMMAND(ID_OK_TEST_MENU,OnOkTestMenu)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CFileNavDlg::GetRecentDirectory(CString& strRecent)
{
	TCHAR lpszPath[MAX_PATH];
	LPITEMIDLIST pidl;
	SHGetSpecialFolderLocation(m_hWnd, CSIDL_RECENT, &pidl);
	SHGetPathFromIDList(pidl, lpszPath);
	strRecent = lpszPath;

	return TRUE;
}

BOOL CFileNavDlg::FindInSearchPath(LPCTSTR sBase, CString* pFullPath)
{
	return TRUE;
}

void CFileNavDlg::GetDefaultBrowserStartURL(CString& strStartPage)
{
	strStartPage = _T("www.autodesk.com");
}

BOOL CFileNavDlg::GetProductName(CString& strProduct)
{
	return strProduct = _T("ArxFileNavTest"), TRUE;
}

BOOL CFileNavDlg::BeginDownloadFiles(CStringArray& strURLs, CDWordArray& dwActionCodes)
{
	for(int j = 0; j < strURLs.GetSize(); j++)
	{
		TRACE(_T("%s\n"), strURLs[j]);
	}
	return CAcUiNavDialog::BeginDownloadFiles(strURLs, dwActionCodes);
}

BOOL CFileNavDlg::OnInitDialog() 
{
	SetToolsMenuItemsPresent(true);
	CAcUiNavDialog::OnInitDialog();
	return TRUE;
}

void CFileNavDlg::OnFolderItemChange()
{
	CAcUiNavDialog::OnFolderItemChange();
}

void CFileNavDlg::OnFilterChange()
{
	CAcUiNavDialog::OnFilterChange();
}

// Called when the file (or path) is selected
BOOL CFileNavDlg::OnFileNameOK()
{
	return CAcUiNavDialog::OnFileNameOK();
}

// Called when user enters/modifies a file name in file name combo box
void CFileNavDlg::OnFileNameChange()
{
	CAcUiNavDialog::OnFileNameChange();
}

// One can add the menu labels from string table instead hard coding.

// Adds one more user defined menu to 'OK' button Popup Menu
void CFileNavDlg::PrepareOkMenu(CMenu* pMenu)
{
	BOOL bRet = pMenu->AppendMenu(MF_SEPARATOR);
    bRet = pMenu->InsertMenu(6,MF_BYPOSITION,ID_OK_TEST_MENU,_T("OK:Test Menu'"));
}

// Adds one more user defined menu to 'View' Popup Menu
void CFileNavDlg::PrepareViewsMenu(CMenu* pMenu)
{
	BOOL bRet = pMenu->AppendMenu(MF_SEPARATOR);
    bRet = pMenu->InsertMenu(6,MF_BYPOSITION,ID_VIEW_TEST_MENU,_T("View:Test Menu'"));
}

// Adds one more user defined menu to 'Tools' Popup Menu
void CFileNavDlg::PrepareToolsMenu(CMenu* pMenu)
{
	BOOL bRet = pMenu->AppendMenu(MF_SEPARATOR);
    bRet = pMenu->InsertMenu(6,MF_BYPOSITION,ID_TOOL_TEST_MENU ,_T("Tools:Test Menu"));
}

BOOL CFileNavDlg::PreTranslateMessage(MSG* pMsg)
{
	return CAdUiDialog::PreTranslateMessage(pMsg);
}

void CFileNavDlg::OnURLDownloadSuccess(CString& strURL)
{
	TRACE(_T("%s\n"), strURL);
}

void CFileNavDlg::OnToolsTestMenu() 
{
    AfxMessageBox (_T("You have slected the 'Tools:Test Menu'"));
}

void CFileNavDlg::OnViewTestMenu()
{
    AfxMessageBox (_T("You have slected the 'View:Test Menu'"));
}

void CFileNavDlg::OnOkTestMenu()
{
    AfxMessageBox (_T("You have slected the 'OK:Test Menu'"));
}