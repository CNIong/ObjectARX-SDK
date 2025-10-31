// (C) Copyright 2002-2006 by Autodesk, Inc. 
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

#include "StdAfx.h"
#include "AsdkEntityRecreator.h"
#include "asdkstyle.h"

AsdkStyleRecreator::AsdkStyleRecreator(void)
{
}

AsdkStyleRecreator::~AsdkStyleRecreator(void)
{
    // Set mpCurDb to !NULL to guarantee resetForNewDb works.
    mpCurDb = ((AcDbDatabase*) !NULL);
    resetForNewDb(NULL);
}

bool AsdkStyleRecreator::replace(	AcDbObject*&	pNewObj,
						AcDbObjectId	originalObjId,
						AcRxClass*	pObjClass,
						AcDbDatabase*	pDb,
						AcDbAuditInfo*	pAuditInfo)
{
	// When replace is called from fetchObject(), the objectID is still valid, but the underlying
	// object itself is not.  We simply want to recreate the entity here and
	// set the pointer to the pNewObj parameter - it should be hooked up to 
	// originalObjId by the audit framework when we return true.
	try
	{
		if(findStyleInNOD()==AcDbObjectId::kNull)
		{
			//There is no correct style in the NOD - replace it here.
			AcDbObjectId id = AsdkStyle::AddToNOD(_T("Standard"));
			if(id.isNull())
				throw _T("Couldn't add a style");
			if(Acad::eOk!=acdbOpenObject(pNewObj,id,AcDb::kForRead))
				throw _T("Object Added to NOD is not valid");
			assert(Acad::eOk==pNewObj->close());//Sets the first argument ref parameter.
			return true;
		}
	}
	catch(ACHAR *pMessage)
	{
		acutPrintf(_T("\nError during RECOVER: %s\n"),pMessage);
	}
	return false;
}

bool AsdkStyleRecreator::redirect(	AcDbObjectId&	newObjId,
						AcDbObjectId	originalObjId,
						AcRxClass*		pObjClass,
						AcDbDatabase*	pDb,
						AcDbAuditInfo*	pAuditInfo)
{
	try
	{
		// If redirect is called, it is assumed that we simply need to 
		if(findStyleInNOD() != AcDbObjectId::kNull)
		{
			// we found the style...and the replace pass therefore checked its integrity
			newObjId = findStyleInNOD();
			return true;
		}
		else
		{
			newObjId = AsdkStyle::AddToNOD(_T("Standard"));//Equivalent to replace
			if(newObjId!=AcDbObjectId::kNull)
				return true;
		}
	}
	catch(ACHAR *pMessage)
	{
		acutPrintf(_T("\nError during RECOVER: %s\n"),pMessage);
	}
	return false;
}

void AsdkStyleRecreator::resetForNewDb(const AcDbDatabase* pDb)
{
    if (pDb == mpCurDb)
        return;
    mpCurDb = pDb;
    mNewObjCount = 0;
	mRedirectFromNull = AcDbObjectId::kNull;
}

Acad::ErrorStatus AsdkStyleRecreator::registerObject(AcDbHandle handle, bool objIsValid, AcRxClass* pObjClass)
{
	//registerObject is invoked from AcDb Recover and Audit internals, and can also be invoked from AcDbObject::audit(), dwgInFields() 
	//and any other override members invoked during a recover operation and
	//its subsequent audit.  It is the easy way to make entries for valid objects, compared to
	//AcDbAuditInfo::updateObject, which has a much more verbose parameter list.

	return Acad::eOk;
}


AcDbObjectId AsdkStyleRecreator::findStyleInNOD(void)
{
	// Tries to find the ASDK_STYLE_OBJECT within the predetermined NOD location, and return the ID.
	// If the method fails, a NULL ID is passed back indicating that the style was not found.  Exceptions
	// are not reported in this method.

	bool bReturn = false;

	AcDbObjectId newId = AcDbObjectId::kNull;
	AcDbDatabase *pDb=acdbHostApplicationServices()->workingDatabase();
	AcTransaction *pTrans=pDb->transactionManager()->startTransaction();
	try
	{
		AcDbDictionary *pNOD=NULL,*pStyleDict=NULL;
		if(Acad::eOk!=pTrans->getObject((AcDbObject*&)pNOD,pDb->namedObjectsDictionaryId(),AcDb::kForRead))
			throw _T("Couldn't get the NOD");

		AcDbObjectId dictId;
		if(Acad::eOk==pNOD->getAt(_T("ASDK_STYLE"),dictId))
			if(Acad::eOk==pTrans->getObject((AcDbObject*&)pStyleDict,dictId,AcDb::kForRead))
				if(Acad::eOk!=pStyleDict->getAt(_T("ASDK_STYLE_OBJECT"),newId))
					newId = AcDbObjectId::kNull;//probably redundant
		
		pDb->transactionManager()->endTransaction();
	}
	catch(ACHAR *pMessage)
	{	
		pDb->transactionManager()->abortTransaction();
		throw pMessage;
	}
	return newId;
}
