//
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

#include "PaletteSet.h"
#include "resource.h"
#include "palette.h"



// The file name of the persisted paletteset
#define PALETTESET_FILENAME _T("TestPaletteSet.xml")

//-----------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//Utility functions to add and get the child node from the parent XML-DOM node
extern BOOL GetChildNode(MSXML::IXMLDOMNode* pNode, 
						 LPCTSTR pszNodeName, 
						 MSXML::IXMLDOMNode** ppChild);

extern BOOL AddChildNode(MSXML::IXMLDOMNode* pNode, LPCTSTR pszChildNodeName,
						 short nNodeType, MSXML::IXMLDOMNode** ppChild);

//-----------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(CMyPaletteSet, CAdUiPaletteSet)

BEGIN_MESSAGE_MAP(CMyPaletteSet, CAdUiPaletteSet)
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------

CMyPaletteSet::CMyPaletteSet()
{
	
}

// Called by the palette set framework to determine size constraints.
// Override these methods to provide minimum and maximum palette set sizes.
void CMyPaletteSet::GetMinimumSize(CSize& size)
{
	size.cx = 300;
	size.cy = 400;
}

void CMyPaletteSet::GetMaximumSize(CSize& size)
{
	size.cx = 400;
	size.cy = 400;
}

BOOL CMyPaletteSet::PreTranslateMessage(MSG *pMsg)
{
	if (pMsg->message == WM_CHAR || pMsg->message == WM_SYSCHAR )
		return CWnd::PreTranslateMessage(pMsg);
	else 
		return CAdUiPaletteSet::PreTranslateMessage(pMsg);
}

int CMyPaletteSet::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CAdUiPaletteSet::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

void CMyPaletteSet::OnDestroy()
{
	// Save PaletteSet data
	SavePaletteSet();
	CAdUiPaletteSet::OnDestroy();
}


void CMyPaletteSet::LoadPaletteSet()
{
	MSXML::IXMLDOMDocumentPtr pDoc = NULL;
	HRESULT hr = pDoc.CreateInstance(CLSID_DOMDocumentAcad);

	// Get the file where the palette set's properties are saved
	const TCHAR *pRoam;
	TCHAR paletteBuffer[MAX_PATH];
	BOOL bResult=acdbHostApplicationServices()->getRoamableRootFolder(pRoam);
	_tcscpy(paletteBuffer, pRoam);
	_tcscat(paletteBuffer, PALETTESET_FILENAME);
	CComVariant var(paletteBuffer);

	VARIANT_BOOL bReturn = pDoc->load(var);
	if (bReturn == VARIANT_TRUE) // success!
	{
		MSXML::IXMLDOMNodePtr pNode;
		GetChildNode(pDoc->documentElement,_T("PS"),&pNode);

		// Call the base class version of Load.
		// This would re-establish the properties of
		// the palette set
		Load(pNode);
	}
}

void CMyPaletteSet::SavePaletteSet()
{
	// Persist the palette set data in TestPaletteSet.xml
	MSXML::IXMLDOMDocumentPtr pDoc = NULL;
	HRESULT hr = pDoc.CreateInstance(CLSID_DOMDocumentAcad);

	// Save pallete set into roaming profile
	const TCHAR *pRoam;
	TCHAR paletteBuffer[MAX_PATH];
	BOOL bResult=acdbHostApplicationServices()->getRoamableRootFolder(pRoam);
	_tcscpy(paletteBuffer, pRoam);
	_tcscat(paletteBuffer, PALETTESET_FILENAME);
	CComVariant var(paletteBuffer);

	// create a root element
	MSXML::IXMLDOMNodePtr pNode;

	if (AddChildNode(pDoc, _T("PS"), MSXML::NODE_ELEMENT, &pNode) == FALSE)
		return;

	// This calls the base class implementation of Save 
	// The base class adds its properties (as XML nodes) into pNode
	Save(pNode);

	// Save the xml document
	hr = pDoc->save(var);
}