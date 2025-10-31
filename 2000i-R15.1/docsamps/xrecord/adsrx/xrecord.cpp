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
//    xrecord.cpp
//
// This program demonstrates how to use ADS to work with xrecords.
// There are two commands defined through LISP: create,  and listxrec.
//
// The create command calls the function createXrecord which creates
// an xrecord,  adds some data to it,  and adds it to a dictionary in
// the named objects dictionary.
//
// The listxrec command calls the function listXrecord which finds the
// xrecord created by the create command and then sends the data list
// of this xrecord to the printList function to be listed out.


#include  <stdio.h>
#include  "rxregsvc.h"
#include  "adslib.h"
#include  "rxdefs.h"

#define ELEMENTS(array) (sizeof(array)/sizeof((array)[0]))


//  local function prototypes

int      dofun         (void);
int      funcload      (void);
int      createXrecord ();
int      listXrecord   ();
int      printList     (struct resbuf* pBuf);


//  LISP registered functions list structure

struct func_entry { char *func_name; int (*func) (); };
static struct func_entry func_table[] = {{"c:asdk_ads_create", createXrecord},
                                         {"c:asdk_ads_listxrec", listXrecord}};

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


// Define this application's external functions.  Return
// RTERROR on error, else RTNORM.
//
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


// Execute external function (called upon an RQSUBR request).  
// Return value from the function executed, RTNORM or RTERROR.

static int
dofun()
{
    int val;

    // Get the function code and check that it's within range.
    //   (It can't fail to be, but paranoia doesn't hurt.)
    //
    if ((val = acedGetFunCode()) < 0 || val >= ELEMENTS(func_table)) {
        acdbFail("Received nonexistent function code.");
        return RTERROR;
    }

    // Call the handler and return its success-failure status.
    //
    return (*func_table[val].func)();
}


// Creates an xrecord,  fills it in with some data,  and
// adds it to the dictionary associated with the key
// "TEST_REC".  If this dictionary doesn't exist,  it's
// created and added to the named objects dictionary.
//
// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.
//
int
createXrecord()
{
    struct resbuf *pXrec, *pDict;
    ads_point testpt = {1.0, 2.0, 0.0};
    ads_name xrecname, namedObj, dictName;

    // Within the named object dictionary, attempt to get
    // the dictionary associated with the key ASDK_DICT.
    // If not present, create it.
    // 
    acdbNamedObjDict(namedObj);
    pDict = acdbDictSearch(namedObj, "ASDK_DICT", 0);
    if (pDict == NULL) {
        pDict = acutBuildList(RTDXF0, "DICTIONARY", 100,
            "AcDbDictionary", 0);
        acdbEntMakeX(pDict, dictName);
        acutRelRb(pDict);
        acdbDictAdd(namedObj, "ASDK_DICT", dictName);
    }
        
    // Create a resbuf list of the xrecord's entity data.
    //
    pXrec = acutBuildList(RTDXF0, "XRECORD",
        100, "AcDbXrecord",
        1, "This is a test Xrecord list", //AcDb::kDxfText
        10, testpt,                       //AcDb::kDxfXCoord
        40, 3.14159,                      //AcDb::kDxfReal
        50, 3.14159,                      //AcDb::kDxfAngle
        60, 1,                            //AcDb::kDxfColor
        70, 180,                          //AcDb::kDxfInt16
        0);

    // Create the xrecord with no owner set.  Place the
    // xrecord's new entity name into the xrecname argument.
    //
    acdbEntMakeX (pXrec, xrecname);
    acutRelRb (pXrec);

    // Set xrecord's owner to be the ASDK_DICT dictionary.
    //
    acdbDictAdd(dictName, "XRECADS", xrecname);

    acedRetVoid();
    return RTNORM;
}

// Accesses the xrecord associated with the key XRECADS in
// the dictionary associated the key TEST_DICT.  Then
// lists out the contents of this xrecord using the
// printList function.
// 
int
listXrecord()
{
    struct resbuf *pObj;
    ads_name dictName;

    // Get the entity name of the ASDK_DICT dictionary in
    // the named object dictionary and place it in dictName.
    //
    acdbNamedObjDict(dictName);
    pObj = acdbDictSearch(dictName, "ASDK_DICT", 0);
    if (pObj) {
        // The entity name is always returned in first resbuf.
        //
        ads_name_set(pObj->resval.rlname, dictName);
    }

    // Get the xrecord associated with the key XRECADS.
    //
    pObj = acdbDictSearch(dictName, "XRECADS", 0);

    if (pObj) {
        printList(pObj);
        acutRelRb(pObj);
    }
    acedRetVoid();
    return RTNORM;
}

// END CODE APPEARING IN SDK DOCUMENT.

// accepts a list of resbufs and prints out the values they contain
//
int
printList(struct resbuf* pBuf)
{
    int rt, i;
    char buf[133];     // should only need 1 byte for <return>, but
                       // play it safe since ads_getstring can accept
                       // up to 132 characters

    for (i = 0;pBuf != NULL;i++, pBuf = pBuf->rbnext)
    {
        if (pBuf->restype < 0)
            rt = pBuf->restype;           // Entity name (or other sentinel)
        else if (pBuf->restype < 10)
            rt = RTSTR;
        else if (pBuf->restype < 38)
            rt = RT3DPOINT;
        else if (pBuf->restype < 60)
            rt = RTREAL;
        else if (pBuf->restype < 80)
            rt = RTSHORT;
        else if (pBuf->restype < 100)
            rt = RTLONG;
        else if (pBuf->restype < 106)
            rt = RTSTR;
        else if (pBuf->restype < 148)
            rt = RTREAL;
        else if (pBuf->restype < 290)
            rt = RTSHORT;
        else if (pBuf->restype < 320)
            rt = RTSTR;
        else if (pBuf->restype < 370)
            rt = RTENAME;
        else if (pBuf->restype < 999)
            rt = RT3DPOINT;
        else                       // pBuf->restype is already RTSHORT, RTSTR,
            rt = pBuf->restype;      // etc. or else it is unknown.

        switch (rt) {
        case RTSHORT:
            if (pBuf->restype == RTSHORT)
                acutPrintf("RTSHORT : %d\n", pBuf->resval.rint);
            else
                acutPrintf("(%d . %d)\n", pBuf->restype, pBuf->resval.rint);
            break;
        case RTREAL:
            if (pBuf->restype == RTREAL)
                acutPrintf("RTREAL : %0.3f\n", pBuf->resval.rreal);
            else
                acutPrintf("(%d . %0.3f)\n", pBuf->restype, pBuf->resval.rreal);
            break;
        case RTSTR:
            if (pBuf->restype == RTSTR)
                acutPrintf("RTSTR : %s\n", pBuf->resval.rstring);
            else
                acutPrintf("(%d . \"%s\")\n", pBuf->restype, pBuf->resval.rstring);
            break;
        case RT3DPOINT:
            if (pBuf->restype == RT3DPOINT)
                acutPrintf("RT3DPOINT : %0.3f, %0.3f, %0.3f\n",
                pBuf->resval.rpoint[X],  pBuf->resval.rpoint[Y],
                    pBuf->resval.rpoint[Z]);
            else
                acutPrintf("(%d %0.3f %0.3f %0.3f)\n", pBuf->restype,
                    pBuf->resval.rpoint[X], pBuf->resval.rpoint[Y],
                    pBuf->resval.rpoint[Z]);
            break;
        case RTLONG:
            acutPrintf("RTLONG : %dl\n", pBuf->resval.rlong);
            break;
        case -1:
        case RTENAME:                          // First block entity
            acutPrintf("(%d . <Entity name: %8lx>)\n", pBuf->restype,
                pBuf->resval.rlname[0]);
            break;
        case -3:                              // marks start of xdata
            acutPrintf("(-3)\n");
        }

        if ((i == 23) && (pBuf->rbnext != NULL)) {
            i = 0;
            acedGetString(0,"Press <ENTER> to continue...", buf);
        }
    }
    return RTNORM;
}
