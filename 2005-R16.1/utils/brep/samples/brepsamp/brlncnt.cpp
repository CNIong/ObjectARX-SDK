// (C) Copyright 1996-1999 by Autodesk, Inc. 
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
// DESCRIPTION:
//
// Source file for the ObjectARX application command "BRLNCNT".

#include "brsample_pch.h"  //precompiled header

void
lineContainment()
{
    AcBr::ErrorStatus returnValue = AcBr::eOk;

	// Select the entity by type
	AcBrEntity* pEnt = NULL;
	AcDb::SubentType subType = AcDb::kNullSubentType;
	returnValue = selectEntityByType(pEnt, subType);
	if (returnValue != AcBr::eOk) {
		acutPrintf("\n Error in selectEntityByType:");
		errorReport(returnValue);
		delete pEnt;
    	return;
    }

	// Query the line by AutoCAD pick
	AcGePoint3d startPt, endPt;
	int hitCount = 0;
	acutPrintf("\n Pick line for containment test, by selecting two points: \n");
	acedGetPoint(NULL, "\n Pick origin of line: \n", asDblArray(startPt));
	acedGetPoint(NULL, "\n Pick another point on line: \n", asDblArray(endPt));
 	acedGetInt("\n Number of hits wanted: ", &hitCount);

	// Query the line type
	const AcGeLinearEnt3d* line = NULL;
    char opt[128];
   	while (Adesk::kTrue) {
		acutPrintf("\nEnter Line Type: ");
		acedInitGet(NULL, "Infinite Ray Segment");
		if (acedGetKword("Infinite/Ray/<Segment>: ", opt) == RTCAN) return;

        // Map the user input to a valid line type
		if ((strcmp(opt, "Segment") == 0) || (strcmp(opt, "") == 0)) {
			line = new AcGeLineSeg3d(startPt, endPt);
			break;
		} else if (strcmp(opt, "Ray") == 0) {
			line = new AcGeRay3d(startPt,endPt);
			break;
		} else if (strcmp(opt, "Infinite") == 0) {
			line = new AcGeLine3d(startPt, endPt);
			break;
		}
	}

	if (line == NULL) {
		acutPrintf("\n lineContainment: unable to allocate memory for line\n");
		delete pEnt;
		return;
	}

    Adesk::UInt32 numHitsWanted = (Adesk::UInt32)hitCount;
    Adesk::UInt32 numHitsFound = 0;
    AcBrHit* hits = NULL;

    returnValue = pEnt->getLineContainment(*line, numHitsWanted, numHitsFound, hits);
    if (returnValue != AcBr::eOk) {
		acutPrintf("\n Error in AcBrEntity::getLineContainment:");
		errorReport(returnValue);
		delete pEnt;
    	return;
    }

	acutPrintf("\n Number of hits found: %d", numHitsFound);

	for (Adesk::UInt32 i = 0; i < numHitsFound; i++) {
		AcBrEntity* entityAssociated = NULL;
		returnValue = hits[i].getEntityAssociated(entityAssociated);
		if (returnValue != AcBr::eOk) {
			acutPrintf("\n Error in AcBrHit::getEntityAssociated:");
			errorReport(returnValue);
			delete entityAssociated;
			break;
		}
		if (!pEnt->isEqualTo(entityAssociated)) {
			acutPrintf("\n lineContainment: Hit owner is not the entity we checked line containment against!");
			delete entityAssociated;
			break;
		}
		
		AcGePoint3d pt;
		returnValue = hits[i].getPoint(pt);
		if (returnValue != AcBr::eOk) {
			acutPrintf("\n Error in AcBrHit::getPoint:");
			errorReport(returnValue);
			break;
		}

		AcBrEntity* entityHit = NULL;
		returnValue = hits[i].getEntityHit(entityHit);
		if (returnValue != AcBr::eOk) {
			acutPrintf("\n Error in AcBrHit::getEntityHit:");
			errorReport(returnValue);
			delete entityHit;
			break;
		}

		AcBrEntity* entityEntered = NULL;
		returnValue = hits[i].getEntityEntered(entityEntered);
		if (returnValue != AcBr::eOk) {
			acutPrintf("\n Error in AcBrHit::getEntityEntered:");
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
