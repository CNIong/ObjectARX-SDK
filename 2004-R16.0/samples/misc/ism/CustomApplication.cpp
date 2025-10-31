// (C) Copyright 1996,1998 by Autodesk, Inc. 
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
//	project name:	Chameleon	
//
//	file name:		CustomApplication.cpp
//
//  Created:		October, 1996	
//	problems:		.
//						   




// ### CustomApplication definition-headers ####################################################
// The header file of this module:

// CustomApplication.h
#include "dbapserv.h"
#include "CustomApplication.h"	// all

// ### end header




// *** CustomApplication ***********************************************************************


// ___ newImageAttach ________________________________________________________________________
//	
//	description:	Create image definition object.
//					Create image entity.
//					Create image reactor.
//
//	parameter:		parEntityId		Returns the object Id of the RasterImage.
//
//	return value:	ErrorStatus
//					Returns Acad::eOk if successfull.
//
//	problems:		The image path has to be updated in the newImageAttach method.
//					Or the image path has to be set in the preference project directory
//					of Acad and set it to the current project.
//
Acad::ErrorStatus	CustomApplication::newImageAttach (AcDbObjectId &  parEntityId)
{

	// declaration
	Acad::ErrorStatus	ErrorStatus;
	
	AcDbObjectId 		ObjectId,			// AcDbRasterImageDef Id
						ReactorId;			// AcDbRasterImageDefReactor Id

	CString				ImageName,			// Name of the image.
						ImagePath;			// Path of the image.

	int					NumberOfEntities,	// Number of Entities that will be created.
						CreatedEntities;	// Number of Entities that are currently created.

	// definition
	ImageName = "atoll";
	ImagePath = "atoll.jpg";
	NumberOfEntities = 2;
	

	// Create image definition object.
	ErrorStatus = createAcDbRasterImageDef(ObjectId, ImageName, ImagePath);
		// check
		if (ErrorStatus != Acad::eOk)
		// Failed to create Definition.
			return ErrorStatus;
	
	for (CreatedEntities = 0; CreatedEntities < NumberOfEntities; CreatedEntities++)
	// Until NumberOfEntities are created.
	{
		// Create image entity.
		ErrorStatus = createAcDbRasterImage	(parEntityId, ObjectId);
			// check
			if (ErrorStatus != Acad::eOk)
			// Failed to create Entity.
				return ErrorStatus;

		// Create image reactor.
		ErrorStatus = createAcDbRasterImageDefReactor (ReactorId, ObjectId, parEntityId);
			// check
			if (ErrorStatus != Acad::eOk)
			// Failed to create Entity.
				return ErrorStatus;
	}

	
	return ErrorStatus;
}
// ___ end newImageAttach




// ___ createRasterImage ______________________________________________________________________
//	
//	description:	Create a new image entity.
//					Set Defintion id in Entity. ( link it to the specified image definition object)
//					Appends the entity to model space.
//					Set Entity ID to Attribute.
//
//	parameter:		parEntityId		Returns object Id of the created RasterImage.
//					parObjectId		Object Id of the RasterImageDef.
//
//	return value:	ErrorStatus
//					Returns Acad::eOk if successfull.
//					Acad::eNullEntityPointer	failed to initialize entity.
//
//	problems:		Could create memory leaks, when one check failes and instance is already created.
//					Check also other methods.
//
Acad::ErrorStatus CustomApplication::createAcDbRasterImage (AcDbObjectId & parEntityId, 
															AcDbObjectId   parObjectId)
{
	// declaration
	Acad::ErrorStatus	ErrorStatus;
	AcDbRasterImage*	pAcDbRasterImage;	// Entity
		
	// Create a new image entity.
	pAcDbRasterImage = new AcDbRasterImage;
		// check
		if ( pAcDbRasterImage == NULL)
		// Failed to initialize entity.
			return Acad::eNullEntityPointer;

	// Set Defintion id in Entity. ( link it to the specified image definition object)
	ErrorStatus = pAcDbRasterImage->setImageDefId(parObjectId);
		// check
		if (ErrorStatus != Acad::eOk) 
		// Failed to set image def id.
		{
			delete pAcDbRasterImage;
			return ErrorStatus;
		}
	
	// Appends the entity to model space.
	ErrorStatus = appendToPaperOrModelSpace ((AcDbEntity*) pAcDbRasterImage, Adesk::kFalse);
		// check
		if (ErrorStatus != Acad::eOk) 
		// Failed to append entity to the paper or model space.
		{
			delete pAcDbRasterImage;
			return ErrorStatus;
		}
	
	// Set Entity ID to Attribute.
	parEntityId = pAcDbRasterImage->objectId();

	// close entity.
	pAcDbRasterImage->close();

	
	return ErrorStatus;
}
// ___ end createAcDbRasterImage




// ___ createAcDbRasterImageDef ________________________________________________________________________
//	
//	description:	Create new image def object
//					set source file name
//					load image
//					Get Dictionary Id.
//					Check if image name already in use.
//
//	parameter:		parObjectId		Returns object Id of the created RasterImageDef.
//					parImageName	Name of the image.
//					parImagePath	Path of the image.
//
//	return value:	ErrorStatus
//					Returns Acad::eOk if successfull.
//					Acad::eNullObjectPointer	failed to initialize entity.
//					Acad::eHandleInUse	image name in use.
//					And error states of this classes: AcDbDictionary, AcDbRasterImageDef, 
//					and the function acdbOpenObject.
//
//	problems:		.
Acad::ErrorStatus	CustomApplication::createAcDbRasterImageDef (AcDbObjectId &	parObjectId, 
																 CString		parImageName, 
																 CString		parImagePath)
{
	// declaration
	Acad::ErrorStatus	ErrorStatus;
	
//	AcDbRasterImageDef*	pAcDbRasterImageDef = NULL;	// Definition
	
	AcDbObjectId		DictionaryId;
    AcDbDictionary*     pDictionary;
	Adesk::Boolean		bNameInUse;
	

	// Create new image def object
	AcDbRasterImageDef* pAcDbRasterImageDef = new AcDbRasterImageDef;			
		// check 
		if (pAcDbRasterImageDef == NULL)
		// Failed to create Definition.
			return Acad::eNullObjectPointer;

	// set source file name
	ErrorStatus = pAcDbRasterImageDef->setSourceFileName(parImagePath);
		// check
		if (ErrorStatus != Acad::eOk) 
		// Failed to set source file name.
		{
			ads_printf("Error: Could not find the image file.\n"); 
			delete pAcDbRasterImageDef;
			return ErrorStatus;
		}

	// load image
	ErrorStatus = pAcDbRasterImageDef->load(); 
		// check
		if (ErrorStatus != Acad::eOk) 
		// Unable to load image.
		{
			ads_printf("Error: Could not open the image file.\n"); 
			delete pAcDbRasterImageDef;
			return ErrorStatus;
		}

	// Get Dictionary Id.
    DictionaryId = AcDbRasterImageDef::imageDictionary(acdbHostApplicationServices()->workingDatabase());
		// check
	    if (DictionaryId.asOldId() == 0) 
		// No Dictionary open.
		{
			// Create dictionary
			ErrorStatus = AcDbRasterImageDef::createImageDictionary(acdbHostApplicationServices()->workingDatabase(), DictionaryId);
				// check 
				if (ErrorStatus!= Acad::eOk)
				// Failed to create Dictionary.
				{
					delete pAcDbRasterImageDef;
					return ErrorStatus;
				}
		}

    // Open AcDbDictionary.
	ErrorStatus = acdbOpenObject((AcDbObject*&)pDictionary, DictionaryId, AcDb::kForWrite);
		// check
		if (ErrorStatus != Acad::eOk)
		// Failed to open Dictioary.
		{
	        delete pAcDbRasterImageDef;
			return ErrorStatus;
	    }

		
	// Check if image name already in use.
	bNameInUse = pDictionary->has(parImageName);
	if (!bNameInUse) 
	// name not in use
		// adds a new entry specified by newValue into the dictionary and returns Object Id.
		ErrorStatus = pDictionary->setAt(parImageName, pAcDbRasterImageDef, parObjectId);
	else
	// name in use
	{
		pDictionary->close();
		delete pAcDbRasterImageDef;
		return Acad::eHandleInUse;
	}

	// close Dicionary and Definition.
	pDictionary->close();
	pAcDbRasterImageDef->close();


	return ErrorStatus;
}
// ___ end createAcDbRasterImageDef




// ___ createAcDbRasterImageDefReactor ______________________________________________________________________
//	
//	description:	Create reactor.
//					Set the entity to be its owner.
//					Link it to the definition object.
//					Set Reactor Id.
//					Adds the database resident object to the reactor list of the object.
//
//	parameter:		parReactorId	Returns object Id of the created RasterImageDefReactor. 
//					parObjectId		Object Id of the RasterImageDef.
//					parEntityId		Object Id of the RasterImage.
//
//	return value:	ErrorStatus
//					Returns Acad::eOk if successfull.
//					And error states of this classes: AcRxClass, AcDbObject, AcDbDatabase, AcDbRasterImage,
//					and the function acdbOpenObject.
//
//	problems:		Using AcDbRasterImageDefReactor insted of TESTAcDbRasterImageDefReactor.
//
Acad::ErrorStatus CustomApplication::createAcDbRasterImageDefReactor (AcDbObjectId & parReactorId, 
																	  AcDbObjectId   parObjectId, 
																	  AcDbObjectId   parEntityId)
{
	// declaration
	Acad::ErrorStatus	ErrorStatus;

	AcDbRasterImage*			pAcDbRasterImage;			// Entity
	AcDbRasterImageDef*			pAcDbRasterImageDef;		// Definition
	AcDbRasterImageDefReactor*	pAcDbRasterImageDefReactor;	// Reactor


	// Disable image definition notification while changing the defintion reactor list.
	AcDbRasterImageDefReactor::setEnable(Adesk::kFalse);

	// open Definition
	ErrorStatus = acdbOpenObject((AcDbObject*&) pAcDbRasterImageDef, parObjectId, AcDb::kForWrite);
		// check
		if (ErrorStatus != Acad::eOk) 
		// Failed to open.
		{
			pAcDbRasterImageDef->close();
			return ErrorStatus;
		}

	// open Entity
	ErrorStatus = acdbOpenObject((AcDbObject*&) pAcDbRasterImage, parEntityId, AcDb::kForWrite);
		// check
		if (ErrorStatus != Acad::eOk) 
		// Failed to open.
		{
			pAcDbRasterImage->close();
			pAcDbRasterImageDef->close();
			return ErrorStatus;
		}

	// Create reactor.
		pAcDbRasterImageDefReactor = new AcDbRasterImageDefReactor;			

		// check 
		if (pAcDbRasterImageDefReactor == NULL)
		// Failed to create Reactor.
			return Acad::eNullObjectPointer;

	// Set the entity to be its owner.
	ErrorStatus = pAcDbRasterImageDefReactor->setOwnerId( parEntityId);
		// check
		if (ErrorStatus != Acad::eOk) 
		// Failed to set owner id.
		{
			pAcDbRasterImage->close();
			pAcDbRasterImageDef->close();
			delete pAcDbRasterImageDefReactor;
			return ErrorStatus;
		}

	// Link it to the definition object.
	ErrorStatus = acdbHostApplicationServices()->workingDatabase()->addAcDbObject( parReactorId, pAcDbRasterImageDefReactor);
		// check
		if (ErrorStatus != Acad::eOk) 
		// Failed to set owner id.
		{
			pAcDbRasterImage->close();
			pAcDbRasterImageDef->close();
			delete pAcDbRasterImageDefReactor;
			return ErrorStatus;
		}

	// Set Reactor Id.
	pAcDbRasterImage->setReactorId( parReactorId);

	// Adds the database resident object to the reactor list of the object.
	pAcDbRasterImageDef->addPersistentReactor(parReactorId);


	//close Reactor, Image, Definition.
	pAcDbRasterImageDefReactor->close();
	pAcDbRasterImageDef->close();
	pAcDbRasterImage->close();

	// Re-enable image def notification.
	AcDbRasterImageDefReactor::setEnable(Adesk::kTrue);
		
	
	return ErrorStatus;
}
// ___ end createAcDbRasterImageDefReactor




// --- Manipulate Objects -------------------------------------------------------------
			
// ___ manipulate ______________________________________________________
//	
//	description:	Set orientation.
//					Set clip boundary to whole image.
//					Set polygonal clip boundary.
//
//	parameter:		parEntityId		Object Id of the RasterImage.
//
//	return value:	ErrorStatus
//					Returns Acad::eOk if successfull.
//	problems:		.
Acad::ErrorStatus CustomApplication::manipulate (AcDbObjectId   parEntityId)
{
	// declaration
	Acad::ErrorStatus		ErrorStatus;
	Adesk::Boolean			ReturnValue;

	AcDbRasterImage*	pAcDbRasterImage;		// Entity

	// definition
		// orientation
			AcGePoint3d		origin	(4, 3, 0);
			AcGeVector3d	u		(6, 0, 0),
							v		(0, 1, 0);

		// clipping
			AcDbRasterImage::ClipBoundaryType	ClipBoundaryType;	// polygonal clip boundary
			AcGePoint2dArray					ClipBoundary;		// clip boundary
			AcGePoint2d							ClipPoint;			// single clip point


	// Open object.
	ErrorStatus = acdbOpenObject((AcDbObject*&) pAcDbRasterImage, parEntityId, AcDb::kForWrite);

	if (ErrorStatus == Acad::eOk) 
	// correct open
	{

			// Get current clip boundary.
			ClipBoundary	 = pAcDbRasterImage->clipBoundary ();
			// type of clip boundary
			ClipBoundaryType = AcDbRasterImage::kPoly;	// polygonal clip boundary


			// Define single clip points to set and append it to the clip boundary.
			//	Be aware that the first and last clip point has to be the same 
			//	and that the clip points are pixel space.
			ClipPoint.set	(100, 100);
			ClipBoundary.setAt (0, ClipPoint);

			ClipPoint.set	(300, 0);
			ClipBoundary.setAt (1, ClipPoint);
			
			ClipPoint.set	(600, 200);
			ClipBoundary.setAt (2, ClipPoint);

			ClipPoint.set	(100, 400);
			ClipBoundary.setAt (3, ClipPoint);

			ClipPoint.set	(100, 100);
			ClipBoundary.setAt (4, ClipPoint);
			
			// Last point has to be same as first point.
			ClipPoint.set	(100, 100);
			ClipBoundary.append (ClipPoint);



		// Set orientation.
		ReturnValue = pAcDbRasterImage->setOrientation( origin, u, v );
			// check
		if (ReturnValue != Adesk::kTrue)
			// Failed to set orientation.
				ads_printf("Error: Set orientation failed.\n"); 
	
		// Set clip boundary.
		ErrorStatus = pAcDbRasterImage->setClipBoundary(ClipBoundaryType, ClipBoundary);
			// check
			if (ErrorStatus != Acad::eOk)
			// Failed to set clip boundary.
				ads_printf("Error: Set orientation failed.\n"); 

		// Close object.
		pAcDbRasterImage->close();
	}


	return ErrorStatus;
}
// ___ end manipulate



// --- Utilities Methods --------------------------------------------------------------

// ___ appendToPaperOrModelSpace ______________________________________________________
//	
//	description:	Appends the entity to paper or to model space.
//
//	parameter:		bToPaperSpace	If it is Adesk::kTrue, then entity gets added to paper space 
//									otherwise to model space.
//
//	return value:	ErrorStatus
//					Returns Acad::eOk if successfull.
//					Returns Adesk::eNoDatabase if there is no AcDbDatabase loaded.
//					And error states of this classes: AcDbDatabase, AcDbBlockTable, AcDbBlockTableRecord.
//	problems:		.
Acad::ErrorStatus CustomApplication::appendToPaperOrModelSpace (AcDbEntity* parEntity, Adesk::Boolean parbToPaperSpace)
{
	// declaration
	Acad::ErrorStatus	ErrorStatus;

	AcDbDatabase*			pDataBase;
	AcDbBlockTable*			pBlockTable; 
	AcDbBlockTableRecord*	pBlockTableRecord;


	// get database
    pDataBase	= acdbHostApplicationServices()->workingDatabase();
		// check
	    if (pDataBase == NULL) 
		// No database
			return Acad::eNoDatabase;


	// get block table
	ErrorStatus = pDataBase->getSymbolTable(pBlockTable, AcDb::kForRead);
		// check
		if (ErrorStatus != Acad::eOk) 
		// Failed to get block table
			return ErrorStatus;


	// appends to ...
	if (parbToPaperSpace)
	// ... paper space		
		ErrorStatus = pBlockTable->getAt(ACDB_PAPER_SPACE, pBlockTableRecord, AcDb::kForWrite);
	else
	// ... model space by default
		ErrorStatus = pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

		// check
	    if (ErrorStatus != Acad::eOk)
		// Failed to get block table record
	    {
			pBlockTable->close();
			return ErrorStatus;
	    }
	

	// append entity to block table record
	ErrorStatus = pBlockTableRecord->appendAcDbEntity (parEntity);

    pBlockTableRecord->close();
    pBlockTable->close();
 
	return ErrorStatus;
}
// ___ end appendToPaperOrModelSpace


// *** end CustomApplication




// ____________________________________________________________________________________
// END OF FILE


