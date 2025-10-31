// (C) Copyright 1997-2006 by Autodesk, Inc. 
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
