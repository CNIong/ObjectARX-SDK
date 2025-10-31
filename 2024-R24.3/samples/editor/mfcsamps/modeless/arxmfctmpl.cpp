//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#include "StdAfx.h"
//
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif




/////////////////////////////////////////////////////////////////////////////
// Define the sole extension module object.
AC_IMPLEMENT_EXTENSION_MODULE(modelessDll);

/////////////////////////////////////////////////////////////////////////////
//
// Rx interface
//
/////////////////////////////////////////////////////////////////////////////

void initApp()
{
	gpDocReactor = new CDocReactor();
	acDocManager->addReactor(gpDocReactor);

	acedRegCmds->addCommand(_T("ASDK_MODELESS"), _T("MODELESS"), _T("MODELESS"), 
		ACRX_CMD_MODAL, &DisplayDialog);
	acutPrintf(_T("\nEnter \"modeless\" to open the dialog.\n") );
}

void unloadApp()
{
	DetachEdReactor();
	if(gpDocReactor)
	{
		acDocManager->removeReactor(gpDocReactor);
		delete gpDocReactor;
	}
	endDlg();
	acedRegCmds->removeGroup (_T("ASDK_MODELESS"));
}
/////////////////////////////////////////////////////////////////////////////
//
// Entry points
//
/////////////////////////////////////////////////////////////////////////////

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
        modelessDll.AttachInstance(hInstance);
	else if (dwReason == DLL_PROCESS_DETACH)
        modelessDll.DetachInstance();  
	
	return 1;   // ok
}


extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* p)
{
	switch( msg ) 
	{
	case AcRx::kInitAppMsg: 
		acrxDynamicLinker->unlockApplication(p);
		acrxRegisterAppMDIAware(p);
		initApp(); 
		break;
	case AcRx::kUnloadDwgMsg:
		detachDbReactor(CUR_DB);
		break;
	case AcRx::kUnloadAppMsg: 
		unloadApp(); 
		break;
	default:
		break;
	}
	return AcRx::kRetOK;
}
