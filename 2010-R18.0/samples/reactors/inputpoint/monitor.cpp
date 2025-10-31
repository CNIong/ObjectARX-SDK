//   Copyright (C) 1998-2007 by Autodesk, Inc.
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

// AsdkInputPointMonitor methods
//

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "acdbabb.h"
#include "adeskabb.h"
#include "aced.h"
#include "dbents.h"
#include "dbosnap.h"
#include "tchar.h"

#include "monitor.h"


Acad::ErrorStatus
AsdkInputPointMonitor::monitorInputPoint(const AcEdInputPoint& input, AcEdInputPointMonitorResult& output)
{
    if ( !input.pointComputed() )
    {
        // Points cannot be computed in the Monitor
        // Forced picking may be enabled

        if ( input.history() & Acad::eCyclingPt)
            acutPrintf( _T("\nNo point computed, but new cycling osnap: %.2f, %.2f, %.2f\n"),
                input.osnappedPoint()[X], input.osnappedPoint()[Y], input.osnappedPoint()[Z] );

        return Acad::eOk;
    }

    // Show historical point selection information
    //
#define HISTORY_CHECK(x)  if (input.history() & Acad:: ## x) acutPrintf(_T("%s "), _T(#x))

    acutPrintf( _T("\nHistory: %d, "), input.history() );

    HISTORY_CHECK(eTablet);
    HISTORY_CHECK(eNotDigitizer);
    HISTORY_CHECK(eLastPt);
    HISTORY_CHECK(eGripped);
    HISTORY_CHECK(eCartSnapped);
    HISTORY_CHECK(eOrtho);
    HISTORY_CHECK(eCyclingPt);
    HISTORY_CHECK(eOsnapped);
    HISTORY_CHECK(ePolarAngle);
    HISTORY_CHECK(eAligned);
    HISTORY_CHECK(eAppFiltered);
    HISTORY_CHECK(eForcedPick);
    HISTORY_CHECK(ePickMask);
    HISTORY_CHECK(eDidNotPick);
    HISTORY_CHECK(eUsedPickBox);
    HISTORY_CHECK(eUsedOsnapBox);
    HISTORY_CHECK(ePickAborted);
    HISTORY_CHECK(eXPending);
    HISTORY_CHECK(eYPending);
    HISTORY_CHECK(eZPending);
    HISTORY_CHECK(eCoordPending);

#undef HISTORY_CHECK

    acutPrintf( _T("\n") );

    // Show more point input information
    //
    if ( input.history() & Acad::eLastPt )
        acutPrintf( _T("Last point:              %.2f, %.2f, %.2f\n"), input.lastPoint()[X], input.lastPoint()[Y], input.lastPoint()[Z] );

    acutPrintf( _T("Raw point:               %.2f, %.2f, %.2f\n"), input.rawPoint()[X], input.rawPoint()[Y], input.rawPoint()[Z] );
    acutPrintf( _T("Computed point:          %.2f, %.2f, %.2f\n"), input.computedPoint()[X], input.computedPoint()[Y], input.computedPoint()[Z] );

    if ( input.history() & Acad::eGripped )
        acutPrintf( _T("Gripped point:           %.2f, %.2f, %.2f\n"), input.grippedPoint()[X], input.grippedPoint()[Y], input.grippedPoint()[Z] );
        
    if ( input.history() & Acad::eCartSnapped )
        acutPrintf( _T("Cartesian snapped point: %.2f, %.2f, %.2f\n"), input.cartesianSnappedPoint()[X], input.cartesianSnappedPoint()[Y], input.cartesianSnappedPoint()[Z] );

    if ( input.history() & Acad::eOsnapped )
    {
        acutPrintf( _T("Osnapped point:          %.2f, %.2f, %.2f\n"), input.osnappedPoint()[X], input.osnappedPoint()[Y], input.osnappedPoint()[Z] );

        acutPrintf( _T("Object snap masks: ") );

#define OSMASK_CHECK(x)  if (input.osnapMask() & AcDb:: ## x) acutPrintf(_T("%s "), _T(#x))

        OSMASK_CHECK(kOsMaskEnd);
        OSMASK_CHECK(kOsMaskMid);
        OSMASK_CHECK(kOsMaskCen);
        OSMASK_CHECK(kOsMaskNode);
        OSMASK_CHECK(kOsMaskQuad);
        OSMASK_CHECK(kOsMaskInt);
        OSMASK_CHECK(kOsMaskIns);
        OSMASK_CHECK(kOsMaskPerp);
        OSMASK_CHECK(kOsMaskTan);
        OSMASK_CHECK(kOsMaskNear);
        OSMASK_CHECK(kOsMaskQuick);
        OSMASK_CHECK(kOsMaskApint);
        OSMASK_CHECK(kOsMaskImmediate);
        OSMASK_CHECK(kOsMaskAllowTan);
        OSMASK_CHECK(kOsMaskDisablePerp);
        OSMASK_CHECK(kOsMaskRelCartesian);
        OSMASK_CHECK(kOsMaskRelPolar);

#undef OSMASK_CHECK

        if ( 0 == input.osnapMask() )
        {
            for ( int i = 0; i < input.customOsnapModes().length(); i++ )
                acutPrintf( _T("%s\n"), input.customOsnapModes()[i]->globalModeString() );
        }
        acutPrintf( _T("\n") );
    }

    // Show the object snap overrides
    //
    if ( 0 != input.osnapOverrides() )
    {

        acutPrintf( _T("Object snap overrides: ") );

#define OSMASK_CHECK(x)  if (input.osnapOverrides() & AcDb:: ## x) acutPrintf(_T("%s "), _T(#x))

        OSMASK_CHECK(kOsMaskEnd);
        OSMASK_CHECK(kOsMaskMid);
        OSMASK_CHECK(kOsMaskCen);
        OSMASK_CHECK(kOsMaskNode);
        OSMASK_CHECK(kOsMaskQuad);
        OSMASK_CHECK(kOsMaskInt);
        OSMASK_CHECK(kOsMaskIns);
        OSMASK_CHECK(kOsMaskPerp);
        OSMASK_CHECK(kOsMaskTan);
        OSMASK_CHECK(kOsMaskNear);
        OSMASK_CHECK(kOsMaskQuick);
        OSMASK_CHECK(kOsMaskApint);
        OSMASK_CHECK(kOsMaskImmediate);
        OSMASK_CHECK(kOsMaskAllowTan);
        OSMASK_CHECK(kOsMaskDisablePerp);
        OSMASK_CHECK(kOsMaskRelCartesian);
        OSMASK_CHECK(kOsMaskRelPolar);

#undef OSMASK_CHECK

        acutPrintf(_T("\n"));
    }

    // Show custom object snap overrides
    //
    if ( 0 != input.customOsnapOverrides().length() )
    {
        acutPrintf( _T("Custom object snap overrides: ") );
        for ( int x = 0; x < input.customOsnapOverrides().length(); x++)
            acutPrintf( _T("%s "), input.customOsnapOverrides()[x]->globalModeString() );
        acutPrintf( _T("\n") );
    }

    // Show object snap or forced pick information: the entities in the aperture
    acutPrintf( _T("%d apertured entities, "), input.pickedEntities().length() );
    acutPrintf( _T("%d nested apertured entities\n"), input.nestedPickedEntities().length() );

    // Show AutoSnap information
    // Note: nestedKeyPointEntities.length() == keyPointGsSelectionMark.length()
    //
    acutPrintf( _T("%d key point entities, "), input.keyPointEntities().length() );
    acutPrintf( _T("%d nested key point entities\n"), input.nestedKeyPointEntities().length() );
    acutPrintf( _T("%d alignment paths\n"), input.alignmentPaths().length() );

    // Add an additional comment to the tootip string
    //
    if ( NULL != input.tooltipString() )
    {
        output.setAdditionalTooltipString(_T(", Additional comment!"));
        acutPrintf( _T("Appending \"%s\" to \"%s\"\n"), _T(", Additional comment!"), input.tooltipString() );
    }
    else
        acutPrintf( _T("Tooltip is NULL\n") );

    acedPostCommandPrompt();
    return Acad::eOk;
}

bool
AsdkInputPointMonitor::excludeFromOsnapCalculation (const AcArray<AcDbObjectId>& nestedEntity, INT_PTR gsSelectionMark)
{
    acutPrintf( _T("\nExcludeFromOsnapCalculation called on monitor...\n") );
    acutPrintf( _T("%d nested entities under cursor\n"), nestedEntity.length() );
    return false;
}
