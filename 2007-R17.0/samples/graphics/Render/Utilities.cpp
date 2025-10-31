//
// (C) Copyright 2005-2006 by Autodesk, Inc. 
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
#include "stdafx.h"

namespace RenderAPISample
{
	Acad::ErrorStatus 
	postEntToCurrentSpace(AcDbDatabase* pDb, AcDbEntity* pEnt)
	{
		AcDbObjectId objId;

		return postEntToCurrentSpace(pDb, pEnt, objId);
	}

	Acad::ErrorStatus 
	postEntToCurrentSpace(AcDbDatabase* pDb, AcDbEntity* pEnt, AcDbObjectId& objId)
	{
		Acad::ErrorStatus es = addEntToCurrentSpace(pDb, pEnt, objId);
		if(es!=Acad::eOk) return es;

		return pEnt->close();
	}

	Acad::ErrorStatus 
	addEntToCurrentSpace(AcDbDatabase* pDb, AcDbEntity* pEnt)
	{
		AcDbObjectId objId;
		return addEntToCurrentSpace(pDb, pEnt, objId);
	}

	Acad::ErrorStatus 
	addEntToCurrentSpace(AcDbDatabase* pDb, AcDbEntity* pEnt, AcDbObjectId& objId)
	{
		Acad::ErrorStatus es;	
		AcDbBlockTableRecord *pBlkRec;
		es = acdbOpenObject(pBlkRec, pDb->currentSpaceId(), AcDb::kForWrite);
		if(es!=Acad::eOk) return es;
		es = pBlkRec->appendAcDbEntity (objId, pEnt) ;   
		if(es!=Acad::eOk) return es;

		return pBlkRec->close();
	}

	// Create the dictionary and name it as 'dictName' if it doesn't exist. Otherwise, add an entry with name 'entryName'
	// into the dictionary. If the entry has already been there, remove it and add a new one to keep it up to date.
	// Parameters:
	//		pObj: pointer to the object which is going to be added to the dictionary.
	//		dictId: return, the ObjectId of the dictionary.
	//		objId: return, the ObjectId of the dictionary entry.
	// Note: If no return ids are needed, please just use another signature following this one.
	Acad::ErrorStatus addAnEntryToADict(AcDbDatabase* pDb, const ACHAR* dictName, const ACHAR* entryName, AcDbObject* pObj, AcDbObjectId& dictId, AcDbObjectId& objId)
	{
		AcDbDictionary *pNamedobj, *pDict;
		Acad::ErrorStatus es;
		es = pDb->getNamedObjectsDictionary(pNamedobj,AcDb::kForRead);
		if(es != Acad::eOk)
			return es;

		if ( (es = pNamedobj->getAt(dictName, dictId) )== Acad::eKeyNotFound)
		{
			pNamedobj->upgradeOpen();
			pDict = new AcDbDictionary;
			assert(pDict);
			es = pNamedobj->setAt(dictName, pDict, dictId);
			if( es != Acad::eOk )
			{
				pNamedobj->close();
				return es;
			}
			pNamedobj->downgradeOpen();
		}
		else
		{
			es = acdbOpenObject(pDict, dictId, AcDb::kForRead);
			if( es != Acad::eOk )
			{
				pNamedobj->close();
				return es;
			}
		}
		pNamedobj->close();

		es = pDict->getAt(entryName, objId);
		pDict->upgradeOpen();
		if( es != Acad::eKeyNotFound )
		{
			es = pDict->remove(entryName);
			assert(es == Acad::eOk);
		}
		es = pDict->setAt(entryName, pObj, objId);
		pDict->downgradeOpen();
		pDict->close();
		return es;
	}

	Acad::ErrorStatus addAnEntryToADict(AcDbDatabase* pDb, const ACHAR* dictName, const ACHAR* entryName, AcDbObject* pObj)
	{
		AcDbObjectId dictId, objId;
		return addAnEntryToADict(pDb, dictName, entryName, pObj, dictId, objId);
	}

	// Get the render environment object or global object.
	// Parameters:
	//		pCls: in, the desc() of the object interested in;
	//		pObj: out, pointer to the object opened for READ. You need to upgrade it to WRITE if you want to modify it.
	Acad::ErrorStatus renderEnvironmentOrGlobalObj(AcDbDatabase* pDb, AcRxClass* pCls, AcDbObject*& pObj)
	{
		AcDbDictionary *pNamedobj;
		ACHAR dictName[MAX_PATH];
		AcDbObjectId objId;

		Acad::ErrorStatus es;
		es = pDb->getNamedObjectsDictionary(pNamedobj,AcDb::kForRead);
		if(es != Acad::eOk)
			return es;

		if(pCls == AcDbRenderEnvironment::desc())
			wcscpy_s(dictName, _T("ACAD_RENDER_ENVIRONMENT"));
		else if( pCls  == AcDbRenderGlobal::desc())
			wcscpy_s(dictName, _T("ACAD_RENDER_GLOBAL"));

		if ( (es = pNamedobj->getAt(dictName, objId) ) != Acad::eKeyNotFound)
		{
			es = acdbOpenObject(pObj, objId, AcDb::kForRead);
			if( es != Acad::eOk )
			{
				pNamedobj->close();
				return es;
			}
		}
		else
		{
			pNamedobj->close();
			pObj = NULL;
			return es;
		}
		es = pNamedobj->close();

		return es;
	}


	//enum ViewType {
	//	NoCurrentView = 0,
	//	ModelSpaceView,
	//	PaperSpaceView
	//};

	AcDbObjectId currentViewId(AcDbDatabase* pDb, ViewType& vt)
	{
		Acad::ErrorStatus es = Acad::eOk;
		AcDbObjectId viewId = AcDbObjectId::kNull;

		// Check whether passed-in DB is valid.
		if(pDb)
		{
			// Check whether  PaperSpace layout is active.
			if (!pDb->tilemode())
			{
				viewId = acdbGetCurVportId(pDb);
				AcDbObjectPointer<AcDbViewport> pViewport(viewId, AcDb::kForRead);
				
				// Check whether no view in the PaperSpace is being activated.
				if( pViewport.openStatus() != Acad::eOk || pViewport->number() == 1 )
				{
					vt = NoCurrentView;
				}
				else	// A view is being activated in the current PaperSpace
				{
					vt = PaperSpaceView;
				}
			}
			else	// In ModelSpace layout
			{
				es = acedVports2VportTableRecords();
				assert(es==Acad::eOk);

				AcDbViewportTable *pVT; 
				es = pDb->getSymbolTable(pVT, AcDb::kForRead); 
				assert(es==Acad::eOk && pVT);
				// Find the current ViewportTableRecord, which will be the first one with the name '*Active'. 
				es = pVT->getAt(_T("*Active"),viewId); 
				pVT->close();

				vt = ModelSpaceView;
			}
		}

		return viewId;
	}
}
