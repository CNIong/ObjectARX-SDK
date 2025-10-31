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
//  testdb.cpp



#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)

#error _DEBUG should not be defined except in internal Adesk debug builds

#endif

#include "rxregsvc.h"

#include "aced.h"

#include "dbsymtb.h"

#include "adslib.h"

#include "dbents.h"

#include "tchar.h"







// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.



void

createDwg()

{

    AcDbDatabase *pDb = new AcDbDatabase();

  

    AcDbBlockTable *pBtbl;

    pDb->getSymbolTable(pBtbl, AcDb::kForRead);



    AcDbBlockTableRecord *pBtblRcd;

    pBtbl->getAt(ACDB_MODEL_SPACE, pBtblRcd,

        AcDb::kForWrite);

    pBtbl->close();



    AcDbCircle *pCir1 = new AcDbCircle(AcGePoint3d(1,1,1),

                                       AcGeVector3d(0,0,1),

                                       1.0),

               *pCir2 = new AcDbCircle(AcGePoint3d(4,4,4),

                                       AcGeVector3d(0,0,1),

                                       2.0);



    pBtblRcd->appendAcDbEntity(pCir1);

    pCir1->close();

    

    pBtblRcd->appendAcDbEntity(pCir2);

    pCir2->close();

    pBtblRcd->close();



    // AcDbDatabase::saveAs() does NOT automatically

    // append a DWG file extension, so it

    // must be specified.

    //

    pDb->saveAs(_T("./test1.dwg"));

    delete pDb;

}





void

readDwg()

{

    // Set constructor parameter to kFalse so that the

    // database will be constructed empty.  This way only

    // what is read in will be in the database.

    //

    AcDbDatabase *pDb = new AcDbDatabase(Adesk::kFalse);



    // The AcDbDatabase::readDwgFile() function

    // automatically appends a DWG extension if it is not

    // specified in the filename parameter.

    //

    if(Acad::eOk != pDb->readDwgFile(_T("./test1.dwg")))

        return;



    // Open the model space block table record.

    //

    AcDbBlockTable *pBlkTbl;

    pDb->getSymbolTable(pBlkTbl, AcDb::kForRead);



    AcDbBlockTableRecord *pBlkTblRcd;

    pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd,

        AcDb::kForRead);

    pBlkTbl->close();



    AcDbBlockTableRecordIterator *pBlkTblRcdItr;

    pBlkTblRcd->newIterator(pBlkTblRcdItr);



    AcDbEntity *pEnt;

    for (pBlkTblRcdItr->start(); !pBlkTblRcdItr->done();

        pBlkTblRcdItr->step())

    {

        pBlkTblRcdItr->getEntity(pEnt,

            AcDb::kForRead);

        acutPrintf(_T("classname: %s\n"),

            (pEnt->isA())->name());

        pEnt->close();

    }

    pBlkTblRcd->close();

    delete pBlkTblRcdItr;

    delete pDb;

}



// END CODE APPEARING IN SDK DOCUMENT.



void

initApp()

{

    acedRegCmds->addCommand(_T("ASDK_DWG_COMMANDS"),

        _T("ASDK_CREATE"), _T("CREATE"), ACRX_CMD_MODAL, createDwg);



    acedRegCmds->addCommand(_T("ASDK_DWG_COMMANDS"),

        _T("ASDK_READ"), _T("READ"),  ACRX_CMD_MODAL, readDwg);

}



void

unloadApp()

{

    acedRegCmds->removeGroup(_T("ASDK_DWG_COMMANDS"));

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

    }

    return AcRx::kRetOK;

}

