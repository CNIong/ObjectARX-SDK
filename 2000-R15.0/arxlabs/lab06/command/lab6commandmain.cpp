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
#include "lab6CommandUtils.h"
#include "dbents.h"
#include <stdio.h>
#include "..\object\lab6ObjectEmployeedetails.h"
#include "..\object\lab6ObjectEmployeeentry.h"

#define DICT "OARXLABS_EMPLOYEE_DICT"
#define DETAILS "DETAILS"

void addEmpCommand()
{ 
    AcDbDictionary* pEmployeeDict=NULL;
    EmployeeDetails* pEmployeeDetails=NULL;
    EmployeeEntry* pEmployeeEntry=NULL;
    //this cannot really happen but...
    if (acdbHostApplicationServices()->workingDatabase()==NULL)
        return;
    try
    {
        //start transaction for the db operations in this command
        actrTransactionManager->startTransaction();

        //get the data from the user
        ads_name ename;
        ads_point pt;
        ADSOK(acedEntSel("Select employee:",ename,pt));

        //do a quick check
        //a more comprehensive check could include 
        //a check to see if we already have the detail object on this candidate
        AcDbObjectId idO;
        ARXOK(acdbGetObjectId(idO,ename));
        AcDbObject* pO;
        ARXOK(actrTransactionManager->getObject(pO,idO,AcDb::kForWrite));
        if (!pO->isKindOf(AcDbBlockReference::desc()))
            throw Acad::eNotThatKindOfClass;

        //go on getting user input
        int id;
        ADSOK(acedGetInt("Enter employee ID:",&id));

        int cubeNumber;
        ADSOK(acedGetInt("Enter cube number:",&cubeNumber));

        char strFirstName[133];
        ADSOK(acedGetString(0,"Enter employee first name:",strFirstName));

        char strLastName[133];
        ADSOK(acedGetString(0,"Enter employee last name:",strLastName));
        
        //create an EmployeeDetails object and set its fields
        if ((pEmployeeDetails= new EmployeeDetails)==NULL)
            throw Acad::eOutOfMemory;
        ARXOK(pEmployeeDetails->setID(id));
        ARXOK(pEmployeeDetails->setCubeNumber(cubeNumber));
        ARXOK(pEmployeeDetails->setFirstName(strFirstName));
        ARXOK(pEmployeeDetails->setLastName(strLastName));

        //get hold of the extension dictionary
        if ((idO = pO->extensionDictionary())==AcDbObjectId::kNull){
            ARXOK(pO->createExtensionDictionary());
            idO = pO->extensionDictionary();
        }
        AcDbDictionary* pExtDict;
        //make sure you open erased extension dictionaries
        //you may need to unerase them
        ARXOK(actrTransactionManager->getObject((AcDbObject*&)pExtDict,idO,AcDb::kForWrite,Adesk::kTrue));
        
        //add the EmployeeDetails to the extension dictionary
        addDictAndEntry(DICT,pExtDict,DETAILS,pEmployeeDetails);
        
        //create the EmployeeEntry and set the id it holds to
        //point to the corresponding EmployeeDetails
        if ((pEmployeeEntry= new EmployeeEntry)==NULL)
            throw Acad::eOutOfMemory;
        ARXOK(pEmployeeEntry->setEmployee(pEmployeeDetails->objectId()));

        //get hold of the NOD
        AcDbDictionary* pNOD;
		ARXOK(getNOD(pNOD,AcDb::kForWrite));
        
        //create string key from the employee id
        char strID[33];
        sprintf(strID,"%d",id);

        //set the EmployeeEntry to the NOD
        addDictAndEntry(DICT,pNOD,strID,pEmployeeEntry);

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
        if (pEmployeeDetails!=NULL && 
            pEmployeeDetails->objectId()==AcDbObjectId::kNull)
            delete pEmployeeDetails;
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

void removeEmpCommand()
{ 
    //this cannot really happen but...
    if (acdbHostApplicationServices()->workingDatabase()==NULL)
        return;
    try
    {
        //start transaction for the db operations in this command
        actrTransactionManager->startTransaction();

        //get you extension dictionary
        AcDbDictionary* pExtDict = NULL;
        getExtDictOfObject(pExtDict);
        
        //get the id from the EmployeeDetails object
        //see if our dictionary is there
        AcDbObjectId idO;
        ARXOK(pExtDict->getAt(DICT,idO));

        //get it for write 
        AcDbObject* pO;
        ARXOK(actrTransactionManager->getObject(pO,idO,AcDb::kForWrite));

        //check if someone has else has created an entry with our name
        //that is not a dictionary. This should never happen as long as
        //I use the registered developer ID.
        AcDbDictionary* pEmployeeDict=NULL;
        if ((pEmployeeDict=AcDbDictionary::cast(pO))==NULL)
            throw Acad::eNotThatKindOfClass;

        //check if a record with this key is there
        ARXOK(pEmployeeDict->getAt(DETAILS,idO));

        //get it for write 
        ARXOK(actrTransactionManager->getObject(pO,idO,AcDb::kForWrite));
        
        EmployeeDetails* pEmployeeDetails;
        if ((pEmployeeDetails=EmployeeDetails::cast(pO))==NULL)
            throw Acad::eNotThatKindOfClass;

        //create string key from the employee id
        char strID[33];
        sprintf(strID,"%d",pEmployeeDetails->ID());

        //and then erase it
        ARXOK(pO->erase());

        //get hold of the NOD
        AcDbDictionary* pNOD;
        ARXOK(getNOD(pNOD,AcDb::kForWrite));
        
        //remove the EmployeeEntry from NOD
        removeEntryFromDict(DICT,pNOD,strID);

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

void listEmpsCommand()
{
    //this cannot really happen but...
    if (acdbHostApplicationServices()->workingDatabase()==NULL)
        return;
    AcDbDictionaryIterator* pIter=NULL;
    try
    {
        //start transaction for the db operations in this command
        actrTransactionManager->startTransaction();
        
        
        //get the named object dictionary
        AcDbDictionary* pNOD;
        ARXOK(getNOD(pNOD,AcDb::kForRead));

        //see if our dictionary is there
        AcDbObjectId idO;
        ARXOK(pNOD->getAt(DICT,idO));

        //get it for write 
        AcDbObject* pO;
        ARXOK(actrTransactionManager->getObject(pO,idO,AcDb::kForWrite));
        //check if someone has else has created an entry with our name
        //that is not a dictionary. This should never happen as long as
        //I use the registered developer ID.
        AcDbDictionary* pEmployeeDict=NULL;
        if ((pEmployeeDict=AcDbDictionary::cast(pO))==NULL)
            throw Acad::eNotThatKindOfClass;

        if ((pIter = pEmployeeDict->newIterator(AcRx::kDictCollated))!=NULL){
            for (;!pIter->done();pIter->next()){
                //get the object
                ARXOK(actrTransactionManager->getObject(pO,pIter->objectId(),AcDb::kForRead));

                //check if it is the right one
                EmployeeEntry* pEmployeeEntry;
                if ((pEmployeeEntry=EmployeeEntry::cast(pO))==NULL)
                    throw Acad::eNotThatKindOfClass;

                //get the corresponding EmployeeDetail object
                ARXOK(actrTransactionManager->getObject(pO,pEmployeeEntry->employee(),AcDb::kForRead));
                EmployeeDetails* pEmployeeDetails;
                if ((pEmployeeDetails=EmployeeDetails::cast(pO))==NULL)
                    throw Acad::eNotThatKindOfClass;

                //print the details now
                acutPrintf("*Employee's ID:%d\n",pEmployeeDetails->ID());
                acutPrintf("*Employee's cube number:%d\n",pEmployeeDetails->cubeNumber());
                acutPrintf("*Employee's first name:%s\n",pEmployeeDetails->firstName());
                acutPrintf("*Employee's last name:%s\n",pEmployeeDetails->lastName());

                //this will ease memory burden when implemented
                ARXOK(actrTransactionManager->markObjectPageable(pO));
            }
            //shouldn't forget this
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
        {
            //An ARX application is locked to memory by default.
            //You must make the following function call to unlock
            //it.
            acrxDynamicLinker->unlockApplication(pkt); 
			acrxDynamicLinker->registerAppMDIAware(pkt);
            //check for the service registered by Lab6Object
            if (!acrxServiceDictionary->at(EMPLOYEE_DETAILS_SERVICE)){
                //try to load lab6Object if it is not yet present
                if (!acrxDynamicLinker->loadModule("lab6object.dbx", 0)){
                    acutPrintf("Unable to load Lab6Object.dbx. Unloading this application...\n");
                    return AcRx::kRetError;
                } 
            }
            if (!acrxServiceDictionary->at(EMPLOYEE_ENTRY_SERVICE)){
                acutPrintf("Service % is not present. This must be a wrong version of lab6Object.\n",EMPLOYEE_ENTRY_SERVICE);
                return AcRx::kRetError;
            }
            //register the command
            acedRegCmds->addCommand("OARX_LAB6","addemp","addemp",ACRX_CMD_MODAL,addEmpCommand);
            acedRegCmds->addCommand("OARX_LAB6","removeemp","removeemp",ACRX_CMD_MODAL,removeEmpCommand);
            acedRegCmds->addCommand("OARX_LAB6","listemps","listemps",ACRX_CMD_MODAL,listEmpsCommand);
            break;
        }
    case AcRx::kUnloadAppMsg:
        {
            //remove the command group so that AutoCAD won't call us
            //when we are not here.
            acedRegCmds->removeGroup("OARX_LAB6");
			acrxDynamicLinker->unloadModule ( "lab6object.dbx" );
            break;
        }
    }
    return AcRx::kRetOK;
}