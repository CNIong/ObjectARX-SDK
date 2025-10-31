//
//
// (C) Copyright 2002-2007 by Autodesk, Inc. 
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
// util.cpp : utility functions

#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "util.h"

#pragma warning(disable: 4101)

//Get the AcDbSortEntsTable of  the model space of current drawing. 
//If it's not already exist, create a new one.
bool getOrCreateSortEntsDictionary(AcDbSortentsTable *&pSortTab)
{
	
	//Get the current working database
	AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
	
	if (pDb)
	{
		AcDbBlockTable *pBT	= NULL;
		AcDbBlockTableRecord *pBTR	= NULL;
		Acad::ErrorStatus es;
		
		//Get block Table
		if (Acad::eOk != pDb->getBlockTable(pBT,AcDb::kForRead))
		{
			acutPrintf(_T("\nCouldn't get the block table"));
			return false;
		}

		acDocManager->lockDocument(acDocManager->document(pDb));
		//Get model space block table record
		if (Acad::eOk != pBT->getAt(ACDB_MODEL_SPACE, pBTR, AcDb::kForRead))
		{
			acutPrintf(_T("\nCouldn't get the MODEL_SPACE block record opened"));
			pBT->close();
			return false;

		}
		pBT->close();

		//Get the AcDbSortEntsTable
		if (Acad::eOk !=pBTR->getSortentsTable(pSortTab, AcDb::kForWrite, true))
		{
			acutPrintf(_T("\nCouldn't get or create AcDbSortEntsTable of Model Space"));
			pBTR->close();
			return false;
		}
		pBTR->close();

		return true;

	}else
	{
		return false;
	}

}


//put the Ids of all the entities on a certain layer in the array, "ents"
bool getAllEntitiesOnLayer(TCHAR* layerName, AcDbObjectIdArray &ents)
{
	
	Acad::ErrorStatus es;
	//construct a resbuffer to select all the entities on a layer
	struct resbuf eb1; 
	TCHAR sbuf1[kNameLength]; // Buffers to hold string 
	eb1.restype = 8;  // select based on layer name
	_tcscpy(sbuf1, layerName); 
	eb1.resval.rstring = sbuf1; 
	eb1.rbnext = NULL; // No other properties 
	
	ads_name ss;
	if (RTNORM != acedSSGet(_T("X"), NULL, NULL, &eb1, ss ) ) 
		return false;
	long nEnts;
	
	//Iterate through the selection set, get all the entities' object Ids and
	//append them to the array, "ents"
	acedSSLength( ss, &nEnts );
	ents.setPhysicalLength(nEnts);
	for(int i = 0; i < nEnts; i++ ) {
		ads_name eName;
		acedSSName(ss, i, eName);
		AcDbObjectId id;
		acdbGetObjectId(id, eName);
		ents.append(id);
	}
	acedSSFree( ss );
	
	return true;

}


//Put the Ids of all the layers in the layer table in array, "arrLayers" 
bool getAllLayers(AcDbObjectIdArray &arrLayers)
{
	
	AcDbLayerTable *layerTable ;    
	Acad::ErrorStatus es ;   
	
	//open the layertable in the current drawing    
	if (Acad::eOk !=  acdbHostApplicationServices()->workingDatabase()->getLayerTable(layerTable, AcDb::kForRead))
	{       
		acutPrintf (_T("\nCouldn''t get the layer table")) ;      
		return false;    
	}   
	
	//create a new iterator    
	AcDbLayerTableIterator *pLayerTableIterator ;   
	if (Acad::eOk != layerTable->newIterator (pLayerTableIterator))
	{       
		acutPrintf (_T("\nCouldn''t get a new layer table iterator")) ;        
		layerTable->close () ;       
		return false ;    
	}    
	layerTable->close () ;   
	AcDbObjectId layerId ;    
	
	//iterate through the all layers and collect their ids   
	for ( ; !pLayerTableIterator->done () ; pLayerTableIterator->step()) 
	{        
		if (Acad::eOk != pLayerTableIterator->getRecordId(layerId))           
		{	      
			acutPrintf(_T("\nCannot get layers"));
			continue;
		}else
		{
			arrLayers.append(layerId);
		}
	}
	delete pLayerTableIterator;
	
	return true;

}


