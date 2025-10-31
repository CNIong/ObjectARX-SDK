// (C) Copyright 1996-2007 by Autodesk, Inc. 
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
// DESCRIPTION:
//
// The main ObjectARX entry point for the AcBr sample app.


// AutoCAD editor service api support
// (application command registration)
#include "brsample_pch.h"  //precompiled header


// include here



extern "C" {
    // locally defined entry point invoked by ObjectARX.
    AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt);
}


static void initModule();
static void unloadModule();

#define STRINGIZE_WORKER( x ) _T(# x)
#define STRINGIZE( x ) STRINGIZE_WORKER(x)

AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
		acrxDynamicLinker->loadModule(STRINGIZE(DLLNAME_ACBR), 1);
        initModule();
        acrxUnlockApplication(pkt); // try to allow unloading
		acrxRegisterAppMDIAware(pkt);
        break ;
    case AcRx::kUnloadAppMsg:
		unloadModule();
        acrxDynamicLinker->unloadModule(STRINGIZE(DLLNAME_ACBR));
        break ;
    default:
        break ;
    }
    return AcRx::kRetOK;
}


static void
initModule()
{
    // Register commands to exemplify the Autodesk Boundary
	// Representation Library

    // this command implemented in brcount.cpp
    acedRegCmds->addCommand(ACRX_T("BREP_CMD"), 
                            ACRX_T("BRCOUNT"),
                            ACRX_T("BRCOUNT"),
                            ACRX_CMD_TRANSPARENT,
                            &countSubents);

    // this command implemented in brdump.cpp
    acedRegCmds->addCommand(ACRX_T("BREP_CMD"), 
                            ACRX_T("BRDUMP"),
                            ACRX_T("BRDUMP"),
                            ACRX_CMD_TRANSPARENT,
                            &dumpModel);

    // this command implemented in brtrmsrf.cpp
    acedRegCmds->addCommand(ACRX_T("BREP_CMD"), 
                            ACRX_T("BRTRMSRF"),
                            ACRX_T("BRTRMSRF"),
                            ACRX_CMD_TRANSPARENT,
                            &trimSurface);

	// this command implemented in brbblock.cpp
    acedRegCmds->addCommand(ACRX_T("BREP_CMD"), 
                            ACRX_T("BRBBLOCK"),
                            ACRX_T("BRBBLOCK"),
                            ACRX_CMD_TRANSPARENT,
                            &dumpBblock);

	// this command implemented in brptcnt.cpp
    acedRegCmds->addCommand(ACRX_T("BREP_CMD"), 
                            ACRX_T("BRPTCNT"),
                            ACRX_T("BRPTCNT"),
                            ACRX_CMD_TRANSPARENT,
                            &pointContainment);

    // this command implemented in brlncnt.cpp
    acedRegCmds->addCommand(ACRX_T("BREP_CMD"), 
                            ACRX_T("BRLNCNT"),
                            ACRX_T("BRLNCNT"),
                            ACRX_CMD_TRANSPARENT,
                            &lineContainment);

    // this command implemented in brmmesh.cpp
    acedRegCmds->addCommand(ACRX_T("BREP_CMD"), 
                            ACRX_T("BRMESH"),
                            ACRX_T("BRMESH"),
                            ACRX_CMD_TRANSPARENT,
                            &meshModel);
}


static void
unloadModule()
{
    // Un-register commands to test the Autodesk Boundary
	// Representation Library
    acedRegCmds->removeGroup(ACRX_T("BREP_CMD"));
}

