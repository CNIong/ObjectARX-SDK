//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// Description:
//
// This program demonstrates using xrecords.  Two commands
// are defined in this program:  CREATE, and LISTXREC.
// 
// The CREATE command calls the function createXrecord()
// which instantiates an xrecord object and adds it to a
// dictionary object in the named objects dictionary.
// 
// The LISTXREC command calls the listXrecord() function
// which opens the dictionary containing the xrecord created
// by the CREATE command and then calls the printList()
// function to print out the data stored in the xrecord.

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <stdlib.h>
#include <rxobject.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbsymtb.h>
#include <dbapserv.h>
#include <adslib.h>
#include <dbxrecrd.h>
#include "tchar.h"



void createXrecord();
void listXrecord();
void printList(struct resbuf* pBuf);
void initApp();
void unloadApp();
extern "C"
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);


// Creates an xrecord object, adds data to it, and then adds
// the xrecord to a dictionary in the named objects
// dictionary.  Technically we could just add the xrecord to
// the named objects dictionary itself, but that's bad form
// since it will tend to clutter up the named objects
// dictionary.
// 
// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.
//
void
createXrecord()
{
    AcDbDictionary *pNamedobj, *pDict;
    acdbHostApplicationServices()->workingDatabase()
        ->getNamedObjectsDictionary(pNamedobj, AcDb::kForWrite);

    // Check to see if the dictionary we want to create is
    // already present. If not, then create it and add
    // it to the named object dictionary.
    // 
    if (pNamedobj->getAt(_T("ASDK_DICT"), (AcDbObject*&) pDict,
        AcDb::kForWrite) == Acad::eKeyNotFound)
    {
        pDict = new AcDbDictionary;
        AcDbObjectId DictId;
        pNamedobj->setAt(_T("ASDK_DICT"), pDict, DictId);
    }
    pNamedobj->close();

    // Add a new xrecord to the ASDK_DICT dictionary.
    //
    AcDbXrecord *pXrec = new AcDbXrecord;
    AcDbObjectId xrecObjId;
    pDict->setAt(_T("XREC1"), pXrec, xrecObjId);
    pDict->close();

    // Create a resbuf list to add to the xrecord.
    //
    struct resbuf *pHead;
    ads_point testpt = {1.0, 2.0, 0.0};
    pHead = acutBuildList(AcDb::kDxfText,
        _T("This is a test Xrecord list"),
        AcDb::kDxfXCoord, testpt,
        AcDb::kDxfReal, 3.14159,
        AcDb::kDxfAngle, 3.14159,
        AcDb::kDxfColor, 1,
        AcDb::kDxfInt16, 180,
        0);

    // Add the data list to the xrecord.  Notice that this
    // member function takes a reference to resbuf, NOT a
    // pointer to resbuf, so you must dereference the
    // pointer before sending it.
    // 
    pXrec->setFromRbChain(*pHead);

    acutRelRb(pHead);
    pXrec->close();
}

// Gets the xrecord associated with the key XREC1 and
// lists out it's contents by passing the resbuf list to the
// function printList.
// 
void
listXrecord()
{
    AcDbDictionary *pNamedobj;
    acdbHostApplicationServices()->workingDatabase()
        ->getNamedObjectsDictionary(pNamedobj, AcDb::kForRead);

    // Get the dictionary object associated with the key ASDK_DICT.
    //
    AcDbDictionary *pDict;
    pNamedobj->getAt(_T("ASDK_DICT"), (AcDbObject*&)pDict,
        AcDb::kForRead);
    pNamedobj->close();

    // Get the xrecord associated with the key XREC1.
    //
    AcDbXrecord *pXrec;
    pDict->getAt(_T("XREC1"), (AcDbObject*&) pXrec,
        AcDb::kForRead);
    pDict->close();

    struct resbuf *pRbList;
    pXrec->rbChain(&pRbList);
    pXrec->close();

    printList(pRbList);
    acutRelRb(pRbList);
}

// END CODE APPEARING IN SDK DOCUMENT.

// Takes a linked list of resbufs as an argument.  Walks the
// list printing out the restypes and resval values one set
// per line.
// 
void
printList(struct resbuf* pBuf)
{
    int rt, i;
    TCHAR buf[133];

    for (i = 0;pBuf != NULL;i++, pBuf = pBuf->rbnext) {
        if (pBuf->restype < 0)
            // Entity name (or other sentinel)
            rt = pBuf->restype;
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
        else if (pBuf->restype < 330)
            rt = RTSTR;
        else if (pBuf->restype < 370)
            rt = RTENAME;
        else if (pBuf->restype < 999)
            rt = RT3DPOINT;
        else // pBuf->restype is already RTSHORT, RTSTR,
            rt = pBuf->restype; // etc. or it is unknown.

        switch (rt) {
        case RTSHORT:
            if (pBuf->restype == RTSHORT)
                acutPrintf(
                _T("RTSHORT : %d\n"), pBuf->resval.rint);
            else
                acutPrintf(_T("(%d . %d)\n"), pBuf->restype,
                    pBuf->resval.rint);
            break;
        case RTREAL:
            if (pBuf->restype == RTREAL)
                acutPrintf(
                _T("RTREAL : %0.3f\n"), pBuf->resval.rreal);
            else
                acutPrintf(_T("(%d . %0.3f)\n"),
                    pBuf->restype, pBuf->resval.rreal);
            break;
        case RTSTR:
            if (pBuf->restype == RTSTR)
                acutPrintf(
                _T("RTSTR : %s\n"), pBuf->resval.rstring);
            else
                acutPrintf(_T("(%d . \"%s\")\n"),
                    pBuf->restype, pBuf->resval.rstring);
            break;
        case RT3DPOINT:
            if (pBuf->restype == RT3DPOINT)
                acutPrintf(
                _T("RT3DPOINT : %0.3f, %0.3f, %0.3f\n"),
                    pBuf->resval.rpoint[X],
                    pBuf->resval.rpoint[Y],
                    pBuf->resval.rpoint[Z]);
            else
                acutPrintf(_T("(%d %0.3f %0.3f %0.3f)\n"),
                    pBuf->restype,
                    pBuf->resval.rpoint[X],
                    pBuf->resval.rpoint[Y],
                    pBuf->resval.rpoint[Z]);
            break;
        case RTLONG:
            acutPrintf(_T("RTLONG : %dl\n"), pBuf->resval.rlong);
            break;
        case -1:
        case RTENAME: // First block entity
            acutPrintf(_T("(%d . <Entity name: %8lx>)\n"),
                pBuf->restype, pBuf->resval.rlname[0]);
            break;
        case -3: // marks start of xdata
            acutPrintf(_T("(-3)\n"));
        }

        if ((i == 23) && (pBuf->rbnext != NULL)) {
            i = 0;
            acedGetString(0,
                _T("Press <ENTER> to continue..."), buf);
        }
    }
    return;
}


// Initialization function called in acrxEntryPoint during
// the kInitAppMsg case.  This is where commands are added
// to the AcEd command stack.
// 
void
initApp()
{
    acedRegCmds->addCommand(_T("ASDK_XRECORD_COMMANDS"),
        _T("ASDK_CREATE"), _T("CREATE"), ACRX_CMD_MODAL,
        createXrecord);
    acedRegCmds->addCommand(_T("ASDK_XRECORD_COMMANDS"),
        _T("ASDK_LISTXREC"), _T("LISTXREC"), ACRX_CMD_MODAL,
        listXrecord);
}


// Clean up function called in acrxEntryPoint during the
// kUnloadAppMsg case.  This app's command group is removed
// from the AcEd command stack.
// 
void
unloadApp()
{
    acedRegCmds->removeGroup(_T("ASDK_XRECORD_COMMANDS"));
}


// ARX entry point.
//
AcRx::AppRetCode
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
    }
    return AcRx::kRetOK;
}
