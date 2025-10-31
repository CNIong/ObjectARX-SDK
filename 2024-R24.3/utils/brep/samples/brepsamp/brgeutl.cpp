//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Source file for AcGe curve and surface utilities.

#include "brsample_pch.h"  //precompiled header


// include here



// Utility function to extract a useful, unbounded surface with native
// surface definition data, from the external bounded surface
AcBr::ErrorStatus
getNativeSurface(const AcBrFace& faceEntity,
                 AcGeSurface*&   surfaceGeometry,
                 AcGeSurface*&   nativeGeometry)
{
    AcBr::ErrorStatus returnValue = faceEntity.getSurface(surfaceGeometry);  
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrFace::getSurface:"));
    	errorReport(returnValue);
        return returnValue;
	}
	if (surfaceGeometry == NULL) {
		acutPrintf(ACRX_T("\n getNativeSurface: external bounded surface is undefined\n"));
        returnValue = AcBr::eMissingGeometry;
        return returnValue;
	}
	if (surfaceGeometry->type() != kExternalBoundedSurface) {
		acutPrintf(ACRX_T("\n getNativeSurface: surface is not an external bounded surface\n"));
        returnValue = AcBr::eMissingGeometry;
        return returnValue;
	}
	AcGeExternalSurface baseGeometry;
	((AcGeExternalBoundedSurface*)surfaceGeometry)->getBaseSurface(baseGeometry);
	if (!baseGeometry.isDefined()) {
		acutPrintf(ACRX_T("\n getNativeSurface: external surface is undefined\n"));
        returnValue = AcBr::eMissingGeometry;
        return returnValue;
	}
	if (!baseGeometry.isNativeSurface(nativeGeometry)
	    || (nativeGeometry == NULL)) {
		acutPrintf(ACRX_T("\n getNativeSurface: native surface is undefined\n"));
        returnValue = AcBr::eMissingGeometry;
        return returnValue;
	}
    return returnValue;
}


// Utility function to extract a useful, bounded curve with native
// curve definition data, from the external (bounded) curve
AcBr::ErrorStatus
getNativeCurve(const AcBrEdge& edgeEntity,
               AcGeCurve3d*&   curveGeometry,
               AcGeCurve3d*&   nativeGeometry)
{
    AcBr::ErrorStatus returnValue = edgeEntity.getCurve(curveGeometry);  
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrEdge::getCurve:"));
        errorReport(returnValue);
        return returnValue;
	}
	if (curveGeometry == NULL) {
		acutPrintf(ACRX_T("\n getNativeCurve: external 3d curve is undefined\n"));
        returnValue = AcBr::eMissingGeometry;
        return returnValue;
	}
	if (curveGeometry->type() != kExternalCurve3d) {
		acutPrintf(ACRX_T("\n getNativeCurve: curve is not an external 3d curve\n"));
        returnValue = AcBr::eMissingGeometry;
        return returnValue;
	}
	if (!((AcGeExternalCurve3d*)curveGeometry)->isDefined()) {
		acutPrintf(ACRX_T("\n getNativeCurve: external 3d curve is undefined\n"));
        returnValue = AcBr::eMissingGeometry;
        return returnValue;
	}
	if (!((AcGeExternalCurve3d*)curveGeometry)->isNativeCurve(nativeGeometry)
	    || (nativeGeometry == NULL)) {
		acutPrintf(ACRX_T("\n getNativeCurve: native 3d curve is undefined\n"));
        returnValue = AcBr::eMissingGeometry;
        return returnValue;
	}
    return returnValue;
}


// Utility function to extract a useful, bounded and oriented curve
// with native curve definition data, from the external (bounded) curve
AcBr::ErrorStatus
getNativeOrientedCurve(const AcBrLoopEdgeTraverser& loopEdge,
                       AcGeCurve3d*&                curveGeometry,
                       AcGeCurve3d*&                nativeGeometry)
{
    AcBr::ErrorStatus returnValue = loopEdge.getOrientedCurve(curveGeometry);  
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrLoopEdgeTraverser::getOrientedCurve:"));
        errorReport(returnValue);
        return returnValue;
	}
	if (curveGeometry == NULL) {
		acutPrintf(ACRX_T("\n getNativeOrientedCurve: external 3d curve is undefined\n"));
        returnValue = AcBr::eMissingGeometry;
        return returnValue;
	}
	if (curveGeometry->type() != kExternalCurve3d) {
		acutPrintf(ACRX_T("\n getNativeOrientedCurve: curve is not an external 3d curve\n"));
        returnValue = AcBr::eMissingGeometry;
        return returnValue;
	}
	if (!((AcGeExternalCurve3d*)curveGeometry)->isDefined()) {
		acutPrintf(ACRX_T("\n getNativeOrientedCurve: external 3d curve is undefined\n"));
        returnValue = AcBr::eMissingGeometry;
        return returnValue;
	}
	if (!((AcGeExternalCurve3d*)curveGeometry)->isNativeCurve(nativeGeometry)
	    || (nativeGeometry == NULL)) {
		acutPrintf(ACRX_T("\n getNativeOrientedCurve: native 3d curve is undefined\n"));
        returnValue = AcBr::eMissingGeometry;
        return returnValue;
	}
    return returnValue;
}


// Utility function to extract a useful 2d nurb curve with native
// definition data, from the external paramcurve
AcBr::ErrorStatus
getNativeParamCurve(const AcBrLoopEdgeTraverser& loopEdge,
                    AcGeCurve2d*&                pcurveGeometry,
                    AcGeNurbCurve2d&             nurbGeometry)
{
    AcBr::ErrorStatus returnValue = loopEdge.getParamCurve(pcurveGeometry);  
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrLoopEdgeTraverser::getParamCurve:"));
        errorReport(returnValue);
        return returnValue;
	}
	if (pcurveGeometry == NULL) {
		acutPrintf(ACRX_T("\n getNativeParamCurve: external param curve is undefined\n"));
        returnValue = AcBr::eMissingGeometry;
        return returnValue;
	}
	if (pcurveGeometry->type() != kExternalCurve2d) {
		acutPrintf(ACRX_T("\n getNativeParamCurve: parameter curve is not an external 2d curve\n"));
        returnValue = AcBr::eMissingGeometry;
        return returnValue;
	}
	if (!((AcGeExternalCurve2d*)pcurveGeometry)->isDefined()) {
		acutPrintf(ACRX_T("\n getNativeParamCurve: external param curve is undefined\n"));
        returnValue = AcBr::eMissingGeometry;
        return returnValue;
	}
	if (!((AcGeExternalCurve2d*)pcurveGeometry)->isNurbCurve(nurbGeometry)) {
		acutPrintf(ACRX_T("\n getNativeParamCurve: native 2d nurb curve is undefined\n"));
        returnValue = AcBr::eMissingGeometry;
        return returnValue;
	}
    return returnValue;
}
