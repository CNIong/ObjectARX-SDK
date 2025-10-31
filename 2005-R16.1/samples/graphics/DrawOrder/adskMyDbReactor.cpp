//
//
// (C) Copyright 2002-2003 by Autodesk, Inc. 
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
//----- adskMyDbReactor.cpp : Implementation of adskMyDbReactor
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "adskMyDbReactor.h"
#include "sorttab.h"
#include "util.h"
//-----------------------------------------------------------------------------
ACRX_CONS_DEFINE_MEMBERS(adskMyDbReactor, AcDbDatabaseReactor, 1)

bool gbDraworderChanged = false;


//-----------------------------------------------------------------------------
adskMyDbReactor::adskMyDbReactor (AcDbDatabase *pDb) : AcDbDatabaseReactor(), mpDatabase(pDb) 
{
	if ( pDb )
		pDb->addReactor (this) ;
}


//-----------------------------------------------------------------------------
adskMyDbReactor::~adskMyDbReactor () {
	Detach () ;
}


//-----------------------------------------------------------------------------
void adskMyDbReactor::Attach (AcDbDatabase *pDb) {
	Detach () ;
	if ( mpDatabase == NULL ) {
		if ( (mpDatabase = pDb) != NULL )
			pDb->addReactor (this) ;
	}
}


void adskMyDbReactor::Detach () {
	if ( mpDatabase ) {
		mpDatabase->removeReactor (this) ;
		mpDatabase = NULL ;
	}
}


AcDbDatabase *adskMyDbReactor::Subject () const {
	return (mpDatabase) ;
}


bool adskMyDbReactor::IsAttached () const {
	return (mpDatabase != NULL) ;
}


//When an new entity is added, set its draw order based on the draw order of other entities on the same layer.
void
adskMyDbReactor::objectAppended(const AcDbDatabase* db, const AcDbObject* pObj)
{
	AcDbEntity * pEnt = AcDbEntity::cast(pObj);
	Acad::ErrorStatus es;
	if (pEnt != NULL)
	{
		AcDbBlockTable *pBT = NULL;
		AcDbBlockTableRecord *pBTR	= NULL;
		
		//use transaction since the datbase is still open for write here.
		es=actrTransactionManager->enableGraphicsFlush(true);
		AcTransaction *pTrans = actrTransactionManager->startTransaction() ;
		
		if(!pTrans)
		{
			acutPrintf("\nCan't start transaction!");
			return;
		}
		AcDbObject *pObj = NULL ;
		AcDbDatabase *pDb = NULL;
		AcDbObjectId modelSpaceId;
		pDb = AcDbDatabase::cast(db);
		
		//get AcDbBlockTable for read
		if(Acad::eOk != pDb->getBlockTable(pBT, AcDb::kForRead))
		{
			acutPrintf("can't open block table for read");
			actrTransactionManager->abortTransaction();
			return;
		}
		
		//get the model space object id
		if(Acad::eOk != pBT->getAt( ACDB_MODEL_SPACE, modelSpaceId))
		{
			acutPrintf("\ncan't get model space Id");
			actrTransactionManager->abortTransaction();
			pBT->close();
			return;
		}
		
		pBT->close();
		
		
		//get model space block record for write from transaction
		if (Acad::eOk != pTrans->getObject((AcDbObject*&)pBTR, modelSpaceId, AcDb::kForWrite))
		{
			acutPrintf("\ncan't open model space block table record for write");
			actrTransactionManager->abortTransaction();
			return;
		}
		
		AcDbObjectIdArray eIds;
		
		//get AcDbSortEntsTable
		AcDbSortentsTable *pSortTab = NULL;
		if(Acad::eOk != pBTR->getSortentsTable(pSortTab, AcDb::kForWrite, false))
		{
			acutPrintf("\ncan't get AcDbSortEntsTable for write");
			actrTransactionManager->abortTransaction();
			return;
		}
		
		//put objectIds of all the entities in an Id array.The order of objectIds in the array is the
		//same as their draworders from bottom to top.The newly created entity is always at the top and the last item
		//in the array
		if(Acad::eOk != pSortTab->getFullDrawOrder(eIds))
		{
			acutPrintf("\ncan't get full draworder");
			pSortTab->close();
			actrTransactionManager->abortTransaction();
			return;
		}
		AcDbEntity *pRefEnt = NULL;
		//iterate through the entities in the order of their draworders. If an entity on the same layer is found
		//insert the newly created entity before it.
		int i;
		for(i =0; i<eIds.length(); i++)
		{
			es = pTrans->getObject((AcDbObject*&)pRefEnt, eIds.at(i), AcDb::kForRead);
			if(pRefEnt->layerId() == pEnt->layerId())
				break;
		}	
		eIds.insertAt(i, pEnt->objectId());
		//remove the newly created entity from the end of the array
		eIds.removeLast();
		//reset draworder
		es = pSortTab->setRelativeDrawOrder(eIds);
		pSortTab->close();
		es=actrTransactionManager->endTransaction();
		actrTransactionManager->flushGraphics();

		//set flag for regen
		gbDraworderChanged = true;	
	}

}