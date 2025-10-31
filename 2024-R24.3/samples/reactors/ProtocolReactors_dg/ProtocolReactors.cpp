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
// ProtocolReactors.cpp : Defines the initialization routines for the DLL.
//
#include "stdafx.h"
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "adscodes.h"
#include "rxdefs.h"
#include "rxregsvc.h"
#include "accmd.h"
#include "acedads.h"
#include "dbmain.h"
#include "dbents.h"
#include "AcString.h"

#include "dbpl.h"
#include "dbapserv.h"
#include "AsdkInsertionPoints.h"
#include "rxprotevnt.h"
#include "dbobjptr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

AsdkInsertionPoints*	pPts = NULL;

void dynBlkTest();
void dynBlkRemove();
void InitApp();
void addInsertionPoints();

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
                pPts = NULL;
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
