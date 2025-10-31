//
//
// (C) Copyright 2003-2006 by Autodesk, Inc. 
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

//-----------------------------------------------------------------------------
//----- BlkDefDlg.cpp : Implementation of CBlkDefDlg
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "resource.h"
#include "BlkDefDlg.h"

#include "asdktable.h"


//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CBlkDefDlg, CAcUiDialog)

BEGIN_MESSAGE_MAP(CBlkDefDlg, CAcUiDialog)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
CBlkDefDlg::CBlkDefDlg (CWnd *pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/) : CAcUiDialog (CBlkDefDlg::IDD, pParent, hInstance) {
}

//-----------------------------------------------------------------------------
void CBlkDefDlg::DoDataExchange (CDataExchange *pDX) {
	CAcUiDialog::DoDataExchange (pDX) ;
	DDX_Control(pDX, IDC_LIST1, m_LstBox);
	DDX_Control(pDX, IDC_CHECK1, m_link);
	DDX_Control(pDX, IDC_COMBO1, m_tableStyleLst);
	DDX_Control(pDX, IDC_EDIT1, m_newStyleName);
}

//-----------------------------------------------------------------------------
BOOL CBlkDefDlg::OnInitDialog()
{
	// Do initialization here
	CDialog::OnInitDialog();
	
	m_newStyleName.SetLimitText(10); // Limit the text input to ten charachters

	// Populate the list box with the block that have attributes
	GetBlkList();
	
	// Populate the table style list
	PopulateTableStyle();
	
	return TRUE;
}
//-----------------------------------------------------------------------------
//----- Needed for modeless dialogs to keep focus.
//----- Return FALSE to not keep the focus, return TRUE to keep the focus
LRESULT CBlkDefDlg::OnAcadKeepFocus (WPARAM, LPARAM) {
	return (TRUE) ;
}

//-----------------------------------------------------------------------------
//----- Populate the list with block definitions which have attributes
void CBlkDefDlg::GetBlkList()
{			
	// Lock the current document
	AcAxDocLock docLk;
	
	AcDbBlockTable *pBT;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBT, AcDb::kForRead);
	
	// Get the blocktable iterator
	AcDbBlockTableIterator *pItr;
	pBT->newIterator(pItr);
	
	while(!pItr->done())
	{
		AcDbBlockTableRecord *pBTR;
		pItr->getRecord(pBTR,AcDb::kForRead);
		
		// Check if it as a regular block def and has attributes
		if((!pBTR->isFromExternalReference()) && (pBTR->hasAttributeDefinitions()) && (!pBTR->isLayout()))
		{
			TCHAR *pBlkName = NULL;
			pBTR->getName(pBlkName);
			
			m_LstBox.InsertString(0,CString(pBlkName));
		}
		
		// Close the block table recod
		pBTR->close();
		
		pItr->step();
	}
	
	// Clean up
	delete pItr;
	pBT->close();
	
	
}
//-----------------------------------------------------------------------------
//----- Populate the table style list box
void CBlkDefDlg::PopulateTableStyle()
{	
	// Open the table style dictionary and iterate through the contents
	AcDbDictionary *pDict = NULL;
	Acad::ErrorStatus es = acdbHostApplicationServices()->workingDatabase() \
							->getTableStyleDictionary(pDict,AcDb::kForRead);

	if(NULL == pDict) PRTMSGRET(_T("unable to get Table Style Dictionary"))
	
	// Check if the Table Style is already existing
	if(false == pDict->has(_T("BlockAttList")))
	{
		// Close the dictionary to add the new Table style
		pDict->close();
		
		// Add a new table style
		// this is done because the existing table styles might not
		// display the table created by this sample as intended.
		// Hence creating and selecting "BlockAttList" as default table style
		addTableStyle(_T("BlockAttList"));
		
		// Open the dictionary again since we closed it to add a new entry
		acdbHostApplicationServices()->workingDatabase() \
			->getTableStyleDictionary(pDict,AcDb::kForRead);
	}
	
	AcDbDictionaryIterator *pItr = NULL;
	pItr = pDict->newIterator();
	pDict->close();

	// First item, add the "<new table style>"
	m_tableStyleLst.InsertString(0,NEWTBLSTYLE);

	if(NULL != pItr)
	{
		while(!pItr->done())
		{
			m_tableStyleLst.InsertString(1,pItr->name()); // insert the table style name
			pItr->next();
		}

		delete pItr;
	}
	
	// Select the first existing table style
	if(1 != m_tableStyleLst.GetCount())
	{
		m_tableStyleLst.SetCurSel(m_tableStyleLst.FindStringExact(0,_T("BlockAttList")));
		m_newStyleName.EnableWindow(FALSE);
	}
	else
	{
		m_tableStyleLst.SetCurSel(0);
		m_newStyleName.EnableWindow(TRUE);
	}
}

//-----------------------------------------------------------------------------
//----- Get the selected table style name, if required create a new one
CString CBlkDefDlg::GetTableStyleName()
{
	// Check if we need to create a new table style
	CString strStyleName;
	if(0 == m_tableStyleLst.GetCurSel())
	{
		long nLen = m_newStyleName.GetLimitText();
		m_newStyleName.GetLine(0,strStyleName.GetBuffer(nLen),nLen);
		strStyleName.ReleaseBuffer();
		if(Acad::eOk != addTableStyle(strStyleName.GetBuffer())) return strStyleName; // return if unable to add a table
	}
	else
	{
		long nIdx = m_tableStyleLst.GetCurSel();
		m_tableStyleLst.GetLBText(nIdx, strStyleName.GetBuffer(m_tableStyleLst.GetLBTextLen(nIdx)));
		strStyleName.ReleaseBuffer();
	}
	return strStyleName;
}

//-----------------------------------------------------------------------------
//----- Create new table
void CBlkDefDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	
	// Get the selected Items text
	int nSelIdx = m_LstBox.GetCurSel();

	if (LB_ERR == nSelIdx)
	{
		AfxMessageBox(_T("Select a block in the list"));
		return;
	}
	
	CString strBlkName;
	m_LstBox.GetText(nSelIdx, strBlkName.GetBuffer(m_LstBox.GetTextLen(nSelIdx)));
	strBlkName.ReleaseBuffer();

	// Close the dialog
	CDialog::OnOK();
	
	// Create the table now	
	CString strTableStyle = GetTableStyleName();
	if(_T("") == strTableStyle) return;
	
	buildTableFromBlock((TCHAR *)strBlkName.GetBuffer(), (TCHAR *)strTableStyle.GetBuffer(),
						 (BST_CHECKED == m_link.GetState()?true:false));
}

//-----------------------------------------------------------------------------
//----- Update existing table
void CBlkDefDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	// Get the selected Items text
	int nSelIdx = m_LstBox.GetCurSel();

	if (LB_ERR == nSelIdx)
	{
		AfxMessageBox(_T("Select a block in the list"));
		return;
	}

	CString strBlkName;
	m_LstBox.GetText(nSelIdx, strBlkName.GetBuffer(m_LstBox.GetTextLen(nSelIdx)));
	strBlkName.ReleaseBuffer();

	// Close the dialog
	CDialog::OnOK();
	
	CString strTableStyle = GetTableStyleName();
	if(_T("") == strTableStyle) return;
	
	// Update the existing table now
	updateExistingTable((TCHAR *)strBlkName.GetBuffer(), (TCHAR *)strTableStyle.GetBuffer(),
						(BST_CHECKED == m_link.GetState()?true:false));
}

//-----------------------------------------------------------------------------
//----- Watch for selection changed
void CBlkDefDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	
	// Check if the  "<new table style>" is selected
	
	if(0 == m_tableStyleLst.GetCurSel())
	{
		m_newStyleName.EnableWindow(TRUE);
	}
	else
	{
		m_newStyleName.EnableWindow(FALSE);
	}
}
