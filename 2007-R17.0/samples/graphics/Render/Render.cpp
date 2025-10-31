//
// (C) Copyright 2005-2006 by Autodesk, Inc. 
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
#include "RenderCmds.h"

#define kpSceneService     _T(/*MSG0*/"SceneUI_Service")
#define kpSceneOEModule      _T(/*MSG0*/"AcSceneOE.dbx")

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch(msg)
    {
    case AcRx::kInitAppMsg:
        acrxUnlockApplication(appId);
        acrxRegisterAppMDIAware(appId);

        // check if the object enabler is loaded or not.
        // if not, load it.
        if (!::acrxAppIsLoaded(kpSceneService))
        {
            if (!acrxLoadModule(kpSceneOEModule, false, true))
                return AcRx::kRetError;
        }
        //bump the reference count 
        acrxLoadModule(kpSceneOEModule, false, false);

        acedRegCmds->addCommand(_T("RENDER_API_SAMPLE"), _T("ObjsToRender"), _T("OTR"), ACRX_CMD_MODAL, objectsToRender);
        acedRegCmds->addCommand(_T("RENDER_API_SAMPLE"), _T("AddLights"), _T("AL"), ACRX_CMD_MODAL, addLights);
        acedRegCmds->addCommand(_T("RENDER_API_SAMPLE"), _T("AddSunAndBackground"), _T("ASB"), ACRX_CMD_MODAL, addSunAndBackground);
        acedRegCmds->addCommand(_T("RENDER_API_SAMPLE"), _T("SetRenderSettings"), _T("SRS"), ACRX_CMD_MODAL, setRenderSettings);
        acedRegCmds->addCommand(_T("RENDER_API_SAMPLE"), _T("ListRenderSettings"), _T("LRS"), ACRX_CMD_MODAL, listRenderSettings);
        break;

    case AcRx::kUnloadAppMsg:
        acedRegCmds->removeGroup(_T("RENDER_API_SAMPLE"));
        //decrement the reference count on the server
        acrxUnloadModule(kpSceneOEModule);
        break;
    }

    return AcRx::kRetOK;
}
