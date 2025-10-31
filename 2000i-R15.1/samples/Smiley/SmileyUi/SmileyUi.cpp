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

// SmileyUi.cpp : Initialization functions

#include "StdAfx.h"
#include "StdArx.h"
#include "resource.h"
#include "SmileJig.h"

// This command registers an ARX command.
void AddCommand(const char* cmdGroup, const char* cmdInt, const char* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal = -1);

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_MSG
void InitApplication();
void UnloadApplication();
//}}AFX_ARX_MSG

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_ADDIN_FUNCS
void RegisterArxApp();
char ThisAppRegistryPath[] = { "Software\\Autodesk\\ObjectARX\\3.0\\SampleApps\\Smiley" };
//}}AFX_ARX_ADDIN_FUNCS

class CSmileyUiApp : public CWinApp
{
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmileyUiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSmileyUiApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CSmileyUiApp, CWinApp)
	//{{AFX_MSG_MAP(CSmileyUiApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CSmileyUiApp theApp;

BOOL CSmileyUiApp::InitInstance()
{
	InitAcUiDLL();
	return CWinApp::InitInstance();
}

bool isModuleLoaded(const char* str)
{
	AcDbVoidPtrArray* pApps = reinterpret_cast<AcDbVoidPtrArray*>(acrxLoadedApps());
	if (pApps==NULL)
		return false;
	bool bFound = false;
	for (int i=0;i<pApps->length();i++)
	{
		if (stricmp(reinterpret_cast<const char*>(pApps->at(i)),str)==0)
		{
			bFound = true;
			break;
		}
	}
	for (;pApps->length()>0;)
	{
		delete reinterpret_cast<char*>(pApps->at(0));
		pApps->removeAt(0);
	}
	delete pApps;
	return bFound;
}

/////////////////////////////////////////////////////////////////////////////
// ObjectARX EntryPoint
extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	AcRxDynamicLinker *pLinker = acrxDynamicLinker;
	switch (msg) {
	case AcRx::kInitAppMsg:
		// Comment out the following line if your
		// application should be locked into memory
		pLinker->unlockApplication(pkt);
		pLinker->registerAppMDIAware(pkt);
		// check if the arx app is loaded or not.
		// if not, load it as UI so that we won't have
		// proxy if this dll is unloaded by OS
		if (!isModuleLoaded("AsdkSmileyDb.dbx"))
		{
			if (!pLinker->loadModule("AsdkSmileyDb.dbx", false, true))
				return AcRx::kRetError;
		}
		// bump the reference count 
		pLinker->loadModule("AsdkSmileyDb.dbx", false, false);
		InitApplication();
		break;
	case AcRx::kUnloadAppMsg:
		pLinker->unloadModule("AsdkSmileyDb.dbx");
		UnloadApplication();
		break;
	}
	return AcRx::kRetOK;
}


// Init this application. Register your
// commands, reactors...
void InitApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_INIT
	AddCommand("ASDK_SMILEY", "ASDK_SMILEY", "SMILEY", ACRX_CMD_MODAL, createSmiley);
	RegisterArxApp();
	//}}AFX_ARX_INIT
}

// Unload this application. Unregister all objects
// registered in InitApplication.
void UnloadApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_EXIT
	acedRegCmds->removeGroup("ASDK_SMILEY");
	//}}AFX_ARX_EXIT
}

// This functions registers an ARX command.
// It can be used to read the localized command name
// from a string table stored in the resources.
void AddCommand(const char* cmdGroup, const char* cmdInt, const char* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal)
{
	char cmdLocRes[65];

	// If idLocal is not -1, it's treated as an ID for
	// a string stored in the resources.
	if (idLocal != -1) {
		HMODULE hModule = GetModuleHandle("AsdkSmileyUi.arx");

		// Load strings from the string table and register the command.
		::LoadString(hModule, idLocal, cmdLocRes, 64);
		acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLocRes, cmdFlags, cmdProc);

	} else
		// idLocal is -1, so the 'hard coded'
		// localized function name is used.
		acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLoc, cmdFlags, cmdProc);
}

// This function registers this ObjectARX Application
// on AutoCAD for demandload and in the
// Windows Registry.
void RegisterArxApp()
{
	int strLength;
	HMODULE hModule = GetModuleHandle("AsdkSmileyUi.arx");

	if (!hModule)
		return;

	//
	// Register the application.
	//

	acrxRegisterApp((AcadApp::LoadReasons) (AcadApp::kOnCommandInvocation |
	                                        AcadApp::kOnLoadRequest |
	                                        AcadApp::kTransparentlyLoadable),
	                "AsdkSmileyUi",
	                ThisAppRegistryPath, 2);

	//
	// Create the registry key for this application
	// (use the variable ThisAppRegistryPath).
	//

	HKEY rkey;
	DWORD result;
	LONG status = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
	                             ThisAppRegistryPath,
	                             0, "",
	                             REG_OPTION_NON_VOLATILE,
	                             KEY_WRITE, NULL, &rkey, &result);
	if (ERROR_SUCCESS != status)
		return;

	HKEY prodKey;
	status = RegCreateKeyEx(rkey, "AsdkSmileyUi", 0, "",
	                        REG_OPTION_NON_VOLATILE,
	                        KEY_WRITE, NULL, &prodKey, &result);
	RegCloseKey(rkey);
	if (ERROR_SUCCESS != status)
		return;

	// Create the 'Commands' key.
	HKEY commandKey;
	status = RegCreateKeyEx(prodKey, "Commands", 0, "",
	                        REG_OPTION_NON_VOLATILE,
	                        KEY_WRITE, NULL, &commandKey, &result);
	if (ERROR_SUCCESS == status) {
		RegSetValueEx(commandKey, "ASDK_SMILEY", 0, REG_SZ,
			          (const unsigned char*) "SMILEY", 7);
		RegCloseKey(commandKey);
	}

	// Create the 'Groups' key.
	HKEY groupKey;
	status = RegCreateKeyEx(prodKey, "Groups", 0, "",
	                        REG_OPTION_NON_VOLATILE,
	                        KEY_WRITE, NULL, &groupKey, &result);
	if (ERROR_SUCCESS == status) {
		RegSetValueEx(groupKey, "ASDK_SMILEY", 0, REG_SZ,
			          (const unsigned char*) "ASDK_SMILEY", 12);
		RegCloseKey(groupKey);
	}

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
		RegSetValueEx(nameKey, "AsdkSmileyUi", 0, REG_SZ,
		              (const unsigned char*) "AsdkSmileyUi", 13);
		RegCloseKey(nameKey);
	}

	//
	// Finished.
	//

	RegCloseKey(prodKey);
}

