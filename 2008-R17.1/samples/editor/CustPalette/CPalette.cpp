// (C) Copyright 2000-2007 by Autodesk, Inc. 
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

//-----------------------------------------------------------------------------
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "Palette.h"
#include "PaletteSet.h"



//Utility functions to add and get the child node from the parent XML-DOM node
extern BOOL GetChildNode(MSXML::IXMLDOMNode* pNode, 
								LPCTSTR pszNodeName, 
								MSXML::IXMLDOMNode** ppChild);

extern BOOL AddChildNode(MSXML::IXMLDOMNode* pNode, LPCTSTR pszChildNodeName,
						 short nNodeType, MSXML::IXMLDOMNode** ppChild);

// The file name of the persisted palette 
#define DATA_PALETTE_FILENAME _T("TestDataPalette.xml")

//-----------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(CDataPalette, CAdUiPalette)


//-----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CDataPalette, CAdUiPalette)
	ON_MESSAGE(WM_CTLCOLORSTATIC, OnCtlColorStatic)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(ID_COMBO, OnComboChange)
	ON_EN_UPDATE(ID_STRING_EDIT, OnStringChange)
	ON_EN_UPDATE(ID_INT_EDIT, OnIntChange)
	ON_EN_UPDATE(ID_REAL_EDIT, OnRealChange)
END_MESSAGE_MAP()

CDataPalette::CDataPalette()
{
	// initialize integer and real arrays to zero
	for(int i = 0; i < 2; i ++){
		integer[i] = 0;
		real[i] = 0;
	}
}

CDataPalette::~CDataPalette()
{
	//
}

// Load the data from xml.
BOOL CDataPalette::Load(IUnknown* pUnk) 
{	
	// Call base class first 
	CAdUiPalette::Load(pUnk);
	
	CComQIPtr<MSXML::IXMLDOMNode> pNode(pUnk);
	MSXML::IXMLDOMNodePtr pChild, pChild1;

	BSTR text;
	////////////// Item 1 ///////////////////////
	GetChildNode(pNode, _T("Item1"), &pChild);
	GetChildNode(pChild, _T("String"), &pChild1);
	pChild1->get_text(&text);
	str[0] = CString(text);

	GetChildNode(pChild, _T("Integer"), &pChild1);
	pChild1->get_text(&text);
	integer[0] = _ttoi(CString(text));

	GetChildNode(pChild, _T("Real"), &pChild1);
	pChild1->get_text(&text);
	real[0] = _tstof(CString(text));

	///////////////// Item 2 ///////////////////
	GetChildNode(pNode, _T("Item2"), &pChild);
	GetChildNode(pChild, _T("String"), &pChild1);
	pChild1->get_text(&text);
	str[1] = CString(text);

	GetChildNode(pChild, _T("Integer"), &pChild1);
	pChild1->get_text(&text);
	integer[1] = _ttoi(CString(text));

	GetChildNode(pChild, _T("Real"), &pChild1);
	pChild1->get_text(&text);
	real[1] = _tstof(CString(text));

	return TRUE;
}

// Save the data to xml.
BOOL CDataPalette::Save(IUnknown* pUnk) 
{
	// Call base class first 
	CAdUiPalette::Save(pUnk);
	
	CComQIPtr<MSXML::IXMLDOMNode> pNode(pUnk);
	MSXML::IXMLDOMNodePtr pChild, pChild1;
	CString *pText=new CString;
	int  n = m_Combo.GetCount();

	///////////////// Item 1 ///////////////////////
	AddChildNode(pNode,_T("Item1"),MSXML::NODE_ELEMENT, &pChild);	
	AddChildNode(pChild, _T("String"), MSXML::NODE_ELEMENT, &pChild1);
	pChild1->put_text(CString(str[0]).AllocSysString());
	

	AddChildNode(pChild, _T("Integer"), MSXML::NODE_ELEMENT, &pChild1);
	pChild1->put_text(bstr_t(integer[0]));
	

	AddChildNode(pChild, _T("Real"), MSXML::NODE_ELEMENT, &pChild1);
	pChild1->put_text(bstr_t(real[0]));
	
	////////////////// Item 2 /////////////////////////
	AddChildNode(pNode,_T("Item2"),MSXML::NODE_ELEMENT, &pChild);	
	AddChildNode(pChild, _T("String"), MSXML::NODE_ELEMENT, &pChild1);
	pChild1->put_text(CString(str[1]).AllocSysString());
	

	AddChildNode(pChild, _T("Integer"), MSXML::NODE_ELEMENT, &pChild1);
	pChild1->put_text(bstr_t(integer[1]));
	

	AddChildNode(pChild, _T("Real"), MSXML::NODE_ELEMENT, &pChild1);
	pChild1->put_text(bstr_t(real[1]));

	/////////////////////////////

	return TRUE;
}


// Called by the palette set when the palette is made active
void CDataPalette::OnSetActive() 
{
	CString s;
	if(m_Combo.GetCurSel() == 0) {
		m_StringEdit.SetWindowText(str[0]);
		s.Format(_T("%d"), integer[0]);
		m_IntEdit.SetWindowText(s);
		s.Format(_T("%.3f"), real[0]);
		m_RealEdit.SetWindowText(s);
		m_TextLabel.SetWindowText(_T("Item 1"));
	} else if (m_Combo.GetCurSel() == 1) {
		m_StringEdit.SetWindowText(str[1]);
		s.Format(_T("%d"), integer[1]);
		m_IntEdit.SetWindowText(s);
		s.Format(_T("%.3f"), real[1]);
		m_RealEdit.SetWindowText(s);
		m_TextLabel.SetWindowText(_T("Item 2"));
	}

	// Create a brush if not already created
	if(m_Brush.m_hObject == NULL)
		m_Brush.CreateSolidBrush(GetPaletteSet()->GetTheme()->GetColor(kPaletteBackground));

	return CAdUiPalette::OnSetActive();
}


LRESULT CDataPalette::OnCtlColorStatic(WPARAM wParam, LPARAM lParam)
{
	HDC hDC = (HDC)wParam;

	// match the background of all static controls to the palette's background color 
	CDC *pDC = CDC::FromHandle(hDC);
	pDC->SetBkMode(TRANSPARENT);
	return (LRESULT)HBRUSH(m_Brush);

}

// Changes text in edit boxes for "Item1" and "Item2"
void CDataPalette::OnComboChange() 
{
	CString s;
	if(m_Combo.GetCurSel() == 0) {
		m_StringEdit.SetWindowText(str[0]);
		s.Format(_T("%d"), integer[0]);
		m_IntEdit.SetWindowText(s);
		s.Format(_T("%.3f"),real[0]);
		m_RealEdit.SetWindowText(s);
		m_TextLabel.SetWindowText(_T("Item 1"));
	} else if (m_Combo.GetCurSel() == 1) {
		m_StringEdit.SetWindowText(str[1]);
		s.Format(_T("%d"), integer[1]);
		m_IntEdit.SetWindowText(s);
		s.Format(_T("%.3f"),real[1]);
		m_RealEdit.SetWindowText(s);
		m_TextLabel.SetWindowText(_T("Item 2"));
	}
}

// "Integer" edit box update
void CDataPalette::OnIntChange()
{
	CString s;
	if(m_Combo.GetCurSel() == 0) { 
		m_IntEdit.GetWindowText(s);
		integer[0] = _ttoi((LPCTSTR)s);
	} else if(m_Combo.GetCurSel() == 1) { 
		m_IntEdit.GetWindowText(s);
		integer[1] = _ttoi((LPCTSTR)s);
	}
}

// "String" edit box update
void CDataPalette::OnStringChange()
{
	CString s;
	if(m_Combo.GetCurSel() == 0) { 
		m_StringEdit.GetWindowText(s);
		str[0] = s;
	} else if(m_Combo.GetCurSel() == 1) { 
		m_StringEdit.GetWindowText(s);
		str[1] = s;
	}
}

// "Real" edit box update
void CDataPalette::OnRealChange()
{
	CString s;
	if(m_Combo.GetCurSel() == 0) { 
		m_RealEdit.GetWindowText(s);
		real[0] = _tstof((LPCTSTR)s);
	} else if(m_Combo.GetCurSel() == 1) { 
		m_RealEdit.GetWindowText(s);
		real[1] = _tstof((LPCTSTR)s);
	}
}

//void CDataPalette::addControls()
//{
int CDataPalette::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CAdUiPalette::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Add combo box
	m_Combo.Create(CBS_DROPDOWNLIST | CBS_SORT | WS_VISIBLE | WS_TABSTOP,
		CRect(10,8,200,300) , this , ID_COMBO);
	m_Combo.AddString(_T("Item 1"));
	m_Combo.AddString(_T("Item 2"));
	m_Combo.SetCurSel(0);

	// Add label for data items
	m_DataLabel.Create(_T("Data for"), SS_LEFT, CRect(0, 0, 60, 20), this, 1);
	m_DataLabel.SetWindowPos(NULL, 60, 60, 60, 20, SWP_SHOWWINDOW);

	// Add dynamic label (based on combo item picked)
	m_TextLabel.Create(_T(""), SS_LEFT, CRect(0, 0, 60, 20), this, ID_STATIC);
	m_TextLabel.SetWindowPos(NULL, 125, 60, 60, 20, SWP_SHOWWINDOW);

	// Add String Edit box
	m_StringEdit.Create(ES_LEFT | WS_BORDER | WS_GROUP, CRect(0, 0, 110, 20), this, ID_STRING_EDIT);
	m_StringEdit.SetWindowPos(NULL, 90, 110, 110, 20, SWP_SHOWWINDOW);
	
	// Add label to String Edit box
	m_StrLabel.Create(_T("String"), SS_LEFT, CRect(0, 0, 60, 20), this);
	m_StrLabel.SetWindowPos(NULL, 20, 110, 60, 20, SWP_SHOWWINDOW);

	// Add Integer Edit box
	m_IntEdit.Create(ES_LEFT | WS_BORDER | ES_NUMBER, CRect(0, 0, 110, 20), this, ID_INT_EDIT);
	m_IntEdit.SetWindowPos(NULL, 90, 160, 110, 20, SWP_SHOWWINDOW);

	// Add label to Integer Edit box
	m_IntLabel.Create(_T("Integer"), SS_LEFT, CRect(0, 0, 60, 20), this);
	m_IntLabel.SetWindowPos(NULL, 20, 160, 60, 20, SWP_SHOWWINDOW);

	// Add Real Edit box
	m_RealEdit.Create(ES_LEFT | WS_BORDER, CRect(0, 0, 110, 20), this, ID_REAL_EDIT);
	m_RealEdit.SetWindowPos(NULL, 90, 210, 110, 20, SWP_SHOWWINDOW);

	// Add label to Real Edit box
	m_RealLabel.Create(_T("Real"), SS_LEFT, CRect(0, 0, 60, 20), this);
	m_RealLabel.SetWindowPos(NULL, 20, 210, 60, 20, SWP_SHOWWINDOW);

	// Load Palette's persistent data
	LoadPalette();

	// Set the Palette's title
	SetName(_T("Data"));
	return 0;
}

void CDataPalette::OnDestroy()
{
	// Save Palette's persistent data
	SavePalette();
	CAdUiPalette::OnDestroy();
}

//Called by AutoCAD to steal focus from the palette
bool CDataPalette::CanFrameworkTakeFocus()
{
	// not simply calling IsFloating() (a BOOL) avoids warning C4800
	return ( GetPaletteSet()->IsFloating() == TRUE ? true : false );
}

void CDataPalette::LoadPalette()
{
	MSXML::IXMLDOMDocumentPtr pDoc = NULL;
	HRESULT hr = pDoc.CreateInstance(CLSID_DOMDocumentAcad);

	const TCHAR *pRoam;
	TCHAR paletteBuffer[MAX_PATH];
	BOOL bResult=acdbHostApplicationServices()->getRoamableRootFolder(pRoam);
	_tcscpy(paletteBuffer, pRoam);
	_tcscat(paletteBuffer, DATA_PALETTE_FILENAME);
	CComVariant var(paletteBuffer);

	VARIANT_BOOL bReturn = pDoc->load(var);
	if (bReturn == VARIANT_TRUE) // success!
	{
		MSXML::IXMLDOMNodePtr pNode;
		GetChildNode(pDoc->documentElement,_T("Palette"),&pNode);
		Load(pNode);
	}
}

void CDataPalette::SavePalette()
{
	MSXML::IXMLDOMDocumentPtr pDoc = NULL;
	HRESULT hr = pDoc.CreateInstance(CLSID_DOMDocumentAcad);

	const TCHAR *pRoam;
	TCHAR paletteBuffer[MAX_PATH];
	BOOL bResult=acdbHostApplicationServices()->getRoamableRootFolder(pRoam);
	_tcscpy(paletteBuffer, pRoam);
	_tcscat(paletteBuffer, DATA_PALETTE_FILENAME);
	CComVariant var(paletteBuffer);

	// create a root element
	MSXML::IXMLDOMNodePtr pNode;
	if (AddChildNode(pDoc, _T("Palette"), MSXML::NODE_ELEMENT, &pNode) == FALSE)
		return;
	Save(pNode);
	hr = pDoc->save(var);
}
