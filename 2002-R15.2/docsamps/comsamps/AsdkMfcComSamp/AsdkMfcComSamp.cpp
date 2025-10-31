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

// AsdkMfcComSamp.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "AsdkMfcComSamp.h"

#include <rxregsvc.h>
#include <aced.h>
#include <adslib.h>
#include <rxmfcapi.h>
#include <AcExtensionModule.h>  // Utility class for extension dlls

#include "acad1.h"



////////////////////////////////////////////////////////////////////////////
//
// Define the sole extension module object.
AC_IMPLEMENT_EXTENSION_MODULE(ThisDLL);

// Now you can use the CAcModuleResourceOverride class in
// your application to switch to the correct resource instance.
// Please see the ObjectARX Documentation for more details

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        // Extension DLL one time initialization
        ThisDLL.AttachInstance(hInstance);
    } else if (dwReason == DLL_PROCESS_DETACH) {
        // Terminate the library before destructors are called
        ThisDLL.DetachInstance();
    }
    return TRUE;    // ok
}

void MfcComCircle()
{
    TRY
    {
        IAcadApplication IApp;
        IAcadDocument IDoc;
        IAcadModelSpace IMSpace;

        IDispatch *pDisp = acedGetAcadWinApp()->GetIDispatch(TRUE);

        IApp.AttachDispatch(pDisp);
        pDisp = IApp.GetActiveDocument();
        IDoc.AttachDispatch(pDisp);
        pDisp = IDoc.GetModelSpace();
        IMSpace.AttachDispatch(pDisp);

        SAFEARRAYBOUND rgsaBound;
        rgsaBound.lLbound = 0L;
        rgsaBound.cElements = 3;

        long i;

        SAFEARRAY* pStartPoint = NULL;

        pStartPoint = SafeArrayCreate(VT_R8, 1, &rgsaBound);

        i = 0;
        double value = 4.0;
        SafeArrayPutElement(pStartPoint, &i, &value);

        value = 2.0;
        i = 1;
        SafeArrayPutElement(pStartPoint, &i, &value);

        value = 0.0;
        i = 2;
        SafeArrayPutElement(pStartPoint, &i, &value);

        VARIANT pt1;
        VariantInit(&pt1);
        V_VT(&pt1) = VT_ARRAY | VT_R8;
        V_ARRAY(&pt1) = pStartPoint;

        IMSpace.AddCircle(pt1, 2.0);
		VariantClear(&pt1);
    }
    CATCH(COleDispatchException,e)
    {
        e->ReportError();
        e->Delete();
    }
    END_CATCH;
}

void
addMenuThroughMfcCom()
{
    TRY
    {
        IAcadApplication IAcad(acedGetAcadWinApp()->GetIDispatch(TRUE));

        IAcadMenuBar IMenuBar(IAcad.GetMenuBar());

        long numberOfMenus;
        numberOfMenus = IMenuBar.GetCount();

        IAcadMenuGroups IMenuGroups(IAcad.GetMenuGroups());

        VARIANT index;
        VariantInit(&index);
        V_VT(&index) = VT_I4;
        V_I4(&index) = 0;

        IAcadMenuGroup IMenuGroup(IMenuGroups.Item(index));

        IAcadPopupMenus IPopUpMenus(IMenuGroup.GetMenus());

        CString cstrMenuName = "AsdkComAccess";

        VariantInit(&index);
        V_VT(&index) = VT_BSTR;
        V_BSTR(&index) = cstrMenuName.AllocSysString();

        IDispatch* pDisp;

        //see if the menu is already there
        TRY{pDisp = IPopUpMenus.Item(index); pDisp->AddRef();} CATCH(COleDispatchException,e){}END_CATCH;

        if (pDisp==NULL) {
            //create it
            IAcadPopupMenu IPopUpMenu(IPopUpMenus.Add(cstrMenuName));

            VariantInit(&index);
            V_VT(&index) = VT_I4;
            V_I4(&index) = 0;
            IPopUpMenu.AddMenuItem(index, "&Add A ComCircle", "_AsdkMfcComCircle ");

            VariantInit(&index);
            V_VT(&index) = VT_I4;
            V_I4(&index) = 1;
            IPopUpMenu.AddSeparator(index);

            VariantInit(&index);
            V_VT(&index) = VT_I4;
            V_I4(&index) = 2;
            IPopUpMenu.AddMenuItem(index, "Auto&LISP Example", "(prin1 \"Hello\") ");

            pDisp = IPopUpMenu.m_lpDispatch;
            pDisp->AddRef();
        }

        IAcadPopupMenu IPopUpMenu(pDisp);
        if (!IPopUpMenu.GetOnMenuBar())
        {
            VariantInit(&index);
            V_VT(&index) = VT_I4;
            V_I4(&index) = numberOfMenus - 2;;
            IPopUpMenu.InsertInMenuBar(index);
        }
        else
        {
            VariantInit(&index);
            V_VT(&index) = VT_BSTR;
            V_BSTR(&index) = cstrMenuName.AllocSysString();
            IPopUpMenus.RemoveMenuFromMenuBar(index);
			VariantClear(&index);
        }
        pDisp->Release();
    }
    CATCH(COleDispatchException,e)
    {
        e->ReportError();
        e->Delete();
    }
    END_CATCH;

}

static void initApp()
{

  acedRegCmds->addCommand("ASDK_MFC_COM",
                          "AsdkMfcComCircle",
                          "MfcComCircle",
                          ACRX_CMD_MODAL,
                          MfcComCircle);

  acedRegCmds->addCommand("ASDK_MFC_COM",
                          "AsdkMfcComMenu",
                          "MfcComMenu",
                          ACRX_CMD_MODAL,
                          addMenuThroughMfcCom);

}


static void unloadApp()
{

  // Do other cleanup tasks here
  acedRegCmds->removeGroup("ASDK_MFC_COM");

}


extern "C" AcRx::AppRetCode acrxEntryPoint( AcRx::AppMsgCode msg, void* appId)
{
  switch( msg )
  {
    case AcRx::kInitAppMsg:

      acrxDynamicLinker->unlockApplication(appId);
      acrxDynamicLinker->registerAppMDIAware(appId);
      initApp();
      break;
    case AcRx::kUnloadAppMsg:
      unloadApp();
      break;

    default:
      break;
  }
  return AcRx::kRetOK;
}

