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
// CategorizedProperty.h : Declaration of the CCategorizedProperty

#ifndef __CATEGORIZEDPROPERTY_H_
#define __CATEGORIZEDPROPERTY_H_

#include "resource.h"       // main symbols
#include "category.h"
#include "simpleproperty.h"

/////////////////////////////////////////////////////////////////////////////
// CCategorizedProperty
class ATL_NO_VTABLE CCategorizedProperty : 
	public CSimpleProperty,
    public ICategorizeProperties
	
{
public:
	CCategorizedProperty();

BEGIN_COM_MAP(CCategorizedProperty)
	COM_INTERFACE_ENTRY(ICategorizeProperties)
    COM_INTERFACE_ENTRY_CHAIN(CSimpleProperty)
END_COM_MAP()


public:
    //Provide a category ID for the property, provide your own or see standards
    //You can ignore the incoming dispid. It's for internal use only
    STDMETHOD(MapPropertyToCategory)( 
                                     /* [in]  */ DISPID dispid,
                                     /* [out] */ PROPCAT* ppropcat) ;
    // Get the name for the category ID
    STDMETHOD(GetCategoryName)(
                               /* [in]  */ PROPCAT propcat, 
                               /* [in]  */ LCID lcid,
                               /* [out] */ BSTR* pbstrName) ;

    // Get the property value, passes the specific object we need the property
    // value for.
    STDMETHOD(GetCurrentValueData)( /*in*/LONG_PTR objectID, 
                                      /*[out]*/VARIANT* pvarData) ;
    // Set the property value, passes the specific object we want to set the 
    // property value for
    STDMETHOD(SetCurrentValueData)( /*[in]*/LONG_PTR objectID, 
                                         /*[in]*/const VARIANT varData) ;
protected:
    PROPCAT m_propCat;
    _bstr_t m_bstrPropCatName;
};

#endif //__CATEGORIZEDPROPERTY_H_
