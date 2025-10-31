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
#include <acutads.h>
#include <aced.h>
#include <dbmain.h>
#include <dbents.h>
#include <dbpl.h>
#include <dbosnap.h>
#include <rxregsvc.h>

#include "ThirdOsnapMode.h"
#include "ThirdOsnapInfo.h"

AsdkThirdOsnapMode thirdMode;
bool bSnapToSegments = false;

void
snapToPolylineSegments()
{
    acutPrintf("\nThird object snap will snap to polyline segments.");
    bSnapToSegments = true;
}

void
snapToWholePolyline()
{
    acutPrintf("\nThird object snap will snap to whole polyline.");
    bSnapToSegments = false;
}

void
initApp()
{
    acedRegCmds->addCommand( "ASDK_THIRD", "ASDK_SNAP2PLINE",    "SNAP2PLINE",   ACRX_CMD_TRANSPARENT, snapToWholePolyline );
    acedRegCmds->addCommand( "ASDK_THIRD", "ASDK_SNAP2SEG",      "SNAP2SEG",     ACRX_CMD_TRANSPARENT, snapToPolylineSegments );

    // Add parent protocol extension class description object to hierarchy
    AsdkThirdOsnapInfo::rxInit();
    acrxBuildClassHierarchy();

    // Create the protocol extension objects
    AsdkThirdOsnapEntityInfo *pEntityInfo = new AsdkThirdOsnapEntityInfo;
    AsdkThirdOsnapCurveInfo *pCurveInfo = new AsdkThirdOsnapCurveInfo;
    AsdkThirdOsnapPolylineInfo *pPolylineInfo = new AsdkThirdOsnapPolylineInfo;

    // Register the protocol extension object with parent class object
    AcDbEntity::desc()->addX( AsdkThirdOsnapInfo::desc(), pEntityInfo );
    AcDbCurve::desc()->addX( AsdkThirdOsnapInfo::desc(), pCurveInfo );
    AcDbPolyline::desc()->addX( AsdkThirdOsnapInfo::desc(), pPolylineInfo );

    acdbCustomOsnapManager()->addCustomOsnapMode( &thirdMode );
    acdbCustomOsnapManager()->activateOsnapMode( "_third" );

    snapToWholePolyline();
}

void
unloadApp()
{
    acedRegCmds->removeGroup( "ASDK_THIRD" );

    acdbCustomOsnapManager()->removeCustomOsnapMode( &thirdMode );

    AcDbEntity::desc()->delX( AsdkThirdOsnapInfo::desc() );
    AcDbCurve::desc()->delX( AsdkThirdOsnapInfo::desc() );
    AcDbPolyline::desc()->delX( AsdkThirdOsnapInfo::desc() );

    deleteAcRxClass( AsdkThirdOsnapInfo::desc() );
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
