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
// xtsndict.cpp
//
// This program demonstrates using extension dictionaries.  Two
// commands are defined in this program:  CREATE,  and LISTXREC.
//
// The CREATE command calls the function createXrecord() which
// instantiates an xrecord object and adds it to the extension
// dictionary of a user selected object.
//
// The LISTXREC command calls the listXrecord() function which
// opens the extension dictionary of a user selected object,
// looks for the xrecord created by the CREATE command and then
// calls the printList() function to print out the data stored
// in the xrecord.

/* here's what a line entity with an extension dictionary looks
like:

((-1 . <Entity name: 2bb0540>) (0 . "LINE") (5 . "28") (102 . 
"{ACAD_XDICTIONARY") (360 . <Entity name: 2bb0548>) (102 . "}") (100 . 
"AcDbEntity") (67 . 0) (8 . "0") (100 . "AcDbLine") (10 7.10996 7.56859 0.0) 
(11 11.5349 3.75213 0.0) (210 0.0 0.0 1.0))

here's what the dictionary <Entity name: 2bb0548> looks like:

((-1 . <Entity name: 2bb0548>) (0 . "DICTIONARY") (5 . "29") (100 . 
"AcDbDictionary") (3 . "XREC1") (350 . <Entity name: 2bb0550>))

here's what the Xrecord <Entity name: 2bb0550> looks like:

((-1 . <Entity name: 2bb0550>) (0 . "XRECORD") (5 . "2A") (102 . 
"{ACAD_REACTORS") (330 . <Entity name: 2bb0548>) (102 . "}") (100 . 
"AcDbXrecord") (1 . "This is a test Xrecord list") (10 1.0 2.0 0.0) (40 . 
3.14159) (50 . 3.14159) (62 . 1) (70 . 180))

*/


#include  <stdio.h>
#include  <string.h>

#include "rxregsvc.h"
#include  "adslib.h"

#include  "rxdefs.h"

#define ELEMENTS(array) (sizeof(array)/sizeof((array)[0]))


//  local function prototypes

int      dofun         (void);
int      funcload      (void);
int      createXrecord ();
int      listXrecord   ();
int      printList     (struct resbuf*);


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


// Allows the user to select an entity.  It then checks to
// see if the selected entity has an extension dictionary.
// If not,  it creates one and adds it to the entity.  It
// then creates an xrecord,  fills it in with some data,
// and adds it to the extension dictionary associated with
// the key "ASDK_XRECADS".
// 
// This function assumes that if an extension dictionary
// already exists it does not have an entry with the key
// "ASDK_XRECADS".
// 
// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.
//
int
createXrecord()
{
    struct resbuf *pXrec, *pEnt, *pDict, *pTemp, *pTemp2;
    ads_point dummy, testpt = {1.0, 2.0, 0.0};
    ads_name xrecname, ename, extDict = {0L, 0L};

    // Have the user select an entity.  Then get its data.
    //
    if (acedEntSel("\nselect entity: ", ename, dummy)
        != RTNORM)
    {
        acutPrintf("\nNothing selected");
        acedRetVoid();
        return RTNORM;
    }
    pEnt = acdbEntGet(ename);

    // Now check to see if the entity already has an
    // extension dictionary.
    //
    for (pTemp = pEnt; pTemp->rbnext != NULL;
        pTemp = pTemp->rbnext)
    {
        if (pTemp->restype == 102) {
            if (!strcmp("{ACAD_XDICTIONARY",
                pTemp->resval.rstring))
            {
                ads_name_set(pTemp->rbnext->resval.rlname, extDict);
                break;
            }
        }
    }

    // If no extension dictionary exists, add one.
    //
    if (extDict[0] == 0L) {
        pDict = acutBuildList(RTDXF0, "DICTIONARY", 100,
            "AcDbDictionary", 0);
        acdbEntMakeX(pDict, extDict);
        acutRelRb(pDict);
        pDict = acutBuildList(102, "{ACAD_XDICTIONARY", 360,
            extDict, 102, "}", 0);
        for (pTemp = pEnt; pTemp->rbnext->restype != 100;
            pTemp = pTemp->rbnext)
            { ; }
        for (pTemp2 = pDict; pTemp2->rbnext != NULL;
            pTemp2 = pTemp2->rbnext)
            { ; }
        pTemp2->rbnext = pTemp->rbnext;
        pTemp->rbnext = pDict;

        acdbEntMod(pEnt);
        acutRelRb(pEnt);
    }
    
    // At this point the entity has an extension dictionary.
    // Create a resbuf list of the xrecord's entity information
    // and data.
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

    // Create the xrecord with no owner set.  The xrecord's
    // new entity name will be placed into the xrecname
    // argument.
    //
    acdbEntMakeX (pXrec, xrecname);
    acutRelRb (pXrec);

    // Set the xrecord's owner to the extension dictionary
    //
    acdbDictAdd(extDict, "ASDK_XRECADS", xrecname);

    acedRetVoid();
    return RTNORM;
}


// Accesses the xrecord associated with the key ASDK_XRECADS in
// the extension dictionary of a user-selected entity.  Then
// list out the contents of this xrecord using the printList
// function.
//
int
listXrecord()
{
    struct resbuf *pXrec, *pEnt, *pTemp;
    ads_point dummy;
    ads_name ename, extDict = {0L, 0L};

    // Have the user select an entity; then get it's data.
    //
    if (acedEntSel("\nselect entity: ", ename, dummy) != RTNORM) {
        acutPrintf("\nNothing selected");
        acedRetVoid();
        return RTNORM;
    }
    pEnt = acdbEntGet(ename);

    // Get the entity name of the extension dictionary.
    //
    for (pTemp = pEnt;pTemp->rbnext != NULL;pTemp = pTemp->rbnext) {
        if (pTemp->restype == 102) {
            if (!strcmp("{ACAD_XDICTIONARY", pTemp->resval.rstring)) {
                ads_name_set(pTemp->rbnext->resval.rlname, extDict);
                break;
            }
        }
    }

    if (extDict[0] == 0L) {
        acutPrintf("\nNo extension dictionary present.");
        return RTNORM;
    }

    pXrec = acdbDictSearch(extDict, "ASDK_XRECADS", 0);

    if(pXrec) {
        printList(pXrec);
        acutRelRb(pXrec);
    }
    acedRetVoid();
    return RTNORM;
}

// END CODE APPEARING IN SDK DOCUMENT.

// accepts a list of resbufs and prints out the values they contain
//
int
printList(struct resbuf *pBuf)
{
    int rt, i;
    char buf[133];     // should only need 1 byte for <return>, but
                       // play it safe since ads_getstring can accept
                       // up to 132 characters

    acutPrintf("\n");  // to make sure we start on a new line
    
    for (i = 0;pBuf != NULL;i++, pBuf = pBuf->rbnext)
    {
        if (pBuf->restype < 0)
            rt = pBuf->restype;         // Entity name (or other sentinel)
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
        else                      // pBuf->restype is already RTSHORT,
            rt = pBuf->restype;   // RTSTR, etc. or else it is unknown.

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
                acutPrintf("(%d . %0.3f)\n", pBuf->restype
                    , pBuf->resval.rreal);
            break;
        case RTSTR:
            if (pBuf->restype == RTSTR)
                acutPrintf("RTSTR : %s\n", pBuf->resval.rstring);
            else
                acutPrintf("(%d . \"%s\")\n", pBuf->restype
                    , pBuf->resval.rstring);
            break;
        case RT3DPOINT:
            if (pBuf->restype == RT3DPOINT)
                acutPrintf("RT3DPOINT : %0.3f, %0.3f, %0.3f\n",
                    pBuf->resval.rpoint[X],  pBuf->resval.rpoint[Y]
                    , pBuf->resval.rpoint[Z]);
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
