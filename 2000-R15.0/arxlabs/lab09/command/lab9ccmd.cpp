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
#include <assert.h>
#include <stdio.h>

#include "aced.h"
#include "acestext.h"
#include "actrans.h"
#include "dbents.h"
#include "dbmain.h"
#include "dbsymtb.h"
#include "rxdlinkr.h"
#include "rxregsvc.h"

#include "adslib.h"

#include "dbapserv.h"
//-----------------------------------------------------------------------------
#include "dbelipse.h"
#include "dbproxy.h"
#include "dbsymtb.h"
#include "geassign.h"
#include "rxboiler.h"

#ifdef LAB9OBJECT
#include "../Object/Lab9Employee.h"
#else
#include "../ObjectA/Lab9aEmployee.h"
#endif

#include "../Lab9Utils.h"

//-----------------------------------------------------------------------------
//----- We need to call the ACRX_DEFINE_MEMBERS() macro in order to define the
//----- ARX static members variable in that module. We *must* not call the ARX
//----- ACRX_DXF_DEFINE_MEMBERS() as we have already done this in the Lab9.arx
//----- module which defines the entity object
ACRX_DEFINE_MEMBERS (OarxEmployee) ;

//-----------------------------------------------------------------------------
//----- This is used as the key for our custom
//----- dictionary. Note the registered developer id 'OARX'
//----- at the beginning
void lab9Command () {
	OarxEmployee *p =NULL ;

	try {
		//----- Start transaction for the db operations in this command
		actrTransactionManager->startTransaction () ;
		//----- Prompt the use for the an id
		int id ;
		ADSOK ( acedGetInt ("Enter employee's ID:", &id) ) ;
		//----- Before continuing, we should verify if that Employee is already registered
		if ( EmployeeService->isEmployeeExist (id) != Adesk::kTrue ) {
			//----- Continue data acquisition
			int cubeNumber ;
			char strFirstName [133] ;
			char strLastName [133] ;
			AcGePoint3d position ;

			ADSOK ( acedGetInt ("Enter cube number:", &cubeNumber) ) ;
			ADSOK ( acedGetString (0, "Enter employee's first name:", strFirstName) ) ;
			ADSOK ( acedGetString (0, "Enter employee's last name:", strLastName) ) ;
			ADSOK ( acedGetPoint (asDblArray (position), NULL, asDblArray (position)) ) ;

			p =EmployeeService->createEmployee (id, position, cubeNumber,strFirstName, strLastName) ;
			if ( p == NULL )
				throw Acad::eOutOfMemory ;
		}
		//----- Stop transaction
        actrTransactionManager->endTransaction () ;

	} catch (const Acad::ErrorStatus es) {
		if ( p != NULL && p->objectId () == AcDbObjectId::kNull )
			delete p ;
		//----- Abort, rollback all db operations
		actrTransactionManager->abortTransaction () ;
		//----- Check if the user has cancelled us, then we don't report anything
		if ( es != Acad::eUserBreak )
			acutPrintf ("***Error: %s\n", acadErrorStatusText (es)) ;
	}
}
