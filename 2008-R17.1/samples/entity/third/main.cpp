//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <acutads.h>
#include <aced.h>
#include <dbmain.h>
#include <dbents.h>
#include <dbpl.h>
#include <dbosnap.h>
#include <rxregsvc.h>

#include "ThirdOsnapMode.h"
#include "ThirdOsnapInfo.h"
#include "tchar.h"



AsdkThirdOsnapMode thirdMode;
bool bSnapToSegments = false;

void
snapToPolylineSegments()
{
    acutPrintf(_T("\nThird object snap will snap to polyline segments."));
    bSnapToSegments = true;
}

void
snapToWholePolyline()
{
    acutPrintf(_T("\nThird object snap will snap to whole polyline."));
    bSnapToSegments = false;
}

void
initApp()
{
    acedRegCmds->addCommand( _T("ASDK_THIRD"), _T("ASDK_SNAP2PLINE"),    _T("SNAP2PLINE"),   ACRX_CMD_TRANSPARENT, snapToWholePolyline );
    acedRegCmds->addCommand( _T("ASDK_THIRD"), _T("ASDK_SNAP2SEG"),      _T("SNAP2SEG"),     ACRX_CMD_TRANSPARENT, snapToPolylineSegments );

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
    acdbCustomOsnapManager()->activateOsnapMode( _T("_third") );

    snapToWholePolyline();
}

void
unloadApp()
{
    acedRegCmds->removeGroup( _T("ASDK_THIRD") );

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
