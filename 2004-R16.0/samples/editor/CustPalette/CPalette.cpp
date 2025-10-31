//
//
// (C) Copyright 2000-2002 by Autodesk, Inc. 
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
#include "Palette.h"

//-----------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(CPicClip, CWnd)
IMPLEMENT_DYNCREATE(CMyPalette, CAdUiPalette)

// PicClip method -------------------------------------------------------------
void CPicClip::SetPicture(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		newValue);
}

//-----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CMyPalette, CAdUiPalette)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(ID_COMBO, OnComboChange)
	ON_EN_UPDATE(ID_STRING_EDIT, OnStringChange)
	ON_EN_UPDATE(ID_INT_EDIT, OnIntChange)
	ON_EN_UPDATE(ID_REAL_EDIT, OnRealChange)
END_MESSAGE_MAP()

CMyPalette::CMyPalette()
{
	m_Brush = new CBrush;
	COLORREF color(RGB(255, 255, 255));
	m_Brush->CreateSolidBrush(color); // White brush

	// initialize integer and real arrays to zero
	for(int i = 0; i < 2; i ++){
		integer[i] = 0;
		real[i] = 0;
	}
}

CMyPalette::~CMyPalette()
{
	delete m_Brush;
	deleteControls();
}

// Load the data from xml.
BOOL CMyPalette::Load(IUnknown* pUnk) 
{	
	// Call base class first 
	CAdUiPalette::Load(pUnk);
	
	CComQIPtr<MSXML::IXMLDOMNode> pNode(pUnk);
	MSXML::IXMLDOMNodePtr pChild, pChild1;

	BSTR text;
	////////////// Item 1 ///////////////////////
	GetChildNode(pNode, "Item1", &pChild);
	GetChildNode(pChild, "String", &pChild1);
	pChild1->get_text(&text);
	str[0] = CString(text);

	GetChildNode(pChild, "Integer", &pChild1);
	pChild1->get_text(&text);
	integer[0] = atoi(CString(text));

	GetChildNode(pChild, "Real", &pChild1);
	pChild1->get_text(&text);
	real[0] = atof(CString(text));

	///////////////// Item 2 ///////////////////
	GetChildNode(pNode, "Item2", &pChild);
	GetChildNode(pChild, "String", &pChild1);
	pChild1->get_text(&text);
	str[1] = CString(text);

	GetChildNode(pChild, "Integer", &pChild1);
	pChild1->get_text(&text);
	integer[1] = atoi(CString(text));

	GetChildNode(pChild, "Real", &pChild1);
	pChild1->get_text(&text);
	real[1] = atof(CString(text));

	return TRUE;
}

// Save the data to xml.
BOOL CMyPalette::Save(IUnknown* pUnk) 
{
	// Call base class first 
	CAdUiPalette::Save(pUnk);
	
	CComQIPtr<MSXML::IXMLDOMNode> pNode(pUnk);
	MSXML::IXMLDOMNodePtr pChild, pChild1;
	CString *pText=new CString;
	int  n = pCombo->GetCount();

	///////////////// Item 1 ///////////////////////
	AddChildNode(pNode,"Item1",MSXML::NODE_ELEMENT, &pChild);	
	AddChildNode(pChild, "String", MSXML::NODE_ELEMENT, &pChild1);
	pChild1->put_text(CString(str[0]).AllocSysString());
	

	AddChildNode(pChild, "Integer", MSXML::NODE_ELEMENT, &pChild1);
	pChild1->put_text(bstr_t(integer[0]));
	

	AddChildNode(pChild, "Real", MSXML::NODE_ELEMENT, &pChild1);
	pChild1->put_text(bstr_t(real[0]));
	
	////////////////// Item 2 /////////////////////////
	AddChildNode(pNode,"Item2",MSXML::NODE_ELEMENT, &pChild);	
	AddChildNode(pChild, "String", MSXML::NODE_ELEMENT, &pChild1);
	pChild1->put_text(CString(str[1]).AllocSysString());
	

	AddChildNode(pChild, "Integer", MSXML::NODE_ELEMENT, &pChild1);
	pChild1->put_text(bstr_t(integer[1]));
	

	AddChildNode(pChild, "Real", MSXML::NODE_ELEMENT, &pChild1);
	pChild1->put_text(bstr_t(real[1]));

	/////////////////////////////

	return TRUE;
}


// Called by the palette set when the palette is made active
void CMyPalette::OnSetActive() 
{
	CString s;
	if(pCombo->GetCurSel() == 0) {
		pStringEdit->SetWindowText(str[0]);
		s.Format("%d", integer[0]);
		pIntEdit->SetWindowText(s);
		s.Format("%.3f", real[0]);
		pRealEdit->SetWindowText(s);
		pTextLabel->SetWindowText("Item 1");
	} else if (pCombo->GetCurSel() == 1) {
		pStringEdit->SetWindowText(str[1]);
		s.Format("%d", integer[1]);
		pIntEdit->SetWindowText(s);
		s.Format("%.3f", real[1]);
		pRealEdit->SetWindowText(s);
		pTextLabel->SetWindowText("Item 2");
	}

	return CAdUiPalette::OnSetActive();
}

// Paints each control's background with m_brush's color
HBRUSH CMyPalette::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CAdUiPalette::OnCtlColor(pDC, pWnd, nCtlColor);

	// Change any attributes of the DC here
	// so background of all controls will show thru.
	pDC->SetBkMode(TRANSPARENT);

	// Return handle to our CBrush object
	hbr = (HBRUSH)m_Brush->GetSafeHandle();
	
	// Return a different brush if the default is not desired
	return hbr;
}

// Changes text in edit boxes for "Item1" and "Item2"
void CMyPalette::OnComboChange() 
{
	CString s;
	if(pCombo->GetCurSel() == 0) {
		pStringEdit->SetWindowText(str[0]);
		s.Format("%d", integer[0]);
		pIntEdit->SetWindowText(s);
		s.Format("%.3f",real[0]);
		pRealEdit->SetWindowText(s);
		pTextLabel->SetWindowText("Item 1");
	} else if (pCombo->GetCurSel() == 1) {
		pStringEdit->SetWindowText(str[1]);
		s.Format("%d", integer[1]);
		pIntEdit->SetWindowText(s);
		s.Format("%.3f",real[1]);
		pRealEdit->SetWindowText(s);
		pTextLabel->SetWindowText("Item 2");
	}
}
	
//Utility functions to add and get the child node from the parent XML-DOM node
BOOL CMyPalette::GetChildNode(MSXML::IXMLDOMNode* pNode, 
							 LPCTSTR pszNodeName, 
							 MSXML::IXMLDOMNode** ppChild)
{
	try {
		ASSERT(ppChild != NULL);
		if (ppChild == NULL)
			return FALSE;

		*ppChild = NULL;

		ASSERT(pNode != NULL && pszNodeName != NULL);
		if (pNode == NULL || pszNodeName == NULL)
			return FALSE;

		USES_CONVERSION;

		CComBSTR bstrName;
		pNode->get_nodeName(&bstrName);

		CString sName = OLE2A(bstrName);
		if (sName.CompareNoCase(pszNodeName) == 0) {
			*ppChild = pNode;
			// AddRef before returning
			if (*ppChild != NULL)
				(*ppChild)->AddRef();
			return TRUE;
		}
		// Get the named child element from the list of children
		//
		MSXML::IXMLDOMNodeListPtr pChildren; 
		pNode->get_childNodes(&pChildren);
		ASSERT(pChildren != NULL);
		if (pChildren == NULL) {
			ASSERT(FALSE);
			return FALSE;
		}

		int nCount = pChildren->Getlength();
		if (nCount < 1) {
			// No children
			return FALSE;
		}

		for (long i=0; i<nCount; i++) {
			MSXML::IXMLDOMNodePtr pNode;
			pChildren->get_item(i, &pNode);
			ASSERT(pNode != NULL);

			CComBSTR bstrName;
			pNode->get_nodeName(&bstrName);

			CString sName = OLE2A(bstrName);
			if (sName.CompareNoCase(pszNodeName) == 0) {
				*ppChild = pNode.GetInterfacePtr();
				// AddRef before returning
				if (*ppChild != NULL)
					(*ppChild)->AddRef();
				return TRUE;
			}
		}
	} catch (_com_error  &e) {
		ASSERT(FALSE);
		SetLastError(e.Error());
		return FALSE;
	} catch (...) {
		TRACE("Exception\n");        
		return FALSE;
	}

	// Named child not found
	return FALSE;
}

BOOL CMyPalette::AddChildNode(MSXML::IXMLDOMNode* pNode, LPCTSTR pszChildNodeName,
							 short nNodeType, MSXML::IXMLDOMNode** ppChild)
{
	USES_CONVERSION;

	try {
		ASSERT(ppChild != NULL);
		if (ppChild == NULL)
			return FALSE;

		*ppChild = NULL;

		ASSERT(pNode != NULL && pszChildNodeName != NULL );
		if (pNode == NULL || pszChildNodeName == NULL)
			return FALSE;

		CString strName(pszChildNodeName);

		MSXML::IXMLDOMDocumentPtr pDoc;
		MSXML::DOMNodeType type;
		pNode->get_nodeType(&type);
		if (type == MSXML::NODE_DOCUMENT)
			pDoc = pNode;
		else {
			pNode->get_ownerDocument(&pDoc);
			ASSERT( pDoc != NULL);
			if (pDoc == NULL)
				return FALSE;
		}

		_variant_t varType(nNodeType);
		_bstr_t varName(strName);//pszChildNodeName);

		MSXML::IXMLDOMNodePtr pNewNode = pDoc->createNode(varType, varName, "");;
		*ppChild = pNewNode.GetInterfacePtr();
		// AddRef before returning
		if (*ppChild != NULL)
			(*ppChild)->AddRef();

		pNode->appendChild(*ppChild);
	} catch (_com_error  &e) {
		ASSERT(FALSE);
		SetLastError(e.Error());
		return FALSE;
	} catch (...) {
		TRACE("Exception\n");        
		return FALSE;
	}
	return TRUE;
}

// "Integer" edit box update
void CMyPalette::OnIntChange()
{
	CString s;
	if( pCombo->GetCurSel() == 0) { 
		pIntEdit->GetWindowText(s);
		integer[0] = _ttoi((LPCTSTR)s);
	} else if( pCombo->GetCurSel() == 1) { 
		pIntEdit->GetWindowText(s);
		integer[1] = _ttoi((LPCTSTR)s);
	}
}

// "String" edit box update
void CMyPalette::OnStringChange()
{
	CString s;
	if( pCombo->GetCurSel() == 0) { 
		pStringEdit->GetWindowText(s);
		str[0] = s;
	} else if( pCombo->GetCurSel() == 1) { 
		pStringEdit->GetWindowText(s);
		str[1] = s;
	}
}

// "Real" edit box update
void CMyPalette::OnRealChange()
{
	CString s;
	if( pCombo->GetCurSel() == 0) { 
		pRealEdit->GetWindowText(s);
		real[0] = atof((LPCTSTR)s);
	} else if( pCombo->GetCurSel() == 1) { 
		pRealEdit->GetWindowText(s);
		real[1] = atof((LPCTSTR)s);
	}
}

void CMyPalette::addControls()
{
	// Add combo box
	pCombo = new CAdUiComboBox;
	pCombo->Create(CBS_DROPDOWNLIST | CBS_SORT | WS_VISIBLE | WS_TABSTOP,
		CRect(10,8,200,300) , this , ID_COMBO);
	pCombo->AddString("Item 1");
	pCombo->AddString("Item 2");
	pCombo->SetCurSel(0);

	// Add label for data items
	pDataLabel = new CStatic;
	pDataLabel->Create("Data for", SS_LEFT, CRect(0, 0, 60, 20), this);
	pDataLabel->SetWindowPos(NULL, 60, 60, 60, 20, SWP_SHOWWINDOW);

	// Add dynamic label (based on combo item picked)
	pTextLabel = new CStatic;
	pTextLabel->Create("", SS_LEFT, CRect(0, 0, 60, 20), this, ID_STATIC);
	pTextLabel->SetWindowPos(NULL, 125, 60, 60, 20, SWP_SHOWWINDOW);

	// Add String Edit box
	pStringEdit = new CAcUiStringEdit;
	pStringEdit->Create(ES_LEFT | WS_BORDER | WS_GROUP, CRect(0, 0, 110, 20), this, ID_STRING_EDIT);
	pStringEdit->SetWindowPos(NULL, 90, 110, 110, 20, SWP_SHOWWINDOW);
	
	// Add label to String Edit box
	pStrLabel = new CStatic;
	pStrLabel->Create("String", SS_LEFT, CRect(0, 0, 60, 20), this);
	pStrLabel->SetWindowPos(NULL, 20, 110, 60, 20, SWP_SHOWWINDOW);

	// Add Integer Edit box
	pIntEdit = new CAcUiNumericEdit;
	pIntEdit->Create(ES_LEFT | WS_BORDER | ES_NUMBER, CRect(0, 0, 110, 20), this, ID_INT_EDIT);
	pIntEdit->SetWindowPos(NULL, 90, 160, 110, 20, SWP_SHOWWINDOW);

	// Add label to Integer Edit box
	pIntLabel = new CStatic;
	pIntLabel->Create("Integer", SS_LEFT, CRect(0, 0, 60, 20), this);
	pIntLabel->SetWindowPos(NULL, 20, 160, 60, 20, SWP_SHOWWINDOW);

	// Add Real Edit box
	pRealEdit = new CAcUiNumericEdit;
	pRealEdit->Create(ES_LEFT | WS_BORDER, CRect(0, 0, 110, 20), this, ID_REAL_EDIT);
	pRealEdit->SetWindowPos(NULL, 90, 210, 110, 20, SWP_SHOWWINDOW);

	// Add label to Real Edit box
	pRealLabel = new CStatic;
	pRealLabel->Create("Real", SS_LEFT, CRect(0, 0, 60, 20), this);
	pRealLabel->SetWindowPos(NULL, 20, 210, 60, 20, SWP_SHOWWINDOW);

	//And an ActiveX control
	//and set an image to the control
	CAcModuleResourceOverride temp;
	bitmap.LoadBitmap(IDB_BITMAP1);
	pictholder.CreateFromBitmap(&bitmap);

	BOOL bRet = mClipCtrl.Create("PicClip.PictureClip.1", WS_CHILD | WS_VISIBLE, CRect(0, 0, 142 , 107), this, 1);
	mClipCtrl.SetWindowPos(NULL, 50, 300, 142, 107, SWP_SHOWWINDOW);
	mClipCtrl.SetPicture(pictholder.GetPictureDispatch());
	mClipCtrl.ShowWindow(SW_NORMAL);
}

// Delete all controls
void CMyPalette::deleteControls()
{
	// Controls in the palette
	delete pCombo;
	delete pStringEdit;
	delete pIntEdit;
	delete pRealEdit;
	// Static texts
	delete pTextLabel;
	delete pDataLabel;
	delete pStrLabel;
	delete pIntLabel;
	delete pRealLabel;
}

//Called by AutoCAD to steal focus from the palette
bool CMyPalette::CanFrameworkTakeFocus()
{
	// not simply calling IsFloating() (a BOOL) avoids warning C4800
	return ( GetPaletteSet()->IsFloating() == TRUE ? true : false );
}