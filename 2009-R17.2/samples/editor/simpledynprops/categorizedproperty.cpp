//
// (C) Copyright 1998-2007 by Autodesk, Inc. 
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
// CategorizedProperty.cpp : Implementation of CCategorizedProperty
#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "SimpleDynProps.h"
#include "CategorizedProperty.h"
#include "xrecordmanager.h"


/////////////////////////////////////////////////////////////////////////////
// CCategorizedProperty

CCategorizedProperty::CCategorizedProperty():
    m_propCat(1),
    m_bstrPropCatName(L"My Category")
{
    m_bstrDisplayName = L"CategorizedProperty";
    m_bstrDescription = L"Description of CategorizedProperty";
    m_valueType = VT_R8;

}
 //Provide a category ID for the property, provide your own or see standards
//You can ignore the incoming dispid. It's for internal use only
STDMETHODIMP CCategorizedProperty::MapPropertyToCategory( 
                                 /* [in]  */ DISPID dispid,
                                 /* [out] */ PROPCAT* pPropCat) 
{
    if (pPropCat==NULL)
        return E_POINTER;
    *pPropCat = m_propCat;
    return S_OK; 
}
// Get the name for the category ID
STDMETHODIMP CCategorizedProperty::GetCategoryName(
                           /* [in]  */ PROPCAT propcat, 
                           /* [in]  */ LCID lcid,
                           /* [out] */ BSTR* pBstrName) 
{
    if (pBstrName==NULL)
        return E_POINTER;
    if (propcat!=1)
        return E_FAIL;
    *pBstrName = ::SysAllocString(m_bstrPropCatName);
    return S_OK;
}

// Get the property value, passes the specific object we need the property
// value for.
STDMETHODIMP CCategorizedProperty::GetCurrentValueData( /*in*/LONG_PTR objectID, 
                                  /*[out]*/VARIANT* pVarData) 
{
    if (pVarData==NULL)
        return E_POINTER;
    AcDbObjectId id;
    id.setFromOldId(objectID);
    resbuf data;
    if (XRecordManager::getData(id,1,data)!=Acad::eOk)
        return E_FAIL;
    ::VariantCopy(pVarData,&_variant_t(data.resval.rreal));
    return S_OK; 
}
// Set the property value, passes the specific object we want to set the 
// property value for
STDMETHODIMP CCategorizedProperty::SetCurrentValueData( /*[in]*/LONG_PTR objectID, 
                                     /*[in]*/const VARIANT varData) 
{
    AcDbObjectId id;
    id.setFromOldId(objectID);
    resbuf data;
    data.restype = AcDb::kDxfReal;
    data.resval.rreal = V_R8(&varData);
    if (XRecordManager::setData(id,1,data)!=Acad::eOk)
        return E_FAIL;
    //if the dynamic property is changed by some other
    if (m_pNotifySink!=NULL)
        m_pNotifySink->OnChanged(this);
    return S_OK; 
}
