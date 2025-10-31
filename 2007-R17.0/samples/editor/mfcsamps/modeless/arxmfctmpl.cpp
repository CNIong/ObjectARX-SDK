//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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
