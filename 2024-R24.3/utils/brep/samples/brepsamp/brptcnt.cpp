//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Source file for the ObjectARX application command "BRPTCNT".

#include "brsample_pch.h"  //precompiled header


// include here



void
pointContainment()
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

	// Query the point by AutoCAD pick
	AcGePoint3d testPt;
	acedGetPoint(NULL, ACRX_T("\n Pick point for containment test: \n"), asDblArray(testPt));

    AcGe::PointContainment containment = AcGe::kOutside;
    AcBrEntity* container = NULL;

    returnValue = pEnt->getPointContainment(testPt, containment, container);
    if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrEntity::getPointContainment:"));
		errorReport(returnValue);
		delete pEnt;
    	return;
    }

    ptContainmentReport(containment, container);

	delete container;
	delete pEnt;

	return;
}
