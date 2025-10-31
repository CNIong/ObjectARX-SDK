//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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

#include "stdafx.h"
#include "ArxDbgCmdGraphicsContainer.h"
#include "ArxDbgDbGraphicsContainer.h"
#include "ArxDbgUtils.h"
#include "ArxDbgKeywordArray.h"
#include "ArxDbgApp.h"
#include "ArxDbgUiDlgGenericDefId.h"

/****************************************************************************
**
**  ArxDbgCmdGraphicsContainer::registerCommandLineFunctions
**
**  **jma
**
*************************************/

void
ArxDbgCmdGraphicsContainer::registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname)
{
	cmdStack->addCommand(appname, _T("ArxDbgGraphicsContainer"),       _T("GraphicsContainer"),       ACRX_CMD_MODAL, &cmdLineMain);
	cmdStack->addCommand(appname, _T("ArxDbgGraphicsContainerAdd"),    _T("GraphicsContainerAdd"),    ACRX_CMD_MODAL, &add);
	cmdStack->addCommand(appname, _T("ArxDbgGraphicsContainerModify"), _T("GraphicsContainerModify"), ACRX_CMD_MODAL, &modify);
}

/****************************************************************************
**
**  ArxDbgCmdGraphicsContainer::cmdLineMain
**
**  **jma
**
*************************************/

void
ArxDbgCmdGraphicsContainer::cmdLineMain()
{
		// ArxDbgKeyword array allows us to use Global and Local keywords (i.e., English
		// and another language) without the need to worry about how it was picked.  In
		// this case, we haven't translated anything, so the keywords are the same.
		// see ArxDbgKeywordArray for more details.
	ArxDbgKeywordArray kwords(ArxDbgApp::getApp()->dllInstance());
    kwords.append(_T("Add"),    _T("Add"));
    kwords.append(_T("Modify"), _T("Modify"));

    CString optionsStr, kwordStr;
    kwords.makeOptionsList(optionsStr);
    kwords.makeKeywordList(kwordStr);

	CString promptStr;
    promptStr.Format(_T("Graphics Container options %s"), optionsStr);

    ArxDbgUiPrKeyWord prCmd(promptStr, kwordStr);
    if (prCmd.go() != ArxDbgUiPrBase::kOk)
        return;

    int keywordIndex;
    if (kwords.find(prCmd.keyWordPicked(), keywordIndex) == false) {
        ASSERT(0);
        return;
    }

    if (keywordIndex == 0)
        add();
    else if (keywordIndex == 1)
        modify();
    else {
        ASSERT(0);
        return;
    }
}

/****************************************************************************
**
**  ArxDbgCmdGraphicsContainer::getContainers
**
**  **jma
**
*************************************/

bool
ArxDbgCmdGraphicsContainer::getContainers(AcDbObjectId& blkDefId, CString& dwgName)
{
	if (!getBlockDef(blkDefId))
		return false;

	bool answer;
	if (ArxDbgUtils::yesNoPromptDef(_T("\nUse external drawing? "), answer,
									!dwgName.IsEmpty()) != ArxDbgUiPrBase::kOk)
		return false;

	if (answer) {
		Acad::ErrorStatus es;
		es = ArxDbgUtils::getFileNameForRead(_T("Drawing To Preview"),
						dwgName, _T("dwg"), dwgName, false, false);
		if (es != Acad::eOk)
			return false;
	}
	else
		dwgName.Empty();	// NULL this out

	return true;
}

/****************************************************************************
**
**  ArxDbgCmdGraphicsContainer::add
**
**  **jma
**
*************************************/

void
ArxDbgCmdGraphicsContainer::add()
{
	AcDbObjectId blkDefId;
	CString dwgName;

	if (!getContainers(blkDefId, dwgName))
		return;

    ArxDbgUiPrPoint prPt(_T("Location"), NULL);
    if (prPt.go() != ArxDbgUiPrBase::kOk)
        return;
	
	ArxDbgDbGraphicsContainer* gCont = new ArxDbgDbGraphicsContainer;
	gCont->setLocation(prPt.value());
	gCont->setBlockId(blkDefId);
	gCont->setExtDwg(dwgName);

	ArxDbgUtils::addToCurrentSpaceAndClose(gCont, acdbHostApplicationServices()->workingDatabase());
}

/****************************************************************************
**
**  ArxDbgCmdGraphicsContainer::modify
**
**  **jma
**
*************************************/

void
ArxDbgCmdGraphicsContainer::modify()
{
	ArxDbgUiPrEntity prEnt(_T("Select Graphics Container to modify"), NULL);
	prEnt.addAllowedClass(ArxDbgDbGraphicsContainer::desc());
	prEnt.setFilterLockedLayers(true);

	if (prEnt.go() != ArxDbgUiPrBase::kOk)
		return;

	ArxDbgDbGraphicsContainer* gCont;
	Acad::ErrorStatus es = acdbOpenObject(gCont, prEnt.objectId(), AcDb::kForWrite);
	if (es == Acad::eOk) {
		AcDbObjectId blkDefId = gCont->blockId();	// set default
		CString dwgName = gCont->extDwg();

		if (getContainers(blkDefId, dwgName)) {
			gCont->setBlockId(blkDefId);
			gCont->setExtDwg(dwgName);
		}

		gCont->close();
	}
	else
		ArxDbgUtils::rxErrorMsg(es);
}

/****************************************************************************
**
**  ArxDbgCmdGraphicsContainer::getBlockDef
**
**  **jma
**
*************************************/

bool
ArxDbgCmdGraphicsContainer::getBlockDef(AcDbObjectId& blkDefId)
{
	SdStrObjIdList blockIds;

	Acad::ErrorStatus es;
	es = ArxDbgUtils::collectBlockIds(blockIds, true, true, true,
				acdbHostApplicationServices()->workingDatabase());
	if (es != Acad::eOk) {
		ArxDbgUtils::rxErrorMsg(es);
		return false;
	}

	ArxDbgUiDlgGenericDefId dbox(acedGetAcadDwgView(),
									blockIds, blkDefId, true);	// allow none
	dbox.setDboxTitle(_T("Block Definitions"));

	if (dbox.DoModal() == IDOK) {
		blkDefId = dbox.getSelectedId();
		return true;
	}

	return false;
}

