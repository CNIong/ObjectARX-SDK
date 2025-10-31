//
// (C) Copyright 1999-2007 by Autodesk, Inc. 
//
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

// AsdkDesignCenterSamp.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f AsdkDesignCenterSampps.mk in the project directory.

#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "resource.h"
#include <initguid.h>
#include "AsdkDesignCenterSamp_i.h"

#include "AsdkDesignCenterSamp_i.c"
#include "AsdkDcContent.h"



CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_AsdkDcContent, CAsdkDcContent)
END_OBJECT_MAP()

void registerAppInfo(HINSTANCE hInstance)
{
    USES_CONVERSION;
    HRESULT hRes = S_OK;

    CComPtr<IRegistrar> p;
    hRes = CoCreateInstance(CLSID_Registrar, NULL,
        CLSCTX_INPROC_SERVER, IID_IRegistrar, (void**)&p);

    if(SUCCEEDED(hRes))
    {
        // Get the AutoCAD Product key from the registry into a CString.
        CString csProdKey = acrxProductKey();
        
        // replace the run-time strings...
        TCHAR szRegKey[MAX_PATH];
        _tcscpy(szRegKey, csProdKey);
        const TCHAR *pszDelimiter = _T("\\");
        TCHAR *pszToken = _tcstok(szRegKey, pszDelimiter);
        const TCHAR *pszIds[] = 
        {
            _T("RELEASE"), _T("AUTH")
        };

        pszToken = _tcstok(NULL, pszDelimiter);
        pszToken = _tcstok(NULL, pszDelimiter);
        pszToken = _tcstok(NULL, pszDelimiter);

        int nCount = 0;
        while(NULL != pszToken) {
            p->AddReplacement(CT2OLE(pszIds[nCount]), CT2OLE(pszToken));
            pszToken = _tcstok(NULL, pszDelimiter);
            if(NULL == pszToken)
                break;
            nCount++;
        }

        _TCHAR szModule[_MAX_PATH];
        GetModuleFileName(hInstance, szModule, _MAX_PATH);
        LPCOLESTR szType = OLESTR("REGISTRY");
        LPOLESTR pszModule = T2OLE(szModule);

        // Pull the registry entries from the resource ID.
        hRes = p->ResourceRegister(pszModule, IDR_REGISTRY1, szType);

        if(FAILED(hRes)) 
            AfxMessageBox(_T("Error registering the app info."));
    }
}

class CAsdkDesignCenterSampApp : public CWinApp
{
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAsdkDesignCenterSampApp)
    public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CAsdkDesignCenterSampApp)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CAsdkDesignCenterSampApp, CWinApp)
    //{{AFX_MSG_MAP(CAsdkDesignCenterSampApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CAsdkDesignCenterSampApp theApp;

BOOL CAsdkDesignCenterSampApp::InitInstance()
{
    _Module.Init(ObjectMap, m_hInstance, &LIBID_ASDKDESIGNCENTERSAMPLib);

    registerAppInfo(m_hInstance);
    DllRegisterServer();

    return CWinApp::InitInstance();
}

int CAsdkDesignCenterSampApp::ExitInstance()
{
    _Module.Term();
    return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
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
    return _Module.UnregisterServer(TRUE);
}


extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch(msg)
    {
    case AcRx::kInitAppMsg:
        acrxRegisterAppMDIAware(appId);
        break;
    case AcRx::kUnloadAppMsg:
        break;
    default:
        break;
    }
    
    return AcRx::kRetOK;
}
