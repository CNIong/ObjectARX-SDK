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
// Jig3d.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "rxdlinkr.h"
#include "aced.h"

static AFX_EXTENSION_MODULE Jig3dDLL = { NULL, NULL };
extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("Jig3d.ARX Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(Jig3dDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(Jig3dDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("Jig3d.ARX Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(Jig3dDLL);
	}
	return 1;   // ok
}
//command handler
extern void jig3d();
const char* cstrCommandGroup = "ASDK_3DJIG";

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt) 
{
    switch (msg) {
    case AcRx::kInitAppMsg:
    {
        acrxDynamicLinker->unlockApplication(pkt); 
        acrxDynamicLinker->registerAppMDIAware(pkt);
		acedRegCmds->addCommand ( cstrCommandGroup, "3djig","3djig",
    		ACRX_CMD_MODAL, &jig3d);
		acutPrintf("Registered modal command ""3djig""");
        break;
    }
    case AcRx::kUnloadAppMsg:
        acedRegCmds->removeGroup(cstrCommandGroup);
        break;
    }
    return AcRx::kRetOK;
}