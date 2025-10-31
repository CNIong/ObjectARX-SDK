//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Brep dump utilities.

#include "brsample_pch.h"  //precompiled header



// Abbreviations
#include "acdbabb.h"




// local function prototypes
static AcBr::ErrorStatus brepDumpDown	(const AcBrBrep& brepEntity);
static AcBr::ErrorStatus brepDumpUp		(const AcBrBrep& brepEntity);


AcBr::ErrorStatus
brepDump(const AcBrBrep& brepEntity)
{ 
    AcBr::ErrorStatus returnValue = AcBr::eOk;

	// Validate the brep vs. the brep "owner"
	AcBrBrep brepOwner;
	returnValue = brepEntity.getBrep(brepOwner);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrBrep::getBrep:"));
		errorReport(returnValue);
		return returnValue;
	}
	if (!brepEntity.isEqualTo(&brepOwner)) {
		acutPrintf(ACRX_T("\n Brep owner is out of sync with brep!"));
		return (AcBr::ErrorStatus)Acad::eAmbiguousOutput;
	}

	// Query traversal direction for brep dump 
	Adesk::Boolean downwards = Adesk::kTrue;
    ACHAR opt[128];
   	while (Adesk::kTrue) {
		acutPrintf(ACRX_T("\nSelect Traversal Direction for Brep Dump: "));
		acedInitGet(NULL, ACRX_T("Upwards Downwards"));
		if (acedGetKword(ACRX_T("Upwards/<Downwards>: "), opt) == RTCAN)
			return returnValue;

        // Map the user input to a valid traversal direction
		if ((_tcscmp(opt, ACRX_T("Downwards")) == 0) || (_tcscmp(opt, ACRX_T("")) == 0)) {
            downwards = Adesk::kTrue;
            break;
        } else if ((_tcscmp(opt, ACRX_T("Upwards")) == 0)) {
            downwards = Adesk::kFalse;
            break;
	    }
    }

	// Switchable dump based on upwards vs. downwards traversal
	if (downwards) brepDumpDown(brepEntity);
	else brepDumpUp(brepEntity);

	return returnValue;
}


static AcBr::ErrorStatus
brepDumpDown(const AcBrBrep& brepEntity)
{ 
    AcBr::ErrorStatus returnValue = AcBr::eOk;

	// make a global complex traverser
	AcBrBrepComplexTraverser brepComplexTrav;
	returnValue = brepComplexTrav.setBrep(brepEntity);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrBrepComplexTraverser::setBrep:"));
		errorReport(returnValue);
		return returnValue;
	}

	// dump the complexes
	int complexCount = 0;
	while (!brepComplexTrav.done() && (returnValue == AcBr::eOk)) {
	    complexCount++;
	    acutPrintf(ACRX_T("\n *Complex No: %d \n"), complexCount);

		// make a complex shell traverser
		AcBrComplexShellTraverser complexShellTrav;
		returnValue = complexShellTrav.setComplex(brepComplexTrav);
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in AcBrComplexShellTraverser::setComplex:"));
			errorReport(returnValue);
			return returnValue;
		}

		// dump the shells
		int shellCount = 0;
		while (!complexShellTrav.done() && (returnValue == AcBr::eOk)) {
			shellCount++;
			acutPrintf(ACRX_T("\n **Shell No: %d \n"), shellCount);

			AcBrShell shell;
			returnValue = complexShellTrav.getShell(shell);
			 if (returnValue != AcBr::eOk) {	
				acutPrintf(ACRX_T("\n Error in AcBrComplexShellTraverser::getShell:")); 
				errorReport(returnValue);
				return returnValue;
			}
			AcBr::ShellType stype;
			shell.getType(stype);
			shellTypeReport(stype);

			// make a shell face traverser
			AcBrShellFaceTraverser shellFaceTrav;
			returnValue = shellFaceTrav.setShell(complexShellTrav);
			if (returnValue != AcBr::eOk) {
				acutPrintf(ACRX_T("\n Error in AcBrShellFaceTraverser::setShell:"));
				errorReport(returnValue);
				return returnValue;
			}

			// count the faces
			int faceCount = 0;
			while (!shellFaceTrav.done() && (returnValue == AcBr::eOk)) {
				faceCount++;
				acutPrintf(ACRX_T("\n ***Face No: %d \n"), faceCount);

				AcBrFace currentFace;
				returnValue = shellFaceTrav.getFace(currentFace);
				if (returnValue != AcBr::eOk) {
					acutPrintf(ACRX_T("\n Error in AcBrShellFaceTraverser::getFace:"));
					errorReport(returnValue);
					return returnValue;
				}

    			// make sure that comparing different types returns kFalse
				// rather than crashing!
				if (currentFace.isEqualTo(&brepEntity)) {
					acutPrintf(ACRX_T("\n Brep and face have the same contents (impossible!)"));
					return (AcBr::ErrorStatus)eAmbiguousOutput;
				}

				int loopCount = 0;
				AcBrFaceLoopTraverser faceLoopTrav;
				returnValue = faceLoopTrav.setFace(shellFaceTrav);
				if (returnValue != AcBr::eOk) {
					// eDegenerateTopology means intrinsically bounded (e.g., sphere, torus)  
					if (returnValue != AcBr::eDegenerateTopology) {
						acutPrintf(ACRX_T("\n Error in AcBrFaceLoopTraverser::setFace:")); 
						errorReport(returnValue);
						return returnValue;
					} else returnValue = AcBr::eOk;
				} else while (!faceLoopTrav.done() && (returnValue == AcBr::eOk)) { 
					loopCount++;
					acutPrintf(ACRX_T("\n ****Loop No: %d \n"), loopCount);

					AcBrLoop loop;
					returnValue = faceLoopTrav.getLoop(loop);
					 if (returnValue != AcBr::eOk) {	
						acutPrintf(ACRX_T("\n Error in AcBrFaceLoopTraverser::getLoop:")); 
						errorReport(returnValue);
						return returnValue;
					}
					AcBr::LoopType ltype;
					loop.getType(ltype);
					loopTypeReport(ltype);

					int edgeCount = 0;
					AcBrLoopEdgeTraverser loopEdgeTrav;
	    			returnValue = loopEdgeTrav.setLoop(faceLoopTrav);
					if ((returnValue != AcBr::eOk) && (returnValue != AcBr::eDegenerateTopology)) {	 
						// eDegenerateTopology means this edge is a singularity (loop-vertex)
						acutPrintf(ACRX_T("\n Error in AcBrLoopEdgeTraverser::setLoop:")); 
						errorReport(returnValue);
						return returnValue;
					} else while (!loopEdgeTrav.done() && (returnValue == AcBr::eOk)) { 
						edgeCount++; 
						acutPrintf(ACRX_T("\n *****Edge No: %d \n"), edgeCount);

						AcBrEdge edgeEntity;
						returnValue = loopEdgeTrav.getEdge(edgeEntity);
						if (returnValue != AcBr::eOk) {
							acutPrintf(ACRX_T("\n Error in AcBrLoopEdgeTraverser::getEdge:"));
							errorReport(returnValue);
							return returnValue;
						}

    					// validate the 3d model space curve associated with this edge
            			AcGeCurve3d* curveGeometry = NULL;
						AcGeCurve3d* nativeGeometry = NULL;

            			returnValue = getNativeOrientedCurve(loopEdgeTrav, curveGeometry, nativeGeometry);  
            			if (returnValue != AcBr::eOk) {
            				acutPrintf(ACRX_T("\n Error in getNativeOrientedCurve:"));
            				errorReport(returnValue);
							delete curveGeometry;
							delete nativeGeometry;
							return returnValue;
            			}
				
    					// validate the 2d parameter space curve associated with this edge
    					AcGeCurve2d* pcurveGeometry =  NULL;
    					AcGeNurbCurve2d nurbGeometry;
    					returnValue = getNativeParamCurve(loopEdgeTrav, pcurveGeometry, nurbGeometry);
    					if (returnValue != AcBr::eOk) {
    						acutPrintf(ACRX_T("\n Error in getNativeParamCurve:"));
    						errorReport(returnValue);
							delete pcurveGeometry;
							return returnValue;
    					}
						if (pcurveGeometry != NULL) {
							// Determine if the model space curve and parameter space curve
							// agree in their orientation (2d curves are presented in loop perspective)
            				AcGeInterval crvIntrvl;
            				((AcGeExternalCurve3d*)curveGeometry)->getInterval(crvIntrvl);
            				AcGeInterval pcrvIntrvl;
            				((AcGeExternalCurve2d*)pcurveGeometry)->getInterval(pcrvIntrvl);
							if (crvIntrvl != pcrvIntrvl) {
								if ((crvIntrvl.upperBound() == -pcrvIntrvl.lowerBound())
									&& (crvIntrvl.lowerBound() == -pcrvIntrvl.upperBound())) {
                					acutPrintf(ACRX_T("\n ******Edge No. %d: Curve and Pcurve Orientations Oppose\n"),
                						edgeCount);
								} else {
                					acutPrintf(ACRX_T("\n ******Edge No. %d: Curve and Pcurve Parameter Bounds Differ\n"),
                						edgeCount);
                					acutPrintf(ACRX_T(" *******Curve Parameterisation is ("));
									acutPrintf(ACRX_T("%lf, "), crvIntrvl.lowerBound());
									acutPrintf(ACRX_T("%lf "), crvIntrvl.upperBound());
									acutPrintf(ACRX_T(")\n"));
                					acutPrintf(ACRX_T(" *******Parameter Curve Parameterisation is ("));
									acutPrintf(ACRX_T("%lf, "), pcrvIntrvl.lowerBound());
									acutPrintf(ACRX_T("%lf "), pcrvIntrvl.upperBound());
									acutPrintf(ACRX_T(")\n"));
								}
							}
						}
						delete pcurveGeometry;
						delete curveGeometry;
						delete nativeGeometry;

						// Inform of any negated orientations, since the model space curve
						// is returned as is (no curve reversal for usage by surface boundary)
            			Adesk::Boolean edgeOriented, loopOriented;
            			returnValue = loopEdgeTrav.getEdgeOrientToLoop(loopOriented);
            			if (returnValue != AcBr::eOk) {
            				acutPrintf(ACRX_T("\n Error in AcBrLoopEdgeTraverser::getEdgeOrientToLoop:"));
							errorReport(returnValue);
            				return returnValue;
            			} 
            			returnValue = edgeEntity.getOrientToCurve(edgeOriented);
            			if (returnValue != AcBr::eOk) {
            				acutPrintf(ACRX_T("\n Error in AcBrEdge::getOrientToCurve:"));
							errorReport(returnValue);
            				return returnValue;
            			} 
            			if (!loopOriented ^ !edgeOriented) {
            				acutPrintf(ACRX_T("\n ******Edge No. %d: Curve Orientation in Loop is Negative\n"),
            					edgeCount);
            			}

						returnValue = loopEdgeTrav.next();
						if (returnValue != AcBr::eOk) {
							acutPrintf(ACRX_T("\n Error in AcBrLoopEdgeTraverser::next:"));
							errorReport(returnValue);
							return returnValue;
		    			}
					} // end edge while

					acutPrintf(ACRX_T("\n *****Loop No. %d has %d edges\n"), loopCount, edgeCount);	  

					int vtxCount = 0;
					AcBrLoopVertexTraverser loopVtxTrav;
	    			returnValue = loopVtxTrav.setLoop(faceLoopTrav);
					if (returnValue != AcBr::eOk) {	 
						acutPrintf(ACRX_T("\n Error in AcBrLoopVertexTraverser::setLoop:")); 
						errorReport(returnValue);
						return returnValue;
					} else while (!loopVtxTrav.done() && (returnValue == AcBr::eOk)) { 
						vtxCount++; 
						acutPrintf(ACRX_T("\n *****Vertex No: %d \n"), vtxCount);

						AcBrVertex loopPoint;
						returnValue = loopVtxTrav.getVertex(loopPoint);
						if (returnValue != AcBr::eOk) {
							acutPrintf(ACRX_T("\n Error in AcBrLoopVertexTraverser::getVertex:"));
							errorReport(returnValue);
							return returnValue;
						}
						acutPrintf(ACRX_T("\nCoordinate of loop vertex: "));
						returnValue = vertexDump(loopPoint);
						if (returnValue != AcBr::eOk) {
							acutPrintf(ACRX_T("\n Error in vertexDump:"));
							errorReport(returnValue);
							return returnValue;
						}
						
						returnValue = loopVtxTrav.next();
						if (returnValue != AcBr::eOk) {
							acutPrintf(ACRX_T("\n Error in AcBrLoopVertexTraverser::next:"));
							errorReport(returnValue);
							return returnValue;
		    			}
					} // end vertex while

					acutPrintf(ACRX_T("\n *****Loop No. %d has %d vertices\n"), loopCount, vtxCount);	  

					returnValue = faceLoopTrav.next();
	    			if (returnValue != AcBr::eOk) {
		    			acutPrintf(ACRX_T("\n Error in AcBrFaceLoopTraverser::next:"));
						errorReport(returnValue);
						return returnValue;
					}
    			} // end loop while

				acutPrintf(ACRX_T("\n ****Face No. %d has %d loops\n"), faceCount, loopCount);	  

				returnValue = shellFaceTrav.next();
				if (returnValue != AcBr::eOk) {
					acutPrintf(ACRX_T("\n Error in AcBrShellFaceTraverser::next:"));  
					errorReport(returnValue);
					return returnValue;
				}

			} // end face while

			acutPrintf(ACRX_T("\n ***Shell No. %d has %d faces\n"), shellCount, faceCount);	  

			returnValue = complexShellTrav.next();
			if (returnValue != AcBr::eOk) {
				acutPrintf(ACRX_T("\n Error in AcBrComplexShellTraverser::next:"));  
				errorReport(returnValue);
				return returnValue;
			}

		} // end shell while

		acutPrintf(ACRX_T("\n **Complex No. %d has %d shells\n"), complexCount, shellCount);	  

		returnValue = brepComplexTrav.next();
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in AcBrBrepComplexTraverser::next:"));  
			errorReport(returnValue);
			return returnValue;
		}

	} // end complex while

	acutPrintf(ACRX_T("\n *Brep has %d complexes\n"), complexCount);	  

	return returnValue;
}


static AcBr::ErrorStatus
brepDumpUp(const AcBrBrep& brepEntity)
{ 
    AcBr::ErrorStatus returnValue = AcBr::eOk;

	// make a global vertex traverser
	AcBrBrepVertexTraverser brepVtxTrav;
	returnValue = brepVtxTrav.setBrep(brepEntity);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrBrepVertexTraverser::setBrep:"));
		errorReport(returnValue);
		return returnValue;
	}

	// dump the context around the vertices
	int vtxCount = 0;
	while (!brepVtxTrav.done() && (returnValue == AcBr::eOk)) {
	    vtxCount++;
	    acutPrintf(ACRX_T("\n *Vertex No: %d \n"), vtxCount);

		AcBrVertex currentVertex;
		returnValue = brepVtxTrav.getVertex(currentVertex);
		if (returnValue != AcBr::eOk) {
		    acutPrintf(ACRX_T("\n Error in AcBrBrepVertexTraverser::getVertex:"));
			errorReport(returnValue);
			return returnValue;
		}

        int edgeCount = 0;
		AcBrVertexEdgeTraverser vtxEdgeTrav;
	    returnValue = vtxEdgeTrav.setVertex(currentVertex);
		if (returnValue != AcBr::eOk) {
			if (returnValue != AcBr::eDegenerateTopology) {	 
				acutPrintf(ACRX_T("\n Error in AcBrVertexEdgeTraverser::setVertex:")); 
				errorReport(returnValue);
				return returnValue;
			} else {
				// eDegenerateTopology means this vertex is a singularity (vertex-loop)
				AcBrVertexLoopTraverser vtxLoopTrav;
				returnValue = vtxLoopTrav.setVertex(currentVertex);
				if (returnValue != AcBr::eOk) {
					acutPrintf(ACRX_T("\n Error in AcBrVertexLoopTraverser::setVertex:"));
					errorReport(returnValue);
					return returnValue;
				} else {
					AcBrLoop vtxLoop;
					returnValue = vtxLoopTrav.getLoop(vtxLoop);
				    if (returnValue != AcBr::eOk) {
						acutPrintf(ACRX_T("\n Error in AcBrVertexLoopTraverser::getLoop:"));
						errorReport(returnValue);
						return returnValue;
					}
            	    acutPrintf(ACRX_T("\n **Vertex No. %d is a vertex loop\n"), vtxCount);	  
				} // end vertex loop
			}
		} else while (!vtxEdgeTrav.done() && (returnValue == AcBr::eOk)) { 
            edgeCount++; 
		    acutPrintf(ACRX_T("\n **Edge No: %d \n"), edgeCount);

			AcBrEdge edgeEntity;
			returnValue = vtxEdgeTrav.getEdge(edgeEntity);
			if (returnValue != AcBr::eOk) {
				acutPrintf(ACRX_T("\n Error in AcBrVertexEdgeTraverser::getEdge:"));
				errorReport(returnValue);
				return returnValue;
			}

			AcBrEdgeLoopTraverser edgeLoopTrav;
		    returnValue = edgeLoopTrav.setEdge(vtxEdgeTrav);
		    if (returnValue != AcBr::eOk) {
				acutPrintf(ACRX_T("\n Error in AcBrEdgeLoopTraverser::setEdge:"));
			    errorReport(returnValue);
				return returnValue;
			}

            // count the radial faces around an edge
		    int adjacentFaces = 0;
			while (!edgeLoopTrav.done() && (returnValue == AcBr::eOk)) {
			    adjacentFaces++;
			    returnValue  = edgeLoopTrav.next();
    			if (returnValue != AcBr::eOk) {
    				acutPrintf(ACRX_T("\n Error in AcBrEdgeLoopTraverser::next:"));
    				errorReport(returnValue);
    				return returnValue;
                }
			} // end radial face while	 

		    acutPrintf(ACRX_T("\n ***Edge No. %d has %d adjacent faces\n"),
		        edgeCount, adjacentFaces);

			returnValue = vtxEdgeTrav.next();
			if (returnValue != AcBr::eOk) {
				acutPrintf(ACRX_T("\n Error in AcBrVertexEdgeTraverser::next:"));
				errorReport(returnValue);
				return returnValue;
		    }
		} // end edge while

	    acutPrintf(ACRX_T("\n **Vertex No. %d has %d edges\n"), vtxCount, edgeCount);	  

        // count the radial faces around a vertex
		int adjacentFaces = 0;
		AcBrVertexLoopTraverser vtxLoopTrav;
	    returnValue = vtxLoopTrav.setVertex(currentVertex);
		if (returnValue != AcBr::eOk) {
			if (returnValue != AcBr::eDegenerateTopology) {	 
				acutPrintf(ACRX_T("\n Error in AcBrVertexLoopTraverser::setVertex:")); 
				errorReport(returnValue);
				return returnValue;
			}
		} else while (!vtxLoopTrav.done() && (returnValue == AcBr::eOk)) { 
            adjacentFaces++; 
			returnValue = vtxLoopTrav.next();
			if (returnValue != AcBr::eOk) {
				acutPrintf(ACRX_T("\n Error in AcBrVertexLoopTraverser::next:"));
				errorReport(returnValue);
				return returnValue;
		    }
		} // end radial face while

	    acutPrintf(ACRX_T("\n **Vertex No. %d has %d adjacent faces\n"), vtxCount, adjacentFaces);	  

		returnValue = brepVtxTrav.next();
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in AcBrBrepVertexTraverser::next:"));  
			errorReport(returnValue);
			return returnValue;
		}
	}  // end vertex while

	acutPrintf(ACRX_T("\n *Brep has %d vertices\n"), vtxCount);	  

	return returnValue;
}

