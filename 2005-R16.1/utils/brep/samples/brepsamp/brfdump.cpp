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
        acutPrintf("\n faceDump: AcBrEntity::isA() failed\n");
        return returnValue;
    }
    if (!faceEntity.isKindOf(AcBrFace::desc())) {
        acutPrintf("\n faceDump: AcBrEntity::isKindOf() failed\n");
        return returnValue;
    }
	AcBrEntity* entClass = (AcBrEntity*)&faceEntity;
	AcBrEdge* pEdge = AcBrEdge::cast(entClass);  
	if (pEdge != NULL) {
		acutPrintf("\n faceDump: AcBrEntity::cast() failed\n");
        return (AcBrErrorStatus)Acad::eNotThatKindOfClass;
	} 

	AcGe::EntityId entId;
	returnValue = faceEntity.getSurfaceType(entId);  
	if (returnValue != AcBr::eOk) {
		acutPrintf("\n Error in AcBrFace::getSurfaceType:");
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
		acutPrintf("\n Error in getNativeSurface:");
		errorReport(returnValue);
        delete surfaceGeometry;
        delete nativeGeometry;
        return returnValue;
	}

	switch (entId) {
	case(kPlane):
	{ 
		acutPrintf("\nSurface Type: Plane\n");
        AcGePlane* planeGeometry = (AcGePlane*)nativeGeometry;
        AcGePoint3d pt = planeGeometry->pointOnPlane();
        AcGeVector3d normal = planeGeometry->normal();
		acutPrintf("\nSurface Definition Data Begin:\n");
		acutPrintf(" Point on Plane is (");
		acutPrintf ("%lf , ", pt.x);	
		acutPrintf ("%lf , ", pt.y);
		acutPrintf ("%lf ", pt.z);
		acutPrintf(")\n");	
		acutPrintf(" Plane normal direction is (");
		acutPrintf ("%lf , ", normal.x);	
		acutPrintf ("%lf , ", normal.y);
		acutPrintf ("%lf ", normal.z);
		acutPrintf(")\n");	
		acutPrintf("Surface Definition Data End\n");
		break;
    } 
	
	case(kSphere):
    {
		acutPrintf("\nSurface Type: Sphere\n");
        AcGeSphere* sphereGeometry = (AcGeSphere*)nativeGeometry;
        AcGePoint3d centre = sphereGeometry->center();
		double ang1, ang2, ang3, ang4;
        sphereGeometry->getAnglesInU(ang1, ang2);
        sphereGeometry->getAnglesInV(ang3, ang4);
        AcGePoint3d north = sphereGeometry->northPole();
        AcGePoint3d south = sphereGeometry->southPole();
		acutPrintf("\nSurface Definition Data Begin:\n");
		acutPrintf(" Sphere centre is (");
		acutPrintf ("%lf , ", centre.x);	
		acutPrintf ("%lf , ", centre.y);
		acutPrintf ("%lf ", centre.z);
		acutPrintf(")\n");	
		acutPrintf(" Sphere radius is %lf\n", sphereGeometry->radius());
		acutPrintf(" Sphere start angle in U is %lf\n", ang1);
		acutPrintf(" Sphere end angle in U is %lf\n", ang2);
		acutPrintf(" Sphere start angle in V is %lf\n", ang3);
		acutPrintf(" Sphere end angle in V is %lf\n", ang4);
		acutPrintf(" Sphere north pole is (");
		acutPrintf ("%lf , ", north.x);	
		acutPrintf ("%lf , ", north.y);
		acutPrintf ("%lf ", north.z);
		acutPrintf(")\n");	
		acutPrintf(" Sphere south pole is (");
		acutPrintf ("%lf , ", south.x);	
		acutPrintf ("%lf , ", south.y);
		acutPrintf ("%lf ", south.z);
		acutPrintf(")\n");	
		acutPrintf("Surface Definition Data End\n");
		break;
    }
	
	case(kTorus):
    {
		acutPrintf("\nSurface Type: Torus\n");
        AcGeTorus* torusGeometry = (AcGeTorus*)nativeGeometry;
        AcGePoint3d centre = torusGeometry->center();
		double ang1, ang2, ang3, ang4;
        torusGeometry->getAnglesInU(ang1, ang2);
        torusGeometry->getAnglesInV(ang3, ang4);
		acutPrintf("\nSurface Definition Data Begin:\n");
		acutPrintf(" Torus centre is (");
		acutPrintf ("%lf , ", centre.x);	
		acutPrintf ("%lf , ", centre.y);
		acutPrintf ("%lf ", centre.z);
		acutPrintf(")\n");	
		acutPrintf(" Torus major radius is %lf\n", torusGeometry->majorRadius());
		acutPrintf(" Torus minor radius is %lf\n", torusGeometry->minorRadius());
		acutPrintf(" Torus start angle in U is %lf\n", ang1);
		acutPrintf(" Torus end angle in U is %lf\n", ang2);
		acutPrintf(" Torus start angle in V is %lf\n", ang3);
		acutPrintf(" Torus end angle in V is %lf\n", ang4);
		acutPrintf("Surface Definition Data End\n");
		break;	
	}	
	
	case(kCylinder):
    {
		acutPrintf("\nSurface Type: Circular Cylinder\n");
        AcGeCylinder* cylinderGeometry = (AcGeCylinder*)nativeGeometry;
        AcGePoint3d origin = cylinderGeometry->origin();
		double ang1, ang2;
        cylinderGeometry->getAngles(ang1, ang2);
        AcGeInterval ht;
        cylinderGeometry->getHeight(ht);
        double height = ht.upperBound() - ht.lowerBound();
        AcGeVector3d refAxis = cylinderGeometry->refAxis();
        AcGeVector3d symAxis = cylinderGeometry->axisOfSymmetry();
		acutPrintf("\nSurface Definition Data Begin:\n");
		acutPrintf(" Circular Cylinder origin is (");
		acutPrintf ("%lf , ", origin.x);	
		acutPrintf ("%lf , ", origin.y);
		acutPrintf ("%lf ", origin.z);
		acutPrintf(")\n");	
		acutPrintf(" Circular Cylinder radius is %lf\n", cylinderGeometry->radius());
		acutPrintf(" Circular Cylinder start angle is %lf\n", ang1);
		acutPrintf(" Circular Cylinder end angle is %lf\n", ang2);
		if (cylinderGeometry->isClosedInU())
			acutPrintf(" Circular Cylinder height is %lf\n", height);
        else acutPrintf(" Circular Cylinder is not closed in U\n");
		acutPrintf(" Circular Cylinder reference axis is (");
		acutPrintf ("%lf , ", refAxis.x);	
		acutPrintf ("%lf , ", refAxis.y);
		acutPrintf ("%lf ", refAxis.z);
		acutPrintf(")\n");	
		acutPrintf(" Circular Cylinder axis of symmetry is (");
		acutPrintf ("%lf , ", symAxis.x);	
		acutPrintf ("%lf , ", symAxis.y);
		acutPrintf ("%lf ", symAxis.z);
		acutPrintf(")\n");	
		acutPrintf("Surface Definition Data End\n");
		break;
    }

	case(kCone):
    {
		acutPrintf("\nSurface Type: Circular Cone\n");
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
		acutPrintf("\nSurface Definition Data Begin:\n");
		acutPrintf(" Circular Cone base centre is (");
		acutPrintf ("%lf , ", centre.x);	
		acutPrintf ("%lf , ", centre.y);
		acutPrintf ("%lf ", centre.z);
		acutPrintf(")\n");	
		acutPrintf(" Circular Cone base radius is %lf\n", coneGeometry->baseRadius());
		acutPrintf(" Circular Cone start angle is %lf\n", ang1);
		acutPrintf(" Circular Cone end angle is %lf\n", ang2);
		acutPrintf(" Circular Cone axis of symmetry is (");
		acutPrintf ("%lf , ", axis1.x);	
		acutPrintf ("%lf , ", axis1.y);
		acutPrintf ("%lf ", axis1.z);
		acutPrintf(")\n");	
		acutPrintf(" Circular Cone reference axis is (");
		acutPrintf ("%lf , ", axis2.x);	
		acutPrintf ("%lf , ", axis2.y);
		acutPrintf ("%lf ", axis2.z);
		acutPrintf(")\n");	
		acutPrintf(" Circular Cone apex is (");
		acutPrintf ("%lf , ", apex.x);	
		acutPrintf ("%lf , ", apex.y);
		acutPrintf ("%lf ", apex.z);
		acutPrintf(")\n");	
		acutPrintf(" Circular Cone cosine of major half-angle is %lf\n", cosAng);
		acutPrintf(" Circular Cone sine of major half-angle is %lf\n", sinAng);
		if (coneGeometry->isClosedInU())
			acutPrintf(" Circular Cone height is %lf\n", height);
        else acutPrintf(" Circular Cone is not closed in U\n");
		acutPrintf("Surface Definition Data End\n");
		break;
    }
	
	case(kNurbSurface):
    {
		acutPrintf("\nSurface Type: NURB Surface\n");
        AcGeNurbSurface* nurbGeometry = (AcGeNurbSurface*)nativeGeometry;
		int nCtrlPtsU = nurbGeometry->numControlPointsInU();
		int nCtrlPtsV = nurbGeometry->numControlPointsInV();
		int nKnotsU = nurbGeometry->numKnotsInU();
		int nKnotsV = nurbGeometry->numKnotsInV();
		acutPrintf("\nSurface Definition Data Begin:\n");
		acutPrintf(" NURB Surface degree in U is %d\n", nurbGeometry->degreeInU());
		acutPrintf(" NURB Surface degree in V is %d\n", nurbGeometry->degreeInV());
		acutPrintf(" NURB Surface number of control points in U is %d\n", nCtrlPtsU);
		acutPrintf(" NURB Surface number of control points in V is %d\n", nCtrlPtsV);
		acutPrintf(" NURB Surface number of knots in U is %d\n", nKnotsU);
		acutPrintf(" NURB Surface number of knots in V is %d\n", nKnotsV);
		acutPrintf("Surface Definition Data End\n");
		break;
    }
	
	// NOTE: This surface is not yet supported in AcGe, so we infer the definition
	// data by analysing evaluated data on the external bounded surface.
	case(kEllipCylinder):
	{
		acutPrintf("\nSurface Type: Elliptic Cylinder\n");
        AcGePoint3d p0 = surfaceGeometry->evalPoint(AcGePoint2d(0.0, 0.0));
        AcGePoint3d p1 = surfaceGeometry->evalPoint(AcGePoint2d(0.0, kPi));
        AcGePoint3d p2 = surfaceGeometry->evalPoint(AcGePoint2d(0.0, kHalfPi));
        AcGePoint3d origin(((p0.x + p1.x) / 2.0),
			               ((p0.y + p1.y) / 2.0),
						   ((p0.z + p1.z) / 2.0));
        AcGeVector3d majAxis = p0 - origin;
        AcGeVector3d minAxis = p2 - origin;
        AcGeVector3d symAxis = (majAxis.crossProduct(minAxis)).normalize();
		acutPrintf("\nSurface Definition Data Begin:\n");
		acutPrintf(" Elliptic Cylinder origin is (");
		acutPrintf ("%lf , ", origin.x);	
		acutPrintf ("%lf , ", origin.y);
		acutPrintf ("%lf ", origin.z);
		acutPrintf(")\n");	
		acutPrintf(" Elliptic Cylinder major radius is %lf\n", majAxis.length());
		acutPrintf(" Elliptic Cylinder minor radius is %lf\n", minAxis.length());
		acutPrintf(" Elliptic Cylinder major axis is (");
		acutPrintf ("%lf , ", majAxis.x);	
		acutPrintf ("%lf , ", majAxis.y);
		acutPrintf ("%lf ", majAxis.z);
		acutPrintf(")\n");	
		acutPrintf(" Elliptic Cylinder minor axis is (");
		acutPrintf ("%lf , ", minAxis.x);	
		acutPrintf ("%lf , ", minAxis.y);
		acutPrintf ("%lf ", minAxis.z);
		acutPrintf(")\n");	
		acutPrintf(" Elliptic Cylinder axis of symmetry is (");
		acutPrintf ("%lf , ", symAxis.x);	
		acutPrintf ("%lf , ", symAxis.y);
		acutPrintf ("%lf ", symAxis.z);
		acutPrintf(")\n");	
		acutPrintf("Surface Definition Data End\n");
		break;
	}

	// NOTE: This surface is not yet supported in AcGe, so we infer the definition
	// data by analysing evaluated data on the external bounded surface.
	case(kEllipCone):
	{
		acutPrintf("\nSurface Type: Elliptic Cone\n");
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
		acutPrintf("\nSurface Definition Data Begin:\n");
		acutPrintf(" Elliptic Cone base centre is (");
		acutPrintf ("%lf , ", centre.x);	
		acutPrintf ("%lf , ", centre.y);
		acutPrintf ("%lf ", centre.z);
		acutPrintf(")\n");	
		acutPrintf(" Elliptic Cone base major radius is %lf\n", majAxis.length());
		acutPrintf(" Elliptic Cone base minor radius is %lf\n", minAxis.length());
		acutPrintf(" Elliptic Cone major axis is (");
		acutPrintf ("%lf , ", majAxis.x);	
		acutPrintf ("%lf , ", majAxis.y);
		acutPrintf ("%lf ", majAxis.z);
		acutPrintf(")\n");	
		acutPrintf(" Elliptic Cone minor axis is (");
		acutPrintf ("%lf , ", minAxis.x);	
		acutPrintf ("%lf , ", minAxis.y);
		acutPrintf ("%lf ", minAxis.z);
		acutPrintf(")\n");	
		acutPrintf(" Elliptic Cone axis of symmetry is (");
		acutPrintf ("%lf , ", symAxis.x);	
		acutPrintf ("%lf , ", symAxis.y);
		acutPrintf ("%lf ", symAxis.z);
		acutPrintf(")\n");	
		acutPrintf(" Elliptic Cone cosine of major half-angle is %lf\n", cos(halfAng));
		acutPrintf(" Elliptic Cone sine of major half-angle is %lf\n", sin(halfAng));
		acutPrintf("Surface Definition Data End\n");
		break;
	}

	default:
		acutPrintf("\nSurface Type: Unexpected Non Surface\n");
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
		acutPrintf("\nSurface Evaluation Begin:\n");
		acutPrintf(" Parameter space bounds are ((");
        acutPrintf("%lf, ", uParam.lowerBound());
        acutPrintf("%lf ", uParam.upperBound());
        acutPrintf("), (\n");
        acutPrintf("%lf, ", vParam.lowerBound());
        acutPrintf("%lf ", vParam.upperBound());
        acutPrintf("))\n");
		acutPrintf(" Parameter space mid-range is (");
        acutPrintf(" %lf, ", midRange.x);
        acutPrintf("%lf ", midRange.y);
        acutPrintf(")\n");
		acutPrintf(" Point on surface is (");
		acutPrintf ("%lf , ", pointOnSurface.x);	
		acutPrintf ("%lf , ", pointOnSurface.y);
		acutPrintf ("%lf ", pointOnSurface.z);
		acutPrintf(")\n");	
		acutPrintf("Surface Evaluation End\n");
    }
	delete surfaceGeometry;

	Adesk::Boolean oriented;
	returnValue = faceEntity.getOrientToSurface(oriented);
	if (returnValue != AcBr::eOk) {
		acutPrintf("\n Error in AcBrFace::getOrientToSurface:");
        errorReport(returnValue);
		return returnValue;
	} 
	oriented ? acutPrintf("\nSurface Orientation is Positive\n")
	    : acutPrintf("\nSurface Orientation is Negative\n");

	return returnValue;
}
