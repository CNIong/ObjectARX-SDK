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


// make sure we don't link with the debug libs for MFC/CRT/STL - autocad runs in
// release mode, and therefore only uses the release versions, not the debug ones

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif


#include "GripCommands.h"
#include "AcCircle.h"
#include "AcLine.h"
#include "AcRect.h"
#include "AcCircleJig.h"
#include "dbxutil.h"
#include "AcRectJig.h"
#include <tchar.h>


#define MAX_BUFFER_SIZE 133

//////////////////////////////////////////////////////////////////////////
// globals
int gRectHorizDynDimSetting = AcDbDimData::kDimEditable|
															AcDbDimData::kDimHideIfValueIsZero|
															AcDbDimData::kDimFocal;
int gRectVertDynDimSetting =	AcDbDimData::kDimEditable|
															AcDbDimData::kDimHideIfValueIsZero|
															AcDbDimData::kDimFocal;
int gCircleDynDimSetting=		AcDbDimData::kDimEditable|
															AcDbDimData::kDimHideIfValueIsZero|
															AcDbDimData::kDimFocal|
															AcDbDimData::kDimRadius;

//////////////////////////////////////////////////////////////////////////
static int SetDynDimModesFor(const TCHAR *command, const TCHAR *dim, int &flag);
//////////////////////////////////////////////////////////////////////////

AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	switch (msg)
	{
	case AcRx::kInitAppMsg :
		acrxDynamicLinker->unlockApplication(pkt);
		initApp();
		acrxDynamicLinker->registerAppMDIAware(pkt);
		break;
	case AcRx::kUnloadAppMsg :
		unloadApp();

	}
	return AcRx::kRetOK;
}

void initApp(void)
{
	acedRegCmds->addCommand(_T("GRIPSAMPLE"), _T("CIRCLEGRIP"), _T("CIRCLEGRIP"), ACRX_CMD_MODAL, CircleGrip);
	acedRegCmds->addCommand(_T("GRIPSAMPLE"), _T("RECTJIG"), _T("RECTJIG"), ACRX_CMD_MODAL, RectangleGrip);
	acedRegCmds->addCommand(_T("GRIPSAMPLE"), _T("SETDYNDIMMODES"), _T("SETDYNDIMMODES"), ACRX_CMD_MODAL, SetDynDimModes);

	AcCircle::rxInit();
	AcLine::rxInit();
	AcRectangle::rxInit();

	acutPrintf(_T("\nGrip sample loaded..."));
	acutPrintf(_T("\nCommand - 'CIRCLEGRIP' - create a circle in a jig"));
	acutPrintf(_T("\nCommand - 'RECTJIG' - create a circle in a jig"));
	acutPrintf(_T("\nCommand - 'SETDYNDIMMODES' - allows the user to set different dynamic dimension modes for the jigs"));
}
void unloadApp(void)
{
	deleteAcRxClass(AcCircle::desc());
	deleteAcRxClass(AcLine::desc());
	deleteAcRxClass(AcRectangle::desc());
}

void CircleGrip(void)
{
	acutPrintf(_T("\nSuccessfully loaded the custom grip sample for custom circle\n"));
	Adesk::Boolean es(kFalse);

	AcCircle *pCircle = new AcCircle();
	AcCircleJig *pCicleJig = new AcCircleJig(acdbHostApplicationServices()->workingDatabase(),pCircle );

	AcDbObjectId stylentId = acdbGetDynDimStyleId();
	AcDbDimStyleTableRecord *pDimStyleTblRecord = NULL;

	es = acdbOpenObject(pDimStyleTblRecord,stylentId,AcDb::kForWrite);
	if(Acad::eOk != es)
		acutPrintf(_T("Error in opening the AcDbDimStyleTable entity"));
	AcCmColor cm;
	//cm.setColor( cm.blue() );
	//cm.setRGB(0,0,255);
	cm.setColorIndex(20);
	es =pDimStyleTblRecord->setDimclrt(cm);
	pDimStyleTblRecord->erase();
	pDimStyleTblRecord->close();	


	pCicleJig->dragIt();
	delete pCicleJig;
}

// ACRECT command main entry.
//
void RectangleGrip()
{
	AcRectangle *pRect = new AcRectangle();
	AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
	AcRectJig jig(pDb, pRect);

	if (jig.acquireDefPoints() == Acad::eOk) {
		jig.prepRect();
		jig.dragIt();
	} else {
		delete pRect;
	}
}

//////////////////////////////////////////////////////////////////////////
// allows the user to setup different dynamic dimension modes
void SetDynDimModes()
{
	acutPrintf(_T("\nThis command sets the default dynamic dimension modes for each jig in this sample..."));

	// setup modes for all the inputs
	SetDynDimModesFor(_T("RectJig"), _T("Horizontal"), gRectHorizDynDimSetting);
	SetDynDimModesFor(_T("RectJig"), _T("Vertcial"), gRectVertDynDimSetting);
	SetDynDimModesFor(_T("CircleJig"), _T("Radius"), gCircleDynDimSetting);
}
//////////////////////////////////////////////////////////////////////////
int SetDynDimModesFor(const TCHAR *command, const TCHAR *dim, int &flag)
{
	// setup the options strings for easy access
	AcArray<TSTDSTRING, AcArrayObjectCopyReallocator<TSTDSTRING>> DynDimOptionsStrings;
	DynDimOptionsStrings.append(_T(""));
	DynDimOptionsStrings.append(_T("Editable"));
	DynDimOptionsStrings.append(_T("Invisible"));
	DynDimOptionsStrings.append(_T("Focal"));
	DynDimOptionsStrings.append(_T("Hideifzero"));
	DynDimOptionsStrings.append(_T("Original"));
	DynDimOptionsStrings.append(_T("RESULTANTLength"));
	DynDimOptionsStrings.append(_T("DELTALength"));
	DynDimOptionsStrings.append(_T("RESULTANTAngle"));
	DynDimOptionsStrings.append(_T("DELTAAngle"));
	DynDimOptionsStrings.append(_T("RAdius"));
	// setup string array access values
	AcArray<int> powers;
	powers.append(0); 
	powers.append(1);
	powers.append(2);
	powers.append(4);
	powers.append(8);
	powers.append(32);
	powers.append(64);
	powers.append(128);
	powers.append(256);
	powers.append(512);
	powers.append(1024);
	int res = RTNONE;
	do 
	{
		acutPrintf(_T("\nCurrent Options for the %s(%s Dimension) are:"), command, dim);
		// print the options currently set,  
		acutPrintf(_T("\n\n%s-%s-%s-%s-%s-%s-%s-%s-%s-%s\n\n"),
			DynDimOptionsStrings[((flag & 1) ? 1:0)].c_str(),
			DynDimOptionsStrings[((flag & 2) ? 2:0)].c_str(),
			DynDimOptionsStrings[((flag & 4) ? 3:0)].c_str(),
			DynDimOptionsStrings[((flag & 8) ? 4:0)].c_str(),
			DynDimOptionsStrings[((flag & 32) ? 5:0)].c_str(),
			DynDimOptionsStrings[((flag & 64) ? 6:0)].c_str(),
			DynDimOptionsStrings[((flag & 128) ? 7:0)].c_str(),
			DynDimOptionsStrings[((flag & 256) ? 8:0)].c_str(),
			DynDimOptionsStrings[((flag & 512) ? 9:0)].c_str(),
			DynDimOptionsStrings[((flag & 1024) ? 10:0)].c_str());

		// setup the keywords required
		acedInitGet(0, _T("Editable Invisible Focal Hideifzero Original RESULTANTLength DELTALength RESULTANTAngle DELTAAngle RAdius"));
		TCHAR kword[133];
		// get the rect jig dyn settings
		res = acedGetKword(_T("\nToggle option [Editable/Invisible/Focal/Hideifzero/Original/RESULTANTLength/DELTALength/RESULTANTAngle/DELTAAngle/RAdius] <Finish> : "), kword);
		// if ok
		if (res == RTNORM)
		{
			int index = -1;
			// search for the option input in our options string
			if (DynDimOptionsStrings.find(kword, index))
			{
				// if we found it, toggle the option
				flag |= (powers[index]);
			}
		}

	}while(res == RTNORM);
	return res;
}
