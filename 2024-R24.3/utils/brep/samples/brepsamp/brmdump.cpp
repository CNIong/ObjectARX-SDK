//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Mesh dump utilities.

#include "brsample_pch.h"  //precompiled header


// include here



AcBr::ErrorStatus
meshDump(const AcBrMesh2d& mesh)
{ 
    AcBr::ErrorStatus returnValue = AcBr::eOk;

	// make a global element traverser
	AcBrMesh2dElement2dTraverser meshElemTrav;
	returnValue = meshElemTrav.setMesh(mesh);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrMesh2dElement2dTraverser::setMesh:"));
		errorReport(returnValue);
		return returnValue;
	}

	// count the elements
	int elemCount = 0;
	while (!meshElemTrav.done() && (returnValue == AcBr::eOk) && !acedUsrBrk()) {
	    elemCount++;
	    acutPrintf(ACRX_T("\n ***Element No: %d \n"), elemCount);

		AcBrElement2d currentElem;
		returnValue = meshElemTrav.getElement(currentElem);
		if (returnValue != AcBr::eOk) {
		    acutPrintf(ACRX_T("\n Error in AcBrMesh2dElement2dTraverser::getElement:"));
			errorReport(returnValue);
			return returnValue;
		}

		AcGeVector3d normal;
		returnValue = currentElem.getNormal(normal);
		if (returnValue != AcBr::eOk) {	
			acutPrintf(ACRX_T("\n Error in AcBrElement2d::getNormal:")); 
			errorReport(returnValue);
			return returnValue;
		}
        acutPrintf(ACRX_T("\n Element Normal is ("));
        acutPrintf (ACRX_T("%lf, "), normal.x);	
        acutPrintf (ACRX_T("%lf, "), normal.y);
        acutPrintf (ACRX_T("%lf"), normal.z);
        acutPrintf(ACRX_T(")\n"));	

    	// Determine the entity which contains this element
    	AcBrEntity* entityAssociated = NULL;
    	returnValue = currentElem.getEntityAssociated(entityAssociated);
    	if (returnValue != AcBr::eOk) {
    		acutPrintf(ACRX_T("\n Error in AcBrElement2d::getEntityAssociated:"));
    		errorReport(returnValue);
    		delete entityAssociated;
    		return returnValue;
    	}
    	entityAssociatedReport(entityAssociated);
    	delete entityAssociated;

    	// count the nodes
		int nodeCount = 0;
		AcBrElement2dNodeTraverser elemNodeTrav;
		returnValue = elemNodeTrav.setElement(meshElemTrav);
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in AcBrElement2dNodeTraverser::setElement:")); 
			errorReport(returnValue);
			return returnValue;
		} 
		
		while (!elemNodeTrav.done() && (returnValue == AcBr::eOk)) { 
		    nodeCount++;

			AcBrNode node;
			returnValue = elemNodeTrav.getNode(node);
		     if (returnValue != AcBr::eOk) {	
			    acutPrintf(ACRX_T("\n Error in AcBrElement2dNodeTraverser::getNode:")); 
			    errorReport(returnValue);
			    return returnValue;
		    }

			// dump the node geometry data
			returnValue = nodeDump(node);
	    	if (returnValue != AcBr::eOk) {
				acutPrintf(ACRX_T("\n Error in nodeDump:"));
			    errorReport(returnValue);
			    return returnValue;
		    }

			// dump the node surface data
			AcGePoint2d point;
			returnValue = elemNodeTrav.getParamPoint(point);
		    if (returnValue != AcBr::eOk) {	
			    acutPrintf(ACRX_T("\n Error in AcBrElement2dNodeTraverser::getParamPoint:")); 
			    errorReport(returnValue);
			    return returnValue;
		    }
        	acutPrintf(ACRX_T("\n Node Param Point is ("));
        	acutPrintf (ACRX_T("%lf, "), point.x);	
        	acutPrintf (ACRX_T("%lf, "), point.y);
        	acutPrintf(ACRX_T(")\n"));

			AcGeVector3d normal;
			returnValue = elemNodeTrav.getSurfaceNormal(normal);
		    if (returnValue != AcBr::eOk) {	
			    acutPrintf(ACRX_T("\n Error in AcBrElement2dNodeTraverser::getSurfaceNormal:")); 
			    errorReport(returnValue);
			    return returnValue;
		    }
        	acutPrintf(ACRX_T("\n Node Surface Normal is ("));
        	acutPrintf (ACRX_T("%lf, "), normal.x);	
        	acutPrintf (ACRX_T("%lf, "), normal.y);
        	acutPrintf (ACRX_T("%lf"), normal.z);
        	acutPrintf(ACRX_T(")\n"));	

			returnValue = elemNodeTrav.next();
	    	if (returnValue != AcBr::eOk) {
		    	acutPrintf(ACRX_T("\n Error in AcBrElement2dNodeTraverser::next:"));
			    errorReport(returnValue);
			    return returnValue;
		    }
		} // end element while

	    acutPrintf(ACRX_T("\n ****Element No. %d has %d nodes\n"), elemCount, nodeCount);	  

		returnValue = meshElemTrav.next();
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in AcBrMesh2dElement2dTraverser::next:"));  
			errorReport(returnValue);
			return returnValue;
		}

	}  // end mesh while

	acutPrintf(ACRX_T("\n ***Mesh has %d elements\n"), elemCount);	  

	return returnValue;
}


AcBr::ErrorStatus
meshDisplay(const AcBrMesh2d& mesh)
{ 
    AcBr::ErrorStatus returnValue = AcBr::eOk;

	// make a global element traverser
	AcBrMesh2dElement2dTraverser meshElemTrav;
	returnValue = meshElemTrav.setMesh(mesh);
	if (returnValue != AcBr::eOk) {
		acutPrintf(ACRX_T("\n Error in AcBrMesh2dElement2dTraverser::setMesh:"));
		errorReport(returnValue);
		return returnValue;
	}

	// display the elements
	while (!meshElemTrav.done() && (returnValue == AcBr::eOk) && !acedUsrBrk()) {
    	// convert the nodes into a 3d point array for AcDbPolyline
        AcGePoint3dArray pts;

		AcBrElement2dNodeTraverser elemNodeTrav;
		returnValue = elemNodeTrav.setElement(meshElemTrav);
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in AcBrElement2dNodeTraverser::setElement:")); 
			errorReport(returnValue);
			return returnValue;
		} 
		
		while (!elemNodeTrav.done() && (returnValue == AcBr::eOk)) { 
			AcBrNode node;
			returnValue = elemNodeTrav.getNode(node);
		     if (returnValue != AcBr::eOk) {	
			    acutPrintf(ACRX_T("\n Error in AcBrElement2dNodeTraverser::getNode:")); 
			    errorReport(returnValue);
			    return returnValue;
		    }

			// add the node geometry data to the lightweight polyline point array
			returnValue = nodeDisplay(node, pts);
	    	if (returnValue != AcBr::eOk) {
				acutPrintf(ACRX_T("\n Error in nodeDisplay:"));
			    errorReport(returnValue);
			    return returnValue;
		    }

			returnValue = elemNodeTrav.next();
	    	if (returnValue != AcBr::eOk) {
		    	acutPrintf(ACRX_T("\n Error in AcBrElement2dNodeTraverser::next:"));
			    errorReport(returnValue);
			    return returnValue;
		    }
		} // end element while

        // create a simple, closed polygon from the element node list
        AcDb3dPolyline* pline = new AcDb3dPolyline(AcDb::k3dSimplePoly, pts, Adesk::kTrue);
        if (pline == NULL) {
            returnValue = (AcBr::ErrorStatus)Acad::eOutOfMemory;
            acutPrintf(ACRX_T("\n Unable to allocate memory for polyline"));
            return returnValue;
		}

		// post the polyline to the database (this should display the element)
        AcDbObjectId objId;
        if (addToDatabase(pline, objId) != AcBr::eOk) {
            acutPrintf(ACRX_T("\n addToDatabase failed"));
            return returnValue;
        }

        // close the database object
        if (pline->close() != AcBr::eOk) {
            acutPrintf(ACRX_T("\n AcDb3dPolyline::close() failed"));
            return returnValue;
        }

		returnValue = meshElemTrav.next();
		if (returnValue != AcBr::eOk) {
			acutPrintf(ACRX_T("\n Error in AcBrMesh2dElement2dTraverser::next:"));  
			errorReport(returnValue);
			return returnValue;
		}

	}  // end mesh while

    return returnValue;
}
