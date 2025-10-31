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
