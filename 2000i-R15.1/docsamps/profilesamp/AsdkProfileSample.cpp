// (C) Copyright 1999 by Autodesk, Inc. 
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


#include <rxregsvc.h>
#include <aced.h>
#include <dbxutil.h>
#include <acprofile.h>
#include <adslib.h>

// Define a class derived from AcApProfileManagerReactor to manage 
// the notifications.
//
class AsdkProfileManagerReactor : public AcApProfileManagerReactor
{
public:
    void currentProfileWillChange(const char *newProfile);
    void currentProfileChanged(const char *newProfile);
    void currentProfileWillBeReset(const char *curProfile);
    void currentProfileReset(const char *curProfile);
    void profileWillReset(const char *profName);
    void profileReset(const char *proName);
};

// Define the notification functions
//
void 
AsdkProfileManagerReactor::
currentProfileWillChange(const char *newProfile)
{
    acutPrintf("\nCurrent profile will change: %s", newProfile);
}

void 
AsdkProfileManagerReactor::
currentProfileChanged(const char *newProfile)
{
    acutPrintf("\nCurrent profile changed: %s", newProfile);
}

void 
AsdkProfileManagerReactor::
currentProfileWillBeReset(const char *curProfile)
{
    acutPrintf("\nCurrent profile will be reset: %s", curProfile);
}

void 
AsdkProfileManagerReactor::
currentProfileReset(const char *curProfile)
{
    acutPrintf("\nCurrent profile has been reset: %s", curProfile);
}

void 
AsdkProfileManagerReactor::
profileWillReset(const char *profName)
{
    acutPrintf("\nA non-current profile will be reset: %s", profName);
}

void 
AsdkProfileManagerReactor::
profileReset(const char *profName)
{
    acutPrintf("\nA non-current profile has been reset: %s", profName);
}


void
aFunction()
{
    acutPrintf("This is AsdkProfileSample Test Application...\n");

    // Attach the reactor for the duration of this command. Normally
    // this would likely be added upon application initialization.
    //
    AsdkProfileManagerReactor *pProfileRector = 
        new AsdkProfileManagerReactor();
    
    acProfileManagerPtr()->addReactor(pProfileRector);

    // Obtain the path for the registry keys and print it out.
    //
    char *pstrKey;
    acProfileManagerPtr()->ProfileRegistryKey(pstrKey, NULL);

    if (pstrKey != NULL) {
        acutPrintf("\nThe profiles registry key is: %s", pstrKey);
        acutDelString(pstrKey);
    }

    // Get the list of all profiles in the users configuration
    // and print them out.
    //
    AcApProfileNameArray arrNameList;
    int nProfiles = 
        acProfileManagerPtr()->ProfileListNames(arrNameList);

    acutPrintf("\nNumber of profiles currently "
        "in the user profile list is: %d", nProfiles);
    for (int i = 0; i < nProfiles; i++)
        acutPrintf("\nProfile name is: %s", arrNameList[i]);
    
    // Copy the unnamed profile to the AsdkTestProfile
    //
    acProfileManagerPtr()->ProfileCopy("AsdkTestProfile", 
                                       "<<Unnamed Profile>>", 
                                       "This is a test");

    // Reset the newly copied profile to AutoCAD defualts.
    //
    acProfileManagerPtr()->ProfileReset("AsdkTestProfile");

    // Make this new profile current.
    //
    acProfileManagerPtr()->ProfileSetCurrent("AsdkTestProfile");
    
    // Change a value in the profile. We'll just make the 
    // cursor big.
    //
    struct resbuf rbCursorSize;
    rbCursorSize.restype = RTSHORT;
    rbCursorSize.resval.rint = 100;
    acedSetVar("CURSORSIZE", &rbCursorSize);

    // Rename the profile to a new name.
    //
    acProfileManagerPtr()->ProfileRename("AsdkTestProfile2", 
                                         "AsdkTestProfile", 
                                         "This is another test");

    // Export the profile.
    //
    acProfileManagerPtr()->ProfileExport("AsdkTestProfile2", 
                                         "./AsdkTestProfile2.arg");

    // Import the profile.
    // 
    acProfileManagerPtr()->ProfileImport("AsdkTestProfile3", 
                                         "./AsdkTestProfile2.arg", 
                                         "This is a copy of AsdkTestProfile2"
                                         "by Exporting/Importing", 
                                         Adesk::kTrue);

    // Remove the reactor.
    //
    acProfileManagerPtr()->removeReactor(pProfileRector);

}

void
initApp()
{
    acutPrintf("AsdkProfileSample ARX Test; Type ProfileSample to execute");
    
    // register a command with the AutoCAD command mechanism
    //
    acedRegCmds->addCommand("AsdkProfileSample_COMMANDS", "AsdkProfileSample", "ProfileSample", ACRX_CMD_MODAL, aFunction);

}


void unloadApp()
{
    
    
    // Remove the command group added via acedRegCmds->addCommand
    //
    acedRegCmds->removeGroup("AsdkProfileSample_COMMANDS");

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

