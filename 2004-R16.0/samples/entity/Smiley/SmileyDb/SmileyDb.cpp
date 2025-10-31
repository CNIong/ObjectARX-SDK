//
// (C) Copyright 2000-2002 by Autodesk, Inc. 
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
//

// SmileyDb.cpp : Initialization functions

#include "StdAfx.h"
#include "StdArx.h"
#include "resource.h"
#include "appinfo.h"

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_MSG
void InitApplication();
void UnloadApplication();
//}}AFX_ARX_MSG

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_ADDIN_FUNCS
void RegisterDbxApp();
//}}AFX_ARX_ADDIN_FUNCS


/////////////////////////////////////////////////////////////////////////////
// ObjectARX EntryPoint
extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	switch (msg) {
	case AcRx::kInitAppMsg:
		// Comment out the following line if your
		// application should be locked into memory
		acrxDynamicLinker->unlockApplication(pkt);
		acrxDynamicLinker->registerAppMDIAware(pkt);
		InitApplication();
		break;
	case AcRx::kUnloadAppMsg:
		UnloadApplication();
		break;
	}
	return AcRx::kRetOK;
}


// Init this application. Register your
// reactors, custom classes...
void InitApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_INIT
	AsdkSmiley::rxInit();
	acrxBuildClassHierarchy();
	acrxRegisterService(ASDKSMILEYDB_DBXSERVICE);
	RegisterDbxApp();
	//}}AFX_ARX_INIT
	AsdkSmiley::initCLSID();
}

// Unload this application. Unregister all objects
// registered in InitApplication.
void UnloadApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_EXIT
	deleteAcRxClass(AsdkSmiley::desc());
	delete acrxServiceDictionary->remove(ASDKSMILEYDB_DBXSERVICE);
	//}}AFX_ARX_EXIT

	// TODO: clean up your application
}

//----- Register the Application in the AutoCAD registry (demand loading)

// This function registers this ObjectARX Application
// on AutoCAD for demandload and in the
// Windows Registry.
void RegisterDbxApp()
{
	// Fill the AppInfo structure with our demand loading details.
	AcadAppInfo appInfo;
	appInfo.setAppName("AsdkSmileyDb");// AppName
	// Get the DBX file path.
	HMODULE hModule=GetModuleHandle("asdkSmileyDb.dbx");
    char modulePath[512];
    DWORD pathLength = GetModuleFileName(hModule, modulePath, 512);
	if (pathLength)
		appInfo.setModuleName(modulePath); // Set the DBX file path.
	appInfo.setAppDesc("AsdkSmileyDb Sample");// Description
	appInfo.setLoadReason(
		AcadApp::LoadReasons(// Specify when we want this app to load.
		AcadApp::kOnProxyDetection |
		AcadApp::kOnLoadRequest));
	
	appInfo.writeToRegistry(true,true);// Write the AppInfo to the registry, include the DBX registry section.
}
