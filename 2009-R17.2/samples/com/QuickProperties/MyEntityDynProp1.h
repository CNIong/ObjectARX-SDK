// (C) Copyright 2002-2008 by Autodesk, Inc. 
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
//////////////////////////////////////////////////////////////////////////
// MyEntityDynProp1.h : Declaration of the CMyEntityDynProp1
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////

#include "resource.h"
#include "QuickProperties.h"

//////////////////////////////////////////////////////////////////////////
// CMyEntityDynProp1
class ATL_NO_VTABLE CMyEntityDynProp1 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMyEntityDynProp1, &CLSID_MyEntityDynProp1>,
	public ISupportErrorInfo,
	public IDispatchImpl<IMyEntityDynProp1, &IID_IMyEntityDynProp1, &LIBID_adskQuickPropertiesLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
  public ICategorizeProperties,
	public IDynamicProperty2,
  // IFilterableProperty  allows control of which properties appear in the CUI QuickProps pane - this is implemented for demo purposes only
  // we won't use it because the display is really handled by the CMyPerInstancePropFactory and the IFilterableSubtypePropertySource
  public IFilterableProperty  
{
public:
	CMyEntityDynProp1 () {
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_MYENTITYDYNPROP1)

	BEGIN_COM_MAP(CMyEntityDynProp1)
		COM_INTERFACE_ENTRY(IMyEntityDynProp1)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ICategorizeProperties)
		COM_INTERFACE_ENTRY(IDynamicProperty2)
    COM_INTERFACE_ENTRY(IFilterableProperty)
	END_COM_MAP()

	//  ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct () {
		return (S_OK) ;
	}
	
	void FinalRelease () {
	}

	IDynamicPropertyNotify2 *m_pNotify ;

public:
	//IDynamicProperty2
	STDMETHOD(GetGUID)(GUID* propGUID) ;
	STDMETHOD(GetDisplayName)(BSTR* bstrName) ;
	STDMETHOD(IsPropertyEnabled)(IUnknown *pUnk, BOOL* pbEnabled) ;
	STDMETHOD(IsPropertyReadOnly)(BOOL* pbReadonly) ;
	STDMETHOD(GetDescription)(BSTR* bstrName) ;
	STDMETHOD(GetCurrentValueName)(BSTR* pbstrName) ;
	STDMETHOD(GetCurrentValueType)(VARTYPE* pVarType) ;
	STDMETHOD(GetCurrentValueData)(IUnknown *pUnk, VARIANT* pvarData) ;
	STDMETHOD(SetCurrentValueData)(IUnknown *pUnk, const VARIANT varData) ;
	STDMETHOD(Connect)(IDynamicPropertyNotify2* pSink) ;
	STDMETHOD(Disconnect)() ;
	//ICategorizePropery
	STDMETHOD(MapPropertyToCategory)(DISPID dispid, PROPCAT* ppropcat) ;
	STDMETHOD(GetCategoryName)(PROPCAT propcat, LCID lcid, BSTR* pbstrName) ;
	//IMyEntityDynProp1

  // IFilterableProperty
  // allows control of which properties appear in the CUI QuickProps pane
  STDMETHOD(ShowFilterableProperty)(/*[in]*/DISPID dispID, /*[in]*/AcFilterablePropertyContext context, /*[out, retval]*/BOOL* pbShow);
} ;

OBJECT_ENTRY_AUTO(__uuidof(MyEntityDynProp1), CMyEntityDynProp1)
//OPM_DYNPROP_OBJECT_ENTRY_AUTO(CMyEntityDynProp1, asdkMyEntity) // used for class property registration
