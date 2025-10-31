//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#include "StdAfx.h"


#include "StdArx.h"
#include "resource.h"
#include <afxdllx.h>



HINSTANCE _hdllInstance =NULL ;

// This command registers an ARX command.
void AddCommand(const ACHAR* cmdGroup, const ACHAR* cmdInt, const ACHAR* cmdLoc,
                const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal = -1);

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_MSG
void InitApplication();
void UnloadApplication();
//}}AFX_ARX_MSG

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_ADDIN_FUNCS
//}}AFX_ARX_ADDIN_FUNCS

////////////////////////////////////////////////////////////////////////////
//
// Define the sole extension module object.
AC_IMPLEMENT_EXTENSION_MODULE(HlrArxSampleDLL);

// Now you can use the CAcModuleRecourceOverride class in
// your application to switch to the correct resource instance.
// Please see the ObjectARX Documentation for more details

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _hdllInstance = hInstance;
        // Extension DLL one time initialization
        HlrArxSampleDLL.AttachInstance(hInstance);
        InitAcUiDLL();
    } else if (dwReason == DLL_PROCESS_DETACH) {
        // Terminate the library before destructors are called
        HlrArxSampleDLL.DetachInstance();
    }
    return TRUE;    // ok
}

static const TCHAR acGeomentObjDbxFile[] = _T("AcGeomentObj.dbx");

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
        acrxLoadModule(acGeomentObjDbxFile, 0);
        InitApplication();
        break;
    case AcRx::kUnloadAppMsg:
        UnloadApplication();
        acrxUnloadModule(acGeomentObjDbxFile);
        break;
    }
    return AcRx::kRetOK;
}


// Init this application. Register your
// commands, reactors...
void InitApplication()
{
    //{{AFX_ARX_INIT
    AddCommand(ACRX_T("ASDK"), ACRX_T("TEST1"), ACRX_T("TEST1"), ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdktest1);
    AddCommand(ACRX_T("ASDK"), ACRX_T("TEST2"), ACRX_T("TEST2"), ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdktest2);
    AddCommand(ACRX_T("ASDK"), ACRX_T("TEST3"), ACRX_T("TEST3"), ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdktest3);
    AddCommand(ACRX_T("ASDK"), ACRX_T("TEST4"), ACRX_T("TEST4"), ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdktest4);
    AddCommand(ACRX_T("ASDK"), ACRX_T("TEST5"), ACRX_T("TEST5"), ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdktest5);
    AddCommand(ACRX_T("ASDK"), ACRX_T("TEST6"), ACRX_T("TEST6"), ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdktest6);
    //}}AFX_ARX_INIT

    // TODO: add your initialization functions

    //----- We need the HLR engine loaded
    if ( !acrxServiceIsRegistered (AsdkHlrApiServiceName) )
        acrxLoadModule (ACRX_T(/*NOXLATE*/"AsdkHlrApi23.dbx"), false, true) ;
    //----- bump the reference count
    acrxLoadModule (ACRX_T(/*NOXLATE*/"AsdkHlrApi23.dbx"), false, false) ;

}

// Unload this application. Unregister all objects
// registered in InitApplication.
void UnloadApplication()
{
    //{{AFX_ARX_EXIT
    acedRegCmds->removeGroup(ACRX_T("ASDK"));
    //}}AFX_ARX_EXIT

    // TODO: clean up your application
    acrxUnloadModule (ACRX_T(/*NOXLATE*/"AsdkHlrApi23.dbx")) ;
}

// This functions registers an ARX command.
// It can be used to read the localized command name
// from a string table stored in the resources.
void AddCommand(const ACHAR* cmdGroup, const ACHAR* cmdInt, const ACHAR* cmdLoc,
                const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal)
{
    ACHAR cmdLocRes[65];

    // If idLocal is not -1, it's treated as an ID for
    // a string stored in the resources.
    if (idLocal != -1) {

        // Load strings from the string table and register the command.
        ::LoadString(_hdllInstance, idLocal, cmdLocRes, 64);
        acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLocRes, cmdFlags, cmdProc);

    } else
        // idLocal is -1, so the 'hard coded'
        // localized function name is used.
        acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLoc, cmdFlags, cmdProc);
}
