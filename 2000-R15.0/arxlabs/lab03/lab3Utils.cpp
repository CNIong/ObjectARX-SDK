//
// (C) Copyright 1999 by Autodesk, Inc. 
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
#include <dbapserv.h> 

#include <dbsymtb.h>
#include <migrtion.h>
#include "lab3utils.h"

Acad::ErrorStatus 
postToDatabase(/*[in]*/AcDbEntity* pEnt,/*[out]*/AcDbObjectId& idObj)
//Purpose:
//  Adds an entity to the MODEL_SPACE of the CURRENT database.
//Note:
//  It could be generalized to add it to any block table record of
//  any database, but why complicate it...
//
{
	Acad::ErrorStatus	  es;
	AcDbBlockTable*		pBlockTable;
	AcDbBlockTableRecord*  pSpaceRecord;

    if (acdbCurDwg()==NULL)
        return Acad::eNoDatabase;
    //Get a pointer to the current drawing
    //and get the drawing's block table.  Open it for read.
    if ((es = acdbCurDwg()->getBlockTable(pBlockTable, AcDb::kForRead))==Acad::eOk){
	//Get the Model Space record and open it for write.  This will be the owner of the new line.
        if ((es = pBlockTable->getAt(ACDB_MODEL_SPACE, pSpaceRecord, AcDb::kForWrite))==Acad::eOk){
            //Append pEnt to Model Space, then close it and the Model Space record.
            if ((es = pSpaceRecord->appendAcDbEntity(idObj, pEnt))==Acad::eOk)
                pEnt->close();
            pSpaceRecord->close();
        }
    pBlockTable->close();
    }
	//it is good programming practice to return an error status
	return es;
}


Acad::ErrorStatus createLayer(/*[in]*/const char* layerName, /*[out]*/ AcDbObjectId& id)
{
	Acad::ErrorStatus es;
	id = AcDbObjectId::kNull;
	AcDbLayerTable* pTable;

	if ((es = acdbCurDwg()->getLayerTable(pTable, AcDb::kForRead)) == Acad::eOk)
	{
		// use the overload of AcDbLayerTable::getAt() that returns the id
		if ((es = pTable->getAt(layerName, id, Adesk::kFalse)) != Acad::eOk)
		{
			// create a new layer table record using the layer name passed in
			AcDbLayerTableRecord* pLTRec = new AcDbLayerTableRecord;
			if (pLTRec)
			{
				pLTRec->setName(layerName);
				// set other properties - color, linetype, state - if desired
				// this will require more input than this simple example provides
				if ((es = pTable->upgradeOpen()) == Acad::eOk)
				{
					es = pTable->add(id, pLTRec);
					// since the new layer was successfully added to the database,
					// close it - DON'T delete it
					pLTRec->close();
				}
				else
					delete pLTRec;
			}
			else
				es = Acad::eOutOfMemory;
		}
		pTable->close();
	}
	return es;
}