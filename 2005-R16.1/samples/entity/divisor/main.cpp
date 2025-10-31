//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
#pragma warning( disable : 4101 )  // Disable warning message for unreferenced local variables

#include <acutads.h>
#include <aced.h>
#include <dbmain.h>
#include <dbents.h>
#include <dbpl.h>
#include <dbosnap.h>
#include <rxregsvc.h>

#include "DivOsnap.h"

void initApp();
void unloadApp();

AsdkDivOsnapMode<3> thirdMode( "THIrd","_THIrd","Third of length", "1/3" );
AsdkDivOsnapMode<4> fourthMode( "FOUrth","_FOUrth","Quarter of length", "1/4" );
AsdkDivOsnapMode<5> fifthMode( "FIFth","_FIFth","Fifth of length", "1/5" );

void
snapToPolylineSegments()
{
    acutPrintf("\nDivisor object snap will snap to polyline segments.");
    ASDK_DIVISOR_SNAP_TO_SEG(3);
    ASDK_DIVISOR_SNAP_TO_SEG(4);
    ASDK_DIVISOR_SNAP_TO_SEG(5);
}

void
snapToWholePolyline()
{
    acutPrintf("\nDivisor object snap will snap to whole polyline.");
    ASDK_DIVISOR_SNAP_TO_PLINE(3);
    ASDK_DIVISOR_SNAP_TO_PLINE(4);
    ASDK_DIVISOR_SNAP_TO_PLINE(5);
}

// Put the boilerplate calls here, rather than in DivOsnapInfo.cpp/.h
// as we want to make one per actual class (i.e. one per template instance)
ACRX_NO_CONS_DEFINE_MEMBERS( AsdkDivOsnapInfo<3>, AcDbCustomOsnapInfo );
ACRX_NO_CONS_DEFINE_MEMBERS( AsdkDivOsnapInfo<4>, AcDbCustomOsnapInfo );
ACRX_NO_CONS_DEFINE_MEMBERS( AsdkDivOsnapInfo<5>, AcDbCustomOsnapInfo );

void
initApp()
{
    acedRegCmds->addCommand( "ASDK_DIVISOR", "ASDK_SNAP2PLINE",    "SNAP2PLINE",   ACRX_CMD_TRANSPARENT, snapToWholePolyline );
    acedRegCmds->addCommand( "ASDK_DIVISOR", "ASDK_SNAP2SEG",      "SNAP2SEG",     ACRX_CMD_TRANSPARENT, snapToPolylineSegments );

    // Add parent protocol extension class to hierarchy
    AsdkDivOsnapInfo<3>::rxInit();
    AsdkDivOsnapInfo<4>::rxInit();
    AsdkDivOsnapInfo<5>::rxInit();
    acrxBuildClassHierarchy();

    ASDK_DEFINE_DIVISOR_OSNAP(3,thirdMode,"_third");
    ASDK_DEFINE_DIVISOR_OSNAP(4,fourthMode,"_fourth");
    ASDK_DEFINE_DIVISOR_OSNAP(5,fifthMode,"_fifth");

    snapToWholePolyline();
}

void
unloadApp()
{
    acedRegCmds->removeGroup( "ASDK_DIVISOR" );

    ASDK_REMOVE_DIVISOR_OSNAP(3,thirdMode);
    ASDK_REMOVE_DIVISOR_OSNAP(4,fourthMode);
    ASDK_REMOVE_DIVISOR_OSNAP(5,fifthMode);

    deleteAcRxClass( AsdkDivOsnapInfo<3>::desc() );
    deleteAcRxClass( AsdkDivOsnapInfo<4>::desc() );
    deleteAcRxClass( AsdkDivOsnapInfo<5>::desc() );
}

extern "C" __declspec(dllexport) AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void *p)
{
    switch (msg)
    {
    case AcRx::kInitAppMsg:
        acrxRegisterAppMDIAware(p);
        acrxUnlockApplication(p);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
        break;
    }
    return AcRx::kRetOK;
}
