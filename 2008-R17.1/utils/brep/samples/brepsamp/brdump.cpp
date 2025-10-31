// (C) Copyright 1996-2006 by Autodesk, Inc. 
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
