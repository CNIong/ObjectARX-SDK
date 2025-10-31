//
//
// (C) Copyright 2003-2007 by Autodesk, Inc. 
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

// AsdkPlotNotifySink.h : Declaration of the CAsdkPlotNotifySink

#pragma once
#include "resource.h"       // main symbols

#include "AsdkPlotApiDialog_i.h"
#include "resource.h"

#include "plotnotificationsdialog.h"

// CAsdkPlotNotifySink

class ATL_NO_VTABLE CAsdkPlotNotifySink : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAsdkPlotNotifySink, &CLSID_CPlotNotifySink>,
	public IDispatchImpl<IAsdkPlotNotifySink, &IID_IAsdkPlotNotifySink, &LIBID_asdkAsdkPlotApiDialogLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CAsdkPlotNotifySink()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ASDKPLOTNOTIFYSINK1)


BEGIN_COM_MAP(CAsdkPlotNotifySink)
	COM_INTERFACE_ENTRY(IAsdkPlotNotifySink)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		// When the sink is instantiated, spawn the notifications dialog to display
		// notifications received by any clients.
		pNotifyDlg=new CPlotNotificationsDialog;
		pNotifyDlg->Create(IDD_PLOTNOTIFICATIONSDIALOG);
		pNotifyDlg->ShowWindow(SW_SHOW);
		return S_OK;
	}
	
	void FinalRelease() 
	{
		// Clean up the notifications dialog.
		// This should be called when the ref-count for the server drops to zero...when both the
		// PLOTAPI dialog, and all the client reactors are destroyed.
		pNotifyDlg->DestroyWindow();
		delete pNotifyDlg;
	}

public:
	CPlotNotificationsDialog *pNotifyDlg;

	STDMETHOD(SendPlotEvent)(BSTR EventString);
	STDMETHOD(get_Visible)(VARIANT_BOOL* pVal);
	STDMETHOD(put_Visible)(VARIANT_BOOL newVal);
};

OBJECT_ENTRY_AUTO(__uuidof(CPlotNotifySink), CAsdkPlotNotifySink)
