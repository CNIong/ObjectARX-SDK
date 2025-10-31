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
#include <dbents.h>
#include <dbsymtb.h>
#include <adscodes.h>
#include <acdb.h>
#include <dbents.h>
#include <actrans.h>
#include "lab6CommandUtils.h"

Acad::ErrorStatus 
postToDatabase(/*[in]*/AcDbEntity* pEnt,/*[out]*/AcDbObjectId& idObj)
//Purpose:
//  Adds an entity to the MODEL_SPACE of the CURRENT database.
//Note:
//  It could be generalized to add it to any block table record of
//  any database, but why complicate it...
//
{
	Acad::ErrorStatus	  es;
	AcDbBlockTable*		pBlockTable;
	AcDbBlockTableRecord*  pSpaceRecord;
    if (acdbHostApplicationServices()->workingDatabase()==NULL)
        return Acad::eNoDatabase;
    //Get a pointer to the current drawing
    //and get the drawing's block table.  Open it for read.
    if ((es = acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead))==Acad::eOk){
	//Get the Model Space record and open it for write.  This will be the owner of the new line.
        if ((es = pBlockTable->getAt(ACDB_MODEL_SPACE, pSpaceRecord, AcDb::kForWrite))==Acad::eOk){
            //Append pEnt to Model Space, then close it and the Model Space record.
            if ((es = pSpaceRecord->appendAcDbEntity(idObj, pEnt))==Acad::eOk)
                pEnt->close();
            pSpaceRecord->close();
        }
    pBlockTable->close();
    }
	//it is good programming practice to return an error status
	return es;
}

Acad::ErrorStatus
RTtoStatus(/*[in]*/int rt)
//Description:
//  Maps an ads return code to an Acad::ErrorStatus
//Note:
//  I don't care about the performance hit that this
//  extra function call introduces.
//  The mapping here is completely arbitrary. Change it if you don't like it.
{
    ACADTRACE("RTtoStatus is mapping %d\n",rt);
    switch (rt){
    case RTNORM:    //5100 /* Request succeeded */
        return Acad::eOk;
    case RTERROR:  //-5001 /* Some other error */
        return Acad::eUnrecoverableErrors ;
    case RTCAN:    //-5002 /* User cancelled request -- Ctl-C */
        return Acad::eUserBreak;
    case RTREJ:    //-5003 /* AutoCAD rejected request -- invalid */
        return Acad::eInvalidInput;
    case RTFAIL:   //-5004 /* Link failure -- Lisp probably died */
        return Acad::eNotApplicable;
    default:
    //case RTKWORD:  //-5005 /* Keyword returned from getxxx() routine */
        //this function only intended to be called 
        //in an error checking situation. See ADSOK.
        assert(0);
        return Acad::eOk;
    }
}

void 
addDictAndEntry(const char* strDictKey, AcDbDictionary* pParent, 
            const char* strEmpKey, AcDbObject* pEmployee) 
{
    AcDbObjectId idO;
    AcDbDictionary* pEmployeeDict;
    //unerase the dictionary if it was erased
    if (pParent->isErased())
        ARXOK(pParent->erase(Adesk::kFalse));
    //see if our dictionary is already there
    if (pParent->getAt(strDictKey,idO)==Acad::eKeyNotFound){
        //create it if not
        if ((pEmployeeDict=new AcDbDictionary)==NULL)
            throw Acad::eOutOfMemory;
        Acad::ErrorStatus es;
        if ((es=pParent->setAt(strDictKey,pEmployeeDict,idO))!=Acad::eOk){
            //make sure that we don't leak memory
            //a smart pointer would come handy but let's not confuse
            //everyone quite yet
            delete pEmployeeDict;
            throw es;
        }
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
    if ((es=pEmployeeDict->getAt(strEmpKey,idO))==Acad::eOk)
        throw Acad::eAlreadyInDb;
    if (es!=Acad::eKeyNotFound)
        throw es;
    ARXOK(pEmployeeDict->setAt(strEmpKey,pEmployee,idO));
    //this will ensure that the newly added object is properly 
    //committed to the db when the transaction ends
    actrTransactionManager->addNewlyCreatedDBRObject(pEmployee);
}

void
removeEntryFromDict(const char* strDictKey, AcDbDictionary* pParent, 
            const char* strEmpKey) 
{
    AcDbObjectId idO;
    //see if our dictionary is there
    ARXOK(pParent->getAt(strDictKey,idO));
    //get it for write 
    AcDbObject* pO;
    ARXOK(actrTransactionManager->getObject(pO,idO,AcDb::kForWrite));
    //check if someone has else has created an entry with our name
    //that is not a dictionary. This should never happen as long as
    //I use the registered developer ID.
    AcDbDictionary* pEmployeeDict;
    if ((pEmployeeDict=AcDbDictionary::cast(pO))==NULL)
        throw Acad::eNotThatKindOfClass;
    //check if a record with this key isthere
    ARXOK(pEmployeeDict->getAt(strEmpKey,idO));
    //get it for write 
    ARXOK(actrTransactionManager->getObject(pO,idO,AcDb::kForWrite));
    //and erase it
    ARXOK(pO->erase());
    //erase dictionary if it has no more entries
    if (pParent->numEntries()==0)
        ARXOK(pParent->erase());
}

void
getExtDictOfObject(AcDbDictionary*& pExtDict)
{
    ads_name ename;
    ads_point pt;

    ADSOK(acedEntSel("Select employee:",ename,pt));
    //do a quick check
    //a more comprehensive check could include 
    //whether we already have the detail object on this candidate
    AcDbObjectId idO;
    ARXOK(acdbGetObjectId(idO,ename));
    AcDbObject* pO;
    ARXOK(actrTransactionManager->getObject(pO,idO,AcDb::kForRead));
    if (!pO->isKindOf(AcDbBlockReference::desc()))
        throw Acad::eNotThatKindOfClass;        
    if ((idO = pO->extensionDictionary())==AcDbObjectId::kNull)
        throw Acad::eKeyNotFound;
    //make sure that you open erased extension dictionaries
    ARXOK(actrTransactionManager->getObject((AcDbObject*&)pExtDict,idO,AcDb::kForWrite, Adesk::kTrue));
    if (pExtDict->isErased())
        ARXOK(pExtDict->erase(Adesk::kFalse));
}
