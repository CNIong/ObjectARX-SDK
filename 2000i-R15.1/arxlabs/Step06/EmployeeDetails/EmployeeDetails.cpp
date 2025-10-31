// EmployeeDetails.cpp : Initialization functions
#include "StdAfx.h"
#include "StdArx.h"
#include "resource.h"

HINSTANCE _hdllInstance =NULL ;

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_MSG
void InitApplication();
void UnloadApplication();
//}}AFX_ARX_MSG

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_ADDIN_FUNCS
//}}AFX_ARX_ADDIN_FUNCS

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
	case AcRx::kInitAppMsg:
		// Comment out the following line if your
		// application should be locked into memory
		acrxDynamicLinker->unlockApplication(pkt);
		acrxDynamicLinker->registerAppMDIAware(pkt);
		InitApplication();
		break;
	case AcRx::kUnloadAppMsg:
		UnloadApplication();
		break;
	}
	return AcRx::kRetOK;
}


// Init this application. Register your
// reactors, custom classes...
void InitApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_INIT
	AsdkEmployeeDetails::rxInit();
	acrxBuildClassHierarchy();
	acrxRegisterService(ASDKEMPLOYEEDETAILS_DBXSERVICE);
	//}}AFX_ARX_INIT

	// TODO: add your initialization functions

}

// Unload this application. Unregister all objects
// registered in InitApplication.
void UnloadApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_EXIT
	deleteAcRxClass(AsdkEmployeeDetails::desc());
	delete acrxServiceDictionary->remove(ASDKEMPLOYEEDETAILS_DBXSERVICE);
	//}}AFX_ARX_EXIT

	// TODO: clean up your application
}

