// Project.cpp : Initialization functions
#include "StdAfx.h"
#include "StdArx.h"
#include "resource.h"

HINSTANCE _hdllInstance =NULL ;

// This command registers an ARX command.
void AddCommand(const char* cmdGroup, const char* cmdInt, const char* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal = -1);

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_MSG
void InitApplication();
void UnloadApplication();
void OnkLoadDwgMsg();
//}}AFX_ARX_MSG

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_ADDIN_FUNCS
//}}AFX_ARX_ADDIN_FUNCS

AsdkEdEmployeeReactor *pEdEmployeeReactor =NULL ;
AsdkEmployeeReactor *pEmployeeReactor =NULL ;

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
        _hdllInstance = hInstance;
	} else if (dwReason == DLL_PROCESS_DETACH) {
	}
	return TRUE;    // ok
}



/////////////////////////////////////////////////////////////////////////////
// ObjectARX EntryPoint
extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	switch (msg) {
	case AcRx::kLoadDwgMsg:
		OnkLoadDwgMsg();
		break;
	case AcRx::kInitAppMsg:
		// Comment out the following line if your
		// application should be locked into memory
		acrxDynamicLinker->unlockApplication(pkt);
		acrxDynamicLinker->registerAppMDIAware(pkt);

		AcRxObject *pSvc ;
		if ( !(pSvc =acrxServiceDictionary->at (ASDKEMPLOYEEDETAILS_DBXSERVICE)) ) {
			// Try to load the module, if it is not yet present
			if ( !acrxDynamicLinker->loadModule ("AsdkEmployeeDetails.dbx", 0) ) {
				acutPrintf ("Unable to load AsdkEmployeeDetails.dbx. Unloading this application...\n") ;
				return (AcRx::kRetError) ;
			} 
		}

		if ( !(pSvc =acrxServiceDictionary->at (ASDKEMPLOYEE_DBXSERVICE)) ) {
			// Try to load the module, if it is not yet present
			if ( !acrxDynamicLinker->loadModule ("AsdkEmployee.dbx", 0) ) {
				acutPrintf ("Unable to load AsdkEmployee.dbx. Unloading this application...\n") ;
				return (AcRx::kRetError) ;
			} 
		}

		InitApplication();
		break;
	case AcRx::kUnloadAppMsg:
		UnloadApplication();
		break;
	}
	return AcRx::kRetOK;
}


// Init this application. Register your
// commands, reactors...
void InitApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_INIT
	AddCommand("ASDK", "MYINPUT", "MYINPUT", ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdkmyinput);
	AddCommand("ASDK", "MYSELECT", "MYSELECT", ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdkmyselect);
	AddCommand("ASDK", "CREATE", "CREATE", ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdkcreate);
	AddCommand("ASDK", "SETLAYER", "SETLAYER", ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdksetlayer);
	AddCommand("ASDK", "ADDENTRY", "ADDENTRY", ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdkaddentry);
	AddCommand("ASDK", "REMOVEENTRY", "REMOVEENTRY", ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdkremoveentry);
	AddCommand("ASDK", "LISTENTRIES", "LISTENTRIES", ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET | ACRX_CMD_NOINTERNALLOCK, asdklistentries);
	AddCommand("ASDK", "ADDDETAIL", "ADDDETAIL", ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdkadddetail);
	AddCommand("ASDK", "REMOVEDETAIL", "REMOVEDETAIL", ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdkremovedetail);
	AddCommand("ASDK", "LISTDETAILS", "LISTDETAILS", ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdklistdetails);
	AddCommand("ASDK", "CREATEEMPLOYEE", "CREATEEMPLOYEE", ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdkcreateemployee);
	//}}AFX_ARX_INIT

	// TODO: add your initialization functions

	pEdEmployeeReactor =new AsdkEdEmployeeReactor (true) ;

	pEmployeeReactor = new AsdkEmployeeReactor ;

}

// Unload this application. Unregister all objects
// registered in InitApplication.
void UnloadApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_EXIT
	acedRegCmds->removeGroup("ASDK");
	//}}AFX_ARX_EXIT

	// TODO: clean up your application
	detachAllEmployeeReactors () ;
	delete pEmployeeReactor ;

	delete pEdEmployeeReactor ;

}

// This functions registers an ARX command.
// It can be used to read the localized command name
// from a string table stored in the resources.
void AddCommand(const char* cmdGroup, const char* cmdInt, const char* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal)
{
	char cmdLocRes[65];

	// If idLocal is not -1, it's treated as an ID for
	// a string stored in the resources.
	if (idLocal != -1) {

		// Load strings from the string table and register the command.
		::LoadString(_hdllInstance, idLocal, cmdLocRes, 64);
		acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLocRes, cmdFlags, cmdProc);

	} else
		// idLocal is -1, so the 'hard coded'
		// localized function name is used.
		acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLoc, cmdFlags, cmdProc);
}
// Entry point message handler function
void OnkLoadDwgMsg()
{
	// TODO: Implement this message handler

	new AsdkDbEmployeeReactor (true, curDoc ()) ;
}

