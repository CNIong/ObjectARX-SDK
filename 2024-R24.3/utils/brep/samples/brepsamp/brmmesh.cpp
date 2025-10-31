//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Source file for the ObjectARX application command "BRMESH".

#include "brsample_pch.h"  //precompiled header


// include here



void
meshModel()
{
    AcBr::ErrorStatus returnValue = AcBr::eOk;

	// Query the mesh dump style
	Adesk::Boolean displayElements = Adesk::kTrue;
    ACHAR opt[128];
   	while (Adesk::kTrue) {
		acutPrintf(ACRX_T("\nSelect Style for Mesh Dump: "));
		acedInitGet(NULL, ACRX_T("Coordinates Polylines"));
		if (acedGetKword(ACRX_T("Coordinates/<Polylines>: "), opt) == RTCAN) return;

        // Map the user input to a valid dump style
		if ((_tcscmp(opt, ACRX_T("Polylines")) == 0) || (_tcscmp(opt, ACRX_T("")) == 0)) {
            displayElements = Adesk::kTrue;
            break;
        } else if ((_tcscmp(opt, ACRX_T("Coordinates")) == 0)) {
            displayElements = Adesk::kFalse;
            break;
	    }
    }

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

    // Call the appropriate subentity mesh routine
	switch (subType) {
	case AcDb::kNullSubentType:
		// brep
		returnValue	= brepMesh((const AcBrBrep&)(*pEnt), displayElements);
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in brepMesh:")); 
			errorReport(returnValue);
		}
		break;
    case AcDb::kFaceSubentType:
		// face
		returnValue = faceMesh((const AcBrFace&)(*pEnt), displayElements);
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in faceMesh:"));
			errorReport(returnValue);
		}
        break;
    default:
        acutPrintf(ACRX_T("\n meshModel: unsupported subentity type: %d\n"), subType);
        break;
	}

	delete pEnt;

	return;
}
