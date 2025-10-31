//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

//

// AsdkInputPointMonitor methods
//

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#ifdef _MSC_VER
#include <Windows.h>
#endif
#include "acdbabb.h"
#include "adeskabb.h"
#include "aced.h"
#include "dbents.h"
#include "dbosnap.h"
#include "tchar.h"

#include "Monitor.h"


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
#define HISTORY_CHECK(x)  if (input.history() & x) acutPrintf(_T("%s "), _T(#x))

    acutPrintf( _T("\nHistory: %d, "), input.history() );


    HISTORY_CHECK(Acad::eTablet);
    HISTORY_CHECK(Acad::eNotDigitizer);
    HISTORY_CHECK(Acad::eLastPt);
    HISTORY_CHECK(Acad::eGripped);
    HISTORY_CHECK(Acad::eCartSnapped);
    HISTORY_CHECK(Acad::eOrtho);
    HISTORY_CHECK(Acad::eCyclingPt);
    HISTORY_CHECK(Acad::eOsnapped);
    HISTORY_CHECK(Acad::ePolarAngle);
    HISTORY_CHECK(Acad::eAligned);
    HISTORY_CHECK(Acad::eAppFiltered);
    HISTORY_CHECK(Acad::eForcedPick);
    HISTORY_CHECK(Acad::ePickMask);
    HISTORY_CHECK(Acad::eDidNotPick);
    HISTORY_CHECK(Acad::eUsedPickBox);
    HISTORY_CHECK(Acad::eUsedOsnapBox);
    HISTORY_CHECK(Acad::ePickAborted);
    HISTORY_CHECK(Acad::eXPending);
    HISTORY_CHECK(Acad::eYPending);
    HISTORY_CHECK(Acad::eZPending);
    HISTORY_CHECK(Acad::eCoordPending);

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

#define OSMASK_CHECK(x)  if (input.osnapMask() & x) acutPrintf(_T("%s "), _T(#x))

        OSMASK_CHECK(AcDb::kOsMaskEnd);
        OSMASK_CHECK(AcDb::kOsMaskMid);
        OSMASK_CHECK(AcDb::kOsMaskCen);
        OSMASK_CHECK(AcDb::kOsMaskNode);
        OSMASK_CHECK(AcDb::kOsMaskQuad);
        OSMASK_CHECK(AcDb::kOsMaskInt);
        OSMASK_CHECK(AcDb::kOsMaskIns);
        OSMASK_CHECK(AcDb::kOsMaskPerp);
        OSMASK_CHECK(AcDb::kOsMaskTan);
        OSMASK_CHECK(AcDb::kOsMaskNear);
        OSMASK_CHECK(AcDb::kOsMaskQuick);
        OSMASK_CHECK(AcDb::kOsMaskApint);
        OSMASK_CHECK(AcDb::kOsMaskImmediate);
        OSMASK_CHECK(AcDb::kOsMaskAllowTan);
        OSMASK_CHECK(AcDb::kOsMaskDisablePerp);
        OSMASK_CHECK(AcDb::kOsMaskRelCartesian);
        OSMASK_CHECK(AcDb::kOsMaskRelPolar);

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

#define OSMASK_CHECK(x)  if (input.osnapOverrides() & x) acutPrintf(_T("%s "), _T(#x))

        OSMASK_CHECK(AcDb::kOsMaskEnd);
        OSMASK_CHECK(AcDb::kOsMaskMid);
        OSMASK_CHECK(AcDb::kOsMaskCen);
        OSMASK_CHECK(AcDb::kOsMaskNode);
        OSMASK_CHECK(AcDb::kOsMaskQuad);
        OSMASK_CHECK(AcDb::kOsMaskInt);
        OSMASK_CHECK(AcDb::kOsMaskIns);
        OSMASK_CHECK(AcDb::kOsMaskPerp);
        OSMASK_CHECK(AcDb::kOsMaskTan);
        OSMASK_CHECK(AcDb::kOsMaskNear);
        OSMASK_CHECK(AcDb::kOsMaskQuick);
        OSMASK_CHECK(AcDb::kOsMaskApint);
        OSMASK_CHECK(AcDb::kOsMaskImmediate);
        OSMASK_CHECK(AcDb::kOsMaskAllowTan);
        OSMASK_CHECK(AcDb::kOsMaskDisablePerp);
        OSMASK_CHECK(AcDb::kOsMaskRelCartesian);
        OSMASK_CHECK(AcDb::kOsMaskRelPolar);

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
