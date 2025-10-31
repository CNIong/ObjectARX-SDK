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

//Implements Grip Enhancement and Dynamic Dimensioning call back methods
# include "AcCircleJig.h"
# include "dbxutil.h" 

AcCircleJig::AcCircleJig(AcDbDatabase *pDb,
						 AcCircle *pCircle):
mpCircle(pCircle),
mpdb(pDb)
{
	
    mElevation = 0.0;
    mNormal.set(0,0,1);
 	mpDimDataArray = new AcDbDimDataPtrArray;
	mpDimDataArray->setLogicalLength(0);

}

AcCircleJig::~AcCircleJig()
{
    if (mpDimDataArray) 
	{
        for (int i = 0; i < mpDimDataArray->length(); i++) 
		{
            AcDbDimData *pData = (*mpDimDataArray)[i];
            delete pData;
		}
	    delete mpDimDataArray;
    }
}

Acad::ErrorStatus
AcCircleJig::setPlane()
{
    // Acquire current UCS transformation matrix.
    // We save the matrix for later use.
    //
    acdbUcsMatrix(mUcsToWcsMat);
    mWcsToUcsMat = mUcsToWcsMat.inverse();

    // Get data from user coordinate system.
    //
    AcGePoint3d orgPt;
    AcGeVector3d xAxis, yAxis, zAxis;
    mUcsToWcsMat.getCoordSystem(orgPt, xAxis, yAxis, zAxis);

    // Get the current elevation w.r.t current UCS, w.r.t the current space.
    //
    struct resbuf rb;
    ads_getvar(/*MSG0*/"CVPORT", &rb);
    double elev;
    if (rb.resval.rint == 1)
        elev = mpdb->pelevation();  // Paper space
    else
        elev = mpdb->elevation();   // Model space

    // Convert elevation from UCS to WCS.
    //
    orgPt += elev * zAxis;
    mElevation = zAxis.dotProduct(orgPt.asVector());
    mNormal = zAxis;
    mHorizDir = xAxis;
    return Acad::eOk;
}

//Purpose: This is the fist function that that command is
//         expected to call. This would call the other drag()
//		   method classes.
void	   
AcCircleJig::dragIt(void)
{

	AcEdJig::DragStatus stat;
	const char* pszPrompt = "Enter the center for the Circle";
	setDispPrompt(pszPrompt);
	stat =acquireDefPt();

	setCircleProperties();

	do
	{
	const char*pszPrompt2 = "Enter the Radius point for the circle";
	setDispPrompt(pszPrompt2);
	addDimData();
	stat = drag();
    } while (stat != AcEdJig::kNormal && stat != AcEdJig::kCancel &&
             stat != AcEdJig::kNull);


	if (stat == AcEdJig::kNormal)
     append();

}

AcEdJig::DragStatus
AcCircleJig::acquireDefPt()
{
	DragStatus stat;

	setUserInputControls( (UserInputControls)
						  (AcEdJig::kAccept3dCoordinates |
						   AcEdJig::kNoNegativeResponseAccepted)
						 );
	AcGePoint3d pt;
	stat =acquirePoint(pt);
	if(mCenterPt != pt)
		mCenterPt=pt;
	if(stat == AcEdJig::kNormal )
		return AcEdJig::kNoChange;
	else
		return stat;
}

AcEdJig::DragStatus	   
AcCircleJig::sampler(void)
{
	DragStatus stat;

    setUserInputControls((UserInputControls)
        (AcEdJig::kAccept3dCoordinates
         | AcEdJig::kGovernedByOrthoMode
         | AcEdJig::kAcceptOtherInputString  
         | AcEdJig::kNoNegativeResponseAccepted
         | AcEdJig::kNullResponseAccepted
         | AcEdJig::kNoZeroResponseAccepted));


    AcGePoint3d pnt;
    stat = acquirePoint(pnt);
    
	if (stat == kNormal) {
        if (pnt == mRadVec){
           return AcEdJig::kNoChange;
        } 
		else{
				mRadVec = pnt;
        }
    }

    return stat;
}


Adesk::Boolean 
AcCircleJig::update()
{
	    AcGeVector3d radVec = mRadVec - mCenterPt;
        double radius = radVec.length();

		mpCircle->setRadius(radius);

		//update the Dynamic Dimension
		updateDimension();
		return Adesk::kTrue;

}
void						
AcCircleJig::setCircleProperties()
{
	mpCircle->setDatabaseDefaults();
	mpCircle->setCenter(mCenterPt);
	mpCircle->setNormal(mNormal);
}

bool						 
AcCircleJig::updateDimension()
{
    if (!mpCircle || !mpDimDataArray || 
		(mpDimDataArray->length() <= 0))
        return false;

    double radius = mpCircle->radius();
    AcGePoint3d cenPt = mpCircle->Center();
    AcGeVector3d radVec = mRadVec - cenPt;
    if (!radVec.isZeroLength())
	{
        radVec.normalize();
        radVec = radius * radVec;
	}

    AcGePoint3d chordPt = cenPt + radVec;
    AcGePoint3d farChordPt = cenPt - radVec;

    for (int i = 0; i < mpDimDataArray->length(); i++)
	{
         AcDbDimData *pData = (*mpDimDataArray)[i];
         int iAppData = *( static_cast<int *>(pData->appData()) );

         AcDbDimension *pDim = (AcDbDimension*)pData->dimension();
         AcDbAlignedDimension *pAlnDim = AcDbAlignedDimension::cast(pDim);
         if (pAlnDim == NULL)
             continue;

		  pAlnDim->setXLine1Point(cenPt);
		  pAlnDim->setXLine2Point(chordPt);
          pAlnDim->setDimLinePoint(chordPt);

	}
	return true;
}

AcDbDimDataPtrArray* 
AcCircleJig::dimData(const double dimScale)
{
	return mpDimDataArray;
}

Acad::ErrorStatus 
AcCircleJig::setDimValue(const AcDbDimData *pdimData,
						 const double dimValue)
{
mpCircle->setRadius(dimValue);
return Acad::eOk;
}

bool
AcCircleJig::addDimData()
{
    if (mpCircle == NULL)
        return false;

    if (mpDimDataArray == NULL) {
        mpDimDataArray = new AcDbDimDataPtrArray();
    } else {
        for (int i = 0; i < mpDimDataArray->length(); i++) {
            AcDbDimData *pData = (*mpDimDataArray)[i];
            delete pData;
		}

	    mpDimDataArray->setLogicalLength(0);
    }

    double radius = mpCircle->radius();
    AcGePoint3d cenPt = mpCircle->Center();

	AcGeVector3d normal = mpCircle->normal();

	AcGeVector3d vertDir = normal.crossProduct(mHorizDir);
	
    AcDbAlignedDimension *pAlnDim1 = new AcDbAlignedDimension();
    pAlnDim1->setDatabaseDefaults();
    pAlnDim1->setNormal(normal);
    pAlnDim1->setElevation(mElevation);
    pAlnDim1->setDimsah(true);
    pAlnDim1->setDimse1(true);
    pAlnDim1->setDimblk1("None");
    pAlnDim1->setXLine1Point(mCenterPt);

    pAlnDim1->setXLine2Point(mRadVec);
    pAlnDim1->setDimLinePoint(mRadVec);

    AcDbDimData *dimData1 = new AcDbDimData(pAlnDim1);
	int DimIndex(1);
    dimData1->setAppData(&DimIndex);
    dimData1->setDimFocal(true);
    dimData1->setDimEditable(true);
    mpDimDataArray->append(dimData1);

	return true;

}