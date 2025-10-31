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
// SimpleProperty.h : Declaration of the CSimpleProperty

#ifndef __SIMPLEPROPERTY_H_
#define __SIMPLEPROPERTY_H_

#include "resource.h"       // main symbols
#include "rxclass.h"
#include "dynprops.h"
#include <comdef.h>
/////////////////////////////////////////////////////////////////////////////
// CSimpleProperty
class ATL_NO_VTABLE CSimpleProperty : 
	public CComObjectRootEx<CComSingleThreadModel>,
    public IDynamicProperty
{
public:
	CSimpleProperty();

BEGIN_COM_MAP(CSimpleProperty)
    COM_INTERFACE_ENTRY(IDynamicProperty)
END_COM_MAP()

public:
    //Unique property ID
    STDMETHOD(GetGUID)( /*[out]*/GUID* propGUID) ;
    // Property display name
    STDMETHOD(GetDisplayName)( /*[out]*/BSTR* bstrName) ;
    // Show/Hide property in the OPM, for this object instance 
    STDMETHOD(IsPropertyEnabled)( /*[in]*/LONG objectID,
                                      /*[out]*/BOOL* pbEnabled) ;
    // Is property showing but disabled
    STDMETHOD(IsPropertyReadOnly)( /*[out]*/BOOL* pbReadonly) ;
    // Get the property description string
    STDMETHOD(GetDescription)( /*[out]*/BSTR* bstrName) ;
    
    // *** Basic property value information ***
    // OPM will typically display these in an edit field
    
    // optional: meta data representing property type name, ex. ACAD_ANGLE
    STDMETHOD(GetCurrentValueName)( /*[out]*/BSTR* pbstrName) ;
    // What is the property type, ex. VT_R8
    STDMETHOD(GetCurrentValueType)( /*[out]*/VARTYPE* pVarType) ;
    // Get the property value, passes the specific object we need the property
    // value for.
    STDMETHOD(GetCurrentValueData)( /*in*/LONG objectID, 
                                      /*[out]*/VARIANT* pvarData) ;
    // Set the property value, passes the specific object we want to set the 
    // property value for
    STDMETHOD(SetCurrentValueData)( /*[in]*/LONG objectID, 
                                         /*[in]*/const VARIANT varData) ;

    //*** Notifications ***
    //OPM passes its implementation of IDynamicPropertyNotify, you
    //cache it and call it to inform OPM your property has changed
    STDMETHOD(Connect)( /*[in]*/IDynamicPropertyNotify* pSink) ;
    STDMETHOD(Disconnect)( ) ;
protected:
    CComPtr<IDynamicPropertyNotify> m_pNotifySink;
    _bstr_t m_bstrDescription;
    _bstr_t m_bstrDisplayName;
    VARTYPE m_valueType;
};

#endif //__SIMPLEPROPERTY_H_
