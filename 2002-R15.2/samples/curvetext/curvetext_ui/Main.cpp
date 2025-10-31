// (C) Copyright 1993-1998 by Autodesk, Inc.
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

#include "CurvetextHelper.h"
#include "utils.h"
#include "resourcehelper.h"
#include "ContextMenu.h"
//////////////////////////////////////////////////////////////
//
// Declarations
//
//////////////////////////////////////////////////////////////
extern "C" _declspec(dllexport) AcRx::AppRetCode acrxEntryPoint( AcRx::AppMsgCode msg, void* pkt);
HINSTANCE _hdllInstance = NULL;

//////////////////////////////////////////////////////////////
// Global values are stored in a struct
struct GLOBALS global;
curvetextContextMenu *pCurvetextContextMenu;
curveContextMenu *pCurveContextMenu;


//////////////////////////////////////////////////////////////
//
// Rx interface
//
//////////////////////////////////////////////////////////////

void initApp()
{
    acedRegCmds->addCommand("CURVETEXT", "ADCG_ct", "ct",
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							curveTextMulti);
    acedRegCmds->addCommand("CURVETEXT", "ADCG_ssp", "sp",
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							setStart);
    acedRegCmds->addCommand("CURVETEXT", "ADCG_sep", "ep",
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							setEnd);
    acedRegCmds->addCommand("CURVETEXT", "ADCG_reverse", "reverse",
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							reverse);
    acedRegCmds->addCommand("CURVETEXT", "ADCG_showCurve", "sc",
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							ShowCurve);
    acedRegCmds->addCommand("CURVETEXT", "ADCG_hideCurve", "hc",
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							HideCurve);
    acedRegCmds->addCommand("CURVETEXT", "ADCG_ShowText", "st",
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							ShowText);
    acedRegCmds->addCommand("CURVETEXT", "ADCG_HideText", "ht",
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							HideText);
    acedRegCmds->addCommand("CURVETEXT", "ADCG_fit", "fit",
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							fit);
    acedRegCmds->addCommand("CURVETEXT", "ADCG_noFit", "nf",
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							DoNotFit);
    acedRegCmds->addCommand("CURVETEXT", "ADCG_repeatText", "rt",
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							RepeatText);
    acedRegCmds->addCommand("CURVETEXT", "ADCG_noTextRepetition", "ntr",
							ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
							DoNotRepeatText);
	setDefaultValues();
}


void unloadApp()
{
	acedRegCmds->removeGroup( "CURVETEXT" );
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
			if (!acrxLoadModule("curveText.dbx", false))
					return AcRx::kRetError;
			acrxDynamicLinker->unlockApplication(pkt);
			acrxRegisterAppMDIAware(pkt);
			initApp();
			updateRegistry();
			pCurvetextContextMenu = new curvetextContextMenu;
			pCurveContextMenu = new curveContextMenu;
			acedAddObjectContextMenu(AcDbCurve::desc(), pCurveContextMenu, pkt);
			acedAddObjectContextMenu(AdcgCurveText::desc(), pCurvetextContextMenu, pkt);
		break;
		case AcRx::kUnloadAppMsg:
			unloadApp(); 
			acedRemoveObjectContextMenu(AcDbCurve::desc(), pCurveContextMenu);
			acedRemoveObjectContextMenu(AdcgCurveText::desc(), pCurvetextContextMenu);
			acrxUnloadModule("curveText.dbx");
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
		// CTemporaryResourceOverride initialization
		CTemporaryResourceOverride::SetDefaultResource(_hdllInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
	}
	return 1;
}

