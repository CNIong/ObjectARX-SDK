//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Brep mesh utilities.

#include "brsample_pch.h"  //precompiled header



// Abbreviations
#include "acdbabb.h"




AcBr::ErrorStatus
brepMesh(const AcBrBrep& brepEntity, Adesk::Boolean displayElements)
{ 
    AcBr::ErrorStatus returnValue = AcBr::eOk;

	// validate the brep vs. the brep "owner"
	AcBrBrep brepOwner;
	returnValue = brepEntity.getBrep(brepOwner);
	if (returnValue != eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrBrep::getBrep:"));
		errorReport(returnValue);
		return returnValue;
	}
	if (!brepEntity.isEqualTo(&brepOwner)) {
		acutPrintf(ACRX_T("\n Brep owner is out of sync with brep!"));
		return (AcBr::ErrorStatus)Acad::eAmbiguousOutput;
	}

	// Ask for the mesh controls
	Adesk::UInt32 maxSubdivisions = 0L;
	double maxNodeSpacing = 0.0;
	double angTol = 0.0;
	double distTol = 0.0;
	double maxAspectRatio = 0.0;
	AcBr::Element2dShape elementShape = AcBr::kDefault;

	acedGetInt(ACRX_T("\nEnter maximum number of subdivisions (i.e., max internal grid lines): "),
		(int*)&maxSubdivisions);
	acedGetReal(ACRX_T("\nEnter maximum spacing between nodes: "),
		&maxNodeSpacing);
	acedGetReal(ACRX_T("\nEnter angle tolerance (in radians) between normals at adjacent nodes on an element: "),
		&angTol);
	acedGetReal(ACRX_T("\nEnter maximum distance between element and original face: "),
		&distTol);
	acedGetReal(ACRX_T("\nEnter maximum element aspect ratio: "),
		&maxAspectRatio);
	
	ACHAR opt[128];
	while (Adesk::kTrue) {
		acutPrintf(ACRX_T("\nEnter element shape criteria: "));
		acedInitGet(NULL, ACRX_T("Default Polygons Quadrilaterals Triangles"));
		acedGetKword(ACRX_T("<Default>/Polygons/Quadrilaterals/Triangles: "), opt);

        // Map the user input to a valid element shape
		if ((_tcscmp(opt, ACRX_T("Default")) == 0) || (_tcscmp(opt, ACRX_T("")) == 0)) {
			elementShape = AcBr::kDefault;
			break;
        } else if (_tcscmp(opt, ACRX_T("Polygons")) == 0) {
			elementShape = AcBr::kAllPolygons;
			break;
        } else if (_tcscmp(opt, ACRX_T("Quadrilaterals")) == 0) {
			elementShape = AcBr::kAllQuadrilaterals;
			break;
        } else if (_tcscmp(opt, ACRX_T("Triangles")) == 0) {
			elementShape = AcBr::kAllTriangles;
			break;
		}
    }

	AcBrMesh2dControl meshCtrl;
	if ((returnValue = meshCtrl.setMaxSubdivisions(maxSubdivisions)) != eOk)
		return returnValue;
	if ((returnValue = meshCtrl.setMaxNodeSpacing(maxNodeSpacing)) != eOk)
		return returnValue;
	if ((returnValue = meshCtrl.setAngTol(angTol)) != eOk) return returnValue;
	if ((returnValue = meshCtrl.setDistTol(distTol)) != eOk) return returnValue;
	if ((returnValue = meshCtrl.setMaxAspectRatio(maxAspectRatio)) != eOk)
		return returnValue;
	if ((returnValue = meshCtrl.setElementShape(elementShape)) != eOk)
		return returnValue;

	// make the mesh filter from the topology entity and the mesh controls
	const AcBrEntity* meshEnt = (AcBrEntity*)&brepEntity;//VC8:Used const pointer to resolve convserion error
	AcBrMesh2dFilter meshFilter;
	meshFilter.insert(make_pair(meshEnt, (const AcBrMesh2dControl)meshCtrl));

    // generate the mesh, display any errors and attempt to dump all
	// generated elements (most errors are not fatal so we want to do
	// the best we can with whatever subset of the brep was meshed).
	AcBrMesh2d brepMesh;
	if ((returnValue = brepMesh.generate(meshFilter)) != eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrMesh2d::generate:"));
		errorReport(returnValue);
	}

    // check to see if the mesh owner is the brep we used in the filter
    AcBrEntity* meshOwner = NULL;
    if ((returnValue = brepMesh.getEntityAssociated(meshOwner)) != eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrMesh2d::getEntityAssociate:"));
		errorReport(returnValue);
	}
    if (!meshEnt->isEqualTo(meshOwner)) {
        acutPrintf(ACRX_T("\nMesh owner is not the brep we asked to mesh!"));
	}

    // dump or display the elements (regardless of incomplete mesh)
	returnValue = (displayElements) ? meshDisplay(brepMesh) : meshDump(brepMesh);

	return returnValue;
}
