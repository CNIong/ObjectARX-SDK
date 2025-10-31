//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Source file for Autocad entity/subentity selection.

#include "brsample_pch.h"  //precompiled header


// include here



// local function prototypes
static AcBr::ValidationLevel validationLevel();
static Adesk::Boolean		 localContext();
static AcDb::SubentType		 subtype();


AcBr::ErrorStatus
selectEntityByType(AcBrEntity*& pEnt, AcDb::SubentType& subType)
{
	Acad::ErrorStatus acadReturnValue = Acad::eOk;
	AcBr::ErrorStatus returnValue = AcBr::eOk;

	// Query validation level
	AcBr::ValidationLevel vlevel = validationLevel();

	// Query the subentity type
	subType = subtype();

	// Query whether to select a database entity or create a new one
	Adesk::Boolean context = (subType != AcDb::kNullSubentType)
		? Adesk::kFalse : localContext();

	if (!context) {
		// Query the subentity by AutoCAD pick and get the subentity path
		AcDbFullSubentPath subPath(kNullSubent);
		acadReturnValue = selectEntity(subType, subPath);
		if (acadReturnValue != Acad::eOk) {
			acutPrintf(ACRX_T("\n Error in selectEntity: %d"), acadReturnValue);
			return (AcBr::ErrorStatus)acadReturnValue;
		}

		// Call the appropriate subentity constructor
		switch (subType) {
		case AcDb::kNullSubentType:
    		pEnt = new AcBrBrep();
			break;
		case AcDb::kFaceSubentType:
    		pEnt = new AcBrFace();
			break;
		case AcDb::kEdgeSubentType:
    		pEnt = new AcBrEdge();
			break;  
		default:
			acutPrintf(ACRX_T("\n selectEntityByType: unsupported subentity type: %d\n"), subType);
			returnValue = (AcBr::ErrorStatus)Acad::eWrongSubentityType;
			return returnValue;
		}
		if (pEnt == NULL) {
			acutPrintf(ACRX_T("\n selectEntityByType: unable to allocate memory\n"));
			returnValue = (AcBr::ErrorStatus)Acad::eOutOfMemory;
			return returnValue;
		}

		returnValue = pEnt->set(subPath);
		if (returnValue != AcBr::eOk) {
    		acutPrintf(ACRX_T("\n Error in AcBrEntity::set:"));
    		errorReport(returnValue);
    		return returnValue;
		}
	} else {
		// Create the entity as a local object
		AcDbEntity* pEntity;
		acadReturnValue = createEntity(pEntity);
		if (acadReturnValue != Acad::eOk) {
			acutPrintf(ACRX_T("\n Error in createEntity: %d"), acadReturnValue);
			return (AcBr::ErrorStatus)acadReturnValue;
		}
		if (pEntity == NULL) {
			acutPrintf(ACRX_T("\n selectEntityByType: unable to allocate memory\n"));
			returnValue = (AcBr::ErrorStatus)Acad::eOutOfMemory;
			return returnValue;
		}

    	pEnt = new AcBrBrep();
		if (pEnt == NULL) {
			acutPrintf(ACRX_T("\n selectEntityByType: unable to allocate memory\n"));
			returnValue = (AcBr::ErrorStatus)Acad::eOutOfMemory;
			return returnValue;
		}

		returnValue = ((AcBrBrep*)pEnt)->set((const AcDbEntity&)*pEntity);
		if (returnValue != AcBr::eOk) {
    		acutPrintf(ACRX_T("\n Error in AcBrEntity::set:"));
    		errorReport(returnValue);
    		return returnValue;
		}
	}

	returnValue = pEnt->setValidationLevel(vlevel);
	if (returnValue != AcBr::eOk) {
    	acutPrintf(ACRX_T("\n Error in AcBrEntity::setValidationLevel:"));
    	errorReport(returnValue);
    	return returnValue;
	}

	return returnValue;
}


static AcBr::ValidationLevel
validationLevel()
{
	// Query validation level for model
	AcBr::ValidationLevel vlevel = AcBr::kFullValidation;
    ACHAR opt[128];
   	while (Adesk::kTrue) {
		acutPrintf(ACRX_T("\nSelect No Validation vs. Full Validation: "));
		acedInitGet(NULL, ACRX_T("None Full"));
		if (acedGetKword(ACRX_T("None/<Full>: "), opt) == RTCAN) break;
		if ((_tcscmp(opt, ACRX_T("Full")) == 0) || (_tcscmp(opt, ACRX_T("")) == 0)) {
            vlevel = AcBr::kFullValidation;
            break;
        } else if ((_tcscmp(opt, ACRX_T("None")) == 0)) {
            vlevel = AcBr::kNoValidation;
            break;
	    }
    }

	return vlevel;
}


static Adesk::Boolean
localContext()
{
	// Query local vs. database context for model
	Adesk::Boolean context = Adesk::kFalse;
    ACHAR opt[128];
   	while (Adesk::kTrue) {
		acutPrintf(ACRX_T("\nSelect Local Entity vs. Database Entity: "));
		acedInitGet(NULL, ACRX_T("Local Database"));
		if (acedGetKword(ACRX_T("Local/<Database>: "), opt) == RTCAN) break;
		if ((_tcscmp(opt, ACRX_T("Database")) == 0) || (_tcscmp(opt, ACRX_T("")) == 0)) {
            context = Adesk::kFalse;
            break;
        } else if ((_tcscmp(opt, ACRX_T("Local")) == 0)) {
            context = Adesk::kTrue;
            break;
	    }
    }

	return context;
}


static AcDb::SubentType
subtype()
{
	// Query the subentity type
	AcDb::SubentType subType = AcDb::kNullSubentType;
    ACHAR opt[128];
   	while (Adesk::kTrue) {
		acutPrintf(ACRX_T("\nEnter Subent Type: "));
		acedInitGet(NULL, ACRX_T("Edge Face Brep"));
		if (acedGetKword(ACRX_T("Edge/Face/<Brep>: "), opt) == RTCAN) {
			subType = AcDb::kNullSubentType;
			break;
		}

        // Map the user input to a valid subentity type
		if ((_tcscmp(opt, ACRX_T("Brep")) == 0) || (_tcscmp(opt, ACRX_T("")) == 0)) {
			subType = AcDb::kNullSubentType;
			break;
        } else if (_tcscmp(opt, ACRX_T("Face")) == 0) {
			subType = AcDb::kFaceSubentType;
			break;
        } else if (_tcscmp(opt, ACRX_T("Edge")) == 0) {
			subType = AcDb::kEdgeSubentType;
			break;
		}
    }

	return subType;
}
