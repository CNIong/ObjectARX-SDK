// (C) Copyright 1996-2006 by Autodesk, Inc. 
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
