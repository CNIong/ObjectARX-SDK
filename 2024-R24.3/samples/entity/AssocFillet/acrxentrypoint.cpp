//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// ARX application initialization.
//
//////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "arxEntryPoint.h"
#include "AssocFilletActionBody.h"

void assocFilletCommandUI();
    

class AssocFilletSampleApp : public AcRxArxApp 
{
public:
    virtual AcRx::AppRetCode On_kInitAppMsg(void* pkt) override
    {
        const AcRx::AppRetCode retCode = AcRxArxApp::On_kInitAppMsg(pkt);
        acedRegCmds->addCommand(L"ASSOCFILLETSAMPLE", L"ASSOCFILLET", L"ASSOCFILLET", ACRX_CMD_MODAL, assocFilletCommandUI);
        AssocFilletActionBody::rxInit();
        acrxBuildClassHierarchy();
        return retCode;
    }

    virtual AcRx::AppRetCode On_kUnloadAppMsg(void* pkt) override
    {
        const AcRx::AppRetCode retCode = AcRxArxApp::On_kUnloadAppMsg(pkt);
        deleteAcRxClass(AssocFilletActionBody::desc());
        acrxBuildClassHierarchy();
        acedRegCmds->removeGroup(L"ASSOCFILLETSAMPLE");
        return retCode;
    }

    virtual void RegisterServerComponents() override {}
};

IMPLEMENT_ARX_ENTRYPOINT(AssocFilletSampleApp)
