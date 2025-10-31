//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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
// ExtendTabs.cpp : Defines the initialization routines for the DLL.
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <aced.h>
#include <rxmfcapi.h>
#include <adui.h>
#include <acui.h>
#include <rxregsvc.h>
#include <AcExtensionModule.h>
#include "MyDlg.h"
#include "Tab1.h"
#include "Tab2.h"




CTab1 gTab1;
CTab2 gTab2;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HINSTANCE _hdllInstance = NULL;

void initApp();
void unloadApp();
void addMyTabs(CAdUiTabExtensionManager* pXtabManager);
void ExtendTabsCreate();

/////////////////////////////////////////////////////////////////////////////
// Define the sole extension module object.
AC_IMPLEMENT_EXTENSION_MODULE(ExtendTabsDLL);
/////////////////////////////////////////////////////////////////////////////

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_hdllInstance = hInstance;
		ExtendTabsDLL.AttachInstance(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		ExtendTabsDLL.DetachInstance();
	}
	return 1;   // ok
}

//////////////////////////////////////////////////////////////
//
// Entry point
//
//////////////////////////////////////////////////////////////

extern "C" __declspec(dllexport) AcRx::AppRetCode 
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
      addMyTabs((CAdUiTabExtensionManager*)pkt);
	  break;
    default:
      break;
  }
  return AcRx::kRetOK;
}


void initApp()
{
	acedRegCmds->addCommand(_T("RX_CMDS"), _T("EXTTABS"), _T("EXTENDTABS"), 
		ACRX_CMD_MODAL, &ExtendTabsCreate);

	// Express interest in adding tabs to the OPTIONS dialog.
	// The name of the OPTIONS dialog in AutoCAD is "OptionsDialog".
	acedRegisterExtendedTab(_T("EXTENDTABS.ARX"), _T("OptionsDialog"));
	acutPrintf(_T("\nCommand is \"ExtendTabs\"."));
}


void unloadApp()
{
  // Do other cleanup tasks here  
  acedRegCmds->removeGroup(_T("RX_CMDS"));
}

void addMyTabs(CAdUiTabExtensionManager* pXtabManager)
// Add the tabs here.
{
    // When resource from this ARX app is needed, just
    // instantiate a local CAcModuleResourceOverride
	CAcModuleResourceOverride resOverride;

	// Add our tabs to the 'OPTIONS' dialog
    pXtabManager->AddTab(_hdllInstance, IDD_TAB1,_T("My Tab1"), &gTab1);
	gTab1.StretchControlXY(IDC_EDIT1, 50, 50);
	gTab1.StretchControlXY(IDC_EDIT2, 50, 50);
    gTab1.MoveControlX(IDC_EDIT2, 100);
	gTab1.MoveControlX(IDC_STATIC2, 100);
	pXtabManager->AddTab(_hdllInstance, IDD_TAB2,_T("My Tab2"), &gTab2);
	gTab2.StretchControlXY(IDC_LIST1, 50, 100);
	gTab2.MoveControlX(IDC_RADIO1, 100);
	gTab2.MoveControlX(IDC_RADIO2, 100);
	gTab2.MoveControlX(IDC_RADIO3, 100);
	gTab2.MoveControlX(IDC_STATIC1, 100);
	gTab2.StretchControlXY(IDC_LIST2, 50, 100);
	gTab2.MoveControlX(IDC_LIST2, 100);
	gTab2.MoveControlY(IDC_STATIC3, 100);
	gTab2.MoveControlY(IDC_EDIT1, 100);
	gTab2.MoveControlY(IDC_BUTTON, 100);
	
}

void ExtendTabsCreate()
{
    // When resource from this ARX app is needed, just
    // instantiate a local CAcModuleResourceOverride
	CAcModuleResourceOverride resOverride;
 
    CMyDlg dlg(acedGetAcadFrame());
    int nRetVal = dlg.DoModal();
}
