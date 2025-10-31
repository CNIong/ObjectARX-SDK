//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Source file for the ObjectARX application command "BRLNCNT".

#include "brsample_pch.h"  //precompiled header


// include here



void
lineContainment()
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

	// Query the line by AutoCAD pick
	AcGePoint3d startPt, endPt;
	int hitCount = 0;
	acutPrintf(ACRX_T("\n Pick line for containment test, by selecting two points: \n"));
	acedGetPoint(NULL, ACRX_T("\n Pick origin of line: \n"), asDblArray(startPt));
	acedGetPoint(NULL, ACRX_T("\n Pick another point on line: \n"), asDblArray(endPt));
 	acedGetInt(ACRX_T("\n Number of hits wanted: "), &hitCount);

	// Query the line type
	const AcGeLinearEnt3d* line = NULL;
    ACHAR opt[128];
   	while (Adesk::kTrue) {
		acutPrintf(ACRX_T("\nEnter Line Type: "));
		acedInitGet(NULL, ACRX_T("Infinite Ray Segment"));
		if (acedGetKword(ACRX_T("Infinite/Ray/<Segment>: "), opt) == RTCAN) return;

        // Map the user input to a valid line type
		if ((_tcscmp(opt, ACRX_T("Segment")) == 0) || (_tcscmp(opt, ACRX_T("")) == 0)) {
			line = new AcGeLineSeg3d(startPt, endPt);
			break;
		} else if (_tcscmp(opt, ACRX_T("Ray")) == 0) {
			line = new AcGeRay3d(startPt,endPt);
			break;
		} else if (_tcscmp(opt, ACRX_T("Infinite")) == 0) {
			line = new AcGeLine3d(startPt, endPt);
			break;
		}
	}

	if (line == NULL) {
		acutPrintf(ACRX_T("\n lineContainment: unable to allocate memory for line\n"));
		delete pEnt;
		return;
	}

    Adesk::UInt32 numHitsWanted = (Adesk::UInt32)hitCount;
    Adesk::UInt32 numHitsFound = 0;
    AcBrHit* hits = NULL;

    returnValue = pEnt->getLineContainment(*line, numHitsWanted, numHitsFound, hits);
    if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrEntity::getLineContainment:"));
		errorReport(returnValue);
		delete pEnt;
    	return;
    }

	acutPrintf(ACRX_T("\n Number of hits found: %d"), numHitsFound);

	for (Adesk::UInt32 i = 0; i < numHitsFound; i++) {
		AcBrEntity* entityAssociated = NULL;
		returnValue = hits[i].getEntityAssociated(entityAssociated);
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in AcBrHit::getEntityAssociated:"));
			errorReport(returnValue);
			delete entityAssociated;
			break;
		}
		if (!pEnt->isEqualTo(entityAssociated)) {
			acutPrintf(ACRX_T("\n lineContainment: Hit owner is not the entity we checked line containment against!"));
			delete entityAssociated;
			break;
		}
		
		AcGePoint3d pt;
		returnValue = hits[i].getPoint(pt);
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in AcBrHit::getPoint:"));
			errorReport(returnValue);
			break;
		}

		AcBrEntity* entityHit = NULL;
		returnValue = hits[i].getEntityHit(entityHit);
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in AcBrHit::getEntityHit:"));
			errorReport(returnValue);
			delete entityHit;
			break;
		}

		AcBrEntity* entityEntered = NULL;
		returnValue = hits[i].getEntityEntered(entityEntered);
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in AcBrHit::getEntityEntered:"));
			errorReport(returnValue);
			delete entityHit;
			delete entityEntered;
			break;
		}

		lnContainmentReport(i, pt, entityHit, entityEntered);

		delete entityHit;
		delete entityEntered;
	}

	delete pEnt;
	delete[] hits;

	return;
}
