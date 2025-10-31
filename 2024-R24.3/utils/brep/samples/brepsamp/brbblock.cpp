//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Source file for the ObjectARX application command "BRBBLOCK".

#include "brsample_pch.h"  //precompiled header

//This is been defined for future use. all headers should be under this guard.

// include here



void
dumpBblock()
{ 
    AcBr::ErrorStatus returnValue = AcBr::eOk;

	// Select the entity by type
	AcBrEntity* pEnt = NULL;
	AcDb::SubentType subType = AcDb::kNullSubentType;
	returnValue = selectEntityByType(pEnt, subType);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in selectEntityByType:"));
		errorReport(returnValue);
		delete pEnt;
    	return;
    }

	AcGeBoundBlock3d bblock;

	returnValue = pEnt->getBoundBlock(bblock);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrEntity::getBoundBlock:")); 
		errorReport(returnValue);
		delete pEnt;
		return;
	}
	delete pEnt;

	AcGePoint3d min, max;
	bblock.getMinMaxPoints(min, max);
	bblockReport(min, max);

	return;
}
