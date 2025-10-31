//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
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
        acutPrintf(ACRX_T("\n edgeDump: AcBrEntity::isA() failed\n"));
        return returnValue;
    }
    if (!edgeEntity.isKindOf(AcBrEdge::desc())) {
        acutPrintf(ACRX_T("\n edgeDump: AcBrEntity::isKindOf() failed\n"));
        return returnValue;
    }
	AcBrEntity* entClass = (AcBrEntity*)&edgeEntity;
	AcBrFace* pFace = AcBrFace::cast(entClass);  
	if (pFace != NULL) {
		acutPrintf(ACRX_T("\n edgeDump: AcBrEntity::cast() failed\n"));
        return (AcBrErrorStatus)Acad::eNotThatKindOfClass;
	} 

	// validate the brep "owner" of the edge
	AcBrBrep brepOwner;
	returnValue = edgeEntity.getBrep(brepOwner);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrEdge::getBrep:"));
		errorReport(returnValue);
		return returnValue;
	}

	AcGe::EntityId entId;
	returnValue = edgeEntity.getCurveType(entId);
	if (returnValue != AcBr::eOk) {
		if (returnValue == (AcBr::ErrorStatus)Acad::eDegenerateGeometry) {
			acutPrintf(ACRX_T("\n Degenerate edge geometry: apex of cone"));
			returnValue = edgeVertexDump(edgeEntity);
			if (returnValue != AcBr::eOk) {
				acutPrintf(ACRX_T("\n Error in edgeVertexDump:"));
				errorReport(returnValue);
				return returnValue;
			}
		} else {
			acutPrintf(ACRX_T("\n Error in AcBrEdge::getCurveType:"));
			errorReport(returnValue);
			return returnValue;
		}
	}  

	AcGeCurve3d* curveGeometry = NULL;
    AcGeCurve3d* nativeGeometry = NULL;

	returnValue = getNativeCurve(edgeEntity, curveGeometry, nativeGeometry);  
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in getNativeCurve:"));
		errorReport(returnValue);
		delete curveGeometry;
		delete nativeGeometry;
		return returnValue;
	}

	switch (entId) {
    case(kLine3d):
	{ 
		acutPrintf(ACRX_T("\nCurve Type: Line\n"));
        AcGeLine3d* lineGeometry = (AcGeLine3d*)nativeGeometry;
        AcGePoint3d pt = lineGeometry->pointOnLine();
        AcGeVector3d dir = lineGeometry->direction();
		acutPrintf(ACRX_T("\nCurve Definition Data Begin:\n"));
		acutPrintf(ACRX_T(" Point on Line is ("));
		acutPrintf (ACRX_T("%lf , "), pt.x);	
		acutPrintf (ACRX_T("%lf , "), pt.y);
		acutPrintf (ACRX_T("%lf "), pt.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Line direction is ("));
		acutPrintf (ACRX_T("%lf , "), dir.x);	
		acutPrintf (ACRX_T("%lf , "), dir.y);
		acutPrintf (ACRX_T("%lf "), dir.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T("Curve Definition Data End\n"));
		break;
    }

	case(kRay3d):
	{ 
		acutPrintf(ACRX_T("\nCurve Type: Ray\n"));
        AcGeRay3d* rayGeometry = (AcGeRay3d*)nativeGeometry;
        AcGePoint3d pt = rayGeometry->pointOnLine();
        AcGeVector3d dir = rayGeometry->direction();
		acutPrintf(ACRX_T("\nCurve Definition Data Begin:\n"));
		acutPrintf(ACRX_T(" Point on Ray is ("));
		acutPrintf (ACRX_T("%lf , "), pt.x);	
		acutPrintf (ACRX_T("%lf , "), pt.y);
		acutPrintf (ACRX_T("%lf "), pt.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Ray direction is ("));
		acutPrintf (ACRX_T("%lf , "), dir.x);	
		acutPrintf (ACRX_T("%lf , "), dir.y);
		acutPrintf (ACRX_T("%lf "), dir.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T("Curve Definition Data End\n"));
		break;
    }

    case(kLineSeg3d):
	{ 
		acutPrintf(ACRX_T("\nCurve Type: Line Segment\n"));
        AcGeLineSeg3d* segGeometry = (AcGeLineSeg3d*)nativeGeometry;
        AcGePoint3d pt = segGeometry->pointOnLine();
        AcGeVector3d dir = segGeometry->direction();
		acutPrintf(ACRX_T("\nCurve Definition Data Begin:\n"));
		acutPrintf(ACRX_T(" Point on Line Segment is ("));
		acutPrintf (ACRX_T("%lf , "), pt.x);	
		acutPrintf (ACRX_T("%lf , "), pt.y);
		acutPrintf (ACRX_T("%lf "), pt.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Line Segment direction is ("));
		acutPrintf (ACRX_T("%lf , "), dir.x);	
		acutPrintf (ACRX_T("%lf , "), dir.y);
		acutPrintf (ACRX_T("%lf "), dir.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T("Curve Definition Data End\n"));
        AcGePoint3d pt1, pt2;
		acutPrintf(ACRX_T("\nCurve Subset Data Begin:\n"));
        if (segGeometry->hasStartPoint(pt1)) {
            acutPrintf(ACRX_T("\n Line Segment start point is("));
    		acutPrintf (ACRX_T("%lf , "), pt1.x);	
    		acutPrintf (ACRX_T("%lf , "), pt1.y);
    		acutPrintf (ACRX_T("%lf "), pt1.z);
    		acutPrintf(ACRX_T(")\n"));	
        }
        if (segGeometry->hasEndPoint(pt2)) {
            acutPrintf(ACRX_T("\n Line Segment end point is("));
    		acutPrintf (ACRX_T("%lf , "), pt2.x);	
    		acutPrintf (ACRX_T("%lf , "), pt2.y);
    		acutPrintf (ACRX_T("%lf "), pt2.z);
    		acutPrintf(ACRX_T(")\n"));	
        }
		acutPrintf(ACRX_T("Curve Subset Data End\n"));
		break;
    }

	case(kEllipArc3d):
    {
		acutPrintf(ACRX_T("\nCurve Type: Elliptic Arc\n"));
        AcGeEllipArc3d* ellipGeometry = (AcGeEllipArc3d*)nativeGeometry;
        AcGePoint3d centre = ellipGeometry->center();
        AcGePoint3d start = ellipGeometry->startPoint();
        AcGePoint3d end = ellipGeometry->endPoint();
		acutPrintf(ACRX_T("\nCurve Definition Data Begin:\n"));
		acutPrintf(ACRX_T(" Elliptic Arc centre is ("));
		acutPrintf (ACRX_T("%lf , "), centre.x);	
		acutPrintf (ACRX_T("%lf , "), centre.y);
		acutPrintf (ACRX_T("%lf "), centre.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Elliptic Arc major radius is %lf\n"), ellipGeometry->majorRadius());
		acutPrintf(ACRX_T(" Elliptic Arc minor radius is %lf\n"), ellipGeometry->minorRadius());
		acutPrintf(ACRX_T(" Elliptic Arc start angle is %lf\n"), ellipGeometry->startAng());
		acutPrintf(ACRX_T(" Elliptic Arc end angle is %lf\n"), ellipGeometry->endAng());
		acutPrintf(ACRX_T(" Elliptic Arc start point  is ("));
		acutPrintf (ACRX_T("%lf , "), start.x);	
		acutPrintf (ACRX_T("%lf , "), start.y);
		acutPrintf (ACRX_T("%lf "), start.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Elliptic Arc end point is ("));
		acutPrintf (ACRX_T("%lf , "), end.x);	
		acutPrintf (ACRX_T("%lf , "), end.y);
		acutPrintf (ACRX_T("%lf "), end.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T("Curve Definition Data End\n"));
        AcGePoint3d pt1, pt2;
		acutPrintf(ACRX_T("\nCurve Subset Data Begin:\n"));
        if (ellipGeometry->hasStartPoint(pt1)) {
            acutPrintf(ACRX_T("\n Elliptic Arc start point is("));
    		acutPrintf (ACRX_T("%lf , "), pt1.x);	
    		acutPrintf (ACRX_T("%lf , "), pt1.y);
    		acutPrintf (ACRX_T("%lf "), pt1.z);
    		acutPrintf(ACRX_T(")\n"));	
        }
        if (ellipGeometry->hasEndPoint(pt2)) {
            acutPrintf(ACRX_T("\n Elliptic Arc end point is("));
    		acutPrintf (ACRX_T("%lf , "), pt2.x);	
    		acutPrintf (ACRX_T("%lf , "), pt2.y);
    		acutPrintf (ACRX_T("%lf "), pt2.z);
    		acutPrintf(ACRX_T(")\n"));	
        }
		acutPrintf(ACRX_T("Curve Subset Data End\n"));
		break;
    }

	case(kCircArc3d):
    {
		acutPrintf(ACRX_T("\nCurve Type: Circular Arc\n"));
        AcGeCircArc3d* circGeometry = (AcGeCircArc3d*)nativeGeometry;
        AcGePoint3d centre = circGeometry->center();
        AcGePoint3d start = circGeometry->startPoint();
        AcGePoint3d end = circGeometry->endPoint();
		acutPrintf(ACRX_T("\nCurve Definition Data Begin:\n"));
		acutPrintf(ACRX_T(" Circular Arc centre is ("));
		acutPrintf (ACRX_T("%lf , "), centre.x);	
		acutPrintf (ACRX_T("%lf , "), centre.y);
		acutPrintf (ACRX_T("%lf "), centre.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Circular Arc radius is %lf\n"), circGeometry->radius());
		acutPrintf(ACRX_T(" Circular Arc start angle is %lf\n"), circGeometry->startAng());
		acutPrintf(ACRX_T(" Circular Arc end angle is %lf\n"), circGeometry->endAng());
		acutPrintf(ACRX_T(" Circular Arc start point  is ("));
		acutPrintf (ACRX_T("%lf , "), start.x);	
		acutPrintf (ACRX_T("%lf , "), start.y);
		acutPrintf (ACRX_T("%lf "), start.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Circular Arc end point is ("));
		acutPrintf (ACRX_T("%lf , "), end.x);	
		acutPrintf (ACRX_T("%lf , "), end.y);
		acutPrintf (ACRX_T("%lf "), end.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T("Curve Definition Data End\n"));
        AcGePoint3d pt1, pt2;
		acutPrintf(ACRX_T("\nCurve Subset Data Begin:\n"));
        if (circGeometry->hasStartPoint(pt1)) {
            acutPrintf(ACRX_T("\n Circular Arc start point is("));
    		acutPrintf (ACRX_T("%lf , "), pt1.x);	
    		acutPrintf (ACRX_T("%lf , "), pt1.y);
    		acutPrintf (ACRX_T("%lf "), pt1.z);
    		acutPrintf(ACRX_T(")\n"));	
        }
        if (circGeometry->hasEndPoint(pt2)) {
            acutPrintf(ACRX_T("\n Circular Arc end point is("));
    		acutPrintf (ACRX_T("%lf , "), pt2.x);	
    		acutPrintf (ACRX_T("%lf , "), pt2.y);
    		acutPrintf (ACRX_T("%lf "), pt2.z);
    		acutPrintf(ACRX_T(")\n"));	
        }
		acutPrintf(ACRX_T("Curve Subset Data End\n"));
		break;
    }

	case(kNurbCurve3d):
    {
		acutPrintf(ACRX_T("\nCurve Type: 3D NURB Curve\n"));
        AcGeNurbCurve3d* nurbGeometry = (AcGeNurbCurve3d*)nativeGeometry;
		acutPrintf(ACRX_T("\nCurve Definition Data Begin:\n"));
		int i, nCtrlPts, nKnots, nWeights;
		acutPrintf(ACRX_T("\n **3D NURB Curve of degree %d and order %d\n"),
			nurbGeometry->degree(), nurbGeometry->order());

		nCtrlPts = nurbGeometry->numControlPoints();
		acutPrintf(ACRX_T("\n **3D NURB Curve has %d control points\n"), nCtrlPts);
		for(i=0; i<nCtrlPts; i++) {
			acutPrintf(ACRX_T("\n ***Control point [%d] (%lf, %lf, %lf)\n"), i,
				nurbGeometry->controlPointAt(i).x,
				nurbGeometry->controlPointAt(i).y,
				nurbGeometry->controlPointAt(i).z);
		}

		nKnots = nurbGeometry->numKnots();
		acutPrintf(ACRX_T("\n **3D NURB Curve has %d knots\n"), nKnots);
	   	for (i=0; i<nKnots; i++) {
			acutPrintf(ACRX_T("\n ***Knot [%d] %lf\n"), i,
				nurbGeometry->knotAt(i));
		}

		nWeights = nurbGeometry->numWeights();
		acutPrintf(ACRX_T("\n **3D NURB Curve has %d weights\n"), nWeights);
		for (i=0; i<nWeights; i++) {
			acutPrintf(ACRX_T("\n ***Weight [%d] %lf\n"), i,
				nurbGeometry->weightAt(i));
		}	  
		acutPrintf(ACRX_T("Curve Definition Data End\n"));
        AcGePoint3d pt1, pt2;
		acutPrintf(ACRX_T("\nCurve Subset Data Begin:\n"));
        if (nurbGeometry->hasStartPoint(pt1)) {
            acutPrintf(ACRX_T("\n **3D NURB Curve start point is("));
    		acutPrintf (ACRX_T("%lf , "), pt1.x);	
    		acutPrintf (ACRX_T("%lf , "), pt1.y);
    		acutPrintf (ACRX_T("%lf "), pt1.z);
    		acutPrintf(ACRX_T(")\n"));	
        }
        if (nurbGeometry->hasEndPoint(pt2)) {
            acutPrintf(ACRX_T("\n **3D NURB Curve end point is("));
    		acutPrintf (ACRX_T("%lf , "), pt2.x);	
    		acutPrintf (ACRX_T("%lf , "), pt2.y);
    		acutPrintf (ACRX_T("%lf "), pt2.z);
    		acutPrintf(ACRX_T(")\n"));	
        }
		acutPrintf(ACRX_T("Curve Subset Data End\n"));
		break;
    }

	default:
		acutPrintf(ACRX_T("\nCurve Type: Unexpected Non Curve\n"));
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
		acutPrintf(ACRX_T("\nCurve Evaluation Begin:\n"));
		acutPrintf(ACRX_T(" Parameterisation is ("));
        acutPrintf(ACRX_T("%lf, "), intrvl.lowerBound());
        acutPrintf(ACRX_T("%lf "), intrvl.upperBound());
        acutPrintf(ACRX_T(")\n"));
		acutPrintf(ACRX_T(" Parameter space mid-point is %lf\n"), midParam);
		acutPrintf(ACRX_T(" Point on curve is ("));
		acutPrintf (ACRX_T("%lf , "), pointOnCurve.x);	
		acutPrintf (ACRX_T("%lf , "), pointOnCurve.y);
		acutPrintf (ACRX_T("%lf "), pointOnCurve.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Curve start point is ("));
		acutPrintf (ACRX_T("%lf , "), startPoint.x);	
		acutPrintf (ACRX_T("%lf , "), startPoint.y);
		acutPrintf (ACRX_T("%lf "), startPoint.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T(" Curve end point is ("));
		acutPrintf (ACRX_T("%lf , "), endPoint.x);	
		acutPrintf (ACRX_T("%lf , "), endPoint.y);
		acutPrintf (ACRX_T("%lf "), endPoint.z);
		acutPrintf(ACRX_T(")\n"));	
		acutPrintf(ACRX_T("Curve Evaluation End\n"));
    }
    delete curveGeometry;

	Adesk::Boolean oriented;
	returnValue = edgeEntity.getOrientToCurve(oriented);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrEdge::getOrientToCurve:"));
        errorReport(returnValue);
		return returnValue;
	} 
	oriented ? acutPrintf(ACRX_T("\nCurve Orientation is Positive\n"))
	    : acutPrintf(ACRX_T("\nCurve Orientation is Negative\n"));

	returnValue = edgeVertexDump(edgeEntity);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in edgeVertexDump:"));
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
		acutPrintf(ACRX_T("\n Error in AcBrEdge::getVertex1:"));
        errorReport(returnValue);
        return returnValue;
	}
	if (!startVertex.isNull()) {
		acutPrintf(ACRX_T("\nCoordinate of vertex1 : "));
		returnValue	= vertexDump(startVertex);
		if (returnValue != AcBr::eOk) {
		    acutPrintf(ACRX_T("\n Error in vertexDump:"));
		    errorReport(returnValue);
			return returnValue;
		}
	}
	
	AcBrVertex endVertex;
	returnValue	= edgeEntity.getVertex2(endVertex);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrEdge::getVertex2:"));
        errorReport(returnValue);
        return returnValue;
	}
	if (!endVertex.isNull()) {
		acutPrintf(ACRX_T("\nCoordinate of vertex2: "));
		returnValue = vertexDump(endVertex);
		if (returnValue != AcBr::eOk) {
		    acutPrintf(ACRX_T("\n Error in vertexDump:"));
		    errorReport(returnValue);
			return returnValue;
		}
	}

	AcBrVertex newVertex;
	AcDbFullSubentPath subPath;
	returnValue = endVertex.get(subPath);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrVertex::get:"));
        errorReport(returnValue);
        return returnValue;
	}
	returnValue = newVertex.set(subPath);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrVertex::set:"));
        errorReport(returnValue);
        return returnValue;
	}
	if (!newVertex.isEqualTo(&endVertex)) {
		acutPrintf(ACRX_T("\n Vertex copy is unequal"));
	}

	return returnValue;
}
