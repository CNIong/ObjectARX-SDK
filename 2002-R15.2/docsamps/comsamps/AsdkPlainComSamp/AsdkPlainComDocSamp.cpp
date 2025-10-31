// (C) Copyright 1999 by Autodesk, Inc. 
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
// AsdkPlainComSamp.cpp
//
// This example shows how to use COM by itself (without MFC), to access
// the AutoCAD ActiveX Automation APIs.
//

#import "..\\..\\..\\inc\\acad.tlb" no_implementation raw_interfaces_only named_guids

#include <rxregsvc.h>
#include <aced.h>
#include <adslib.h>

static bool bIsMenuLoaded = false;

void
addCircleThroughCom()
{
    AutoCAD::IAcadApplication *pAcad;
    AutoCAD::IAcadDocument *pDoc;
    AutoCAD::IAcadModelSpace *pMSpace;

    HRESULT hr = NOERROR;
    CLSID clsid;
    LPUNKNOWN pUnk = NULL;
    LPDISPATCH pAcadDisp = NULL; 

    hr = ::CLSIDFromProgID(L"AutoCAD.Application", &clsid);
    if (FAILED(hr))
		return;

    if(::GetActiveObject(clsid, NULL, &pUnk) != S_OK)
		return;

    hr = pUnk->QueryInterface(IID_IDispatch, (LPVOID*) &pAcadDisp);
	pUnk->Release();
	if (FAILED(hr))
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
    CLSID clsid;
    LPUNKNOWN pUnk = NULL;
    LPDISPATCH pAcadDisp = NULL; 

    hr = ::CLSIDFromProgID(L"AutoCAD.Application", &clsid);
    if (FAILED(hr))
		return;

    if(::GetActiveObject(clsid, NULL, &pUnk) != S_OK)
		return;

    hr = pUnk->QueryInterface(IID_IDispatch, (LPVOID*) &pAcadDisp);
    pUnk->Release();
	if (FAILED(hr))
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
    MultiByteToWideChar(CP_ACP, 0, "AsdkComAccess", -1, wstrMenuName, 256); 

    // Enables the menu to be loaded/unloaded with the same command.
    if (!bIsMenuLoaded) {
        pPopUpMenus->Add(wstrMenuName, &pPopUpMenu);

        if (pPopUpMenu != NULL) {

            WCHAR wstrMenuItemName[256];
            MultiByteToWideChar(CP_ACP, 0, "&Add A ComCircle", -1, wstrMenuItemName, 256); 
            WCHAR wstrMenuItemMacro[256];
            MultiByteToWideChar(CP_ACP, 0, "AsdkComCircle ", -1, wstrMenuItemMacro, 256); 

            VariantInit(&index);
            V_VT(&index) = VT_I4;
            V_I4(&index) = 0;
            pPopUpMenu->AddMenuItem(index, wstrMenuItemName, wstrMenuItemMacro, &pPopUpMenuItem);

            VariantInit(&index);
            V_VT(&index) = VT_I4;
            V_I4(&index) = 1;
            pPopUpMenu->AddSeparator(index, &pPopUpMenuItem);

            MultiByteToWideChar(CP_ACP, 0, "Auto&LISP Example", -1, wstrMenuItemName, 256); 
            MultiByteToWideChar(CP_ACP, 0, "(prin1 \"Hello\") ", -1, wstrMenuItemMacro, 256); 

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
            acutPrintf("\nMenu not created.");
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
    ads_printf("AsdkComAccess ARX Test; Type ComMenu or ComCircle to execute");

    // register a command with the AutoCAD command mechanism
    //
    acedRegCmds->addCommand("AsdkComAccess_COMMANDS", "AsdkComCircle", "ComCircle", ACRX_CMD_MODAL, addCircleThroughCom);
    acedRegCmds->addCommand("AsdkComAccess_COMMANDS", "AsdkComMenu", "ComMenu", ACRX_CMD_MODAL, addMenuThroughCom);
}


void unloadApp()
{
    
    
    // Remove the command group added via acedRegCmds->addCommand
    //
    acedRegCmds->removeGroup("AsdkComAccess_COMMANDS");

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

