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
//-----------------------------------------------------------------------------
#include "windows.h"

#include "aced.h"
#include "rxregsvc.h"
#include "rxdlinkr.h"

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

//-----------------------------------------------------------------------------
void lab9Command () ;

//-----------------------------------------------------------------------------
bool isModuleLoaded (const char *str) {
    AcDbVoidPtrArray *pApps =reinterpret_cast<AcDbVoidPtrArray *>(acrxLoadedApps ()) ;
    if ( pApps == NULL )
        return (false) ;
    bool bFound =false ;
    for ( int i =0 ; i < pApps->length () ; i++ ) {
        if ( stricmp (reinterpret_cast<const char *>(pApps->at (i)), str) == 0 ) {
            bFound =true ;
            break ;
        }
    }
    for ( ; pApps->length () > 0 ; ) {
        delete reinterpret_cast<char *>(pApps->at (0)) ;
        pApps->removeAt (0) ;
    }
    delete pApps ;
    return (bFound) ;
}

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
			//----- This module is dependant of module OarxLab9(a).dbx which 
			//----- defines the custom entity. 
			//----- Try to load OarxLab9(a).dbx and/or add a dependency on it

            if ( !isModuleLoaded (MODULE_FILENAME) ) {
                //----- Try demand loading first
                if ( !acrxLoadApp (MODULE_NAME, true) ) {
                    //----- If it does not work then try loading it from the search path
                    if ( !acrxDynamicLinker->loadModule (MODULE_FILENAME, false, true) ) { //----- OarxLab9(a).dbx
                        //----- OarxLab9(a).dbx is not is the acad search path

                        //----- Try to load the DBX module from the same directory as us.
                        HMODULE hInst =::GetModuleHandle ("OarxLab9c.arx") ;
                        char buffer [MAX_PATH] ;
                        ::GetModuleFileName (hInst, buffer, MAX_PATH) ;

                        char *p =strrchr (buffer, '\\') + 1 ;
                        strcpy (p, MODULE_FILENAME) ;
                    
                        if ( !acrxDynamicLinker->loadModule (buffer, false, true) ) {
				            //----- We *must* stop here while the command cannot work without
				            //----- module OarxLab9(a).dbx
				            //----- We probably could try to load the module ourself, but we do not
				            //----- want to complicate the code in a sample.
				            acutPrintf ("\nCannot continue!") ;
                            acutPrintf ("\nUnable to load %s, the module is probably not in the AutoCAD search path.\n", MODULE_FILENAME) ;
                            //----- Return an Error, so AutoCAD will unload that module
				            return AcRx::kRetError ;
                        }
                    }
                }
			}
            //----- Bump the reference count 
            acrxLoadModule (MODULE_FILENAME, false, false) ;

			if ( acrxServiceIsRegistered (EmployeeServiceName) == 0 ) {
                acutPrintf ("\nService % is not present. This must be a wrong version of %s\n", EmployeeServiceName, MODULE_NAME) ;
                acrxDynamicLinker->unloadModule (MODULE_NAME) ;
                return AcRx::kRetError ;
			}
			//----- Register the command
			acedRegCmds->addCommand ("OARX_LAB9C", "_lab9c", "lab9c", ACRX_CMD_MODAL, lab9Command) ;
			break ;
		case AcRx::kUnloadAppMsg:
            //----- Unreference the DBX module
			acrxDynamicLinker->unloadModule (MODULE_NAME) ;
			//----- Remove the command group so that AutoCAD won't call us
			//----- when we are not here.
			acedRegCmds->removeGroup ("OARX_LAB9C") ;
			break ;
    }
    return (AcRx::kRetOK) ;
}
