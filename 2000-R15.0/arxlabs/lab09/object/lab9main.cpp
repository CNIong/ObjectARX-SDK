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
#include "aced.h"
#include "rxdlinkr.h"

//-----------------------------------------------------------------------------
#include "dbelipse.h"
#include "dbmain.h"
#include "dbproxy.h"
#include "dbsymtb.h"
#include "geassign.h"
#include "rxboiler.h"
#include "rxdict.h"

#include "Lab9Employee.h"

//-----------------------------------------------------------------------------
//----- This is the entry point that makes a simple DLL an ARX.
//----- This entry point must be exported either by means of a def file
//----- or by the means of _declspec
extern "C" AcRx::AppRetCode acrxEntryPoint (AcRx::AppMsgCode msg, void *pkt) {
    switch (msg) {
		case AcRx::kInitAppMsg:
			//----- An ARX application is locked to memory by default.
			//----- You must make the following function call to unlock it.
			acrxDynamicLinker->unlockApplication (pkt) ;
			//----- Register as  MDI aware
			acrxDynamicLinker->registerAppMDIAware(pkt);
			//----- Register the OarxEmployee class into the AutoCAD runtime class hierachy
			OarxEmployee::rxInit () ;
			//----- Build-up the AutoCAD runtime class hierachy with the new class entry
			acrxBuildClassHierarchy () ;
			//----- Do not forget our ServiceName
			acrxDynamicLinker->registerService (EmployeeServiceName, new OarxEmployeeService) ;
			break ;
		case AcRx::kUnloadAppMsg:
			//----- Unregister the OarxEmployee class from the AutoCAD runtime
			//----- class hierachy. So AutoCAD will turn our custom entity into
			//----- a proxy entity when we are not there.
			deleteAcRxClass (OarxEmployee::desc ()) ;
			//----- Do not forget to remove the dictionary entry
			delete acrxServiceDictionary->remove (EmployeeServiceName) ;
			break ;
    }
    return (AcRx::kRetOK) ;
}
