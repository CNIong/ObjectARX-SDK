// (C) Copyright 1998 by Autodesk, Inc. 
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
// squareui.cpp
// 
// Example square custom entity UI
//


#include <acdocman.h>
#include <aced.h>
#include <acdb.h>
#include <adslib.h>

#include "squarent.h"

bool append(AcDbEntity* pEntity)
{
    AcDbBlockTable *pBlockTable;

	AcApDocument* pDoc = acDocManager->curDocument();

	Acad::ErrorStatus es = acDocManager->lockDocument(pDoc);
    if (es != Acad::eOk) {
        acedAlert("Failed to lock the document...");
        return false;
    }

	AcDbDatabase* pDb = pDoc->database();
    
    es = pDb->getBlockTable(pBlockTable, AcDb::kForRead);
    if (es != Acad::eOk) {
        acedAlert("Failed to get block table...");
        return false;
    }

    AcDbBlockTableRecord *pBlockRec;
    es = pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockRec, AcDb::kForWrite);
    if (es != Acad::eOk) {
        acedAlert("Failed to get block table record...");
        pBlockTable->close();
        return false;
    }

    es = pBlockRec->appendAcDbEntity(pEntity);
    if (es != Acad::eOk) {
        acedAlert("Failed to append entity...");
        pBlockTable->close();
        pBlockRec->close();
        delete pEntity;
        return false;
    }
    pBlockRec->close();
    pBlockTable->close();
    return true;

}


void aSquare()
{
	
	AsdkSquare* mySquare = new AsdkSquare();

	if( !mySquare ) {
		acutPrintf("\n Memory allocation error.");
		return;
	}

	ads_point pt1, pt2, pt3;
	struct resbuf UCS, WCS;
	
	WCS.restype = RTSHORT;
	WCS.resval.rint = 0;

	UCS.restype = RTSHORT;
	UCS.resval.rint = 1;

	acedGetPoint(NULL, "\nPick a point for the center: ", pt1);
	acedGetPoint(pt1, "\nPick a direction for corner and size: ", pt2);

	pt2[X] = pt2[X] - pt1[X];
	pt2[Y] = pt2[Y] - pt1[Y];
	pt2[Z] = pt2[Z] - pt1[Z];

	pt3[X] = pt3[Y] = 0.0;
	pt3[Z] = 1.0;

	acedTrans(pt1, &UCS, &WCS, 0, pt1);
	acedTrans(pt2, &UCS, &WCS, 1, pt2);
	acedTrans(pt3, &UCS, &WCS, 1, pt3);

	mySquare->setSquareCenter(AcGePoint3d(pt1[X],pt1[Y],pt1[Z]));
	mySquare->setSquareOrient(AcGeVector3d(pt2[X],pt2[Y],pt2[Z]));	
	mySquare->setSquareNormal(AcGeVector3d(pt3[X],pt3[Y],pt3[Z]));

	append(mySquare);

	mySquare->close();

	return;

}

void
initApp()
{
    acutPrintf("AsdkSquare ARX application; Type SQ to execute");

    // register a command with the AutoCAD command mechanism
    //
    acedRegCmds->addCommand("SQUARE_COMMANDS", "ASDKSQUARE", 
							"SQ", ACRX_CMD_MODAL, aSquare);

}


void unloadApp()
{
    
    // Remove the command group added via acedRegCmds->addCommand
    //
    acedRegCmds->removeGroup("SQUARE_COMMANDS");

}

extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
		acrxDynamicLinker->loadModule("square.dbx", true);
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

