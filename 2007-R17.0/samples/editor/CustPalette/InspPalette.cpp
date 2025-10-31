// (C) Copyright 2000-2006 by Autodesk, Inc. 
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
//----- InspPalette.cpp : Implementation of CInspPalette
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "resource.h"
#include "acpi_i.c"
#include "InspPalette.h"



//////////////////////////////////////////////////////////////////////////////
// dialog resource for the inspector control
#define ID_INSPECTOR 1011

//////////////////////////////////////////////////////////////////////////////
// import the MSXML functionality
#import "msxml.dll" named_guids
using namespace MSXML;


CComObject<CInspData> *InspPaletteDataManager::pData = NULL;

//////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC (CInspPalette, CAdUiPalette)

BEGIN_MESSAGE_MAP(CInspPalette, CAdUiPalette)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SIZING()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////
CInspPalette::CInspPalette() : CAdUiPalette(), m_pInspWnd(NULL) 
{
}

//////////////////////////////////////////////////////////////////////////////
CInspPalette::~CInspPalette () 
{
	if(m_pInspWnd)
		delete m_pInspWnd;
}

//////////////////////////////////////////////////////////////////////////////
// Load the input data from xml.
BOOL CInspPalette::Load(IUnknown* pUnk) 
{	
	// Call base class first 
	CAdUiPalette::Load(pUnk);

	// initialise for XML
	CComQIPtr<MSXML::IXMLDOMNode> pNode(pUnk);
	MSXML::IXMLDOMNodePtr pChild, pChild1;

	// TODO: read in data from palette XML
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// Save the input data to xml.
BOOL CInspPalette::Save(IUnknown* pUnk) 
{
	// Call base class first 
	CAdUiPalette::Save(pUnk);

	// initialise for XML
	CComQIPtr<MSXML::IXMLDOMNode> pNode(pUnk);
	MSXML::IXMLDOMNodePtr pChild, pChild1;

	// TODO: save data to palette XML
	return TRUE;
}


int CInspPalette::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CAdUiPalette::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pInspWnd = new CWnd();
	CRect rect;
	GetWindowRect(&rect);
	rect.top += 20;
	rect.bottom -= 20;
	rect.right -= 20;

	// Create the inspector ActiveX control
	BOOL res = m_pInspWnd->CreateControl(CLSID_AcPiPropertyInspector, NULL, WS_CHILD|WS_TABSTOP|WS_VISIBLE,
		rect, this, ID_INSPECTOR);

	CComQIPtr<IAcPiPropertyInspector> pInsp = m_pInspWnd->GetControlUnknown();

	m_pInsp = pInsp;

	// Set the Palette's title
	SetName(_T("Inspector"));

	// Populate the property inspector with data
	Refresh();

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
// Called by the palette set when the palette is made active
void CInspPalette::OnSetActive() 
{
	return CAdUiPalette::OnSetActive();
}
//////////////////////////////////////////////////////////////////////////////
// Called by AutoCAD to steal focus from the palette
bool CInspPalette::CanFrameworkTakeFocus()
{
	// not simply calling IsFloating() (a BOOL) avoids warning C4800
	return ( GetPaletteSet()->IsFloating() == TRUE ? true : false );
}

//////////////////////////////////////////////////////////////////////////////
// Size the inspector to match the size of the palette
void CInspPalette::OnSize(UINT nType, int cx, int cy)
{
	CAdUiPalette::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(rect);

	m_pInspWnd->SetWindowPos(NULL, 10, 0,
		rect.right - rect.left - 20,
		rect.bottom - rect.top ,
		SWP_NOZORDER);

	m_pInspWnd->SetRedraw(TRUE);
	m_pInspWnd->Invalidate();
	m_pInspWnd->SetFocus();
}

void CInspPalette::Refresh()
{
	// Load the single instance of InspectorData into the property inspector.
	m_pData = InspPaletteDataManager::GetData();

	CComVariant objVarUnkArray, dynVarUnkArray;
	_variant_t pObjUnk(m_pData->GetUnknown());
	_variant_t pUnk;

	// Create a safe array of IUnknowns to object 
	SAFEARRAYBOUND rgsaBound[1]; 
	rgsaBound[0].lLbound = 0; 
	rgsaBound[0].cElements = 1; 
	SAFEARRAY* psaObj = SafeArrayCreate(VT_VARIANT, 1, rgsaBound); 

	long index = 0;
	SafeArrayPutElement( psaObj, &index, &pObjUnk );

	objVarUnkArray.vt = VT_ARRAY | VT_VARIANT;
	objVarUnkArray.parray = psaObj;

	// Create a safe array of  corresponding dynprop managers
	// In this case, there is no dynprop manager, so make a dummy array
	SAFEARRAY* psaDynPropMan = SafeArrayCreate(VT_VARIANT, 1, rgsaBound);

	// Add a dummy element
	SafeArrayPutElement(psaDynPropMan, &index, &pUnk);

	_variant_t dynVarPropManArray;
	dynVarPropManArray.vt = VT_ARRAY | VT_VARIANT;
	dynVarPropManArray.parray = psaDynPropMan;

	//  Create an array of IUnknowns to dynpropman array
	SAFEARRAY* psaDynpropUnk = SafeArrayCreate(VT_VARIANT, 1, rgsaBound);
	SafeArrayPutElement(psaDynpropUnk, &index, &dynVarPropManArray);

	dynVarUnkArray.vt = VT_ARRAY | VT_VARIANT;
	dynVarUnkArray.parray = psaDynpropUnk;

	// Load the object into the inspector control
	HRESULT hr = m_pInsp->Reset(&objVarUnkArray, &dynVarUnkArray, ACPI_CLEARCACHE_REFRESH);
}