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

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.h
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"

#include "dbobjptr.h"
#include "asdkentity.h"

#include "asdkstyle.h"

#include "asdkentityrecreator.h"


//-----------------------------------------------------------------------------
#define szRDS _RXST("Asdk")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CAudit_RecoverApp : public AcRxArxApp {
	static AsdkStyleRecreator *pRecreator;
public:
	CAudit_RecoverApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		initAuditRecreate();

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		uninitAuditRecreate();

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}


	static void CAudit_RecoverApp::initAuditRecreate(void)
	{
		pRecreator = new AsdkStyleRecreator();
		AsdkStyle::desc()->addX(AcDbAuditRecreatePE::desc(), pRecreator);
	}

	static void CAudit_RecoverApp::uninitAuditRecreate(void)
	{
		if(pRecreator)
		{
			AsdkStyle::desc()->delX(AcDbAuditRecreatePE::desc());
			delete pRecreator;
			pRecreator = NULL;
		}
	}


	// - AsdkAuditRecover.CREATE command (do not rename)
	static void AsdkAuditRecoverCREATE(void)
	{
		AcDbDatabase *pDb=acdbHostApplicationServices()->workingDatabase();
		AcTransaction *pTrans=pDb->transactionManager()->startTransaction();
		AsdkEntity *pEntity = NULL;
		try
		{
			AcDbBlockTableRecordPointer pBTR(ACDB_MODEL_SPACE,acdbHostApplicationServices()->workingDatabase(),AcDb::kForWrite);
			if(Acad::eOk != pBTR.openStatus())
				throw _T("Can't get MODEL_SPACE");

			ads_point pt;
			if(RTNORM != acedGetPoint(NULL,_T("Select an Insertion Point:"), pt))
				throw _T("User Cancelled");

			pEntity = new AsdkEntity();
			pEntity->setDatabaseDefaults();

			if(Acad::eOk != pEntity->setCenter(asPnt3d(pt)))
				throw _T("Couldn't set Circle Center");

			if(Acad::eOk != pEntity->setRadius(2.0))
				throw _T("Couldn't set Circle Radius");

			AcDbObjectId styleId = AsdkStyle::AddToNOD(_T("Standard"));

			if(AcDbObjectId::kNull != styleId)
			{
				pEntity->setStyle(styleId);
				if(Acad::eOk!=pBTR->appendAcDbEntity(pEntity))
					throw _T("Couldn't append entity to Model Space");
				pDb->transactionManager()->addNewlyCreatedDBRObject(pEntity);
			}
			else
				throw _T("Could not create Style Object");
			
			pDb->transactionManager()->endTransaction();
		}
		catch (ACHAR *pMessage)
		{
			if(pEntity)
				delete pEntity;
			acutPrintf(_T("\nError: %s\n"),pMessage);
			pDb->transactionManager()->abortTransaction();
		}
	}

	// - AsdkAuditRecover.CORRUPT command (do not rename)
	// This will invalidate the radius, and reset the style so that it is incorrect.
	// It does not actually remove the style, only set the ID to point to something
	// it shouldn't (the Model Space BTR).
	static void AsdkAuditRecoverCORRUPT(void)
	{
		AcDbDatabase *pDb=acdbHostApplicationServices()->workingDatabase();
		
		AcDbBlockTableRecordPointer pBTR(ACDB_MODEL_SPACE,pDb,AcDb::kForWrite);
		AcDbBlockTableRecordIterator *pItr = NULL;
		pBTR->newIterator(pItr);
		assert(pBTR);
		
		AcTransaction *pTrans=pDb->transactionManager()->startTransaction();
		try
		{
			for(;!pItr->done();pItr->step())
			{
				AcDbObjectId entityId;
				pItr->getEntityId(entityId);
				
				AcDbEntity *pEnt = NULL;
				if(Acad::eOk==pTrans->getObject((AcDbObject*&)pEnt,entityId,AcDb::kForWrite))
				{
					if(AsdkEntity::desc()==pEnt->isA())
					{
						AsdkEntity *pCircle = AsdkEntity::cast(pEnt);
						assert(Acad::eOk==pCircle->setRadius(.001));

						// Corrupt the style by setting it to the MODEL_SPACE object id
						pCircle->setStyle(pBTR->objectId());
					}
				}
			}
			pDb->transactionManager()->endTransaction();
		}
		catch(ACHAR *pMessage)
		{
			acutPrintf(_T("\nError: %s\n"),pMessage);
			pDb->transactionManager()->abortTransaction();
		}
	}

	// - AsdkAuditRecover.CORRUPT command (do not rename)
	// This will invalidate the radius, and erase the style altogether.
	static void AsdkAuditRecoverCORRUPT2(void)
	{
		AcDbDatabase *pDb=acdbHostApplicationServices()->workingDatabase();
		
		AcDbBlockTableRecordPointer pBTR(ACDB_MODEL_SPACE,pDb,AcDb::kForWrite);
		AcDbBlockTableRecordIterator *pItr = NULL;
		pBTR->newIterator(pItr);
		assert(pBTR);

		AcTransaction *pTrans=pDb->transactionManager()->startTransaction();
		try
		{
			for(;!pItr->done();pItr->step())
			{
				AcDbObjectId entityId;
				pItr->getEntityId(entityId);
				AcDbEntity *pEnt = NULL;
				if(Acad::eOk==pTrans->getObject((AcDbObject*&)pEnt,entityId,AcDb::kForWrite,false))
				{
					if(AsdkEntity::desc()==pEnt->isA())
					{
						AsdkEntity *pCircle = AsdkEntity::cast(pEnt);
						assert(Acad::eOk==pCircle->setRadius(.001));

						// Erase the style...
						AsdkStyle *pStyle = NULL;
						if(Acad::eOk==pTrans->getObject((AcDbObject*&)pStyle,pCircle->style(),AcDb::kForWrite))
						{
							if(pStyle->isA() == AsdkStyle::desc())
								assert(Acad::eOk==pStyle->erase(true));
							else
								throw _T("Style was valid, but not an AsdkStyle!");
						}
						else
							throw _T("Could not open associated style");

						pCircle->setStyle(AcDbObjectId::kNull);
					}
					else
						throw _T("AsdkEntity not selected");

					pDb->transactionManager()->endTransaction();
				}
			}
		}
		catch(ACHAR *pMessage)
		{
			acutPrintf(_T("\nError: %s\n"),pMessage);
			pDb->transactionManager()->abortTransaction();
		}
	}

public:

	// - AsdkAudit_Recover.GETSTYLE command (do not rename)
	static void AsdkAudit_RecoverGETSTYLE(void)
	{
		ads_name ent;
		ads_point pt;
		if(RTNORM!=acedEntSel(_T("Select an Entity"),ent,pt))
			return;
		
		AcDbDatabase *pDb=acdbHostApplicationServices()->workingDatabase();
		AcTransaction *pTrans=pDb->transactionManager()->startTransaction();
		try
		{
			AcDbObjectId id;
			acdbGetObjectId(id,ent);
			AsdkEntity *pEnt = NULL;

			if(Acad::eOk!=pTrans->getObject((AcDbObject*&)pEnt,id,AcDb::kForRead))
				throw _T("Couldn't obtain pointer for selected entity");

			if(pEnt->isA() != AsdkEntity::desc())
				throw _T("Entity was valid, but is not an AsdkEntity!");

			AsdkStyle *pStyle = NULL;
			if(Acad::eOk!=pTrans->getObject((AcDbObject*&)pStyle,pEnt->style(),AcDb::kForRead))
				throw _T("Couldn't obtain pointer for selected entity's style");
				
			if(pStyle->isA() != AsdkStyle::desc())
				throw _T("Style was valid, but is not an AsdkStyle!");

			acutPrintf(_T("\nStyle Name: %s"),pStyle->getStyleName());
			
			pDb->transactionManager()->endTransaction();
		}
		catch (const ACHAR* pMessage)
		{
			acutPrintf(_T("\nError: %s\n"),pMessage);
			pDb->transactionManager()->abortTransaction();
		}
	}
} ;
AsdkStyleRecreator* CAudit_RecoverApp::pRecreator = NULL;


//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CAudit_RecoverApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CAudit_RecoverApp, AsdkAuditRecover, CREATE, CREATE, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CAudit_RecoverApp, AsdkAuditRecover, CORRUPT, CORRUPT, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CAudit_RecoverApp, AsdkAuditRecover, CORRUPT2, CORRUPT2, ACRX_CMD_TRANSPARENT, NULL)



ACED_ARXCOMMAND_ENTRY_AUTO(CAudit_RecoverApp, AsdkAudit_Recover, GETSTYLE, GETSTYLE, ACRX_CMD_TRANSPARENT, NULL)
