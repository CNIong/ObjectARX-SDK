//
// (C) Copyright 1998-2002 by Autodesk, Inc. 
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

//Implements AcCircle
# include "AcCircle.h"
# include "GripImp.h"


ACRX_DXF_DEFINE_MEMBERS(AcCircle,AcDbEntity,AcDb::kDHL_CURRENT,
						AcDb::kMReleaseCurrent,AcDbProxyEntity::kNoOperation, 
						ASDKACCIRCLE,ASDKACCIRCLE);

//Static variable declaration
appDataType AcCircle::msAppData;
bool		AcCircle::mbHover;
AcDbObjectId AcCircle::mentId;

AcCircle::AcCircle()
:mRadius(0)
{}

appDataType::iterator 
AcCircle::putAppData()
{
	if(msAppData.empty())
	{
		msAppData.reserve(GripCount);
		std::string sAppData[GripCount]=
		{
			"Center","First","Second",
			"Third","Fourth"
		};

		for(int i=0;i<GripCount;i++)
		{
			msAppData.push_back(sAppData[i]);
		}
	}
	return msAppData.begin();
	
}

AcCircle::AcCircle(AcGePoint3d &pt,AcGeVector3d &curView,
								   double radius)
									:mCenter(pt),
									 mNormal(curView)
{
	mRadius=radius;
}

AcCircle::~AcCircle()
{}


Acad::ErrorStatus 
AcCircle::dwgInFields(AcDbDwgFiler *pFiler)
{
	assertWriteEnabled();
	Acad::ErrorStatus es;

	
	if( (es = AcDbEntity::dwgInFields(pFiler)) != Acad::eOk)
		return es;

	pFiler->readItem(&mNormal);
	pFiler->readItem(&mCenter);
	pFiler->readItem(&mRadius);

	return pFiler->filerStatus();
}


Acad::ErrorStatus 
AcCircle::dwgOutFields(AcDbDwgFiler *pFiler) const
{
	assertReadEnabled();
	Acad::ErrorStatus es;
	
	if( (es = AcDbEntity::dwgOutFields(pFiler)) != Acad::eOk)
		return es;

	pFiler->writeItem(mNormal);
	pFiler->writeItem(mCenter);
	pFiler->writeItem(mRadius);

	return pFiler->filerStatus();
}
 
Acad::ErrorStatus 
AcCircle::dxfInFields (AcDbDxfFiler *pFiler)
{
	assertWriteEnabled();

	if ((AcDbEntity::dxfInFields(pFiler) != Acad::eOk) ||
	    !pFiler->atSubclassData("AcCircle"))
		return pFiler->filerStatus();

	return pFiler->filerStatus();
}

Acad::ErrorStatus 
AcCircle::dxfOutFields(AcDbDxfFiler *pFiler) const
{
	assertReadEnabled();
	Acad::ErrorStatus es;

	if ((es = AcDbEntity::dxfOutFields(pFiler)) != Acad::eOk)
		return es;

	return pFiler->filerStatus();
}

Acad::ErrorStatus 
AcCircle::getGripPoints(AcGePoint3dArray&,AcDbIntArray&,
							  			    AcDbIntArray&) const
{
	return Acad::eOk;
}

Acad::ErrorStatus 
AcCircle::moveGripPointsAt(const AcDbIntArray&,
						   const AcGeVector3d&)
{
	return Acad::eOk;
}

Acad::ErrorStatus  
AcCircle::getGripPoints(AcDbGripDataPtrArray& grips,
					   const double			 viewSize,
					   const int			 gripSize,
					   const AcGeVector3d&   curViewDir, 
  					   const int			 bitflags) const
{
	assertReadEnabled();

	double xCord1(0),xCord2(0),xCord3(0),xCord4(0);
	double yCord1(0),yCord2(0),yCord3(0),yCord4(0);
	
	appDataType::iterator appIter = putAppData();

	//All the GripData pointer are deallocated automatically
	AcDbGripData *pCenterCoordGrip = new AcDbGripData();
	pCenterCoordGrip = new AcDbGripData();
	pCenterCoordGrip->setGripPoint(mCenter);
	pCenterCoordGrip->setAppData((void*)&(*appIter));
	pCenterCoordGrip->setToolTipFunc(GripCback::GripToolTipFunc);
	pCenterCoordGrip->setHotGripFunc(GripCback::hotGripfunc);
	pCenterCoordGrip->setHoverFunc(GripCback::hoverGripfunc);
	pCenterCoordGrip->setGripOpStatFunc(GripCback::OpStatusfunc);
	pCenterCoordGrip->setWorldDraw(GripCback::WorldDrawfunc);
	pCenterCoordGrip->setRtClk(GripCback::Rtclkfunc);
	pCenterCoordGrip->setGripOpStatFunc(GripCback::OpStatusfunc);
	 grips.append(pCenterCoordGrip);	
	 appIter+=1;
	

	AcDbGripData *pFirstCoordGrip   = new AcDbGripData();
	//Computing the x and the y coordinate for the first grip 
	//point 
	xCord1 = (cos(45*PI/180) * mRadius + mCenter[0]);
	yCord1 = (sin(45*PI/180) * mRadius + mCenter[1]);
	
	pFirstCoordGrip->setGripPoint(AcGePoint3d(xCord1,yCord1,0));
	pFirstCoordGrip->setAppData((void*)&(*appIter));
	pFirstCoordGrip->setToolTipFunc(GripCback::GripToolTipFunc);
	pFirstCoordGrip->setHotGripFunc(GripCback::hotGripfunc);
	pFirstCoordGrip->setHoverFunc(GripCback::hoverGripfunc);
	//pFirstCoordGrip->setGripOpStatFunc(GripCback::OpStatusfunc);
	//pFirstCoordGrip->setWorldDraw(GripCback::WorldDrawfunc);
	//pFirstCoordGrip->setRtClk(GripCback::Rtclkfunc);
	//pCenterCoordGrip->setGripOpStatFunc(GripCback::grigripOpStatusCbackfunc);
	grips.append(pFirstCoordGrip);	
	appIter+=1;

	AcDbGripData *pSecondCoordGrip  = new AcDbGripData();
	xCord2 = (cos(135*PI/180) * mRadius + mCenter[0]);
	yCord2 = (sin(135*PI/180) * mRadius + mCenter[1]);

	pSecondCoordGrip->setGripPoint(AcGePoint3d(xCord2,yCord2,0));
	pSecondCoordGrip->setAppData((void*)&(*appIter));
	pSecondCoordGrip->setToolTipFunc(GripCback::GripToolTipFunc);
	pSecondCoordGrip->setHotGripFunc(GripCback::hotGripfunc);
	pSecondCoordGrip->setHoverFunc(GripCback::hoverGripfunc);
	//pSecondCoordGrip->setGripOpStatFunc(GripCback::OpStatusfunc);
	//pSecondCoordGrip->setWorldDraw(GripCback::WorldDrawfunc);
	//pSecondCoordGrip->setRtClk(GripCback::Rtclkfunc);
	//pCenterCoordGrip->setGripOpStatFunc(GripCback::grigripOpStatusCbackfunc);
	grips.append(pSecondCoordGrip);	
	appIter+=1;

	AcDbGripData *pThirdCoordGrip   = new AcDbGripData();
	
	xCord3 = (cos(225*PI/180) * mRadius + mCenter[0]);
	yCord3 = (sin(225*PI/180) * mRadius + mCenter[1]);

	pThirdCoordGrip->setGripPoint(AcGePoint3d(xCord3,yCord3,0));
	pThirdCoordGrip->setAppData((void*)&(*appIter));
	pThirdCoordGrip->setToolTipFunc(GripCback::GripToolTipFunc);
	pThirdCoordGrip->setHotGripFunc(GripCback::hotGripfunc);
	pThirdCoordGrip->setHoverFunc(GripCback::hoverGripfunc);
	//pThirdCoordGrip->setGripOpStatFunc(GripCback::OpStatusfunc);
	//pThirdCoordGrip->setWorldDraw(GripCback::WorldDrawfunc);
	//pThirdCoordGrip->setRtClk(GripCback::Rtclkfunc);
	//pThirdCoordGrip->setGripOpStatFunc(GripCback::grigripOpStatusCbackfunc);
	grips.append(pThirdCoordGrip);	
	appIter+=1;

	
	AcDbGripData *pFourthCoordGrip  = new AcDbGripData();

	xCord4 = (cos(315*PI/180) * mRadius + mCenter[0]);
	yCord4 = (sin(315*PI/180) * mRadius + mCenter[1]);

	pFourthCoordGrip->setGripPoint(AcGePoint3d(xCord4,yCord4,0));
	pFourthCoordGrip->setAppData((void*)&(*appIter));
	pFourthCoordGrip->setToolTipFunc(GripCback::GripToolTipFunc);
	pFourthCoordGrip->setHotGripFunc(GripCback::hotGripfunc);
	//pFourthCoordGrip->setHoverFunc(GripCback::hoverGripfunc);
	//pFourthCoordGrip->setGripOpStatFunc(GripCback::OpStatusfunc);
//	pFourthCoordGrip->setWorldDraw(GripCback::WorldDrawfunc);
	//pFourthCoordGrip->setRtClk(GripCback::Rtclkfunc);
	//pFourthCoordGrip->setGripOpStatFunc(GripCback::grigripOpStatusCbackfunc);
	grips.append(pFourthCoordGrip);	
	appIter+=1;
	return Acad::eOk;
}

Acad::ErrorStatus  
AcCircle::moveGripPointsAt(const AcDbVoidPtrArray& gripAppData,
						   const AcGeVector3d& offset,
						   const int bitflags)
{
	assertWriteEnabled();
	std::string *pString = static_cast<std::string *>(gripAppData[0]);	
	if( (*pString == "First") || (*pString == "Second")|| (*pString == "Third") ||
		(*pString == "Fourth")|| (*pString == "Center")
	 )
	mCenter += offset;

	return Acad::eOk;
	
}

Adesk::Boolean 
AcCircle::worldDraw(AcGiWorldDraw* pWd)
{
	if(pWd){
	pWd->subEntityTraits().setColor(Colors::kYellow);
	pWd->geometry().circle(mCenter,mRadius,mNormal);
	}
	return Adesk::kTrue;
}

void 
AcCircle::dragStatus(const AcDb::DragStat status)
{
}

void 
AcCircle::gripStatus(const AcDb::GripStat status)
{
	if(AcDb::kGripsToBeDeleted ){
	}
		
}

/////Dynamic DImneison Callback functions

void
AcCircle::hotGripDimensionfunc(	    AcDbGripData			   *pThis,
									const AcDbObjectId		   &entId,
									double					    dimScale,
									AcDbDimDataPtrArray		   &dimData)
{
	setHover(false);
	gripDimensionCbackfn(pThis,entId,dimScale,dimData);
}

void
AcCircle::hoverGripDimensionfunc(	AcDbGripData				*pGrip,
									const AcDbObjectId			&objId,
									double 						dimScale,
									AcDbDimDataPtrArray			&dimDataArr)
{

	setHover(true);
	gripDimensionCbackfn(pGrip,objId,dimScale,dimDataArr);
}

void
AcCircle::gripDimensionCbackfn(				AcDbGripData* pThis,
											const AcDbObjectId& entId,
											double dimScale,
											AcDbDimDataPtrArray& dimData)
{
		std::string *pszAppData  = static_cast<std::string *>(pThis->appData());

		
		AcDbEntity *pEnt = NULL;
		Acad::ErrorStatus es(Acad::eNotImplementedYet);

		if( Acad::eOk != acdbOpenAcDbEntity(pEnt,entId,AcDb::kForRead) ){
			acutPrintf("\n Error in returning valid pointer to an Entity");
			return;
		}
		
		AcCircle   *pCircle = static_cast<AcCircle *>(pEnt);
		mentId = entId;
		
		AcGeVector3d mNormal = pCircle->normal();

		AcGeVector3d NormalDir    = pCircle->normal();
		
		AcGeVector3d horizDir =		mNormal.perpVector();
		AcGeVector3d vertDir =		mNormal.crossProduct(horizDir);
		
		AcGePoint3d  center	  = pCircle->Center();
		double		 radius	      = pCircle->radius();
        int          dimIndex1(0);




		AcGePoint3d points[5] =
		{
			center,
			center + radius * horizDir,
			center + radius * vertDir,
			center - radius * horizDir,
			center - radius * vertDir
		};

		AcGePoint3d dimPt1,dimPt2;


	    AcDb2LineAngularDimension *pDim1 = new  AcDb2LineAngularDimension ();
		pDim1->setDatabaseDefaults();

		pDim1->setNormal(NormalDir);


		if( *pszAppData == "First")
		{
		      dimIndex1 =1;
		      dimPt1 = center + (1.5 * radius + 0.5 * dimScale) * horizDir;

		      pDim1->setXLine1Start(points[0]);
	      	  pDim1->setXLine1End(points[1]);
		      pDim1->setXLine2Start(points[0]);
		      pDim1->setXLine2End(points[2]);
		      pDim1->setArcPoint(dimPt1);
		}
		else if( *pszAppData == "Second")
		{
            dimIndex1=2;
			dimPt1 =  center + (1.5* radius + 0.5 * dimScale) * vertDir;
			pDim1->setXLine1Start(points[0]);
			pDim1->setXLine1End(points[2]);

			pDim1->setXLine2Start(center);
			pDim1->setXLine2End(points[3]);
			pDim1->setArcPoint(dimPt1);

		}
		else if(*pszAppData == "Third")
		{
			dimIndex1=3;
			dimPt1 =  center -  (1.5*radius + 0.5 * dimScale) * horizDir;
			pDim1->setXLine1Start(points[0]);
			pDim1->setXLine1End(points[3]);

			pDim1->setXLine2Start(points[0]);
			pDim1->setXLine2End(points[4]);
			pDim1->setArcPoint(dimPt1);
		}
		else if( *pszAppData == "Fourth")

		{
			dimIndex1=4;
			dimPt1 =  center - (1.5 * radius + 0.5 * dimScale) * vertDir;
			pDim1->setXLine1Start(points[0]);
			pDim1->setXLine1End(points[4]);

			pDim1->setXLine2Start(points[0]);
			pDim1->setXLine2End(points[1]);
			pDim1->setArcPoint(dimPt1);
		}

		unsigned int bitFlags(0);
		unsigned int bitRetFlags(0);
		AcDbDimData *pdimData1=NULL;
		pdimData1 = new AcDbDimData();
		es =pdimData1->setDimension(pDim1);
		bitFlags = AcDbDimData::kDimEditable;			
		es =pdimData1->setBitFlags(bitFlags);
		
		es =pdimData1->setAppData(&dimIndex1);
		es =pdimData1->setOwnerId(mentId);
		dimData.append(pdimData1);
		pCircle->close();
}


 AcGeVector3d
 AcCircle::setDimValueCbackFunc(AcDbDimData* pThis,
                                AcDbEntity* pEnt,
                                 double newValue,
                                 const AcGeVector3d& offset)
{
	AcGeVector3d newOffset(offset);

	   if ((pThis == NULL) || (pEnt == NULL))
        return newOffset;

	AcDbObjectId objId;

	AcCircle *pCir = AcCircle::cast(pEnt);
   	 if (pCir == NULL)
        	return newOffset;
    int nAppData = *(static_cast<int *>(pThis->appData()));
	
	 AcDbDimension *pDimension = pThis->dimension();
	 AcDb2LineAngularDimension  *pAngDim = AcDb2LineAngularDimension::cast(pDimension);
	 const char *pszClassName = pAngDim->isA()->name();

	 switch(nAppData)
	 {
	 	case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
	 	case 7:
		case 8:
		    pCir->setRadius(newValue);
		    break;
		default:
			break;
	 };
	return newOffset;
}

