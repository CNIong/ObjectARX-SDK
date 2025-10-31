//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <Windows.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbxutil.h>
#include <acprofile.h>
#include <adslib.h>
#include "tchar.h"



// Define a class derived from AcApProfileManagerReactor to manage 
// the notifications.
//
class AsdkProfileManagerReactor : public AcApProfileManagerReactor
{
public:
    void currentProfileWillChange(const TCHAR *newProfile);
    void currentProfileChanged(const TCHAR *newProfile);
    void currentProfileWillBeReset(const TCHAR *curProfile);
    void currentProfileReset(const TCHAR *curProfile);
    void profileWillReset(const TCHAR *profName);
    void profileReset(const TCHAR *proName);
};

// Define the notification functions
//
void 
AsdkProfileManagerReactor::
currentProfileWillChange(const TCHAR *newProfile)
{
    acutPrintf(_T("\nCurrent profile will change: %s"), newProfile);
}

void 
AsdkProfileManagerReactor::
currentProfileChanged(const TCHAR *newProfile)
{
    acutPrintf(_T("\nCurrent profile changed: %s"), newProfile);
}

void 
AsdkProfileManagerReactor::
currentProfileWillBeReset(const TCHAR *curProfile)
{
    acutPrintf(_T("\nCurrent profile will be reset: %s"), curProfile);
}

void 
AsdkProfileManagerReactor::
currentProfileReset(const TCHAR *curProfile)
{
    acutPrintf(_T("\nCurrent profile has been reset: %s"), curProfile);
}

void 
AsdkProfileManagerReactor::
profileWillReset(const TCHAR *profName)
{
    acutPrintf(_T("\nA non-current profile will be reset: %s"), profName);
}

void 
AsdkProfileManagerReactor::
profileReset(const TCHAR *profName)
{
    acutPrintf(_T("\nA non-current profile has been reset: %s"), profName);
}


void
aFunction()
{
    acutPrintf(_T("This is AsdkProfileSample Test Application...\n"));

    // Attach the reactor for the duration of this command. Normally
    // this would likely be added upon application initialization.
    //
    AsdkProfileManagerReactor *pProfileRector = 
        new AsdkProfileManagerReactor();
    
    acProfileManagerPtr()->addReactor(pProfileRector);

    // Obtain the path for the registry keys and print it out.
    //
    TCHAR *pstrKey;
    acProfileManagerPtr()->ProfileRegistryKey(pstrKey, NULL);

    if (pstrKey != NULL) {
        acutPrintf(_T("\nThe profiles registry key is: %s"), pstrKey);
        acutDelString(pstrKey);
    }

    // Get the list of all profiles in the users configuration
    // and print them out.
    //
    AcApProfileNameArray arrNameList;
    int nProfiles = 
        acProfileManagerPtr()->ProfileListNames(arrNameList);

    acutPrintf(_T("\nNumber of profiles currently ")
        _T("in the user profile list is: %d"), nProfiles);
    for (int i = 0; i < nProfiles; i++)
        acutPrintf(_T("\nProfile name is: %s"), arrNameList[i]);
    
    // Copy the unnamed profile to the AsdkTestProfile
    //
    acProfileManagerPtr()->ProfileCopy(_T("AsdkTestProfile"), 
                                       _T("<<Unnamed Profile>>"), 
                                       _T("This is a test"));

    // Reset the newly copied profile to AutoCAD defualts.
    //
    acProfileManagerPtr()->ProfileReset(_T("AsdkTestProfile"));

    // Make this new profile current.
    //
    acProfileManagerPtr()->ProfileSetCurrent(_T("AsdkTestProfile"));
    
    // Change a value in the profile. We'll just make the 
    // cursor big.
    //
    struct resbuf rbCursorSize;
    rbCursorSize.restype = RTSHORT;
    rbCursorSize.resval.rint = 100;
    acedSetVar(_T("CURSORSIZE"), &rbCursorSize);

    // Rename the profile to a new name.
    //
    acProfileManagerPtr()->ProfileRename(_T("AsdkTestProfile2"), 
                                         _T("AsdkTestProfile"), 
                                         _T("This is another test"));

    // Export the profile.
    //
    acProfileManagerPtr()->ProfileExport(_T("AsdkTestProfile2"), 
                                         _T("./AsdkTestProfile2.arg"));

    // Import the profile.
    // 
    acProfileManagerPtr()->ProfileImport(_T("AsdkTestProfile3"), 
                                         _T("./AsdkTestProfile2.arg"), 
                                         _T("This is a copy of AsdkTestProfile2")
                                         _T("by Exporting/Importing"), 
                                         Adesk::kTrue);

    // Remove the reactor.
    //
    acProfileManagerPtr()->removeReactor(pProfileRector);

}

void
initApp()
{
    acutPrintf(_T("AsdkProfileSample ARX Test; Type ProfileSample to execute"));
    
    // register a command with the AutoCAD command mechanism
    //
    acedRegCmds->addCommand(_T("AsdkProfileSample_COMMANDS"), _T("AsdkProfileSample"), _T("ProfileSample"), ACRX_CMD_MODAL, aFunction);

}


void unloadApp()
{
    
    
    // Remove the command group added via acedRegCmds->addCommand
    //
    acedRegCmds->removeGroup(_T("AsdkProfileSample_COMMANDS"));

}

extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
        acrxDynamicLinker->registerAppMDIAware(appId);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
        break;
    case AcRx::kLoadDwgMsg:

        break;
    case AcRx::kUnloadDwgMsg:

        break;
    case AcRx::kInvkSubrMsg:

        break;
    default:
        ;
    }
    return AcRx::kRetOK;
}

