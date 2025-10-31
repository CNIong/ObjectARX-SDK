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
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxDbgCmdSnoop.h"
#include "ArxDbgUiTdmEntities.h"
#include "ArxDbgUiTdmEditor.h"
#include "ArxDbgUiTdmDatabase.h"
#include "ArxDbgUiDlgServiceDict.h"
#include "ArxDbgUiDlgSysRegistry.h"
#include "ArxDbgKeywordArray.h"
#include "ArxDbgUiPrompts.h"
#include "ArxDbgSelSet.h"
#include "ArxDbgApp.h"
#include "ArxDbgUtils.h"



/****************************************************************************
**
**  ArxDbgCmdSnoop::registerCommandLineFunctions
**
**  **jma
**
*************************************/

void
ArxDbgCmdSnoop::registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname)
{
	cmdStack->addCommand(appname, _T("ArxDbgSnoop"),			_T("Snoop"),            ACRX_CMD_MODAL, &cmdLineMain);
	cmdStack->addCommand(appname, _T("ArxDbgSnoopEnts"),        _T("SnoopEnts"),        ACRX_CMD_MODAL, &entities);
	cmdStack->addCommand(appname, _T("ArxDbgSnoopNents"),       _T("SnoopNents"),       ACRX_CMD_MODAL, &entitiesNested);
	cmdStack->addCommand(appname, _T("ArxDbgSnoopEd"),          _T("SnoopEd"),          ACRX_CMD_MODAL, &editor);
	cmdStack->addCommand(appname, _T("ArxDbgSnoopDb"),          _T("SnoopDb"),          ACRX_CMD_MODAL, &database);
	cmdStack->addCommand(appname, _T("ArxDbgSnoopServices"),    _T("SnoopServices"),    ACRX_CMD_MODAL, &services);
	cmdStack->addCommand(appname, _T("ArxDbgSnoopSysRegistry"), _T("SnoopSysRegistry"), ACRX_CMD_MODAL, &sysRegistry);
}

/****************************************************************************
**
**  ArxDbgCmdSnoop::cmdLineMain
**
**  **jma
**
*************************************/

void
ArxDbgCmdSnoop::cmdLineMain()
{
		// ArxDbgKeyword array allows us to use Global and Local keywords (i.e., English
		// and another language) without the need to worry about how it was picked.  In
		// this case, we haven't translated anything, so the keywords are the same.
		// see ArxDbgKeywordArray for more details.
	ArxDbgKeywordArray kwords(ArxDbgApp::getApp()->dllInstance());
    kwords.append(_T("ENtities"), _T("ENtities"));
    kwords.append(_T("Nested"),   _T("Nested"), _T("Nested entities"));
    kwords.append(_T("EDitor"),   _T("EDitor"));
	kwords.append(_T("Database"), _T("Database"));
	kwords.append(_T("Services"), _T("Services"));
	kwords.append(_T("Registry"), _T("Registry"), _T("system Registry"));

    CString optionsStr, kwordStr;
    kwords.makeOptionsList(optionsStr);
    kwords.makeKeywordList(kwordStr);

	CString promptStr;
    promptStr.Format(_T("Snoop options %s"), optionsStr);

    ArxDbgUiPrKeyWord prCmd(promptStr, kwordStr);
    if (prCmd.go() != ArxDbgUiPrBase::kOk)
        return;

    int keywordIndex;
    if (kwords.find(prCmd.keyWordPicked(), keywordIndex) == false) {
        ASSERT(0);
        return;
    }

    if (keywordIndex == 0)
        entities();
    else if (keywordIndex == 1)
        entitiesNested();
    else if (keywordIndex == 2)
        editor();
    else if (keywordIndex == 3)
        database();
    else if (keywordIndex == 4)
        services();
    else if (keywordIndex == 5)
        sysRegistry();
    else {
        ASSERT(0);
        return;
    }
}

/****************************************************************************
**
**  ArxDbgCmdSnoop::entities
**      display the information available for a given entity.
**
**  **jma
**
*************************************/

void
ArxDbgCmdSnoop::entities()
{
    ArxDbgSelSet ss;
    if (ss.userSelect() == ArxDbgSelSet::kSelected) {    // have user select entities from DWG
        AcDbObjectIdArray objList;
        ss.asArray(objList);
        if (!objList.isEmpty()) {
            ArxDbgUiTdmEntities dbox(objList, false, acedGetAcadDwgView(), _T("Selected Entities"));
            dbox.DoModal();
        }
    }
}

/****************************************************************************
**
**  ArxDbgCmdSnoop::entitiesNested
**      display the information available for a given entity (but possibly nested
**	within a block or xref).
**
**  **jma
**
*************************************/

void
ArxDbgCmdSnoop::entitiesNested()
{
	AcDbObjectIdArray objIds;
	AcDbObjectId objId;
	Acad::ErrorStatus es;

	ads_point ptResult;
	ads_name ent;
	ads_matrix xformres;
	resbuf* refstkres;

	while (1) {
		refstkres = NULL;
		acedInitGet(0, _T("Done"));
		int result = acedNEntSelP(_T("\nSelect nested entities or [Done]: "), ent, ptResult, 0, xformres, &refstkres);
		if (refstkres != NULL)
			acutRelRb(refstkres);	// we don't need to know what the container ents were.

		if (result == RTNORM) {
			es = acdbGetObjectId(objId, ent);
			if (es == Acad::eOk) {
				if (objIds.contains(objId) == false)
					objIds.append(objId);
			}
			else
				ArxDbgUtils::rxErrorMsg(es);
		}
		else if (result == RTKWORD)
			break;	// we'll just assume its our only keyword
		else
			return;
	}

	if (objIds.isEmpty() == false) {
		ArxDbgUiTdmEntities dbox(objIds, false, acedGetAcadDwgView(), _T("Selected Entities (Nested)"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**	ArxDbgCmdSnoop::editor
**
**	**jma
**
*************************************/

void
ArxDbgCmdSnoop::editor()
{
    ArxDbgUiTdmEditor dbox(acedGetAcadDwgView());
    dbox.DoModal();
}

/****************************************************************************
**
**	ArxDbgCmdSnoop::database
**
**	**jma
**
*************************************/

void
ArxDbgCmdSnoop::database()
{
	CString dboxTitle = acDocManager->curDocument()->docTitle();

    ArxDbgUiTdmDatabase dbox(acdbHostApplicationServices()->workingDatabase(), acedGetAcadDwgView(), dboxTitle);
    dbox.DoModal();
}

/****************************************************************************
**
**  ArxDbgCmdSnoop::services
**
**  **jma
**
*************************************/

void
ArxDbgCmdSnoop::services()
{
    ArxDbgUiDlgServiceDict dbox(acedGetAcadDwgView());
    dbox.DoModal();
}

/****************************************************************************
**
**  ArxDbgCmdSnoop::sysRegistry
**
**  **jma
**
*************************************/

void
ArxDbgCmdSnoop::sysRegistry()
{
    ArxDbgUiDlgSysRegistry dbox(acedGetAcadDwgView());
    dbox.DoModal();
}


