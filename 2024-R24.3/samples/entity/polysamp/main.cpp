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
// DESCRIPTION:
//
// This file contains the code for interfacing to AutoCAD.
#define WIN32_LEAN_AND_MEAN
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "windows.h"
#include "objbase.h"

#include "rxregsvc.h"
#include "aced.h"

#include "poly.h"
#include "command.h"
#include "match.h"

#include "dbapserv.h"
#include "appinfo.h"
#include "tchar.h"



extern "C" {

// locally defined entry point invoked by Rx.

AcRx::AppRetCode __declspec(dllexport) acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt);

}

extern void UpdateUserInterfaceForPolySamp();
extern void  CleanUpUserInterfaceForPolySamp();

//----------------------------------------------------------------------------
// Match Property
// Pointer for protocol Extension Objects. Pointers are global so that they
// can be accessed during initialization and cleanup.
// This is an application wide variable and thus MDI safe
static AsdkPolyMatchProp *pMatchPoly;


// Forward declaration for the AppEventCatcher class
//
Adesk::Boolean addMatchPoly();

// This is an application wide variable and thus MDI safe
short AppEventCatcher::thisAppLoaded = 0;

//----------------------------------------------------------------------------

void
AppEventCatcher::rxAppLoaded(const TCHAR* moduleName)
{
    if (!thisAppLoaded) 
    {
        addMatchPoly();
    }
}

//----------------------------------------------------------------------------

Adesk::Boolean
addMatchPoly()
{
    AcRxObject *pTemp;

    if (pTemp = acrxServiceDictionary->at(_T("MatchProperties")))
    {
        acutPrintf (_T("MatchProperties is now available.\n")
                    _T("Now adding match prop protocol extension to AsdkPoly.\n"));
        acedPostCommandPrompt();


        AcRxService *pSvc = AcRxService::cast(pTemp);
  
        if (pSvc == NULL)
          // something's terribly wrong so abort
          acrx_abort(_T("\nProblem with service dictionary\n"));

        // now to add the dependency to match.arx
        pSvc->addDependency();
        
        pMatchPoly = new AsdkPolyMatchProp;
        AsdkPoly::desc()->addX(AcDbMatchProperties::desc(), pMatchPoly);
       
        AppEventCatcher::thisAppLoaded = 1;
        
        return Adesk::kTrue;
    }

    return Adesk::kFalse;
}

//----------------------------------------------------------------------------

void
AsdkPolyMatchProp::copyProperties(AcDbEntity *pSrcEntity, AcDbEntity *pTrgEntity, 
                                  unsigned int gMatchFlag) const
{
    AsdkPoly *pPoly = AsdkPoly::cast(pTrgEntity);

    //Do Poly property related property painting....
    if (pSrcEntity->isKindOf(AsdkPoly::desc())) {
      AsdkPoly *pSrcPoly = AsdkPoly::cast(pSrcEntity);

      // copy num sides
      pPoly->setNumSides(pSrcPoly->numSides());

      // add more polysamp properties to match here 
    }

    //Do basic property painting
    
    // COLOR
    if (gMatchFlag & kColorFlag)
        pTrgEntity->setColorIndex(pSrcEntity->colorIndex());

    //LAYER
    if (gMatchFlag & kLayerFlag)
        pTrgEntity->setLayer(pSrcEntity->layerId());

    // LINETYPE
    if (gMatchFlag & kLtypeFlag)
        pTrgEntity->setLinetype(pSrcEntity->linetypeId());

        // LINETYPESCALE
    if (gMatchFlag & kLtscaleFlag)
        pTrgEntity->setLinetypeScale(pSrcEntity->linetypeScale());

    // VISIBILITY. copied always. Should be transparent. 
    pTrgEntity->setVisibility(pSrcEntity->visibility());
}

//----------------------------------------------------------------------------

// Initialization Function

void initModule()
{

    // add match prop protocol extension to AsdkPoly
    //
    if (!addMatchPoly()) 
    {
        acutPrintf (_T("MatchProperties has not been registered.\n")
                    _T("Protocol extension will be added when MATCHPROP is used\n"));
        acedPostCommandPrompt();
    }

    acedRegCmds->addCommand(_T("ASDK_POLYGON"),
                            _T("ASDK_POLY"),
                            _T("POLY"),
                            ACRX_CMD_MODAL,
                            &polyCommand);

    acedRegCmds->addCommand(_T("ASDK_POLYGON"),
                            _T("PPOLY"),
                            _T("PPOLY"),
                            ACRX_CMD_MODAL | ACRX_CMD_INTERRUPTIBLE,
                            &polyCommand2);

    acedRegCmds->addCommand(_T("ASDK_POLYGON"),
                            _T("ASDK_DRAGPOLY"),
                            _T("DRAGPOLY"),
                            ACRX_CMD_MODAL,
                            &dragPolyCommand);

    acedRegCmds->addCommand(_T("ASDK_POLYGON"),
                            _T("ASDK_POLYEDIT"),
                            _T("POLYEDIT"),
                            ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET,
                            &polyeditCommand);

    acedRegCmds->addCommand(_T("ASDK_POLYGON"),
                            _T("ASDK_TRANSACT"),
                            _T("TRANSACT"),
                            ACRX_CMD_MODAL,
                            &transactCommand);

    acedRegCmds->addCommand(_T("ASDK_POLYGON"),
                            _T("ASDK_HILITPOLY"),
                            _T("HILITPOLY"),
                            ACRX_CMD_MODAL,
                            &hilitPoly);

    acedRegCmds->addCommand(_T("ASDK_POLYGON"),
                            _T("ASDK_HILITSOLID"),
                            _T("HILITSOLID"),
                            ACRX_CMD_MODAL,
                            &hilitSolid);

    acedRegCmds->addCommand(_T("ASDK_POLYGON"),
                            _T("ASDK_CREATEINSERT"),
                            _T("CREATEINSERT"),
                            ACRX_CMD_MODAL,
                            &createInsert);

    acedRegCmds->addCommand(_T("ASDK_POLYGON"),
                            _T("ASDK_HILITINSERT"),
                            _T("HILITINSERT"),
                            ACRX_CMD_MODAL,
                            &hilitInsert);

    acedRegCmds->addCommand(_T("ASDK_POLYGON"),
                            _T("ASDK_USEDRAGDATA"),
                            _T("USEDRAGDATA"),
                            ACRX_CMD_TRANSPARENT,
                            setUseDragData);
	acedRegCmds->addCommand(_T("ASDK_POLYGON"),
							_T("ASDK_POLYCLEANUI"),
							_T("POLYCLEANUI"),
							ACRX_CMD_TRANSPARENT,
							&CleanUpUserInterfaceForPolySamp);
		
	UpdateUserInterfaceForPolySamp();
}

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

void updateRegistry()
{
	// Fill the AppInfo structure with our demand loading details.
	AcadAppInfo appInfo;
	appInfo.setAppName(_T("AsdkPolyCAD")); // Application name
	appInfo.setModuleName(acedGetAppName());// Module path
	appInfo.setAppDesc(_T("AsdkPolyCAD")); // Description
	appInfo.setLoadReason(// Specify when we want these to load
		AcadApp::LoadReasons(
		AcadApp::kOnCommandInvocation |
		AcadApp::kOnLoadRequest));
	
	appInfo.writeToRegistry();// Write the appInfo to the registry.
	
	appInfo.writeGroupNameToRegistry(_T("ASDK_POLYGON"));// Write the group name
	
	// Write out all our commands (Global,Local).
	appInfo.writeCommandNameToRegistry(_T("ASDK_POLY"),_T("POLY"));
	appInfo.writeCommandNameToRegistry(_T("ASDK_DRAGPOLY"),_T("DRAGPOLY"));
	appInfo.writeCommandNameToRegistry(_T("ASDK_POLYEDIT"),_T("POLYEDIT"));
	appInfo.writeCommandNameToRegistry(_T("ASDK_TRANSACT"),_T("TRANSACT"));
	appInfo.writeCommandNameToRegistry(_T("ASDK_HILITPOLY"),_T("HILITPOLY"));
	appInfo.writeCommandNameToRegistry(_T("ASDK_HILITSOLID"),_T("HILITSOLID"));
	appInfo.writeCommandNameToRegistry(_T("ASDK_CREATEINSERT"),_T("CREATEINSERT"));
	appInfo.writeCommandNameToRegistry(_T("ASDK_HILITINSERT"),_T("HILITINSERT"));
}

// END CODE APPEARING IN SDK DOCUMENT.

typedef HRESULT (*DllCanUnloadNowFunc)();
STDAPI DllCanUnloadNow(void);

static const TCHAR acGeomentObjDbxFile[] = _T("AcGeomentObj.dbx");

AcRx::AppRetCode __declspec(dllexport)
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    static AppEventCatcher* appEventCatcher = NULL;
    static void *moduleHandle;
    static HINSTANCE hDllAuto = NULL;
    
    switch(msg) {

    case AcRx::kInitAppMsg:

        if (!acrxLoadModule(acGeomentObjDbxFile, 0))
            return AcRx::kRetError;

		if (!acrxLoadModule(_T("asdkpolyobj.dbx"), 0))
			return AcRx::kRetError;

        acrxUnlockApplication(pkt);		// Try to allow unloading
		acrxDynamicLinker->registerAppMDIAware(pkt);
        moduleHandle = pkt;
        // If match app server isn't present, then create and attach
        // a dynamic linker reactor to watch to see if ever loads up
        //
        if (!acrxClassDictionary->at(_T("MatchProperties"))) {
            appEventCatcher = new AppEventCatcher();
            acrxDynamicLinker->addReactor(appEventCatcher);
        }

        initModule();
        updateRegistry();

        if (!hDllAuto)
            hDllAuto = LoadLibrary(_T("OemPolyApp.dll"));
        if (hDllAuto)
        {
            HRESULT (*f)() = (HRESULT (*)()) GetProcAddress(hDllAuto, "initAutomation");
            if (f) f();
        }
        break;

    case AcRx::kUnloadAppMsg:

        if (appEventCatcher != NULL) {
            acrxDynamicLinker->removeReactor(appEventCatcher);
            delete appEventCatcher;
		}
		
        acedRegCmds->removeGroup(_T("ASDK_POLYGON"));
		
        // If we are unloading because AutoCAD is shutting down,
        // then it's possible that the match.arx application is
        // already gone,  so we need to check to see if it's still
        // there.  If it's not,  then we can't remove the protocol
        // extension nor decrement the dependency counter.
        //
		AcRxObject* pTemp;
        if (pTemp = acrxServiceDictionary->at(_T("MatchProperties")))
        {
            // remove the protocol extension.
            AsdkPoly::desc()->delX(AsdkPolyMatchProp::desc());
            delete pMatchPoly;

            AcRxService *pSvc = AcRxService::cast(pTemp);
          
            if (pSvc != NULL)
                pSvc->removeDependency();
        }
        
        //try to unload the object definition
        acrxUnloadModule(_T("asdkpolyobj.dbx"));

        acrxUnloadModule(acGeomentObjDbxFile);

        if (hDllAuto)
        {
            HRESULT (*f)() = (HRESULT (*)()) GetProcAddress(hDllAuto, "exitAutomation");
            if (f) f();
        }
        break;
   }
   return AcRx::kRetOK;
}
