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

// DWGPreview.h : Declaration of the CDWGPreview
#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>
#include "CustPalette.h"

//////////////////////////////////////////////////////////////////////////
// Event notification
//////////////////////////////////////////////////////////////////////////

template <class T>
class CProxyIAcPiPropertyEditEventsSink : public IConnectionPointImpl<T, &IID_IAcPiPropertyEditEventsSink, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_Clicked()
	{
		HRESULT hr = S_OK;
		CComDynamicUnkArray connections;
		CopySinkArray(connections);
		int nConnectionIndex;
		int nConnections = connections.GetSize();

		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			CComQIPtr<IAcPiPropertyEditEventsSink, &IID_IAcPiPropertyEditEventsSink> sp =
				connections.GetAt(nConnectionIndex);
			if (sp)
				hr = sp->OnClick();
		}
		return hr;
	}

	HRESULT Fire_DblClicked()
	{
		HRESULT hr = S_OK;
		CComDynamicUnkArray connections;
		CopySinkArray(connections);
		int nConnectionIndex;
		int nConnections = connections.GetSize();

		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			CComQIPtr<IAcPiPropertyEditEventsSink, &IID_IAcPiPropertyEditEventsSink> sp = 
				connections.GetAt(nConnectionIndex);
			if (sp)
				hr = sp->OnDblClick();
		}
		return hr;
	}

	HRESULT Fire_KeyDown(long nChar, long nKeyData)
	{
		HRESULT hr = S_OK;
		CComDynamicUnkArray connections;
		CopySinkArray(connections);
		int nConnectionIndex;
		int nConnections = connections.GetSize();

		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			CComQIPtr<IAcPiPropertyEditEventsSink, &IID_IAcPiPropertyEditEventsSink> sp = 
				connections.GetAt(nConnectionIndex);
			if (sp)
				hr = sp->OnKeyDown(nChar, nKeyData);
		}
		return hr;

	}

	HRESULT Fire_RButtonDown(WPARAM wParam, LPARAM lParam)
	{
		HRESULT hr = S_OK;
		CComDynamicUnkArray connections;
		CopySinkArray(connections);
		int nConnectionIndex;
		int nConnections = connections.GetSize();

		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			CComQIPtr<IAcPiPropertyEditEventsSink, &IID_IAcPiPropertyEditEventsSink> sp = 
				connections.GetAt(nConnectionIndex);
			if (sp)
				hr = sp->OnRButtonDown(wParam, lParam);
		}
		return hr;
	}

	HRESULT Fire_MButtonDown(WPARAM wParam, LPARAM lParam)
	{
		HRESULT hr = S_OK;
		CComDynamicUnkArray connections;
		CopySinkArray(connections);
		int nConnectionIndex;
		int nConnections = connections.GetSize();

		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			CComQIPtr<IAcPiPropertyEditEventsSink, &IID_IAcPiPropertyEditEventsSink> sp = 
				connections.GetAt(nConnectionIndex);
			if (sp)
				hr = sp->OnMButtonDown(wParam, lParam);
		}
		return hr;
	}

	HRESULT Fire_KeyUp(long nChar, long nKeyData)
	{
		HRESULT hr = S_OK;
		CComDynamicUnkArray connections;
		CopySinkArray(connections);
		int nConnectionIndex;
		int nConnections = connections.GetSize();

		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			CComQIPtr<IAcPiPropertyEditEventsSink, &IID_IAcPiPropertyEditEventsSink> sp = 
				connections.GetAt(nConnectionIndex);
			if (sp)
				hr = sp->OnKeyDown(nChar, nKeyData);
		}
		return hr;
	}

	HRESULT Fire_BeginPropertyUpdate()
	{
		HRESULT hr = S_OK;
		CComDynamicUnkArray connections;
		CopySinkArray(connections);
		int nConnectionIndex;
		int nConnections = connections.GetSize();

		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			CComQIPtr<IPropEditUIEventsSink, &IID_IPropEditUIEventsSink> sp = 
				connections.GetAt(nConnectionIndex);
			if (sp)
				hr = sp->OnBeginPropertyUpdate();
		}
		return hr;
	}

	HRESULT Fire_EndPropertyUpdate()
	{
		HRESULT hr = S_OK;
		CComDynamicUnkArray connections;
		CopySinkArray(connections);
		int nConnectionIndex;
		int nConnections = connections.GetSize();

		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			CComQIPtr<IAcPiPropertyEditEventsSink, &IID_IAcPiPropertyEditEventsSink> sp = 
				connections.GetAt(nConnectionIndex);
			if (sp)
				hr = sp->OnEndPropertyUpdate();
		}
		return hr;
	}

protected:
	void CopySinkArray(CComDynamicUnkArray& pCopy)
	{
		pCopy.clear();
		IUnknown** pp = NULL;
		T* pT = static_cast<T*>(this);

		pT->Lock();
		for (pp = m_vec.begin(); pp < m_vec.end(); pp++)
		{
			if (*pp == NULL)
				continue;
			pCopy.Add(*pp);
		}
		pT->Unlock();
	}
};
//////////////////////////////////////////////////////////////////////////

template <class T>
class ATL_NO_VTABLE CProxyIPropertyNotifySink : public IConnectionPointImpl<T, &IID_IPropertyNotifySink, CComDynamicUnkArray>
{
public:

	HRESULT Fire_OnChanged(LONG dispID)
	{
		HRESULT ret = S_OK;
		CComDynamicUnkArray connections;
		CopySinkArray(connections);
		int nConnectionIndex;
		int nConnections = connections.GetSize();

		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			CComPtr<IUnknown> sp = connections.GetAt(nConnectionIndex);
			IPropertyNotifySink* pIPropertyNotifySink = reinterpret_cast<IPropertyNotifySink*>(sp.p);
			if (pIPropertyNotifySink != NULL)
				ret = pIPropertyNotifySink->OnChanged(dispID);
		}

		return ret;
	}

	HRESULT Fire_OnRequestEdit(LONG dispID)
	{
		HRESULT ret = S_OK;
		CComDynamicUnkArray connections;
		CopySinkArray(connections);
		int nConnectionIndex;
		int nConnections = connections.GetSize();

		for (nConnectionIndex = 0; nConnectionIndex < nConnections && SUCCEEDED(ret); nConnectionIndex++)
		{
			CComPtr<IUnknown> sp = connections.GetAt(nConnectionIndex);
			IPropertyNotifySink* pIPropertyNotifySink = reinterpret_cast<IPropertyNotifySink*>(sp.p);
			if (pIPropertyNotifySink != NULL)
				ret = pIPropertyNotifySink->OnRequestEdit(dispID);
		}

		return ret;
	}

protected:
	void CopySinkArray(CComDynamicUnkArray& pCopy)
	{
		pCopy.clear();
		IUnknown** pp = NULL;
		T* pT = static_cast<T*>(this);

		pT->Lock();
		for (pp = m_vec.begin(); pp < m_vec.end(); pp++)
		{
			if (*pp == NULL)
				continue;
			pCopy.Add(*pp);
		}
		pT->Unlock();
	}
};
//////////////////////////////////////////////////////////////////////////
// CDWGPreview
// Defines the PEX control for showing DWG thumbnail in the property inspector

class ATL_NO_VTABLE CDWGPreview : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IPersistStreamInitImpl<CDWGPreview>,
	public IOleControlImpl<CDWGPreview>,
	public IOleObjectImpl<CDWGPreview>,
	public IOleInPlaceActiveObjectImpl<CDWGPreview>,
	public IViewObjectExImpl<CDWGPreview>,
	public IOleInPlaceObjectWindowlessImpl<CDWGPreview>,
	public ISupportErrorInfo,
	public IPersistStorageImpl<CDWGPreview>,
	public ISpecifyPropertyPagesImpl<CDWGPreview>,
	public IQuickActivateImpl<CDWGPreview>,
	public IDataObjectImpl<CDWGPreview>,
	public IProvideClassInfo2Impl<&CLSID_DWGPreview, NULL, &LIBID_AsdkCustPaletteLib>,
	public CComCoClass<CDWGPreview, &CLSID_DWGPreview>,
	public CComControl<CDWGPreview>,
	public IConnectionPointContainerImpl<CDWGPreview>,
	public CProxyIAcPiPropertyEditEventsSink<CDWGPreview>,
	public CProxyIPropertyNotifySink<CDWGPreview>,
	public IDispatchImpl<IAcPiPropertyEditControl, &IID_IDWGPreview, &LIBID_AsdkCustPaletteLib>,
	public IDWGPreview
{
public:

	CDWGPreview()
	{
	}

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE | 
	OLEMISC_CANTLINKINSIDE | 
	OLEMISC_INSIDEOUT | 
	OLEMISC_ACTIVATEWHENVISIBLE | 
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_DWGPREVIEW)

BEGIN_COM_MAP(CDWGPreview)
	COM_INTERFACE_ENTRY(IDWGPreview)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IAcPiPropertyEditControl)
END_COM_MAP()

BEGIN_PROP_MAP(CDWGPreview)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
END_PROP_MAP()


BEGIN_MSG_MAP(CDWGPreview)
	CHAIN_MSG_MAP(CComControl<CDWGPreview>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IDWGPreview,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

	// Connection points
	BEGIN_CONNECTION_POINT_MAP(CDWGPreview)
		CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
		CONNECTION_POINT_ENTRY(IID_IAcPiPropertyEditEventsSink)
	END_CONNECTION_POINT_MAP()

// IDWGPreview
public:
		// Called when the control is drawn
		HRESULT OnDraw(ATL_DRAWINFO& di)
		{
			HRESULT hr = S_OK;
			RECT& rc = *(RECT*)di.prcBounds;
			// Set Clip region to the rectangle specified by di.prcBounds
			HRGN hRgnOld = NULL;
			if (GetClipRgn(di.hdcDraw, hRgnOld) != 1)
				hRgnOld = NULL;
			bool bSelectOldRgn = false;

			HRGN hRgnNew = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);

			if (hRgnNew != NULL)
			{
				bSelectOldRgn = (SelectClipRgn(di.hdcDraw, hRgnNew) != ERROR);
			}
			Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

			// Fill with white color
			COLORREF white = RGB(255,255,255);


			HBRUSH hBrush = CreateSolidBrush (RGB (255, 255, 255)); 
			FillRgn (di.hdcDraw, hRgnNew, hBrush);
			DeleteObject (hBrush);

			// Here is where the preview bitmap is drawn
			_bstr_t file(m_fileName);
			if(!acdbDisplayPreviewFromDwg(file, ::WindowFromDC(di.hdcDraw)))
			{
				// Write error messaget	
				SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
				LPCTSTR pszText = _T("Error getting dwg preview!");
				TextOut(di.hdcDraw, 
					(rc.left + rc.right) / 2, 
					(rc.top + rc.bottom) / 2, 
					pszText, 
					lstrlen(pszText));
				hr =  E_FAIL;
			} 

			if (bSelectOldRgn)
				SelectClipRgn(di.hdcDraw, hRgnOld);

			return hr;
	}


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		// To indicate the control is windowed
		m_bWindowOnly = true;
		return S_OK;
	}
	
	void FinalRelease() 
	{
		// Delete the allocated string
		::SysFreeString(m_fileName);

		// Release all dispatch pointers
		if (m_ppDisp) {
			for (int i = 0; i < m_numDisp; i++) {
				if (m_ppDisp[i] != NULL)
					m_ppDisp[i]->Release();        
			}
			delete [] m_ppDisp;
		}
	}

	//IAcPiPropertyEditControl
	STDMETHOD(InitEditControl)(LPVARIANT pVarObjDispArray,LPVARIANT pVarDynPropArray,LPVARIANT pDispidArray, VARIANT_BOOL bReadOnly);
	STDMETHOD(Refresh)(DWORD dwFlags);
	STDMETHOD(get_KeepFocus)(VARIANT_BOOL *bKeepFocus); // get_KeepFocus
	STDMETHOD(get_ForeColor)(OLE_COLOR *pClr); // get_ForeColor
	STDMETHOD(put_ForeColor)(OLE_COLOR pClr);  // put_ForeColor
	STDMETHOD(get_BackColor)(OLE_COLOR *pClr);  // get_BackColor
	STDMETHOD(put_BackColor)(OLE_COLOR pClr);  // put_ForeColor
	STDMETHOD(get_ReadOnlyForeColor)(OLE_COLOR *pClr);  // get_ReadOnlyForeColor
	STDMETHOD(put_ReadOnlyForeColor)(OLE_COLOR pClr);  // put_ReadOnlyForeColor
	STDMETHOD(get_ReadOnlyBackColor)(OLE_COLOR *pClr);  // get_ReadOnlyBackColor
	STDMETHOD(put_ReadOnlyBackColor)(OLE_COLOR pClr);  // put_ReadOnlyBackColor
	STDMETHOD(get_Font)(IUnknown **pIFont);  // get_Font
	STDMETHOD(put_Font)(IUnknown *pIFont);  // put_Font

	//IDWGPreview

	// Method to get the file name 
	STDMETHOD(GetFileName)(BSTR *fileName);
	// Reset - helper to reset file name
	STDMETHOD(resetFileName)();

private:
	// Store a local copy of the path to the DWG file
	// The path is obtained from the COM Wrapper (CInspData object)
	BSTR m_fileName;  
	// Array of IDispatchs to COM wrapper (CInspData object)
	// which provide the DWG file name for this control
	// In this sample, the array represents a single instance of CInspData object
	IDispatch   **m_ppDisp;
	// num of dispatch pointers
	int m_numDisp;


};

OBJECT_ENTRY_AUTO(__uuidof(DWGPreview), CDWGPreview)
