//   Copyright (C) 1998 by Autodesk, Inc.
//
//     Permission to use, copy, modify, and distribute this software
//     for any purpose is restricted by the VIP Subscription program
//     license agreement.  This application was developed exclusively
//     for distribution by the VIP subscription program and may not
//     be posted pubicly, modified, copied, or distributed by any other
//     methods. 
//
//     AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.  
//     AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF 
//     MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
//     DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE 
//     UNINTERRUPTED OR ERROR FREE.
//
//     Use, duplication, or disclosure by the U.S. Government is subject to 
//     restrictions set forth in FAR 52.227-19 (Commercial Computer 
//     Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii) 
//     (Rights in Technical Data and Computer Software), as applicable. 
//

#include "aced.h"
#include "dbmain.h"
#include "acdbabb.h"
#include "adeskabb.h"
#include "rxregsvc.h"
#include "acgi.h"
#include "acdocman.h"
#include "dbapserv.h"

#include "monitor.h"
#include "filter.h"
#include "reactor.h"

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
    acutPrintf( "Input point monitor added.\n" );
}

void cmdRemoveMonitor()
{
    curDoc()->inputPointManager()->removePointMonitor( &myMonitor );
    acutPrintf( "Input point monitor removed.\n" );
}

// Installs an input point filter
//
void cmdAddFilter()
{
    curDoc()->inputPointManager()->registerPointFilter( &myFilter );
    acutPrintf( "Input point filter added.\n" );
    cmdFilterChangesOff();
}

void cmdRemoveFilter()
{
    if ( NULL != curDoc()->inputPointManager()->currentPointFilter() )
    {
        curDoc()->inputPointManager()->revokePointFilter();
        acutPrintf( "Input point filter removed.\n" );
    }
}

void cmdFilterChangesOn()
{
    acutPrintf( "Filter will now make changes to the computed point & tooltip.\n" );
    myFilter.enableChanges();
}

void cmdFilterChangesOff()
{
    acutPrintf( "Filter will not make changes.\n" );
    myFilter.disableChanges();
}

// Installs an input context reactor
//
void cmdAddReactor()
{
    curDoc()->inputPointManager()->addInputContextReactor( &myReactor );
    acutPrintf( "Input context reactor added.\n" );
}

void cmdRemoveReactor()
{
    curDoc()->inputPointManager()->removeInputContextReactor( &myReactor);
    acutPrintf( "Input context reactor removed.\n" );
}

// Turns on forced entity picking
//
void cmdForcedPickOn()
{
    acutPrintf( "%d callers have turned on forced picking.\n", curDoc()->inputPointManager()->forcedPickCount() );
    acutPrintf( "Turning off forced picking...\n" );
    curDoc()->inputPointManager()->turnOnForcedPick();
    acutPrintf( "%d callers have turned on forced picking.\n", curDoc()->inputPointManager()->forcedPickCount() );
}

void cmdForcedPickOff()
{
    acutPrintf( "%d callers have turned on forced picking.\n", curDoc()->inputPointManager()->forcedPickCount() );
    acutPrintf( "Turning on forced picking...\n" );
    curDoc()->inputPointManager()->turnOffForcedPick();
    acutPrintf( "%d callers have turned on forced picking.\n", curDoc()->inputPointManager()->forcedPickCount() );
}

// Enables system cursor graphics
//
void cmdCursorOn()
{
    acutPrintf( "%d callers have disabled system graphics.\n", curDoc()->inputPointManager()->systemCursorDisableCount() );
    acutPrintf( "Disabling system graphics...\n" );
    curDoc()->inputPointManager()->disableSystemCursorGraphics();
    acutPrintf( "%d callers have disabled system graphics.\n", curDoc()->inputPointManager()->systemCursorDisableCount() );
}

void cmdCursorOff()
{
    acutPrintf( "%d callers have disabled system graphics.\n", curDoc()->inputPointManager()->systemCursorDisableCount() );
    acutPrintf( "Enabling system graphics...\n" );
    curDoc()->inputPointManager()->enableSystemCursorGraphics();
    acutPrintf( "%d callers have disabled system graphics.\n", curDoc()->inputPointManager()->systemCursorDisableCount() );
}

extern "C" __declspec( dllexport )
AcRx::AppRetCode acrxEntryPoint( AcRx::AppMsgCode msg, void *p )
{
    switch ( msg )
    {
    case AcRx::kInitAppMsg:
        acrxRegisterAppMDIAware( p );
        acrxUnlockApplication( p );
        acedRegCmds->addCommand( "AsdkInputPoint", "AddMonitor", "ADDMON", ACRX_CMD_TRANSPARENT, cmdAddMonitor );
        acedRegCmds->addCommand( "AsdkInputPoint", "RemoveMonitor", "REMMON", ACRX_CMD_TRANSPARENT, cmdRemoveMonitor );
        acedRegCmds->addCommand( "AsdkInputPoint", "AddFilter", "ADDFIL", ACRX_CMD_TRANSPARENT, cmdAddFilter );
        acedRegCmds->addCommand( "AsdkInputPoint", "RemoveFilter", "REMFIL", ACRX_CMD_TRANSPARENT, cmdRemoveFilter );
        acedRegCmds->addCommand( "AsdkInputPoint", "ChangesOn", "CHON", ACRX_CMD_TRANSPARENT, cmdFilterChangesOn );
        acedRegCmds->addCommand( "AsdkInputPoint", "ChangesOff", "CHOFF", ACRX_CMD_TRANSPARENT, cmdFilterChangesOff );
        acedRegCmds->addCommand( "AsdkInputPoint", "AddReactor", "ADDREAC", ACRX_CMD_TRANSPARENT, cmdAddReactor );
        acedRegCmds->addCommand( "AsdkInputPoint", "RemoveReactor", "REMREAC", ACRX_CMD_TRANSPARENT, cmdRemoveReactor );
        acedRegCmds->addCommand( "AsdkInputPoint", "ForcedPickon", "FPON", ACRX_CMD_TRANSPARENT, cmdForcedPickOn );
        acedRegCmds->addCommand( "AsdkInputPoint", "ForcedPickoff", "FPOFF", ACRX_CMD_TRANSPARENT, cmdForcedPickOff );
        acedRegCmds->addCommand( "AsdkInputPoint", "CursorOn", "CURON", ACRX_CMD_TRANSPARENT, cmdCursorOn );
        acedRegCmds->addCommand( "AsdkInputPoint", "CursorOff", "CUROFF", ACRX_CMD_TRANSPARENT, cmdCursorOff );
        break;

    case AcRx::kUnloadAppMsg:
        acedRegCmds->removeGroup( "AsdkInputPoint" );
        break;
    }
    return AcRx::kRetOK;
}