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
// Edge and curve dump utilities.

#include "brsample_pch.h"  //precompiled header

// Abbreviations
#include "brgblabb.h"


// local function prototypes
static AcBr::ErrorStatus edgeVertexDump(const AcBrEdge& edgeEntity);


AcBr::ErrorStatus
edgeDump(const AcBrEdge& edgeEntity)
{
	AcBr::ErrorStatus returnValue = AcBr::eOk;

	// Verify that AcBr was explicitly and not implicitly loaded,
	// by testing ObjectARX functions (which are unavailable unless
	// explicitly loaded)
    if (edgeEntity.isA() == NULL) {
        acutPrintf("\n edgeDump: AcBrEntity::isA() failed\n");
        return returnValue;
    }
    if (!edgeEntity.isKindOf(AcBrEdge::desc())) {
        acutPrintf("\n edgeDump: AcBrEntity::isKindOf() failed\n");
        return returnValue;
    }
	AcBrEntity* entClass = (AcBrEntity*)&edgeEntity;
	AcBrFace* pFace = AcBrFace::cast(entClass);  
	if (pFace != NULL) {
		acutPrintf("\n edgeDump: AcBrEntity::cast() failed\n");
        return (AcBrErrorStatus)Acad::eNotThatKindOfClass;
	} 

	// validate the brep "owner" of the edge
	AcBrBrep brepOwner;
	returnValue = edgeEntity.getBrep(brepOwner);
	if (returnValue != AcBr::eOk) {
		acutPrintf("\n Error in AcBrEdge::getBrep:");
		errorReport(returnValue);
		return returnValue;
	}

	AcGe::EntityId entId;
	returnValue = edgeEntity.getCurveType(entId);
	if (returnValue != AcBr::eOk) {
		if (returnValue == (AcBr::ErrorStatus)Acad::eDegenerateGeometry) {
			acutPrintf("\n Degenerate edge geometry: apex of cone");
			returnValue = edgeVertexDump(edgeEntity);
			if (returnValue != AcBr::eOk) {
				acutPrintf("\n Error in edgeVertexDump:");
				errorReport(returnValue);
				return returnValue;
			}
		} else {
			acutPrintf("\n Error in AcBrEdge::getCurveType:");
			errorReport(returnValue);
			return returnValue;
		}
	}  

	AcGeCurve3d* curveGeometry = NULL;
    AcGeCurve3d* nativeGeometry = NULL;

	returnValue = getNativeCurve(edgeEntity, curveGeometry, nativeGeometry);  
	if (returnValue != AcBr::eOk) {
		acutPrintf("\n Error in getNativeCurve:");
		errorReport(returnValue);
		delete curveGeometry;
		delete nativeGeometry;
		return returnValue;
	}

	switch (entId) {
    case(kLine3d):
	{ 
		acutPrintf("\nCurve Type: Line\n");
        AcGeLine3d* lineGeometry = (AcGeLine3d*)nativeGeometry;
        AcGePoint3d pt = lineGeometry->pointOnLine();
        AcGeVector3d dir = lineGeometry->direction();
		acutPrintf("\nCurve Definition Data Begin:\n");
		acutPrintf(" Point on Line is (");
		acutPrintf ("%lf , ", pt.x);	
		acutPrintf ("%lf , ", pt.y);
		acutPrintf ("%lf ", pt.z);
		acutPrintf(")\n");	
		acutPrintf(" Line direction is (");
		acutPrintf ("%lf , ", dir.x);	
		acutPrintf ("%lf , ", dir.y);
		acutPrintf ("%lf ", dir.z);
		acutPrintf(")\n");	
		acutPrintf("Curve Definition Data End\n");
		break;
    }

	case(kRay3d):
	{ 
		acutPrintf("\nCurve Type: Ray\n");
        AcGeRay3d* rayGeometry = (AcGeRay3d*)nativeGeometry;
        AcGePoint3d pt = rayGeometry->pointOnLine();
        AcGeVector3d dir = rayGeometry->direction();
		acutPrintf("\nCurve Definition Data Begin:\n");
		acutPrintf(" Point on Ray is (");
		acutPrintf ("%lf , ", pt.x);	
		acutPrintf ("%lf , ", pt.y);
		acutPrintf ("%lf ", pt.z);
		acutPrintf(")\n");	
		acutPrintf(" Ray direction is (");
		acutPrintf ("%lf , ", dir.x);	
		acutPrintf ("%lf , ", dir.y);
		acutPrintf ("%lf ", dir.z);
		acutPrintf(")\n");	
		acutPrintf("Curve Definition Data End\n");
		break;
    }

    case(kLineSeg3d):
	{ 
		acutPrintf("\nCurve Type: Line Segment\n");
        AcGeLineSeg3d* segGeometry = (AcGeLineSeg3d*)nativeGeometry;
        AcGePoint3d pt = segGeometry->pointOnLine();
        AcGeVector3d dir = segGeometry->direction();
		acutPrintf("\nCurve Definition Data Begin:\n");
		acutPrintf(" Point on Line Segment is (");
		acutPrintf ("%lf , ", pt.x);	
		acutPrintf ("%lf , ", pt.y);
		acutPrintf ("%lf ", pt.z);
		acutPrintf(")\n");	
		acutPrintf(" Line Segment direction is (");
		acutPrintf ("%lf , ", dir.x);	
		acutPrintf ("%lf , ", dir.y);
		acutPrintf ("%lf ", dir.z);
		acutPrintf(")\n");	
		acutPrintf("Curve Definition Data End\n");
        AcGePoint3d pt1, pt2;
		acutPrintf("\nCurve Subset Data Begin:\n");
        if (segGeometry->hasStartPoint(pt1)) {
            acutPrintf("\n Line Segment start point is(");
    		acutPrintf ("%lf , ", pt1.x);	
    		acutPrintf ("%lf , ", pt1.y);
    		acutPrintf ("%lf ", pt1.z);
    		acutPrintf(")\n");	
        }
        if (segGeometry->hasEndPoint(pt2)) {
            acutPrintf("\n Line Segment end point is(");
    		acutPrintf ("%lf , ", pt2.x);	
    		acutPrintf ("%lf , ", pt2.y);
    		acutPrintf ("%lf ", pt2.z);
    		acutPrintf(")\n");	
        }
		acutPrintf("Curve Subset Data End\n");
		break;
    }

	case(kEllipArc3d):
    {
		acutPrintf("\nCurve Type: Elliptic Arc\n");
        AcGeEllipArc3d* ellipGeometry = (AcGeEllipArc3d*)nativeGeometry;
        AcGePoint3d centre = ellipGeometry->center();
        AcGePoint3d start = ellipGeometry->startPoint();
        AcGePoint3d end = ellipGeometry->endPoint();
		acutPrintf("\nCurve Definition Data Begin:\n");
		acutPrintf(" Elliptic Arc centre is (");
		acutPrintf ("%lf , ", centre.x);	
		acutPrintf ("%lf , ", centre.y);
		acutPrintf ("%lf ", centre.z);
		acutPrintf(")\n");	
		acutPrintf(" Elliptic Arc major radius is %lf\n", ellipGeometry->majorRadius());
		acutPrintf(" Elliptic Arc minor radius is %lf\n", ellipGeometry->minorRadius());
		acutPrintf(" Elliptic Arc start angle is %lf\n", ellipGeometry->startAng());
		acutPrintf(" Elliptic Arc end angle is %lf\n", ellipGeometry->endAng());
		acutPrintf(" Elliptic Arc start point  is (");
		acutPrintf ("%lf , ", start.x);	
		acutPrintf ("%lf , ", start.y);
		acutPrintf ("%lf ", start.z);
		acutPrintf(")\n");	
		acutPrintf(" Elliptic Arc end point is (");
		acutPrintf ("%lf , ", end.x);	
		acutPrintf ("%lf , ", end.y);
		acutPrintf ("%lf ", end.z);
		acutPrintf(")\n");	
		acutPrintf("Curve Definition Data End\n");
        AcGePoint3d pt1, pt2;
		acutPrintf("\nCurve Subset Data Begin:\n");
        if (ellipGeometry->hasStartPoint(pt1)) {
            acutPrintf("\n Elliptic Arc start point is(");
    		acutPrintf ("%lf , ", pt1.x);	
    		acutPrintf ("%lf , ", pt1.y);
    		acutPrintf ("%lf ", pt1.z);
    		acutPrintf(")\n");	
        }
        if (ellipGeometry->hasEndPoint(pt2)) {
            acutPrintf("\n Elliptic Arc end point is(");
    		acutPrintf ("%lf , ", pt2.x);	
    		acutPrintf ("%lf , ", pt2.y);
    		acutPrintf ("%lf ", pt2.z);
    		acutPrintf(")\n");	
        }
		acutPrintf("Curve Subset Data End\n");
		break;
    }

	case(kCircArc3d):
    {
		acutPrintf("\nCurve Type: Circular Arc\n");
        AcGeCircArc3d* circGeometry = (AcGeCircArc3d*)nativeGeometry;
        AcGePoint3d centre = circGeometry->center();
        AcGePoint3d start = circGeometry->startPoint();
        AcGePoint3d end = circGeometry->endPoint();
		acutPrintf("\nCurve Definition Data Begin:\n");
		acutPrintf(" Circular Arc centre is (");
		acutPrintf ("%lf , ", centre.x);	
		acutPrintf ("%lf , ", centre.y);
		acutPrintf ("%lf ", centre.z);
		acutPrintf(")\n");	
		acutPrintf(" Circular Arc radius is %lf\n", circGeometry->radius());
		acutPrintf(" Circular Arc start angle is %lf\n", circGeometry->startAng());
		acutPrintf(" Circular Arc end angle is %lf\n", circGeometry->endAng());
		acutPrintf(" Circular Arc start point  is (");
		acutPrintf ("%lf , ", start.x);	
		acutPrintf ("%lf , ", start.y);
		acutPrintf ("%lf ", start.z);
		acutPrintf(")\n");	
		acutPrintf(" Circular Arc end point is (");
		acutPrintf ("%lf , ", end.x);	
		acutPrintf ("%lf , ", end.y);
		acutPrintf ("%lf ", end.z);
		acutPrintf(")\n");	
		acutPrintf("Curve Definition Data End\n");
        AcGePoint3d pt1, pt2;
		acutPrintf("\nCurve Subset Data Begin:\n");
        if (circGeometry->hasStartPoint(pt1)) {
            acutPrintf("\n Circular Arc start point is(");
    		acutPrintf ("%lf , ", pt1.x);	
    		acutPrintf ("%lf , ", pt1.y);
    		acutPrintf ("%lf ", pt1.z);
    		acutPrintf(")\n");	
        }
        if (circGeometry->hasEndPoint(pt2)) {
            acutPrintf("\n Circular Arc end point is(");
    		acutPrintf ("%lf , ", pt2.x);	
    		acutPrintf ("%lf , ", pt2.y);
    		acutPrintf ("%lf ", pt2.z);
    		acutPrintf(")\n");	
        }
		acutPrintf("Curve Subset Data End\n");
		break;
    }

	case(kNurbCurve3d):
    {
		acutPrintf("\nCurve Type: 3D NURB Curve\n");
        AcGeNurbCurve3d* nurbGeometry = (AcGeNurbCurve3d*)nativeGeometry;
		acutPrintf("\nCurve Definition Data Begin:\n");
		int i, nCtrlPts, nKnots, nWeights;
		acutPrintf("\n **3D NURB Curve of degree %d and order %d\n",
			nurbGeometry->degree(), nurbGeometry->order());

		nCtrlPts = nurbGeometry->numControlPoints();
		acutPrintf("\n **3D NURB Curve has %d control points\n", nCtrlPts);
		for(i=0; i<nCtrlPts; i++) {
			acutPrintf("\n ***Control point [%d] (%lf, %lf, %lf)\n", i,
				nurbGeometry->controlPointAt(i).x,
				nurbGeometry->controlPointAt(i).y,
				nurbGeometry->controlPointAt(i).z);
		}

		nKnots = nurbGeometry->numKnots();
		acutPrintf("\n **3D NURB Curve has %d knots\n", nKnots);
	   	for (i=0; i<nKnots; i++) {
			acutPrintf("\n ***Knot [%d] %lf\n", i,
				nurbGeometry->knotAt(i));
		}

		nWeights = nurbGeometry->numWeights();
		acutPrintf("\n **3D NURB Curve has %d weights\n", nWeights);
		for (i=0; i<nWeights; i++) {
			acutPrintf("\n ***Weight [%d] %lf\n", i,
				nurbGeometry->weightAt(i));
		}	  
		acutPrintf("Curve Definition Data End\n");
        AcGePoint3d pt1, pt2;
		acutPrintf("\nCurve Subset Data Begin:\n");
        if (nurbGeometry->hasStartPoint(pt1)) {
            acutPrintf("\n **3D NURB Curve start point is(");
    		acutPrintf ("%lf , ", pt1.x);	
    		acutPrintf ("%lf , ", pt1.y);
    		acutPrintf ("%lf ", pt1.z);
    		acutPrintf(")\n");	
        }
        if (nurbGeometry->hasEndPoint(pt2)) {
            acutPrintf("\n **3D NURB Curve end point is(");
    		acutPrintf ("%lf , ", pt2.x);	
    		acutPrintf ("%lf , ", pt2.y);
    		acutPrintf ("%lf ", pt2.z);
    		acutPrintf(")\n");	
        }
		acutPrintf("Curve Subset Data End\n");
		break;
    }

	default:
		acutPrintf("\nCurve Type: Unexpected Non Curve\n");
		return (AcBrErrorStatus)Acad::eInvalidInput;
		break;
	} // end switch(entId)	
    delete nativeGeometry;

    // Evaluate the curve 
	AcGeInterval intrvl;
	((AcGeExternalCurve3d*)curveGeometry)->getInterval(intrvl);
    // Make sure the interval is legal and bounded
    if ((intrvl.isBounded()) && (intrvl.length() >= 0.0)) {
		double midParam = intrvl.lowerBound() + (intrvl.length() / 2.0);
		AcGePoint3d pointOnCurve =
			((AcGeExternalCurve3d*)curveGeometry)->evalPoint(midParam);
		AcGePoint3d startPoint =
			((AcGeExternalCurve3d*)curveGeometry)->evalPoint(intrvl.lowerBound());
		AcGePoint3d endPoint =
			((AcGeExternalCurve3d*)curveGeometry)->evalPoint(intrvl.upperBound());
		acutPrintf("\nCurve Evaluation Begin:\n");
		acutPrintf(" Parameterisation is (");
        acutPrintf("%lf, ", intrvl.lowerBound());
        acutPrintf("%lf ", intrvl.upperBound());
        acutPrintf(")\n");
		acutPrintf(" Parameter space mid-point is %lf\n", midParam);
		acutPrintf(" Point on curve is (");
		acutPrintf ("%lf , ", pointOnCurve.x);	
		acutPrintf ("%lf , ", pointOnCurve.y);
		acutPrintf ("%lf ", pointOnCurve.z);
		acutPrintf(")\n");	
		acutPrintf(" Curve start point is (");
		acutPrintf ("%lf , ", startPoint.x);	
		acutPrintf ("%lf , ", startPoint.y);
		acutPrintf ("%lf ", startPoint.z);
		acutPrintf(")\n");	
		acutPrintf(" Curve end point is (");
		acutPrintf ("%lf , ", endPoint.x);	
		acutPrintf ("%lf , ", endPoint.y);
		acutPrintf ("%lf ", endPoint.z);
		acutPrintf(")\n");	
		acutPrintf("Curve Evaluation End\n");
    }
    delete curveGeometry;

	Adesk::Boolean oriented;
	returnValue = edgeEntity.getOrientToCurve(oriented);
	if (returnValue != AcBr::eOk) {
		acutPrintf("\n Error in AcBrEdge::getOrientToCurve:");
        errorReport(returnValue);
		return returnValue;
	} 
	oriented ? acutPrintf("\nCurve Orientation is Positive\n")
	    : acutPrintf("\nCurve Orientation is Negative\n");

	returnValue = edgeVertexDump(edgeEntity);
	if (returnValue != AcBr::eOk) {
		acutPrintf("\n Error in edgeVertexDump:");
        errorReport(returnValue);
        return returnValue;
	}

	return returnValue;
}


static AcBr::ErrorStatus
edgeVertexDump(const AcBrEdge& edgeEntity)
{
	AcBr::ErrorStatus returnValue = AcBr::eOk;

	AcBrVertex startVertex;
	returnValue	= edgeEntity.getVertex1(startVertex);
	if (returnValue != AcBr::eOk) {
		acutPrintf("\n Error in AcBrEdge::getVertex1:");
        errorReport(returnValue);
        return returnValue;
	}
	if (!startVertex.isNull()) {
		acutPrintf("\nCoordinate of vertex1 : ");
		returnValue	= vertexDump(startVertex);
		if (returnValue != AcBr::eOk) {
		    acutPrintf("\n Error in vertexDump:");
		    errorReport(returnValue);
			return returnValue;
		}
	}
	
	AcBrVertex endVertex;
	returnValue	= edgeEntity.getVertex2(endVertex);
	if (returnValue != AcBr::eOk) {
		acutPrintf("\n Error in AcBrEdge::getVertex2:");
        errorReport(returnValue);
        return returnValue;
	}
	if (!endVertex.isNull()) {
		acutPrintf("\nCoordinate of vertex2: ");
		returnValue = vertexDump(endVertex);
		if (returnValue != AcBr::eOk) {
		    acutPrintf("\n Error in vertexDump:");
		    errorReport(returnValue);
			return returnValue;
		}
	}

	AcBrVertex newVertex;
	AcDbFullSubentPath subPath;
	returnValue = endVertex.get(subPath);
	if (returnValue != AcBr::eOk) {
		acutPrintf("\n Error in AcBrVertex::get:");
        errorReport(returnValue);
        return returnValue;
	}
	returnValue = newVertex.set(subPath);
	if (returnValue != AcBr::eOk) {
		acutPrintf("\n Error in AcBrVertex::set:");
        errorReport(returnValue);
        return returnValue;
	}
	if (!newVertex.isEqualTo(&endVertex)) {
		acutPrintf("\n Vertex copy is unequal");
	}

	return returnValue;
}
