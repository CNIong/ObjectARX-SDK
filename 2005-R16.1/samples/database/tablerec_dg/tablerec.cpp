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
// Description:
//
// This program demonstrates creating a symbol table record
// (specifically a layer table record) filling in the
// required data, and then adding it to the layer table.
// 
// One command is defined, ADDLAYER, which calls the
// function addLayer

#include <rxobject.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbsymtb.h>
#include <dbapserv.h>
#include <adslib.h>

void addLayer();
void initApp();
void unloadApp();
extern "C"
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);


// This function creates a new AcDbLayerTableRecord, fills
// it in, and adds it to the layer table
// 
// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.
//
void
addLayer()
{
    AcDbLayerTable *pLayerTbl;
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pLayerTbl, AcDb::kForWrite);

    if (!pLayerTbl->has("ASDK_TESTLAYER")) {
        AcDbLayerTableRecord *pLayerTblRcd
            = new AcDbLayerTableRecord;
        pLayerTblRcd->setName("ASDK_TESTLAYER");
        pLayerTblRcd->setIsFrozen(0);// layer to THAWED
        pLayerTblRcd->setIsOff(0);   // layer to ON
        pLayerTblRcd->setVPDFLT(0);  // viewport default
        pLayerTblRcd->setIsLocked(0);// un-locked

        AcCmColor color;
        color.setColorIndex(1); // set color to red
        pLayerTblRcd->setColor(color);

        // For linetype, we need to provide the object ID of
        // the linetype record for the linetype we want to
        // use.  First, we need to get the object ID.
	//
        AcDbLinetypeTable *pLinetypeTbl;
        AcDbObjectId ltId;
        acdbHostApplicationServices()->workingDatabase()
            ->getSymbolTable(pLinetypeTbl, AcDb::kForRead);
        if ((pLinetypeTbl->getAt("DASHED", ltId))
            != Acad::eOk)
        {
            acutPrintf("\nUnable to find DASHED"
                " linetype. Using CONTINUOUS");
            
            // CONTINUOUS is in every drawing, so use it.
            //
            pLinetypeTbl->getAt("CONTINUOUS", ltId);
        }
        pLinetypeTbl->close();

        pLayerTblRcd->setLinetypeObjectId(ltId);
        pLayerTbl->add(pLayerTblRcd);
        pLayerTblRcd->close();
        pLayerTbl->close();
    } else {
        pLayerTbl->close();
        acutPrintf("\nlayer already exists");
    }
}

// END CODE APPEARING IN SDK DOCUMENT.

// Initialization function called in acrxEntryPoint during
// the kInitAppMsg case.  This is where commands are added
// to the AcEd command stack.
// 
void
initApp()
{
    acedRegCmds->addCommand("ASDK_TABLETEST_COMMANDS",
        "ASDK_ADDLAYER", "ADDLAYER", ACRX_CMD_MODAL,
        addLayer);
}

// Clean up function called in acrxEntryPoint during the
// kUnloadAppMsg case.  This app's command group is removed
// from the AcEd command stack.
// 
void
unloadApp()
{
    acedRegCmds->removeGroup("ASDK_TABLETEST_COMMANDS");
}


// ARX entry point.
//
AcRx::AppRetCode
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
