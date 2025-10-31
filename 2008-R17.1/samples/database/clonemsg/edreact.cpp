// (C) Copyright 1996-2006 by Autodesk, Inc. 
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
//  edreact.cpp

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "acdb.h"             // acdb definitions
#include "adslib.h"           // ads defs
#include "dbents.h"           // "old" entities
#include "aced.h"             // aced stuff
#include "dbdict.h"           // dictionaries
#include "dbsymtb.h"          // symboltables
#include "acgi.h"             // graphical definitions
#include "dbidmap.h"          // id mapping
#include "edreact.h"
#include "mkrenti.h"
#include "arxutils.h"
#include "mkrobje.h"
#include "tchar.h"



Adesk::Boolean
isCloned( const AcDbObjectId&  refId,
		 const AcDbIdMapping& idMap )
{
	AcDbIdPair pair;
	pair.setKey( refId );
	return idMap.compute( pair ) && pair.value() != 0;
}


// editor reactor EditorReactor
//
static AsdkEditorReactor* pEditorReactor = NULL; // MDI Safe

// call this function to
// create the reactor EditorReactor
//
void
create_EditorReactor()
{
	if (NULL == pEditorReactor)
		pEditorReactor = new AsdkEditorReactor();
	acedEditor->addReactor( pEditorReactor );
}

// call this function to
// erase the reactor EditorReactor
//
void
erase_EditorReactor()
{
	acedEditor->removeReactor(pEditorReactor);
	delete pEditorReactor;
}



void
AsdkEditorReactor::beginDeepCloneXlation(AcDbIdMapping&     idMap,
										 Acad::ErrorStatus* pRetStatus)
{
#ifdef NOD
#if defined( XLATE ) && !defined( DIRECT )
	AcDbDatabase *pOrigDb, *pDestDb;
	idMap.origDb( pOrigDb );
	idMap.destDb( pDestDb );
	bool res;
	
	AcDbIdMappingIter iter(idMap);
	AcDbIdPair idPair;
	bool bDictCloned = false;
	Acad::ErrorStatus es;
	AcDb::DeepCloneType  dcc = idMap.deepCloneContext();
	for (iter.start(); !iter.done(); iter.next()) 
	{
		if (!iter.getMap(idPair))
			continue;
		if (!idPair.isCloned())
			continue;
		
		AsdkMkrEntity *pMkrEnt;
		if (Acad::eOk != acdbOpenObject( pMkrEnt, idPair.key(), AcDb::kForRead ))
			continue;
		AcDbObjectId refId = pMkrEnt->refId();
		pMkrEnt->close();
		
		if (!isCloned( refId, idMap )) 
		{
			// for soft pointer id's.
			//
			AcDbObject* pO=NULL,*pClone=NULL;
			if (acdbOpenObject(pO,refId,AcDb::kForRead)!=Acad::eOk)
				continue;
			AcDbObjectId newId;
			if (AcDb::kDcWblock == idMap.deepCloneContext() 
#ifndef HARDPOINTER
				|| AcDb::kDcWblkObjects == idMap.deepCloneContext()
#endif  // !HARDPOINTER
				)
			{
				// no action required when using hard pointer id's
#ifndef HARDPOINTER
				//pDestDb->addAcDbObject( newId, pClone );
				es = pO->wblockClone(pDestDb,pClone,idMap,false);
				if (pClone!=NULL)
					pClone->close();
#endif  // !HARDPOINTER
			}
			else 
			{
				assert(pOrigDb!=NULL);
				assert(pDestDb!=NULL);
				//get or create our dictionary in the destination database
				AcDbDictionary *pDestDict =
					getDict( _T(/*NOXLATE*/"ASDK_MYDICT"), AcDb::kForWrite, pDestDb );
				assert(NULL != pDestDict);
				//get our dictionary in the the source db
				AcDbObjectId srcId = getDictId( _T(/*NOXLATE*/"ASDK_MYDICT"), pOrigDb,false );
				//make sure that this pair appears in the id map
				AcDbIdPair searchPair(srcId,pDestDict->objectId(),false,true,true);
				if (pDestDict->isNewObject())
					searchPair.setIsCloned(true); //it was 'cloned': we just created it
				idMap.assign(searchPair);
				//clone the object
				es = pO->deepClone(pDestDict,pClone,idMap,true);
				assert(es==Acad::eOk);
				if (pClone!=NULL)
				{
					if (pDestDict->has( _T(/*NOXLATE*/"MYENTRY") ))
						pDestDict->setAt( _T("*"), pClone, newId );
					else
						pDestDict->setAt( _T(/*NOXLATE*/"MYENTRY"), pClone, newId );
					searchPair.setKey(pO->objectId());
					//find this pair
					res = idMap.compute(searchPair);
					assert(res);
					//let everyone know that its owner has been xlated
					searchPair.setIsOwnerXlated(true);
					//change it
					idMap.change(searchPair);
					pClone->close();
				}
				pDestDict->close();
			}
			pO->close();
		}
		//handle refedit across dbs
		if (AcDb::kDcWblkObjects == idMap.deepCloneContext() )
		{
			//we use the same code for check-in and check-out!
			AcDbIdPair pair;
			//lookup the object in the map
			pair.setKey( refId);
			res = idMap.compute( pair );
			assert(res);
			AcDbObject* pClone;
			AcDbObjectId newId;
			//open clone, it has already been copied either automatically (hard pointer) or
			//by the code above (soft pointer)
			if (acdbOpenObject(pClone,pair.value(),AcDb::kForWrite)==Acad::eOk)
			{
				//try to get our dictionary in the destination database
				AcDbDictionary* pDestDict = 
					getDict( _T(/*NOXLATE*/"ASDK_MYDICT"),AcDb::kForWrite, pDestDb,false);
				if (pDestDict == NULL)
				{
					//Not yet there:
					//it is being copied so find it and set up its owner
					AcDbObject* pO;
					if ((es = acdbOpenObject(pO,pair.key(),AcDb::kForRead))==Acad::eOk)
					{
						AcDbIdPair searchPair;
						searchPair.setKey(pO->ownerId());
						es = pO->close();
						if (es == Acad::eOk && idMap.compute(searchPair))
						{
							AcDbDictionary* pNOD;
							if ((es=pDestDb->getNamedObjectsDictionary(pNOD,AcDb::kForWrite))==Acad::eOk)
							{
								if ((es=acdbOpenObject(pO,searchPair.value(),AcDb::kForWrite))==Acad::eOk)
								{
									//Let NOD in the dest db know that this dict belongs to it
									if ((es = pNOD->setAt(_T(/*NOXLATE*/"ASDK_MYDICT"),pO,newId))==Acad::eOk)
									{
										//Let the cloning process know that we have set
										//the owner
										searchPair.setIsOwnerXlated(true);
										idMap.change(searchPair);
										bDictCloned = true;
									}
									es = pO->close();
								}
								es = pNOD->close();
							}
						}
					}
				}
				else
				{
					//the destination db has our dictionary:
					//check if it was just cloned above
					//if it was cloned then there's nothing we need to do
					if (!bDictCloned)
					{
						//simply use anonymous objects
						if ((es =pDestDict->setAt(_T("*"),pClone,newId))==Acad::eOk)
						{
							//make sure the the longtransaction tries to use swapIdWith
							//(it only applies during checkin)
							pair.setIsPrimary(true);
							//Let the cloning process know that we have set
							//the owner
							pair.setIsOwnerXlated(true);
							idMap.change(pair);
						}
					}
					pDestDict->close();
				}
				if (es!=Acad::eOk)
				{
					*pRetStatus = es;
					return;
				}
				pClone->close();
			}
		}
	}
#endif  // XLATE
#endif //NOD
}


