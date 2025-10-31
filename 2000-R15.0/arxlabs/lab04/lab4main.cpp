//
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
//
#include "rxdlinkr.h"
#include "aced.h"
#include "actrans.h"
#include "dbdict.h"
#include "acestext.h"
#include "lab4utils.h"
#include "dbxrecrd.h"

//This is used as the key for our custom
//dictionary. Note the registered developer id 'OARX'
//at the beginning
#define DICT "OARXLABS_EMPLOYEE_DICT"

void addEntryCommand()
//Description:
//  This is the command handler for the ADDENTRY command.
//Note:
//  When this command invoked at the first time
//  it creates two objects: an AcDbDictionary object in the named
//  objects dictionary (NOD) and an empty AcDbXrecord object to represent
//  an individual entry. The xrecord will be replaced in lab6 by a
//  custom object EmployeeEntry.
//  At later invokations the command just adds new xrecords to this
//  dictionary.
//  We use a transaction to wrap all db operations thus enabling
//  easy undo if the command is aborted by the user or an internal error.
//  Storing these entries in the NOD will enable us to query all
//  employees in the db quickly without iterating through all
//  AcDbBlockTableRecord in the database.
{
    //place these two variables into function
    //scope so the catch handler can access them below
    AcDbDictionary* pEmployeeDict=NULL;
    AcDbXrecord* pEmployeeEntry=NULL;

    if (acdbHostApplicationServices()->workingDatabase()==NULL)
        return;
    try
    {
        //start transaction for the db operations in this command
        actrTransactionManager->startTransaction();
        
        //prompt the use for the an id
        char strID[133];
        ADSOK(acedGetString(0,"Enter employee name(<33 chars):",strID));
        //dictionary keys cannot be longer than 32 character long
        if (strlen(strID)>32)
            throw Acad::eInvalidInput;
        
        //get the named object dictionary
        AcDbDictionary* pNOD;
        ARXOK(getNOD(pNOD,AcDb::kForWrite));
        
        //see if our dictionary is already there
        AcDbObjectId idO;
        if (pNOD->getAt(DICT,idO) == Acad::eKeyNotFound){
            //create it if not
            if ((pEmployeeDict=new AcDbDictionary)==NULL)
                throw Acad::eOutOfMemory;
            ARXOK(pNOD->setAt(DICT,pEmployeeDict,idO));
            //this will ensure that the newly added object is properly 
            //committed to the db when the transaction ends
            actrTransactionManager->addNewlyCreatedDBRObject(pEmployeeDict);
        } else {
            //get it for write if it is already there
            AcDbObject* pO;
            ARXOK(actrTransactionManager->getObject(pO,idO,AcDb::kForWrite));
            //check if someone has else has created an entry with our name
            //that is not a dictionary. This should never happen as long as
            //I use the registered developer ID.
            if ((pEmployeeDict=AcDbDictionary::cast(pO))==NULL)
                throw Acad::eNotThatKindOfClass;
        }
        //check if a record with this key is already there
        Acad::ErrorStatus es;
        if ((es=pEmployeeDict->getAt(strID,idO))==Acad::eOk)
            throw Acad::eAlreadyInDb;
        if (es!=Acad::eKeyNotFound)
            throw es;

        //okey-dokey. let's add the new record
        //append an empty xrecord. this will be replaced by a custom object
        if ((pEmployeeEntry=new AcDbXrecord)==NULL)
                throw Acad::eOutOfMemory;
        ARXOK(pEmployeeDict->setAt(strID,pEmployeeEntry,idO));
        //this will ensure that the newly added object is properly 
        //committed to the db when the transaction ends
        actrTransactionManager->addNewlyCreatedDBRObject(pEmployeeEntry);

        actrTransactionManager->endTransaction();
    }
    catch (const Acad::ErrorStatus es)
    {
        //we have run into some error
        //do the proper cleanup. a smart pointer could check these in its
        //destructor and then we wouldn't need this but we I don't want to
        //complicate the picture with that yet.
        if (pEmployeeDict!=NULL && 
            pEmployeeDict->objectId()==AcDbObjectId::kNull)
            delete pEmployeeDict;
        if (pEmployeeEntry!=NULL && 
            pEmployeeEntry->objectId()==AcDbObjectId::kNull)
            delete pEmployeeEntry;
        //abort, rollback all db operations
        actrTransactionManager->abortTransaction();
        //check if the user has cancelled us, then we don't report
        //anything
        if (es!=Acad::eUserBreak)
            acutPrintf("***Error: %s\n",acadErrorStatusText(es));
    }
}

void
getEmployeeDict(/*[out]*/AcDbDictionary*& pEmployeeDict){
//Description:
//  Gets the employee dictionary from NOD.
//Note:
//  It requires a running transaction
//  It throws Acad::ErrorStatus exceptions
    AcDbDictionary* pNOD;
    //get the named object dictionary
    ARXOK(getNOD(pNOD,AcDb::kForRead));
    AcDbObjectId idO;
    //see if our dictionary is there
    ARXOK(pNOD->getAt(DICT,idO));
    //get it for write 
    AcDbObject* pO;
    ARXOK(actrTransactionManager->getObject(pO,idO,AcDb::kForWrite));
    //check if someone else has created an entry with our name
    //that is not a dictionary. This should never happen as long as
    //I use the registered developer ID.
    if ((pEmployeeDict=AcDbDictionary::cast(pO))==NULL)
        throw Acad::eNotThatKindOfClass;
}

void removeEntryCommand()
//Description:
//  This is the command handler for the REMOVEENTRY command
{ 

    if (acdbHostApplicationServices()->workingDatabase()==NULL)
        return;
    try
    {
        //start transaction for the db operations in this command
        actrTransactionManager->startTransaction();
                
        //prompt the use for the an id
        char strID[133];
        ADSOK(acedGetString(0,"Enter employee name(<33 chars):",strID));
        //dictionary keys cannot be longer then 32 character long
        if (strlen(strID)>32)
            throw Acad::eInvalidInput;

        //get the employee dictionary
        AcDbDictionary* pEmployeeDict=NULL;
        getEmployeeDict(pEmployeeDict);
        
        //check if a record with this key is there
        AcDbObjectId idO;
        ARXOK(pEmployeeDict->getAt(strID,idO));
        
        //get it for write 
        AcDbObject* pO;
        ARXOK(actrTransactionManager->getObject(pO,idO,AcDb::kForWrite));
        //and erase it
        ARXOK(pO->erase());

        actrTransactionManager->endTransaction();
    }
    catch (const Acad::ErrorStatus es)
    {
        //abort, rollback all db operations
        actrTransactionManager->abortTransaction();
        //check if the user has cancelled us, then we don't report
        //anything
        if (es!=Acad::eUserBreak)
            acutPrintf("***Error: %s\n",acadErrorStatusText(es));
    }
}

void listEntriesCommand()
//Description:
//  List all the entries in DICT
{

    if (acdbHostApplicationServices()->workingDatabase()==NULL)
        return;
    AcDbDictionaryIterator* pIter=NULL;
    try
    {
        actrTransactionManager->startTransaction();
        AcDbDictionary* pEmployeeDict=NULL;
        AcDbXrecord* pEmployee=NULL;
        //start transaction for the db operations in this command
        getEmployeeDict(pEmployeeDict);
        if ((pIter = pEmployeeDict->newIterator(AcRx::kDictCollated))!=NULL){
            for (;!pIter->done();pIter->next()){
                //print name
                acutPrintf("*Employee:%s\n",pIter->name());
            }
            delete pIter;
            pIter=NULL;
        }

        actrTransactionManager->endTransaction();
    }
    catch (const Acad::ErrorStatus es)
    {
        if (pIter!=NULL)
            delete pIter;
        //abort, rollback all db operations
        actrTransactionManager->abortTransaction();
        //check if the user has cancelled us, then we don't report
        //anything
        if (es!=Acad::eUserBreak)
            acutPrintf("***Error: %s\n",acadErrorStatusText(es));
    }
}

//This is the entry point that makes a simple DLL an ARX.
//This entry point must be exported either by means of a def file
//or by the means of _declspec
extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt) 
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        //An ARX application is locked to memory by default.
        //You must make the following function call to unlock
        //it.
        acrxDynamicLinker->unlockApplication(pkt); 

        // This is an MDI aware application
        acrxDynamicLinker->registerAppMDIAware(pkt);

        //register the command
        acedRegCmds->addCommand("OARX_LAB4","addentry","addentry",ACRX_CMD_MODAL,addEntryCommand);
        acedRegCmds->addCommand("OARX_LAB4","removeentry","removeentry",ACRX_CMD_MODAL,removeEntryCommand);
        acedRegCmds->addCommand("OARX_LAB4","listentries","listentries",ACRX_CMD_MODAL,listEntriesCommand);
        break;
    case AcRx::kUnloadAppMsg:
        //remove the command group so that AutoCAD won't call us
        //when we are not here.
        acedRegCmds->removeGroup("OARX_LAB4");
        break;
    }
    return AcRx::kRetOK;
}