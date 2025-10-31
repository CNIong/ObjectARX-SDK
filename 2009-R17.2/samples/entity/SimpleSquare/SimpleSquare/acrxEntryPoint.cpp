//
// (C) Copyright 2006-2007 by Autodesk, Inc. 
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


//-----------------------------------------------------------------------------
//----- acrxEntryPoint.h
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include <mgdinterop.h>
#include <gcroot.h>

#include "Asdksimplesquare.h"

//-----------------------------------------------------------------------------
#define szRDS _RXST("ASDK")


// Note:  To create a managed wrapper that can be *instantiated* independently of YOUR code, you need only do two things:

// 1) Declare the AcMgObjectFactoryBase as shown directly below

// 2) Create the factory array of these objects as shown below in the 'Step 2' code within CSimpleSquareApp::RegisterManagedWrapperLink()

static AcMgObjectFactoryBase __nogc * __nogc *g_PEs = NULL;
//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CSimpleSquareApp : public AcRxDbxApp {

public:
	CSimpleSquareApp () : AcRxDbxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxDbxApp::On_kInitAppMsg (pkt) ;

		RegisterManagedWrapperLink(); // Setup the managed-unmanaged connection.
		RegisterDbxApp(); // Setup demand-loading for this object enabler module.

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxDbxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here

		return (retCode) ;
	}

	// Step 2:

	// create a new object factory array.  This code will link your wrapper to the unmanaged AsdkSimpleSquare object so that
	// AutoCAD can instantiate the wrapper when code (independent or otherwise) encounters your object in an AutoCAD 
	// database and wants to interrogate it.

private:

	void RegisterManagedWrapperLink()
	{
			static AcMgObjectFactoryBase* PEs[] = 
			{
				new AcMgObjectFactory<Autodesk::SimpleSquare::MgSimpleSquare,AsdkSimpleSquare>(), 
				// end the array with a NULL
				NULL
			};
			g_PEs = PEs;
	}

	// Here is the code which will register this object enabler module in the registry so that
	// when a drawing is loaded with one of these square objects, it will know where to find
	// this module...
	void RegisterDbxApp()
	{
		// Fill the AppInfo structure with our demand loading details.
		AcadAppInfo appInfo;
		appInfo.setAppName(_T("ASDKSimpleSquare"));// AppName
		// Get the DBX file path.
		HMODULE hModule=GetModuleHandle(_T("ASDKSimpleSquare.dll"));
		TCHAR modulePath[512];
		DWORD pathLength = GetModuleFileName(hModule, modulePath, 512);
		if (pathLength)
			appInfo.setModuleName(modulePath); // Set the DBX file path.
		appInfo.setAppDesc(_T("DBX module demonstrating exposure to .NET through managed C++"));// Description
		appInfo.setLoadReason(
			AcadApp::LoadReasons(// Specify when we want this app to load.
			AcadApp::kOnProxyDetection |
			AcadApp::kOnLoadRequest));
		
		appInfo.writeToRegistry(true,true);// Write the AppInfo to the registry, include the DBX registry section.
	}

	virtual void RegisterServerComponents () 
	{
	}
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CSimpleSquareApp)

