//
//
// (C) Copyright 1990-2003 by Autodesk, Inc. 
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
#include "subselfilter.h"
bool pointInsideRect(AcGePoint3d point, AcDbEntity* pEnt);

CSubSelFilter::CSubSelFilter(void)
{
	

}

CSubSelFilter::~CSubSelFilter(void)
{
}
	
 Acad::ErrorStatus CSubSelFilter::subSelectClassList(AcArray<AcRxClass*>& clsIds)
 { 
		clsIds.append(AsdkRings::desc()); 
		clsIds.append(AcDbCircle::desc()); 
		clsIds.append(AcDbEllipse::desc()); 
		clsIds.append(AcDbPolyline::desc()); 

		return Acad::eOk; 
}

    bool CSubSelFilter::selectEntity(const AcGePoint3d&  wvpt, 
            const AcGeVector3d& wvwdir, const AcGeVector3d& wvwxdir,           
            double wxaper, double wyaper,           
            const AcGiViewport* pCurVp, AcDbEntity*  pEnt ) const  
    {  
		     bool retVal = false;
			 AsdkRings *pRings = NULL;
			if (pEnt == NULL)return false;
			
			AcGeEllipArc3d *pGeEArc = new AcGeEllipArc3d();
			AcGeCircArc3d *pGeCArc  = new AcGeCircArc3d();

			if (pEnt->isKindOf(AsdkRings::desc()))
			{
		      pRings = (AsdkRings*) pEnt;

			     //Do a hit test to see if point is in entity
			       retVal = pRings ->hitTest(wvpt,wvwdir);
			}
			else if (pEnt->isKindOf(AcDbCircle::desc()))
			{
				double radius;

				 AcGePoint3d center;
                 AcDbCircle *pCircl = (AcDbCircle *)pEnt;
				 center = pCircl -> center();
				 radius = pCircl -> radius();
 
	             AcGePlane pln;
	             pln.set(center,AcGeVector3d(0,0,1));
	             AcGePoint3d projPt = wvpt.project(pln,wvwdir); //Projection of clicked point on the XY plane

				 pGeCArc->setCenter(center);
				 pGeCArc->setRadius(radius);

				 if (pGeCArc->isInside(projPt) == Adesk::kTrue)	retVal = true;
				 
			    
			}
			else if (pEnt->isKindOf(AcDbEllipse::desc()))
			{	
				
				 double majorRadius,minorRadius;
				 AcGePoint3d center;
				 AcGeVector3d majorAxis, minorAxis;

                 AcDbEllipse *pEllipse = (AcDbEllipse *)pEnt;
				 center = pEllipse -> center();
				 minorAxis = pEllipse -> minorAxis();
                 majorAxis = pEllipse ->  majorAxis();
				 minorRadius = minorAxis.length();
				 majorRadius = majorAxis.length();

	             AcGePlane pln;
	             pln.set(center,AcGeVector3d(0,0,1));

	             AcGePoint3d projPt = wvpt.project(pln,wvwdir); //Projection of clicked point on the XY plane
		
				 pGeEArc->setCenter(center);
				 pGeEArc->setAxes(majorAxis,minorAxis);
				 pGeEArc->setMajorRadius(majorRadius);
				 pGeEArc->setMinorRadius(minorRadius);
				 if (pGeEArc->isInside(projPt) == Adesk::kTrue)retVal = true;	
				
			}
			else if (pointInsideRect(wvpt, pEnt))
			{
				retVal = true;
			}
			    if(pGeEArc != NULL)delete pGeEArc;
                if(pGeCArc != NULL)delete pGeCArc;
				return retVal;
	}

	  //SUBSELECTION OF ENTITY HERE
	     AcEdSubSelectFilter::SubSelectStatus CSubSelFilter::subSelectEntity(
            const AcGePoint3d&  wpt1,
            const AcGePoint3d&  wpt2,
            const AcGeVector3d& wvwdir,
            const AcGeVector3d& wvwxdir,
			double wxaper,
			double wyaper,                             
			AcDb::SelectType    seltype,
			bool                bAugment,
			bool                bIsInPickfirstSet,
			const AcGiViewport* pCurVP,
            AcDbEntity*         pEnt,
            AcSubentPathArray&  paths)
    { 

		 AcGeMatrix3d viewXform;
		 int numPaths;
		 AcDbFullSubentPath* subentPaths;
		 if (pEnt == NULL)return AcEdSubSelectFilter::kSubSelectionNone;

	  if(pEnt->isKindOf(AsdkRings::desc()))
	  {
        AsdkRings *pRings  = (AsdkRings *) pEnt;
		
		//if a new entity is being selected, augment the selection set
		if (!mSelectedEnts.contains(pEnt->objectId())){
			mSelectedEnts.append(pEnt->objectId());
			return AcEdSubSelectFilter::kSubSelectionAugment;
		}

       int marker = 0;

	   pRings ->setSubSelection(wpt1,wvwdir, marker);
	   if (marker == 0)return AcEdSubSelectFilter::kSubSelectionNone;


		pRings->getSubentPathsAtGsMarker(AcDb::kEdgeSubentType,marker,wpt1,viewXform,numPaths,subentPaths,0,NULL);
		paths.append(subentPaths[0]);

        //Remove other entities and subselect this only
		return AcEdSubSelectFilter::kSubSelectionExclusive;
	 }
	  //For ellipse, circle and rectangle, no subselection
	 if (pEnt->isKindOf(AcDbEllipse::desc()) || pEnt->isKindOf(AcDbCircle::desc()) || pointInsideRect(wpt1,pEnt))
		 return AcEdSubSelectFilter::kSubSelectAll;	
	 else
	 return AcEdSubSelectFilter::kSubSelectionNone;

	}

bool
CSubSelFilter::cancelSubSelect(AcDbEntity* pEnt)
{ 
	
	if (pEnt->isKindOf(AsdkRings::desc()))
	{
		AsdkRings* pRings = (AsdkRings*) pEnt;
		pRings ->setSubSelState(0);
	}
     return mSelectedEnts.remove(pEnt->objectId());
	 
}
bool CSubSelFilter::reSubSelectEntity(AcDbEntity* pEnt, AcSubentPathArray& paths)
{
	/*
	AsdkRings *pRings = NULL;
	if (pEnt == NULL)return false;
	if (pEnt->isKindOf(AsdkRings::desc()))
	{
		pRings = (AsdkRings*) pEnt;

	   //if the current selection state is full selection, do nothing
		if (pRings ->getSubSelState()== 0)
			return false;
	}
*/
	return true;//
}

bool CSubSelFilter::cancelAllSubSelect()
{
    int nElts = mSelectedEnts.length();
	
	AcDbEntity *pEnt;
     AsdkRings *pRings = NULL;
    for (int i=0; i<nElts; i++)
	{
       acdbOpenAcDbEntity(pEnt,mSelectedEnts[i],AcDb::kForRead);
	    if (pEnt->isKindOf(AsdkRings::desc()))
	    {
		  pRings = (AsdkRings*) pEnt;
		  pRings ->setSubSelState(0);
		}
		pEnt->close();
	}
    mSelectedEnts.setLogicalLength(0);

   // selstatus = true;
	return true;
	
}


//helper function to check if a point is inside a polyline rectangle entity
bool pointInsideRect(AcGePoint3d pt, AcDbEntity* pEnt)
{
     AcGePoint3d pt1,pt2,pt3,pt4;
	AcGeVector3d side1, side2, side3, side4;
	double minX, minY,maxX,maxY, tol=0.0000001;

	//First check if entity is a polyline
	if (pEnt ->isKindOf(AcDbPolyline::desc()))
	{
		AcDbPolyline *pPoly = (AcDbPolyline *)pEnt;
		if (pPoly -> isClosed() != Adesk::kTrue || pPoly ->numVerts() != 4)return false;
		pPoly -> getPointAt(0,pt1);	
		pPoly -> getPointAt(1,pt2);
		pPoly -> getPointAt(2,pt3);
		pPoly -> getPointAt(3,pt4);


        AcGeVector3d vec1(pt1[0], pt1[1], pt1[2]);
		AcGeVector3d vec2(pt2[0], pt2[1], pt2[2]);
		AcGeVector3d vec3(pt3[0], pt3[1], pt3[2]);
		AcGeVector3d vec4(pt4[0], pt4[1], pt4[2]);

		AcGePoint3dArray pts;
        pts.append(pt1);pts.append(pt2);pts.append(pt3);pts.append(pt4);

		side1.setToSum(vec2,vec1.negate());
		side2.setToSum(vec3,vec2.negate());
		side3.setToSum(vec4,vec3.negate());
		vec1.set(pt1[0], pt1[1], pt1[2]);//reset vec1
		side4.setToSum(vec1,vec4.negate());
       
		if (side1.isPerpendicularTo(side2) == Adesk::kFalse || side3.isPerpendicularTo(side4) == Adesk::kFalse)
			return false;
  
		//Point inside rectangle
		minX  =  minY = 1.0E+300; maxX = maxY = -1.0E+300;
		for (int i = 0; i<4; i++)
		{
          if ((pts[i][0] - maxX) > tol)maxX = pts[i][0];
		  if ((pts[i][1] - maxY) > tol)maxY = pts[i][1];
		  if ((pts[i][0] - minX) < tol)minX = pts[i][0];
		  if ((pts[i][1] - minY) < tol)minY = pts[i][1];
		}
		// Now check if point (pt) is inside rectangle
		if ((pt[0] - minX) >= tol && (pt[0] - maxX) <= tol && (pt[1] - minY) >= tol && (pt[1] - maxY) <= tol)return true;

	 }

	return false;
}




