//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// AsdkAcUiSample.cpp : Defines the initialization routines for the DLL.
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "AsdkAcUiSample.h"

#include "AsdkAcUiDialogSample.h"
#include "AcExtensionModule.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Define the sole extension module object.

AC_IMPLEMENT_EXTENSION_MODULE(theArxDLL);

void dialogCreate()
{
 
    // Modal
    AsdkAcUiDialogSample dlg(CWnd::FromHandle(adsw_acadMainWnd()));
    INT_PTR nReturnValue = dlg.DoModal();
    
}

static void initApp()
{

  CAcModuleResourceOverride resOverride;

  acedRegCmds->addCommand(_T("ASDK_ACUI_SAMPLE"), 
                          _T("ASDKACUISAMPLE"), 
                          _T("ACUISAMPLE"), 
                          ACRX_CMD_MODAL, 
                          dialogCreate,
                          NULL,
                          -1,
                          theArxDLL.ModuleResourceInstance());

}


static void unloadApp()
{

  // Do other cleanup tasks here  
  acedRegCmds->removeGroup(_T("ASDK_ACUI_SAMPLE"));  
}



//////////////////////////////////////////////////////////////
//
// Entry points
//
//////////////////////////////////////////////////////////////

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    // Remove this if you use lpReserved
    UNREFERENCED_PARAMETER(lpReserved);
    
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        theArxDLL.AttachInstance(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        theArxDLL.DetachInstance();  
    }
    return 1;   // ok
}


extern "C" AcRx::AppRetCode acrxEntryPoint( AcRx::AppMsgCode msg, void* appId)
{
    switch( msg ) 
    {
    case AcRx::kInitAppMsg: 
        acrxDynamicLinker->unlockApplication(appId);
        acrxDynamicLinker->registerAppMDIAware(appId);
        initApp(); 
        break;
    case AcRx::kUnloadAppMsg: 
        unloadApp(); 
        break;
    case AcRx::kInitDialogMsg:
        
        break;
    default:
        break;
    }
    return AcRx::kRetOK;
}

