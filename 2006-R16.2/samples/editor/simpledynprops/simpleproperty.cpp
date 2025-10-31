//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
// SimpleProperty.cpp : Implementation of CSimpleProperty
#include "stdafx.h"
#include "SimpleDynProps.h"
#include "SimpleProperty.h"
#include <comdef.h>
#include "xrecordmanager.h"

/////////////////////////////////////////////////////////////////////////////
// CSimpleProperty

CSimpleProperty::CSimpleProperty():
    m_bstrDisplayName(L"SimpleProperty"),
    m_bstrDescription(L"Description of SimpleProperty"),
    m_valueType(VT_R8)
{
    
}
//Unique property ID
STDMETHODIMP CSimpleProperty::GetGUID( /*[out]*/GUID* propGUID) 
{
    return E_NOTIMPL; 
}
// Property display name
STDMETHODIMP CSimpleProperty::GetDisplayName( /*[out]*/BSTR* pBstrName) 
{
    if (pBstrName==NULL)
        return E_POINTER;
    *pBstrName = ::SysAllocString(m_bstrDisplayName);
    return S_OK; 
}
// Show/Hide property in the OPM, for this object instance 
STDMETHODIMP CSimpleProperty::IsPropertyEnabled( /*[in]*/LONG objectID,
                                  /*[out]*/BOOL* pbEnabled) 
{
    if (pbEnabled==NULL)
        return E_POINTER;
    AcDbObjectId id;
    id.setFromOldId(objectID);
    *pbEnabled = XRecordManager::isDataPresent(id)?TRUE:FALSE;
    return S_OK; 
}
// Is property showing but disabled
STDMETHODIMP CSimpleProperty::IsPropertyReadOnly( /*[out]*/BOOL* pbReadonly) 
{
    if (pbReadonly==NULL)
        return E_POINTER;
    *pbReadonly= FALSE;
    return S_OK; 
}
// Get the property description string
STDMETHODIMP CSimpleProperty::GetDescription( /*[out]*/BSTR* pBstrName) 
{
    if (pBstrName==NULL)
        return E_POINTER;
    *pBstrName = ::SysAllocString(m_bstrDescription);
    return S_OK; 
}

// *** Basic property value information ***
// OPM will typically display these in an edit field

// optional: meta data representing property type name, ex. ACAD_ANGLE
STDMETHODIMP CSimpleProperty::GetCurrentValueName( /*[out]*/BSTR* pbstrName) 
{
    return E_NOTIMPL; 
}
// What is the property type, ex. VT_R8
STDMETHODIMP CSimpleProperty::GetCurrentValueType( /*[out]*/VARTYPE* pVarType) 
{
    if (pVarType==NULL)
        return E_POINTER;
    *pVarType = m_valueType;
    return S_OK; 
}
// Get the property value, passes the specific object we need the property
// value for.
STDMETHODIMP CSimpleProperty::GetCurrentValueData( /*in*/LONG objectID, 
                                  /*[out]*/VARIANT* pVarData) 
{
    if (pVarData==NULL)
        return E_POINTER;
    AcDbObjectId id;
    id.setFromOldId(objectID);
    resbuf data;
    if (XRecordManager::getData(id,0,data)!=Acad::eOk)
        return E_FAIL;
    ::VariantCopy(pVarData,&_variant_t(data.resval.rreal));
    return S_OK; 
}
// Set the property value, passes the specific object we want to set the 
// property value for
STDMETHODIMP CSimpleProperty::SetCurrentValueData( /*[in]*/LONG objectID, 
                                     /*[in]*/const VARIANT varData) 
{
    AcDbObjectId id;
    id.setFromOldId(objectID);
    resbuf data;
    data.restype = AcDb::kDxfReal;
    data.resval.rreal = V_R8(&varData);
    if (XRecordManager::setData(id,0,data)!=Acad::eOk)
        return E_FAIL;
    //if the dynamic property is changed by some other
    if (m_pNotifySink!=NULL)
        m_pNotifySink->OnChanged(this);
    return S_OK; 
}

//*** Notifications ***
//OPM passes its implementation of IDynamicPropertyNotify, you
//cache it and call it to inform OPM your property has changed
STDMETHODIMP CSimpleProperty::Connect( /*[in]*/IDynamicPropertyNotify* pSink) 
{
    if (pSink==NULL)
        return E_POINTER;
    m_pNotifySink = pSink;
    return S_OK; 
}
STDMETHODIMP CSimpleProperty::Disconnect( ) 
{
    m_pNotifySink.Release();
    return S_OK; 
}
