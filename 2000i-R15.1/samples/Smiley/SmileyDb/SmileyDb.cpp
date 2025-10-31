//
// (C) Copyright 2000 by Autodesk, Inc. 
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


// This function registers this ObjectARX Application
// on AutoCAD for demandload and in the
// Windows Registry.
void RegisterDbxApp()
{
	int strLength;
	HMODULE hModule = GetModuleHandle("AsdkSmileyDb.dbx");

	if (!hModule)
		return;

	//
	// Register the application.
	//
	char ThisAppRegistryPath[] = { "Software\\Autodesk\\ObjectARX\\3.0\\SampleApps\\Smiley\\" };

	const char* dbxRegRoot = acrxObjectDBXRegistryKey();
	char DbxAppRegistryPath[256];
	strcpy(DbxAppRegistryPath, dbxRegRoot);
	strcat(DbxAppRegistryPath, "\\Applications\\");
	strcat(DbxAppRegistryPath, "AsdkSmileyDb");
	//
	// Create the registry key under the DBX path
	// (use the variable DbxRegistryPath).
	//

	HKEY dbxKey;
	DWORD result;
	LONG status = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
	                             DbxAppRegistryPath,
	                             0, "",
	                             REG_OPTION_NON_VOLATILE,
	                             KEY_WRITE, NULL, &dbxKey, &result);
	if (ERROR_SUCCESS != status)
		return;

	// Create the 'LOADCTRLS' value.
	int loadReason = AcadApp::kOnProxyDetection |
	                 AcadApp::kOnLoadRequest |
	                 AcadApp::kTransparentlyLoadable;
	status = RegSetValueEx(dbxKey, "LOADCTRLS", 0, REG_DWORD,
	              (const unsigned char*) &loadReason,
	              sizeof(loadReason));
	if (ERROR_SUCCESS != status)
		return;

	// Create the 'REGPATH' value.
	char regPath[256];
	strcpy(regPath, "\\\\HKEY_LOCAL_MACHINE\\");
	strcat(regPath, ThisAppRegistryPath);
	strcat(regPath, "AsdkSmileyDb");
	status = RegSetValueEx(dbxKey, "REGPATH", 0, REG_SZ,
	              (const unsigned char*) regPath, strlen(regPath) + 1);

	status = RegCloseKey(dbxKey);
	if (ERROR_SUCCESS != status)
		return;

	//
	// Create the registry key for this application
	// (use the variable ThisAppRegistryPath).
	//

	HKEY appKey;
	status = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
	                             ThisAppRegistryPath,
	                             0, "",
	                             REG_OPTION_NON_VOLATILE,
	                             KEY_WRITE, NULL, &appKey, &result);
	if (ERROR_SUCCESS != status)
		return;

	HKEY prodKey;
	status = RegCreateKeyEx(appKey, "AsdkSmileyDb", 0, "",
	                        REG_OPTION_NON_VOLATILE,
	                        KEY_WRITE, NULL, &prodKey, &result);
	RegCloseKey(appKey);
	if (ERROR_SUCCESS != status)
		return;

	// Create the 'Loader' key.
	HKEY loaderKey;
	status = RegCreateKeyEx(prodKey, "Loader", 0, "",
	                        REG_OPTION_NON_VOLATILE,
	                        KEY_WRITE, NULL, &loaderKey, &result);
	if (ERROR_SUCCESS == status) {
		char modulePath[512];
		strLength = GetModuleFileName(hModule, modulePath, 512);
		if (strLength)
			RegSetValueEx(loaderKey, "MODULE", 0, REG_SZ,
			              (const unsigned char*)modulePath, strLength + 1);
		RegCloseKey(loaderKey);
	}

	// Create the 'Name' key.
	HKEY nameKey;
	status = RegCreateKeyEx(prodKey, "Name", 0, "",
	                        REG_OPTION_NON_VOLATILE,
	                        KEY_WRITE, NULL, &nameKey, &result);
	if (ERROR_SUCCESS == status) {
		RegSetValueEx(nameKey, "AsdkSmileyDb", 0, REG_SZ,
		              (const unsigned char*) "AsdkSmileyDb", 13);
		RegCloseKey(nameKey);
	}

	//
	// Finished.
	//

	RegCloseKey(prodKey);
}

