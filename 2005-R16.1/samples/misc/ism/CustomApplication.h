// (C) Copyright 1996 by Autodesk, Inc. 
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
//	file name:		CustomApplication.h
//
//  Created:		October, 1996	
//
//	top class:		CustomApplication
//	problems:		.




// ### CustomApplication definition-headers ########################################################
// The needed modules and their definitions:

#ifndef _CustomApplication_H
#define _CustomApplication_H 1

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#include <afxwin.h>         // MFC core and standard components

// ism
#include "imgdef.h"		// AcDbRasterImageDef and reactors, 	
#include "imgent.h"		// AcDbRasterImage
#include "imgvars.h"	// AcDbRasterVariables

// arx
#include "dbmain.h"		// Adesk, Acad
#include "dbdict.h"		// AcDbDictionary
#include "dbsymtb.h"	// AcDbBlockTable, AcDbBlockTableRecord

// ### end header
  



// ... prototypes .....................................................................
// This prototypes of classes and functions that are needed in that module.

// ... otherHaeder ....................................................................
class AcDbRasterImage;
class AcDbRasterImageDef;
class AcDbRasterImageDefReactor;

// ... intern .........................................................................
class CustomApplication;

// ... end prototypes ...




// *** CustomApplication ***********************************************************************
// duties:		Example class of using the Image Support Module (ISM).
//				It can attach an image by creating an entity, defintion and reactor.
//				Also it can add the object to the model or paper space.
//
// problems:	The image path has to be updated in the newImageAttach method.
//
class CustomApplication 
{
	public:
	// Methods

		// Attaches an new Image
			virtual Acad::ErrorStatus	newImageAttach					(AcDbObjectId & parEntityId);
		// Manipulate Image
			virtual Acad::ErrorStatus	manipulate						(AcDbObjectId   parEntityId);


		// Create Objects
			virtual Acad::ErrorStatus	createAcDbRasterImage			(AcDbObjectId & parEntityId, AcDbObjectId parObjectId);
			// creates the entity
			virtual Acad::ErrorStatus	createAcDbRasterImageDef		(AcDbObjectId &	parObjectId, CString parImageName, CString parImagePath);
			// creates the definition
			virtual Acad::ErrorStatus	createAcDbRasterImageDefReactor	(AcDbObjectId & parReactorId, AcDbObjectId parObjectId, AcDbObjectId parEntityId);
			// creates the reactor


		// Utilities Method
			virtual	Acad::ErrorStatus	appendToPaperOrModelSpace		(AcDbEntity* parEntity, Adesk::Boolean parbToPaperSpace);
};
// *** end CustomApplication




#endif // _CustomApplication_H




// ____________________________________________________________________________________
// END OF FILE
