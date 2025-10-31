//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
//
#include <stdio.h>
#include <string.h>

//-----------------------------------------------------------------------------
#include "acestext.h"
#include "acgi.h"

#include "dbdict.h"
#include "dbelipse.h"
#include "dbmain.h"
#include "dbapserv.h"
#include "dbproxy.h"
#include "dbsymtb.h"
#include "dbxrecrd.h"
#include "geassign.h"
#include "rxboiler.h"

#include "Lab9Employee.h"
#include "../Lab9Utils.h"

//-----------------------------------------------------------------------------
#pragma warning (disable : 4101)

//-----------------------------------------------------------------------------
unsigned long OarxEmployee::mVersion =0 ; //---- That is our first version
ACRX_DXF_DEFINE_MEMBERS (
    OarxEmployee, AcDbEllipse, 
    AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
    AcDbProxyEntity::kAllAllowedBits, OARX_EMPLOYEE, OarxLab9
)

//-----------------------------------------------------------------------------
//----- This is the Custom Entity Implementation
OarxEmployee::OarxEmployee () : AcDbEllipse (AcGePoint3d (), AcGeVector3d (0, 0, 1), AcGeVector3d (1, 0, 0), 1) {
	mID =-1 ;
	mCubeNumber =-1 ;
	mFirstName =NULL ;
	mLastName =NULL ;
}

OarxEmployee::~OarxEmployee () {
	CleanUp () ;
}

void OarxEmployee::CleanUp () {
	//----- Clean up
	mID =-1 ;
	mCubeNumber =-1 ;
	if ( mFirstName != NULL )
		acdbFree (mFirstName) ;
	mFirstName =NULL ;
	if ( mLastName != NULL )
		acdbFree ( mLastName) ;
	mLastName =NULL ;
}

//----- DXF protocol
Acad::ErrorStatus OarxEmployee::dxfOutFields (AcDbDxfFiler *pFiler) const {
	//----- Make sure the object is open is read mode
	assertReadEnabled () ;
	//----- Call parent class implementation for header
	AcDbEllipse::dxfOutFields (pFiler) ;
	//----- 100 SubClass
	pFiler->writeItem (AcDb::kDxfSubclass, "OarxEmployee") ;
	//----- Write class version
	pFiler->writeItem (AcDb::kDxfInt32, mVersion) ;
	//----- Write Employee Data
	pFiler->writeItem (AcDb::kDxfInt32, mID) ; //----- 90
	pFiler->writeItem (AcDb::kDxfInt32 + 1, mCubeNumber) ; //----- 91
	pFiler->writeItem (AcDb::kDxfXTextString, mFirstName) ; //----- 300
	pFiler->writeItem (AcDb::kDxfXTextString + 1, mLastName) ; //----- 301

	return (pFiler->filerStatus ()) ;
}

//----- DxfIn implemented to support non order dependant DXF code
Acad::ErrorStatus OarxEmployee::dxfInFields (AcDbDxfFiler *pFiler) {
	//----- Make sure the object is open is write mode
	//----- And enable UNDO resolution
	assertWriteEnabled () ;
	//----- Call parent class implementation for header
	AcDbEllipse::dxfInFields (pFiler) ;
	//----- Move to our class pointer in the DXF file (Dxf code: 100)
	Adesk::Boolean bResult ;
	if ( (bResult =pFiler->atSubclassData ("OarxEmployee")) != Adesk::kTrue )
		return (Acad::eMissingDxfField) ;
	//----- Read the version number
	Acad::ErrorStatus es ;
	struct resbuf rb ;
	if ( (es =pFiler->readResBuf (&rb)) != Acad::eOk )
		return (es) ;
	if ( rb.restype != AcDb::kDxfInt32 || (unsigned long)rb.resval.rlong != mVersion )
		return (Acad::eMakeMeProxy) ;
	//----- Read datas in a non dependant order
	while ( pFiler->readResBuf (&rb) == Acad::eOk ) {
		if ( (es =pFiler->readItem (&rb)) != Acad::eOk )
			return (es) ;
		switch ( rb.restype ) {
			case AcDb::kDxfInt32:
				mID =rb.resval.rlong ;
				break ;
			case AcDb::kDxfInt32 + 1:
				mCubeNumber =rb.resval.rlong ;
				break ;
			case AcDb::kDxfXTextString:
				setFirstName (rb.resval.rstring) ;
				acdbFree (rb.resval.rstring) ;
				rb.resval.rstring =NULL ;
				break ;
			case AcDb::kDxfXTextString + 1:
				setLastName (rb.resval.rstring) ;
				acdbFree (rb.resval.rstring) ;
				rb.resval.rstring =NULL ;
				break ;
			default:
				pFiler->pushBackItem () ;
				break ;
		}
	}
	if ( mID == -1 || mCubeNumber == -1 || mLastName == NULL || mFirstName == NULL )
		return (Acad::eMissingDxfField) ;
	return (pFiler->filerStatus ()) ;
}

//----- DWG protocol
Acad::ErrorStatus OarxEmployee::dwgOutFields (AcDbDwgFiler *pFiler) const {
	//----- Make sure the object is open is read mode
	assertReadEnabled () ;
	//----- Call parent class implementation for header
	AcDbEllipse::dwgOutFields (pFiler) ;
	//----- Write class version
	pFiler->writeUInt32 (mVersion) ;
	//----- Write Employee Datas
	pFiler->writeInt32 (mID) ;
	pFiler->writeInt32 (mCubeNumber) ;
	pFiler->writeString (mFirstName) ;
	pFiler->writeString (mLastName) ;

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus OarxEmployee::dwgInFields (AcDbDwgFiler *pFiler) {
	//----- Make sure the object is open is write mode
	assertWriteEnabled () ;
	//----- Call parent class implementation for header
	AcDbEllipse::dwgInFields (pFiler) ;
	//----- Read class version
	unsigned long version =0 ;
	pFiler->readUInt32 (&version) ;
	if ( version != mVersion ) {
		//----- Be carefull the version number does not match the current class
		//----- definitionversion. We normally need to process the information
		//----- differently. Or we return Acad::eMakeMeProxy
		return (Acad::eMakeMeProxy) ;
	}
	//-----  Deallocate an previous strings
	CleanUp () ;
	//----- Read Employee Datas
	pFiler->readInt32 (&mID) ;
	pFiler->readInt32 (&mCubeNumber) ;
	pFiler->readString (&mFirstName) ;
	pFiler->readString (&mLastName) ;

	return (pFiler->filerStatus ()) ;
}

//----- worldDraw
Adesk::Boolean OarxEmployee::worldDraw (AcGiWorldDraw *mode) {
	//----- Make sure the object is open is read mode
	assertReadEnabled () ;
	//----- Draw the entity
	AcDbEllipse::worldDraw (mode) ;
	//----- Write the Employee ID and Name
	char buffer [255] ;
	sprintf (buffer, "%d", mID) ;
	mode->geometry ().text (center (), normal (), majorAxis (), minorAxis ().length () / 2, 1.0, 0.0, buffer) ;
	sprintf (buffer, "%s %s", mFirstName, mLastName) ;
	mode->geometry ().text (center () - minorAxis () / 2, normal (), majorAxis (), minorAxis ().length () / 2, 1.0, 0.0, buffer) ;
	//----- Returns Adesk::kTrue to not call viewportDraw()
	return (Adesk::kTrue) ;
}

//----- subErase
Acad::ErrorStatus OarxEmployee::subErase (Adesk::Boolean erasing) {
	AcDbDictionary *pAppDict =NULL ;
	AcDbXrecord *pRec =NULL ;

	try {
		//----- Get Dictionary
		AcDbObjectId idDict =EmployeeService->getAppDictionary () ;
		if ( idDict == AcDbObjectId::kNull )
			throw Acad::eNullObjectId ;
		ARXOK ( acdbOpenAcDbObject ((AcDbObject *&)pAppDict, idDict, AcDb::kForRead) ) ;

		char buffer [33] ;
		sprintf (buffer, "%d", mID) ;

		AcDbObjectId id0 ;
		if ( erasing == Adesk::kTrue && EmployeeService->isEmployeeExist (mID) == Adesk::kTrue ) {
			pAppDict->getAt (buffer, id0) ;
			ARXOK ( acdbOpenAcDbObject ((AcDbObject *&)pRec, id0, AcDb::kForWrite) ) ;
			ARXOK ( pRec->erase (Adesk::kTrue) ) ;
		} else if ( erasing == Adesk::kFalse && EmployeeService->isEmployeeExist (mID) == Adesk::kFalse ) {
			pRec =new AcDbXrecord ;
			if ( pRec == NULL )
				throw Acad::eOutOfMemory ;

			struct resbuf rb ;
			rb.restype =330 ; //----- SoftPointerId to the OarxEmployee entity
			rb.rbnext =NULL ;
			ARXOK ( acdbGetAdsName (rb.resval.rlname, objectId ()) ) ;

			ARXOK ( pRec->setFromRbChain (rb) ) ;
			pRec->setXlateReferences (Adesk::kTrue) ;

			ARXOK ( pAppDict->upgradeOpen () ) ;

			ARXOK ( pAppDict->setAt (buffer, pRec, id0) ) ;
		}

		//----- Call parents
		Acad::ErrorStatus es ;
		ARXOK ( es =AcDbEllipse::subErase (erasing) ) ;

		pAppDict->close () ;
		pRec->close () ;

		return (es) ;

	} catch (const Acad::ErrorStatus es) {
		if ( pAppDict != NULL )
			pAppDict->cancel () ;
		if ( pRec != NULL && pRec->objectId () == AcDbObjectId::kNull )
			delete pRec ;
		else if ( pRec != NULL )
			pRec->cancel () ;

		return (es) ;
	}
}

//-----------------------------------------------------------------------------
//----- OarxEmployee protocol
long OarxEmployee::ID () const {
	assertReadEnabled () ;
	return (mID) ;
}

Acad::ErrorStatus OarxEmployee::setID (const long ID) {
	assertWriteEnabled () ;
	mID =ID ;
	return (Acad::eOk) ;
}

long OarxEmployee::cubeNumber () const {
	assertReadEnabled () ;
	return (mCubeNumber) ;
}

Acad::ErrorStatus OarxEmployee::setCubeNumber (const long cubeNumber) {
	assertWriteEnabled () ;
	mCubeNumber =cubeNumber ;
	return (Acad::eOk) ;
}

const char *OarxEmployee::firstName () const {
	assertReadEnabled () ;
	return (mFirstName) ;
}

Acad::ErrorStatus OarxEmployee::setFirstName (const char *strFirstName) {
	assertWriteEnabled () ;
	//----- Checking new value
	if ( strFirstName == NULL )
		return (Acad::eInvalidInput) ;
	//----- Allocate memory
	size_t length =strlen (strFirstName) ;
	if ( length == 0 )
		return (Acad::eInvalidInput) ;
	char *temp =(char *)acdbAlloc (length+1) ;
	if ( temp == NULL )
		return (Acad::eOutOfMemory) ;
	//----- Deallocate any previous piece
	if ( mFirstName != NULL )
		acdbFree (mFirstName) ;
	//----- Assigning
	mFirstName =temp ;
	strcpy (mFirstName, strFirstName) ;
	return (Acad::eOk) ;
}

const char *OarxEmployee::lastName () const {
	assertReadEnabled () ;
	return (mLastName) ;
}

Acad::ErrorStatus OarxEmployee::setLastName (const char *strLastName) {
	assertWriteEnabled () ;
	//----- Checking new value
	if ( strLastName == NULL )
		return (Acad::eInvalidInput) ;
	//----- Allocate memory
	size_t length =strlen (strLastName) ;
	if ( length == 0 )
		return (Acad::eInvalidInput) ;
	char *temp =(char *)acdbAlloc (length+1) ;
	if ( temp == NULL )
	return (Acad::eOutOfMemory) ;
	//----- Deallocate any previous piece
	if ( mLastName != NULL )
		acdbFree (mLastName) ;
	//----- Assigning
	mLastName =temp ;
	strcpy (mLastName,strLastName) ;
	return (Acad::eOk) ;
}

//-----------------------------------------------------------------------------
//----- This is the AcRxService class Implementation
Adesk::Boolean OarxEmployeeService::isEmployeeExist (int id) {
	AcDbDictionary *pNOD =NULL ;
	AcDbDictionary *pFirmDict =NULL ;
	AcDbDictionary *pAppDict =NULL ;

	try {
		//----- Get hold of the NOD
		ARXOK ( getNOD (pNOD, AcDb::kForRead) ) ;
		//----- Get our Firm Dictionary
		AcDbObjectId id0 ;
		ARXOK ( pNOD->getAt (OARX_FIRM_DICT, id0) ) ;
		ARXOK ( acdbOpenAcDbObject ((AcDbObject *&)pFirmDict, id0, AcDb::kForRead) ) ;
		//----- Get our App Dictionary
		ARXOK ( pFirmDict->getAt (OARX_APP_DICT, id0) ) ;
		ARXOK ( acdbOpenAcDbObject ((AcDbObject *&)pAppDict, id0, AcDb::kForRead) ) ;
		//----- Check if that entry already exist
		char buffer [33] ;
		sprintf (buffer, "%d", id) ;
		Adesk::Boolean bRet =pAppDict->has (buffer) ;
		//----- Normally we should have open the associated XRecord, and check the validity of
		//----- the SoftPointerId which is supposed to point to an OarxEmployee entity... But
		//----- to simplify the sample we stop checking here!

		pNOD->close () ;
		pFirmDict->close () ;
		pAppDict->close () ;

		return (bRet) ;

	} catch (const Acad::ErrorStatus es) {
		if ( pNOD != NULL )
			pNOD->cancel () ;
		if ( pFirmDict != NULL )
			pFirmDict->cancel () ;
		if ( pAppDict != NULL )
			pAppDict->cancel () ;

		return (Adesk::kFalse) ;
	}
}

AcDbObjectId OarxEmployeeService::getAppDictionary () {
	AcDbDictionary *pNOD =NULL ;
	AcDbDictionary *pFirmDict =NULL ;
	AcDbDictionary *pAppDict =NULL ;

	try {
		//----- Get hold of the NOD
		ARXOK ( getNOD (pNOD, AcDb::kForRead) ) ;
		//----- Get our Firm Dictionary
		AcDbObjectId id0 ;
		if ( pNOD->getAt (OARX_FIRM_DICT, id0) == Acad::eKeyNotFound ) {
			//----- Then create it
			pFirmDict =new AcDbDictionary ;
			if ( pFirmDict == NULL )
				throw Acad::eOutOfMemory ;
			ARXOK ( pNOD->upgradeOpen () ) ;
			ARXOK ( pNOD->setAt (OARX_FIRM_DICT, pFirmDict, id0) ) ;
		} else {
			//----- Open the dictionary
			ARXOK ( acdbOpenAcDbObject ((AcDbObject *&)pFirmDict, id0, AcDb::kForRead) ) ;
		}
		//----- Get our App Dictionary
		if ( pFirmDict->getAt (OARX_APP_DICT, id0) == Acad::eKeyNotFound ) {
			//----- Then create it
			pAppDict =new AcDbDictionary ;
			if ( pAppDict == NULL )
				throw Acad::eOutOfMemory ;
            if ( pFirmDict->isWriteEnabled () == false )
			    ARXOK ( pFirmDict->upgradeOpen () ) ;
			ARXOK ( pFirmDict->setAt (OARX_APP_DICT, pAppDict, id0) ) ;
			id0 =pAppDict->objectId () ;
		}

		pNOD->close () ;
		pFirmDict->close () ;
		pAppDict->close () ;

		return (id0) ;

	} catch (const Acad::ErrorStatus es) {
		if ( pNOD != NULL )
			pNOD->cancel () ;

		if ( pFirmDict != NULL && pFirmDict->objectId () == AcDbObjectId::kNull )
			delete pFirmDict ;
		else if ( pFirmDict != NULL )
			pFirmDict->cancel () ;

		if ( pAppDict != NULL && pAppDict->objectId () == AcDbObjectId::kNull )
			delete pAppDict ;
		else
			pAppDict->cancel () ;

		return (AcDbObjectId::kNull) ;
	}
}

OarxEmployee *OarxEmployeeService::createEmployee (int id, AcGePoint3d location, int cubeNumber, char *strFirstName, char *strLastName) {
	OarxEmployee *p =NULL ;
	AcDbXrecord *pRec =NULL ;
	AcDbDictionary *pAppDict =NULL ;

	try {
		//----- Create the object
		p =new OarxEmployee ;
		if ( p == NULL )
			throw Acad::eOutOfMemory ;

		ARXOK ( p->setID (id) ) ;
		ARXOK ( p->setCubeNumber (cubeNumber) ) ;
		ARXOK ( p->setFirstName (strFirstName) ) ;
		ARXOK ( p->setLastName (strLastName) ) ;
		ARXOK ( p->setCenter (location) ) ;

		AcDbObjectId id0 ;
		ARXOK ( postToDatabase (p, id0) ) ;

		pRec =new AcDbXrecord ;
		if ( pRec == NULL )
			throw Acad::eOutOfMemory ;

		struct resbuf rb ;
		rb.restype =330 ; //----- SoftPointerId to the OarxEmployee entity
		rb.rbnext =NULL ;
		ARXOK ( acdbGetAdsName (rb.resval.rlname, id0) ) ;

		ARXOK ( pRec->setFromRbChain (rb) ) ;
		pRec->setXlateReferences (Adesk::kTrue) ;

		AcDbObjectId idDict =getAppDictionary () ;
		if ( idDict == AcDbObjectId::kNull )
			throw Acad::eNullObjectId ;
		ARXOK ( acdbOpenAcDbObject ((AcDbObject *&)pAppDict, idDict, AcDb::kForWrite) ) ;

		char buffer [33] ;
		sprintf (buffer, "%d", id) ;
		ARXOK ( pAppDict->setAt (buffer, pRec, id0) ) ;

		pRec->close () ;
		pAppDict->close () ;

		return (p) ;

	} catch (const Acad::ErrorStatus es) {
		if ( p != NULL && p->objectId () == AcDbObjectId::kNull )
			delete p ;
		else
			p->cancel () ;

		if ( pRec != NULL && pRec->objectId () == AcDbObjectId::kNull )
			delete pRec ;
		else
			pRec->cancel () ;

		if ( pAppDict != NULL )
			pAppDict->cancel () ;

		return (NULL) ;
	}
}
