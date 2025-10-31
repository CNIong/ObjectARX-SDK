///////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form. 
//
// DESCRIPTION:
//
// The modeler throws an exception of type ErrorCode anytime it encounters an 
// error condition.
//
// To indicate an error (throw an exception), use the checkError() function.
// For example:
//
//   checkError(factor > epsNor(), eScaleFactorMustBePositive);
//
///////////////////////////////////////////////////////////////////////////////
#ifndef AMODELER_INC_ERRCODES_H
#define AMODELER_INC_ERRCODES_H


#include <tchar.h>

AMODELER_NAMESPACE_BEGIN

// An enum of all ErrorCodes which can be thrown by AModeler. When adding a new 
// ErrorCode, do not forget to update the errorCodeStrings[] array in file
// errcodes.cpp so that the errorString(ErrorCode) function can return the 
// ErrorCode as a string.
// 
enum ErrorCode
{
    eOk = 0,                    // This value should never be thrown
    eFail,                      
    eViewPointLiesInsideScene,
    eBadBodyGeometry,
    eBadSurfaceType,
    eBadCurveType,
    eBadInput,
    eNullVector,
    eNullNormalVector,
    eBadPlane,
    eBadLine,
    eBadAxis,
    eBadTransform,
    ePointLiesInPlane,
    eInputBodiesMustNotBeNegated,
    eRadiusMustBePositive,                                 
    eRadiusMustBeNonNegative,
    eRadiusMustNotBeZero,
    eApproximationMustBeAtLeastFour,
    eScaleFactorMustBePositive,
    eAngleMustNotBeZero,
    eBodyPointerIsNull,
    eFacePointerIsNull,
    eEdgePointerIsNull,
    eVertexPointerIsNull,
    ePolygonPointerIsNull,
    eProfilePolygonPointerIsNull,
    ePathPolygonPointerIsNull,
    eBodyIsNegative,
    eIntervalIsNull,
    eFileNameIsNull,
    eBadFile,
    eIncorrectFile,
    eFilePointerIsNull,
    eFileOpenError,                                        
    eFileReadError,
    eFileWriteError,
    eSaveError,
    eRestoreError,
    eBadDataRestored,
    eFileIsNewerThanCurrentVersionOfModeler,
    eBoxSizesMustNotBeZero,
    eMajorRadiusMustBeGreaterThanMinorRadius,
    eInnerRadiusMustBeSmallerThanOuterRadius,
    eInnerRadiusCanBeZeroOnlyIfOuterRadiusIsZero,
    eViewPointCoincidesWithTargetPoint,                    
    eEpsilonMustBePositive,
    eCallbackObjectPointerIsNull,
    ePickingNotPossible,
    eAtLeast4NonCoplanarPointsRequired,
    ePointsDoNotDefineConvexPolyhedron,
    eApexMustNotLieInPolygon,
    eExtrusionVectorMustNotBeParallelToPolygon,
    eAxisOfRevolutionMustLieInPolygonPlane,
    eAxisOfRevolutionIntersectsPolygon,
    eBadNormal,                                            
    eBadPolygon,
    ePolygonIsSelfIntersectingOrTouching,
    eBadRelativePolygonPosition,
    eCannotCreateFillet,
    eBadArcCenter,
    eRadiusTooSmall,
    eFilletRadiusMustBePositive,
    eCannotFilletVerticesBelongingToArcs,
    eFirstAndLastVertexInEndpointRevolutionMustNotBeFilleted,      
    eArcBetweenLastAndFirstVertexNotAllowedForEndpointRevolution,  
    eEntitiesSectionNotFoundInDxfFile,
    ePolylineEntityNotFoundInDxfFile,
    ePolylineMustBeClosed,
    e3dPolylineOrMeshNotAllowed,
    eBadDxfFile,
    ePointsAreColinearOrCoincident,
    eSourceArgumentsAreColinearOrCoincident,
    eDestinationArgumentsAreColinearOrCoincident,
    ePointsAreCoplanar,
    eChamferingDistanceMustBePositive,
    eOnlyManifoldEdgesCanBeFilletedAndChamfered,
    eOnlyStraightAndCircularEdgesCanBeFilletedAndChamfered,
    ePlanarEdgesCannotBeFilletedAndChamfered,
    eAtLeastOneEdgeExpected,
    eFilletRadiusTooLarge,
    eChamferDistanceTooLarge,
    eCannotFilletEdge,
    eCannotMitreEdgesOfDifferentConvexity,
    eTooComplexMixedConvexityCap,
    eNotYetImplemented,
    eCircleIsNotValid,
    eBaseNormalPerpendicularToAxisVector,
    eEndCentersMustHaveEqualDistance,
    eFaceMustNotBelongToABody,
    eFaceHasNoEdges,
    eOneSidedFaceExpected,
    eProfileFacesMustHaveTheSameNumberOfEdges,
    eAtLeastTwoProfilesExpected,
    eBodyProfileMustContainExactlyOneFace,
    eProfileFaceHasNoEdges,
    eBadMorphingMap,
    eEdgesOfFirstProfileCannotBeMarkedApproximating,
    eBaseSizesMustBePositive,
    eTopCircleMustLieAboveBaseRectangle,
    eFilletByRadiusOrArcByBulgeTypeExpected,
    eArcByRadiusTypeExpected,
    eArc3dTypeExpected,
    eCannotCreateTouchingCircle,
    eNonPlanarPolygon,
    eNonPlanarProfileFace,
    eFaceMustHaveAtLeastThreeEdges,
    ePolygonPointsCoincide,
    eBadPath,
    eBadProfileAndPathOrientation,
    eFirstPathPointMustLieInStartProfilePlane,
    eLastPathPointMustLieInEndProfilePlane,
    eWidthTooSmall,
    eHeightTooSmall,
    eEndProfileNotAllowedWhenPathIsClosed,
    eScaleFactorNotAllowedWhenPathIsClosed,
    eTwistAngleNotAllowedWhenPathIsClosed,
    eMorphingMustBeIdentityWhenPathIsClosed,
    eExtrusionBodyLooksSelfIntersecting,
    eMorphingMapRequiresEndProfile,
    eNegativeIndexInMorphingMap,
    eFixedPointMustLieInPolygonPlane,
    eTriStripsMayBeGeneratedOnlyWhenCachingTriangles,
    eStartProfileNormalHasOppositeDirectionThanFirstPathSegment,
    eEndProfileNormalHasOppositeDirectionThanLastPathSegment,
    eStartProfileIsParallelWithFirstPathSegment,
    eEndProfileIsParallelWithLastPathSegment,
    eProfilePolygonMustContainAtLeastOnePoint,
    eArcByRadiusNotAllowedForPathPolygons_UseArc3d,
    eArcByBulgeNotAllowedForPathPolygons_UseArc3d,
    eNumberOfLinearSegmentsMustBeAtLeastOne,
    eZeroBulgeNotAllowed,
    eFixedPointMustLieInStartProfilePlane,
    eBodyCannotBeClosed,
    ePolygonNormalNotPerpendicularToPolygonPlane,
    eSizeMustBePositive,
    ePointerIsNull,
    eToleranceMustBePositive,
    eValueMustBePositive,
    ePartnerEdgesOfNonManifoldEdgeCannotBeOrdered,
    eNonManifoldEdgesMustHaveEvenNumberOfPartners,
    eFaceMustHaveManifoldEdgesOnly,
    eStitchingFacesDidNotProduceAValidBody,
    eFaceCanNotBeMoved,
    eManifoldEdgeExpected,
    eEdgeSharedByTwoDifferentFacesExpected,
    eCoplanarFacesExpected,
    eInvalidVector,
    eAngleMustBePositive,
    eMinNumberOfFacesInSurfaceMustBeAtLeastTwo,
    eUnspecifiedCurveTypeExpected,
    eInvalidTerrainBody,
    eHeightMustBePositive,
    eCannotCreateLoopOfEdges,
    eTerrainSurfaceContainsHole,
    eBadIndexInMorphingMap,
    eStartProfileIsWrong,
    eEndProfileIsWrong,
    eExtrusionPathIsWrong,
    eStartProfileMustHaveOnlySingleLoop,
    eEndProfileMustHaveOnlySingleLoop,
    eInternalError                                         = 1000
}; // enum ErrorCode

// By default AModeler does very strict body validation during boolean operation.
// Thus sometimes boolean operation throws exceptions. This is generally fine
// since the client code will capture the expcetion and recover from the problem. 
// But the client code is not possible get the result body once a exception is 
// thrown. This makes sense as using a invalid body could cause problems 
//
// While we are doing 2D Section we use boolean operation to cut the target body.
// The result body then put into the HLR algorithm and will be discarded after 
// that. If we get an exception from the boolean operation we do not have a chance
// to generate 2d section result any more. Since the body will be discarded after 
// HLR algorithm it should be safe to just ignore those exceptions. 
//
// The methods below provides an option to temporarily disable exception been 
// thrown while encounter errors.

DllImpExp void disableExceptionForError(unsigned int err);
DllImpExp void enableExceptionForError(unsigned int err);
DllImpExp bool isExceptionDisabledForError(unsigned int err);


#ifdef _DEBUG

#define checkError(testExpr, err) checkErrorFunc(testExpr, err, _T(__FILE__), __LINE__)

DllImpExp void checkErrorFunc(bool testExpr, ErrorCode, const wchar_t* file, int line);

#else

inline void checkError(bool testExpr, ErrorCode err)
{
    if (!testExpr && !isExceptionDisabledForError(static_cast<unsigned int>(err)))
        throw err;
}

#endif


// Returns the error string corresponding to the ErrorCode or a string "nnn" 
// where "nnn" is the error number if there is no error string for the given 
// ErrorCode
//
DllImpExp const wchar_t* errorString(ErrorCode);

AMODELER_NAMESPACE_END
#endif
