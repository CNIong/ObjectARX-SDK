//////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////
//
// arxmfctmpl.cpp : Template file for MFC Based ARX applications.
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "cmdarx.h"         // command mode 
#include "defaultarx.h"     // default mode
#include "editarx.h"        // edit mode
#include <dbents.h>         // entity support for edit mode
#include <acdocman.h>
#include <rxmfcapi.h>
#include "resource.h"



//extern "C" HINSTANCE _hdllInstance;
HINSTANCE _hdllInstance = NULL;
static AFX_EXTENSION_MODULE arxmfcDLL;

cmCommandContext *gpCmCommand;
defaultContext *gpDefContext;
myEntityContext *gpEntMC;
myCircleContext *gpCircMC;
myLineContext *gpLineMC;

//////////////////////////////////////////////////////////////
//
// Entry point (1) - gets called first (before acrxEntryPoint)
//
//////////////////////////////////////////////////////////////

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
        _hdllInstance =  hInstance;		
		if (!AfxInitExtensionModule(arxmfcDLL, hInstance))
		 return 0;

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(arxmfcDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
      AfxTermExtensionModule(arxmfcDLL);
	
	return 1;   // ok
}
//////////////////////////////////////////////////////////////
//
// Rx interface
//
//////////////////////////////////////////////////////////////

void initApp(void* pAppID)
{	
    gpCmCommand = new cmCommandContext;   // command mode
    gpDefContext = new defaultContext;    // default mode
    gpEntMC = new myEntityContext;        // edit mode - for all entites
    gpCircMC = new myCircleContext;       // edit mode - for circle(s)
    gpLineMC = new myLineContext;         // edit mode - for line(s)
    
    acDocManager->pushResourceHandle(_hdllInstance);

    CString str1, str2, str3;
    str1.LoadString(IDS_CMDARX_GROUP);
    str2.LoadString(IDS_CMDARX_GLOBALNAME);
    str3.LoadString(IDS_CMDARX_LOCALNAME);
    // For command mode, supply ptr to AcEdUIContext object when
    // regestering the command with the editor.
    acedRegCmds->addCommand(str1, str2, str3, ACRX_CMD_MODAL, &cm, gpCmCommand);
    
//    CString menuLabel;
//    menuLabel.LoadString(IDS_CMDARX_MENU_LABEL);
    
    // No name is given for the menu, thus AutoCAD will use the filename
    // without the arx app as the name. In this case it will be "contextmenu"
    // to give the name you should call
    // acedAddDefaultContextMenu(&gpDefContext,gpAppID,name);  
	Adesk::Boolean b = acedAddDefaultContextMenu(gpDefContext, pAppID);
	assert(b == Adesk::kTrue);
    
    // gpEntMC is added to the class AcDbEntity. This will show whenever
    // something derived from AcDbEntity is selected.
    str1.LoadString(IDS_ERROR_ADDING);

    if (acedAddObjectContextMenu(AcDbEntity::desc(), gpEntMC, pAppID) == Adesk::kFalse)
        acutPrintf(str1);

    // gpCircMC is added to AcDbCircle. This will show up whenever a circle or something
    // derived from it is selected.      
    if (acedAddObjectContextMenu(AcDbCircle::desc(), gpCircMC, pAppID) == Adesk::kFalse)
        acutPrintf(str1);    
    
    // gpLineMC is added to AcDbLine. This will show up whenever a line or something
    // derived from it is selected.    
    if (acedAddObjectContextMenu(AcDbLine::desc(), gpLineMC, pAppID) == Adesk::kFalse)
        acutPrintf(str1);

    acDocManager->popResourceHandle();
}


void unloadApp()
{
    HINSTANCE hInst = AfxGetResourceHandle();
    AfxSetResourceHandle(_hdllInstance);

    CString str;
    str.LoadString(IDS_CMDARX_GROUP);
    acedRegCmds->removeGroup(str);

    // Lets be a good arx app and remove the menus before unloading.
    str.LoadString(IDS_ERROR_REMOVING);

    // Lets be a good arx app and remove the menus before unloading.
    acedRemoveDefaultContextMenu(gpDefContext);
    if (acedRemoveObjectContextMenu(AcDbEntity::desc(), gpEntMC) == Adesk::kFalse)
        acutPrintf(str);
    if (acedRemoveObjectContextMenu(AcDbCircle::desc(), gpCircMC) == Adesk::kFalse)
        acutPrintf(str);
    if (acedRemoveObjectContextMenu(AcDbLine::desc(), gpLineMC) == Adesk::kFalse)
        acutPrintf(str);

    delete gpCmCommand;
    delete gpDefContext;
    delete gpEntMC;
    delete gpCircMC;
    delete gpLineMC;

    AfxSetResourceHandle(hInst);

}

//////////////////////////////////////////////////////////////
//
// Entry point (2) - called after DllMain is called.
//
//////////////////////////////////////////////////////////////

extern "C" __declspec(dllexport) AcRx::AppRetCode 
acrxEntryPoint( AcRx::AppMsgCode msg, void* pkt)
{
    switch( msg ) 
    {
    case AcRx::kInitAppMsg: 
        acrxDynamicLinker->unlockApplication(pkt);
        acrxDynamicLinker->registerAppMDIAware(pkt);
        initApp(pkt); 
        break;
    case AcRx::kUnloadAppMsg: 
        unloadApp(); 
        break;
    default:
        break;
    }
    return AcRx::kRetOK;
}



