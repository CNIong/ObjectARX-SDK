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

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif


#include <afxdisp.h>        // MFC OLE automation classes



#include "adslib.h"
#include "acadi.h"
#include "rxmfcapi.h"

#include "acadi_i.c"


bool getApplication(LPDISPATCH * pVal)
{
    LPDISPATCH pDispatch = acedGetAcadWinApp()->GetIDispatch(TRUE);
    if (pDispatch == NULL)
        return false;
    *pVal = pDispatch;
    return true;
}


bool getAcadMenuGroup(IAcadMenuGroup  **pVal)
{

    IAcadApplication *acadApp = NULL;
    LPDISPATCH  pDisp = NULL;

    if (!getApplication(&pDisp))
        return false;

    HRESULT hr = S_OK;
    hr = pDisp->QueryInterface(IID_IAcadApplication, (LPVOID*)&acadApp);
    if (FAILED(hr))
        return false;


    LPDISPATCH  pTempDisp = NULL;
    IAcadMenuGroups *mnuGrps = NULL;
    long cnt = 0;

    //get the menu groups
    hr = acadApp->get_MenuGroups(&mnuGrps);
    if (FAILED(hr))
    {
        acadApp->Release();
        return false;
    }
    mnuGrps->get_Count(&cnt);


    //get AutoCAD menu group. say it is index 0.
    IAcadMenuGroup *mnuGrp = NULL;

    VARIANT  vtName;
    vtName.vt = VT_I4;
    BSTR  grpName;
    bool found = false ;
    for (long i=0; i < cnt; i++)
    {
        vtName.lVal = i;
        hr = mnuGrps->Item(vtName, &mnuGrp);
        if (FAILED(hr))
            return false;


        hr  = mnuGrp->get_Name(&grpName);
        CString cgrpName(grpName);
        if (cgrpName.CompareNoCase(_T("Acad"))==0) 
        {
            found = true;
            *pVal = mnuGrp;
            break;
        }
    }

    acadApp->Release();
    return found;
}


void CreateToolbars()
{
    IAcadMenuGroup *mnuGrp = NULL;
    if (!getAcadMenuGroup(&mnuGrp))
        return ;
    //now get all the popup menus 
    IAcadToolbars  *tlbrs = NULL;
    HRESULT hr = S_OK;
    hr = mnuGrp->get_Toolbars(&tlbrs);
    mnuGrp->Release();
    //let us create toolbars for polysamp
    IAcadToolbar  *tlbr = NULL;
    hr = tlbrs->Add(L"POLYSAMP APPLICATION", &tlbr);
    if FAILED(hr)
        return;
    tlbrs->Release();
    //now add toolbar buttons
    IAcadToolbarItem *button=NULL;
    VARIANT index;
    index.vt = VT_I4;
    index.lVal = 100l;

    VARIANT vtFalse;
    vtFalse.vt = VT_BOOL;
    vtFalse.boolVal = VARIANT_FALSE;

    TCHAR szFileName[MAX_PATH];
    GetModuleFileName(GetModuleHandle(_T("asdkPolyUi.arx")),szFileName,MAX_PATH);
    CString csPath(szFileName);
    csPath=csPath.Left(csPath.ReverseFind(_T('\\')));
    //x64 binaries are created within x64\ folder
#if defined(_WIN64) || defined(_AC64)
    csPath=csPath.Left(csPath.ReverseFind(_T('\\')));
#endif
    csPath=csPath.Left(csPath.ReverseFind(_T('\\'))+1);

    hr = tlbr->AddToolbarButton(index, L"POLY", L"Creates poly entity", L"_poly ", vtFalse, &button);
    hr=button->SetBitmaps(CComBSTR(csPath+_T("1_Poly1.ico")),CComBSTR(csPath+_T("1_Poly1.ico")));
    button->Release();
    hr = tlbr->AddToolbarButton(index, L"DRAGPOLY", L"Creates poly entity using dragging", L"_dragpoly ", vtFalse, &button);
    hr=button->SetBitmaps(CComBSTR(csPath+_T("1_Poly2.ico")),CComBSTR(csPath+_T("1_Poly2.ico")));
    button->Release();
    hr = tlbr->AddToolbarButton(index, L"POLYEDIT", L"Edits poly entity", L"_POLYEDIT ", vtFalse, &button);
    hr=button->SetBitmaps(CComBSTR(csPath+_T("1_Poly3.ico")),CComBSTR(csPath+_T("1_Poly3.ico")));
    button->Release();
    hr = tlbr->AddToolbarButton(index, L"TRANSACT", L"Test Transaction on  poly entity", L"_TRANSACT ", vtFalse, &button);
    hr=button->SetBitmaps(CComBSTR(csPath+_T("1_Poly4.ico")),CComBSTR(csPath+_T("1_Poly4.ico")));
    button->Release();
    hr = tlbr->AddToolbarButton(index, L"HILITPOLY", L"Hilight poly entity", L"_HILITPOLY ", vtFalse, &button);
    hr=button->SetBitmaps(CComBSTR(csPath+_T("1_Poly5.ico")),CComBSTR(csPath+_T("1_Poly5.ico")));
    button->Release();
    hr = tlbr->AddToolbarButton(index, L"HILITSOLID", L"Hilight solid entity", L"_HILITSOLID ", vtFalse, &button);
    hr=button->SetBitmaps(CComBSTR(csPath+_T("1_Poly6.ico")),CComBSTR(csPath+_T("1_Poly6.ico")));
    button->Release();
    hr = tlbr->AddToolbarButton(index, L"CREATEINSERT", L"Creates inserted entity", L"_CREATEINSERT ", vtFalse, &button);
    hr=button->SetBitmaps(CComBSTR(csPath+_T("1_Poly7.ico")),CComBSTR(csPath+_T("1_Poly7.ico")));
    button->Release();
    hr = tlbr->AddToolbarButton(index, L"HILITINSERT", L"Highlight inserted entity", L"_HILITINSERT ", vtFalse, &button);
    hr=button->SetBitmaps(CComBSTR(csPath+_T("1_Poly8.ico")),CComBSTR(csPath+_T("1_Poly8.ico")));
    button->Release();
    hr = tlbr->AddToolbarButton(index, L"USEDRAGDATA", L"Test user dragging mechanism", L"_USEDRAGDATA ", vtFalse, &button);
    hr=button->SetBitmaps(CComBSTR(csPath+_T("1_Poly1.ico")),CComBSTR(csPath+_T("1_Poly1.ico")));
    button->Release();


    tlbr->Dock(acToolbarDockLeft);
    tlbr->Release();
    return;


}


void CreateMenus()
{

    IAcadMenuGroup *mnuGrp = NULL;
    if (!getAcadMenuGroup(&mnuGrp))
        return ;

    //now get all the popup menus 
    IAcadPopupMenus  *mnus = NULL;
    HRESULT hr = S_OK;
    hr = mnuGrp->get_Menus(&mnus);
    long cnt = 0l;
    hr = mnus->get_Count(&cnt);
    mnuGrp->Release();

    //now get Tools menu
    IAcadPopupMenu *toolsMenu = NULL;
    BSTR   tempName;
    VARIANT vtName;
    bool found = false;
    for (long i=0; i < cnt; i++)
    {
        vtName.vt = VT_I4;
        vtName.lVal = i;
        hr = mnus->Item(vtName, &toolsMenu);
        if (FAILED(hr))
            return ;

        hr = toolsMenu->get_NameNoMnemonic(&tempName);
        CString mnuName(tempName);

        if(mnuName.CompareNoCase(_T("Tools"))==0)
        {
            found = true;
            break;
        }
    }
    mnus->Release();
    if (!found)
    {
        acutPrintf(_T("Could not found tools menu\n"));
        return;
    }

    hr = toolsMenu->get_Count(&cnt);
    VARIANT  vtIndex;
    vtIndex.vt = VT_I4;
    vtIndex.lVal = cnt + 1;
    IAcadPopupMenuItem  *item1 = NULL;
    hr = toolsMenu->AddSeparator(vtIndex, &item1);
    item1->Release();
    vtIndex.lVal = cnt + 2;
    IAcadPopupMenu *polyMnu = NULL;
    hr = toolsMenu->AddSubMenu(vtIndex, L"Polysamp Application", &polyMnu);
    if(FAILED(hr))
        return;
    toolsMenu->Release();


    IAcadPopupMenuItem *polycmds = NULL;
    vtIndex.lVal = 0;
    hr = polyMnu->AddMenuItem(vtIndex, L"POLY", L"_poly ", &polycmds);

    vtIndex.lVal = 1;
    hr = polyMnu->AddMenuItem(vtIndex, L"POLYEDIT", L"_polyedit ", &polycmds);
    vtIndex.lVal = 2;
    hr = polyMnu->AddMenuItem(vtIndex, L"TRANSACT", L"_TRANSACT ", &polycmds);
    vtIndex.lVal = 3;
    hr = polyMnu->AddMenuItem(vtIndex, L"HILITPOLY", L"_HILITPOLY ", &polycmds);
    vtIndex.lVal = 4;
    hr = polyMnu->AddMenuItem(vtIndex, L"CREATEINSERT", L"_CREATEINSERT ", &polycmds);
    vtIndex.lVal = 5;
    hr = polyMnu->AddMenuItem(vtIndex, L"HILITINSERT", L"_HILITINSERT ", &polycmds);
    vtIndex.lVal = 6;
    hr = polyMnu->AddMenuItem(vtIndex, L"USEDRAGDATA", L"_USEDRAGDATA ", &polycmds);
    vtIndex.lVal = 7;
    hr = polyMnu->AddMenuItem(vtIndex, L"HILITINSERT", L"_HILITINSERT ", &polycmds);
    vtIndex.lVal = 8;
    hr = polyMnu->AddMenuItem(vtIndex, L"HILITINSERT", L"_HILITINSERT ", &polycmds);
//    polycmds->Release();
    polyMnu->Release();

    return;
}


void CleanUpMenus()
{
    IAcadMenuGroup *mnuGrp = NULL;
    if (!getAcadMenuGroup(&mnuGrp))
        return ;

    //now get all the popup menus 
    IAcadPopupMenus  *mnus = NULL;
    HRESULT hr = S_OK;
    hr = mnuGrp->get_Menus(&mnus);
    long cnt = 0l;
    hr = mnus->get_Count(&cnt);
    mnuGrp->Release();

    //now get Tools menu
    IAcadPopupMenu *toolsMenu = NULL;
    BSTR   tempName;
    VARIANT vtName;
    bool found = false;
    long i;
    for (i=0; i < cnt; i++)
    {
        vtName.vt = VT_I4;
        vtName.lVal = i;
        hr = mnus->Item(vtName, &toolsMenu);
        if (FAILED(hr))
            return ;

        hr = toolsMenu->get_NameNoMnemonic(&tempName);
        CString mnuName(tempName);
        SysFreeString(tempName);
        if(mnuName.CompareNoCase(_T("Tools"))==0)
        {
            found = true;
            break;
        }
    }
    mnus->Release();

    if (!found)
    {
        acutPrintf(_T("Could not found tools menu\n"));
        return;
    }

    hr = toolsMenu->get_Count(&cnt);
    VARIANT vIndex;
    vIndex.vt = VT_I4;
    vIndex.lVal = cnt;
    IAcadPopupMenu  *polySampCmds = NULL;
    IAcadPopupMenuItem *cmd1 = NULL;
    long index = 0l;
    for ( i=0; i < cnt; i++)
    {
        vtName.vt = VT_I4;
        vtName.lVal = i;
        hr = toolsMenu->Item(vtName, &cmd1);
        hr = cmd1->get_Label(&tempName);
        CString mnuName(tempName);
        SysFreeString(tempName);
        if(mnuName.CompareNoCase(_T("PolySamp Application"))==0)
        {    index = i-1;
            break;
        }
    }

    vIndex.vt = VT_I4;
    vIndex.lVal = index;
    //Remove all the menus loaded by this program
    IAcadPopupMenuItem *tempItem = NULL;
    hr = toolsMenu->Item(vIndex, &tempItem);
    hr = tempItem->Delete();
    tempItem->Release();
    hr = toolsMenu->Item(vIndex, &tempItem);
    hr = tempItem->Delete();
    tempItem->Release();
    toolsMenu->Release();


    return;
}



void CleanUpToolbars()
{
    IAcadMenuGroup *mnuGrp = NULL;
    if (!getAcadMenuGroup(&mnuGrp))
        return ;


    IAcadToolbars  *tlbrs = NULL;
    HRESULT hr = S_OK;

    hr = mnuGrp->get_Toolbars(&tlbrs);
    mnuGrp->Release();

    long cnt = 0;
    hr = tlbrs->get_Count(&cnt);

    IAcadToolbar *polyTlbr = NULL;
    BSTR  tempName;

    VARIANT vtName;
    for ( long i=0; i < cnt; i++)
    {
        vtName.vt = VT_I4;
        vtName.lVal = i;
        hr = tlbrs->Item(vtName, &polyTlbr);
        hr = polyTlbr->get_Name(&tempName);
        CString tlbrName(tempName);
        SysFreeString(tempName);
        if(tlbrName.CompareNoCase(_T("POLYSAMP APPLICATION"))==0)
        {
            polyTlbr->Delete();
            //can not call following because delete has already removed it.
            //    polyTlbr->Release();
            break;
        }
        else
            polyTlbr->Release();

    }

    tlbrs->Release();
    return;
}



void UpdateUserInterfaceForPolySamp()
{
    CreateMenus();
    CreateToolbars();
}

void CleanUpUserInterfaceForPolySamp()
{
    CleanUpMenus();
    CleanUpToolbars();

}
