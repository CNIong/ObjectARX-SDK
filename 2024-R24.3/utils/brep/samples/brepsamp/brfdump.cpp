//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Face and surface dump utilities.


// C-RTL
#include "brsample_pch.h"  //precompiled header



// Abbreviations
#include "brgblabb.h"




// Math constants (used for evaluating external bounded surfaces)
const double kPi      = 3.14159265358979323846;
const double kTwoPi   = 6.28318530717958647692;
const double kHalfPi  = 1.57079632679489661923;


AcBr::ErrorStatus
faceDump(const AcBrFace& faceEntity)
{ 
    AcBr::ErrorStatus returnValue = AcBr::eOk;

	// Verify that AcBr was explicitly and not implicitly loaded,
	// by testing ObjectARX functions (which are unavailable unless
	// explicitly loaded)
    if (faceEntity.isA() == NULL) {
        acutPrintf(ACRX_T("\n faceDump: AcBrEntity::isA() failed\n"));
        return returnValue;
    }
    if (!faceEntity.isKindOf(AcBrFace::desc())) {
        acutPrintf(ACRX_T("\n faceDump: AcBrEntity::isKindOf() failed\n"));
        return returnValue;
    }
	AcBrEntity* entClass = (AcBrEntity*)&faceEntity;
	AcBrEdge* pEdge = AcBrEdge::cast(entClass);  
	if (pEdge != NULL) {
		acutPrintf(ACRX_T("\n faceDump: AcBrEntity::cast() failed\n"));
        return (AcBrErrorStatus)Acad::eNotThatKindOfClass;
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
		!= (AcBrErrorStatus)Acad::eInvalidInput)) {
		acutPrintf(ACRX_T("\n Error in getNativeSurface:"));
		errorReport(returnValue);
        delete surfaceGeometry;
        delete nativeGeometry;
        return returnValue;
	}

	switch (entId) {
	case(kPlane):
	{ 
		acutPrintf(ACRX_T("\nSurface Type: Plane\n"));
        AcGePlane* planeGeometry = (AcGePlane*)nativeGeometry;
        AcGePoint3d pt = planeGeometry->pointOnPlane();
        AcGeVector3d normal = planeGeometry->normal();
		acutPrintf(ACRX_T("\nSurface Definition Data Begin:\n"));
		acutPrintf(ACRX_T(" Point on Plane is ("));
		acutPrintf (ACRX_T("%lf , "), pt.x);	
		acutPrintf (ACRX_T("%lf , "), pt.y);
		acutPrintf (ACRX_T("%lf "), pt.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Plane normal direction is ("));
		acutPrintf (ACRX_T("%lf , "), normal.x);	
		acutPrintf (ACRX_T("%lf , "), normal.y);
		acutPrintf (ACRX_T("%lf "), normal.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T("Surface Definition Data End\n"));
		break;
    } 
	
	case(kSphere):
    {
		acutPrintf(ACRX_T("\nSurface Type: Sphere\n"));
        AcGeSphere* sphereGeometry = (AcGeSphere*)nativeGeometry;
        AcGePoint3d centre = sphereGeometry->center();
		double ang1, ang2, ang3, ang4;
        sphereGeometry->getAnglesInU(ang1, ang2);
        sphereGeometry->getAnglesInV(ang3, ang4);
        AcGePoint3d north = sphereGeometry->northPole();
        AcGePoint3d south = sphereGeometry->southPole();
		acutPrintf(ACRX_T("\nSurface Definition Data Begin:\n"));
		acutPrintf(ACRX_T(" Sphere centre is ("));
		acutPrintf (ACRX_T("%lf , "), centre.x);	
		acutPrintf (ACRX_T("%lf , "), centre.y);
		acutPrintf (ACRX_T("%lf "), centre.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Sphere radius is %lf\n"), sphereGeometry->radius());
		acutPrintf(ACRX_T(" Sphere start angle in U is %lf\n"), ang1);
		acutPrintf(ACRX_T(" Sphere end angle in U is %lf\n"), ang2);
		acutPrintf(ACRX_T(" Sphere start angle in V is %lf\n"), ang3);
		acutPrintf(ACRX_T(" Sphere end angle in V is %lf\n"), ang4);
		acutPrintf(ACRX_T(" Sphere north pole is ("));
		acutPrintf (ACRX_T("%lf , "), north.x);	
		acutPrintf (ACRX_T("%lf , "), north.y);
		acutPrintf (ACRX_T("%lf "), north.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Sphere south pole is ("));
		acutPrintf (ACRX_T("%lf , "), south.x);	
		acutPrintf (ACRX_T("%lf , "), south.y);
		acutPrintf (ACRX_T("%lf "), south.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T("Surface Definition Data End\n"));
		break;
    }
	
	case(kTorus):
    {
		acutPrintf(ACRX_T("\nSurface Type: Torus\n"));
        AcGeTorus* torusGeometry = (AcGeTorus*)nativeGeometry;
        AcGePoint3d centre = torusGeometry->center();
		double ang1, ang2, ang3, ang4;
        torusGeometry->getAnglesInU(ang1, ang2);
        torusGeometry->getAnglesInV(ang3, ang4);
		acutPrintf(ACRX_T("\nSurface Definition Data Begin:\n"));
		acutPrintf(ACRX_T(" Torus centre is ("));
		acutPrintf (ACRX_T("%lf , "), centre.x);	
		acutPrintf (ACRX_T("%lf , "), centre.y);
		acutPrintf (ACRX_T("%lf "), centre.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Torus major radius is %lf\n"), torusGeometry->majorRadius());
		acutPrintf(ACRX_T(" Torus minor radius is %lf\n"), torusGeometry->minorRadius());
		acutPrintf(ACRX_T(" Torus start angle in U is %lf\n"), ang1);
		acutPrintf(ACRX_T(" Torus end angle in U is %lf\n"), ang2);
		acutPrintf(ACRX_T(" Torus start angle in V is %lf\n"), ang3);
		acutPrintf(ACRX_T(" Torus end angle in V is %lf\n"), ang4);
		acutPrintf(ACRX_T("Surface Definition Data End\n"));
		break;	
	}	
	
	case(kCylinder):
    {
		acutPrintf(ACRX_T("\nSurface Type: Circular Cylinder\n"));
        AcGeCylinder* cylinderGeometry = (AcGeCylinder*)nativeGeometry;
        AcGePoint3d origin = cylinderGeometry->origin();
		double ang1, ang2;
        cylinderGeometry->getAngles(ang1, ang2);
        AcGeInterval ht;
        cylinderGeometry->getHeight(ht);
        double height = ht.upperBound() - ht.lowerBound();
        AcGeVector3d refAxis = cylinderGeometry->refAxis();
        AcGeVector3d symAxis = cylinderGeometry->axisOfSymmetry();
		acutPrintf(ACRX_T("\nSurface Definition Data Begin:\n"));
		acutPrintf(ACRX_T(" Circular Cylinder origin is ("));
		acutPrintf (ACRX_T("%lf , "), origin.x);	
		acutPrintf (ACRX_T("%lf , "), origin.y);
		acutPrintf (ACRX_T("%lf "), origin.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Circular Cylinder radius is %lf\n"), cylinderGeometry->radius());
		acutPrintf(ACRX_T(" Circular Cylinder start angle is %lf\n"), ang1);
		acutPrintf(ACRX_T(" Circular Cylinder end angle is %lf\n"), ang2);
		if (cylinderGeometry->isClosedInU())
			acutPrintf(ACRX_T(" Circular Cylinder height is %lf\n"), height);
        else acutPrintf(ACRX_T(" Circular Cylinder is not closed in U\n"));
		acutPrintf(ACRX_T(" Circular Cylinder reference axis is ("));
		acutPrintf (ACRX_T("%lf , "), refAxis.x);	
		acutPrintf (ACRX_T("%lf , "), refAxis.y);
		acutPrintf (ACRX_T("%lf "), refAxis.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Circular Cylinder axis of symmetry is ("));
		acutPrintf (ACRX_T("%lf , "), symAxis.x);	
		acutPrintf (ACRX_T("%lf , "), symAxis.y);
		acutPrintf (ACRX_T("%lf "), symAxis.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T("Surface Definition Data End\n"));
		break;
    }

	case(kCone):
    {
		acutPrintf(ACRX_T("\nSurface Type: Circular Cone\n"));
        AcGeCone* coneGeometry = (AcGeCone*)nativeGeometry;
        AcGePoint3d centre = coneGeometry->baseCenter();
		double ang1, ang2;
        coneGeometry->getAngles(ang1, ang2);
        AcGeVector3d axis1 = coneGeometry->axisOfSymmetry();
        AcGeVector3d axis2 = coneGeometry->refAxis();
        AcGePoint3d apex = coneGeometry->apex();
		double cosAng, sinAng;
        coneGeometry->getHalfAngle(cosAng, sinAng);
        AcGeInterval ht;
        coneGeometry->getHeight(ht);
        double height = ht.upperBound() - ht.lowerBound();
		acutPrintf(ACRX_T("\nSurface Definition Data Begin:\n"));
		acutPrintf(ACRX_T(" Circular Cone base centre is ("));
		acutPrintf (ACRX_T("%lf , "), centre.x);	
		acutPrintf (ACRX_T("%lf , "), centre.y);
		acutPrintf (ACRX_T("%lf "), centre.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Circular Cone base radius is %lf\n"), coneGeometry->baseRadius());
		acutPrintf(ACRX_T(" Circular Cone start angle is %lf\n"), ang1);
		acutPrintf(ACRX_T(" Circular Cone end angle is %lf\n"), ang2);
		acutPrintf(ACRX_T(" Circular Cone axis of symmetry is ("));
		acutPrintf (ACRX_T("%lf , "), axis1.x);	
		acutPrintf (ACRX_T("%lf , "), axis1.y);
		acutPrintf (ACRX_T("%lf "), axis1.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Circular Cone reference axis is ("));
		acutPrintf (ACRX_T("%lf , "), axis2.x);	
		acutPrintf (ACRX_T("%lf , "), axis2.y);
		acutPrintf (ACRX_T("%lf "), axis2.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Circular Cone apex is ("));
		acutPrintf (ACRX_T("%lf , "), apex.x);	
		acutPrintf (ACRX_T("%lf , "), apex.y);
		acutPrintf (ACRX_T("%lf "), apex.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Circular Cone cosine of major half-angle is %lf\n"), cosAng);
		acutPrintf(ACRX_T(" Circular Cone sine of major half-angle is %lf\n"), sinAng);
		if (coneGeometry->isClosedInU())
			acutPrintf(ACRX_T(" Circular Cone height is %lf\n"), height);
        else acutPrintf(ACRX_T(" Circular Cone is not closed in U\n"));
		acutPrintf(ACRX_T("Surface Definition Data End\n"));
		break;
    }
	
	case(kNurbSurface):
    {
		acutPrintf(ACRX_T("\nSurface Type: NURB Surface\n"));
        AcGeNurbSurface* nurbGeometry = (AcGeNurbSurface*)nativeGeometry;
		int nCtrlPtsU = nurbGeometry->numControlPointsInU();
		int nCtrlPtsV = nurbGeometry->numControlPointsInV();
		int nKnotsU = nurbGeometry->numKnotsInU();
		int nKnotsV = nurbGeometry->numKnotsInV();
		acutPrintf(ACRX_T("\nSurface Definition Data Begin:\n"));
		acutPrintf(ACRX_T(" NURB Surface degree in U is %d\n"), nurbGeometry->degreeInU());
		acutPrintf(ACRX_T(" NURB Surface degree in V is %d\n"), nurbGeometry->degreeInV());
		acutPrintf(ACRX_T(" NURB Surface number of control points in U is %d\n"), nCtrlPtsU);
		acutPrintf(ACRX_T(" NURB Surface number of control points in V is %d\n"), nCtrlPtsV);
		acutPrintf(ACRX_T(" NURB Surface number of knots in U is %d\n"), nKnotsU);
		acutPrintf(ACRX_T(" NURB Surface number of knots in V is %d\n"), nKnotsV);
		acutPrintf(ACRX_T("Surface Definition Data End\n"));
		break;
    }
	
	// NOTE: This surface is not yet supported in AcGe, so we infer the definition
	// data by analysing evaluated data on the external bounded surface.
	case(kEllipCylinder):
	{
		acutPrintf(ACRX_T("\nSurface Type: Elliptic Cylinder\n"));
        AcGePoint3d p0 = surfaceGeometry->evalPoint(AcGePoint2d(0.0, 0.0));
        AcGePoint3d p1 = surfaceGeometry->evalPoint(AcGePoint2d(0.0, kPi));
        AcGePoint3d p2 = surfaceGeometry->evalPoint(AcGePoint2d(0.0, kHalfPi));
        AcGePoint3d origin(((p0.x + p1.x) / 2.0),
			               ((p0.y + p1.y) / 2.0),
						   ((p0.z + p1.z) / 2.0));
        AcGeVector3d majAxis = p0 - origin;
        AcGeVector3d minAxis = p2 - origin;
        AcGeVector3d symAxis = (majAxis.crossProduct(minAxis)).normalize();
		acutPrintf(ACRX_T("\nSurface Definition Data Begin:\n"));
		acutPrintf(ACRX_T(" Elliptic Cylinder origin is ("));
		acutPrintf (ACRX_T("%lf , "), origin.x);	
		acutPrintf (ACRX_T("%lf , "), origin.y);
		acutPrintf (ACRX_T("%lf "), origin.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Elliptic Cylinder major radius is %lf\n"), majAxis.length());
		acutPrintf(ACRX_T(" Elliptic Cylinder minor radius is %lf\n"), minAxis.length());
		acutPrintf(ACRX_T(" Elliptic Cylinder major axis is ("));
		acutPrintf (ACRX_T("%lf , "), majAxis.x);	
		acutPrintf (ACRX_T("%lf , "), majAxis.y);
		acutPrintf (ACRX_T("%lf "), majAxis.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Elliptic Cylinder minor axis is ("));
		acutPrintf (ACRX_T("%lf , "), minAxis.x);	
		acutPrintf (ACRX_T("%lf , "), minAxis.y);
		acutPrintf (ACRX_T("%lf "), minAxis.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Elliptic Cylinder axis of symmetry is ("));
		acutPrintf (ACRX_T("%lf , "), symAxis.x);	
		acutPrintf (ACRX_T("%lf , "), symAxis.y);
		acutPrintf (ACRX_T("%lf "), symAxis.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T("Surface Definition Data End\n"));
		break;
	}

	// NOTE: This surface is not yet supported in AcGe, so we infer the definition
	// data by analysing evaluated data on the external bounded surface.
	case(kEllipCone):
	{
		acutPrintf(ACRX_T("\nSurface Type: Elliptic Cone\n"));
        AcGePoint3d p0 = surfaceGeometry->evalPoint(AcGePoint2d(0.0, 0.0));
        AcGePoint3d p1 = surfaceGeometry->evalPoint(AcGePoint2d(0.0, kPi));
        AcGePoint3d p2 = surfaceGeometry->evalPoint(AcGePoint2d(0.0, kHalfPi));
        AcGePoint3d p3 = surfaceGeometry->evalPoint(AcGePoint2d(1.0, 0.0));
        AcGePoint3d centre(((p0.x + p1.x) / 2.0),
			               ((p0.y + p1.y) / 2.0),
						   ((p0.z + p1.z) / 2.0));
        AcGeVector3d majAxis = p0 - centre;
        AcGeVector3d minAxis = p2 - centre;
        AcGeVector3d symAxis = (majAxis.crossProduct(minAxis)).normalize();
		double halfAng = kHalfPi - majAxis.angleTo(p3 - p0);
		acutPrintf(ACRX_T("\nSurface Definition Data Begin:\n"));
		acutPrintf(ACRX_T(" Elliptic Cone base centre is ("));
		acutPrintf (ACRX_T("%lf , "), centre.x);	
		acutPrintf (ACRX_T("%lf , "), centre.y);
		acutPrintf (ACRX_T("%lf "), centre.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Elliptic Cone base major radius is %lf\n"), majAxis.length());
		acutPrintf(ACRX_T(" Elliptic Cone base minor radius is %lf\n"), minAxis.length());
		acutPrintf(ACRX_T(" Elliptic Cone major axis is ("));
		acutPrintf (ACRX_T("%lf , "), majAxis.x);	
		acutPrintf (ACRX_T("%lf , "), majAxis.y);
		acutPrintf (ACRX_T("%lf "), majAxis.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Elliptic Cone minor axis is ("));
		acutPrintf (ACRX_T("%lf , "), minAxis.x);	
		acutPrintf (ACRX_T("%lf , "), minAxis.y);
		acutPrintf (ACRX_T("%lf "), minAxis.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Elliptic Cone axis of symmetry is ("));
		acutPrintf (ACRX_T("%lf , "), symAxis.x);	
		acutPrintf (ACRX_T("%lf , "), symAxis.y);
		acutPrintf (ACRX_T("%lf "), symAxis.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Elliptic Cone cosine of major half-angle is %lf\n"), cos(halfAng));
		acutPrintf(ACRX_T(" Elliptic Cone sine of major half-angle is %lf\n"), sin(halfAng));
		acutPrintf(ACRX_T("Surface Definition Data End\n"));
		break;
	}

	default:
		acutPrintf(ACRX_T("\nSurface Type: Unexpected Non Surface\n"));
		return (AcBrErrorStatus)Acad::eInvalidInput;
	} // end switch(entId)	
    
	delete nativeGeometry;

	// Evaluate the surface - note that the u,v bounds will not consider any
	// holes in the surface. To compute a u,v zone of exclusion for evaluation,
	// check for additional (i.e., inner) loops and get the bounding boxes for
	// the loops, then convert those to parameter space boxes. There is no
	// particular guarantee that outer loop(s) are the first in the face-loop
	// list, however, and we currently have no way to query a loop to find out
	// which type it is. Still, the maximal u,v parameter range will be useful
	// for most surfaces and most evaluation purposes.
	AcGeInterval uParam;
	AcGeInterval vParam;
	((AcGeExternalBoundedSurface*)surfaceGeometry)->getEnvelope(uParam, vParam);
    // Make sure the u,v values are legal and the envelope is bounded
    if ((uParam.isBounded()) && (vParam.isBounded())) {
		AcGePoint2d midRange;
		midRange.x = uParam.lowerBound() + (uParam.length() / 2.0);
		midRange.y = vParam.lowerBound() + (vParam.length() / 2.0);
		AcGePoint3d pointOnSurface =
			((AcGeExternalBoundedSurface*)surfaceGeometry)->evalPoint(midRange);
		acutPrintf(ACRX_T("\nSurface Evaluation Begin:\n"));
		acutPrintf(ACRX_T(" Parameter space bounds are (("));
        acutPrintf(ACRX_T("%lf, "), uParam.lowerBound());
        acutPrintf(ACRX_T("%lf "), uParam.upperBound());
        acutPrintf(ACRX_T("), (\n"));
        acutPrintf(ACRX_T("%lf, "), vParam.lowerBound());
        acutPrintf(ACRX_T("%lf "), vParam.upperBound());
        acutPrintf(ACRX_T("))\n"));
		acutPrintf(ACRX_T(" Parameter space mid-range is ("));
        acutPrintf(ACRX_T(" %lf, "), midRange.x);
        acutPrintf(ACRX_T("%lf "), midRange.y);
        acutPrintf(ACRX_T(")\n"));
		acutPrintf(ACRX_T(" Point on surface is ("));
		acutPrintf (ACRX_T("%lf , "), pointOnSurface.x);	
		acutPrintf (ACRX_T("%lf , "), pointOnSurface.y);
		acutPrintf (ACRX_T("%lf "), pointOnSurface.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T("Surface Evaluation End\n"));
    }
	delete surfaceGeometry;

	Adesk::Boolean oriented;
	returnValue = faceEntity.getOrientToSurface(oriented);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrFace::getOrientToSurface:"));
        errorReport(returnValue);
		return returnValue;
	} 
	oriented ? acutPrintf(ACRX_T("\nSurface Orientation is Positive\n"))
	    : acutPrintf(ACRX_T("\nSurface Orientation is Negative\n"));

	return returnValue;
}
