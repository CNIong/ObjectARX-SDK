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
// EnumProperty.h : Declaration of the CEnumProperty

#ifndef __ENUMPROPERTY_H_
#define __ENUMPROPERTY_H_

#include "resource.h"       // main symbols
#include "categorizedproperty.h"

/////////////////////////////////////////////////////////////////////////////
// CEnumProperty
class ATL_NO_VTABLE CEnumProperty : 
	public CCategorizedProperty,
    public IDynamicEnumProperty
{
public:
	CEnumProperty();

BEGIN_COM_MAP(CEnumProperty)
	COM_INTERFACE_ENTRY(IDynamicEnumProperty)
    COM_INTERFACE_ENTRY_CHAIN(CCategorizedProperty)
END_COM_MAP()

public:
    // - for properties types which are enums or finite valued but dynamic
    // OPM will typically display these in a dropdown list
    
    // total number of values this property can have, or currently has
    // A -1 return value indicates continuous range. In this case, only 
    //"Get/SetCurrentValue" methods will be used
    STDMETHOD(GetNumPropertyValues)( /*[out]*/LONG* numValues) ;
    // called for each property value, 0-based indexed to GetNumPropertyValues()
    STDMETHOD(GetPropValueName)( /*in*/LONG index, 
                                   /*[out]*/BSTR* valueName) ;
    // called for each property value, 0-based indexed to GetNumPropertyValues()
    STDMETHOD(GetPropValueData)( /*in*/LONG index, 
                                   /*[out]*/VARIANT* valueName) ;

    // Get the property value, passes the specific object we need the property
    // value for.
    STDMETHOD(GetCurrentValueData)( /*in*/LONG_PTR objectID, 
                                      /*[out]*/VARIANT* pvarData) ;
    // Set the property value, passes the specific object we want to set the 
    // property value for
    STDMETHOD(SetCurrentValueData)( /*[in]*/LONG_PTR objectID, 
                                         /*[in]*/const VARIANT varData) ;
protected:
    long m_numPropertyValues;
};

#endif //__ENUMPROPERTY_H_
