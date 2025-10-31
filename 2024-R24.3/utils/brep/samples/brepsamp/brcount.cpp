//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Source file for the ObjectARX application command "BRCOUNT".

#include "brsample_pch.h"  //precompiled header



// Abbreviations
#include "acdbabb.h"




// local function prototypes
static AcBr::ErrorStatus countComplexes	(const AcBrBrep& brepEntity);
static AcBr::ErrorStatus countShells	(const AcBrBrep& brepEntity);
static AcBr::ErrorStatus countFaces		(const AcBrBrep& brepEntity);
static AcBr::ErrorStatus countEdges		(const AcBrBrep& brepEntity);
static AcBr::ErrorStatus countVertices	(const AcBrBrep& brepEntity);


void
countSubents()
{
    AcBr::ErrorStatus returnValue = AcBr::eOk;
    Acad::ErrorStatus acadReturnValue = eOk;

    // Get the subentity path for a brep
	AcDbFullSubentPath subPath(kNullSubent);
	acadReturnValue = selectEntity(AcDb::kNullSubentType, subPath);
	if (acadReturnValue != eOk) {
		acutPrintf(ACRX_T("\n Error in getPath: %d"), acadReturnValue);
		return;
	}

	// Make a brep entity to access the solid
	AcBrBrep brepEntity;
	returnValue = ((AcBrEntity*)&brepEntity)->set(subPath);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrBrep::set:"));
		errorReport(returnValue);
		return;
	}

	// count the unique complexes in the brep
	returnValue = countComplexes(brepEntity);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in countComplexes:"));
		errorReport(returnValue);
		return;
	}

	// count the unique shells in the brep
	returnValue = countShells(brepEntity);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in countShells:"));
		errorReport(returnValue);
		return;
	}

	// count the unique faces in the brep
	returnValue = countFaces(brepEntity);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in countFaces:"));
		errorReport(returnValue);
		return;
	}

	// count the unique edges in the brep
	returnValue = countEdges(brepEntity);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in countEdges:"));
		errorReport(returnValue);
		return;
	}

	// count the unique vertices in the brep
	returnValue = countVertices(brepEntity);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in countVertices:"));
		errorReport(returnValue);
		return;
	}

	return;
}


static AcBr::ErrorStatus 
countComplexes(const AcBrBrep& brepEntity)
{
	AcBr::ErrorStatus returnValue = AcBr::eOk;

	// make a global complex traverser
	AcBrBrepComplexTraverser brepComplexTrav;
	returnValue = brepComplexTrav.setBrep(brepEntity);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrBrepComplexTraverser::setBrep:"));
		errorReport(returnValue);
		return returnValue;
	}

	// count the faces
	int complexCount = 0;
	while (!brepComplexTrav.done() && (returnValue == AcBr::eOk)) {
	    complexCount++;
		returnValue = brepComplexTrav.next();
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in AcBrBrepComplexTraverser::next:"));  
			errorReport(returnValue);
			return returnValue;
		}
	}
	acutPrintf(ACRX_T("\n ***Brep has %d complexes\n"), complexCount);	  

	return returnValue;
}


static AcBr::ErrorStatus 
countShells(const AcBrBrep& brepEntity)
{
	AcBr::ErrorStatus returnValue = AcBr::eOk;

	// make a global shell traverser
	AcBrBrepShellTraverser brepShellTrav;
	returnValue = brepShellTrav.setBrep(brepEntity);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrBrepShellTraverser::setBrep:"));
		errorReport(returnValue);
		return returnValue;
	}

	// count the shells
	int shellCount = 0;
	while (!brepShellTrav.done() && (returnValue == AcBr::eOk)) {
	    shellCount++;
		returnValue = brepShellTrav.next();
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in AcBrBrepShellTraverser::next:"));  
			errorReport(returnValue);
			return returnValue;
		}
	}
	acutPrintf(ACRX_T("\n ***Brep has %d shells\n"), shellCount);	  

	return returnValue;
}


static AcBr::ErrorStatus 
countFaces(const AcBrBrep& brepEntity)
{
	AcBr::ErrorStatus returnValue = AcBr::eOk;

	// make a global face traverser
	AcBrBrepFaceTraverser brepFaceTrav;
	returnValue = brepFaceTrav.setBrep(brepEntity);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrBrepFaceTraverser::setBrep:"));
		errorReport(returnValue);
		return returnValue;
	}

	// count the faces
	int faceCount = 0;
	while (!brepFaceTrav.done() && (returnValue == AcBr::eOk)) {
	    faceCount++;
		returnValue = brepFaceTrav.next();
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in AcBrBrepFaceTraverser::next:"));  
			errorReport(returnValue);
			return returnValue;
		}
	}
	acutPrintf(ACRX_T("\n ***Brep has %d faces\n"), faceCount);	  

	return returnValue;
}


static AcBr::ErrorStatus 
countEdges(const AcBrBrep& brepEntity)
{
	AcBr::ErrorStatus returnValue = AcBr::eOk;

	// make a global edge traverser
	AcBrBrepEdgeTraverser brepEdgeTrav;
	returnValue = brepEdgeTrav.setBrep(brepEntity);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrBrepEdgeTraverser::setBrep:"));
		errorReport(returnValue);
		return returnValue;
	}

	// count the edges
	int edgeCount = 0;
	while (!brepEdgeTrav.done() && (returnValue == AcBr::eOk)) {
	    edgeCount++;
		returnValue = brepEdgeTrav.next();
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in AcBrBrepEdgeTraverser::next:"));  
			errorReport(returnValue);
			return returnValue;
		}
	}
	acutPrintf(ACRX_T("\n ***Brep has %d edges\n"), edgeCount);	  

	return returnValue;
}


static AcBr::ErrorStatus 
countVertices(const AcBrBrep& brepEntity)
{
	AcBr::ErrorStatus returnValue = AcBr::eOk;

	// make a global vertex traverser
	AcBrBrepVertexTraverser brepVertexTrav;
	returnValue = brepVertexTrav.setBrep(brepEntity);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrBrepVertexTraverser::setBrep:"));
		errorReport(returnValue);
		return returnValue;
	}

	// count the vertices
	int vertexCount = 0;
	while (!brepVertexTrav.done() && (returnValue == AcBr::eOk)) {
	    vertexCount++;
		returnValue = brepVertexTrav.next();
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in AcBrBrepVertexTraverser::next:"));  
			errorReport(returnValue);
			return returnValue;
		}
	}
	acutPrintf(ACRX_T("\n ***Brep has %d vertices\n"), vertexCount);	  

	return returnValue;
}
