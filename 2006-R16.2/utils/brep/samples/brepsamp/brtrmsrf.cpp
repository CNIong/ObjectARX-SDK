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
// Source file for the ObjectARX application command "BRTRMSRF".
#include "brsample_pch.h"  //precompiled header

// Abbreviations
#include "acdbabb.h"

// local function prototypes
static AcBr::ErrorStatus faceToTrimmedSurface(AcBrFace& faceEntity);
static AcBr::ErrorStatus faceToNurbSurface(AcBrFace& faceEntity);


void
trimSurface()
{								  
    AcBr::ErrorStatus returnValue = AcBr::eOk;
    Acad::ErrorStatus acadReturnValue = eOk;

    // Get the subentity path for a face
	AcDbFullSubentPath subPath(kNullSubent);
	acadReturnValue = selectEntity(AcDb::kFaceSubentType, subPath);
	if (acadReturnValue != eOk) {
		acutPrintf("\n Error in getPath: %d", acadReturnValue);
		return;
	}

	// Make a face entity to access the surface
	AcBrFace faceEntity;
	returnValue = faceEntity.set(subPath);
	if (returnValue != AcBr::eOk) {
		acutPrintf("\n Error in AcBrFace::set:");
		errorReport(returnValue);
		return;
	}

	// Query the style for trimmed surface dump
	Adesk::Boolean trimmed = Adesk::kTrue;
    char opt[128];
   	while (Adesk::kTrue) {
		acutPrintf("\nSelect Style for Trimmed Surface Dump: ");
		acedInitGet(NULL, "Nurb Trimmed");
		if (acedGetKword("Nurb/<Trimmed>: ", opt) == RTCAN) return;

        // Map the user input to a valid dump style
		if ((strcmp(opt, "Trimmed") == 0) || (strcmp(opt, "") == 0)) {
            trimmed = Adesk::kTrue;
            break;
        } else if ((strcmp(opt, "Nurb") == 0)) {
            trimmed = Adesk::kFalse;
            break;
	    }
    }

	(trimmed) ? faceToTrimmedSurface(faceEntity) : faceToNurbSurface(faceEntity);

	return;
}


static AcBr::ErrorStatus
faceToTrimmedSurface(AcBrFace& faceEntity)
{ 
    AcBr::ErrorStatus returnValue = AcBr::eOk;

	// This is the full trimmed face, which may split to multiple surfaces.
	Adesk::UInt32 numNurbs = 0;
	AcGeExternalBoundedSurface** nurbs = NULL;

	returnValue = faceEntity.getSurfaceAsTrimmedNurbs(numNurbs, nurbs);
	if (returnValue != AcBr::eOk) {
		acutPrintf("\n Error in AcBrFace::getSurfaceAsTrimmedNurbs:");
    	errorReport(returnValue);
        return returnValue;
	}
	acutPrintf("\nSurface As Trimmed Nurbs\n");

	for (Adesk::UInt32 i = 0; i < numNurbs; i++) {
		AcGeInterval uParam, vParam;
		nurbs[i]->getEnvelope(uParam, vParam);

		int numBoundaries = 0;
		AcGeCurveBoundary* pBoundaries = NULL;
		nurbs[i]->getContours(numBoundaries, pBoundaries);
		if ((numBoundaries == 0) || (pBoundaries == NULL))
			return AcBr::eMissingGeometry;

		acutPrintf("\n*Trimmed Surface No. %d\n", i+1);

		acutPrintf(" Parameter space bounds are ((");
		if (uParam.isBoundedBelow()) {
			acutPrintf("%lf, ", uParam.lowerBound());
		} else {
			acutPrintf("-INF, ");
		}
		if (uParam.isBoundedAbove()) {
			acutPrintf("%lf ", uParam.upperBound());
		} else {
			acutPrintf("INF ");
		}
		acutPrintf("), (\n");
		if (vParam.isBoundedBelow()) {
			acutPrintf("%lf, ", vParam.lowerBound());
		} else {
			acutPrintf("-INF, ");
		}
		if (vParam.isBoundedAbove()) {
			acutPrintf("%lf ", vParam.upperBound());
		} else {
			acutPrintf("INF ");
		}
		acutPrintf("))\n");

		for (int j = 0; j < numBoundaries; j++) {
			int numCurveElements = 0;
			AcGeEntity3d** ppCurves = NULL;
			AcGeCurve2d** ppPcurves = NULL;
			Adesk::Boolean* pOrient3d = NULL;
			Adesk::Boolean* pOrient2d = NULL;
			pBoundaries[j].getContour(numCurveElements, &ppCurves, &ppPcurves,
				&pOrient3d, &pOrient2d);
			if ((numCurveElements == 0) || (ppCurves == NULL) || (pOrient3d == NULL))
				return AcBr::eMissingGeometry;
			acutPrintf("\n**Surface Boundary Contour No. %d\n", j+1);

			for (int k = 0; k < numCurveElements; k++) {
				acutPrintf("\n***Contour Curve Element No. %d\n", k+1);

				switch (ppCurves[k]->type()) {
				case(AcGe::kPosition3d):
				{
					AcGePoint3d pt(*(AcGePosition3d*)ppCurves[k]);
					acutPrintf("\n****Contour Curve Degenerate Point is (");
					acutPrintf ("%lf, ", pt.x);	
					acutPrintf ("%lf, ", pt.y);
					acutPrintf ("%lf", pt.z);
					acutPrintf(")\n");	
					break;
				}
				case(AcGe::kExternalCurve3d):
				{
					// Make sure the interval is legal and bounded
					AcGeInterval intrvl;
					((AcGeExternalCurve3d*)ppCurves[k])->getInterval(intrvl);
					if ((!intrvl.isBounded()) || (intrvl.length() < 0.0)) 
						return (AcBr::ErrorStatus)Acad::eAmbiguousOutput;
					AcGePoint3d startPt =
						((AcGeExternalCurve3d*)ppCurves[k])->evalPoint(intrvl.lowerBound());
					AcGePoint3d endPt =
						((AcGeExternalCurve3d*)ppCurves[k])->evalPoint(intrvl.upperBound());
					acutPrintf("\n****Contour Curve Start Point is (");
					acutPrintf ("%lf , ", startPt.x);	
					acutPrintf ("%lf , ", startPt.y);
					acutPrintf ("%lf ", startPt.z);
					acutPrintf(")\n");	
					acutPrintf("\n****Contour Curve End Point is (");
					acutPrintf ("%lf , ", endPt.x);	
					acutPrintf ("%lf , ", endPt.y);
					acutPrintf ("%lf ", endPt.z);
					acutPrintf(")\n");
					pOrient3d[k]
						? acutPrintf("\n****Contour Curve Orientation is Positive\n")
						: acutPrintf("\n****Contour Curve Orientation is Negative\n");
					break;
				}
				default:
					acutPrintf("\nfaceToTrimmedSurface: Illegal Contour Entity Type\n");
					return (AcBr::ErrorStatus)Acad::eAmbiguousOutput;
				}
				delete ppCurves[k];

				if (ppPcurves[k]->type() == AcGe::kExternalCurve2d) {
					// Dump the start and end points in UV space to locate gaps
					AcGePoint2d startPt, endPt, lastEndPt;
					((AcGeExternalCurve2d*)ppPcurves[k])->hasStartPoint(startPt);
					((AcGeExternalCurve2d*)ppPcurves[k])->hasEndPoint(endPt);
					if (k)
						((AcGeExternalCurve2d*)ppPcurves[k-1])->hasEndPoint(lastEndPt);
					else
						((AcGeExternalCurve2d*)ppPcurves[numCurveElements-1])->hasEndPoint(lastEndPt);
					acutPrintf("\n****Contour Curve UV-Dist from last is (");
					char s[80] = "";
					sprintf(s, "%g)\n", (startPt-lastEndPt).length());
					acutPrintf(s);
					acutPrintf("\n****Contour Parameter Curve Start Point is (");
					acutPrintf ("%lf , ", startPt.x);	
					acutPrintf ("%lf ", startPt.y);
					acutPrintf(")\n");	
					acutPrintf("\n****Contour Parameter Curve End Point is (");
					acutPrintf ("%lf , ", endPt.x);	
					acutPrintf ("%lf ", endPt.y);
					acutPrintf(")\n");
					pOrient2d[k]
						? acutPrintf("\n****Contour Parameter Curve Orientation is Positive\n")
						: acutPrintf("\n****Contour Parameter Curve Orientation is Negative\n");
				} else {
					acutPrintf("\nfaceToTrimmedSurface: Illegal Contour Entity Type\n");
					return (AcBr::ErrorStatus)Acad::eAmbiguousOutput;
				}
				//delete ppPcurves[k];
			}
			delete[] ppCurves;
			delete[] ppPcurves;
			delete[] pOrient3d;
			delete[] pOrient2d;
		}
		delete[] pBoundaries;
		delete nurbs[i];
	}
	delete[] nurbs;

    return returnValue;
}


static AcBr::ErrorStatus
faceToNurbSurface(AcBrFace& faceEntity)
{ 
    AcBr::ErrorStatus returnValue = AcBr::eOk;

	// This is the face-bounded surface converted to a NURB.
	double fitTol = 0.0;

	AcGeNurbSurface surfaceGeometry;
    returnValue = faceEntity.getSurfaceAsNurb(surfaceGeometry, 0.0, fitTol);  
	if (returnValue != AcBr::eOk) {
		acutPrintf("\n Error in AcBrFace::getSurfaceAsNurb:");
    	errorReport(returnValue);
        return returnValue;
	}

	acutPrintf("\nSurface As Bounded Nurb\n");
	acutPrintf("\n*Surface fit tolerance is %lf\n", fitTol);
	
	acutPrintf("\n**NURB Surface Definition Data begin:\n");
	acutPrintf("\n**NURB Surface degree in U is %d\n", surfaceGeometry.degreeInU());
	acutPrintf("\n**NURB Surface degree in V is %d\n", surfaceGeometry.degreeInV());
	acutPrintf("\n**NURB Surface number of control points in U is %d\n", 
		surfaceGeometry.numControlPointsInU());
	acutPrintf("\n**NURB Surface number of control points in V is %d\n", 
		surfaceGeometry.numControlPointsInV());
	acutPrintf("\n**NURB Surface number of knots in U is %d\n", 
		surfaceGeometry.numKnotsInU());
	acutPrintf("\n**NURB Surface number of knots in V is %d\n", 
		surfaceGeometry.numKnotsInV());
	acutPrintf("\n*NURB Surface Definition Data End\n");

	// make a face loop traverser to access the surface boundary
	AcBrFaceLoopTraverser faceLoopTrav;
	returnValue = faceLoopTrav.setFace(faceEntity);
	if (returnValue != AcBr::eOk) {
        // eDegenerateTopology means intrinsically bounded (e.g., sphere, torus)  
		if (returnValue != AcBr::eDegenerateTopology) {
		    acutPrintf("\n Error in AcBrFaceLoopTraverser::setFace:"); 
			errorReport(returnValue);
			return returnValue;
        } else {
		    acutPrintf("\n faceToTrimmedSurface: trimmed data unavailable on intrinsically bounded surfaces\n"); 
			errorReport(returnValue);
			return returnValue;
        }
	} else while (!faceLoopTrav.done() && (returnValue == AcBr::eOk)) { 
    	// make a loop edge traverser to access the trimming data
	    AcBrLoopEdgeTraverser loopEdgeTrav;
    	returnValue = loopEdgeTrav.setLoop(faceLoopTrav);
	    if (returnValue != AcBr::eOk) {	 
            // eDegenerateTopology means loop vertex (special case and go to next loop) 
        	if (returnValue != AcBr::eDegenerateTopology) {
			    acutPrintf("\n Error in AcBrLoopEdgeTraverser::setLoop:"); 
    		    errorReport(returnValue);
    		    return returnValue;
			} else {
				AcBrLoopVertexTraverser loopVertexTrav;
				returnValue = loopVertexTrav.setLoop(faceLoopTrav);
				if (returnValue != AcBr::eOk) {
					acutPrintf("\n Error in AcBrLoopVertexTraverser::setLoop:");
					errorReport(returnValue);
					return returnValue;
				} else {
					AcBrVertex loopVertex;
					returnValue = loopVertexTrav.getVertex(loopVertex);
					if (returnValue != AcBr::eOk) {
						acutPrintf("\n Error in AcBrLoopVertexTraverser::getVertex:");
						errorReport(returnValue);
						return returnValue;
					}

					AcGePoint3d pointGeometry;
					returnValue = loopVertex.getPoint(pointGeometry);
				    if (returnValue != AcBr::eOk) {
						acutPrintf("\n Error in AcBrVertex::getPoint:");
						errorReport(returnValue);
						return returnValue;
					}
                	acutPrintf("\n*** Coordinates (x,y,z) at loop vertex: ");
					acutPrintf("%lf,%lf,%lf\n", pointGeometry.x, pointGeometry.y,
						pointGeometry.z);

					AcGePoint2d ppointGeometry;
					returnValue = loopVertexTrav.getParamPoint(ppointGeometry);
				    if (returnValue != AcBr::eOk) {
						acutPrintf("\n Error in AcBrLoopVertexTraverser::getParamPoint:");
						errorReport(returnValue);
						return returnValue;
					}
                	acutPrintf("\n*** Parameters (u,v) at loop vertex: ");
					acutPrintf("%lf,%lf\n", ppointGeometry.x, ppointGeometry.y);
				} // end loop vertex
			}
	    } else while (!loopEdgeTrav.done() && (returnValue == AcBr::eOk)) { 
			int i, nCtrlPts, nKnots, nWeights;
			
			// Dump the model space NURB curve data
			AcGeNurbCurve3d curveGeometry;
			returnValue = loopEdgeTrav.getOrientedCurveAsNurb(curveGeometry, 0.0, fitTol);  
			if (returnValue != AcBr::eOk) {
				acutPrintf("\n Error in AcBrLoopEdgeTraverser::getOrientedCurveAsNurb:");
    			errorReport(returnValue);
				return returnValue;
		    }

			acutPrintf("\n3D NURB Curve fit tolerance is %lf\n", fitTol);

			acutPrintf("\n **3D NURB Curve of degree %d and order %d\n",
			    curveGeometry.degree(), curveGeometry.order());

			nCtrlPts = curveGeometry.numControlPoints();
			acutPrintf("\n **3D NURB Curve has %d control points\n", nCtrlPts);
			for(i=0; i<nCtrlPts; i++) {
				acutPrintf("\n ***Control point [%d] (%lf, %lf, %lf)\n", i,
					curveGeometry.controlPointAt(i).x,
					curveGeometry.controlPointAt(i).y,
					curveGeometry.controlPointAt(i).z);
			}

			nKnots = curveGeometry.numKnots();
		   	acutPrintf("\n **3D NURB Curve has %d knots\n", nKnots);
		   	for (i=0; i<nKnots; i++) {
				acutPrintf("\n ***Knot [%d] %lf\n", i,
					curveGeometry.knotAt(i));
			}

			nWeights = curveGeometry.numWeights();
			acutPrintf("\n **3D NURB Curve has %d weights\n", nWeights);
			for (i=0; i<nWeights; i++) {
				acutPrintf("\n ***Weight [%d] %lf)\n", i,
					curveGeometry.weightAt(i));
			}	  

			AcGePoint3d pt1, pt2;
			if (curveGeometry.hasStartPoint(pt1)) {
				acutPrintf("\n **3D NURB Curve start point is(");
    			acutPrintf ("%lf , ", pt1.x);	
    			acutPrintf ("%lf , ", pt1.y);
    			acutPrintf ("%lf ", pt1.z);
    			acutPrintf(")\n");	
			}
			if (curveGeometry.hasEndPoint(pt2)) {
				acutPrintf("\n **3D NURB Curve end point is(");
    			acutPrintf ("%lf , ", pt2.x);	
    			acutPrintf ("%lf , ", pt2.y);
    			acutPrintf ("%lf ", pt2.z);
    			acutPrintf(")\n");	
			}

			// Dump the parameter space NURB curve data
			AcGeNurbCurve2d pcurveGeometry;
			returnValue = loopEdgeTrav.getParamCurveAsNurb(pcurveGeometry, 0.0, fitTol);  
			if (returnValue != AcBr::eOk) {
				acutPrintf("\n Error in AcBrLoopEdgeTraverser::getParamCurveAsNurb:");
    			errorReport(returnValue);
				return returnValue;
		    }

			acutPrintf("\n2D NURB Curve fit tolerance is %lf\n", fitTol);

			acutPrintf("\n **2D NURB Curve of degree %d and order %d\n",
			    pcurveGeometry.degree(), pcurveGeometry.order());

			nCtrlPts = pcurveGeometry.numControlPoints();
			acutPrintf("\n **2D NURB Curve has %d control points\n", nCtrlPts);
			for(i=0; i<nCtrlPts; i++) {
				acutPrintf("\n ***Control point [%d] (%lf, %lf)\n", i,
					pcurveGeometry.controlPointAt(i).x,
					pcurveGeometry.controlPointAt(i).y);
			}

			nKnots = pcurveGeometry.numKnots();
		   	acutPrintf("\n **2D NURB Curve has %d knots\n", nKnots);
		   	for (i=0; i<nKnots; i++) {
				acutPrintf("\n ***Knot [%d] %lf\n", i,
					pcurveGeometry.knotAt(i));
			}

			nWeights = pcurveGeometry.numWeights();
			acutPrintf("\n **2D NURB Curve has %d weights\n", nWeights);
			for (i=0; i<nWeights; i++) {
				acutPrintf("\n ***Weight [%d] %lf)\n", i,
					pcurveGeometry.weightAt(i));
			}	  

			returnValue = loopEdgeTrav.next();
		    if (returnValue != AcBr::eOk) {
			    acutPrintf("\n Error in AcBrLoopEdgeTraverser::next:");
			    errorReport(returnValue);
			    return returnValue;
	    	}
	    } // end edge while

    	returnValue = faceLoopTrav.next();
    	if (returnValue != AcBr::eOk) {
	    	acutPrintf("\n Error in AcBrFaceLoopTraverser::next:");
		    errorReport(returnValue);
		    return returnValue;
	    }
	} // end loop while

    return returnValue;
}

