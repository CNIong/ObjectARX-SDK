// (C) Copyright 1993-2002 by Autodesk, Inc.
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

//////////////////////////////////////////////////////////////
//
// Includes
//
//////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "CurveText.h"
#include "utils.h"

//////////////////////////////////////////////////////////////
//
// Declarations
//
//////////////////////////////////////////////////////////////
extern "C" _declspec(dllexport) AcRx::AppRetCode acrxEntryPoint( AcRx::AppMsgCode msg, void* pkt);
HINSTANCE _hdllInstance = NULL;

#define CURVETEXT_DBX_SERVICE "CURVETEXT_OBJECT_SERVICE"


//////////////////////////////////////////////////////////////
// Global values are stored in a struct
struct GLOBALS global;

//////////////////////////////////////////////////////////////
//
// Rx interface
//
//////////////////////////////////////////////////////////////

void initApp()
{
	AsdkCurveText::rxInit();
	acrxBuildClassHierarchy();
}


void unloadApp()
{
    deleteAcRxClass(AsdkCurveText::desc());
}


//////////////////////////////////////////////////////////////
//
// Entry point
//
//////////////////////////////////////////////////////////////

extern "C" AcRx::AppRetCode acrxEntryPoint( AcRx::AppMsgCode msg, void* pkt)
{
    static void *pSvc=NULL, *moduleHandle=NULL;

	switch( msg )
	{
		case AcRx::kInitAppMsg:
			acrxUnlockApplication(pkt);
			acrxRegisterAppMDIAware(pkt);
			initApp();
			updateRegistry();
		break;
		case AcRx::kUnloadAppMsg:
			unloadApp(); 
		break;
		default:
		break;
	}
	return AcRx::kRetOK;
}


//////////////////////////////////////////////////////////////
//
// MFC Initialization
//
//////////////////////////////////////////////////////////////
extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_hdllInstance =  hInstance;         
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
	}
	return 1;
}
