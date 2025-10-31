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

#include "ArxDbgApp.h"
#include "ArxDbgUiDlgSplash.h"
#include "ArxDbgDbDictRecord.h"
#include "ArxDbgWorldDraw.h"
#include "ArxDbgDwgFiler.h"
#include "ArxDbgReferenceFiler.h"
#include "ArxDbgAppEditorReactor.h"
#include "ArxDbgDatabaseReactor.h"
#include "ArxDbgDLinkerReactor.h"
#include "ArxDbgDocumentReactor.h"
#include "ArxDbgEditorReactor.h"
#include "ArxDbgEventReactor.h"
#include "ArxDbgGsReactor.h"
#include "ArxDbgLayoutManagerReactor.h"
#include "ArxDbgLongTransactionReactor.h"
#include "ArxDbgTransactionReactor.h"
#include "ArxDbgDbEntity.h"
#include "ArxDbgDbAdeskLogo.h"
#include "ArxDbgDbAdeskLogoStyle.h"
#include "MapTest.h"
#include "ArxDbgUiTdcOptions.h"
#include "AcExtensionModule.h"
#include "ArxDbgPersistentEntReactor.h"
#include "ArxDbgPersistentObjReactor.h"
#include "ArxDbgTransientEntReactor.h"
#include "ArxDbgTransientObjReactor.h"
#include "ArxDbgEdUiContext.h"
#include "ArxDbgCmdAdeskLogo.h"
#include "ArxDbgCmdSnoop.h"
#include "ArxDbgCmdReactors.h"
#include "ArxDbgCmdTests.h"
#include "ArxDbgUiTdmReactors.h"



extern void cmdAboutBox();
extern void mapTestExportDwg();
extern void mapTestImportDwg();


AC_IMPLEMENT_EXTENSION_MODULE(ArxDbgDll);

ArxDbgApp*    ThisApp = NULL;

/****************************************************************************
**
**  DllMain
**
**  **jma
**
*************************************/

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH) {
        ArxDbgDll.AttachInstance(hInstance);
        ThisApp = new ArxDbgApp;
    }
    else if (dwReason == DLL_PROCESS_DETACH) {
        ArxDbgDll.DetachInstance();  
        if (ThisApp) {
            delete ThisApp;
            ThisApp = NULL;
        }
    }
    return 1;   // ok
}

/****************************************************************************
**
**  acrxEntryPoint:
**
**  **jma
**
*************************************/

extern "C" __declspec(dllexport) AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pPkt)
{
    return ThisApp->entryPoint(msg, pPkt);
}

/****************************************************************************
**
**  ArxDbgApp::getApp
**      static function to get access to this module in general
**
**  **jma
**
*************************************/

ArxDbgApp*
ArxDbgApp::getApp()
{
    return ThisApp;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**  ArxDbgApp::ArxDbgApp
**
**  **jma
**
*************************************/

ArxDbgApp::ArxDbgApp()
:   m_isUnlockable(true),
    m_acadAppPtr(NULL),
    m_appServicePtr(NULL),
    m_appName(_T("ArxDbg")),
    m_verStr(_T("2.0")),
    m_appId(0),
    m_didInit(false),
	m_tdcOptions(NULL)
{
	m_moduleName = m_appName;
#ifdef _DEBUG
    m_moduleName += _T("D");
#endif
}

/****************************************************************************
**
**  ArxDbgApp::~ArxDbgApp
**
**  **jma
**
*************************************/

ArxDbgApp::~ArxDbgApp()
{
	//ASSERT(m_tdcOptions == NULL);	// TBD: should have been deleted by a call to endDialog

	if (m_tdcOptions)
		delete m_tdcOptions;
}

static const TCHAR acGeomentObjDbxFile[] = _T("AcGeomentObj.dbx");

/****************************************************************************
**
**  ArxDbgApp::entryPoint
**      print out message saying that we recieved the app message from ARX
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxDbgApp::entryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    if (msg == AcRx::kInitAppMsg) {
		m_acadAppPtr = pkt;	// keep track of this for later use
        acutPrintf(_T("\nAPPMSG: %s, kInitAppMsg"), m_appName);
        acrxLoadModule(acGeomentObjDbxFile, 0);
        return initApp();
    }
    else if (msg == AcRx::kUnloadAppMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kUnloadAppMsg"), m_appName);
        acrxUnloadModule(acGeomentObjDbxFile);
        return exitApp();
    }
    else if (msg == AcRx::kLoadDwgMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kLoadDwgMsg"), m_appName);
        return initDwg();
    }
    else if (msg == AcRx::kUnloadDwgMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kUnloadDwgMsg"), m_appName);
        return exitDwg();
    }
    else if (msg == AcRx::kInvkSubrMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kInvkSubrMsg"), m_appName);
        return invokeSubr();
    }
    else if (msg == AcRx::kCfgMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kCfgMsg"), m_appName);
        return config();
    }
    else if (msg == AcRx::kEndMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kEndMsg"), m_appName);
        return endDwg();
    }
    else if (msg == AcRx::kQuitMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kQuitMsg"), m_appName);
        return quitDwg();
    }
    else if (msg == AcRx::kSaveMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kSaveMsg"), m_appName);
        return saveDwg();
    }
    else if (msg == AcRx::kDependencyMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kDependencyMsg"), m_appName);

        if (m_appServicePtr == pkt) {
            acutPrintf(_T("\nLocking app: %s"), m_appName);
            acrxDynamicLinker->lockApplication(m_acadAppPtr);
        }

        return AcRx::kRetOK;
    }
    else if (msg == AcRx::kNoDependencyMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kNoDependencyMsg"), m_appName);

        if (m_appServicePtr == pkt) {
            acutPrintf(_T("\nUnlocking app: %s"), m_appName);
            acrxDynamicLinker->unlockApplication(m_acadAppPtr);
        }

        return AcRx::kRetOK;
    }
    else if (msg == AcRx::kOleUnloadAppMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kOleUnloadAppMsg"), m_appName);
        return AcRx::kRetOK;
    }
    else if (msg == AcRx::kPreQuitMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kPreQuitMsg"), m_appName);
        return AcRx::kRetOK;
    }
    else if (msg == AcRx::kInitDialogMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kInitDialogMsg"), m_appName);
        return initDialog(pkt);
    }
    else if (msg == AcRx::kEndDialogMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kEndDialogMsg"), m_appName);
        return endDialog(pkt);
    }
    else {
        ASSERT(0);        // just see if it ever happens
        return AcRx::kRetOK;
    }
}

/****************************************************************************
**
**  ArxDbgApp::initApp
**      Called one time only each time the application is loaded. Init
**  only those things that are specific to the application itself, not the
**  current drawing.
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxDbgApp::initApp()
{
    acrxUnlockApplication(m_acadAppPtr);
    acrxDynamicLinker->registerAppMDIAware(m_acadAppPtr);

        // get the name of this app so we can find where other
        // things are located.
    CString appFileName = acedGetAppName();

    TCHAR dir[_MAX_DIR], drive[_MAX_DRIVE], path[_MAX_PATH];
    _tsplitpath_s(appFileName, drive, _MAX_DRIVE, dir, _MAX_DIR, NULL, 0, NULL, 0);
    _tmakepath(path, drive, dir, NULL, NULL);
    m_appPath = path;

	CWnd* splashScreen = startSplashScreen();

    registerClasses();
    registerCommands();
    acrxBuildClassHierarchy();

    m_appServicePtr = acrxRegisterService(_T("ArxDbgServices"));

    ArxDbgAppEditorReactor::getInstance();
    MapTestReactor::getInstance();

	registerDialogExtensions();
	registerAppMenu();

	endSplashScreen(splashScreen);

    m_didInit = true;
    return AcRx::kRetOK;
}

/**************************************************************************
**
**  ArxDbgApp::exitApp:
**      Clean up any application related stuff.  Note that we must
**  be unlocked in order to allow unloading.
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxDbgApp::exitApp()
{
	unRegisterAppMenu();

        // delete any of the notification spies that have been allocated
    ArxDbgUiTdmReactors::cleanUpReactors();
    ArxDbgAppEditorReactor::destroyInstance();
	MapTestReactor::destroyInstance();

    if (m_didInit) {
        unRegisterCommands();
        unRegisterClasses();

        acutPrintf(_T("\n%s has been unloaded ... "), appName());
    }

    return AcRx::kRetOK;
}

/****************************************************************************
**
**  ArxDbgApp::initDwg:
**      Called each time a drawing is loaded. Initialize drawing
**  specific information.
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxDbgApp::initDwg()
{
		// this is just a place-holder for tests
    return AcRx::kRetOK;
}

/**************************************************************************
**
**  ArxDbgApp::exitDwg:
**      Called each time a drawing is exited. Clean up anything
**  that is drawing specific.
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxDbgApp::exitDwg()
{
		// this is just a place-holder for tests
    return AcRx::kRetOK;
}

/**************************************************************************
**
**  ArxDbgApp::saveDwg:
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxDbgApp::saveDwg()
{
		// this is just a place-holder for tests
    return AcRx::kRetOK;
}

/**************************************************************************
**
**  ArxDbgApp::endDwg:
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxDbgApp::endDwg()
{
		// this is just a place-holder for tests
    return AcRx::kRetOK;
}

/**************************************************************************
**
**  ArxDbgApp::quitDwg
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxDbgApp::quitDwg()
{
		// this is just a place-holder for tests
    return AcRx::kRetOK;
}

/**************************************************************************
**
**  ArxDbgApp::config
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxDbgApp::config()
{
		// this is just a place-holder for tests
    return AcRx::kRetOK;
}

/**************************************************************************
**
**  ArxDbgApp::invokeSubr
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxDbgApp::invokeSubr()
{
		// this is just a place-holder for tests
    return AcRx::kRetOK;
}

/****************************************************************************
**
**  ArxDbgApp::initDialog
**      Called indirectly from a tab-extensible dialog (during initialization) 
**      that this app is registered with.
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxDbgApp::initDialog(void* pkt)
{
    CAdUiTabExtensionManager* pTabExtMgr = static_cast<CAdUiTabExtensionManager*>(pkt);

        // Get name of extensible dialog
    CString tabDlgName = pTabExtMgr->GetDialogName();

        // Add the "ArxDbg" tab to the Options dialog
    if (!tabDlgName.CompareNoCase(_T("OptionsDialog"))) {

			// TBD: It seems that we have to hold on to the dialog between invocations.
			// I would think that we would get a call to endDialog that would allow us
			// to delete the dialog after it closes... but that doesn't appear to be
			// the case.
		if (m_tdcOptions == NULL)
			m_tdcOptions = new ArxDbgUiTdcOptions;

        if (m_tdcOptions) {
            pTabExtMgr->AddTab(dllInstance(), ARXDBG_TDC_OPTIONS, _T("ArxDbg"), m_tdcOptions);
        }
    }

    return AcRx::kRetOK;
}

/****************************************************************************
**
**  ArxDbgApp::endDialog
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxDbgApp::endDialog(void* pTabExtMgr)
{
		// TBD: why does this never get called?
	delete m_tdcOptions;
    m_tdcOptions = NULL;

    return AcRx::kRetOK;
}

/**************************************************************************
**
**  ArxDbgApp::registerClasses:
**		call rxInit on all classes we have defined that are derived
**	from AcRxObject or any of its descendants
**
**  **jma
**
*************************************/

void
ArxDbgApp::registerClasses()
{
    ArxDbgPersistentObjReactor::rxInit();    // our test case for persistent object reactors
    ArxDbgPersistentEntReactor::rxInit();    // our test case for persistent entity reactors
    ArxDbgTransientObjReactor::rxInit();     // our test case for transient object reactors
    ArxDbgTransientEntReactor::rxInit();     // our test case for transient entity reactors

    ArxDbgAppEditorReactor::rxInit();
    ArxDbgDwgFiler::rxInit();
    ArxDbgReferenceFiler::rxInit();

    ArxDbgGiContext::rxInit();
    ArxDbgGiSubEntityTraits::rxInit();
    ArxDbgGiWorldGeometry::rxInit();
    ArxDbgGiWorldDraw::rxInit();

    ArxDbgDbDictRecord::rxInit();    // test case for basic dictionary entry
	ArxDbgDbEntity::rxInit();
    ArxDbgDbAdeskLogo::rxInit();
    ArxDbgDbAdeskLogoStyle::rxInit();

	ArxDbgDatabaseReactor::rxInit();
	ArxDbgDLinkerReactor::rxInit();
	ArxDbgDocumentReactor::rxInit();
	ArxDbgEditorReactor::rxInit();
    ArxDbgEventReactor::rxInit();
	ArxDbgLayoutManagerReactor::rxInit();
	ArxDbgLongTransactionReactor::rxInit();
	ArxDbgTransactionReactor::rxInit();
}

/**************************************************************************
**
**  ArxDbgApp::unRegisterClasses:
**      reverse everything done in ArxDbgApp::registerClasses()
**
**  **jma
**
*************************************/

void
ArxDbgApp::unRegisterClasses()
{
    deleteAcRxClass(ArxDbgPersistentEntReactor::desc());
    deleteAcRxClass(ArxDbgPersistentObjReactor::desc());
    deleteAcRxClass(ArxDbgTransientEntReactor::desc());
    deleteAcRxClass(ArxDbgTransientObjReactor::desc());

    deleteAcRxClass(ArxDbgAppEditorReactor::desc());
    deleteAcRxClass(ArxDbgDwgFiler::desc());
    deleteAcRxClass(ArxDbgReferenceFiler::desc());

    deleteAcRxClass(ArxDbgGiWorldDraw::desc());
    deleteAcRxClass(ArxDbgGiWorldGeometry::desc());
    deleteAcRxClass(ArxDbgGiSubEntityTraits::desc());
    deleteAcRxClass(ArxDbgGiContext::desc());

    deleteAcRxClass(ArxDbgDbAdeskLogo::desc());
    deleteAcRxClass(ArxDbgDbAdeskLogoStyle::desc());
    deleteAcRxClass(ArxDbgDbDictRecord::desc());
	deleteAcRxClass(ArxDbgDbEntity::desc());

	deleteAcRxClass(ArxDbgDatabaseReactor::desc());
	deleteAcRxClass(ArxDbgDLinkerReactor::desc());
	deleteAcRxClass(ArxDbgDocumentReactor::desc());
	deleteAcRxClass(ArxDbgEditorReactor::desc());
    deleteAcRxClass(ArxDbgEventReactor::desc());
	deleteAcRxClass(ArxDbgLayoutManagerReactor::desc());
	deleteAcRxClass(ArxDbgLongTransactionReactor::desc());
	deleteAcRxClass(ArxDbgTransactionReactor::desc());
}

/**************************************************************************
**
**  ArxDbgApp::registerCommands:
**
**  **jma
**
*************************************/

void
ArxDbgApp::registerCommands()
{
		// allocate the command classes.  These will in turn register their own
		// group of CmdLine functions through AcEd::addCommand()
	m_cmdClasses.append(new ArxDbgCmdAdeskLogo);
	m_cmdClasses.append(new ArxDbgCmdSnoop);
	m_cmdClasses.append(new ArxDbgCmdReactors);
	m_cmdClasses.append(new ArxDbgCmdTests);

    AcEdCommandStack* cmdStack = acedRegCmds;
    VERIFY(cmdStack != NULL);

	ArxDbgCmd* tmpCmdClass;
	int len = m_cmdClasses.length();
	for (int i=0; i<len; i++) {
		tmpCmdClass = static_cast<ArxDbgCmd*>(m_cmdClasses[i]);
		tmpCmdClass->registerCommandLineFunctions(cmdStack, m_appName);
	}

		// add in a few stragglers that don't have their own ArxDbgCmd class yet
    cmdStack->addCommand(m_appName, _T("ArxDbgAbout"), _T("ArxDbgAbout"), ACRX_CMD_MODAL, &cmdAboutBox);

		// GIS Map tests for ADE
	cmdStack->addCommand(m_appName, _T("ArxDbgMapTestExport"), _T("MapTestExport"), ACRX_CMD_MODAL, &mapTestExportDwg);
    cmdStack->addCommand(m_appName, _T("ArxDbgMapTestImport"), _T("MapTestImport"), ACRX_CMD_MODAL, &mapTestImportDwg);
}

/**************************************************************************
**
**  ArxDbgApp::unRegisterCommands:
**
**  **jma
**
*************************************/

void
ArxDbgApp::unRegisterCommands()
{
		// delete any command classes we have allocated
	ArxDbgCmd* tmpCmdClass;
	int len = m_cmdClasses.length();
	for (int i=0; i<len; i++) {
		tmpCmdClass = static_cast<ArxDbgCmd*>(m_cmdClasses[i]);
		delete tmpCmdClass;
	}

	m_cmdClasses.setLogicalLength(0);

    acedRegCmds->removeGroup(m_appName);    // remove any registered commands
}

/**************************************************************************
**
**  ArxDbgApp::startSplashScreen
**
**  **jma
**
*************************************/

CWnd*
ArxDbgApp::startSplashScreen()
{
    CString bmpFileName = appPath();
    bmpFileName += _T("support\\ArxDbgSplash.bmp");    // TBD: make this better later!

        // make sure file is there (either in a main directory, which is
		// where someone would install it, or for developers, go out of 
		// "Debug" directory and up to the main directory.
    CFileStatus status;
    // Watch out for exceptions from GetStatus() due to bad date fields on the file.
    BOOL success = false;
    try {
        success = CFile::GetStatus(bmpFileName, status); // try/catch safe
        if (success == FALSE) {
    	    bmpFileName = appPath();
    	    //x64 binaries are created within x64\ folder
#if defined(_WIN64) || defined(_AC64)
        	bmpFileName += _T("..\\..\\support\\ArxDbgSplash.bmp");  // TBD: make this better later!
#else
        	bmpFileName += _T("..\\support\\ArxDbgSplash.bmp");  // TBD: make this better later!
#endif
    	    success = CFile::GetStatus(bmpFileName, status);  // try/catch safe
        }
    }
    catch (COleException* e) {
        e->Delete();
        // If we get here the file exists but it has a bad date field
        success = true;
    }

	if (success) {
        ArxDbgUiDlgSplash* dbox = new ArxDbgUiDlgSplash(bmpFileName);
        dbox->setTextStrings(appName(), versionStr(), _T(""), _T(""));

        // TBD: have to do this manually right now, although it should
        // have worked to pass up resource handle through the constructor!
        {
            CAcModuleResourceOverride resOverride;
            dbox->Create(acedGetAcadDwgView());
        }

        dbox->ShowWindow(SW_SHOW);
        dbox->UpdateWindow();

        return dbox;
    }
    else {        // intended a splash screen but could not find it!
        acutPrintf(_T("\nCould not find splash box image: \"%s\""), bmpFileName);
        return NULL;
    }
}

/**************************************************************************
**
**  ArxDbgApp::endSplashScreen
**
**  **jma
**
*************************************/

void
ArxDbgApp::endSplashScreen(CWnd* splashScreen)
{
    if (splashScreen) {
        Sleep(1000);    // waste a little bit of time to ensure that they see it
        splashScreen->ShowWindow(SW_HIDE);
        splashScreen->UpdateWindow();
        splashScreen->DestroyWindow();
        delete splashScreen;
        acedGetAcadDwgView()->Invalidate();
        acedGetAcadDwgView()->UpdateWindow();
    }
}

/**************************************************************************
**
**  ArxDbgApp::registerAppMenu
**
**  **jma
**
*************************************/

void
ArxDbgApp::registerAppMenu()
{
    m_uiContext = new ArxDbgEdUiContextApp;

	if ((m_uiContext->isValid() == false) ||
		(acedAddDefaultContextMenu(m_uiContext, m_acadAppPtr, _T("ArxDbg")) == false)) {
		ASSERT(0);

        delete m_uiContext;
        m_uiContext = NULL;
    }
}

/**************************************************************************
**
**  ArxDbgApp::unRegisterAppMenu
**
**  **jma
**
*************************************/

void
ArxDbgApp::unRegisterAppMenu()
{
    if (m_uiContext) {
        acedRemoveDefaultContextMenu(m_uiContext);
        delete m_uiContext;
        m_uiContext = NULL;
    }
}

/**************************************************************************
**
**  ArxDbgApp::registerDialogExtensions
**
**  **jfk
**
*************************************/

void
ArxDbgApp::registerDialogExtensions()
{
        // Register the fact that we want to add a tab to the following dialogs
    acedRegisterExtendedTab(m_moduleName, _T("OptionsDialog"));
}

/**************************************************************************
**
**  ArxDbgApp::dllInstance
**
**  **jma
**
*************************************/

HINSTANCE
ArxDbgApp::dllInstance() const
{
	return ArxDbgDll.ModuleResourceInstance();
}

