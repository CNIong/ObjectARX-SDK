// (C) Copyright 2002-2007 by Autodesk, Inc. 
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

//-----------------------------------------------------------------------------
//----- ConnectingLink.h : Declaration of the CConnectingLink
//-----------------------------------------------------------------------------
#pragma once
#include "resource.h"

#include "SliderCrankDb_i.h"



//----- CConnectingLink
class ATL_NO_VTABLE CConnectingLink : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CConnectingLink, &CLSID_ConnectingLink>,
	public ISupportErrorInfo,
	public IAcadEntityDispatchImpl<CConnectingLink, &CLSID_ConnectingLink, IConnectingLink, &IID_IConnectingLink, &LIBID_AsdkSliderCrankDbLib>
#ifdef NEVER
	//- Please do not remove the following line. It is here to make .NET ATL Wizards
	//- running properly. The parent class will not compile but is required by .NET to recognize
	//-	this class as being an ATL coclass
	,public IDispatchImpl<IConnectingLink, &IID_IIConnectingLink, &LIBID_AsdkSliderCrankDbLib>
#endif
{
public:
	CConnectingLink () {
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_CONNECTINGLINK)

	BEGIN_COM_MAP(CConnectingLink)
		COM_INTERFACE_ENTRY(IConnectingLink)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
		COM_INTERFACE_ENTRY(IAcadBaseObject)
		COM_INTERFACE_ENTRY(IAcadBaseObject2)
		COM_INTERFACE_ENTRY(IAcadObject)
		COM_INTERFACE_ENTRY(IAcadEntity)
		COM_INTERFACE_ENTRY(IRetrieveApplication)
	END_COM_MAP()

	//----- ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct () {
		return (S_OK) ;
	}
	
	void FinalRelease () {
	}

	//IAcadBaseObjectImpl
	virtual HRESULT CreateNewObject (AcDbObjectId &objId, AcDbObjectId &ownerId, TCHAR *keyName);
	//IAcadBaseObject2Impl
	STDMETHOD(ForceDbResident)(VARIANT_BOOL *forceDbResident) ;
	STDMETHOD(CreateObject)(AcDbObjectId ownerId =AcDbObjectId::kNull, TCHAR *keyName =NULL);
	STDMETHOD(AddToDb)(AcDbObjectId &objId, AcDbObjectId ownerId =AcDbObjectId::kNull, TCHAR *keyName =NULL);

public:
	//IConnectingLink
	STDMETHOD(get_Length)(DOUBLE* pVal);
	STDMETHOD(put_Length)(DOUBLE newVal);
} ;

OBJECT_ENTRY_AUTO(__uuidof(ConnectingLink), CConnectingLink)
