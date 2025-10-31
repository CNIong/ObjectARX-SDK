// (C) Copyright 1993-2006 by Autodesk, Inc.
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
#include "StdAfx.h"
//////////////////////////////////////////////////////////////
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "afxdllx.h"

#include "CurvetextHelper.h"
#include "utils.h"
#include "ContextMenu.h"


//////////////////////////////////////////////////////////////
//
// Declarations
//
//////////////////////////////////////////////////////////////
extern "C" _declspec(dllexport) AcRx::AppRetCode acrxEntryPoint( AcRx::AppMsgCode msg, void* pkt);

// Define the sole extension module object.
AC_IMPLEMENT_EXTENSION_MODULE(theArxDLL);

HINSTANCE _hdllInstance = NULL;

//////////////////////////////////////////////////////////////
// Global values are stored in a struct
curvetextContextMenu *pCurvetextContextMenu;
curveContextMenu *pCurveContextMenu;


//////////////////////////////////////////////////////////////
//
// Rx interface
//
//////////////////////////////////////////////////////////////

void initApp()
{
    acedRegCmds->addCommand(_T("ASDK_CURVETEXT"), _T("curvetext"), _T("curvetext"),
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							curveTextMulti);
    acedRegCmds->addCommand(_T("ASDK_CURVETEXT"), _T("ssp"), _T("sp"),
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							setStart);
    acedRegCmds->addCommand(_T("ASDK_CURVETEXT"), _T("sep"), _T("ep"),
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							setEnd);
    acedRegCmds->addCommand(_T("ASDK_CURVETEXT"), _T("reverse"), _T("reverse"),
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							reverse);
    acedRegCmds->addCommand(_T("ASDK_CURVETEXT"), _T("showCurve"), _T("sc"),
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							ShowCurve);
    acedRegCmds->addCommand(_T("ASDK_CURVETEXT"), _T("hideCurve"), _T("hc"),
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							HideCurve);
    acedRegCmds->addCommand(_T("ASDK_CURVETEXT"), _T("ShowText"), _T("st"),
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							ShowText);
    acedRegCmds->addCommand(_T("ASDK_CURVETEXT"), _T("HideText"), _T("ht"),
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							HideText);
    acedRegCmds->addCommand(_T("ASDK_CURVETEXT"), _T("fit"), _T("fit"),
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							fit);
    acedRegCmds->addCommand(_T("ASDK_CURVETEXT"), _T("noFit"), _T("nf"),
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							DoNotFit);
    acedRegCmds->addCommand(_T("ASDK_CURVETEXT"), _T("repeatText"), _T("rt"),
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							RepeatText);
    acedRegCmds->addCommand(_T("ASDK_CURVETEXT"), _T("noTextRepetition"), _T("ntr"),
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							DoNotRepeatText);
}


void unloadApp()
{
	acedRegCmds->removeGroup( _T("ASDK_CURVETEXT") );
}




//////////////////////////////////////////////////////////////
//
// Entry point
//
//////////////////////////////////////////////////////////////

extern "C" AcRx::AppRetCode acrxEntryPoint( AcRx::AppMsgCode msg, void* pkt)
{
	switch( msg )
	{
		case AcRx::kInitAppMsg:
			if (!acrxLoadModule(_T("AsdkCurveText.dbx"), false))
					return AcRx::kRetError;
			acrxDynamicLinker->unlockApplication(pkt);
			acrxRegisterAppMDIAware(pkt);
			initApp();
			updateRegistry();
			pCurvetextContextMenu = new curvetextContextMenu;
			pCurveContextMenu = new curveContextMenu;
			acedAddObjectContextMenu(AcDbCurve::desc(), pCurveContextMenu, pkt);
			acedAddObjectContextMenu(AsdkCurveText::desc(), pCurvetextContextMenu, pkt);
		break;
		case AcRx::kUnloadAppMsg:
			unloadApp(); 
			acedRemoveObjectContextMenu(AcDbCurve::desc(), pCurveContextMenu);
			acedRemoveObjectContextMenu(AsdkCurveText::desc(), pCurvetextContextMenu);
			acrxUnloadModule(_T("AsdkCurveText.dbx"));
			delete pCurveContextMenu;
			delete pCurvetextContextMenu;
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
	// UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_hdllInstance =  hInstance;
		theArxDLL.AttachInstance(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		theArxDLL.DetachInstance();
	}
	return 1;
}

