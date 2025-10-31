//
// (C) Copyright 2000 by Autodesk, Inc. 
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
//

// SmileyApplication.h : Declaration of the CSmileyApplication

#ifndef __SMILEYAPPLICATION_H_
#define __SMILEYAPPLICATION_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSmileyApplication
class ATL_NO_VTABLE CSmileyApplication : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSmileyApplication, &CLSID_SmileyApplication>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CSmileyApplication>,
	public IDispatchImpl<ISmileyApplication, &IID_ISmileyApplication, &LIBID_SmileyUi>
{
public:
	CSmileyApplication()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SMILEYAPPLICATION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSmileyApplication)
	COM_INTERFACE_ENTRY(ISmileyApplication)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CSmileyApplication)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISmileyApplication
public:
	STDMETHOD(CreateSmiley)();
};

#endif //__SMILEYAPPLICATION_H_
