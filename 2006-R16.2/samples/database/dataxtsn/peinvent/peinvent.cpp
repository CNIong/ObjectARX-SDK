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

/* ================  ARX Protocol Extension Example =========================

    Test App for ARX Usage of Protocol Extension in conjunction with the AcDb
    library.

    This specific app features a demonstration of using Xdata along with a
    protocol extension class to store and retrieve per-instance state.  The
    "inventory Id" string managed by this application shows the effective
    addition of a new common member variable to AcDbObject, without affecting
    existing clients of AcDbObject.

    This app defines the AdskObjectInventory Protocol extension class for
    AcDbObject,  and a default implementation.

    In this example, the protocol extension is not really meant to be
    overridden for derived classes.   There is nothing to prevent use of
    XData with protocol extension applications that require a set of
    protocol extension classes to implement polymorphic behavior across
    various classes for a given protocol extension class definition.


    To Use this application:

    There are two commands, GETID and SETID.  For either one, you can either
    pick an entity, or type "H" at the pick prompt, then enter in the
    hexadecimal representation of any object handle (remember, entities are
    objects too!).

    GETID
      will ask the user to select an object,  then print the last known
      inventory Id, or else print a message stating that the object doesn't
      have an Id yet.

    SETID
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

#include "adscodes.h"
#include "acedads.h"

// --- This app's exported Protocol Extension Class
#include "pex.h"

// --- Protocol Extension Objects ---
//
AsdkObjectInventory *pObjectInventory =NULL; // -- MDI Safe

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
void
listInventoryId()
{
    AcDbObject *pObj;
    AcDbObjectId pObjId;
    if ((pObj = selectObject(pObjId, AcDb::kForRead)) == NULL)
        return;

    char *pIdStr;
    ACRX_X_CALL (pObj, AsdkObjectInventory)->inventoryId(pObj, pIdStr);

    pObj->close();

    if (pIdStr == NULL)
        acutPrintf("\nNo Inventory Id for selected object.\n");
    else {
        acutPrintf("\nInventory Id for selected object is: %s\n", pIdStr);
        free(pIdStr);
    }
}

void setInventoryId()
{
    AcDbObjectId pObjId;
    char inventoryId[132];
    AcDbObject *pObj= selectObject(pObjId, AcDb::kForWrite);
    if ( pObj == NULL )
        return;

    if ( acedGetString(Adesk::kFalse, "Enter Inventory Id: ", inventoryId) == RTNORM )
        ACRX_X_CALL (pObj, AsdkObjectInventory)->setInventoryId(pObj, inventoryId);

    pObj->close();
}

// =================== ARx Module Interface Functions ================
//
extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt) {
    switch (msg) {
	case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(pkt);

        // This is an MDI aware application
        acrxDynamicLinker->registerAppMDIAware(pkt);

        // Register the class
        //
        AsdkObjectInventory::rxInit();
        acrxBuildClassHierarchy();

        // Create the protocol extension object.
	    //
	    pObjectInventory = new AsdkObjectInventory();

        // Register the protocol extension object
        // with rightful class object.  Note that defining
        // class is used as key, always.
        //
        AcDbObject::desc()->addX(AsdkObjectInventory::desc(),
            pObjectInventory);

        // Register a couple of commands to set and list
        // inventory Id for objects
        //
        acedRegCmds->addCommand(PE_INVENTORY_GROUP,
                                /*NOXLATE*/"ASDK_GETID",
                                "GETID",
                                ACRX_CMD_TRANSPARENT,
                                listInventoryId);

        acedRegCmds->addCommand(PE_INVENTORY_GROUP,
                                /*NOXLATE*/"ASDK_SETID",
                                "SETID",
                                ACRX_CMD_TRANSPARENT,
                                setInventoryId);

        acrxRegisterService(PE_INVENTORY_SERVICE);

        break;
	case AcRx::kUnloadAppMsg:
        // Clean up after ourselves.
        
        // unregister commands
        //
        acedRegCmds->removeGroup(PE_INVENTORY_GROUP);

        // Unregister, then delete protocol extension object
        //
        AcDbObject::desc()->delX(AsdkObjectInventory::desc());
        delete pObjectInventory;
        
        // remove the protocol extension class definition.
        //
        deleteAcRxClass(AsdkObjectInventory::desc());
        
        // unregister the service
        //
        delete acrxServiceDictionary->remove(PE_INVENTORY_SERVICE);

        break;
    }
    return AcRx::kRetOK;
}
