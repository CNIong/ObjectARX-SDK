// Copyright 2004-2006 by Autodesk, Inc.
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

// ProtocolReactors.cpp : Defines the initialization routines for the DLL.
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <afxdllx.h>
#include "dbpl.h"
#include "dbapserv.h"
#include "AsdkInsertionPoints.h"
#include "rxprotevnt.h"
#include "dbobjptr.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

AsdkInsertionPoints*	pPts = NULL;
static AFX_EXTENSION_MODULE ProtocolReactorsDLL = { NULL, NULL };

void dynBlkTest();
void dynBlkRemove();
void InitApp();
void addInsertionPoints();

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("ProtocolReactors.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(ProtocolReactorsDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(ProtocolReactorsDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("ProtocolReactors.DLL Terminating!\n");

		// Terminate the library before destructors are called
		AfxTermExtensionModule(ProtocolReactorsDLL);
	}
	return 1;   // ok
}

void createBlock()
{
	AcDbBlockTableRecord* pBTR = new AcDbBlockTableRecord();
	pBTR->setName(DYNBLKSAMP_BLOCKNAME);
	AcDbSymbolTable* pBT = NULL;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBT, AcDb::kForWrite);
	pBT->add(pBTR);
	pBT->close();	
	
	
	AcGePoint3d pt1(0.0, 0.0, 0.0);
	AcGePoint3d pt2(2.0, 0.0, 0.0);
	AcDbLine* pLine = new AcDbLine(pt1, pt2);
	pBTR->appendAcDbEntity(pLine);
	pLine->close();

	pt1 = pt2;
	pt2.y = 2.0;
	pLine = new AcDbLine(pt1, pt2);
	pBTR->appendAcDbEntity(pLine);
	pLine->close();

	pt1 = pt2;
	pt2.x = 0.0;
	pLine = new AcDbLine(pt1, pt2);
	pBTR->appendAcDbEntity(pLine);
	pLine->close();

	pt1 = pt2;
	pt2.y = 0.0;
	pLine = new AcDbLine(pt1, pt2);
	pBTR->appendAcDbEntity(pLine);
	pLine->close();
	
	pBTR->close();
}

extern "C"
AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	switch(msg)
	{
        case AcRx::kInitAppMsg:
			acrxUnlockApplication(pkt);
			acrxRegisterAppMDIAware(pkt);
			InitApp();
            break;
        case AcRx::kUnloadAppMsg:
			acedRegCmds->removeGroup(_T("DYNBLKAPP"));
			if (pPts)
			{
				ACRX_PROTOCOL_REACTOR_LIST_AT(AcDbBlockTableRecord::desc(), 
					AsdkInsertionPoints::desc())->removeReactor(pPts);
				delete pPts;
			}
            break;
        default:
            break;
    }
	return AcRx::kRetOK;
}

void InitApp()
{
	acedRegCmds->addCommand(_T("DYNBLKAPP"), _T("BLKINSPTS"), _T("blkinspts"), ACRX_CMD_MODAL,
		addInsertionPoints);
	createBlock();
}


void addInsertionPoints()
{
	if (!pPts)
	{
		pPts = new AsdkInsertionPoints();
		ACRX_PROTOCOL_REACTOR_LIST_AT(AcDbBlockTableRecord::desc(),
			AsdkInsertionPoints::desc())->addReactor(pPts);
	}
}
