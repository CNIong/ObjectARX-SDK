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
#include <dbents.h>
#include <dbsymtb.h>
#include <dbapserv.h>
#include "lab2utils.h"

Acad::ErrorStatus 
postToDatabase(/*[in]*/AcDbEntity* pEnt,/*[out]*/AcDbObjectId& idObj)
//Purpose:
//  Adds an entity to the MODEL_SPACE of the CURRENT database.
//Note:
//  It could be generalized to add it to any block table record of
//  any database, but for now let's keep it simple...
//
{
	Acad::ErrorStatus	  es;
	AcDbBlockTable*		pBlockTable;
	AcDbBlockTableRecord*  pSpaceRecord;
	//Make sure that we have a working database
//{{BEGIN_LEVEL_ADVANCED
    if (acdbHostApplicationServices()->workingDatabase()==NULL)
        return Acad::eNoDatabase;
//{{END_LEVEL_ADVANCED
    //Get a pointer to the current drawing
    //and get the drawing's block table.  Open it for read.
//{{BEGIN_LEVEL_ADVANCED
    if ((es = acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead))==Acad::eOk){
//{{END_LEVEL_ADVANCED
	//Then get the Model Space record and open it for write.  
	//This will be the owner of the new line.
//{{BEGIN_LEVEL_ADVANCED
	//...
//{{BEGIN_LEVEL_INTERMEDIATE
        if ((es = pBlockTable->getAt(ACDB_MODEL_SPACE, pSpaceRecord, AcDb::kForWrite))==Acad::eOk){
//{{END_LEVEL_INTERMEDIATE
//{{END_LEVEL_ADVANCED
    //Append pEnt to Model Space, then close it and the Model Space record.
//{{BEGIN_LEVEL_ADVANCED
	//...
//{{BEGIN_LEVEL_INTERMEDIATE
            if ((es = pSpaceRecord->appendAcDbEntity(idObj, pEnt))==Acad::eOk)
                pEnt->close();
            pSpaceRecord->close();
        }
//{{END_LEVEL_INTERMEDIATE
//{{END_LEVEL_ADVANCED
	//Close the block table
//{{BEGIN_LEVEL_ADVANCED
	    pBlockTable->close();
//{{END_LEVEL_ADVANCED
    }
	//it is good programming practice to return an error status
	return es;
}

