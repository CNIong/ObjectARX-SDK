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
// deepclon.cpp


#include <string.h>
#include <stdlib.h>
#include <aced.h>
#include <dbents.h>
#include <dbsymtb.h>
#include <adslib.h>
#include <geassign.h>
#include <dbidmap.h>
#include <dbapserv.h>

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

void
cloneSameOwnerObjects()
{
    // Step 1:  Obtain the set of objects to be cloned

    ads_name sset;
    if (acedSSGet(NULL, NULL, NULL, NULL, sset) != RTNORM) {
        acutPrintf("\nNothing selected");
        return;
    }

    // Step 2: Add obtained objectIds to list of objects
    // to be cloned

    long length;
    acedSSLength(sset, &length);

    AcDbObjectIdArray  objList;
    AcDbObjectId ownerId = AcDbObjectId::kNull;
    for (int i = 0; i < length; i++) {
        ads_name ent;
        acedSSName(sset, i, ent);

        AcDbObjectId objId;
        acdbGetObjectId(objId, ent);

        // check to be sure same owner as first object
        //
        AcDbObject *pObj;
        acdbOpenObject(pObj, objId, AcDb::kForRead);

        if (pObj->ownerId() == ownerId)
            objList.append(objId);
        else if (i == 0) {
            ownerId = pObj->ownerId();
            objList.append(objId);
        }
        pObj->close();
    }
    acedSSFree(sset);

    // Step 3: Get the objectId of the desired owner for
    // the cloned objects.  We'll use Model Space for
    // this example.

    AcDbBlockTable *pBlockTable;
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);

    AcDbObjectId  modelSpaceId;
    pBlockTable->getAt(ACDB_MODEL_SPACE, modelSpaceId);
    pBlockTable->close();

    // Step 4:  Create a new ID map
    //
    AcDbIdMapping idMap;

    // Step 5: Call deepCloneObjects()
    //
    acdbHostApplicationServices()->workingDatabase()
        ->deepCloneObjects(objList, modelSpaceId, idMap);

    // Now we can go through the idMap and do whatever we'd
    // like to the original and/or clone objects.
    //
    // For this example we'll print out the objectId's of
    // the new objects resulting from the cloning process
    
    AcDbIdMappingIter iter(idMap);
    for (iter.start(); !iter.done(); iter.next()) {
        AcDbIdPair idPair;
        iter.getMap(idPair);
        if (!idPair.isCloned())
            continue;

        acutPrintf("\nObjectId is: %Ld",
            idPair.value().asOldId());
    }
}

void
cloneDiffOwnerObjects()
{
    // Step 1:  Obtain the set of objects to be cloned.
    // For the two owners we'll use Model Space and
    // Paper Space,  so we'll need to do two acedSSGet
	// calls.

    acutPrintf("\nSelect entities to be cloned to"
        " Model Space");
    
    ads_name ssetMS;
    acedSSGet(NULL, NULL, NULL, NULL, ssetMS);

    long lengthMS;
    acedSSLength(ssetMS, &lengthMS);

    acutPrintf("\nSelect entities to be cloned to"
        " Paper Space");

    ads_name ssetPS;
    if (acedSSGet(NULL, NULL, NULL, NULL, ssetPS)
        != RTNORM && lengthMS == 0)
    {
        acutPrintf("\nNothing selected");
        return;
    }
    long lengthPS;
    acedSSLength(ssetPS, &lengthPS);
   
    // Step 2: Add obtained objectIds to lists of
    // objects to be cloned,  one list for objects to
    // be owned by Model Space and one for those to
    // be owned by Paper Space.
    
    AcDbObjectId ownerId = AcDbObjectId::kNull;

    // For Model Space
    //
    AcDbObjectIdArray  objListMS;
    for (int i = 0; i < lengthMS; i++) {
        ads_name ent;
        acedSSName(ssetMS, i, ent);

        AcDbObjectId objId;
        acdbGetObjectId(objId, ent);

        // check to be sure same owner as first object
        //
        AcDbObject *pObj;
        acdbOpenObject(pObj, objId, AcDb::kForRead);

        if (pObj->ownerId() == ownerId)
            objListMS.append(objId);
        else if (i == 0) {
            ownerId = pObj->ownerId();
            objListMS.append(objId);
        }
        pObj->close();
    }
    acedSSFree(ssetMS);

    // For Paper Space
    //
    ownerId = AcDbObjectId::kNull;
    AcDbObjectIdArray  objListPS;
    for (i = 0; i < lengthPS; i++) {
        ads_name ent;
        acedSSName(ssetPS, i, ent);

        AcDbObjectId objId;
        acdbGetObjectId(objId, ent);

        // check to be sure same owner as first object
        //
        AcDbObject *pObj;
        acdbOpenObject(pObj, objId, AcDb::kForRead);

        if (pObj->ownerId() == ownerId)
            objListPS.append(objId);
        else if (i == 0) {
            ownerId = pObj->ownerId();
            objListPS.append(objId);
        }
        pObj->close();
    }
    acedSSFree(ssetPS);

    // Step 3: Get the objectId of the desired owners for
    // the cloned objects.  We're using Model Space and
    // Paper Space for this example.
    
    AcDbBlockTable *pBlockTable;
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);

    AcDbObjectId  modelSpaceId, paperSpaceId;
    pBlockTable->getAt(ACDB_MODEL_SPACE, modelSpaceId);
    pBlockTable->getAt(ACDB_PAPER_SPACE, paperSpaceId);
    pBlockTable->close();

    // Step 4:  Create a new ID map
    //
    AcDbIdMapping idMap;

    // Step 5: Call deepCloneObjects()
    
    acdbHostApplicationServices()->workingDatabase()
        ->deepCloneObjects(objListMS, modelSpaceId, idMap, Adesk::kTrue);

    acdbHostApplicationServices()->workingDatabase()
        ->deepCloneObjects(objListPS, paperSpaceId, idMap);

    // Now we can go through the idMap and do whatever we'd
    // like to the original and/or clone objects.
    //
    // For this example we'll print out the objectId's of
    // the new objects resulting from the cloning process
    //
    AcDbIdMappingIter iter(idMap);
    for (iter.start(); !iter.done(); iter.next()) {
        AcDbIdPair idPair;
        iter.getMap(idPair);
        if (!idPair.isCloned())
            continue;

        acutPrintf("\nObjectId is: %Ld",
            idPair.value().asOldId());
    }
}

// END CODE APPEARING IN SDK DOCUMENT.

void
initApp()
{
    acedRegCmds->addCommand("ASDK_DEEPCLONEOBJECTS",
                            "ASDK_SAMEOWNER",
                            "SAMEOWNER",
                            ACRX_CMD_MODAL,
                            cloneSameOwnerObjects);

    acedRegCmds->addCommand("ASDK_DEEPCLONEOBJECTS",
                            "ASDK_DIFFOWNER",
                            "DIFFOWNER",
                            ACRX_CMD_MODAL,
                            cloneDiffOwnerObjects);
}

void
unloadApp()
{
    acedRegCmds->removeGroup("ASDK_DEEPCLONEOBJECTS");
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
