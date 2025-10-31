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
//////////////////////////////////////////////////////////////////////////
// MyPerInstancePropFactory.cpp
// 
// IPropertySource implementation
// this class controls creating per-instance duynamic properties
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "MyEntityWrapper.h"
#include "MyEntityDynProp1.h"
#include "MyEntityDynProp2.h"
#include "MyEntityDynProp3.h"
#include "MyPerInstancePropFactory.h"

//////////////////////////////////////////////////////////////////////////
// CMyPerInstancePropFactory
STDMETHODIMP CMyPerInstancePropFactory::get_Name (BSTR *pName) 
{
  if ( pName == NULL )
    return (E_POINTER) ;
  *pName =::SysAllocString (L"MyPerInstancePropFactory") ;
  return (S_OK) ;
}
//////////////////////////////////////////////////////////////////////////
// tell the Property palette what properties are available for this instance
STDMETHODIMP CMyPerInstancePropFactory::GetProperties (IUnknown *pObject, VARIANT *pPropertyArray) 
{
  // basic error checking
  if ( pPropertyArray == NULL )
    return (E_POINTER) ;
  if ( pObject == NULL )
    return (E_INVALIDARG) ;

  // 
  V_VT(pPropertyArray) =VT_ARRAY | VT_UNKNOWN ;
  CComSafeArray<IUnknown *> *psa =new CComSafeArray<IUnknown *>((ULONG)0, (LONG)0) ;
  V_ARRAY(pPropertyArray) = *psa;

  // now add the standard props
  {
    // instantiate My Integer Dyn prop
    CComObject<CMyEntityDynProp1> *pProp1 = NULL ;
    CComObject<CMyEntityDynProp1>::CreateInstance(&pProp1);
    pProp1->AddRef () ;
    IUnknown *pUnk =NULL ;
    pProp1->QueryInterface (IID_IUnknown, (void **)&pUnk);
    psa->Add (pUnk) ;
  }

  {
    // instantiate My Double Dyn prop
    CComObject<CMyEntityDynProp2> *pProp2 = NULL;
    CComObject<CMyEntityDynProp2>::CreateInstance(&pProp2);
    pProp2->AddRef ();
    IUnknown *pUnk =NULL ;
    pProp2->QueryInterface(IID_IUnknown, (void **)&pUnk);
    psa->Add (pUnk);
  }

  {
    // instantiate My String Dyn prop
    CComObject<CMyEntityDynProp3> *pProp3 = NULL;
    CComObject<CMyEntityDynProp3>::CreateInstance(&pProp3);
    pProp3->AddRef ();
    IUnknown *pUnk =NULL ;
    pProp3->QueryInterface(IID_IUnknown, (void **)&pUnk);
    psa->Add (pUnk);
  }

  return (S_OK) ;
}

//////////////////////////////////////////////////////////////////////////
// helper function for CMyPerInstancePropFactory::GetSubtypes below
void addStringToGUIDArray(COleSafeArray& arrayGUIDs, long& index, REFCLSID clsid)
{
  LPOLESTR pbstrGuid = NULL;
  StringFromCLSID(clsid, &pbstrGuid);
  CComBSTR guidStr(pbstrGuid);
  arrayGUIDs.PutElement(&index, guidStr.Detach());
  index++;
}
//////////////////////////////////////////////////////////////////////////
// The "GetSubtypes" method returns an array of BSTR items that identify
// each subtype defined by this interface implementation via the
// "pSubtypeGUIDsArray" output parameter.  Each BSTR is
// the string representation of a "subtype"s GUID.
STDMETHODIMP CMyPerInstancePropFactory::GetSubtypes (VARIANT *pSubtypeGUIDsArray)
{
  // check to see if it's valid
  if (pSubtypeGUIDsArray == NULL)
    return E_POINTER;

  long index = 0;
  COleSafeArray guidArray;
  guidArray.CreateOneDim(VT_BSTR, 3);
  addStringToGUIDArray(guidArray, index, GUID_MyEntityNormal);
  addStringToGUIDArray(guidArray, index, GUID_MyEntityWithText);
  addStringToGUIDArray(guidArray, index, GUID_MyEntityThicknessWithText);
  ASSERT(index == 3);
  *pSubtypeGUIDsArray = guidArray.Detach();

  return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// helper function for CMyPerInstancePropFactory::GetSubtypeName below
bool getNameIfGUIDsMatch(REFCLSID clsid, BSTR* pbstrSubtypeGUID, UINT nId, BSTR* bstrSubtypeName)
{
  LPOLESTR pbstrGuid = NULL;
  StringFromCLSID(clsid, &pbstrGuid);
  if (_tcscmp(OLE2T(*pbstrSubtypeGUID), OLE2T(pbstrGuid)) == 0) 
  {
    // switch the MFC resource pointer to my dll
    CAcModuleResourceOverride res;
    // now load the string
    CComBSTR nameStr;
    nameStr.LoadString(nId);
    *bstrSubtypeName = nameStr.Detach();
    return true;
  }

  return false;
}
//////////////////////////////////////////////////////////////////////////
// The "GetSubtypeName" returns the name of the "subtype" that's
// identified by the GUID BSTR passed in via the "bstrSubtypeGUID"
// parameter in a BSTR via the "bstrSubtypeName" output parameter.
STDMETHODIMP CMyPerInstancePropFactory::GetSubtypeName (BSTR bstrSubtypeGUID, BSTR* bstrSubtypeName)
{
  int passed = 0;
  // find the display name that matches the GUID passed
  passed += getNameIfGUIDsMatch(GUID_MyEntityNormal, &bstrSubtypeGUID, IDS_QUIK_NormalText, bstrSubtypeName);
  passed += getNameIfGUIDsMatch(GUID_MyEntityWithText, &bstrSubtypeGUID, IDS_QUIK_WithText, bstrSubtypeName);
  passed += getNameIfGUIDsMatch(GUID_MyEntityThicknessWithText, &bstrSubtypeGUID, IDS_QUIK_ThicknessWithText, bstrSubtypeName);

  if (passed)
    return S_OK;
  else
    return S_FALSE;
}

//////////////////////////////////////////////////////////////////////////
// helper functions for CMyPerInstancePropFactory::GetSubtypeProperties below
bool GUIDsMatch(REFCLSID clsid, BSTR* pbstrSubtypeGUID)
{
  LPOLESTR pbstrGuid = NULL;
  // convert the guid to the
  StringFromCLSID(clsid, &pbstrGuid);
  return (_tcscmp(OLE2T(*pbstrSubtypeGUID), OLE2T(pbstrGuid)) == 0);
}
//////////////////////////////////////////////////////////////////////////
// The "GetSubtypeProperties" method should create the dynamic
// properties for the given "subtype" whose GUID string is passed in via
// the "bstrSubtypeGUID" input parameter that should be included in
// the property filter customization user interface for the IPropertySource
// implementation that is implementing this interface.  As is the case for
// the IPropertySource::GetProperties" method that this method is modelled
// after, the properties are returned via the "pPropertyArray" output
// parameter.
STDMETHODIMP CMyPerInstancePropFactory::GetSubtypeProperties(BSTR bstrSubtypeGUID, VARIANT *pPropertyArray)
{
  // basic error checking
  if ( pPropertyArray == NULL )
    return (E_POINTER) ;

  // duplicate the code from CMyPerInstancePropFactory::GetProperties, but this time there should be no instance
  // specific rules because the CUI doesn't know about object instances
  V_VT(pPropertyArray) =VT_ARRAY | VT_UNKNOWN ;
  CComSafeArray<IUnknown *> *psa = new CComSafeArray<IUnknown *>((ULONG)0, (LONG)0) ;
  V_ARRAY(pPropertyArray) = *psa;

  // see which subtype we are on, basically, if it's any one of them then add the 2 standard properties
  if (GUIDsMatch(GUID_MyEntityNormal, &bstrSubtypeGUID) || 
      GUIDsMatch(GUID_MyEntityWithText, &bstrSubtypeGUID) ||
      GUIDsMatch(GUID_MyEntityThicknessWithText, &bstrSubtypeGUID))
  {
    {
      // instantiate My Integer Dyn prop
      CComObject<CMyEntityDynProp1> *pProp1 = NULL ;
      CComObject<CMyEntityDynProp1>::CreateInstance(&pProp1);
      pProp1->AddRef () ;
      IUnknown *pUnk =NULL ;
      pProp1->QueryInterface (IID_IUnknown, (void **)&pUnk);
      psa->Add (pUnk) ;
    }

    {
      // instantiate My Double Dyn prop
      CComObject<CMyEntityDynProp2> *pProp2 = NULL;
      CComObject<CMyEntityDynProp2>::CreateInstance(&pProp2);
      pProp2->AddRef ();
      IUnknown *pUnk =NULL ;
      pProp2->QueryInterface(IID_IUnknown, (void **)&pUnk);
      psa->Add (pUnk);
    }
  }

  // now check if we have a text option
  if (GUIDsMatch(GUID_MyEntityWithText, &bstrSubtypeGUID) ||
      GUIDsMatch(GUID_MyEntityThicknessWithText, &bstrSubtypeGUID)) 
  {
    // instantiate My String Dyn prop
    CComObject<CMyEntityDynProp3> *pProp3 = NULL;
    CComObject<CMyEntityDynProp3>::CreateInstance(&pProp3);
    pProp3->AddRef ();
    IUnknown *pUnk =NULL ;
    pProp3->QueryInterface(IID_IUnknown, (void **)&pUnk);
    psa->Add (pUnk);
  }

  return (S_OK) ;
}
//////////////////////////////////////////////////////////////////////////
// The "GetObjectSubtype" method is used to identify the "subtype" of the
// entity instance whose IUknown* is passed in via the "pObject" input
// parameter.  A BSTR representaion of the GUID of the subtype of the
// passed instance is returned via the "bstrSubtypeGUID" output parameter.
STDMETHODIMP CMyPerInstancePropFactory::GetObjectSubtype(IUnknown* pObject,  BSTR* bstrSubtypeGUID)
{
  // here's where we start to decide which dynamic properties appear when the property palette is being used
  CComQIPtr<IAcadBaseObject> pObj (pObject);
  CComQIPtr<IMyEntityWrapper> pMyEntity (pObj);
  // get the My Type
  LONG myType = 0;
  pMyEntity->get_MyType(&myType);

  switch(myType)
  {
    // normal 
    case 0: 
    {
      StringFromCLSID(GUID_MyEntityNormal, bstrSubtypeGUID); 
    }
    break;

    // with text
    case 1: 
    {
      StringFromCLSID(GUID_MyEntityWithText, bstrSubtypeGUID); 
    }
    break;

    // thickness with text
    case 2: 
    {
      StringFromCLSID(GUID_MyEntityThicknessWithText, bstrSubtypeGUID); 
    }
    break;

    default : return E_FAIL;
  }

  return S_OK;
}
