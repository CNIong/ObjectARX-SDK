//
//
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

// AsdkPlotNotifySink.cpp : Implementation of CAsdkPlotNotifySink
#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "AsdkPlotNotifySink.h"



// CAsdkPlotNotifySink


STDMETHODIMP CAsdkPlotNotifySink::SendPlotEvent(BSTR EventString)
{
	// Received a notification...
	CComBSTR bstr(EventString);
	// Unicode-ATL: LPCTSTR sztEventString=CW2A(bstr);
    CW2T tempEventString(bstr);
    LPCTSTR sztEventString = tempEventString;

	//...append a time and date to the string, and add it to the notifications list.
	CTime time=CTime::GetCurrentTime();
    CString csTime = (CString)sztEventString+time.Format( _T(": %A, %B %d, %Y - %H:%M:%S") );
	
	pNotifyDlg->m_NotificationsList.AddString(csTime);
    
	return S_OK;
}

// Get and Put visibility are here to support minimizing during a PLOT PREVIEW
STDMETHODIMP CAsdkPlotNotifySink::get_Visible(VARIANT_BOOL* pVal)
{
	*pVal=pNotifyDlg->IsWindowVisible();
	return S_OK;
}

STDMETHODIMP CAsdkPlotNotifySink::put_Visible(VARIANT_BOOL newVal)
{
	if(newVal==TRUE)
		pNotifyDlg->ShowWindow(SW_SHOW);
	else
		pNotifyDlg->ShowWindow(SW_HIDE);
	return S_OK;
}
