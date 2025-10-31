//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#ifdef _MSC_VER
#include <Windows.h>
#endif
#include "aced.h"
#include "dbmain.h"
#include "acdbabb.h"
#include "adeskabb.h"
#include "rxregsvc.h"
#include "acgi.h"
#include "acdocman.h"
#include "dbapserv.h"

#include "Monitor.h"
#include "filter.h"
#include "reactor.h"
#include "tchar.h"



void cmdAddMonitor();
void cmdRemoveMonitor();
void cmdAddFilter();
void cmdRemoveFilter();
void cmdFilterChangesOn();
void cmdFilterChangesOff();
void cmdAddReactor();
void cmdRemoveReactor();
void cmdForcedPickOn();
void cmdForcedPickOff();
void cmdCursorOn();
void cmdCursorOff();

// My input point monitor
AsdkInputPointMonitor myMonitor;

// My input point filter
AsdkInputPointFilter myFilter;

// My input context reactor
AsdkInputContextReactor myReactor;


// Command definition
//

// Installs an input point monitor
//
void cmdAddMonitor()
{
    curDoc()->inputPointManager()->addPointMonitor( &myMonitor );
    acutPrintf( _T("Input point monitor added.\n") );
}

void cmdRemoveMonitor()
{
    curDoc()->inputPointManager()->removePointMonitor( &myMonitor );
    acutPrintf( _T("Input point monitor removed.\n") );
}

// Installs an input point filter
//
void cmdAddFilter()
{
    curDoc()->inputPointManager()->registerPointFilter( &myFilter );
    acutPrintf( _T("Input point filter added.\n") );
    cmdFilterChangesOff();
}

void cmdRemoveFilter()
{
    if ( NULL != curDoc()->inputPointManager()->currentPointFilter() )
    {
        curDoc()->inputPointManager()->revokePointFilter();
        acutPrintf( _T("Input point filter removed.\n") );
    }
}

void cmdFilterChangesOn()
{
    acutPrintf( _T("Filter will now make changes to the computed point & tooltip.\n") );
    myFilter.enableChanges();
}

void cmdFilterChangesOff()
{
    acutPrintf( _T("Filter will not make changes.\n") );
    myFilter.disableChanges();
}

// Installs an input context reactor
//
void cmdAddReactor()
{
    curDoc()->inputPointManager()->addInputContextReactor( &myReactor );
    acutPrintf( _T("Input context reactor added.\n") );
}

void cmdRemoveReactor()
{
    curDoc()->inputPointManager()->removeInputContextReactor( &myReactor);
    acutPrintf( _T("Input context reactor removed.\n") );
}

// Turns on forced entity picking
//
void cmdForcedPickOn()
{
    acutPrintf( _T("%d callers have turned on forced picking.\n"), curDoc()->inputPointManager()->forcedPickCount() );
    acutPrintf( _T("Turning off forced picking...\n") );
    curDoc()->inputPointManager()->turnOnForcedPick();
    acutPrintf( _T("%d callers have turned on forced picking.\n"), curDoc()->inputPointManager()->forcedPickCount() );
}

void cmdForcedPickOff()
{
    acutPrintf( _T("%d callers have turned on forced picking.\n"), curDoc()->inputPointManager()->forcedPickCount() );
    acutPrintf( _T("Turning on forced picking...\n") );
    curDoc()->inputPointManager()->turnOffForcedPick();
    acutPrintf( _T("%d callers have turned on forced picking.\n"), curDoc()->inputPointManager()->forcedPickCount() );
}

// Enables system cursor graphics
//
void cmdCursorOn()
{
    acutPrintf( _T("%d callers have disabled system graphics.\n"), curDoc()->inputPointManager()->systemCursorDisableCount() );
    acutPrintf( _T("Disabling system graphics...\n") );
    curDoc()->inputPointManager()->disableSystemCursorGraphics();
    acutPrintf( _T("%d callers have disabled system graphics.\n"), curDoc()->inputPointManager()->systemCursorDisableCount() );
}

void cmdCursorOff()
{
    acutPrintf( _T("%d callers have disabled system graphics.\n"), curDoc()->inputPointManager()->systemCursorDisableCount() );
    acutPrintf( _T("Enabling system graphics...\n") );
    curDoc()->inputPointManager()->enableSystemCursorGraphics();
    acutPrintf( _T("%d callers have disabled system graphics.\n"), curDoc()->inputPointManager()->systemCursorDisableCount() );
}

extern "C" __declspec( dllexport )
AcRx::AppRetCode acrxEntryPoint( AcRx::AppMsgCode msg, void *p )
{
    switch ( msg )
    {
    case AcRx::kInitAppMsg:
        acrxRegisterAppMDIAware( p );
        acrxUnlockApplication( p );
        acedRegCmds->addCommand( _T("AsdkInputPoint"), _T("AddMonitor"), _T("ADDMON"), ACRX_CMD_TRANSPARENT, cmdAddMonitor );
        acedRegCmds->addCommand( _T("AsdkInputPoint"), _T("RemoveMonitor"), _T("REMMON"), ACRX_CMD_TRANSPARENT, cmdRemoveMonitor );
        acedRegCmds->addCommand( _T("AsdkInputPoint"), _T("AddFilter"), _T("ADDFIL"), ACRX_CMD_TRANSPARENT, cmdAddFilter );
        acedRegCmds->addCommand( _T("AsdkInputPoint"), _T("RemoveFilter"), _T("REMFIL"), ACRX_CMD_TRANSPARENT, cmdRemoveFilter );
        acedRegCmds->addCommand( _T("AsdkInputPoint"), _T("ChangesOn"), _T("CHON"), ACRX_CMD_TRANSPARENT, cmdFilterChangesOn );
        acedRegCmds->addCommand( _T("AsdkInputPoint"), _T("ChangesOff"), _T("CHOFF"), ACRX_CMD_TRANSPARENT, cmdFilterChangesOff );
        acedRegCmds->addCommand( _T("AsdkInputPoint"), _T("AddReactor"), _T("ADDREAC"), ACRX_CMD_TRANSPARENT, cmdAddReactor );
        acedRegCmds->addCommand( _T("AsdkInputPoint"), _T("RemoveReactor"), _T("REMREAC"), ACRX_CMD_TRANSPARENT, cmdRemoveReactor );
        acedRegCmds->addCommand( _T("AsdkInputPoint"), _T("ForcedPickon"), _T("FPON"), ACRX_CMD_TRANSPARENT, cmdForcedPickOn );
        acedRegCmds->addCommand( _T("AsdkInputPoint"), _T("ForcedPickoff"), _T("FPOFF"), ACRX_CMD_TRANSPARENT, cmdForcedPickOff );
        acedRegCmds->addCommand( _T("AsdkInputPoint"), _T("CursorOn"), _T("CURON"), ACRX_CMD_TRANSPARENT, cmdCursorOn );
        acedRegCmds->addCommand( _T("AsdkInputPoint"), _T("CursorOff"), _T("CUROFF"), ACRX_CMD_TRANSPARENT, cmdCursorOff );
        break;

    case AcRx::kUnloadAppMsg:
        acedRegCmds->removeGroup( _T("AsdkInputPoint") );
        break;
    }
    return AcRx::kRetOK;
}
