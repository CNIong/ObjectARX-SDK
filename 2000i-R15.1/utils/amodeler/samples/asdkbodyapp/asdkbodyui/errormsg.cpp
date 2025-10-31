
///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 1996 by Autodesk, Inc.
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
// Facet Modeler Error Message Passing
//
///////////////////////////////////////////////////////////////////////////////

#include "amodeler.h"
#include "errormsg.h"

#if _MSC_VER >= 1000
using namespace AModeler;
#endif

struct ErrorMsg
{
    ErrorCode code;
    char *msg;
};

// Facet Modeler error messages
//
// Sorry, I was too lazy to remove the "e" and add spaces between
// the words.
//
// Also: this list will probably change as time goes on.  Must be
// in synch with AModeler's ERRCODES.H.
//
static ErrorMsg ErrorMessages[] =
{
    AModeler::eFail, "eFail",
    AModeler::eViewPointLiesInsideScene, "eViewPointLiesInsideScene",
    AModeler::eBadBodyGeometry, "eBadBodyGeometry",
    AModeler::eBadSurfaceType, "eBadSurfaceType",
    AModeler::eBadCurveType, "eBadCurveType",
    AModeler::eBadInput, "eBadInput",
    AModeler::eNullVector, "eNullVector",
    AModeler::eNullNormalVector, "eNullNormalVector",
    AModeler::eBadPlane, "eBadPlane",
    AModeler::eBadLine, "eBadLine",
    AModeler::eBadAxis, "eBadAxis",
    AModeler::eBadTransform, "eBadTransform",
    AModeler::eInputBodiesMustNotBeNegated, "eInputBodiesMustNotBeNegated",
    AModeler::eRadiusMustBePositive, "eRadiusMustBePositive",
    AModeler::eRadiusMustBeNonNegative, "eRadiusMustBeNonNegative",
    AModeler::eRadiusMustNotBeZero, "eRadiusMustNotBeZero",
    AModeler::eApproximationMustBeAtLeastFour, "eApproximationMustBeAtLeastFour",
    AModeler::eScaleFactorMustBePositive, "eScaleFactorMustBePositive",
    AModeler::eAngleMustNotBeZero, "eAngleMustNotBeZero",
    AModeler::eBodyPointerIsNull, "eBodyPointerIsNull",
    AModeler::eFacePointerIsNull, "eFacePointerIsNull",
    AModeler::eEdgePointerIsNull, "eEdgePointerIsNull",
    AModeler::eVertexPointerIsNull, "eVertexPointerIsNull",
    AModeler::ePolygonPointerIsNull, "ePolygonPointerIsNull",
    AModeler::eProfilePolygonPointerIsNull, "eProfilePolygonPointerIsNull",
    AModeler::ePathPolygonPointerIsNull, "ePathPolygonPointerIsNull",
    AModeler::eBodyIsNegative, "eBodyIsNegative",
    AModeler::eFileNameIsNull, "eFileNameIsNull",
    AModeler::eBadFile, "eBadFile",
    AModeler::eFilePointerIsNull, "eFilePointerIsNull",
    AModeler::eFileOpenError, "eFileOpenError",
    AModeler::eFileReadError, "eFileReadError",
    AModeler::eFileWriteError, "eFileWriteError",
    AModeler::eSaveError, "eSaveError",
    AModeler::eRestoreError, "eRestoreError",
    AModeler::eBadDataRestored, "eBadDataRestored",
    AModeler::eFileIsNewerThanCurrentVersionOfModeler, "eFileIsNewerThanCurrentVersionOfModeler",
    AModeler::eBoxSizesMustNotBeZero, "eBoxSizesMustNotBeZero",
    AModeler::eMajorRadiusMustBeGreaterThanMinorRadius, "eMajorRadiusMustBeGreaterThanMinorRadius",
    AModeler::eInnerRadiusMustBeSmallerThanOuterRadius, "eInnerRadiusMustBeSmallerThanOuterRadius",
    AModeler::eInnerRadiusCanBeZeroOnlyIfOuterRadiusIsZero, "eInnerRadiusCanBeZeroOnlyIfOuterRadiusIsZero",
    AModeler::eViewPointCoincidesWithTargetPoint, "eViewPointCoincidesWithTargetPoint",
    AModeler::eEpsilonMustBePositive, "eEpsilonMustBePositive",
    AModeler::eCallbackObjectPointerIsNull, "eCallbackObjectPointerIsNull",
    AModeler::ePickingNotPossible, "ePickingNotPossible",
    AModeler::eAtLeast4NonCoplanarPointsRequired, "eAtLeast4NonCoplanarPointsRequired",
    AModeler::ePointsDoNotDefineConvexPolyhedron, "ePointsDoNotDefineConvexPolyhedron",
    AModeler::eApexMustNotLieInPolygon, "eApexMustNotLieInPolygon",
    AModeler::eExtrusionVectorMustNotBeParallelToPolygon, "eExtrusionVectorMustNotBeParallelToPolygon",
    AModeler::eAxisOfRevolutionMustLieInPolygonPlane, "eAxisOfRevolutionMustLieInPolygonPlane",
    AModeler::eAxisOfRevolutionIntersectsPolygon, "eAxisOfRevolutionIntersectsPolygon",
    AModeler::eBadNormal, "eBadNormal",
    AModeler::eBadPolygon, "eBadPolygon",
    AModeler::ePolygonIsSelfIntersectingOrTouching, "ePolygonIsSelfIntersectingOrTouching",
    AModeler::eBadRelativePolygonPosition, "eBadRelativePolygonPosition",
    AModeler::eCannotCreateFillet, "eCannotCreateFillet",
    AModeler::eBadArcCenter, "eBadArcCenter",
    AModeler::eRadiusTooSmall, "eRadiusTooSmall",
    AModeler::eFilletRadiusMustBePositive, "eFilletRadiusMustBePositive",
    AModeler::eCannotFilletVerticesBelongingToArcs, "eCannotFilletVerticesBelongingToArcs",
    AModeler::eFirstAndLastVertexInEndpointRevolutionMustNotBeFilleted, "eFirstAndLastVertexInEndpointRevolutionMustNotBeFilleted",
    AModeler::eArcBetweenLastAndFirstVertexNotAllowedForEndpointRevolution, "eArcBetweenLastAndFirstVertexNotAllowedForEndpointRevolution",
    AModeler::eEntitiesSectionNotFoundInDxfFile, "eEntitiesSectionNotFoundInDxfFile",
    AModeler::ePolylineEntityNotFoundInDxfFile, "ePolylineEntityNotFoundInDxfFile",
    AModeler::ePolylineMustBeClosed, "ePolylineMustBeClosed",
    AModeler::e3dPolylineOrMeshNotAllowed, "e3dPolylineOrMeshNotAllowed",
    AModeler::eBadDxfFile, "eBadDxfFile",
    AModeler::ePointsAreColinearOrCoincident, "ePointsAreColinearOrCoincident",
    AModeler::eSourceArgumentsAreColinearOrCoincident, "eSourceArgumentsAreColinearOrCoincident",
    AModeler::eDestinationArgumentsAreColinearOrCoincident, "eDestinationArgumentsAreColinearOrCoincident",
    AModeler::ePointsAreCoplanar, "ePointsAreCoplanar",
    AModeler::eChamferingDistanceMustBePositive, "eChamferingDistanceMustBePositive",
    AModeler::eOnlyManifoldEdgesCanBeFilletedAndChamfered, "eOnlyManifoldEdgesCanBeFilletedAndChamfered",
    AModeler::eOnlyStraightAndCircularEdgesCanBeFilletedAndChamfered, "eOnlyStraightAndCircularEdgesCanBeFilletedAndChamfered",
    AModeler::ePlanarEdgesCannotBeFilletedAndChamfered, "ePlanarEdgesCannotBeFilletedAndChamfered",
    AModeler::eAtLeastOneEdgeExpected, "eAtLeastOneEdgeExpected",
    AModeler::eFilletRadiusTooLarge, "eFilletRadiusTooLarge",
    AModeler::eChamferDistanceTooLarge, "eChamferDistanceTooLarge",
    AModeler::eCannotFilletEdge, "eCannotFilletEdge",
    AModeler::eCannotMitreEdgesOfDifferentConvexity, "eCannotMitreEdgesOfDifferentConvexity",
    AModeler::eTooComplexMixedConvexityCap, "eTooComplexMixedConvexityCap",
    AModeler::eNotYetImplemented, "eNotYetImplemented",
    AModeler::eCircleIsNotValid, "eCircleIsNotValid",
    AModeler::eBaseNormalPerpendicularToAxisVector, "eBaseNormalPerpendicularToAxisVector",
    AModeler::eEndCentersMustHaveEqualDistance, "eEndCentersMustHaveEqualDistance",
    AModeler::eFaceMustNotBelongToABody, "eFaceMustNotBelongToABody",
    AModeler::eFaceHasNoEdges, "eFaceHasNoEdges",
    AModeler::eOneSidedFaceExpected, "eOneSidedFaceExpected",
    AModeler::eProfileFacesMustHaveTheSameNumberOfEdges, "eProfileFacesMustHaveTheSameNumberOfEdges",
    AModeler::eAtLeastTwoProfilesExpected, "eAtLeastTwoProfilesExpected",
    AModeler::eBodyProfileMustContainExactlyOneFace, "eBodyProfileMustContainExactlyOneFace",
    AModeler::eProfileFaceHasNoEdges, "eProfileFaceHasNoEdges",
    AModeler::eBadMorphingMap, "eBadMorphingMap",
    AModeler::eEdgesOfFirstProfileCannotBeMarkedApproximating, "eEdgesOfFirstProfileCannotBeMarkedApproximating",
    AModeler::eBaseSizesMustBePositive, "eBaseSizesMustBePositive",
    AModeler::eTopCircleMustLieAboveBaseRectangle, "eTopCircleMustLieAboveBaseRectangle",
    AModeler::eFilletByRadiusOrArcByBulgeTypeExpected, "eFilletByRadiusOrArcByBulgeTypeExpected",
    AModeler::eArcByRadiusTypeExpected, "eArcByRadiusTypeExpected",
    AModeler::eArc3dTypeExpected, "eArc3dTypeExpected",
    AModeler::eCannotCreateTouchingCircle, "eCannotCreateTouchingCircle",
    AModeler::eNonPlanarPolygon, "eNonPlanarPolygon",
    AModeler::eNonPlanarProfileFace, "eNonPlanarProfileFace",
    AModeler::eFaceMustHaveAtLeastThreeEdges, "eFaceMustHaveAtLeastThreeEdges",
    AModeler::ePolygonPointsCoincide, "ePolygonPointsCoincide",
    AModeler::eBadPath, "eBadPath",
    AModeler::eBadProfileAndPathOrientation, "eBadProfileAndPathOrientation",
    AModeler::eFirstPathPointMustLieInStartProfilePlane, "eFirstPathPointMustLieInStartProfilePlane",
    AModeler::eLastPathPointMustLieInEndProfilePlane, "eLastPathPointMustLieInEndProfilePlane",
    AModeler::eWidthTooSmall, "eWidthTooSmall",
    AModeler::eHeightTooSmall, "eHeightTooSmall",
    AModeler::eEndProfileNotAllowedWhenPathIsClosed, "eEndProfileNotAllowedWhenPathIsClosed",
    AModeler::eScaleFactorNotAllowedWhenPathIsClosed, "eScaleFactorNotAllowedWhenPathIsClosed",
    AModeler::eTwistAngleNotAllowedWhenPathIsClosed, "eTwistAngleNotAllowedWhenPathIsClosed",
    AModeler::eMorphingMustBeIdentityWhenPathIsClosed, "eMorphingMustBeIdentityWhenPathIsClosed",
    AModeler::eExtrusionBodyLooksSelfIntersecting, "eExtrusionBodyLooksSelfIntersecting",
    AModeler::eMorphingMapRequiresEndProfile, "eMorphingMapRequiresEndProfile",
    AModeler::eNegativeIndexInMorphingMap, "eNegativeIndexInMorphingMap",
    AModeler::eFixedPointMustLieInPolygonPlane, "eFixedPointMustLieInPolygonPlane",
    AModeler::eTriStripsMayBeGeneratedOnlyWhenCachingTriangles, "eTriStripsMayBeGeneratedOnlyWhenCachingTriangles",
    AModeler::eStartProfileNormalHasOppositeDirectionThanFirstPathSegment, "eStartProfileNormalHasOppositeDirectionThanFirstPathSegment",
    AModeler::eEndProfileNormalHasOppositeDirectionThanLastPathSegment, "eEndProfileNormalHasOppositeDirectionThanLastPathSegment",
    AModeler::eStartProfileIsParallelWithFirstPathSegment, "eStartProfileIsParallelWithFirstPathSegment",
    AModeler::eEndProfileIsParallelWithLastPathSegment, "eEndProfileIsParallelWithLastPathSegment",
    AModeler::eProfilePolygomNustContainAtLeastOnePoint, "eProfilePolygomNustContainAtLeastOnePoint",
    AModeler::eArcByRadiusNotAllowedForPathPolygons_UseArc3d, "eArcByRadiusNotAllowedForPathPolygons_UseArc3d",
    AModeler::eArcByBulgeNotAllowedForPathPolygons_UseArc3d, "eArcByBulgeNotAllowedForPathPolygons_UseArc3d",
    AModeler::eNumberOfLinearSegmentsMustBeAtLeastOne, "eNumberOfLinearSegmentsMustBeAtLeastOne",
    AModeler::eZeroBulgeNotAllowed, "eZeroBulgeNotAllowed",
    AModeler::eFixedPointMustLieInStartProfilePlane, "eFixedPointMustLieInStartProfilePlane",
    AModeler::eInternalError, "eInternalError",
    AModeler::eOk, "eOk, should never happen"
};

//
// getErrorMsg
//
// Passes back a char pointer to the error message
// associated with the code passed.
//
char*
getErrorMsg(ErrorCode err)
{
    for (int i = 0; ErrorMessages[i].code != AModeler::eOk; i++)
        if (ErrorMessages[i].code == err)
            return ErrorMessages[i].msg;
    return NULL;
}
