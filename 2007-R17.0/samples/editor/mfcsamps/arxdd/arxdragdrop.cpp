//
// (C) Copyright 1996-2006 by Autodesk, Inc. 
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
// arxdragdrop.cpp : Defines the initialization routines for the DLL.
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif


#include <aced.h>
#include <adslib.h>
#include <rxregsvc.h>
#include <AcExtensionModule.h>
#include "resource.h"




void MFCTest();

//////////////////////////////////////////////////////////////
//
// Rx interface
//
//////////////////////////////////////////////////////////////

// global FileDropTarget;
CMyFileDropTarget gFileDropTarget;
CMainFrame *gpMainFrame = NULL;


void initApp()
{
    acutPrintf( _T("\nLoading Drag & Drop Sample ...") );
    
    acedRegCmds->addCommand( _T("ASDK_CMDS"),          // Group name 
        _T("arxdd"),        // Global function name
        _T("arxdd"),        // Local function name
        ACRX_CMD_MODAL, // Type
        &MFCTest );      // Function pointer
    
    acedAddDropTarget(&gFileDropTarget);
    
    acutPrintf( _T(".OK!\n") );
}

void unloadApp()
{
    // Remove the command group because we are unloading
    //
    acedRegCmds->removeGroup( _T("ASDK_CMDS") );
    acedRemoveDropTarget(&gFileDropTarget);
	if(gpMainFrame)
		gpMainFrame->DestroyWindow();
}

//////////////////////////////////////////////////////////////
//
// Entry points
//
//////////////////////////////////////////////////////////////
// Define the sole extension module object.

AC_IMPLEMENT_EXTENSION_MODULE(theArxDLL);

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


extern "C" AcRx::AppRetCode acrxEntryPoint( AcRx::AppMsgCode msg, void* p)
{
    switch( msg ) 
    {
    case AcRx::kInitAppMsg: 
        initApp(); 
		acrxRegisterAppMDIAware(p);
        break;
    case AcRx::kUnloadAppMsg: 
        unloadApp(); 
        break;
    default:
        break;
    }
    return AcRx::kRetOK;
}


//////////////////////////////////////////////////////////////
void MFCTest()
{ 
    // When resource from this ARX app is needed, just
    // instantiate a local CAcModuleResourceOverride
    CAcModuleResourceOverride resOverride;
    
	if(gpMainFrame && gpMainFrame->m_hWnd)
	{
		gpMainFrame->ShowWindow(SW_SHOW);
		return;
	}
    gpMainFrame = new CMainFrame;
    RECT rect = {0,0,130,180}; 
    if (!gpMainFrame->Create(_T("Arxdd"),
        WS_VISIBLE | WS_SYSMENU | WS_CAPTION, rect, NULL))
        TRACE(_T("Error: Unable to show window!"));
}

