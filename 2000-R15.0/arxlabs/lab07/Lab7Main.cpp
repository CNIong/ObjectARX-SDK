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
#include "aced.h"
#include "rxregsvc.h"
#include "dbsymtb.h"
#include "acdocman.h"
#include "Lab7DatabaseReactor.h"
#include "Lab7EditorReactor.h"
#include "Lab7ObjectReactor.h"
#include "lab7Utils.h"

#include "Lab7PerDocData.h"
//the reactor AsdkLab7ObjectReactor
AsdkLab7ObjectReactor* pAsdkLab7ObjectReactor = NULL;


//This is the entry point that makes a simple DLL an ARX.
//This entry point must be exported either by means of a def file
//or by the means of _declspec
extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt) 
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        //An ARX application is locked to memory by default.
        //You must make the following function call to unlock
        //it.
        acrxDynamicLinker->unlockApplication(pkt); 
		//support MDI
		acrxDynamicLinker->registerAppMDIAware(pkt);
       //Create transient object reactor
        pAsdkLab7ObjectReactor = new AsdkLab7ObjectReactor;

		// Add the database and the object reactors to the actual doc
		// For the other documents these will be added on document activation
		assert ( chEmployeesInfo.m_pDbReactor == NULL );
		chEmployeesInfo.m_pDbReactor = new AsdkLab7DbReactor();
		acdbHostApplicationServices()->workingDatabase()->addReactor(chEmployeesInfo.m_pDbReactor);

		attachReactorToAllEmployee(true);

		//Create the editor reactor - not document specific
        CreateMyEditorReactor();
        break;
    case AcRx::kUnloadAppMsg:
        //Delete the editor reactor
        EraseMyEditorReactor();
		//Delete the transient object reactor
        if (pAsdkLab7ObjectReactor)
            delete pAsdkLab7ObjectReactor;
        break;
   }
    return AcRx::kRetOK;
}