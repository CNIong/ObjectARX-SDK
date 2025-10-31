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

/* ========= EDINVENT:  ARX Extension Dictionary Example ================ 

    This Application demonstrates basic Usage of of the AcDbObject Extension
    Dictionary.  It presents a mechanism for attaching an arbitrary string to
    any AcDbObject, as an "inventory Id".

    The "inventory Id" string managed by this application shows the effective
    addition of a new common member variable to AcDbObject, without affecting
    existing clients of AcDbObject.

    To do this,  the class AsdkInventoryData is derived directly from
    AcDbObject.  Objects of this class are added to the extension dictionaries
    of entities thus adding the "inventory Id" data to these objects.

    In this example, the one object class is not meant to be overridden with
    different objects under the same extension dictionary entry name, but
    there is nothing to prevent this from being done to implement
    polymorphic behavior across various classes for a given protocol extension
    class definition.

    Extending an object via the extension dictionary is rather cumbersome to
    program, and incurs some 70-100 bytes of overhead per attached extension
    object.  But, this attached object has no limits on size or content, AND
    it can be defined and used as a persistent reactor, and thus actively
    monitor database and system events.  That can be worth a few extra bytes
    for some cases. So if you have either a huge object, or one that demands
    to be notified of changes in any object in the system, especially its
    owner object, then this may be the extension mechanism for you.  It is
    fully supported in the R13c0 DWG file format.  Unfortunately, it
    was broken in DXF until R13c4

    There are two commands defined in this program:

    GET_ID
      will ask the user to select an object,  then print the last known
      inventory Id, or else print a message stating that the object doesn't
      have an Id yet.

    SET_ID
      will prompt for an object first, then a string to be attached to it as
      the Inventory Id.

    For either command, you can either pick an entity, or type "H" at the
    pick prompt, then enter in the hexadecimal representation of any object
    handle (remember, entities are objects too!).

    The code checks for most things that can go wrong, but if something does
    go wrong, the resulting messages may not be very informative.
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "rxregsvc.h"
#include "aced.h"

#include "dbdict.h"

#include "adscodes.h"
#include "acedads.h"

// This app's exported Extension Object Class

#include "edinvent.h"

// --- Select Entity
//
AcDbObject*
selectObject(AcDbObjectId& eId, AcDb::OpenMode openMode)
{
    // Allow user to either pick an entity, or type in the object handle.
    //
    ads_name en;
    ads_point pt;
    acedInitGet(RSG_OTHER, "Handle _Handle");
    int ss = acedEntSel(
                "\nSelect an Entity or enter 'H' to any enter object handle: ",
                en, pt
             );

    char handleStr[132];
    switch (ss) {
    case RTNORM:   // got it!
        break;
    case RTKWORD:
        if ((acedGetString(Adesk::kFalse, "Enter Valid Object Handle: ",
            handleStr) == RTNORM) && (acdbHandEnt(handleStr, en) == RTNORM))
            break;
    // Fall-through intentional
    //
    default:
        acutPrintf("Nothing Selected, Return Code==%d\n", ss);
        return NULL;
    }

    // Now, exchange the old-fangled ads_name for the new-fangled
    // object id...
    //
    Acad::ErrorStatus retStat = acdbGetObjectId(eId, en);
    if (retStat != Acad::eOk) {
        acutPrintf("\nacdbGetObjectId failed");
        acutPrintf(/*NOXLATE*/"\nen==(%lx,%lx), retStat==%d\n", en[0], en[1], eId);
        return NULL;
    }

    AcDbObject *pObj;
    if ((retStat = acdbOpenObject(pObj, eId, openMode)) != Acad::eOk) {
        acutPrintf("\nacdbOpenEntity failed: ename=(%lx,%lx), mode==%d"
	        " retStat==%d\n", en[0], en[1], openMode, retStat);
        return NULL;
    }
    return pObj;
}

// =================== Commands defined in this Module ================
//
static void
commonOpen(AcDbObjectId& pObjId,
           AcDb::OpenMode  mode,
           AcDbObject*& pObj,
           AcDbDictionary*& pXDict,
           AsdkInventoryData*& pIObj)
{
    // Get the main object.
    //
    pObj = NULL;
    pObjId =AcDbObjectId::kNull;
    if ((pObj = selectObject(pObjId, mode)) == NULL)
        return;

    // Get extension dictionary object Id
    //
    pXDict =NULL;
    AcDbObjectId xDictId = pObj->extensionDictionary();

    // If there is no dictionary to be opened,
    // then there are no relevant contents.
    //
    if (xDictId == AcDbObjectId::kNull) {
        if (mode != AcDb::kForWrite)
            return;

        // This next step should never fail.
    	//
        if (pObj->createExtensionDictionary() != Acad::eOk)
            return;

        // This next step should also never fail.
    	//
        if ((xDictId = pObj->extensionDictionary()) == AcDbObjectId::kNull)
            return;
    }

    // Open the dictionary, if we can.
    //
    if (acdbOpenObject(pXDict, xDictId, mode) != Acad::eOk)
        return;

    // Now, get and open the inventory object, if it is there.
    // If we can't open it, that's OK for now.
    //
    pIObj = NULL;
    pXDict->getAt(ED_INVENTORY_SERVICE, ((AcDbObject*&) pIObj), mode);
}


void
listInventoryId()
{
    AcDbObjectId pObjId;
    AcDbObject* pObj;
    AcDbDictionary* xDict;
    AsdkInventoryData* iObj;

    commonOpen(pObjId, AcDb::kForRead, pObj, xDict, iObj);

    // No Object or no extension dictionary means
    // there is nothing to do.
    //
    if (pObj == NULL)
        return;

    char *idStr = NULL;
    if (iObj != NULL)
        idStr = iObj->inventoryId();

    if (idStr == NULL)
        acutPrintf("\nNo Inventory Id for selected object.\n");
    else {
        acutPrintf("\nInventory Id for selected object is: %s\n", idStr);
        free(idStr);
    }

    if (iObj != NULL)
        iObj->close();
    if (xDict != NULL)
        xDict->close();
    if (pObj != NULL)
        pObj->close();
}

void
setInventoryId()
{
    AcDbObjectId pObjId;
    AcDbObject* pObj;
    AcDbDictionary* pXDict;
    AsdkInventoryData* pIObj;

    commonOpen(pObjId, AcDb::kForWrite, pObj, pXDict, pIObj);

    // No Object or no extension dictionary means
    // there is nothing to do.
    //
    if (pObj == NULL)
        return;

    if (pXDict == NULL) {
        pObj->close();
        return;
    }

    char inventoryId[255];
    if (acedGetString(Adesk::kFalse, "Enter Inventory Id: ", inventoryId) != RTNORM)
    {
        pObj->close();
        pXDict->close();
        if (pIObj != NULL)
	        pIObj->close();
        return;
    }

    // No inventory object id in the extension dictionary means
    // it is time to create one.
    //
    if (pIObj == NULL) {
        AcDbObjectId iObjId;
        pIObj = new AsdkInventoryData;
        if (pXDict->setAt(ED_INVENTORY_SERVICE, pIObj, iObjId) != Acad::eOk) {
	        delete pIObj;
            pXDict->close();
            pObj->close();
            return;
        }
    }
    pIObj->setInventoryId(inventoryId);

    pIObj->close();
    pXDict->close();
    pObj->close();
}

// =================== ARx Module Interface Functions ================
//
extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt) {
    switch (msg) {
	case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(pkt);

        // This is an MDI aware application
        acrxDynamicLinker->registerAppMDIAware(pkt);

        // Register the class
        //
        AsdkInventoryData::rxInit();
        acrxBuildClassHierarchy();

        // Register a couple of commands to set and list
        // inventory Id for objects
        //
        acedRegCmds->addCommand(ED_INVENTORY_GROUP,
                                /*NOXLATE*/"ASDK_GET_ID",
                                "GET_ID",
                                ACRX_CMD_TRANSPARENT,
                                listInventoryId);

        acedRegCmds->addCommand(ED_INVENTORY_GROUP,
                                /*NOXLATE*/"ASDK_SET_ID",
                                "SET_ID",
                                ACRX_CMD_TRANSPARENT,
                                setInventoryId);

        acrxRegisterService(ED_INVENTORY_SERVICE);

        break;
    case AcRx::kUnloadAppMsg:
        // Clean up after ourselves.

        // unregister commands
        //
        acedRegCmds->removeGroup(ED_INVENTORY_GROUP);

        // remove the protocol extension class definition.
        //
        deleteAcRxClass(AsdkInventoryData::desc());

        // unregister the service
        //
        delete acrxServiceDictionary->remove(ED_INVENTORY_SERVICE);

        break;
    }
    return AcRx::kRetOK;
}
