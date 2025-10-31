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
// ExtDwgSetng.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <aced.h>
#include <rxmfcapi.h>
#include <adui.h>
#include <acui.h>
#include <rxregsvc.h>
#include <AcExtensionModule.h>

#include "TabInfo.h"
#include "DwgSetngTab1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HINSTANCE _hdllInstance = NULL;
static AFX_EXTENSION_MODULE ExtendTabsDLL = { NULL, NULL };

CDwgSetngTab1* gpTab1;

void initApp();
void unloadApp();
void addDwgSetngTabs(CAdUiTabExtensionManager*);
void dwgSetngTabsCreate();

/////////////////////////////////////////////////////////////////////////////
// Define the sole extension module object.
AC_IMPLEMENT_EXTENSION_MODULE(theArxDLL);
/////////////////////////////////////////////////////////////////////////////

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_hdllInstance = hInstance;
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(ExtendTabsDLL, hInstance))
			return 0;

		new CDynLinkLibrary(ExtendTabsDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		// Terminate the library before destructors are called
		AfxTermExtensionModule(ExtendTabsDLL);
	}
	return 1;   // ok
}

//////////////////////////////////////////////////////////////
//
// Entry point
//
//////////////////////////////////////////////////////////////

//extern "C" __declspec(dllexport) AcRx::AppRetCode 
extern "C" AcRx::AppRetCode
acrxEntryPoint( AcRx::AppMsgCode msg, void* pkt)
{
  switch( msg ) 
  {
    case AcRx::kInitAppMsg: 
  	  acrxDynamicLinker->unlockApplication(pkt);
	  acrxRegisterAppMDIAware(pkt);
      initApp(); 
      break;
    case AcRx::kUnloadAppMsg: 
      unloadApp(); 
      break;
    case AcRx::kInitDialogMsg:
      addDwgSetngTabs((CAdUiTabExtensionManager*)pkt);
	  break;
    default:
      break;
  }
  return AcRx::kRetOK;
}


void initApp()
{
	acedRegCmds->addCommand("RX_CMDS", "EXTDWG", "EXTENDDWG", 
		ACRX_CMD_MODAL, &dwgSetngTabsCreate);

	// Add a tab to the existing 'Drawing Settings...' dialog
	acedRegisterExtendedTab("EXTDWGSETNG.ARX", "DrawingSettingsDialog");
	acutPrintf("\nCommand is \"ExtendDwg\".");
}


void unloadApp()
{
  // Do other cleanup tasks here  
  acedRegCmds->removeGroup("RX_CMDS");
}

void addDwgSetngTabs(CAdUiTabExtensionManager* pXtabManager)
{
    // When resource from this ARX app is needed, just
    // instantiate a local CAcModuleResourceOverride
	CAcModuleResourceOverride resOverride;

	gpTab1 = new CDwgSetngTab1;
	pXtabManager->AddTab(_hdllInstance, IDD_TAB1,"My Tab1", gpTab1);

}

void dwgSetngTabsCreate()
{
    // When resource from this ARX app is needed, just
    // instantiate a local CAcModuleResourceOverride
	CAcModuleResourceOverride resOverride;
 
    CTabInfo dlg(acedGetAcadFrame());

    int nReturnValue = dlg.DoModal();

}