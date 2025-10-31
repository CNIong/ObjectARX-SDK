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
#include "acdb.h"
#include "adslib.h"
#include "dbents.h"
#include "aced.h"
#include "dbmain.h"
#include "dbdict.h"
#include "dbsymtb.h"
#include "Lab7DatabaseReactor.h"
#include "Lab7ObjectReactor.h"

#include "lab7Utils.h"

#include "Lab7PerDocData.h"

#include <string.h>

//global variables
extern AsdkLab7ObjectReactor* pAsdkLab7ObjectReactor;


///////////////////////////////////////////////////////
//database reactor AsdkLab7DbReactor



/////////////////////////////////////////////////////
//database reactor notifications

void AsdkLab7DbReactor::objectAppended(const AcDbDatabase* dwg,
                                        const AcDbObject* dbObj)
{
    // dbObj should be of kind AcDbBlockReference
	// and of name "employee"
	//
    AcDbBlockReference *pInsert;
	
	if(!isAnInsertOfEmployee(dbObj, pInsert))
		return;
	
    //ok, this is an employee.
    //attach the object reactor
	//
    pInsert->addReactor(pAsdkLab7ObjectReactor);
}
