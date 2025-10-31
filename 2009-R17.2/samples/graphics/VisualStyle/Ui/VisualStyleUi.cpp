//
// (C) Copyright 2005-2006 by Autodesk, Inc. 
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

// TO DO: When added to ARX disk spec, tweak IDE settings as follows:
//        1. Remove environment variables from compile & link settings
//        2. Make build target AutoCAD program files directory
//        3. Track down all TO DO's and remove them!
//

// VisualSylteUi.cpp : Initialization functions
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(_FULLDEBUG_)
#define _DEBUG_WAS_DEFINED
#pragma message ("       Compiling MFC /STL /ATL header files in release mode.")
#undef _DEBUG
#endif

#include "resource.h"
#include "VisualStyleJig.h"
#include "VisualStyleCmd.h"

#include "appinfo.h"

#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif

const ACHAR kAppRegPath[] = 
    ACRX_T("Software\\Autodesk\\ObjectARX\\3.0\\SampleApps\\VisualStyle\\");
const ACHAR *kAppName       = ACRX_T("AsdkVisualStyleUi");
const ACHAR *kAppDescr      = ACRX_T("ARX sample app to demonstrate AcDbVisualStyles");
const ACHAR *kGroupName     = ACRX_T("ASDK_VISUALSTYLE");
const ACHAR *kDbxModuleName = ACRX_T("AsdkVisualStyleDb.dbx");


////////////////////////////////////////////////////////////////////////////////
// Register the ARX application command handlers
// (This function can be used to read the localized command name
// from a string table stored in the resources).
//
void AddCommand(const ACHAR* cmdGroup, const ACHAR* cmdInt, const ACHAR* cmdLoc,
                const int cmdFlags, const AcRxFunctionPtr cmdProc, 
                const int idLocal)
{
    // If idLocal is not -1, it's treated as an ID for
    // a string stored in the resources.
    if (idLocal != -1) {
        ACHAR cmdLocRes[65];
        HMODULE hModule = GetModuleHandle(LPCTSTR(ACRX_T("AsdkVisualStyleUi.arx")));

        // Load strings from the string table and register the command.
        ::LoadString(hModule, idLocal, (LPTSTR)cmdLocRes, 64);
        acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLocRes, cmdFlags, cmdProc);

    } else
        // idLocal is -1, so the 'hard coded'
        // localized function name is used.
        acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLoc, cmdFlags, cmdProc);
}

////////////////////////////////////////////////////////////////////////////////
// Register the ARX application commands for demand loading
//
void RegisterArxApp(void)
{
    AcadAppInfo appInfo;

    appInfo.setAppName    (kAppName);                    // Application name
    appInfo.setModuleName (acedGetAppName());            // ARX file location
    appInfo.setAppDesc    (kAppDescr);                   // Description
    appInfo.setLoadReason (AcadApp::LoadReasons(         // Reasons for loading:
                           AcadApp::kOnCommandInvocation //  -command invoked
                         | AcadApp::kOnLoadRequest));    //  -load requested

    appInfo.writeToRegistry(false,true);                 // Commit to registry

    appInfo.writeGroupNameToRegistry   (kGroupName);     // Write group name
    for (int i = 0; i < VisualStyleCmd::kCmdCt; ++i)
        appInfo.writeCommandNameToRegistry (
            VisualStyleCmd::cmdName(i),  // Write command name
            VisualStyleCmd::cmdName(i));   
}

////////////////////////////////////////////////////////////////////////////////
// Initialize this application. Register your commands, reactors...
//
void InitApplication(void)
{
    // Register the command handlers
    for (int i = 0; i < VisualStyleCmd::kCmdCt; ++i)
        AddCommand(kGroupName,                    // Group name
                   VisualStyleCmd::cmdName(i),    // Global command name
                   VisualStyleCmd::cmdName(i),    // Local command name
                   ACRX_CMD_MODAL,                // Command flags
                   VisualStyleCmd::cmdHandler(i), // Command handler function
                   -1);                           // Use localized function name

    // Register for demand loading
    RegisterArxApp();
}


////////////////////////////////////////////////////////////////////////////////
// Unload this application. Unregister all objects registered in 
// InitApplication.
//
void UnloadApplication(void)
{
    acedRegCmds->removeGroup(kGroupName);
}

////////////////////////////////////////////////////////////////////////////////
// ObjectARX entry point
//
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

        // Check if the dbx app is loaded or not. If not, then load it.
        if (!::acrxAppIsLoaded(kDbxModuleName))
            if (!pLinker->loadModule(kDbxModuleName, false, true))
                return AcRx::kRetError;

        // Bump the reference count 
        pLinker->loadModule(kDbxModuleName, false, false);

        InitApplication();
        break;

    case AcRx::kUnloadAppMsg:
        pLinker->unloadModule(kDbxModuleName);

        UnloadApplication();
        break;

    case AcRx::kUnloadDwgMsg:
        VisualStyleCmd::unload();
        break;
    }

    return AcRx::kRetOK;
}
