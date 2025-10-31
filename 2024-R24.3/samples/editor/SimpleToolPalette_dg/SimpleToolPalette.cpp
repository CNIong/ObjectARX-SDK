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
//-----------------------------------------------------------------------------
//----- SimpleToolPalette.cpp : Initialization functions
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "resource.h"
#include <initguid.h>
#include "SimpleToolPalette_i.h"
#include <afxdllx.h>
#include "SimpleToolPalette_i.c"
#include "acadi_i.c"
#include "AcExtensionModule.h"
#include "adui.h"
#include "acui.h"

//-----------------------------------------------------------------------------
class CSimpleToolPaletteModule : public CAtlDllModuleT<CSimpleToolPaletteModule> {

public :
	DECLARE_LIBID(LIBID_asdkSimpleToolPaletteLib)
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SIMPLETOOLPALETTE, "{031BF2BB-90B5-4890-9385-CC98D11D76E0}")
} ;

CSimpleToolPaletteModule _AtlModule ;

//-----------------------------------------------------------------------------
//----- Define the sole extension module object.
AC_IMPLEMENT_EXTENSION_MODULE(SimpleToolPaletteDLL)
//- Please do not remove the 3 following lines. These are here to make .NET MFC Wizards
//- running properly. The object will not compile but is require by .NET to recognize
//- this project as being an MFC project
#ifdef NEVER
AFX_EXTENSION_MODULE SimpleToolPaletteExtDLL ={ NULL, NULL } ;
#endif

//----- Now you can use the CAcModuleResourceOverride class in
//----- your application to switch to the correct resource instance.
//----- Please see the ObjectARX Documentation for more details

//-----------------------------------------------------------------------------
//----- DLL Entry Point
extern "C"
BOOL WINAPI DllMain (HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
	//----- Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved) ;

	if ( dwReason == DLL_PROCESS_ATTACH ) {
        _hdllInstance =hInstance ;
		SimpleToolPaletteDLL.AttachInstance (hInstance) ;
		InitAcUiDLL () ;
	} else if ( dwReason == DLL_PROCESS_DETACH ) {
		SimpleToolPaletteDLL.DetachInstance () ;
	}
	return (_AtlModule.DllMain (dwReason, lpReserved)) ;
}

//-----------------------------------------------------------------------------
//----- Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow (void) {
	return ((_AtlModule.GetLockCount () == 0) ? S_OK : S_FALSE) ;
}

//-----------------------------------------------------------------------------
//----- Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject (REFCLSID rclsid, REFIID riid, LPVOID *ppv) {
	return (_AtlModule.GetClassObject (rclsid, riid, ppv)) ;
}

//-----------------------------------------------------------------------------
//----- DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer (void) {
	//----- Registers object, typelib and all interfaces in typelib
	return (_AtlModule.RegisterServer (TRUE)) ;
}

//-----------------------------------------------------------------------------
//----- DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer (void) {
	return (_AtlModule.UnregisterServer (TRUE)) ;
}

