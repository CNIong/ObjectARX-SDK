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

// SmileyUiCom.cpp : Initialization functions

// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f SmileyUiComps.mk in the project directory.

#include "StdAfx.h"
#include "StdArx.h"
#include "resource.h"
#include <initguid.h>
#include "SmileyUiCom.h"
#include "SmileyUiCom_i.c"
#include "acad15_i.c"
#include "SmileyApplication.h"

CComModule _Module;

HINSTANCE _hdllInstance = NULL;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_SmileyApplication, CSmileyApplication)
END_OBJECT_MAP()

HINSTANCE hArxModule = NULL;

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
// DLL Entry Point
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    static const char* strAsdkSmileyUi = "AsdkSmileyUi.arx";

	if (dwReason == DLL_PROCESS_ATTACH)
	{
        _hdllInstance = hInstance;

		_Module.Init(ObjectMap, hInstance, &LIBID_SmileyUi);
		DisableThreadLibraryCalls(hInstance);

        // check if the arx app is loaded or not.
        // if not, load it as UI so that we won't have
        // proxy if this dll is unloaded by OS
        if (!isModuleLoaded(strAsdkSmileyUi))
        {
            if (!acrxLoadModule(strAsdkSmileyUi, false, true))
 	           return FALSE; //this will trigger a DLL_PROCESS_DETACH right away
        }
        //bump the reference count 
        acrxLoadModule(strAsdkSmileyUi, false, false);
		hArxModule = ::LoadLibrary( strAsdkSmileyUi );

		DllRegisterServer();

	} else if (dwReason == DLL_PROCESS_DETACH) {
		_Module.Term();
		::FreeLibrary( hArxModule );
	}
	return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
	return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
	// Registers object, typelib and all interfaces in typelib
	return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
	return _Module.UnregisterServer(TRUE);
}
