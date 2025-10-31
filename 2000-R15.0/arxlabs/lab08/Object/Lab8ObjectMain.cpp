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
#include "rxdlinkr.h"
#include "aced.h"
#include "rxregsvc.h"
#include "lab8objectemployeedetails.h"
#include "lab8objectemployeeentry.h"


//This is the entry point that makes a simple DLL an ARX.
//This entry point must be exported either by means of a def file
//or by the means of _declspec

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt) 
{
	static bool bServiceRegistered = false;
    switch (msg) {
    case AcRx::kInitAppMsg:
        //An ARX application is locked to memory by default.
        //You must make the following function call to unlock
        //it.
        acrxDynamicLinker->unlockApplication(pkt); 
		//support MDI
		acrxDynamicLinker->registerAppMDIAware(pkt);

		// checking if somebody else has registered a service with
		// the same name as the service we'd like to register or not
        if (acrxServiceDictionary->at(EMPLOYEE_DETAILS_SERVICE) ||
			 acrxServiceDictionary->at(EMPLOYEE_ENTRY_SERVICE) ){
			
			acutPrintf("Cannot continue bacause another module has registered the service\nname EMPLOYEE_DETAILS_SERVICE or EMPLOYEE_ENTRY_SERVICE\nUNLOADING!" );
            return AcRx::kRetError;	
		}
        acrxRegisterService(EMPLOYEE_DETAILS_SERVICE);
        acrxRegisterService(EMPLOYEE_ENTRY_SERVICE);
		bServiceRegistered = true;

        //intialize our custom classes
        EmployeeDetails::rxInit();
        EmployeeEntry::rxInit();
        acrxBuildClassHierarchy();
        break;
    case AcRx::kUnloadAppMsg:
		if ( !bServiceRegistered )
			break;
        deleteAcRxClass(EmployeeDetails::desc());
        deleteAcRxClass(EmployeeEntry::desc());
        delete acrxServiceDictionary->remove(EMPLOYEE_DETAILS_SERVICE);
        delete acrxServiceDictionary->remove(EMPLOYEE_ENTRY_SERVICE);
        break;
	}
    return AcRx::kRetOK;
}
