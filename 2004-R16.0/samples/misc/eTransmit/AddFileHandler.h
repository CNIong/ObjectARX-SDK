//
// (C) Copyright 2001, 2002 by Autodesk, Inc. 
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

// AddFileHandler.h : Declaration of the CAddFileHandler

#ifndef __ADDFILEHANDLER_H_
#define __ADDFILEHANDLER_H_

#include "resource.h"       // main symbols

#import "..\..\..\inc\AcETransmit16.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

/////////////////////////////////////////////////////////////////////////////
// CAddFileHandler
class ATL_NO_VTABLE CAddFileHandler : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAddFileHandler, &CLSID_AddFileHandler>,
	public IDispatchImpl<IAddFileHandler, &IID_IAddFileHandler, &LIBID_AsdkETRANSMITNOTIFIERLib>,
	public IDispatchImpl<ITransmittalAddFileNotificationHandler, &IID_ITransmittalAddFileNotificationHandler, &LIBID_TRANSMITTALLib>
{
public:
	CAddFileHandler()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ADDFILEHANDLER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAddFileHandler)
	COM_INTERFACE_ENTRY(IAddFileHandler)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY2(IDispatch, IAddFileHandler)
	COM_INTERFACE_ENTRY(ITransmittalAddFileNotificationHandler)
END_COM_MAP()

// IAddFileHandler
public:
// ITransmittalAddFileNotificationHandler
	STDMETHOD(addFileNotificationHandler)(ITransmittalFile * pFile, ITransmittalOperation * pTransmit);
	STDMETHOD(beginFilesGraphCreation)(ITransmittalOperation * pTransmit);
	STDMETHOD(endFilesGraphCreation)(ITransmittalOperation * pTransmit);


};


#endif