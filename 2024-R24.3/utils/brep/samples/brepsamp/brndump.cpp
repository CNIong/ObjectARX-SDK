//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Mesh node dump utilities.

#include "brsample_pch.h"  //precompiled header

// include here



AcBr::ErrorStatus
nodeDump(const AcBrNode& node)
{
	AcBr::ErrorStatus returnValue = AcBr::eOk;

	// Determine the entity which contains this node
	AcBrEntity* entityAssociated = NULL;
	returnValue = node.getEntityAssociated(entityAssociated);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrNode::getEntityAssociated:"));
		errorReport(returnValue);
		delete entityAssociated;
		return returnValue;
	}
	entityAssociatedReport(entityAssociated);
	delete entityAssociated;

	AcGePoint3d nodePoint;
	returnValue = node.getPoint(nodePoint);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrNode::getPoint:"));
        errorReport(returnValue);
		return returnValue;
	}
	acutPrintf(ACRX_T("\n Node Point is ("));
	acutPrintf (ACRX_T("%lf, "), nodePoint.x);	
	acutPrintf (ACRX_T("%lf, "), nodePoint.y);
	acutPrintf (ACRX_T("%lf"), nodePoint.z);
	acutPrintf(ACRX_T(")\n"));	
	
	return returnValue;
}


AcBr::ErrorStatus
nodeDisplay(const AcBrNode& node, AcGePoint3dArray& pts)
{
	AcBr::ErrorStatus returnValue = AcBr::eOk;

	AcGePoint3d nodePoint;	
	returnValue = node.getPoint(nodePoint);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrNode::getPoint:"));
        errorReport(returnValue);
		return returnValue;
	}
    pts.append((const AcGePoint3d&)nodePoint);
    
	return returnValue;
}

