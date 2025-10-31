// (C) Copyright 2003-2006 by Autodesk, Inc. 
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

// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

// CAsdkPlotNotifySinkClient wrapper class

class CAsdkPlotNotifySinkClient : public COleDispatchDriver
{
public:
	CAsdkPlotNotifySinkClient(){} // Calls COleDispatchDriver default constructor
	CAsdkPlotNotifySinkClient(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CAsdkPlotNotifySinkClient(const CAsdkPlotNotifySinkClient& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IAsdkPlotNotifySink methods
public:
	void SendPlotEvent(LPCTSTR EventString)
	{
		// Note:  This example simply uses the process ID for the background plot process...
		// It is not necessarily the best way to identify a plot job.

		// Append the current process ID (which assumes this is being called from a background process)
		TCHAR sbuff[32];
		_itot(GetCurrentProcessId(),sbuff,10);
        
		TCHAR tszDest[512];
        _tcscpy(tszDest,_T("ID:"));
		_tcscat(tszDest,sbuff);
		_tcscat(tszDest,_T("  "));
        _tcscat(tszDest,EventString);

		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, tszDest);
	}
	BOOL get_Visible()
	{
		BOOL result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Visible(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}

	// IAsdkPlotNotifySink properties
public:

};
