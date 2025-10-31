//
// (C) Copyright 2001 by Autodesk, Inc. 
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
// DblClick.cpp : Initialization functions

#include "StdAfx.h"
#include "StdArx.h"
#include "resource.h"
#include <afxdllx.h>
#include "dbspline.h"
#include "AcDblClkEdit.h"
#include "AcDbDoubleClickEditSpline.h"
#include "AcDbDoubleClickEditPline.h"
#include "AcDbDoubleClickCircle.h"
#include "dbpl.h"
#include "dbents.h"


HINSTANCE _hdllInstance =NULL ;

// This command registers an ARX command.
void AddCommand(const char* cmdGroup, const char* cmdInt, const char* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal = -1);

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_MSG
void InitApplication();
void UnloadApplication();
//}}AFX_ARX_MSG

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_ADDIN_FUNCS
//}}AFX_ARX_ADDIN_FUNCS


////////////////////////////////////////////////////////////////////////////
//
// Define the sole extension module object.
AC_IMPLEMENT_EXTENSION_MODULE(DblClickDLL);

// Now you can use the CAcModuleRecourceOverride class in
// your application to switch to the correct resource instance.
// Please see the ObjectARX Documentation for more details

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
        _hdllInstance = hInstance;
		// Extension DLL one time initialization
		DblClickDLL.AttachInstance(hInstance);
		InitAcUiDLL();
	} else if (dwReason == DLL_PROCESS_DETACH) {
		// Terminate the library before destructors are called
		DblClickDLL.DetachInstance();

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
// commands, reactors...
void InitApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_INIT
	//}}AFX_ARX_INIT

	// Load the Double Click Arx Module...
	if(!acrxDynamicLinker->loadModule(/*MSG0*/"ACDBLCLKEDITPE.ARX",Adesk::kFalse)) {
		AfxMessageBox("'ACDBLCLKEDITPE.ARX' Load Failed");
		return ;
	}

	// Initialize Double Click Editing
	AcDbDoubleClickEdit::rxInit();
	
	// Initialize for Spline...
	AcDbDoubleClickEditSpline *pSplineEdit=new AcDbDoubleClickEditSpline;
	AcDbSpline::desc()->addX(AcDbDoubleClickEdit::desc(),pSplineEdit);

	// Initialize for Pline...
	AcDbDoubleClickEditPline *pPlineEdit=new AcDbDoubleClickEditPline;
	AcDbPolyline::desc()->addX(AcDbDoubleClickEdit::desc(),pPlineEdit);
		
		
	// Intialize for Circle...
	AcDbDoubleClickCircle *pCircleEdit=new AcDbDoubleClickCircle;
	AcDbCircle::desc()->addX(AcDbDoubleClickEdit::desc(),pCircleEdit);
	
	// Message for Sample Usage
	AfxMessageBox("Double-Click Editing API Sample:\nDouble Click 'Pline' and 'Spline' Entities to Add Vertexes,\nDouble Click 'Circle' to Cycle Color.");
	
}

// Unload this application. Unregister all objects
// registered in InitApplication.
void UnloadApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_EXIT
	//}}AFX_ARX_EXIT

	// Uninitialize the double-click editing feature
	// for each entity type
	AcDbSpline::desc()->delX(AcDbDoubleClickEdit::desc());
	AcDbPolyline::desc()->delX(AcDbDoubleClickEdit::desc());
	AcDbCircle::desc()->delX(AcDbDoubleClickEdit::desc());
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
