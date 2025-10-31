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
// DesignCtrSample.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//		To merge the proxy/stub code into the object DLL, add the file 
//		dlldatax.c to the project.  Make sure precompiled headers 
//		are turned off for this file, and add _MERGE_PROXYSTUB to the 
//		defines for the project.  
//
//		If you are not running WinNT4.0 or Win95 with DCOM, then you
//		need to remove the following define from dlldatax.c
//		#define _WIN32_WINNT 0x0400
//
//		Further, if you are running MIDL without /Oicf switch, you also 
//		need to remove the following define from dlldatax.c.
//		#define USE_STUBLESS_PROXY
//
//		Modify the custom build rule for DesignCtrSample.idl by adding the following 
//		files to the Outputs.
//			DesignCtrSample_p.c
//			dlldata.c
//		To build a separate proxy/stub DLL, 
//		run nmake -f DesignCtrSampleps.mk in the project directory.

#include "stdafx.h"

#include <aced.h>
#include <rxregsvc.h>

#include "resource.h"
#include "initguid.h"
#include "DesignCtrSample.h"

#include "DesignCtrSample_i.c"
#include "DesignCtrSampleObject.h"

#ifdef _MERGE_PROXYSTUB
extern "C" HINSTANCE hProxyDll;
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_DesignCtrSampleObject, CDesignCtrSampleObject)
END_OBJECT_MAP()

HINSTANCE _hdllInstance = NULL;
//HINSTANCE ghDllInstance;
static AFX_EXTENSION_MODULE DesignCtrSampleDll = { NULL, NULL};

void registerAppInfo(HINSTANCE hInstance)
{
	USES_CONVERSION;
	HRESULT hRes = S_OK;
	CComPtr<IRegistrar> p;
	hRes = CoCreateInstance(CLSID_Registrar, NULL,
		CLSCTX_INPROC_SERVER, IID_IRegistrar, (void**)&p);
	if(SUCCEEDED(hRes))
	{
		CString csProdKey = acrxProductKey();
		CString csPath = "SOFTWARE\\Autodesk\\AutoCAD\\R15.0\\";
		CString csStamp = csProdKey.Right(csProdKey.GetLength() - csPath.GetLength());

		_TCHAR szRegKey[_MAX_PATH];
        _tcscpy(szRegKey, csStamp);
		LPOLESTR pszId = T2OLE("AUTH");
		// do a runtime swap of the registry key value
        p->AddReplacement(pszId, T2OLE(szRegKey));

		_TCHAR szModule[_MAX_PATH];
		GetModuleFileName(hInstance, szModule, _MAX_PATH);
		LPCOLESTR szType = OLESTR("REGISTRY");
		LPOLESTR pszModule = T2OLE(szModule);

		hRes = p->ResourceRegister(pszModule, IDR_REGISTRY_APP, szType);
		if(FAILED(hRes)) 
			//ReportError(hRes, NULL);
			AfxMessageBox("Error register the app info.");
	}
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
#ifdef _MERGE_PROXYSTUB
	if (PrxDllCanUnloadNow() != S_OK)
		return S_FALSE;
#endif
	return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
#ifdef _MERGE_PROXYSTUB
	if (PrxDllGetClassObject(rclsid, riid, ppv) == S_OK)
		return S_OK;
#endif
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
	HRESULT hRes = PrxDllRegisterServer();
	if (FAILED(hRes))
		return hRes;
#endif
	// registers object, typelib and all interfaces in typelib
	return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
	PrxDllUnregisterServer();
#endif
	_Module.UnregisterServer();
	return S_OK;
}
//
// for MFC initialization
//
extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
		_hdllInstance = hInstance;
		if(!AfxInitExtensionModule(DesignCtrSampleDll, hInstance))
			return 0;
		new CDynLinkLibrary(DesignCtrSampleDll);

		_Module.Init(ObjectMap, hInstance);
		//
		registerAppInfo(hInstance);
		DllRegisterServer();
		break;
	
	case DLL_PROCESS_DETACH:
		AfxTermExtensionModule(DesignCtrSampleDll);
		_Module.Term();
		break;
	}

	return 1;
}
//
//
// 
extern "C" __declspec(dllexport) AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* p)
{
	switch(msg)
	{
	case AcRx::kInitAppMsg:
        acrxRegisterAppMDIAware(p);
		break;
	case AcRx::kUnloadAppMsg:
		break;
	default:
		break;
	}
	return AcRx::kRetOK;
}

// _ATL_NO_UUIDOF