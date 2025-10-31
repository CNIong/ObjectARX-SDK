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
// This program demonstrates using extension dictionaries.
// Two commands are defined in this program:  CREATE, and
// LISTXREC.
// 
// The CREATE command calls the function createXrecord()
// which instantiates an xrecord object and adds it to the
// extension dictionary of a user selected object.
// 
// The LISTXREC command calls the listXrecord() function
// which opens the extension dictionary of a user selected
// object, looks for the xrecord created by the CREATE
// command and then calls the printList() function to print
// out the data stored in the xrecord.

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <stdlib.h>
#include <rxobject.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbsymtb.h>
#include <adslib.h>
#include <dbxrecrd.h>
#include <acestext.h>
#include "tchar.h"



void                        createXrecord();
void                        listXrecord();
AcDbObject*                 selectObject(AcDb::OpenMode);
void                        printList(struct resbuf* pBuf);
void                        initApp();
void                        unloadApp();
extern "C"
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);


// The createXrecord() functions creates an xrecord object, 
// adds data to it, and then adds the xrecord to the extension 
// dictionary of a user selected object.
// 
// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.
//
void
createXrecord()
{
    AcDbXrecord *pXrec = new AcDbXrecord;
    AcDbObject *pObj;
    AcDbObjectId dictObjId, xrecObjId;
    AcDbDictionary* pDict;

    pObj = selectObject(AcDb::kForWrite);
    if (pObj == NULL) {
        return;
    }

    // Try to create an extension dictionary for this
    // object.  If the extension dictionary already exists,
    // this will be a no-op.
    // 
    pObj->createExtensionDictionary();

    // Get the object ID of the extension dictionary for the
    // selected object.
    // 
    dictObjId = pObj->extensionDictionary();
    pObj->close();

    // Open the extension dictionary and add the new
    // xrecord to it.
    //
    acdbOpenObject(pDict, dictObjId, AcDb::kForWrite);
    pDict->setAt(_T("ASDK_XREC1"), pXrec, xrecObjId);
    pDict->close();

    // Create a resbuf list to add to the xrecord.
    //
    struct resbuf* head;
    ads_point testpt = {1.0, 2.0, 0.0};
    head = acutBuildList(AcDb::kDxfText,
        _T("This is a test Xrecord list"),
        AcDb::kDxfXCoord, testpt,
        AcDb::kDxfReal, 3.14159,
        AcDb::kDxfAngle, 3.14159,
        AcDb::kDxfColor, 1,
        AcDb::kDxfInt16, 180,
        0);

    // Add the data list to the xrecord.  Notice that this
    // member function takes a reference to a resbuf NOT a
    // pointer to a resbuf, so you must dereference the
    // pointer before sending it.
    // 
    pXrec->setFromRbChain(*head);
    pXrec->close();
    acutRelRb(head);
}


// The listxrecord() functions gets the xrecord associated with the 
// key "ASDK_XREC1" and lists out its contents by passing the resbuf 
// list to the function printList().
// 
void
listXrecord()
{
    AcDbObject *pObj;
    AcDbXrecord *pXrec;
    AcDbObjectId dictObjId;
    AcDbDictionary *pDict;

    pObj = selectObject(AcDb::kForRead);
    if (pObj == NULL) {
        return;
    }
    // Get the object ID of the object's extension dictionary.
    //
    dictObjId = pObj->extensionDictionary();
    pObj->close();

    // Open the extension dictionary and get the xrecord
    // associated with the key ASDK_XREC1.
    // 
    acdbOpenObject(pDict, dictObjId, AcDb::kForRead);
    pDict->getAt(_T("ASDK_XREC1"), (AcDbObject*&)pXrec,
        AcDb::kForRead);
    pDict->close();

    // Get the xrecord's data list and then close the xrecord.
    //
    struct resbuf *pRbList;
    pXrec->rbChain(&pRbList);
    pXrec->close();

    printList(pRbList);
    acutRelRb(pRbList);
}

// END CODE APPEARING IN SDK DOCUMENT.

// The selectObject() function prompts the user to select an 
// entity or enter an object's handle.  It then proceeds to 
// open the object/entity and return a pointer to it.
// 
AcDbObject*
selectObject(AcDb::OpenMode openMode)
{
    ads_name en;
    ads_point pt;
    TCHAR handleStr[132];
    AcDbObjectId eId;

    Acad::ErrorStatus retStat;
    int ss;

    // Allow user to either pick an entity,
    // or type in the object handle.
    //
    acedInitGet(RSG_OTHER, _T("Handle _Handle"));
    ss = acedEntSel(_T("\nSelect an Entity or enter")
        _T(" 'H' to enter its handle:  "), en, pt);

    switch (ss) {
    case RTNORM:   // got it!
        break;
    case RTKWORD:
        if ((acedGetString(Adesk::kFalse,
            _T("Enter Valid Object Handle: "),
            handleStr) == RTNORM)
            && (acdbHandEnt(handleStr, en) == RTNORM))
        {
            break;
        }
    // Fall-through intentional
    //
    default:
        acutPrintf(_T("Nothing Selected, Return Code==%d\n"),
            ss);
        return NULL;
    }

    // Now, exchange the ads_name for the object Id...
    //
    retStat = acdbGetObjectId(eId, en);
    if (retStat != Acad::eOk) {
        acutPrintf(_T("\nacdbGetObjectId failed"));
        acutPrintf(_T("\nen==(%lx,%lx), retStat==%d\n"),
            en[0], en[1], eId.asOldId());
        return NULL;
    }

    AcDbObject* pObj;

    if ((retStat = acdbOpenObject(pObj, eId, openMode))
        != Acad::eOk)
    {
        acutPrintf(_T("acdbOpenEntity failed: ename:")
            _T("(%lx,%lx), mode:%d retStat:%d"), en[0],
            en[1], openMode, retStat);
        return NULL;
    }
    return pObj;
}


// The printList() function takes a linked list of resbufs 
// as an argument.  Walks the list printing out the restypes 
// and resval values one set per line.
// 
void
printList(struct resbuf* pBuf)
{
    int rt, i;
    TCHAR buf[133];

    for (i = 0;pBuf != NULL;i++, pBuf = pBuf->rbnext) {
        if (pBuf->restype < 0)
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
        else
            rt = pBuf->restype;

        switch (rt) {
        case RTSHORT:
            if (pBuf->restype == RTSHORT)
                acutPrintf(_T("RTSHORT : %d\n"),
                    pBuf->resval.rint);
            else
                acutPrintf(_T("(%d . %d)\n"), pBuf->restype,
                    pBuf->resval.rint);
            break;
        case RTREAL:
            if (pBuf->restype == RTREAL)
                acutPrintf(_T("RTREAL : %0.3f\n"),
                    pBuf->resval.rreal);
            else
                acutPrintf(_T("(%d . %0.3f)\n"), pBuf->restype,
                    pBuf->resval.rreal);
            break;
        case RTSTR:
            if (pBuf->restype == RTSTR)
                acutPrintf(_T("RTSTR : %s\n"),
                   pBuf->resval.rstring);
            else
                acutPrintf(_T("(%d . \"%s\")\n"), pBuf->restype,
                    pBuf->resval.rstring);
            break;
        case RT3DPOINT:
            if (pBuf->restype == RT3DPOINT)
                acutPrintf(
                _T("RT3DPOINT : %0.3f, %0.3f, %0.3f\n"),
                    pBuf->resval.rpoint[X],
                    pBuf->resval.rpoint[Y],
                    pBuf->resval.rpoint[Z]);
            else
                acutPrintf(
                   _T("(%d %0.3f %0.3f %0.3f)\n"),
                    pBuf->restype,
                    pBuf->resval.rpoint[X],
                    pBuf->resval.rpoint[Y],
                    pBuf->resval.rpoint[Z]);
            break;
        case RTLONG:
            acutPrintf(_T("RTLONG : %dl\n"),
                pBuf->resval.rlong);
            break;
        case -1:
        case RTENAME:
            acutPrintf(_T("(%d . <Entity name: %8lx>)\n"),
                pBuf->restype, pBuf->resval.rlname[0]);
            break;
        case -3:
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


// Initialization function called in acrxEntryPoint
// during the kInitAppMsg case.  This is where commands
// are added to the AcEd command stack.
// 
void
initApp()
{
    acedRegCmds->addCommand(_T("ASDK_EXTDICT_COMMANDS"),
        _T("ASDK_CREATE"), _T("CREATE"), ACRX_CMD_MODAL,
        createXrecord);
    acedRegCmds->addCommand(_T("ASDK_EXTDICT_COMMANDS"),
        _T("ASDK_LISTXREC"), _T("LISTXREC"), ACRX_CMD_MODAL,
        listXrecord);
}

// Clean up function called in acrxEntryPoint during the
// kUnloadAppMsg case.  This app's command group is
// removed from the AcEd command stack.
// 
void
unloadApp()
{
    acedRegCmds->removeGroup(_T("ASDK_EXTDICT_COMMANDS"));
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
