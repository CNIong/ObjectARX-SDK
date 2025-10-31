//
//
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
//----- adskMyDbReactor.cpp : Implementation of adskMyDbReactor
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

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
	if (pEnt != NULL)
	{
		// use transaction since the datbase is still open for write here
		Acad::ErrorStatus es = actrTransactionManager->enableGraphicsFlush(true);
		AcTransaction *pTrans = actrTransactionManager->startTransaction();
		// if ok
		if (pTrans)
		{
			AcDbBlockTableRecord *pBTR = NULL;
			// get model space block record for write from transaction
			es = pTrans->getObject((AcDbObject*&)pBTR, db->currentSpaceId(), AcDb::kForWrite);
			// if ok
			if (es == Acad::eOk)
			{
				AcDbSortentsTable *pSortTab = NULL;
				// get AcDbSortEntsTable
				es = pBTR->getSortentsTable(pSortTab, AcDb::kForWrite, false);
				// if ok
				if (es == Acad::eOk)
				{
					// attach a smartpointer to the pSortTable so that it autocloses
					AcDbObjectPointer<AcDbSortentsTable> sortTab;
					sortTab.acquire(pSortTab);
					AcDbObjectIdArray eIds;		
					// put objectIds of all the entities in an Id array.The order of objectIds in the array is the
					// same as their draworders from bottom to top.The newly created entity is always at the top and the last item
					// in the array
					es = sortTab->getFullDrawOrder(eIds);
					// if ok
					if (es == Acad::eOk)
					{
						AcDbEntity *pRefEnt = NULL;
						// iterate through the entities in the order of their draworders. If an entity on the same layer is found
						// insert the newly created entity before it.
						int i;
						for(i=0; i<eIds.length(); i++)
						{
							es = pTrans->getObject((AcDbObject*&)pRefEnt, eIds.at(i), AcDb::kForRead);
							if(pRefEnt->layerId() == pEnt->layerId())
								break;
						}	
						eIds.insertAt(i, pEnt->objectId());
						//remove the newly created entity from the end of the array
						eIds.removeLast();
						//reset draworder
						es = sortTab->setRelativeDrawOrder(eIds);
						es=actrTransactionManager->endTransaction();
						actrTransactionManager->flushGraphics();

						//set flag for regen
						gbDraworderChanged = true;	
						return;
					}
				}
			}

			// in the unlikely event that we don't return before, abort the transaction as something has gone wrong
			actrTransactionManager->abortTransaction();
		}
	}
}