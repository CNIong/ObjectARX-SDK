//
//
/// (C) Copyright 2003 by Autodesk, Inc. 
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

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.h
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "plotapidialog.h"

CPlotApiDialog *pPlotDialog=NULL;
AsdkPlotReactor *pPlotReactor;
//-----------------------------------------------------------------------------
#define szRDS _RXST("asdk")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CAsdkPlotApiDialogApp : public AcRxArxApp {

public:
	CAsdkPlotApiDialogApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) 
	{
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		if(!pPlotReactor)
		{
			// Always create and add the plot reactor
			pPlotReactor=new AsdkPlotReactor;
			acplPlotReactorMgrPtr()->addReactor(pPlotReactor);
		}
		return (retCode);
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) 
	{
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;
		DestroyReactor();// When exiting, make sure this is destroyed.
		return (retCode) ;
	}

	virtual void RegisterServerComponents ()
	{
	}

	static void asdkNeoPlotTestPLOTAPI(void)
	{
		// The reactor is only for background plot notifications, so we destroy
		// it when we run this command in the UI.
		DestroyReactor();
		
		// Create the custom modeless PLOT UI Dialog here.
		pPlotDialog=new CPlotApiDialog;
		pPlotDialog->Create(IDD_APIPLOTDIALOG);
		pPlotDialog->ShowWindow(SW_SHOW);
	}

	static void DestroyReactor(void)
	{
		// Remove the reactor...
		if(pPlotReactor)
		{
			acplPlotReactorMgrPtr()->removeReactor(pPlotReactor);
			delete pPlotReactor;
			pPlotReactor=NULL;
		}
	}
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CAsdkPlotApiDialogApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CAsdkPlotApiDialogApp, asdkNeoPlotTest, PLOTAPI, PLOTAPI, ACRX_CMD_TRANSPARENT | ACRX_CMD_MODAL, NULL)
