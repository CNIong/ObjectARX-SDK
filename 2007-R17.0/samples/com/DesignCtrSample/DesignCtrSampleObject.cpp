//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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
// DesignCtrSampleObject.cpp : Implementation of CDesignCtrSampleObject
#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <rxmfcapi.h>
#include "DesignCtrSample.h"
#include "DesignCtrSampleObject.h"



extern HINSTANCE _hdllInstance;

/////////////////////////////////////////////////////////////////////////////
// CDesignCtrSampleObject

STDMETHODIMP CDesignCtrSampleObject::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = { &IID_IDesignCtrSampleObject, };
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
/////////////////////////////////////////////////////////////////////////////
HRESULT CDesignCtrSampleObject::OnDraw(ATL_DRAWINFO& di)
{
    return S_OK;
}

HRESULT CDesignCtrSampleObject::FinalRelease()
{
    return S_OK;
}
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CDesignCtrSampleObject::Initialize(VARIANT varBrowser, VARIANT varReserved)
{
	return S_OK; 
}

STDMETHODIMP CDesignCtrSampleObject::SetImageLists()
{
	return S_OK;
}

STDMETHODIMP CDesignCtrSampleObject::NavigatorNodeExpanding(
			VARIANT varhNode,
			BSTR bstrFullPath)
{
	return S_OK;
}

STDMETHODIMP CDesignCtrSampleObject::NavigatorNodeCollapsing(
			VARIANT varhNode,
			BSTR bstrFullPath)
{
	return S_OK;
}

STDMETHODIMP CDesignCtrSampleObject::NavigatorNodeClick(
			VARIANT varhNode,
			BSTR bstrFullPath)
{
	return S_OK;
}

STDMETHODIMP CDesignCtrSampleObject::NavigatorMouseUp(
			VARIANT varhNode,
			BSTR bstrFullPath,
			VARIANT varX, 
			VARIANT varY)
{
	return S_OK;
}

STDMETHODIMP CDesignCtrSampleObject::PaletteItemClick(BSTR bstrItemText)
{
	USES_CONVERSION;
	m_strSelectedItemText = OLE2T(bstrItemText);
	ASSERT(m_strSelectedItemText.IsEmpty() == FALSE);
	if(m_strSelectedItemText.Right(4).CompareNoCase(_T(".dwf")) == 0)
		createWhipWndAndShowContent();

	return S_OK;
}

void CDesignCtrSampleObject::createWhipWndAndShowContent()
{
	destroyWhipWnd();

	CRect rect;  
	acedGetAcadFrame()->GetClientRect(&rect);
	
	AfxSetResourceHandle(_hdllInstance);
	m_pWhipWnd = new CWhipMdiChildWnd;
	m_pWhipWnd->SetDwfFileName(m_strSelectedItemText);
	if (!m_pWhipWnd->Create(NULL, _T("View DWF File"),
			WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_MAXIMIZE, 
			rect, acedGetAcadFrame(), NULL))
		return;
	AfxSetResourceHandle(acedGetAcadResourceInstance());

	m_pWhipWnd->MDIMaximize();
}

void CDesignCtrSampleObject::destroyWhipWnd()
{
	if(m_pWhipWnd && ::IsWindow(m_pWhipWnd->m_hWnd))
		m_pWhipWnd->DestroyWindow();
}

STDMETHODIMP CDesignCtrSampleObject::PaletteItemDblClick(BSTR bstrItemText)
{
	USES_CONVERSION;
	m_strSelectedItemText = OLE2T(bstrItemText);
	ASSERT(m_strSelectedItemText.IsEmpty() == FALSE);
	if(m_strSelectedItemText.Right(4).CompareNoCase(_T(".dwf")) == 0)
		createWhipWndAndShowContent();

	return S_OK;
}

STDMETHODIMP CDesignCtrSampleObject::PaletteColumnClick(
			VARIANT varIndex)
{
	return S_OK;
}

STDMETHODIMP CDesignCtrSampleObject::PaletteMouseUp(
			VARIANT varButton,
			VARIANT varItemTexts,
			VARIANT varX, 
			VARIANT varY)
{
	return S_OK;
}

STDMETHODIMP CDesignCtrSampleObject::PaletteMouseDown(
			VARIANT varButton,
			BSTR bstrFullText, 
			VARIANT varX, VARIANT varY)
{
	return S_OK;
}

STDMETHODIMP CDesignCtrSampleObject::RenderPreviewWindow(
			BSTR bstrFullText,
			VARIANT varhPreviewWindow)
{
	return S_OK;
}

STDMETHODIMP CDesignCtrSampleObject::PreviewMouseUp(
			VARIANT varButton, 
			VARIANT varX,
			VARIANT varY)
{
	return S_OK;
}

STDMETHODIMP CDesignCtrSampleObject::Refresh()
{
	return S_OK;
}

STDMETHODIMP CDesignCtrSampleObject::PaletteBeginDrag(
			VARIANT varItemTexts,
			VARIANT varX, 
			VARIANT varY)
{
	return S_OK;
}

STDMETHODIMP CDesignCtrSampleObject::ReleaseBrowser()
{
	return S_OK;
}

STDMETHODIMP CDesignCtrSampleObject::QueryContextMenu(
			VARIANT varhMenu,
			VARIANT varIndex,
			VARIANT varCmdFirst,
			VARIANT varCmdLast,
			VARIANT varItemTexts)
{
	return S_OK;
}

STDMETHODIMP CDesignCtrSampleObject::InvokeCommand(VARIANT varMenuID)
{
	return S_OK;
}

STDMETHODIMP 
CDesignCtrSampleObject::IsExpandable(/* [string][in] */ BSTR bstrItemText,
							/* [retval][out] */ VARIANT __RPC_FAR *pvarIsExpandable)
{
	return E_NOTIMPL;
}
    
STDMETHODIMP 
CDesignCtrSampleObject::GetLargeImage(/* [in] */ BSTR bstrFileName,
									  /* [out][in] */ VARIANT __RPC_FAR *pvarhLargeImage)
{
	return E_NOTIMPL;
}

STDMETHODIMP
CDesignCtrSampleObject::GetSmallImageListForContent(BSTR bstrFileName,
													VARIANT *pvarhImageList)
{
    return E_NOTIMPL;
} 

STDMETHODIMP
CDesignCtrSampleObject::GetLargeImageListForContent(BSTR bstrFileName,
													VARIANT *pvarhImageList)
{
    return E_NOTIMPL;
} 

STDMETHODIMP 
CDesignCtrSampleObject::GetCommandString(VARIANT varMenuID,
										 dcMenuInfoFlag, 
										 VARIANT *pvarReserved,   
										 BSTR *pbstrName)
{
    return E_NOTIMPL;
}

STDMETHODIMP
CDesignCtrSampleObject::DeleteItemData(dcItemDataSource dcSrc, VARIANT varItemDataArray)
{
    return E_NOTIMPL;
} // CDesignCtrSampleObject::DeleteItemData 

