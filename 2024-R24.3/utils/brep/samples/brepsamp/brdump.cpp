//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Source file for the ObjectARX application command "BRDUMP".

#include "brsample_pch.h"  //precompiled header

// include here



void
dumpModel()
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

	switch (subType) {
	case AcDb::kNullSubentType:
		// brep
		returnValue	= brepDump((const AcBrBrep&)(*pEnt));
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in brepDump:")); 
			errorReport(returnValue);
			return;
		}
		break;
    case AcDb::kFaceSubentType:
		// face
		returnValue = faceDump((const AcBrFace&)(*pEnt));
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in faceDump:"));
			errorReport(returnValue);
			return;
		}
        break;
    case AcDb::kEdgeSubentType:
	    // edge
		returnValue = edgeDump((const AcBrEdge&)(*pEnt));
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in edgeDump:"));
			errorReport(returnValue);
			return;
		}
		break;  
    default:
        acutPrintf(ACRX_T("\n dumpModel: unsupported subentity type: %d\n"), subType);
        return;
	}
	delete pEnt;

	return;
}
