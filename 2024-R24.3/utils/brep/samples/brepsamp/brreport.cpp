//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Source file for the report utilities.

#include "brsample_pch.h"  //precompiled header


// include here



void
errorReport(AcBr::ErrorStatus errorCode)
{
    switch (errorCode) {
	case(AcBr::eBrepChanged):
		acutPrintf(ACRX_T(" Brep Changed\n"));
		break;        
    case(AcBr::eUnsuitableTopology):
		acutPrintf(ACRX_T(" Unsuitable Topology\n"));
		break;        
    case(AcBr::eDegenerateTopology):
		acutPrintf(ACRX_T(" Degenerate Topology\n"));
		break;        
    case(AcBr::eUninitialisedObject):
		acutPrintf(ACRX_T(" Uninitialised Object\n"));
		break;        
	default: 
		acutPrintf(ACRX_T(" AutoCAD Error Code: %d\n"), errorCode);
		acadErrorStatusText((Acad::ErrorStatus)errorCode);
		break;    
	}

	return;
}


void
entityAssociatedReport(AcBrEntity* entityAssociated)
{
	if (entityAssociated != NULL) {
		if (entityAssociated->isKindOf(AcBrBrep::desc())) {
		    acutPrintf(ACRX_T("\n Mesh subobject is inside the brep\n"));
		} else if (entityAssociated->isKindOf(AcBrFace::desc())) {
			acutPrintf(ACRX_T("\n Mesh subobject is on a face\n"));
		} else if (entityAssociated->isKindOf(AcBrEdge::desc())) {
			acutPrintf(ACRX_T("\n Mesh subobject is on an edge\n"));
		} else if (entityAssociated->isKindOf(AcBrVertex::desc())) {
			acutPrintf(ACRX_T("\n Mesh subobject is on a vertex\n"));
        } else acutPrintf(ACRX_T("\n Unsupported entity type encountered\n"));
	}
}


void
ptContainmentReport(AcGe::PointContainment containment,
				    AcBrEntity*			   container)
{
    switch (containment) {
	case(AcGe::kOutside):
		acutPrintf(ACRX_T("\n Point is outside entity boundary\n"));
		break;
	case(AcGe::kInside):
		acutPrintf(ACRX_T("\n Point is inside entity boundary\n"));
		break;     
	case(AcGe::kOnBoundary):
		if (container != NULL) {
			if (container->isKindOf(AcBrFace::desc())) {
				acutPrintf(ACRX_T("\n Point is on a face boundary of entity\n"));
			} else if (container->isKindOf(AcBrEdge::desc())) {
				acutPrintf(ACRX_T("\n Point is on an edge boundary of entity\n"));
			} else if (container->isKindOf(AcBrVertex::desc())) {
				acutPrintf(ACRX_T("\n Point is on a vertex boundary of entity\n"));
			} else acutPrintf(ACRX_T("\n Indeterminate point containment\n"));
		}
		break;        
	default: 
		acutPrintf(ACRX_T("\n Indeterminate point containment\n"));
		break;    
	}

	return;
}


void
lnContainmentReport(Adesk::UInt32& hitIndex,
					AcGePoint3d&   hitPoint,
					AcBrEntity*    entityHit,
					AcBrEntity*    entityEntered)
{
	acutPrintf(ACRX_T("\n Hit point %d is ("), hitIndex+1);
	acutPrintf (ACRX_T("%lf , "), hitPoint.x);	
	acutPrintf (ACRX_T("%lf , "), hitPoint.y);
	acutPrintf (ACRX_T("%lf "), hitPoint.z);
	acutPrintf(ACRX_T(")\n"));

    if (entityHit != NULL) {
		if (entityHit->isKindOf(AcBrBrep::desc())) {
			acutPrintf(ACRX_T("\n Hit is inside solid\n"));
		} else if (entityHit->isKindOf(AcBrFace::desc())) {
			acutPrintf(ACRX_T("\n Hit is on a face\n"));
		} else if (entityHit->isKindOf(AcBrEdge::desc())) {
			acutPrintf(ACRX_T("\n Hit is on an edge\n"));
		} else if (entityHit->isKindOf(AcBrVertex::desc())) {
			acutPrintf(ACRX_T("\n Hit is on a vertex\n"));
		} else acutPrintf(ACRX_T("\n Indeterminate hit containment\n"));
	}

    if (entityEntered != NULL) {
		if (entityEntered->isKindOf(AcBrBrep::desc())) {
			acutPrintf(ACRX_T("\n Segment is inside solid\n"));
		} else if (entityEntered->isKindOf(AcBrFace::desc())) {
			acutPrintf(ACRX_T("\n Segment is on a face\n"));
		} else if (entityEntered->isKindOf(AcBrEdge::desc())) {
			acutPrintf(ACRX_T("\n Segment is on an edge\n"));
		} else acutPrintf(ACRX_T("\n Indeterminate segment containment\n"));
	}

	return;
}


void
propsReport(AcBrMassProps& massProps,
			double         area,
			double         length)
{
    acutPrintf(ACRX_T("\n Mass Properties Data Begin:\n"));
    acutPrintf(ACRX_T("\n Volume is %lf"), massProps.mVolume);
    acutPrintf(ACRX_T("\n Surface area is %lf"), area);
    acutPrintf(ACRX_T("\n Perimeter length is %lf"), length);
    acutPrintf(ACRX_T("\n Mass is %lf"), massProps.mMass);
    acutPrintf(ACRX_T("\n Centroid is ("));
	acutPrintf (ACRX_T("%lf, "), massProps.mCentroid.x);	
	acutPrintf (ACRX_T("%lf, "), massProps.mCentroid.y);
	acutPrintf (ACRX_T("%lf"), massProps.mCentroid.z);
	acutPrintf(ACRX_T(")\n"));	
    acutPrintf(ACRX_T("\n Radii of Gyration are kx:%lf, ky:%lf, kz:%lf"),
		massProps.mRadiiGyration[0],
		massProps.mRadiiGyration[1],
		massProps.mRadiiGyration[2]);
    acutPrintf(ACRX_T("\n Moments of Inertia are Ix:%lf, Iy:%lf, Iz:%lf"),
		massProps.mMomInertia[0],
		massProps.mMomInertia[1],
		massProps.mMomInertia[2]);
    acutPrintf(ACRX_T("\n Products of Inertia are Ixy:%lf, Ixy:%lf, Iyz:%lf"),
		massProps.mProdInertia[0],
		massProps.mProdInertia[1],
		massProps.mProdInertia[2]);
    acutPrintf(ACRX_T("\n Prinicpal Moments are I1:%lf, I2:%lf, I3:%lf"),
		massProps.mPrinMoments[0],
		massProps.mPrinMoments[1],
		massProps.mPrinMoments[2]);
    acutPrintf(ACRX_T("\n Prinicpal Axes are:"));
	acutPrintf(ACRX_T("\n X: ("));
	acutPrintf (ACRX_T("%lf, "), massProps.mPrinAxes[0].x);	
	acutPrintf (ACRX_T("%lf, "), massProps.mPrinAxes[0].y);
	acutPrintf (ACRX_T("%lf"), massProps.mPrinAxes[0].z);
	acutPrintf(ACRX_T(")\n"));	
	acutPrintf(ACRX_T("\n Y: ("));
	acutPrintf (ACRX_T("%lf, "), massProps.mPrinAxes[1].x);	
	acutPrintf (ACRX_T("%lf, "), massProps.mPrinAxes[1].y);
	acutPrintf (ACRX_T("%lf"), massProps.mPrinAxes[1].z);
	acutPrintf(ACRX_T(")\n"));	
	acutPrintf(ACRX_T("\n Z: ("));
	acutPrintf (ACRX_T("%lf, "), massProps.mPrinAxes[2].x);	
	acutPrintf (ACRX_T("%lf, "), massProps.mPrinAxes[2].y);
	acutPrintf (ACRX_T("%lf"), massProps.mPrinAxes[2].z);
	acutPrintf(ACRX_T(")\n"));	
    acutPrintf(ACRX_T("\n Mass Properties Data End:\n"));
}


void
bblockReport(AcGePoint3d& min, AcGePoint3d& max)
{
    acutPrintf(ACRX_T("\n Bounding Block lower corner is ("));
	acutPrintf (ACRX_T("%lf, "), min.x);	
	acutPrintf (ACRX_T("%lf, "), min.y);
	acutPrintf (ACRX_T("%lf"), min.z);
	acutPrintf(ACRX_T(")\n"));	
    acutPrintf(ACRX_T("\n Bounding Block upper corner is ("));
	acutPrintf (ACRX_T("%lf, "), max.x);	
	acutPrintf (ACRX_T("%lf, "), max.y);
	acutPrintf (ACRX_T("%lf"), max.z);
	acutPrintf(ACRX_T(")\n"));	

	return;
}


void
shellTypeReport(AcBr::ShellType shellType)
{
    switch (shellType) {
	case(AcBr::kShellUnclassified):
		acutPrintf(ACRX_T(" Shell type cannot be determined at this time\n"));
		break;        
    case(AcBr::kShellExterior):
		acutPrintf(ACRX_T(" This is the exterior shell\n"));
		break;
    case(AcBr::kShellInterior):
		acutPrintf(ACRX_T(" This is an interior shell\n"));
		break;
	default:
		acutPrintf(ACRX_T(" Unexpected shell type encountered\n"));
		break;
	}

	return;
}


void
loopTypeReport(AcBr::LoopType loopType)
{
    switch (loopType) {
	case(AcBr::kLoopUnclassified):
		acutPrintf(ACRX_T(" Loop type cannot be determined at this time, or is ambiguous\n"));
		break;        
    case(AcBr::kLoopExterior):
		acutPrintf(ACRX_T(" This is the exterior loop\n"));
		break;
    case(AcBr::kLoopInterior):
		acutPrintf(ACRX_T(" This is an interior loop\n"));
		break;
    case(AcBr::kLoopWinding):
		acutPrintf(ACRX_T(" This is a winding loop on an analytic surface\n"));
		break;
	default:
		acutPrintf(ACRX_T(" Unexpected loop type encountered\n"));
		break;
	}

	return;
}
