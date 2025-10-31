// (C) Copyright 1996,1998 by Autodesk, Inc. 
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
//    ownrshp.cpp
//
// This application demonstrates how to set up an object ownership tree using
// standard ADS.

// In order to show all aspects of this mechanism,  a custom object class
// is used that has two data members one to store an integer (simulating real
// data) and the other stores a hard ownership objectId.

// The custom object is defined in the ARX application "ownrshp.arx" which must
// be loaded as well in order for this program to work.


#include  <stdio.h>
#include  "rxregsvc.h"
#include  "adslib.h"
#include  "rxdefs.h"

#define ELEMENTS(array) (sizeof(array)/sizeof((array)[0]))

struct func_entry { char *func_name; int (*func) (); };
int createObjs();
static struct func_entry func_table[] = {{"c:ads_asdk_create", createObjs}};

//  Declarations of other local functions

int      dofun      (void);
int      funcload   (void);


extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch(msg) {
    case AcRx::kInitAppMsg:
		acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
        break;
    case AcRx::kInvkSubrMsg:
        dofun();
        break;
    case AcRx::kLoadDwgMsg:
        funcload();
    }
    return AcRx::kRetOK;
}


// FUNCLOAD  --  Define this application's external functions.  Return
//               RTERROR on error, else RTNORM.                   

static int 
funcload()
{
    short i;

    for (i = 0; i < ELEMENTS(func_table); i++) {
        if (!acedDefun(func_table[i].func_name, i))
            return RTERROR;
    }
    
    return RTNORM;
}


// DOFUN -- Execute external function (called upon an RQSUBR request).  
//          Return value from the function executed, RTNORM or RTERROR.

static int 
dofun()
{
    int val;

    // Get the function code and check that it's within range.
    // (It can't fail to be, but paranoia doesn't hurt.)
    if ((val = acedGetFunCode()) < 0 || val >= ELEMENTS(func_table)) {
        acdbFail("Received nonexistent function code.");
        return RTERROR;
    }

    // Call the handler and return its success-failure status.
    return (*func_table[val].func)();
}


// Creates an AsdkOwnerDemo object (pObjC) and adds data to
// it.  Next AsdkOwnerDemo pObjC is created and set to be
// the owner of pObjC.  Next AsdkOwnerDemo pObjA is created
// and set to own pObjB.  Finally pObjA is added to a
// dictionary in the named object dictionary.  Technically
// we could just add pObjA to the named object dictionary
// itself,  but that's bad form since it will tend to
// clutter up the named object dictionary.
// 
// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.
//
int 
createObjs()
{
    struct resbuf *pList;
    ads_name enameA, enameB, enameC,
        namedObj, enameTestDict;

    // Create a resbuf list of objC's info and data.  This
    // will include a "dummy" ownership group of 0 since
    // this object won't own any others. The group 70 is the
    // "dummy" integer data value.
    // 
    pList = acutBuildList(RTDXF0, "ASDKOWNERDEMO", 100,
        "AsdkOwnerDemo", 70, 3, 0);

    // Create the object "C" with no owner set.  The
    // object's new entity name will be placed into the
    // objC argument.
    //
    acdbEntMakeX(pList, enameC);
    acutRelRb(pList);

    // Create a resbuf list of objB's info and data.  This
    // will include an ownership group with the entity name
    // of objC.  The group 70 is the "dummy" integer data
    // value.
    // 
    pList = acutBuildList(RTDXF0, "ASDKOWNERDEMO",
        100, "AsdkOwnerDemo", 70, 2, 360, enameC, 0);

    // Create the object "B" with no owner set.  The
    // object's new entity name will be placed into the objC
    // argument
    // 
    acdbEntMakeX(pList, enameB);
    acutRelRb(pList);

    // Create a resbuf list of objA's info and data.  This
    // will include an ownership group with the entity name
    // of objB.  The group 70 is the "dummy" integer data
    // value.
    // 
    pList = acutBuildList(RTDXF0, "ASDKOWNERDEMO",
        100, "AsdkOwnerDemo", 70, 1, 360, enameB, 0);

    // Create the object "A" with no owner set.  The
    // object's new entity name will be placed into the objC
    // argument
    // 
    acdbEntMakeX(pList, enameA);
    acutRelRb(pList);

    // Add object A to a dictionary so it has an owner.

    // Look for the dictionary associated with the key
    // "ASDK_DICT".  If it is not found,  create it and add
    // it to the named object dictionary.
    // 
    acdbNamedObjDict(namedObj);
    if ((pList = acdbDictSearch(namedObj, "ASDK_DICT", 0))
        == NULL)
    {
        pList = acutBuildList(RTDXF0, "DICTIONARY",
            100, "AcDbDictionary", 0);
        acdbEntMakeX (pList, enameTestDict);
        acdbDictAdd(namedObj, "ASDK_DICT", enameTestDict);
    } else {
        // The entity name is always returned in the first resbuf.
        //
        ads_name_set(enameTestDict, pList->resval.rlname);
    }

    // Now add object A to the ASDK_DICT dictionary
    // so it has an owner.
    //
    acdbDictAdd(enameTestDict, "OBJA", enameA);
    acutRelRb(pList);

    acedRetVoid();
    return RTNORM;
}

// END CODE APPEARING IN SDK DOCUMENT.
