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
#include "rxregsvc.h"
#include "lab5CommandUtils.h"
#include "dbents.h"
#include "..\object\lab5objectemployeedetails.h"

//This is used as the key for our custom
//dictionary. Note the registered developer id 'OARX'
//at the beginning
#define DICT "OARXLABS_EMPLOYEE_DICT"

//This is used as the key in our custom dictionary
#define DETAILS "DETAILS"

void addDetailCommand()
{ 
    AcDbDictionary* pEmployeeDict=NULL;
    EmployeeDetails* pEmployeeDetails=NULL;
    //this cannot really happen but...
    if (acdbHostApplicationServices()->workingDatabase()==NULL)
        return;
    try
    {
        //start transaction for the db operations in this command
        actrTransactionManager->startTransaction();
        //prompt the use for the an id
        int id,cubeNumber;
        char strFirstName[133];
        char strLastName[133];
        ads_name ename;
        ads_point pt;
        //get the data from the user
        ADSOK(acedEntSel("Select employee:",ename,pt));
        //do a quick check
        //a more comprehensive check could include 
        //whether we already have the detail object on this candidate
        AcDbObjectId idO;
        ARXOK(acdbGetObjectId(idO,ename));
        AcDbObject* pO;
        ARXOK(actrTransactionManager->getObject(pO,idO,AcDb::kForWrite));
        if (!pO->isKindOf(AcDbBlockReference::desc()))
            throw Acad::eNotThatKindOfClass;
        //go on getting user input
        ADSOK(acedGetInt("Enter employee ID:",&id));
        ADSOK(acedGetInt("Enter cube number:",&cubeNumber));
        ADSOK(acedGetString(0,"Enter employee first name:",strFirstName));
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

        addDictAndEntry(DICT,pExtDict,DETAILS,pEmployeeDetails);

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
        //abort, rollback all db operations
        actrTransactionManager->abortTransaction();
        //check if the user has cancelled us, then we don't report
        //anything
        if (es!=Acad::eUserBreak)
            acutPrintf("***Error: %s\n",acadErrorStatusText(es));
    }
}

void removeDetailCommand()
{ 
    //this cannot really happen but...
    if (acdbHostApplicationServices()->workingDatabase()==NULL)
        return;
    try
    {
        AcDbDictionary* pEmployeeDict=NULL;
        //start transaction for the db operations in this command
        actrTransactionManager->startTransaction();
        AcDbDictionary* pExtDict;
        getExtDictOfObject(pExtDict);
        removeEntryFromDict(DICT,pExtDict,DETAILS);
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

void listDetailCommand()
{
    //this cannot really happen but...
    if (acdbHostApplicationServices()->workingDatabase()==NULL)
        return;
    try
    {
        AcDbDictionary* pExtDict;
        AcDbObjectId idO;
        actrTransactionManager->startTransaction();
        getExtDictOfObject(pExtDict);
        //look for out dictionary
        ARXOK(pExtDict->getAt(DICT,idO));
        //get it for write 
        AcDbObject* pO;
        ARXOK(actrTransactionManager->getObject(pO,idO,AcDb::kForRead));
        //check if someone has else has created an entry with our name
        //that is not a dictionary. This should never happen as long as
        //I use the registered developer ID.
        AcDbDictionary* pEmployeeDict;
        if ((pEmployeeDict=AcDbDictionary::cast(pO))==NULL)
            throw Acad::eNotThatKindOfClass;
        ARXOK(pEmployeeDict->getAt(DETAILS,idO));
        ARXOK(actrTransactionManager->getObject(pO,idO,AcDb::kForRead));
        EmployeeDetails* pEmployeeDetails;
        if ((pEmployeeDetails=EmployeeDetails::cast(pO))==NULL)
            throw Acad::eNotThatKindOfClass;

        acutPrintf("*Employee's ID:%d\n",pEmployeeDetails->ID());
        acutPrintf("*Employee's cube number:%d\n",pEmployeeDetails->cubeNumber());
        acutPrintf("*Employee's first name:%s\n",pEmployeeDetails->firstName());
        acutPrintf("*Employee's last name:%s\n",pEmployeeDetails->lastName());

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
            //check for the service registered by Lab5Object
			acrxDynamicLinker->registerAppMDIAware(pkt);
            AcRxObject* pSvc;
            if (!(pSvc = acrxServiceDictionary->at(EMPLOYEE_DETAILS_SERVICE))){
                //try to load lab5Object if it is not yet present
                if (!acrxDynamicLinker->loadModule("lab5object.dbx", 0)){
                    acutPrintf("Unable to load Lab5Object.dbx. Unloading this application...\n");
                    return AcRx::kRetError;
                } 
            }
            //register the command
            acedRegCmds->addCommand("OARX_LAB5","adddetail","adddetail",ACRX_CMD_MODAL,addDetailCommand);
            acedRegCmds->addCommand("OARX_LAB5","removedetail","removedetail",ACRX_CMD_MODAL,removeDetailCommand);
            acedRegCmds->addCommand("OARX_LAB5","listdetail","listdetail",ACRX_CMD_MODAL,listDetailCommand);
        
            break;
        }
    case AcRx::kUnloadAppMsg:
        {
            //remove the command group so that AutoCAD won't call us
            //when we are not here.
            acedRegCmds->removeGroup("OARX_LAB5");
			// unload "lab5object.dbx"
			acrxDynamicLinker->unloadModule("lab5object.dbx" );
            break;
        }
    }
    return AcRx::kRetOK;
}