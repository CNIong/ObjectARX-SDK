//
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

// SmileyDbCom.cpp : Initialization functions

// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f SmileyDbComps.mk in the project directory.

#include "StdAfx.h"
#include "StdArx.h"
#include "resource.h"
#include <initguid.h>
#include "SmileyDbCom.h"
#include "SmileyDbCom_i.c"
#include "axdb_i.c"
#include "SmileyEntity.h"

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_MSG
//}}AFX_ARX_MSG

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_ADDIN_FUNCS
//}}AFX_ARX_ADDIN_FUNCS

CComModule _Module;

HINSTANCE _hdllInstance = NULL;

BEGIN_OBJECT_MAP(ObjectMap)
    OBJECT_ENTRY(CLSID_SmileyEntity, CSmileyEntity)
END_OBJECT_MAP()


/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    static const char* strAsdkSmileyDb = "AsdkSmileyDb.dbx";

    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _hdllInstance = hInstance;

        _Module.Init(ObjectMap, hInstance, &LIBID_SmileyDb);
        DisableThreadLibraryCalls(hInstance);

        // check if the arx app is loaded or not.
        // if not, load it as UI so that we won't have
        // proxy if this dll is unloaded by OS
        if (!::acrxAppIsLoaded(strAsdkSmileyDb))
        {
            if (!acrxLoadModule(strAsdkSmileyDb, false, true))
                return FALSE; //this will trigger a DLL_PROCESS_DETACH right away
        }
        //bump the reference count 
        acrxLoadModule(strAsdkSmileyDb, false, false);

        DllRegisterServer();

    } else if (dwReason == DLL_PROCESS_DETACH) {
        //try to decrease the refcount on the dbx
        //if we couldn't load it then this a no op.
        acrxUnloadModule(strAsdkSmileyDb);

        _Module.Term();
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
