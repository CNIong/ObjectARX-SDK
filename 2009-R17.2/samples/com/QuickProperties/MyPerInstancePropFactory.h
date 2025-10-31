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
// MyPerInstancePropFactory.h : 
// 
// IPropertySource implementation
// this class controls creating per-instance duynamic properties
//////////////////////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////////////////////

#include "resource.h"

//////////////////////////////////////////////////////////////////////////
// CMyPerInstancePropFactory
class ATL_NO_VTABLE CMyPerInstancePropFactory : 
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<CMyPerInstancePropFactory, &CLSID_MyPerInstancePropFactory>,
  public IMyPerInstancePropFactory,
  public IPropertySource,
  // we could have any one of these 3 interfaces, I'll implement the most difficult
  // IFilterablePropertySource
  // IFilterableMultiplePropertySource
  public IFilterableSubtypePropertySource
{
public:
  CMyPerInstancePropFactory (){
  }

  DECLARE_NOT_AGGREGATABLE(CMyPerInstancePropFactory)

  BEGIN_COM_MAP(CMyPerInstancePropFactory)
    COM_INTERFACE_ENTRY(IMyPerInstancePropFactory)
    COM_INTERFACE_ENTRY(IPropertySource)
    COM_INTERFACE_ENTRY(IFilterableSubtypePropertySource)
  END_COM_MAP()

  DECLARE_PROTECT_FINAL_CONSTRUCT()

  HRESULT FinalConstruct () {
    return (S_OK) ;
  }

  void FinalRelease () {
  }

public:
  //IPropertySource
  STDMETHOD(get_Name) (BSTR *pName) ;
  STDMETHOD(GetProperties) (IUnknown *pObject, VARIANT *pPropertyArray) ;

  //IMyPerInstancePropFactory

  // *** IFilterableSubtypePropertySource methods ***
  STDMETHOD(GetSubtypes)(VARIANT *pSubtypeGUIDsArray);
  STDMETHOD(GetSubtypeName)(BSTR bstrSubtypeGUID, BSTR* bstrSubtypeName);
  STDMETHOD(GetSubtypeProperties)(BSTR bstrSubtypeGUID, VARIANT *pPropertyArray);
  STDMETHOD(GetObjectSubtype)(IUnknown* pObject,  BSTR* bstrSubtypeGUID);
} ;

// OBJECT_ENTRY_AUTO(__uuidof(MyPerInstancePropFactory), CMyPerInstancePropFactory)
OPM_DYNPROP_PERINSTANCE_ENTRY_AUTO(CMyPerInstancePropFactory, asdkMyEntity)

