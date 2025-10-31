//
// (C) Copyright 2002-2003 by Autodesk, Inc. 
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
// MaterialDb.cpp : Initialization functions
//

#include "StdAfx.h"
#include "resource.h"
#include "appinfo.h"
#include "AsdkMaterial.h"

const char kAppName[]       = "AsdkMaterialDb";
const char kAppDescr[]      = "DBX sample app to demonstrate AcDbMaterials";
const char kDbxModuleName[] = "AsdkMaterialDb.dbx";

////////////////////////////////////////////////////////////////////////////////
// Register the DBX application for demand loading
//
void RegisterDbxApp(void)
{
	// Get the DBX module path
    char dbxModulePath[512] = "";
	HMODULE hModule = GetModuleHandle(kDbxModuleName);
    DWORD pathLength = GetModuleFileName(hModule, dbxModulePath, 512);

    // Set up the demand loading
    AcadAppInfo appInfo;

    appInfo.setAppName    (kAppName);                  // Application name
    appInfo.setModuleName (dbxModulePath);             // ARX file location
    appInfo.setAppDesc    (kAppDescr);                 // Description
    appInfo.setLoadReason (AcadApp::LoadReasons(       // Reasons for loading:
                           AcadApp::kOnProxyDetection  //  -proxy object detected
                         | AcadApp::kOnLoadRequest));  //  -load requested

    appInfo.writeToRegistry(true,true);                  // Commit to registry 
                                                       // in DBX section
}

////////////////////////////////////////////////////////////////////////////////
// Initialize this application. Register your custom classes and reactors.
//
void InitApplication()
{
	AsdkMaterial::rxInit();
	acrxBuildClassHierarchy();
	acrxRegisterService(ASDKMATERIALDB_DBXSERVICE);
	RegisterDbxApp();
}

////////////////////////////////////////////////////////////////////////////////
// Unload this application. Unregister all objects registered in 
// InitApplication.
//
void UnloadApplication()
{
	deleteAcRxClass(AsdkMaterial::desc());
	delete acrxServiceDictionary->remove(ASDKMATERIALDB_DBXSERVICE);
}

////////////////////////////////////////////////////////////////////////////////
// ObjectARX entry point
//
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