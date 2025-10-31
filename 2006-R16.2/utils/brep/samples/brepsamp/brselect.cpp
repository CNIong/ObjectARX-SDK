// (C) Copyright 1997-1999 by Autodesk, Inc. 
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
// Source file for Autocad entity/subentity selection.

#include "brsample_pch.h"  //precompiled header

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
			acutPrintf("\n Error in selectEntity: %d", acadReturnValue);
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
			acutPrintf("\n selectEntityByType: unsupported subentity type: %d\n", subType);
			returnValue = (AcBr::ErrorStatus)Acad::eWrongSubentityType;
			return returnValue;
		}
		if (pEnt == NULL) {
			acutPrintf("\n selectEntityByType: unable to allocate memory\n");
			returnValue = (AcBr::ErrorStatus)Acad::eOutOfMemory;
			return returnValue;
		}

		returnValue = pEnt->set(subPath);
		if (returnValue != AcBr::eOk) {
    		acutPrintf("\n Error in AcBrEntity::set:");
    		errorReport(returnValue);
    		return returnValue;
		}
	} else {
		// Create the entity as a local object
		AcDbEntity* pEntity;
		acadReturnValue = createEntity(pEntity);
		if (acadReturnValue != Acad::eOk) {
			acutPrintf("\n Error in createEntity: %d", acadReturnValue);
			return (AcBr::ErrorStatus)acadReturnValue;
		}
		if (pEntity == NULL) {
			acutPrintf("\n selectEntityByType: unable to allocate memory\n");
			returnValue = (AcBr::ErrorStatus)Acad::eOutOfMemory;
			return returnValue;
		}

    	pEnt = new AcBrBrep();
		if (pEnt == NULL) {
			acutPrintf("\n selectEntityByType: unable to allocate memory\n");
			returnValue = (AcBr::ErrorStatus)Acad::eOutOfMemory;
			return returnValue;
		}

		returnValue = ((AcBrBrep*)pEnt)->set((const AcDbEntity&)*pEntity);
		if (returnValue != AcBr::eOk) {
    		acutPrintf("\n Error in AcBrEntity::set:");
    		errorReport(returnValue);
    		return returnValue;
		}
	}

	returnValue = pEnt->setValidationLevel(vlevel);
	if (returnValue != AcBr::eOk) {
    	acutPrintf("\n Error in AcBrEntity::setValidationLevel:");
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
    char opt[128];
   	while (Adesk::kTrue) {
		acutPrintf("\nSelect No Validation vs. Full Validation: ");
		acedInitGet(NULL, "None Full");
		if (acedGetKword("None/<Full>: ", opt) == RTCAN) break;
		if ((strcmp(opt, "Full") == 0) || (strcmp(opt, "") == 0)) {
            vlevel = AcBr::kFullValidation;
            break;
        } else if ((strcmp(opt, "None") == 0)) {
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
    char opt[128];
   	while (Adesk::kTrue) {
		acutPrintf("\nSelect Local Entity vs. Database Entity: ");
		acedInitGet(NULL, "Local Database");
		if (acedGetKword("Local/<Database>: ", opt) == RTCAN) break;
		if ((strcmp(opt, "Database") == 0) || (strcmp(opt, "") == 0)) {
            context = Adesk::kFalse;
            break;
        } else if ((strcmp(opt, "Local") == 0)) {
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
    char opt[128];
   	while (Adesk::kTrue) {
		acutPrintf("\nEnter Subent Type: ");
		acedInitGet(NULL, "Edge Face Brep");
		if (acedGetKword("Edge/Face/<Brep>: ", opt) == RTCAN) {
			subType = AcDb::kNullSubentType;
			break;
		}

        // Map the user input to a valid subentity type
		if ((strcmp(opt, "Brep") == 0) || (strcmp(opt, "") == 0)) {
			subType = AcDb::kNullSubentType;
			break;
        } else if (strcmp(opt, "Face") == 0) {
			subType = AcDb::kFaceSubentType;
			break;
        } else if (strcmp(opt, "Edge") == 0) {
			subType = AcDb::kEdgeSubentType;
			break;
		}
    }

	return subType;
}