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
#include <adscodes.h>
#include <acdb.h>
#include <actrans.h>
#include "lab4utils.h"

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
    if (acdbHostApplicationServices()->workingDatabase()==NULL)
        return Acad::eNoDatabase;
    //Get a pointer to the current drawing
    //and get the drawing's block table.  Open it for read.
    if ((es = acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead))==Acad::eOk){
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

Acad::ErrorStatus
RTtoStatus(/*[in]*/int rt)
//Description:
//  Maps an ads return code to an Acad::ErrorStatus
//Note:
//  I don't care about the performance hit that this
//  extra function call introduces. 
//  The mapping here is completely arbitrary. Change it if you don't like it.
{
    ACADTRACE("RTtoStatus is mapping %d\n",rt);
    switch (rt){
    case RTNORM:    //5100 /* Request succeeded */
        return Acad::eOk;
    case RTERROR:  //-5001 /* Some other error */
        return Acad::eUnrecoverableErrors ;
    case RTCAN:    //-5002 /* User cancelled request -- Ctl-C */
        return Acad::eUserBreak;
    case RTREJ:    //-5003 /* AutoCAD rejected request -- invalid */
        return Acad::eInvalidInput;
    case RTFAIL:   //-5004 /* Link failure -- Lisp probably died */
        return Acad::eNotApplicable;
    default:
    //case RTKWORD:  //-5005 /* Keyword returned from getxxx() routine */
        //this function only intended to be called 
        //in an error checking situation. See ADSOK.
        assert(0);
        return Acad::eOk;
    }
}

