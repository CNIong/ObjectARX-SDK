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
// AsdkLongTransSample.cpp
// 
// Example showing how to use Long Transactions.
//


#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <rxregsvc.h>
#include <aced.h>

#include <dbidmap.h>
#include <lngtrans.h>
#include <dbltrans.h>

#include <dbmain.h>
#include <dbsymtb.h>
#include <dbents.h>
#include <dbapserv.h>
#include <adslib.h>
#include "tchar.h"



// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

void
refEditApiExample()
{

    AcDbObjectId transId;
    AcDbDatabase* pDb;
    TCHAR *fname;
    struct resbuf *rb;

    // Get a dwg file from the user.
    //
    rb = acutNewRb(RTSTR);
    int stat = acedGetFileD(_T("Pick a drawing"), NULL, _T("dwg"), 0, rb);
    
    if ((stat != RTNORM) || (rb == NULL)) {
        acutPrintf(_T("\nYou must pick a drawing file."));
        return;
    }

    const size_t nSize = _tcslen(rb->resval.rstring) + 1;
    fname = (TCHAR*)acad_malloc(nSize * sizeof(TCHAR));
    errno_t err = _tcscpy_s(fname, nSize, rb->resval.rstring);
    assert(err == 0);
    acutRelRb(rb);
    
    // Open the dwg file.
    //
    pDb = new AcDbDatabase(Adesk::kFalse);
    if (pDb->readDwgFile(fname) != Acad::eOk) {
        acutPrintf(_T("\nSorry, that drawing is probably already open."));
        return;
    }

    // Get the Block Table and then the model space record.
    //
    AcDbBlockTable *pBlockTable;
    pDb->getSymbolTable(pBlockTable, AcDb::kForRead);
    AcDbBlockTableRecord *pOtherMsBtr;
    pBlockTable->getAt(ACDB_MODEL_SPACE, pOtherMsBtr, AcDb::kForRead);
    pBlockTable->close();

    // Create an iterator.
    //
    AcDbBlockTableRecordIterator *pIter;
    pOtherMsBtr->newIterator(pIter);

    // Set up an object ID array.
    //
    AcDbObjectIdArray objIdArray;

    // Iterate over the model space BTR. Look specifically 
    // for lines and append their object ID to the array.
    //
    for (pIter->start(); !pIter->done(); pIter->step()) {
        AcDbEntity *pEntity;
        pIter->getEntity(pEntity, AcDb::kForRead);

        // Look for only AcDbLine objects and add them to the 
        // object ID array.
        //
        if (pEntity->isKindOf(AcDbLine::desc())) {
            objIdArray.append(pEntity->objectId());
        }
        pEntity->close();
    }
    delete pIter;
    pOtherMsBtr->close();

    if (objIdArray.isEmpty()) {
        acad_free(fname);
        acutPrintf(_T("\nYou must pick a drawing file that contains lines."));
        return;
    }

    // Now get the current database and the object ID for the
    // current database's model space BTR.
    //
    AcDbBlockTable *pThisBlockTable;
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pThisBlockTable, AcDb::kForRead);

    AcDbBlockTableRecord *pThisMsBtr;
    pThisBlockTable->getAt(ACDB_MODEL_SPACE, pThisMsBtr, AcDb::kForWrite);
    pThisBlockTable->close();
    
    AcDbObjectId id = pThisMsBtr->objectId();
    pThisMsBtr->close();


    // Create the long transaction. This will check all the entities 
    // out of the external database.
    //
    AcDbIdMapping errorMap;
    acapLongTransactionManagerPtr()->checkOut(transId, objIdArray, id, errorMap);

    // Now modify the color of these entities.
    //
    int colorIndex;
    acedGetInt(_T("\nEnter color number to change entities to: "), &colorIndex);
    AcDbObject* pObj;
    if (acdbOpenObject(pObj, transId, AcDb::kForRead) == Acad::eOk) {

        // Get a pointer to the transaction.
        //
        AcDbLongTransaction* pLongTrans = AcDbLongTransaction::cast(pObj);
        if (pLongTrans != NULL) {

            // Get a work set iterator.
            //
            AcDbLongTransWorkSetIterator* pWorkSetIter;
            pLongTrans->newWorkSetIterator(pWorkSetIter);

            // Iterate over the entities in the work set and change the color.
            //
            for (pWorkSetIter->start(); !pWorkSetIter->done(); pWorkSetIter->step()) {
                AcDbEntity *pEntity;
                acdbOpenAcDbEntity(pEntity, pWorkSetIter->objectId(), AcDb::kForWrite);
                pEntity->setColorIndex(colorIndex);
                pEntity->close();
            }
            delete pWorkSetIter;
        }
        pObj->close();
    }

    // Pause to see the change.
    //
    TCHAR str[132];
    acedGetString(0, _T("\nSee the new colors. Press return to check the object into the original database"), str);

    // Check the entities back in to the original database.
    //
    acapLongTransactionManagerPtr()->checkIn(transId, errorMap);

    // Save the original database, since we have made changes.
    //
    pDb->saveAs(fname);

    // Close/Delete the database
    //
    delete pDb;
    pDb = NULL;

    acad_free(fname);
}

// END CODE APPEARING IN SDK DOCUMENT.

void
initApp()
{

    // register a command with the AutoCAD command mechanism
    //
    acedRegCmds->addCommand(_T("AsdkLongTransSample_COMMANDS"), _T("AsdkLongTrans"), _T("LongTrans"), ACRX_CMD_MODAL, refEditApiExample);

}


void unloadApp()
{
    
    // Remove the command group added via acedRegCmds->addCommand
    //
    acedRegCmds->removeGroup(_T("AsdkLongTransSample_COMMANDS"));

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

