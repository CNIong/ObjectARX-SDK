//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Vertex and point dump utilities.

#include "brsample_pch.h"  //precompiled header


// include here.



AcBr::ErrorStatus
vertexDump(const AcBrVertex& vertexEntity)
{
	AcBr::ErrorStatus returnValue = AcBr::eOk;

	AcGePoint3d vertexPoint;	
	returnValue = vertexEntity.getPoint(vertexPoint);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrVertex::getPoint:"));
        errorReport(returnValue);
		return returnValue;
	}
	acutPrintf(ACRX_T("\n Vertex Point is ("));
	acutPrintf (ACRX_T("%lf, "), vertexPoint.x);	
	acutPrintf (ACRX_T("%lf, "), vertexPoint.y);
	acutPrintf (ACRX_T("%lf"), vertexPoint.z);
	acutPrintf(ACRX_T(")\n"));	
	
	return returnValue;
}
