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
#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxDbgEdUiContext.h"
#include "ArxDbgApp.h"
#include "AcExtensionModule.h"
#include "Res_ArxDbg.h"



//ACRX_CONS_DEFINE_MEMBERS(ArxDbgEdUiContextApp, AcEdUiContext, 1)

/**************************************************************************
**
**  ArxDbgEdUiContextApp::ArxDbgEdUiContextApp
**
**  **jma
**
*************************************/

ArxDbgEdUiContextApp::ArxDbgEdUiContextApp()
{
	CAcModuleResourceOverride(ArxDbgApp::getApp()->dllInstance());

    m_cMenu = new CMenu;
    BOOL res = m_cMenu->LoadMenu(ARXDBG_MNU_APP);
    VERIFY(res);
    if (!res) {
        delete m_cMenu;
        m_cMenu = NULL;
    }
}

/**************************************************************************
**
**  ArxDbgEdUiContextApp::ArxDbgEdUiContextApp
**
**  **jma
**
*************************************/

ArxDbgEdUiContextApp::~ArxDbgEdUiContextApp()
{
    if (m_cMenu) 
        delete m_cMenu;
}

/**************************************************************************
**
**  ArxDbgEdUiContextApp::getMenuContext
**
**  **jma
**
*************************************/

void* 
ArxDbgEdUiContextApp::getMenuContext(const AcRxClass* classtype, const AcDbObjectIdArray& selectedObjs)
{
    m_hMenu = m_cMenu->GetSubMenu(0)->GetSafeHmenu();
    return &m_hMenu;
}

/**************************************************************************
**
**  ArxDbgEdUiContextApp::onCommand
**
**  **jma
**
*************************************/

void  
ArxDbgEdUiContextApp::onCommand(Adesk::UInt32 cmdId)
{
	LPCTSTR cmdStr = NULL;
	CString str;

	if (cmdId == ARXDBG_APPCMD_EDITOR_INFO)
		cmdStr = _T("ArxDbgSnoopEd");
	else if (cmdId == ARXDBG_APPCMD_DB_INFO)
		cmdStr = _T("ArxDbgSnoopDb");
	else if (cmdId == ARXDBG_APPCMD_ENT_INFO)
		cmdStr = _T("ArxDbgSnoopEnts");
	else if (cmdId == ARXDBG_APPCMD_NESTEDENT_INFO)
		cmdStr = _T("ArxDbgSnoopNents");
	else if (cmdId == ARXDBG_APPCMD_SERVICES_INFO)
		cmdStr = _T("ArxDbgSnoopServices");
	else if (cmdId == ARXDBG_APPCMD_REGISTRY_INFO)
		cmdStr = _T("ArxDbgSnoopSysRegistry");
	else if (cmdId == ARXDBG_APPCMD_REACTOR_INFO)
		cmdStr = _T("ArxDbgReactors");
	else if (cmdId == ARXDBG_APPCMD_OBJ_STATE)
		cmdStr = _T("ArxDbgTestState");
	else if (cmdId == ARXDBG_APPCMD_DWG_FILER)
		cmdStr = _T("ArxDbgTestDwgFiler");
	else if (cmdId == ARXDBG_APPCMD_TEST_TRANSDB_CLONES)
		cmdStr = _T("ArxDbgTestTransDbClones");
	else if (cmdId == ARXDBG_APPCMD_TEST_WORLD_DRAW)
		cmdStr = _T("ArxDbgTestWorldDraw");
	else if (cmdId == ARXDBG_APPCMD_TEST_CURVES)
		cmdStr = _T("ArxDbgTestCurve");
	else if (cmdId == ARXDBG_APPCMD_TEST_SELSET)
		cmdStr = _T("ArxDbgTestSelSet");
	else if (cmdId == ARXDBG_APPCMD_TEST_XDATA)
		cmdStr = _T("ArxDbgTestXdata");
	else if (cmdId == ARXDBG_APPCMD_TEST_EXTENTS)
		cmdStr = _T("ArxDbgTestExtents");
	else if (cmdId == ARXDBG_APPCMD_TEST_INTERSECT)
		cmdStr = _T("ArxDbgTestIntersect");
	else if (cmdId == ARXDBG_APPCMD_TEST_GRIPPTS)
		cmdStr = _T("ArxDbgTestGetGripPoints");
	else if (cmdId == ARXDBG_APPCMD_TEST_STRETCHPTS)
		cmdStr = _T("ArxDbgTestGetStretchPoints");
	else if (cmdId == ARXDBG_APPCMD_TEST_OSNAP)
		cmdStr = _T("ArxDbgTestGetOsnapPoints");
	else if (cmdId == ARXDBG_APPCMD_TEST_EXTDICTADD)
		cmdStr = _T("ArxDbgTestExtDictAdd");
	else if (cmdId == ARXDBG_APPCMD_TEST_EXTDICT_REMOVE)
		cmdStr = _T("ArxDbgTestExtDictRemove");
	else if (cmdId == ARXDBG_APPCMD_TEST_COLOR)
		cmdStr = _T("ArxDbgTestColor");
	else if (cmdId == ARXDBG_APPCMD_TEST_PURGE)
		cmdStr = _T("ArxDbgTestPruge");
	else if (cmdId == ARXDBG_APPCMD_TEST_COUNTREFS)
		cmdStr = _T("ArxDbgTestCountHardRefs");
	else if (cmdId == ARXDBG_APPCMD_TEST_ENTMAKE)
		cmdStr = _T("ArxDbgTestEntMake");
	else if (cmdId == ARXDBG_APPCMD_TEST_TBLMAKE)
		cmdStr = _T("ArxDbgTestTblMake");
	else if (cmdId == ARXDBG_APPCMD_TEST_XFORM)
		cmdStr = _T("ArxDbgTestXform");
	else if (cmdId == ARXDBG_APPCMD_LOGO_ADD)
		cmdStr = _T("ArxDbgAdeskLogoAdd");
	else if (cmdId == ARXDBG_APPCMD_LOGO_MODIFY)
		cmdStr = _T("ArxDbgAdeskLogoModify");
	else if (cmdId == ARXDBG_APPCMD_LOGO_HARDWIRE1)
		cmdStr = _T("ArxDbgAdeskLogoHardwire1");
	else if (cmdId == ARXDBG_APPCMD_LOGO_HARDWIRE2)
		cmdStr = _T("ArxDbgAdeskLogoHardwire2");
	else if (cmdId == ARXDBG_APPCMD_LOGO_ADD_STYLE)
		cmdStr = _T("ArxDbgAdeskLogoStyleAdd");
	else if (cmdId == ARXDBG_APPCMD_LOGO_MOD_STYLE)
		cmdStr = _T("ArxDbgAdeskLogoStyleModify");
	else if (cmdId == ARXDBG_APPCMD_ABOUT)
		cmdStr = _T("ArxDbgAbout");

	if (cmdStr != NULL) {
		str.Format(_T("%s\n"), cmdStr);
	    acDocManager->sendStringToExecute(acDocManager->curDocument(), str, false, false);
	}
}

