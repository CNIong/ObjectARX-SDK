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

// AsdkInputPointMonitor methods
//

#include "acdbabb.h"
#include "adeskabb.h"
#include "aced.h"
#include "dbents.h"
#include "dbosnap.h"

#include "monitor.h"

Acad::ErrorStatus
AsdkInputPointMonitor::monitorInputPoint(
 
          bool&                             appendToTooltipStr,
          char*&                            additionalTooltipString,

          AcGiViewportDraw*                   pDrawContext,

          AcApDocument*                       document,
          bool                                pointComputed,
          int                                 history,
          const AcGePoint3d&                  lastPoint,
          const AcGePoint3d&                  rawPoint,
          const AcGePoint3d&                  grippedPoint,
          const AcGePoint3d&                  cartesianSnappedPoint,
          const AcGePoint3d&                  osnappedPoint,
          AcDb::OsnapMask                     osnapMasks,
          const AcArray<AcDbCustomOsnapMode*>& customOsnapModes,
          AcDb::OsnapMask                     osnapOverrides,
          const AcArray<AcDbCustomOsnapMode*>& customOsnapOverrides,
          const AcArray<AcDbObjectId>&        apertureEntities,
          const AcArray< AcDbObjectIdArray, AcArrayObjectCopyReallocator< AcDbObjectIdArray > >&
                                           nestedPickedEntities,
          const AcArray<int>&                                 gsSelectionMark,
          const AcArray<AcDbObjectId>&        keyPointEntities,
          const AcArray< AcDbObjectIdArray, AcArrayObjectCopyReallocator< AcDbObjectIdArray > >&
                                           nestedKeyPointEntities,
          const AcArray<int>&                        keyPointGsSelectionMark,
          const AcArray<AcGeCurve3d*>&          alignmentPaths,
          const AcGePoint3d&                  computedPoint,
          const char*                         tooltipString)
{
    if ( !pointComputed )
    {
        // Points cannot be computed in the Monitor
        // Forced picking may be enabled

        if ( history & Acad::eCyclingPt)
            acutPrintf( "\nNo point computed, but new cycling osnap: %.2f, %.2f, %.2f\n",
                osnappedPoint[X], osnappedPoint[Y], osnappedPoint[Z] );

        return Acad::eOk;
    }

    // Show historical point selection information
    //
#define HISTORY_CHECK(x)  if (history & Acad:: ## x) acutPrintf("%s ", #x)

    acutPrintf( "\nHistory: %d, ", history );

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

    acutPrintf( "\n" );

    // Show more point input information
    //
    if ( history & Acad::eLastPt )
        acutPrintf( "Last point:              %.2f, %.2f, %.2f\n", lastPoint[X], lastPoint[Y], lastPoint[Z] );

    acutPrintf( "Raw point:               %.2f, %.2f, %.2f\n", rawPoint[X], rawPoint[Y], rawPoint[Z] );
    acutPrintf( "Computed point:          %.2f, %.2f, %.2f\n", computedPoint[X], computedPoint[Y], computedPoint[Z] );

    if ( history & Acad::eGripped )
        acutPrintf( "Gripped point:           %.2f, %.2f, %.2f\n", grippedPoint[X], grippedPoint[Y], grippedPoint[Z] );
        
    if ( history & Acad::eCartSnapped )
        acutPrintf( "Cartesian snapped point: %.2f, %.2f, %.2f\n", cartesianSnappedPoint[X], cartesianSnappedPoint[Y], cartesianSnappedPoint[Z] );

    if ( history & Acad::eOsnapped )
    {
        acutPrintf( "Osnapped point:          %.2f, %.2f, %.2f\n", osnappedPoint[X], osnappedPoint[Y], osnappedPoint[Z] );

        acutPrintf( "Object snap masks: " );

#define OSMASK_CHECK(x)  if (osnapMasks & AcDb:: ## x) acutPrintf("%s ", #x)

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

        if ( 0 == osnapMasks )
        {
            for ( int i = 0; i < customOsnapModes.length(); i++ )
                acutPrintf( "%s\n", customOsnapModes[i]->globalModeString() );
        }
        acutPrintf( "\n" );
    }

    // Show the object snap overrides
    //
    if ( 0 != osnapOverrides )
    {

        acutPrintf( "Object snap overrides: " );

#define OSMASK_CHECK(x)  if (osnapOverrides & AcDb:: ## x) acutPrintf("%s ", #x)

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

        acutPrintf("\n");
    }

    // Show custom object snap overrides
    //
    if ( 0 != customOsnapOverrides.length() )
    {
        acutPrintf( "Custom object snap overrides: " );
        for ( int x = 0; x < customOsnapOverrides.length(); x++)
            acutPrintf( "%s ", customOsnapOverrides[x]->globalModeString() );
        acutPrintf( "\n" );
    }

    // Show object snap or forced pick information: the entities in the aperture
    acutPrintf( "%d apertured entities, ", apertureEntities.length() );
    acutPrintf( "%d nested apertured entities\n", nestedPickedEntities.length() );

    // Show AutoSnap information
    // Note: nestedKeyPointEntities.length() == keyPointGsSelectionMark.length()
    //
    acutPrintf( "%d key point entities, ", keyPointEntities.length() );
    acutPrintf( "%d nested key point entities\n", nestedKeyPointEntities.length() );
    acutPrintf( "%d alignment paths\n", alignmentPaths.length() );

    // Add an additional comment to the tootip string
    //
    if ( NULL != tooltipString )
    {
        additionalTooltipString = ", Additional comment!";
        appendToTooltipStr = true;
        acutPrintf( "Appending \"%s\" to \"%s\"\n", additionalTooltipString, tooltipString );
    }
    else
        acutPrintf( "Tooltip is NULL\n" );

    return Acad::eOk;
}

bool
AsdkInputPointMonitor::excludeFromOsnapCalculation (const AcArray<AcDbObjectId>& nestedEntity, int gsSelectionMark)
{
    acutPrintf( "\nExcludeFromOsnapCalculation called on monitor...\n" );
    acutPrintf( "%d nested entities under cursor\n", nestedEntity.length() );
    return false;
}
