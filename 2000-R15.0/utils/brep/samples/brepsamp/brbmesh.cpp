// (C) Copyright 1997-1999 by Autodesk, Inc. 
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
// Brep mesh utilities.

#include <string.h>

#include "acutads.h"	// acutPrintf
#include "acedads.h"	// acedGetKword, acedGetInt, ...

// AcBr support 
//#include "brmesh2d.h"
//#include "brelem2d.h"
//#include "brnode.h"
//#include "brm2dctl.h"
//#include "brmetrav.h"
//#include "brentrav.h"

// AcBr sample app support
#include "brreport.h"
#include "brgeutl.h"
#include "brbmesh.h"
#include "brmdump.h"

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
		acutPrintf("\n Error in AcBrBrep::getBrep:");
		errorReport(returnValue);
		return returnValue;
	}
	if (!brepEntity.isEqualTo(&brepOwner)) {
		acutPrintf("\n Brep owner is out of sync with brep!");
		return (AcBr::ErrorStatus)Acad::eAmbiguousOutput;
	}

	// Ask for the mesh controls
	Adesk::UInt32 minSubdivisionsInU = 0L;
	Adesk::UInt32 minSubdivisionsInV = 0L;
	Adesk::UInt32 maxSubdivisions = 0L;
	double maxNodeSpacing = 0.0;
	double angTol = 0.0;
	double distTol = 0.0;
	double maxAspectRatio = 0.0;
	AcBr::Element2dShape elementShape = AcBr::kDefault;

	acedGetInt("\nEnter minimum number of subdivisions in u: ",
		(int*)&minSubdivisionsInU);
	acedGetInt("\nEnter minimum number of subdivisions in v: ",
		(int*)&minSubdivisionsInV);
	acedGetInt("\nEnter maximum number of subdivisions (i.e., max internal grid lines): ",
		(int*)&maxSubdivisions);
	acedGetReal("\nEnter maximum spacing between nodes: ",
		&maxNodeSpacing);
	acedGetReal("\nEnter angle tolerance (in radians) between normals at adjacent nodes on an element: ",
		&angTol);
	acedGetReal("\nEnter maximum distance between element and original face: ",
		&distTol);
	acedGetReal("\nEnter maximum element aspect ratio: ",
		&maxAspectRatio);
	
	char opt[128];
	while (Adesk::kTrue) {
		acutPrintf("\nEnter element shape criteria: ");
		acedInitGet(NULL, "Default Polygons Quadrilaterals Triangles");
		acedGetKword("<Default>/Polygons/Quadrilaterals/Triangles: ", opt);

        // Map the user input to a valid element shape
		if ((strcmp(opt, "Default") == 0) || (strcmp(opt, "") == 0)) {
			elementShape = AcBr::kDefault;
			break;
        } else if (strcmp(opt, "Polygons") == 0) {
			elementShape = AcBr::kAllPolygons;
			break;
        } else if (strcmp(opt, "Quadrilaterals") == 0) {
			elementShape = AcBr::kAllQuadrilaterals;
			break;
        } else if (strcmp(opt, "Triangles") == 0) {
			elementShape = AcBr::kAllTriangles;
			break;
		}
    }

	AcBrMesh2dControl meshCtrl;
	if ((returnValue = meshCtrl.setMinSubdivisionsInU(minSubdivisionsInU)) != eOk)
		return returnValue;
	if ((returnValue = meshCtrl.setMinSubdivisionsInV(minSubdivisionsInV)) != eOk)
		return returnValue;
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
	AcBrEntity* meshEnt = (AcBrEntity*)&brepEntity;
	AcBrMesh2dFilter meshFilter;
	meshFilter.insert(make_pair(meshEnt, (const AcBrMesh2dControl)meshCtrl));

    // generate the mesh, display any errors and attempt to dump all
	// generated elements (most errors are not fatal so we want to do
	// the best we can with whatever subset of the brep was meshed).
	AcBrMesh2d brepMesh;
	if ((returnValue = brepMesh.generate(meshFilter)) != eOk) {
		acutPrintf("\n Error in AcBrMesh2d::generate:");
		errorReport(returnValue);
	}

    // check to see if the mesh owner is the brep we used in the filter
    AcBrEntity* meshOwner = NULL;
    if ((returnValue = brepMesh.getEntityAssociated(meshOwner)) != eOk) {
		acutPrintf("\n Error in AcBrMesh2d::getEntityAssociate:");
		errorReport(returnValue);
	}
    if (!meshEnt->isEqualTo(meshOwner)) {
        acutPrintf("\nMesh owner is not the brep we asked to mesh!");
	}

    // dump or display the elements (regardless of incomplete mesh)
	returnValue = (displayElements) ? meshDisplay(brepMesh) : meshDump(brepMesh);

	return returnValue;
}
