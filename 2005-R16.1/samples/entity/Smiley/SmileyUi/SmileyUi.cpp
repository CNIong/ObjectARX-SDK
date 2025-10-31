//
//
// (C) Copyright 2000-2003 by Autodesk, Inc. 
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
#include "appinfo.h"

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
        if (!::acrxAppIsLoaded("AsdkSmileyDb.dbx"))
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
    // Fill the AppInfo structure with our demand loading details.
    AcadAppInfo appInfo;
    appInfo.setAppName("AsdkSmileyUi");// Application Name
    appInfo.setModuleName(acedGetAppName());// ARX File Location
    appInfo.setAppDesc("AsdkSmileyUi Sample"); // Description
    appInfo.setLoadReason( // Specify when we want this to load
        AcadApp::LoadReasons(
        AcadApp::kOnCommandInvocation |
        AcadApp::kOnLoadRequest));
    
    appInfo.writeToRegistry(false,true);// Write the AppInfo to the registry, don't write to DBX registry section.
    appInfo.writeGroupNameToRegistry("ASDK_SMILEY"); // Write the Group Name
    appInfo.writeCommandNameToRegistry("SMILEY","SMILEY");// Write our command.
}
