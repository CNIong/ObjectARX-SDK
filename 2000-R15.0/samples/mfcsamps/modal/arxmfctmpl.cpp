// (C) Copyright 1996-1998 by Autodesk, Inc. 
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
//////////////////////////////////////////////////////////////
//
// Includes
//
//////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <aced.h>
#include <rxregsvc.h>
#include <acutads.h>
#include <rxmfcapi.h>
#include <AcExtensionModule.h>
#include "modal.h"

extern "C" HWND adsw_acadMainWnd();

/////////////////////////////////////////////////////////////////////////////
// Define the sole extension module object.

AC_IMPLEMENT_EXTENSION_MODULE(theArxDLL);

void modalDlgTest()
{
    // When resource from this ARX app is needed, just
    // instantiate a local CAcModuleResourceOverride
    CAcModuleResourceOverride resOverride;

    CTestDlg dlg(CWnd::FromHandle(adsw_acadMainWnd()));
	dlg.DoModal();
}
//////////////////////////////////////////////////////////////
//
// MFC Initialization - DllMain will be called first once 
// the application loaded.
//
//////////////////////////////////////////////////////////////
extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
        theArxDLL.AttachInstance(hInstance);
	else if (dwReason == DLL_PROCESS_DETACH)
        theArxDLL.DetachInstance();  
	
	return 1;   // ok
}

//
// Entry point - called after DllMain() is called
//
extern "C" __declspec(dllexport)
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* p)
{
	switch( msg ) 
	{
	case AcRx::kInitAppMsg: 
		acrxRegisterAppMDIAware(p);
		acedRegCmds->addCommand( "RX_TEST", "MODAL", "MODAL",
  					ACRX_CMD_MODAL, &modalDlgTest);
		acutPrintf( "\nEnter \"modal\" to bring up the dialog.\n" );
		break;
	case AcRx::kUnloadAppMsg: 
		acedRegCmds->removeGroup("RX_TEST" );
		break;
	default:
		break;
	}
	return AcRx::kRetOK;
}
