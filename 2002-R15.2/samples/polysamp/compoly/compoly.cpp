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
// compoly.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//		To build a separate proxy/stub DLL, 
//		run nmake -f compolyps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"

#include "compoly.h"

#include "compoly_i.c"

#include "ComPolygon.h"
#include "poly.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_ComPolygon, CComPolygon)
END_OBJECT_MAP()
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
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_Module.Init(ObjectMap, hInstance);
		DisableThreadLibraryCalls(hInstance);
       // check if the arx app is loaded or not.
 	   // if not, load it as UI so that we won't have
 	   // proxy if this dll is unloaded by OS
 	   if (!isModuleLoaded("asdkpolyobj.dbx"))
       {
            if (!acrxLoadModule("asdkpolyobj.dbx", false, true))
 	           return FALSE; //this will trigger a DLL_PROCESS_DETACH right away
       }
       //bump the reference count 
       acrxLoadModule("asdkpolyobj.dbx", false, false);
 	}
	else if (dwReason == DLL_PROCESS_DETACH)
    {
		_Module.Term();

        //try to decrease the refcount on the dbx
		//if we couldn't load it then this a no op.
		acrxUnloadModule("asdkpolyobj.dbx");
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
	// registers object, typelib and all interfaces in typelib
	return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	_Module.UnregisterServer();
	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
//make this additional entry point available so when user loads
//this dll as an arx it will register itself 
extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt) 
{
	switch (msg) {
	case AcRx::kInitAppMsg:
        //unlock the application
		acrxDynamicLinker->unlockApplication(pkt);
		acrxRegisterAppMDIAware(pkt);
		//register ourselves
        DllRegisterServer();
		break;
	case AcRx::kUnloadAppMsg:
        break;
    case AcRx::kOleUnloadAppMsg :
        //respond to this message according to our current state
        return DllCanUnloadNow()==S_OK?AcRx::kRetOK:AcRx::kRetError;
	}
	return AcRx::kRetOK;
}