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

// InspData.h : Declaration of the CInspData

#pragma once
#include "resource.h"       // main symbols
#include "opmdialog.h"
#include "CustPalette.h"

// CInspData - Class to store data that will be shown by the property inspector
//			   as properties
// 
class ATL_NO_VTABLE CInspData : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CInspData, &CLSID_InspData>,
	public IDispatchImpl<IInspData, &IID_IInspData, &LIBID_AsdkCustPaletteLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IAcPiPropertyDisplayImpl<CInspData>,
	public IDWGPreview
{
public:
	CInspData()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_INSPDATA)

BEGIN_PERPROPDISPLAY_MAP()
	// Return the progId of our DWGPreview control to show it as  
	// a property in the property inspector
	PROP_DISP_ENTRY(0x00000002, _T("CustPalette.DWGPreview.1"), NULL, NULL, NULL, 
					NULL, RGB(255, 0, 0), TRUE, 20, 0)
END_PERPROPDISPLAY_MAP()

BEGIN_COM_MAP(CInspData)
	COM_INTERFACE_ENTRY(IInspData)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IAcPiPropertyDisplay)
	COM_INTERFACE_ENTRY(IDWGPreview)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

	// IAcPiPropertyDisplayImpl
	virtual HINSTANCE GetResourceInstance () { return _hdllInstance;  }
	// IDWGPreview
	STDMETHOD(GetFileName)(/* [in] */ BSTR *pFileName);

	STDMETHOD(get_FileName)(BSTR* pVal);
	STDMETHOD(put_FileName)(BSTR newVal);
	STDMETHOD(get_Preview)(BOOL *pv);
	STDMETHOD(put_Preview)(BOOL newVal);

};


OBJECT_ENTRY_AUTO(__uuidof(InspData), CInspData)
