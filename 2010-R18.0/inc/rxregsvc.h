//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 1992-2007 by Autodesk, Inc.
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
//////////////////////////////////////////////////////////////////////////////
//
// Name:            rxregsvc.h
//
// Description:     
//
//////////////////////////////////////////////////////////////////////////////
#ifndef   _RXREGSVC_H
#define   _RXREGSVC_H 1

#include "rxdlinkr.h"
#include "adesk.h"
#pragma pack (push, 8)

// Load a module, given its file name. 
//
bool acrxLoadModule(const ACHAR * moduleName, bool printit, bool asCmd=false);

// Load an app, given its logical app name. 
//
bool acrxLoadApp(const ACHAR * appname, bool asCmd=false);

// UnLoad a module, given its file name. Module's services and classes are 
// queried for dependencies.  If all module elements have no dependencies, 
// then unload can proceed.
//
bool acrxUnloadModule(const ACHAR * moduleName, bool asCmd=false);

// UnLoad an app, given its logical app name.
//
bool acrxUnloadApp(const ACHAR * appName, bool asCmd=false);

// Return an AcDbVoidPtrArray* containing names of applications
// that are currently loaded.  Caller must delete the names
// and the array afterwards.  See acrxAppIsLoaded(), if that's
// all you want to use this for.
//
void *acrxLoadedApps();

// Find out if an app is loaded.  Name is case independent
// but must include the extension (.arx etc).
//
bool ADESK_STDCALL acrxAppIsLoaded(const ACHAR  *pAppName);

// Return a const string containing the product name and the product version
// to use in writing to the Registry
// e.g Software\Autodesk\AutoCAD\R14.0
//
const ACHAR * acrxProductKey();

// Return a const string containing the ObjectDBX Registry root,
// e.g. Software\Autodesk\ObjectDBX\R15.0
//
const ACHAR * acrxObjectDBXRegistryKey();

// Return 32 bit value containing the product locale id
//
unsigned long acrxProductLCID();

// Write an entry to the NT/WIN95 system registry for this app.
// Returns:
// AcadApp::eOk if success.
// AcadApp::eKeyExists if entry already exists and can't be over written.
// AcadApp::eRejected if the write could not be completed.
//
AcadApp::ErrorStatus acrxRegisterApp(AcadApp::LoadReasons alr,
        const ACHAR  *logicalName, bool bDwgU = false);

// Remove app entry from the NT/WIN95 system registry.
// Returns:
// AcadApp::eOk if success.
// AcadApp::eRejected if entry cannot be removed.
// AcadApp::eKeyNotFound if entry cannot be found.
//
AcadApp::ErrorStatus acrxUnregisterApp(const ACHAR  *logicalname, 
                                       bool bDwgU = false);

// return a void * representing a handle to the module that
// registered the service, NIL if service is not present.
//
// For be use in C API libraries to link up stub entry points with
// real ones.  C++ libraries can use this function as well. 
//
void * acrxGetServiceSymbolAddr(const ACHAR * serviceName, const ACHAR * symbol);

// Tell system that the service represented by serviceName string is
// present in this module.  The system registers an instance
// of AcRxService with this name, for internal use.  
//
void* acrxRegisterService(const ACHAR * serviceName);

// Return boolean indicating whether named service is registered
// and present in the system. 
//
bool acrxServiceIsRegistered(const ACHAR * serviceName);


// Unlocks an application to enable it from being unloaded in mid-session.
// The default is that applications are locked, and hence unloadable in
// mid-session. The appId argument is the Id passed in as a void* during
// the AcRx::kInitAppMsg call back when the application is loaded. Return
// of non-zero means success.
//
bool acrxUnlockApplication(void* appId);

// Returns non-zero if the specified app is locked.
//
bool acrxApplicationIsLocked(const ACHAR * modulename);

// Symmetric to acrxUnlockApplication. Locks it, and hence prevents it from
// being unloaded in mid-session. Return of non-zero means success.
//
bool acrxLockApplication(void* appId);

// acrxApplicationsIsMDIAware() 
// Retruns non-zero if application has registered itself as MDI aware during its kInitApp msg
//
bool acrxIsAppMDIAware(const ACHAR  * moduleName);

// acrxSetApplicationMDIAware() 
// Register Application as MDI aware default is NOT MDI aware
//
bool acrxRegisterAppMDIAware(void* appId);

// acrxSetApplicationNotMDIAware() 
// ARX application is NOT MDI aware this is the default.
//
bool acrxRegisterAppNotMDIAware(void* appId);


#pragma pack (pop)
#endif
