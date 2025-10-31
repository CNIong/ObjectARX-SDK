//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Source file for Autocad database utilities.

#include "brsample_pch.h"  //precompiled header


// include here



// local function prototypes
static Acad::ErrorStatus extractSolidFromBlock(ads_name                ename,
											   const AcDb::SubentType& subType,
											   const short&            marker,
											   const AcGePoint3d&      pickpnt,                                           
					                           AcDbFullSubentPath&     subPath);

static Acad::ErrorStatus makeSubentPath(const AcDbObject*        pObj,
			                            const AcDbObjectIdArray& objIdList,
			                            const AcDb::SubentType&  subType,
			                            const short&             marker,
			                            const AcGePoint3d&       pickpnt,                                           
			                            AcDbFullSubentPath&      subPath);

static void objIds2SubPath(const AcDbObjectIdArray&  objIdList,
			               const AcDb::SubentType&   subType,
	                       const AcDbFullSubentPath* subentIds,
			               AcDbFullSubentPath&       subPath);

			   
Acad::ErrorStatus
createEntity(AcDbEntity*& pEntity)
{
	Acad::ErrorStatus acadReturnValue = Acad::eOk;

	// Make a blank solid
	pEntity = new AcDb3dSolid();
	if (pEntity == NULL) {
		acutPrintf(ACRX_T("\n createEntity: unable to allocate memory\n"));
		acadReturnValue = Acad::eOutOfMemory;
		return acadReturnValue;
	}

	// Query the solid primitive type
	int entType = 0;
    ACHAR opt[128];
   	while (Adesk::kTrue) {
		acutPrintf(ACRX_T("\nEnter Solid Primitive Type: "));
		acedInitGet(NULL, ACRX_T("Box Wedge Frustum Sphere Torus"));
		if (acedGetKword(ACRX_T("Box/Wedge/Frustum/Sphere/<Torus>: "), opt) == RTCAN) {
			entType = 0;
			break;
		}

        // Map the user input to a valid solid primitive type
		if ((_tcscmp(opt, ACRX_T("Torus")) == 0) || (_tcscmp(opt, ACRX_T("")) == 0)) {
			entType = 1;
			break;
        } else if (_tcscmp(opt, ACRX_T("Sphere")) == 0) {
			entType = 2;
			break;
        } else if (_tcscmp(opt, ACRX_T("Frustum")) == 0) {
			entType = 3;
			break;
        } else if (_tcscmp(opt, ACRX_T("Wedge")) == 0) {
			entType = 4;
			break;
        } else if (_tcscmp(opt, ACRX_T("Box")) == 0) {
			entType = 5;
			break;
		}
    }

	// Set the solid to the selected primitive type, created at the
	// origin using unit size.

	switch (entType) {
	case 0:
	case 1:
		((AcDb3dSolid*)pEntity)->createTorus(1.0, 0.1);
		break;
	case 2:
		((AcDb3dSolid*)pEntity)->createSphere(1.0);
		break;
	case 3:
		((AcDb3dSolid*)pEntity)->createFrustum(1.0, 0.3, 0.2, 0.1);
		break;
	case 4:
		((AcDb3dSolid*)pEntity)->createWedge(1.0, 0.9, 0.8);
		break;
	case 5:
		((AcDb3dSolid*)pEntity)->createBox(1.0, 0.9, 0.8);
		break;
	default:
		acutPrintf(ACRX_T("\n createEntity: unsupported solid primitive type: %d\n"), entType);
		acadReturnValue = Acad::eWrongObjectType;
		return acadReturnValue;
	}

	return acadReturnValue;
}


Acad::ErrorStatus
selectEntity(const AcDb::SubentType& subType,
			 AcDbFullSubentPath&     subPath)
{
	Acad::ErrorStatus acadReturnValue = Acad::eOk;

	int errStat = RTERROR;
	ads_name sset;
	AcGePoint3d pickPnt;

	struct resbuf org_osnap;
	acedGetVar(ACRX_T("OSMODE"), &org_osnap);
	struct resbuf new_osnap = org_osnap;
	new_osnap.resval.rint = 0;
	acedSetVar(ACRX_T("OSMODE"), &new_osnap);

    while ((errStat != RTNORM) && (errStat != RTCAN) && (errStat != RTREJ)
        && (errStat != RTNONE)) {
        ads_name ent_name;
        switch(subType) {
		case AcDb::kNullSubentType:
			errStat = acedEntSel(ACRX_T("\n Pick a solid\n"), ent_name, asDblArray(pickPnt));
			break;
		case AcDb::kFaceSubentType:
			errStat = acedEntSel(ACRX_T("\n Pick a face\n"), ent_name, asDblArray(pickPnt));
			break;
		case AcDb::kEdgeSubentType:
			errStat = acedEntSel(ACRX_T("\n Pick an edge\n"), ent_name, asDblArray(pickPnt));
			break;
		default:
			acutPrintf(ACRX_T("\n getPath: unsupported subentity type: %d\n"), subType);
			return Acad::eInvalidInput;
		}

        if (errStat == RTERROR) {
            struct resbuf buf_errno;
			acedGetVar(ACRX_T("ERRNO"), &buf_errno);
	        if (buf_errno.resval.rint == OL_ENTSELNULL) errStat = RTNONE;
        }
    }

	if (errStat == RTNORM) {
	    errStat = acedSSGet(NULL, asDblArray(pickPnt), NULL, NULL, sset);
	}
    acedSetVar(ACRX_T("OSMODE"), &org_osnap);

	if (errStat != RTNORM) return Acad::eAmbiguousInput;

	// Get the entity name
	struct resbuf* rb;
	errStat = acedSSNameX(&rb, sset, 0L);
    if (errStat != RTNORM) {
		acedSSFree(sset);
		return Acad::eAmbiguousInput;
    }  

	// Free the selection set
    acedSSFree(sset);

	// The selected entity is the final entry in the resbuf
	int i;
    struct resbuf* pTemp;
	for (i=1, pTemp=rb; i<3; i++, pTemp=pTemp->rbnext)
		;
	ads_name ename;
	ads_name_set(pTemp->resval.rlname, ename);

	// Get the GsMarker
	pTemp = pTemp->rbnext;
	short marker = pTemp->resval.rint;

	// Free the rb resbuf entity
	acutRelRb(rb);


	// Get the object ID of the selected entity
	AcDbObjectId objId;
	acadReturnValue = acdbGetObjectId(objId, ename);
    if (acadReturnValue != Acad::eOk) {
		acutPrintf(ACRX_T("\n acdbGetObjectId failed\n"));
		return acadReturnValue;
	}

    // Use an existing transaction if there is one;
	// else open a new one
	Adesk::Boolean ownTransaction = Adesk::kFalse;
	acadReturnValue = dbOpenTransaction(ownTransaction);
	if (acadReturnValue != Acad::eOk) {
		acutPrintf(ACRX_T("\n Error in dbOpenTransaction:"));
		errorReport((AcBr::ErrorStatus)acadReturnValue);
		return acadReturnValue;
	}
	
	// Open the object for read-only
	AcDbObject* pObj = NULL;
	acadReturnValue = actrTransactionManager->getObject(
		pObj, objId, AcDb::kForRead);
	if (acadReturnValue != Acad::eOk) {
		dbAbortTransaction(ownTransaction);
		acutPrintf(ACRX_T("\n Error in getPath:"));
		errorReport((AcBr::ErrorStatus)acadReturnValue);
		return acadReturnValue;
	}

	if (AcDbBlockReference::cast(pObj) != NULL) {
		acadReturnValue = extractSolidFromBlock(ename, subType, marker, pickPnt, subPath);
		if (acadReturnValue != Acad::eOk) {
			dbCloseTransaction(ownTransaction);
			acutPrintf(ACRX_T("\n extractSolidFromBlock failed\n"));
			return acadReturnValue;
		}
	} else {
		AcDbObjectIdArray objIdList;
		objIdList.append(objId);
		acadReturnValue = makeSubentPath(pObj, objIdList, subType, marker, pickPnt, subPath);
		if (acadReturnValue != Acad::eOk) {
			dbCloseTransaction(ownTransaction);
			acutPrintf(ACRX_T("\n makeSubentPath failed\n"));
			return acadReturnValue;
		}
	}

	// Close the transaction
	dbCloseTransaction(ownTransaction);
	
	return acadReturnValue;
}


static Acad::ErrorStatus
extractSolidFromBlock(ads_name                ename,
					  const AcDb::SubentType& subType,
					  const short&            marker,
					  const AcGePoint3d&      pickpnt,                                           
					  AcDbFullSubentPath&     subPath)
{
	Acad::ErrorStatus acadReturnValue = Acad::eOk;

	struct resbuf* insertStack;
	ads_matrix adsMatrix;

	int errStat = RTERROR;
	errStat = acedNEntSelP(NULL, ename, asDblArray(pickpnt), Adesk::kTrue, 
		adsMatrix, &insertStack);
	if (errStat != RTNORM) {
		acutPrintf(ACRX_T("\n %d nentselp failed\n"), errStat); 
		return acadReturnValue;
	} 
	
	// ename should be the solid
	AcDbObjectId objId;
	acadReturnValue = acdbGetObjectId(objId, ename);
	if (acadReturnValue != Acad::eOk) {
		acutPrintf(ACRX_T("\n acdbGetObjectId failed\n"));
		errorReport((AcBr::ErrorStatus)acadReturnValue);
		return acadReturnValue;
	}

	// Use an existing transaction if there is one;
	// else open a new one
	Adesk::Boolean ownTransaction = Adesk::kFalse;
	acadReturnValue = dbOpenTransaction(ownTransaction);
	if (acadReturnValue != Acad::eOk) {
		acutPrintf(ACRX_T("\n Error in dbOpenTransaction:"));
		errorReport((AcBr::ErrorStatus)acadReturnValue);
		return acadReturnValue;
	}
	
	// Open the object for read-only
	AcDbObject* pObj = NULL;
	acadReturnValue = actrTransactionManager->getObject(
		pObj, objId, AcDb::kForRead);
	if (acadReturnValue != Acad::eOk) {
		dbAbortTransaction(ownTransaction);
		acutPrintf(ACRX_T("\n Error in getPath:"));
		errorReport((AcBr::ErrorStatus)acadReturnValue);
		return acadReturnValue;
	}

	int count = 0;
	AcDbObjectId* idArray = new AcDbObjectId[100];
	idArray[count++] = objId;
	
	while (insertStack != NULL) {
        ename[0] = insertStack->resval.rlname[0];
       	ename[1] = insertStack->resval.rlname[1];

		acadReturnValue = acdbGetObjectId(objId, ename);
		if (acadReturnValue != Acad::eOk) {
			acutPrintf(ACRX_T("\n acdbGetObjectId failed\n"));
			errorReport((AcBr::ErrorStatus)acadReturnValue);
			dbCloseTransaction(ownTransaction);
			return acadReturnValue;
		}

		idArray[count++] = objId;
		insertStack = insertStack->rbnext;
	}

	// Invert the list
	AcDbObjectIdArray objIdList;
	for (int j=(count-1); j>=0; j--) objIdList.append(idArray[j]);

	acadReturnValue = makeSubentPath(pObj, objIdList, subType, marker, pickpnt, subPath);
	if (acadReturnValue != Acad::eOk) {
		acutPrintf(ACRX_T("\n makeSubentPath failed\n"));
		dbCloseTransaction(ownTransaction);
		return acadReturnValue;
	}

	// Close the transaction
	dbCloseTransaction(ownTransaction);

	return acadReturnValue;
}


static Acad::ErrorStatus
makeSubentPath(const AcDbObject*        pObj,
			   const AcDbObjectIdArray& objIdList,
			   const AcDb::SubentType&  subType,
			   const short&             marker,
			   const AcGePoint3d&       pickpnt,                                           
			   AcDbFullSubentPath&      subPath)
{
	Acad::ErrorStatus acadReturnValue = Acad::eOk;

	AcGeMatrix3d xform(AcGeMatrix3d::kIdentity);
	int numIds = 0L;
	AcDbFullSubentPath* subentIds = NULL;

	// Check to see if entity is a supported solid, surface, region or body
	AcDb3dSolid* pSolid = NULL;
    AcDbSurface* pSurface = NULL;
	AcDbRegion* pRegion = NULL;
	AcDbBody* pBody = NULL;
	if ((pSolid = AcDb3dSolid::cast(pObj)) != NULL) {
		if (subType != AcDb::kNullSubentType) {
			acadReturnValue = pSolid->getSubentPathsAtGsMarker(
    			subType, marker, pickpnt, xform, numIds, subentIds);
			if (subentIds == NULL) acadReturnValue = Acad::ePointNotOnEntity;
			if (acadReturnValue != Acad::eOk) {
				acutPrintf(ACRX_T("\n getSubentPathsAtGsMarker failed\n"));
				errorReport((AcBr::ErrorStatus)acadReturnValue);
				return acadReturnValue;
			}
		}
		objIds2SubPath(objIdList, subType, subentIds, subPath);
    } else if ((pSurface = AcDbSurface::cast(pObj)) != NULL) {
		if (subType != AcDb::kNullSubentType) {
			acadReturnValue = pSurface->getSubentPathsAtGsMarker(
    			subType, marker, pickpnt, xform, numIds, subentIds);
			if (subentIds == NULL) acadReturnValue = Acad::ePointNotOnEntity;
			if (acadReturnValue != Acad::eOk) {
				acutPrintf(ACRX_T("\n getSubentPathsAtGsMarker failed\n"));
				errorReport((AcBr::ErrorStatus)acadReturnValue);
				return acadReturnValue;
			}
		}
		objIds2SubPath(objIdList, subType, subentIds, subPath);
    } else if ((pRegion = AcDbRegion::cast(pObj)) != NULL) {
		if (subType != AcDb::kNullSubentType) {
			acadReturnValue = pRegion->getSubentPathsAtGsMarker(
    			subType, marker, pickpnt, xform, numIds, subentIds);
			if (subentIds == NULL) acadReturnValue = Acad::ePointNotOnEntity;
			if (acadReturnValue != Acad::eOk) {
				acutPrintf(ACRX_T("\n getSubentPathsAtGsMarker failed\n"));
				errorReport((AcBr::ErrorStatus)acadReturnValue);
				return acadReturnValue;
			}
		}
		objIds2SubPath(objIdList, subType, subentIds, subPath);
    } else if ((pBody = AcDbBody::cast(pObj)) != NULL) {
		if (subType != AcDb::kNullSubentType) {
			acadReturnValue = pBody->getSubentPathsAtGsMarker(
    			subType, marker, pickpnt, xform, numIds, subentIds);
			if (subentIds == NULL) acadReturnValue = Acad::ePointNotOnEntity;
			if (acadReturnValue != Acad::eOk) {
				acutPrintf(ACRX_T("\n getSubentPathsAtGsMarker failed\n"));
				errorReport((AcBr::ErrorStatus)acadReturnValue);
				return acadReturnValue;
			}
		}
		objIds2SubPath(objIdList, subType, subentIds, subPath);
	} else {
		acutPrintf(ACRX_T("\n Selected object not a brep object\n"));
		return Acad::eWrongObjectType;
	}

	return acadReturnValue;
}

	
static void
objIds2SubPath(const AcDbObjectIdArray&  objIdList,
			   const AcDb::SubentType&   subType,
	           const AcDbFullSubentPath* subentIds,
			   AcDbFullSubentPath&       subPath)
{
	if (subType != AcDb::kNullSubentType) {
		// Make a subent path for a face or an edge using the 
		// picked subentity (retrieved from the GS markers)
		subPath = subentIds[0];
		subPath.objectIds() = objIdList;
	} else {
		// Make a subent path for a brep object (object ID array
		// with null subentity ID)
		subPath = kNullSubent;
		subPath.objectIds() = objIdList;
	}

	return;
}


// Add the given entity to the current Database
Acad::ErrorStatus
addToDatabase(AcDbEntity* pEnt, AcDbObjectId& objId)
{
    Acad::ErrorStatus acadReturnValue = Acad::eOk;
    AcDbBlockTable* pBlockTable;
    AcDbBlockTableRecord* pSpaceRecord;

	AcDbDatabase *pCurDwg = acdbHostApplicationServices()->workingDatabase();
    if (pCurDwg==NULL)
        return Acad::eNoDatabase;

    if ((acadReturnValue = pCurDwg->getBlockTable(pBlockTable,
        AcDb::kForRead)) != Acad::eOk) {
        acutPrintf(ACRX_T("\n acdbCurDwg()->getBlockTable() failed"));
        return acadReturnValue;
    }

    if ((acadReturnValue = pBlockTable->getAt(ACDB_MODEL_SPACE, 
        pSpaceRecord, AcDb::kForWrite)) != Acad::eOk) {
        acutPrintf(ACRX_T("\n AcDbBlockTable::getAt() failed"));
        return acadReturnValue;
    }
 
    // close the block table object
    if ((acadReturnValue = pBlockTable->close()) != Acad::eOk) {
        acutPrintf(ACRX_T("\n AcDbBlockTable::close() failed"));
        return acadReturnValue;
    }

    // append the entity to the display list
    if ((acadReturnValue = pSpaceRecord->appendAcDbEntity(objId, pEnt))
        != Acad::eOk) {
        acutPrintf(ACRX_T("\n AcDbBlockTableRecord::appendAcDbEntity() failed"));
        return acadReturnValue;
    }

    // close the block table record object
    if ((acadReturnValue = pSpaceRecord->close()) != Acad::eOk) {
        acutPrintf(ACRX_T("\n AcDbBlockTableRecord::close() failed"));
        return acadReturnValue;
    }

    return acadReturnValue;
}


Acad::ErrorStatus
dbOpenTransaction(Adesk::Boolean& ownTransaction)
{
	Acad::ErrorStatus acadReturnValue = Acad::eOk;

    // Open a new transaction only when there is not an existing one.
	if (actrTransactionManager->numActiveTransactions() == 0) {
		if (actrTransactionManager->startTransaction() == NULL) {
			return Acad::eNoActiveTransactions;
		} else ownTransaction = kTrue;
	} else ownTransaction = kFalse;

	return acadReturnValue;
}


// Note: This function conditionally closes a transaction.
Acad::ErrorStatus
dbCloseTransaction(Adesk::Boolean& ownTransaction)
{
	Acad::ErrorStatus acadReturnValue = Acad::eOk;

    // Close only in the case where we own the transaction.
    if (ownTransaction)
		acadReturnValue = actrTransactionManager->endTransaction();

	return acadReturnValue;
}


// Note: This function conditionally aborts a transaction, which invokes UNDO.
Acad::ErrorStatus
dbAbortTransaction(Adesk::Boolean& ownTransaction)
{
	Acad::ErrorStatus acadReturnValue = Acad::eOk;

    // Abort only in the case where we own the transaction.
	if (ownTransaction)
		acadReturnValue = actrTransactionManager->abortTransaction();

	return acadReturnValue;
}
