//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Face and surface mesh utilities.

#include "brsample_pch.h"  //precompiled header




// Abbreviations
#include "acdbabb.h"




// Math constants (used for specifying surface-typed mesh controls)
const double kPi      = 3.14159265358979323846;
const double kTwoPi   = 6.28318530717958647692;
const double kHalfPi  = 1.57079632679489661923;
const double kRad2Deg = 57.295779513082323;
const double kDeg2Rad = 0.0174563292519943295;


AcBr::ErrorStatus
faceMesh(const AcBrFace& faceEntity, Adesk::Boolean displayElements)
{ 
    AcBr::ErrorStatus returnValue = AcBr::eOk;

	// Verify that AcBr was explicitly and not implicitly loaded,
	// by testing ObjectARX functions (which are unavailable unless
	// explicitly loaded)
    if (faceEntity.isA() == NULL) {
        acutPrintf(ACRX_T("\n faceMesh: AcBrEntity::isA() failed\n"));
        return returnValue;
    }
    if (!faceEntity.isKindOf(AcBrFace::desc())) {
        acutPrintf(ACRX_T("\n faceMesh: AcBrEntity::isKindOf() failed\n"));
        return returnValue;
    }
	AcBrEntity* entClass = (AcBrEntity*)&faceEntity;
	AcBrEdge* pEdge = AcBrEdge::cast(entClass);  
	if (pEdge != NULL) {
		acutPrintf(ACRX_T("\n faceMesh: AcBrEntity::cast() failed\n"));
        return (AcBr::ErrorStatus)eNotThatKindOfClass;
	} 

	AcGe::EntityId entId;
	returnValue = faceEntity.getSurfaceType(entId);  
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrFace::getSurfaceType:"));
		errorReport(returnValue);
        return returnValue;
	}

	AcGeSurface* surfaceGeometry = NULL;
    AcGeSurface* nativeGeometry = NULL;

	// NOTE: ignore unsupported geometry types for now, since we already know 
	// that elliptic cylinders and elliptic cones are rejected by AcGe, but we
	// can still perform useful evaluations on the external bounded surface.
	returnValue = getNativeSurface(faceEntity, surfaceGeometry, nativeGeometry);  
	if ((returnValue != AcBr::eOk) && (returnValue
		!= (AcBr::ErrorStatus)Acad::eInvalidInput)) {
		acutPrintf(ACRX_T("\n Error in getNativeSurface:"));
		errorReport(returnValue);
        delete surfaceGeometry;
        delete nativeGeometry;
        return returnValue;
	}

	// conditionally set the mesh controls based on surface type
	AcBrMesh2dControl meshCtrl;
	switch (entId) {
	case(kPlane):
		acutPrintf(ACRX_T("\nSurface Type: Plane\n"));
    	if ((returnValue = meshCtrl.setMaxSubdivisions()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setMaxNodeSpacing(2.0)) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setAngTol(90.0 * kDeg2Rad)) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setDistTol(0.5)) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setMaxAspectRatio(8.0)) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setElementShape(AcBr::kAllPolygons)) != eOk)
			return returnValue;
		break;
	case(kSphere):
		acutPrintf(ACRX_T("\nSurface Type: Sphere\n"));
    	if ((returnValue = meshCtrl.setMaxSubdivisions()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setMaxNodeSpacing()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setAngTol()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setDistTol(0.5)) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setMaxAspectRatio(2.0)) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setElementShape(AcBr::kAllQuadrilaterals)) != eOk)
			return returnValue;
		break;
	case(kTorus):
		acutPrintf(ACRX_T("\nSurface Type: Torus\n"));
    	if ((returnValue = meshCtrl.setMaxSubdivisions()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setMaxNodeSpacing()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setAngTol()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setDistTol(0.5)) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setMaxAspectRatio(4.0)) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setElementShape(AcBr::kAllQuadrilaterals)) != eOk)
			return returnValue;
		break;
	case(kCylinder):
		acutPrintf(ACRX_T("\nSurface Type: Circular Cylinder\n"));
    	if ((returnValue = meshCtrl.setMaxSubdivisions()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setMaxNodeSpacing()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setAngTol()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setDistTol(0.5)) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setMaxAspectRatio(2.0)) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setElementShape(AcBr::kAllQuadrilaterals)) != eOk)
			return returnValue;
		break;
	case(kCone):
		acutPrintf(ACRX_T("\nSurface Type: Circular Cone\n"));
    	if ((returnValue = meshCtrl.setMaxSubdivisions()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setMaxNodeSpacing()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setAngTol()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setDistTol(0.5)) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setMaxAspectRatio(2.0)) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setElementShape(AcBr::kAllQuadrilaterals)) != eOk)
			return returnValue;
		break;
	case(kNurbSurface):
		acutPrintf(ACRX_T("\nSurface Type: NURB Surface\n"));
    	if ((returnValue = meshCtrl.setMaxSubdivisions()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setMaxNodeSpacing()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setAngTol(30.0 * kDeg2Rad)) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setDistTol(0.5)) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setMaxAspectRatio(2.0)) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setElementShape(AcBr::kAllQuadrilaterals)) != eOk)
			return returnValue;
		break;
	// NOTE: This surface is not yet supported in AcGe, so we infer the definition
	// data by analysing evaluated data on the external bounded surface.
	case(kEllipCylinder):
		acutPrintf(ACRX_T("\nSurface Type: Elliptic Cylinder\n"));
    	if ((returnValue = meshCtrl.setMaxSubdivisions()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setMaxNodeSpacing()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setAngTol()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setDistTol(0.5)) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setMaxAspectRatio(4.0)) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setElementShape(AcBr::kAllQuadrilaterals)) != eOk)
			return returnValue;
		break;
	// NOTE: This surface is not yet supported in AcGe, so we infer the definition
	// data by analysing evaluated data on the external bounded surface.
	case(kEllipCone):
		acutPrintf(ACRX_T("\nSurface Type: Elliptic Cone\n"));
    	if ((returnValue = meshCtrl.setMaxSubdivisions()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setMaxNodeSpacing()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setAngTol()) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setDistTol(0.5)) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setMaxAspectRatio(4.0)) != eOk) return returnValue;
    	if ((returnValue = meshCtrl.setElementShape(AcBr::kAllQuadrilaterals)) != eOk)
			return returnValue;
		break;
	default:
		acutPrintf(ACRX_T("\nSurface Type: Unexpected Non Surface\n"));
		return (AcBr::ErrorStatus)Acad::eInvalidInput;
	} // end switch(entId)	
    delete nativeGeometry;

	// make the mesh filter from the topology entity and the mesh controls
	const AcBrEntity* meshEnt = (AcBrEntity*)&faceEntity;//VC8:Used const pointer to resolve convserion error
	AcBrMesh2dFilter meshFilter;
	meshFilter.insert(make_pair(meshEnt, (const AcBrMesh2dControl)meshCtrl));

    // generate the mesh, display any errors and attempt to dump all
	// generated elements (most errors are not fatal so we want to do
	// the best we can with whatever subset of the face was meshed).
	AcBrMesh2d faceMesh;
	if ((returnValue = faceMesh.generate(meshFilter)) != eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrMesh2d::generate:"));
		errorReport(returnValue);
	}

    // check to see if the mesh owner is the face we used in the filter
    AcBrEntity* meshOwner = NULL;
    if ((returnValue = faceMesh.getEntityAssociated(meshOwner)) != eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrMesh2d::getEntityAssociate:"));
		errorReport(returnValue);
	}
    if (!meshEnt->isEqualTo(meshOwner)) {
        acutPrintf(ACRX_T("\nMesh owner is not the face we asked to mesh!"));
	}

    // dump or display the elements (regardless of incomplete mesh)
	returnValue = (displayElements) ? meshDisplay(faceMesh) : meshDump(faceMesh);

    return returnValue;
}
