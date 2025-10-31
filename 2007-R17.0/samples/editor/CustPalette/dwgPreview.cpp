// (C) Copyright 2005-2006 by Autodesk, Inc. 
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

// DWGPreview.cpp : Implementation of CDWGPreview
#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "acpi.h"
#include "DWGPreview.h"




// CDWGPreview

//IAcPiPropertyEditControl
HRESULT CDWGPreview::InitEditControl(LPVARIANT pVarObjDispArray,LPVARIANT pVarDynPropArray,LPVARIANT pDispidArray, VARIANT_BOOL bReadOnly)
{
	// Cache the disp pointer
	ModifyStyle(WS_VISIBLE | WS_TABSTOP, 0); 
	long ub, lb;
	SafeArrayGetUBound(pVarObjDispArray->parray, 1, &ub);
	SafeArrayGetLBound(pVarObjDispArray->parray, 1, &lb);
	m_ppDisp = new IDispatch*[ub+1];
	CComPtr<IDispatch> pDisp = NULL;
	m_numDisp = ub + 1;
	for (int i = lb; i <= ub; i++) 
	{
		pDisp = NULL;		
		SafeArrayGetElement(pVarObjDispArray->parray, (LONG*)&i, reinterpret_cast <IDispatch *>(&pDisp));
		m_ppDisp[i] = pDisp;
		if(pDisp != NULL) {
			m_ppDisp[i]->AddRef();
		}
	}

	resetFileName();
	return S_OK;
}

HRESULT CDWGPreview::Refresh(DWORD dwFlags)
{
	resetFileName();
	return S_OK;
}

// get_KeepFocus
// Called to determine if the control is willing to lose focus. Simply call 
// the CanStealFocus() helper method.
HRESULT CDWGPreview::get_KeepFocus(VARIANT_BOOL *bKeepFocus)
{
	return E_NOTIMPL;
}

// get_ForeColor
HRESULT CDWGPreview::get_ForeColor(OLE_COLOR *pClr)
{
	return E_NOTIMPL;
}

// put_ForeColor
HRESULT CDWGPreview::put_ForeColor(OLE_COLOR pClr)
{
	return E_NOTIMPL;
}

// get_BackColor
HRESULT CDWGPreview::get_BackColor(OLE_COLOR *pClr)
{
	return E_NOTIMPL;
}

// put_ForeColor
HRESULT CDWGPreview::put_BackColor(OLE_COLOR pClr)
{
	return E_NOTIMPL;
}

// get_ReadOnlyForeColor
HRESULT CDWGPreview::get_ReadOnlyForeColor(OLE_COLOR *pClr)
{
	return E_NOTIMPL;
}

// put_ReadOnlyForeColor
HRESULT CDWGPreview::put_ReadOnlyForeColor(OLE_COLOR pClr)
{
	return E_NOTIMPL;
}

// get_ReadOnlyBackColor
HRESULT CDWGPreview::get_ReadOnlyBackColor(OLE_COLOR *pClr)
{
	return E_NOTIMPL;
}

// put_ReadOnlyBackColor
HRESULT CDWGPreview::put_ReadOnlyBackColor(OLE_COLOR pClr)
{
	return E_NOTIMPL;
}

// get_Font
HRESULT CDWGPreview::get_Font(IUnknown **pIFont)
{
	return E_NOTIMPL;
}

// put_Font
HRESULT CDWGPreview::put_Font(IUnknown *pIFont)
{
	return E_NOTIMPL;
}


// IDWGPreview

STDMETHODIMP CDWGPreview::GetFileName(BSTR *fileName)
{
	//  Do nothing
	return S_OK;
}

STDMETHODIMP CDWGPreview::resetFileName()
{
	CComPtr<IDispatch> pDisp;
	pDisp = m_ppDisp[0];
	CComQIPtr<IDWGPreview> pObj(pDisp);
	if(pObj)
	{
		BSTR fileName;
		pObj->GetFileName(&fileName);
		m_fileName = _bstr_t(fileName).copy();
		::SysFreeString(fileName);
	}
	return S_OK;
}