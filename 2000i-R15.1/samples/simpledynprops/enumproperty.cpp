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
// EnumProperty.cpp : Implementation of CEnumProperty
#include "stdafx.h"
#include "SimpleDynProps.h"
#include "EnumProperty.h"
#include "xrecordmanager.h"

//A property is enumerated if
//GetCurrentValueType returns VT_USERDEFINED _AND_
//GetCurrentValueName returns a NULL string _AND
//the object supports the IDynamicEnumProperty inteface

/////////////////////////////////////////////////////////////////////////////
// CEnumProperty
CEnumProperty::CEnumProperty():
    m_numPropertyValues(3)
{
    m_bstrDisplayName = L"EnumProperty";
    m_bstrDescription = L"Description of EnumProperty";
    m_valueType = VT_USERDEFINED; 
}
// - for properties types which are enums or finite valued but dynamic
// OPM will typically display these in a dropdown list

// total number of values this property can have, or currently has
// A -1 return value indicates continuous range. In this case, only 
//"Get/SetCurrentValue" methods will be used
STDMETHODIMP CEnumProperty::GetNumPropertyValues( /*[out]*/LONG* numValues) 
{ 
    if (numValues==NULL)
        return E_POINTER;
    *numValues = m_numPropertyValues;
    return S_OK;
}
// called for each property value, 0-based indexed to GetNumPropertyValues()
STDMETHODIMP CEnumProperty::GetPropValueName( /*in*/LONG index, 
                               /*[out]*/BSTR* pValueName) 
{
    if (pValueName==NULL)
        return E_POINTER;
    *pValueName = ::SysAllocString(_bstr_t(index));
    return S_OK;
}

// called for each property value, 0-based indexed to GetNumPropertyValues()
STDMETHODIMP CEnumProperty::GetPropValueData( /*in*/LONG index, 
                               /*[out]*/VARIANT* pValueData) 
{ 
    if (pValueData==NULL)
        return E_POINTER;
    if (index>2)
        return E_FAIL;
    //OPM only handles VT_I4 for now
    ::VariantCopy(pValueData,&_variant_t(index));
    return S_OK;
}

// Get the property value, passes the specific object we need the property
// value for.
STDMETHODIMP CEnumProperty::GetCurrentValueData( /*in*/LONG objectID, 
                                  /*[out]*/VARIANT* pVarData) 
{
    if (pVarData==NULL)
        return E_POINTER;
    AcDbObjectId id;
    id.setFromOldId(objectID);
    resbuf data;
    if (XRecordManager::getData(id,2,data)!=Acad::eOk)
        return E_FAIL;
    ::VariantCopy(pVarData,&_variant_t(data.resval.rlong));
    return S_OK; 
}
// Set the property value, passes the specific object we want to set the 
// property value for
STDMETHODIMP CEnumProperty::SetCurrentValueData( /*[in]*/LONG objectID, 
                                     /*[in]*/const VARIANT varData) 
{
    AcDbObjectId id;
    id.setFromOldId(objectID);
    resbuf data;
    data.restype = AcDb::kDxfInt32;
    data.resval.rlong = V_I4(&varData);
    if (XRecordManager::setData(id,2,data)!=Acad::eOk)
        return E_FAIL;
    //if the dynamic property is changed by some other
    if (m_pNotifySink!=NULL)
        m_pNotifySink->OnChanged(this);
    return S_OK; 
}