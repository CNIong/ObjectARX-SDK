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
//  Test Application for AcDbDatabaseReactor,

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "rxobject.h"
#include "rxregsvc.h"
#include "rxdlinkr.h"
#include "rxditer.h"
#include "aced.h"
#include "dbmain.h"
#include "dbdict.h"
#include "dbidmap.h"
#include "dbapserv.h"
#include "adslib.h"
#include "tchar.h"



void printDbEvent(const AcDbObject*, const TCHAR* eventStr);
static void printObj(const AcDbObject* pObj);
void watchDb();
void clearReactors();
extern "C"
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

class AsdkDbReactor;

long gEntAcc = 0;            // Global entity count
AsdkDbReactor *gpDbr = NULL; // Pointer to database reactor

//
// Custom AcDbDatabaseReactor class for database
// event notification.
//
class AsdkDbReactor : public AcDbDatabaseReactor
{
public:

    virtual void objectAppended(const AcDbDatabase* dwg,
        const AcDbObject* dbObj);

    virtual void objectModified(const AcDbDatabase* dwg,
        const AcDbObject* dbObj);

    virtual void objectErased(const AcDbDatabase* dwg,
        const AcDbObject* dbObj, Adesk::Boolean pErased);
};


// Called whenever an object is added to the database.
//
void
AsdkDbReactor::objectAppended(const AcDbDatabase* db,
    const AcDbObject* pObj)
{
    printDbEvent(pObj, _T("objectAppended"));
    acutPrintf(_T(" Db==%lx\n"), (long) db);
    gEntAcc++;
    acutPrintf(_T("Entity Count = %d\n"), gEntAcc);
}


// Called whenever an object in the database is modified.
//
void
AsdkDbReactor::objectModified(const AcDbDatabase* db,
    const AcDbObject* pObj)
{
    printDbEvent(pObj, _T("objectModified"));
    acutPrintf(_T(" Db==%lx\n"), (long) db);
}


// Called whenever an object is erased from the database.
//
void
AsdkDbReactor::objectErased(const AcDbDatabase* db,
    const AcDbObject* pObj, Adesk::Boolean pErased)
{
    if (pErased) {
        printDbEvent(pObj, _T("objectErased"));
        gEntAcc--;
    } else {
        printDbEvent(pObj, _T("object(Un)erased"));
        gEntAcc++;
    }
    acutPrintf(_T(" Db==%lx\n"), (long) db);
    acutPrintf(_T("Entity Count = %d\n"), gEntAcc);
}


// Prints the message passed in by eventStr and then 
// calls printObj to print the information about
// the object that triggered the notification.
//
void
printDbEvent(const AcDbObject* pObj, const TCHAR* pEvent)
{
    acutPrintf(_T("  Event: AcDbDatabaseReactor::%s "), pEvent);
    printObj(pObj);
}


// Prints out the basic information about the object pointed
// to by pObj.
//
static void
printObj(const AcDbObject* pObj)
{
    if (pObj == NULL) {
        acutPrintf(_T("(NULL)"));
        return;
    }

    AcDbHandle objHand;
    TCHAR  handbuf[17];

    // Get the handle as a string.
    //
    pObj->getAcDbHandle(objHand);
    objHand.getIntoAsciiBuffer(handbuf);

    acutPrintf(
        _T("\n   (class==%s, handle==%s, id==%lx, db==%lx)"),
        pObj->isA()->name(), handbuf,
        pObj->objectId().asOldId(), pObj->database());
}


// Adds a reactor to the database to monitor changes.
// This can be called multiple times without any ill
// effect because subsequent calls will be ignored.
//
void
watchDb()
{
    if (gpDbr == NULL) {
        gpDbr = new AsdkDbReactor();
    }
    acdbHostApplicationServices()->workingDatabase()->addReactor(gpDbr);
    acutPrintf(
        _T("  Added Database Reactor to ")
        _T("acdbHostApplicationServices()->workingDatabase().\n"));
}


// Removes the database reactor.
//
void
clearReactors()
{
    if (acdbHostApplicationServices()->workingDatabase() != NULL) {
        acdbHostApplicationServices()->workingDatabase()->removeReactor(gpDbr);
        delete gpDbr;
        gpDbr = NULL;
    }
}

// Arx entry point function.
//
AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppNotMDIAware(appId);
        acedRegCmds->addCommand(_T("ASDK_NOTIFY_TEST"),
            _T("ASDK_WATCH"),
            _T("WATCH"),
            ACRX_CMD_TRANSPARENT,
            watchDb);

        acedRegCmds->addCommand(_T("ASDK_NOTIFY_TEST"),
            _T("ASDK_CLEAR"),
            _T("CLEAR"),
            ACRX_CMD_TRANSPARENT,
            clearReactors);
        break;
    case AcRx::kUnloadAppMsg:
        clearReactors();
        acedRegCmds->removeGroup(_T("ASDK_NOTIFY_TEST"));
        break;
    }
    return AcRx::kRetOK;
}

// END CODE APPEARING IN SDK DOCUMENT.
