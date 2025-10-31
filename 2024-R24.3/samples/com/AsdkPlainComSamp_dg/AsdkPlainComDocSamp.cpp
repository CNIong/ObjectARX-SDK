//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
// AsdkPlainComSamp.cpp
//
// This example shows how to use COM by itself (without MFC), to access
// the AutoCAD ActiveX Automation APIs.
//
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#pragma warning( disable : 4278 )
#import "acax24ENU.tlb" no_implementation raw_interfaces_only named_guids
#pragma warning( default : 4278 )

#include <rxregsvc.h>
#include <aced.h>
#include <adslib.h>
#include "tchar.h"



static bool bIsMenuLoaded = false;

void
addCircleThroughCom()
{
    AutoCAD::IAcadApplication *pAcad;
    AutoCAD::IAcadDocument *pDoc;
    AutoCAD::IAcadModelSpace *pMSpace;

    HRESULT hr = NOERROR;
    LPUNKNOWN pUnk = NULL;
    LPDISPATCH pAcadDisp = acedGetIDispatch(true); 
	if(pAcadDisp==NULL)
		return;
	
	hr = pAcadDisp->QueryInterface(AutoCAD::IID_IAcadApplication,(void**)&pAcad);
	pAcadDisp->Release();
	if (FAILED(hr))
		return;

	hr = pAcad->get_ActiveDocument(&pDoc);
	pAcad->Release();
	if (FAILED(hr))
		return;

	hr = pDoc->get_ModelSpace(&pMSpace);
	pDoc->Release();
	if (FAILED(hr))
		return;


    SAFEARRAYBOUND rgsaBound;
    rgsaBound.lLbound = 0L;
    rgsaBound.cElements = 3;
    long i;
    SAFEARRAY* pStartPoint = NULL;
    pStartPoint = SafeArrayCreate(VT_R8, 1, &rgsaBound);

    i = 0;
    double value = 4.0;
    SafeArrayPutElement(pStartPoint, &i, &value);
    
    i = 1;
    value = 2.0;
    SafeArrayPutElement(pStartPoint, &i, &value);
    
    i = 2;
    value = 0.0;
    SafeArrayPutElement(pStartPoint, &i, &value);
    
    VARIANT pt1;
    pt1.vt = VT_ARRAY | VT_R8;
    pt1.parray = pStartPoint;

    AutoCAD::IAcadCircle *pCircle;
    pMSpace->AddCircle(pt1, 2.0, &pCircle);
	VariantClear(&pt1);
    pMSpace->Release();
}

void
addMenuThroughCom()
{

    AutoCAD::IAcadApplication *pAcad;
    AutoCAD::IAcadMenuBar *pMenuBar;
    AutoCAD::IAcadMenuGroups *pMenuGroups;
    AutoCAD::IAcadMenuGroup *pMenuGroup;
    AutoCAD::IAcadPopupMenus *pPopUpMenus;
    AutoCAD::IAcadPopupMenu *pPopUpMenu;
    AutoCAD::IAcadPopupMenuItem *pPopUpMenuItem;

    HRESULT hr = NOERROR;
    LPUNKNOWN pUnk = NULL;
	LPDISPATCH pAcadDisp = acedGetIDispatch(true); 
	if(pAcadDisp==NULL)
		return;

	hr = pAcadDisp->QueryInterface(AutoCAD::IID_IAcadApplication,(void**)&pAcad);
    pAcadDisp->Release();
	if (FAILED(hr))
        return;

    pAcad->put_Visible(true);
	pAcad->get_MenuBar(&pMenuBar);
    pAcad->get_MenuGroups(&pMenuGroups);
    pAcad->Release();
    long numberOfMenus;
    pMenuBar->get_Count(&numberOfMenus);
    pMenuBar->Release();

    VARIANT index;
    VariantInit(&index);
    V_VT(&index) = VT_I4;
    V_I4(&index) = 0;

    pMenuGroups->Item(index, &pMenuGroup);
    pMenuGroups->Release();
    
    pMenuGroup->get_Menus(&pPopUpMenus);
    pMenuGroup->Release();

    WCHAR wstrMenuName[256];
   _tcscpy(wstrMenuName, L"AsdkComAccess");

    // Enables the menu to be loaded/unloaded with the same command.
    if (!bIsMenuLoaded) {
        pPopUpMenus->Add(wstrMenuName, &pPopUpMenu);

        if (pPopUpMenu != NULL) {

            WCHAR wstrMenuItemName[256];
            WCHAR wstrMenuItemMacro[256];
            _tcscpy(wstrMenuItemName, L"&Add A ComCircle");
            _tcscpy(wstrMenuItemMacro, L"AsdkComCircle ");

            VariantInit(&index);
            V_VT(&index) = VT_I4;
            V_I4(&index) = 0;
            pPopUpMenu->AddMenuItem(index, wstrMenuItemName, wstrMenuItemMacro, &pPopUpMenuItem);

            VariantInit(&index);
            V_VT(&index) = VT_I4;
            V_I4(&index) = 1;
            pPopUpMenu->AddSeparator(index, &pPopUpMenuItem);

            _tcscpy(wstrMenuItemName, L"Auto&LISP Example");
            _tcscpy(wstrMenuItemMacro, L"(prin1 \"Hello\") ");

            VariantInit(&index);
            V_VT(&index) = VT_I4;
            V_I4(&index) = 2;
            pPopUpMenu->AddMenuItem(index, wstrMenuItemName, wstrMenuItemMacro, &pPopUpMenuItem);

            VariantInit(&index);
            V_VT(&index) = VT_I4;
            V_I4(&index) = numberOfMenus - 2;
            pPopUpMenu->InsertInMenuBar(index);
    
            pPopUpMenuItem->Release();
            bIsMenuLoaded = true;
        } else {
            acutPrintf(_T("\nMenu not created."));
        }
    } else {
        VariantInit(&index);
        V_VT(&index) = VT_BSTR;
        V_BSTR(&index) = wstrMenuName;
        pPopUpMenus->RemoveMenuFromMenuBar(index);
        VariantClear(&index);
        bIsMenuLoaded = false;
    }

    pPopUpMenus->Release();
}


void
initApp()
{
    ads_printf(_T("AsdkComAccess ARX Test; Type ComMenu or ComCircle to execute"));

    // register a command with the AutoCAD command mechanism
    //
    acedRegCmds->addCommand(_T("AsdkComAccess_COMMANDS"), _T("AsdkComCircle"), _T("ComCircle"), ACRX_CMD_MODAL, addCircleThroughCom);
    acedRegCmds->addCommand(_T("AsdkComAccess_COMMANDS"), _T("AsdkComMenu"), _T("ComMenu"), ACRX_CMD_MODAL, addMenuThroughCom);
}


void unloadApp()
{
    
    
    // Remove the command group added via acedRegCmds->addCommand
    //
    acedRegCmds->removeGroup(_T("AsdkComAccess_COMMANDS"));

}

extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
        acrxDynamicLinker->registerAppMDIAware(appId);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
        break;
    case AcRx::kLoadDwgMsg:

        break;
    case AcRx::kUnloadDwgMsg:

        break;
    case AcRx::kInvkSubrMsg:

        break;
    default:
        ;
    }
    return AcRx::kRetOK;
}

