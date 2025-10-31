// (C) Copyright 1996-1999 by Autodesk, Inc. 
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
// Source file for the report utilities.

#include "brsample_pch.h"  //precompiled header

void
errorReport(AcBr::ErrorStatus errorCode)
{
    switch (errorCode) {
	case(AcBr::eBrepChanged):
		acutPrintf(" Brep Changed\n");
		break;        
    case(AcBr::eUnsuitableTopology):
		acutPrintf(" Unsuitable Topology\n");
		break;        
    case(AcBr::eDegenerateTopology):
		acutPrintf(" Degenerate Topology\n");
		break;        
    case(AcBr::eUninitialisedObject):
		acutPrintf(" Uninitialised Object\n");
		break;        
	default: 
		acutPrintf(" AutoCAD Error Code: %d\n", errorCode);
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
		    acutPrintf("\n Mesh subobject is inside the brep\n");
		} else if (entityAssociated->isKindOf(AcBrFace::desc())) {
			acutPrintf("\n Mesh subobject is on a face\n");
		} else if (entityAssociated->isKindOf(AcBrEdge::desc())) {
			acutPrintf("\n Mesh subobject is on an edge\n");
		} else if (entityAssociated->isKindOf(AcBrVertex::desc())) {
			acutPrintf("\n Mesh subobject is on a vertex\n");
        } else acutPrintf("\n Unsupported entity type encountered\n");
	}
}


void
ptContainmentReport(AcGe::PointContainment containment,
				    AcBrEntity*			   container)
{
    switch (containment) {
	case(AcGe::kOutside):
		acutPrintf("\n Point is outside entity boundary\n");
		break;
	case(AcGe::kInside):
		acutPrintf("\n Point is inside entity boundary\n");
		break;     
	case(AcGe::kOnBoundary):
		if (container != NULL) {
			if (container->isKindOf(AcBrFace::desc())) {
				acutPrintf("\n Point is on a face boundary of entity\n");
			} else if (container->isKindOf(AcBrEdge::desc())) {
				acutPrintf("\n Point is on an edge boundary of entity\n");
			} else if (container->isKindOf(AcBrVertex::desc())) {
				acutPrintf("\n Point is on a vertex boundary of entity\n");
			} else acutPrintf("\n Indeterminate point containment\n");
		}
		break;        
	default: 
		acutPrintf("\n Indeterminate point containment\n");
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
	acutPrintf("\n Hit point %d is (", hitIndex+1);
	acutPrintf ("%lf , ", hitPoint.x);	
	acutPrintf ("%lf , ", hitPoint.y);
	acutPrintf ("%lf ", hitPoint.z);
	acutPrintf(")\n");

    if (entityHit != NULL) {
		if (entityHit->isKindOf(AcBrBrep::desc())) {
			acutPrintf("\n Hit is inside solid\n");
		} else if (entityHit->isKindOf(AcBrFace::desc())) {
			acutPrintf("\n Hit is on a face\n");
		} else if (entityHit->isKindOf(AcBrEdge::desc())) {
			acutPrintf("\n Hit is on an edge\n");
		} else if (entityHit->isKindOf(AcBrVertex::desc())) {
			acutPrintf("\n Hit is on a vertex\n");
		} else acutPrintf("\n Indeterminate hit containment\n");
	}

    if (entityEntered != NULL) {
		if (entityEntered->isKindOf(AcBrBrep::desc())) {
			acutPrintf("\n Segment is inside solid\n");
		} else if (entityEntered->isKindOf(AcBrFace::desc())) {
			acutPrintf("\n Segment is on a face\n");
		} else if (entityEntered->isKindOf(AcBrEdge::desc())) {
			acutPrintf("\n Segment is on an edge\n");
		} else acutPrintf("\n Indeterminate segment containment\n");
	}

	return;
}


void
propsReport(AcBrMassProps& massProps,
			double         area,
			double         length)
{
    acutPrintf("\n Mass Properties Data Begin:\n");
    acutPrintf("\n Volume is %lf", massProps.mVolume);
    acutPrintf("\n Surface area is %lf", area);
    acutPrintf("\n Perimeter length is %lf", length);
    acutPrintf("\n Mass is %lf", massProps.mMass);
    acutPrintf("\n Centroid is (");
	acutPrintf ("%lf, ", massProps.mCentroid.x);	
	acutPrintf ("%lf, ", massProps.mCentroid.y);
	acutPrintf ("%lf", massProps.mCentroid.z);
	acutPrintf(")\n");	
    acutPrintf("\n Radii of Gyration are kx:%lf, ky:%lf, kz:%lf",
		massProps.mRadiiGyration[0],
		massProps.mRadiiGyration[1],
		massProps.mRadiiGyration[2]);
    acutPrintf("\n Moments of Inertia are Ix:%lf, Iy:%lf, Iz:%lf",
		massProps.mMomInertia[0],
		massProps.mMomInertia[1],
		massProps.mMomInertia[2]);
    acutPrintf("\n Products of Inertia are Ixy:%lf, Ixy:%lf, Iyz:%lf",
		massProps.mProdInertia[0],
		massProps.mProdInertia[1],
		massProps.mProdInertia[2]);
    acutPrintf("\n Prinicpal Moments are I1:%lf, I2:%lf, I3:%lf",
		massProps.mPrinMoments[0],
		massProps.mPrinMoments[1],
		massProps.mPrinMoments[2]);
    acutPrintf("\n Prinicpal Axes are:");
	acutPrintf("\n X: (");
	acutPrintf ("%lf, ", massProps.mPrinAxes[0].x);	
	acutPrintf ("%lf, ", massProps.mPrinAxes[0].y);
	acutPrintf ("%lf", massProps.mPrinAxes[0].z);
	acutPrintf(")\n");	
	acutPrintf("\n Y: (");
	acutPrintf ("%lf, ", massProps.mPrinAxes[1].x);	
	acutPrintf ("%lf, ", massProps.mPrinAxes[1].y);
	acutPrintf ("%lf", massProps.mPrinAxes[1].z);
	acutPrintf(")\n");	
	acutPrintf("\n Z: (");
	acutPrintf ("%lf, ", massProps.mPrinAxes[2].x);	
	acutPrintf ("%lf, ", massProps.mPrinAxes[2].y);
	acutPrintf ("%lf", massProps.mPrinAxes[2].z);
	acutPrintf(")\n");	
    acutPrintf("\n Mass Properties Data End:\n");
}


void
bblockReport(AcGePoint3d& min, AcGePoint3d& max)
{
    acutPrintf("\n Bounding Block lower corner is (");
	acutPrintf ("%lf, ", min.x);	
	acutPrintf ("%lf, ", min.y);
	acutPrintf ("%lf", min.z);
	acutPrintf(")\n");	
    acutPrintf("\n Bounding Block upper corner is (");
	acutPrintf ("%lf, ", max.x);	
	acutPrintf ("%lf, ", max.y);
	acutPrintf ("%lf", max.z);
	acutPrintf(")\n");	

	return;
}


void
shellTypeReport(AcBr::ShellType shellType)
{
    switch (shellType) {
	case(AcBr::kShellUnclassified):
		acutPrintf(" Shell type cannot be determined at this time\n");
		break;        
    case(AcBr::kShellExterior):
		acutPrintf(" This is the exterior shell\n");
		break;
    case(AcBr::kShellInterior):
		acutPrintf(" This is an interior shell\n");
		break;
	default:
		acutPrintf(" Unexpected shell type encountered\n");
		break;
	}

	return;
}


void
loopTypeReport(AcBr::LoopType loopType)
{
    switch (loopType) {
	case(AcBr::kLoopUnclassified):
		acutPrintf(" Loop type cannot be determined at this time, or is ambiguous\n");
		break;        
    case(AcBr::kLoopExterior):
		acutPrintf(" This is the exterior loop\n");
		break;
    case(AcBr::kLoopInterior):
		acutPrintf(" This is an interior loop\n");
		break;
    case(AcBr::kLoopWinding):
		acutPrintf(" This is a winding loop on an analytic surface\n");
		break;
	default:
		acutPrintf(" Unexpected loop type encountered\n");
		break;
	}

	return;
}
