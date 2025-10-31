//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#if defined(_DEBUG) && !defined(_FULLDEBUG_)
#define _DEBUG_WAS_DEFINED
#pragma message ("       Compiling MFC /STL /ATL header files in release mode.")
#undef _DEBUG
#endif

#include "amodeler.h"
#include "errormsg.h"

#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif

#if _MSC_VER >= 1000
using namespace AModeler;
#endif

struct ErrorMsg
{
    ErrorCode code;
    ACHAR *msg;
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
    AModeler::eFail, ACRX_T("eFail"),
    AModeler::eViewPointLiesInsideScene, ACRX_T("eViewPointLiesInsideScene"),
    AModeler::eBadBodyGeometry, ACRX_T("eBadBodyGeometry"),
    AModeler::eBadSurfaceType, ACRX_T("eBadSurfaceType"),
    AModeler::eBadCurveType, ACRX_T("eBadCurveType"),
    AModeler::eBadInput, ACRX_T("eBadInput"),
    AModeler::eNullVector, ACRX_T("eNullVector"),
    AModeler::eNullNormalVector, ACRX_T("eNullNormalVector"),
    AModeler::eBadPlane, ACRX_T("eBadPlane"),
    AModeler::eBadLine, ACRX_T("eBadLine"),
    AModeler::eBadAxis, ACRX_T("eBadAxis"),
    AModeler::eBadTransform, ACRX_T("eBadTransform"),
    AModeler::eInputBodiesMustNotBeNegated, ACRX_T("eInputBodiesMustNotBeNegated"),
    AModeler::eRadiusMustBePositive, ACRX_T("eRadiusMustBePositive"),
    AModeler::eRadiusMustBeNonNegative, ACRX_T("eRadiusMustBeNonNegative"),
    AModeler::eRadiusMustNotBeZero, ACRX_T("eRadiusMustNotBeZero"),
    AModeler::eApproximationMustBeAtLeastFour, ACRX_T("eApproximationMustBeAtLeastFour"),
    AModeler::eScaleFactorMustBePositive, ACRX_T("eScaleFactorMustBePositive"),
    AModeler::eAngleMustNotBeZero, ACRX_T("eAngleMustNotBeZero"),
    AModeler::eBodyPointerIsNull, ACRX_T("eBodyPointerIsNull"),
    AModeler::eFacePointerIsNull, ACRX_T("eFacePointerIsNull"),
    AModeler::eEdgePointerIsNull, ACRX_T("eEdgePointerIsNull"),
    AModeler::eVertexPointerIsNull, ACRX_T("eVertexPointerIsNull"),
    AModeler::ePolygonPointerIsNull, ACRX_T("ePolygonPointerIsNull"),
    AModeler::eProfilePolygonPointerIsNull, ACRX_T("eProfilePolygonPointerIsNull"),
    AModeler::ePathPolygonPointerIsNull, ACRX_T("ePathPolygonPointerIsNull"),
    AModeler::eBodyIsNegative, ACRX_T("eBodyIsNegative"),
    AModeler::eFileNameIsNull, ACRX_T("eFileNameIsNull"),
    AModeler::eBadFile, ACRX_T("eBadFile"),
    AModeler::eFilePointerIsNull, ACRX_T("eFilePointerIsNull"),
    AModeler::eFileOpenError, ACRX_T("eFileOpenError"),
    AModeler::eFileReadError, ACRX_T("eFileReadError"),
    AModeler::eFileWriteError, ACRX_T("eFileWriteError"),
    AModeler::eSaveError, ACRX_T("eSaveError"),
    AModeler::eRestoreError, ACRX_T("eRestoreError"),
    AModeler::eBadDataRestored, ACRX_T("eBadDataRestored"),
    AModeler::eFileIsNewerThanCurrentVersionOfModeler, ACRX_T("eFileIsNewerThanCurrentVersionOfModeler"),
    AModeler::eBoxSizesMustNotBeZero, ACRX_T("eBoxSizesMustNotBeZero"),
    AModeler::eMajorRadiusMustBeGreaterThanMinorRadius, ACRX_T("eMajorRadiusMustBeGreaterThanMinorRadius"),
    AModeler::eInnerRadiusMustBeSmallerThanOuterRadius, ACRX_T("eInnerRadiusMustBeSmallerThanOuterRadius"),
    AModeler::eInnerRadiusCanBeZeroOnlyIfOuterRadiusIsZero, ACRX_T("eInnerRadiusCanBeZeroOnlyIfOuterRadiusIsZero"),
    AModeler::eViewPointCoincidesWithTargetPoint, ACRX_T("eViewPointCoincidesWithTargetPoint"),
    AModeler::eEpsilonMustBePositive, ACRX_T("eEpsilonMustBePositive"),
    AModeler::eCallbackObjectPointerIsNull, ACRX_T("eCallbackObjectPointerIsNull"),
    AModeler::ePickingNotPossible, ACRX_T("ePickingNotPossible"),
    AModeler::eAtLeast4NonCoplanarPointsRequired, ACRX_T("eAtLeast4NonCoplanarPointsRequired"),
    AModeler::ePointsDoNotDefineConvexPolyhedron, ACRX_T("ePointsDoNotDefineConvexPolyhedron"),
    AModeler::eApexMustNotLieInPolygon, ACRX_T("eApexMustNotLieInPolygon"),
    AModeler::eExtrusionVectorMustNotBeParallelToPolygon, ACRX_T("eExtrusionVectorMustNotBeParallelToPolygon"),
    AModeler::eAxisOfRevolutionMustLieInPolygonPlane, ACRX_T("eAxisOfRevolutionMustLieInPolygonPlane"),
    AModeler::eAxisOfRevolutionIntersectsPolygon, ACRX_T("eAxisOfRevolutionIntersectsPolygon"),
    AModeler::eBadNormal, ACRX_T("eBadNormal"),
    AModeler::eBadPolygon, ACRX_T("eBadPolygon"),
    AModeler::ePolygonIsSelfIntersectingOrTouching, ACRX_T("ePolygonIsSelfIntersectingOrTouching"),
    AModeler::eBadRelativePolygonPosition, ACRX_T("eBadRelativePolygonPosition"),
    AModeler::eCannotCreateFillet, ACRX_T("eCannotCreateFillet"),
    AModeler::eBadArcCenter, ACRX_T("eBadArcCenter"),
    AModeler::eRadiusTooSmall, ACRX_T("eRadiusTooSmall"),
    AModeler::eFilletRadiusMustBePositive, ACRX_T("eFilletRadiusMustBePositive"),
    AModeler::eCannotFilletVerticesBelongingToArcs, ACRX_T("eCannotFilletVerticesBelongingToArcs"),
    AModeler::eFirstAndLastVertexInEndpointRevolutionMustNotBeFilleted, ACRX_T("eFirstAndLastVertexInEndpointRevolutionMustNotBeFilleted"),
    AModeler::eArcBetweenLastAndFirstVertexNotAllowedForEndpointRevolution, ACRX_T("eArcBetweenLastAndFirstVertexNotAllowedForEndpointRevolution"),
    AModeler::eEntitiesSectionNotFoundInDxfFile, ACRX_T("eEntitiesSectionNotFoundInDxfFile"),
    AModeler::ePolylineEntityNotFoundInDxfFile, ACRX_T("ePolylineEntityNotFoundInDxfFile"),
    AModeler::ePolylineMustBeClosed, ACRX_T("ePolylineMustBeClosed"),
    AModeler::e3dPolylineOrMeshNotAllowed, ACRX_T("e3dPolylineOrMeshNotAllowed"),
    AModeler::eBadDxfFile, ACRX_T("eBadDxfFile"),
    AModeler::ePointsAreColinearOrCoincident, ACRX_T("ePointsAreColinearOrCoincident"),
    AModeler::eSourceArgumentsAreColinearOrCoincident, ACRX_T("eSourceArgumentsAreColinearOrCoincident"),
    AModeler::eDestinationArgumentsAreColinearOrCoincident, ACRX_T("eDestinationArgumentsAreColinearOrCoincident"),
    AModeler::ePointsAreCoplanar, ACRX_T("ePointsAreCoplanar"),
    AModeler::eChamferingDistanceMustBePositive, ACRX_T("eChamferingDistanceMustBePositive"),
    AModeler::eOnlyManifoldEdgesCanBeFilletedAndChamfered, ACRX_T("eOnlyManifoldEdgesCanBeFilletedAndChamfered"),
    AModeler::eOnlyStraightAndCircularEdgesCanBeFilletedAndChamfered, ACRX_T("eOnlyStraightAndCircularEdgesCanBeFilletedAndChamfered"),
    AModeler::ePlanarEdgesCannotBeFilletedAndChamfered, ACRX_T("ePlanarEdgesCannotBeFilletedAndChamfered"),
    AModeler::eAtLeastOneEdgeExpected, ACRX_T("eAtLeastOneEdgeExpected"),
    AModeler::eFilletRadiusTooLarge, ACRX_T("eFilletRadiusTooLarge"),
    AModeler::eChamferDistanceTooLarge, ACRX_T("eChamferDistanceTooLarge"),
    AModeler::eCannotFilletEdge, ACRX_T("eCannotFilletEdge"),
    AModeler::eCannotMitreEdgesOfDifferentConvexity, ACRX_T("eCannotMitreEdgesOfDifferentConvexity"),
    AModeler::eTooComplexMixedConvexityCap, ACRX_T("eTooComplexMixedConvexityCap"),
    AModeler::eNotYetImplemented, ACRX_T("eNotYetImplemented"),
    AModeler::eCircleIsNotValid, ACRX_T("eCircleIsNotValid"),
    AModeler::eBaseNormalPerpendicularToAxisVector, ACRX_T("eBaseNormalPerpendicularToAxisVector"),
    AModeler::eEndCentersMustHaveEqualDistance, ACRX_T("eEndCentersMustHaveEqualDistance"),
    AModeler::eFaceMustNotBelongToABody, ACRX_T("eFaceMustNotBelongToABody"),
    AModeler::eFaceHasNoEdges, ACRX_T("eFaceHasNoEdges"),
    AModeler::eOneSidedFaceExpected, ACRX_T("eOneSidedFaceExpected"),
    AModeler::eProfileFacesMustHaveTheSameNumberOfEdges, ACRX_T("eProfileFacesMustHaveTheSameNumberOfEdges"),
    AModeler::eAtLeastTwoProfilesExpected, ACRX_T("eAtLeastTwoProfilesExpected"),
    AModeler::eBodyProfileMustContainExactlyOneFace, ACRX_T("eBodyProfileMustContainExactlyOneFace"),
    AModeler::eProfileFaceHasNoEdges, ACRX_T("eProfileFaceHasNoEdges"),
    AModeler::eBadMorphingMap, ACRX_T("eBadMorphingMap"),
    AModeler::eEdgesOfFirstProfileCannotBeMarkedApproximating, ACRX_T("eEdgesOfFirstProfileCannotBeMarkedApproximating"),
    AModeler::eBaseSizesMustBePositive, ACRX_T("eBaseSizesMustBePositive"),
    AModeler::eTopCircleMustLieAboveBaseRectangle, ACRX_T("eTopCircleMustLieAboveBaseRectangle"),
    AModeler::eFilletByRadiusOrArcByBulgeTypeExpected, ACRX_T("eFilletByRadiusOrArcByBulgeTypeExpected"),
    AModeler::eArcByRadiusTypeExpected, ACRX_T("eArcByRadiusTypeExpected"),
    AModeler::eArc3dTypeExpected, ACRX_T("eArc3dTypeExpected"),
    AModeler::eCannotCreateTouchingCircle, ACRX_T("eCannotCreateTouchingCircle"),
    AModeler::eNonPlanarPolygon, ACRX_T("eNonPlanarPolygon"),
    AModeler::eNonPlanarProfileFace, ACRX_T("eNonPlanarProfileFace"),
    AModeler::eFaceMustHaveAtLeastThreeEdges, ACRX_T("eFaceMustHaveAtLeastThreeEdges"),
    AModeler::ePolygonPointsCoincide, ACRX_T("ePolygonPointsCoincide"),
    AModeler::eBadPath, ACRX_T("eBadPath"),
    AModeler::eBadProfileAndPathOrientation, ACRX_T("eBadProfileAndPathOrientation"),
    AModeler::eFirstPathPointMustLieInStartProfilePlane, ACRX_T("eFirstPathPointMustLieInStartProfilePlane"),
    AModeler::eLastPathPointMustLieInEndProfilePlane, ACRX_T("eLastPathPointMustLieInEndProfilePlane"),
    AModeler::eWidthTooSmall, ACRX_T("eWidthTooSmall"),
    AModeler::eHeightTooSmall, ACRX_T("eHeightTooSmall"),
    AModeler::eEndProfileNotAllowedWhenPathIsClosed, ACRX_T("eEndProfileNotAllowedWhenPathIsClosed"),
    AModeler::eScaleFactorNotAllowedWhenPathIsClosed, ACRX_T("eScaleFactorNotAllowedWhenPathIsClosed"),
    AModeler::eTwistAngleNotAllowedWhenPathIsClosed, ACRX_T("eTwistAngleNotAllowedWhenPathIsClosed"),
    AModeler::eMorphingMustBeIdentityWhenPathIsClosed, ACRX_T("eMorphingMustBeIdentityWhenPathIsClosed"),
    AModeler::eExtrusionBodyLooksSelfIntersecting, ACRX_T("eExtrusionBodyLooksSelfIntersecting"),
    AModeler::eMorphingMapRequiresEndProfile, ACRX_T("eMorphingMapRequiresEndProfile"),
    AModeler::eNegativeIndexInMorphingMap, ACRX_T("eNegativeIndexInMorphingMap"),
    AModeler::eFixedPointMustLieInPolygonPlane, ACRX_T("eFixedPointMustLieInPolygonPlane"),
    AModeler::eTriStripsMayBeGeneratedOnlyWhenCachingTriangles, ACRX_T("eTriStripsMayBeGeneratedOnlyWhenCachingTriangles"),
    AModeler::eStartProfileNormalHasOppositeDirectionThanFirstPathSegment, ACRX_T("eStartProfileNormalHasOppositeDirectionThanFirstPathSegment"),
    AModeler::eEndProfileNormalHasOppositeDirectionThanLastPathSegment, ACRX_T("eEndProfileNormalHasOppositeDirectionThanLastPathSegment"),
    AModeler::eStartProfileIsParallelWithFirstPathSegment, ACRX_T("eStartProfileIsParallelWithFirstPathSegment"),
    AModeler::eEndProfileIsParallelWithLastPathSegment, ACRX_T("eEndProfileIsParallelWithLastPathSegment"),
    AModeler::eProfilePolygonMustContainAtLeastOnePoint, ACRX_T("eProfilePolygomNustContainAtLeastOnePoint"),
    AModeler::eArcByRadiusNotAllowedForPathPolygons_UseArc3d, ACRX_T("eArcByRadiusNotAllowedForPathPolygons_UseArc3d"),
    AModeler::eArcByBulgeNotAllowedForPathPolygons_UseArc3d, ACRX_T("eArcByBulgeNotAllowedForPathPolygons_UseArc3d"),
    AModeler::eNumberOfLinearSegmentsMustBeAtLeastOne, ACRX_T("eNumberOfLinearSegmentsMustBeAtLeastOne"),
    AModeler::eZeroBulgeNotAllowed, ACRX_T("eZeroBulgeNotAllowed"),
    AModeler::eFixedPointMustLieInStartProfilePlane, ACRX_T("eFixedPointMustLieInStartProfilePlane"),
    AModeler::eBodyCannotBeClosed, ACRX_T("eBodyCannotBeClosed"),
    AModeler::ePolygonNormalNotPerpendicularToPolygonPlane, ACRX_T("ePolygonNormalNotPerpendicularToPolygonPlane"),
    AModeler::eSizeMustBePositive, ACRX_T("eSizeMustBePositive"),
    AModeler::ePointerIsNull, ACRX_T("ePointerIsNull"),
    AModeler::eToleranceMustBePositive, ACRX_T("eToleranceMustBePositive"),
    AModeler::eValueMustBePositive, ACRX_T("eValueMustBePositive"),
    AModeler::ePartnerEdgesOfNonManifoldEdgeCannotBeOrdered, ACRX_T("ePartnerEdgesOfNonManifoldEdgeCannotBeOrdered"),
    AModeler::eNonManifoldEdgesMustHaveEvenNumberOfPartners, ACRX_T("eNonManifoldEdgesMustHaveEvenNumberOfPartners"),
    AModeler::eFaceMustHaveManifoldEdgesOnly, ACRX_T("eFaceMustHaveManifoldEdgesOnly"),
    AModeler::eStitchingFacesDidNotProduceAValidBody, ACRX_T("eStitchingFacesDidNotProduceAValidBody"),
    AModeler::eFaceCanNotBeMoved, ACRX_T("eFaceCanNotBeMoved"),
    AModeler::eManifoldEdgeExpected, ACRX_T("eManifoldEdgeExpected"),
    AModeler::eEdgeSharedByTwoDifferentFacesExpected, ACRX_T("eEdgeSharedByTwoDifferentFacesExpected"),
    AModeler::eCoplanarFacesExpected, ACRX_T("eCoplanarFacesExpected"),
    AModeler::eInvalidVector, ACRX_T("eInvalidVector"),
    AModeler::eAngleMustBePositive, ACRX_T("eAngleMustBePositive"),
    AModeler::eMinNumberOfFacesInSurfaceMustBeAtLeastTwo, ACRX_T("eMinNumberOfFacesInSurfaceMustBeAtLeastTwo"),
    AModeler::eUnspecifiedCurveTypeExpected, ACRX_T("eUnspecifiedCurveTypeExpected"),
    AModeler::eInvalidTerrainBody, ACRX_T("eInvalidTerrainBody"),
    AModeler::eHeightMustBePositive, ACRX_T("eHeightMustBePositive"),
    AModeler::eCannotCreateLoopOfEdges, ACRX_T("eCannotCreateLoopOfEdges"),
    AModeler::eTerrainSurfaceContainsHole, ACRX_T("eTerrainSurfaceContainsHole"),
    AModeler::eBadIndexInMorphingMap, ACRX_T("eBadIndexInMorphingMap"),
    AModeler::eStartProfileIsWrong, ACRX_T("eStartProfileIsWrong"),
    AModeler::eEndProfileIsWrong, ACRX_T("eEndProfileIsWrong"),
    AModeler::eExtrusionPathIsWrong, ACRX_T("eExtrusionPathIsWrong"),
    AModeler::eStartProfileMustHaveOnlySingleLoop, ACRX_T("eStartProfileMustHaveOnlySingleLoop"),
    AModeler::eEndProfileMustHaveOnlySingleLoop, ACRX_T("eEndProfileMustHaveOnlySingleLoop"),
    AModeler::eInternalError, ACRX_T("eInternalError"),
    AModeler::eOk, ACRX_T("eOk, should never happen")
};

//
// getErrorMsg
//
// Passes back a char pointer to the error message
// associated with the code passed.
//
ACHAR*
getErrorMsg(ErrorCode err)
{
    for (int i = 0; ErrorMessages[i].code != AModeler::eOk; i++)
        if (ErrorMessages[i].code == err)
            return ErrorMessages[i].msg;
    return NULL;
}
