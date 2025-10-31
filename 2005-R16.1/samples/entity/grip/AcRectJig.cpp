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

#include "acrectjig.h"
#include "geassign.h"
#include "acmain.h"
#include "acrect.h"
#include <math.h>

// AcRectJig class member function implementation.
//

AcRectJig::AcRectJig(AcDbDatabase* pDb, AcRectangle* pRect)
{
    mElevation = 0.0;
    mNormal.set(0,0,1);
    mpDb = pDb;
    mpRect = pRect;
    mLockWidth = false;
    mLockHeight = false;
    mKeyword = 0;
    mpDimData = NULL;
}

AcRectJig::~AcRectJig()
{
    // Delete AcDbDimData if any
    //
    if (mpDimData) {
        for (int i = 0; i < mpDimData->length(); i++) {
            AcDbDimData *pData = (*mpDimData)[i];
            AppData *pAppData = (AppData*)pData->appData();
            if (pAppData)
                delete pAppData;
            delete pData;
		}

	    delete mpDimData;
    }
}

Acad::ErrorStatus
AcRectJig::setPlane()
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
        elev = mpDb->pelevation();  // Paper space
    else
        elev = mpDb->elevation();   // Model space

    // Convert elevation from UCS to WCS.
    //
    orgPt += elev * zAxis;
    mElevation = zAxis.dotProduct(orgPt.asVector());
    mNormal = zAxis;
    mHorizDir = xAxis;
    mVertDir = mNormal.crossProduct(mHorizDir);
    return Acad::eOk;
}

Acad::ErrorStatus
AcRectJig::acquireDefPoints()
{
    setUserInputControls((UserInputControls)
        (AcEdJig::kAccept3dCoordinates
         | AcEdJig::kGovernedByOrthoMode
         | AcEdJig::kNoNegativeResponseAccepted
         | AcEdJig::kNullResponseAccepted
         | AcEdJig::kNoZeroResponseAccepted));

    setPlane();
    const char* prompt = "\nSpecify first corner point: ";
    setDispPrompt(prompt);

    int stat = acquirePoint(mWcsPt1);
    return (stat == AcEdJig::kNormal) ? Acad::eOk : Acad::eInvalidInput;
}

void AcRectJig::prepRect()
{
    assert(mpRect);
    mpRect->setDatabaseDefaults();
    mpRect->setNormal(mNormal);
    mpRect->setElevation(mElevation);
    mpRect->setCenter(mWcsPt1);
    mpRect->setHorizDir(mHorizDir);
}


void AcRectJig::dragIt()
{
    AcEdJig::DragStatus stat;
    const char* prompt = "\nSpecify other corner point: ";

    do {
        setDispPrompt(prompt);
        stat = drag();
        //keywordHandler(stat);

    } while (stat != AcEdJig::kNormal && stat != AcEdJig::kCancel &&
             stat != AcEdJig::kNull);

    // Use AcDimJig's append
    if (stat == AcEdJig::kNormal) {
        append();

    } else { 
        delete mpRect;
    }
}

// This function is called by the drag function in order to
// aquire a sample input
//
AcEdJig::DragStatus AcRectJig::sampler()
{
    DragStatus stat;

    setUserInputControls((UserInputControls)
        (AcEdJig::kAccept3dCoordinates
         | AcEdJig::kGovernedByOrthoMode
         | AcEdJig::kAcceptOtherInputString  
         | AcEdJig::kNoNegativeResponseAccepted
         | AcEdJig::kNullResponseAccepted
         | AcEdJig::kNoZeroResponseAccepted));

    //const char* keyWord = "Horz Vert All None";
    //setKeywordList(keyWord);

    AcGePoint3d pnt;
    stat = acquirePoint(pnt);
    if (stat == kNormal) {
        if (pnt == mWcsPt2)   {
            return AcEdJig::kNoChange;
        } else {
            mWcsPt2 = pnt;
        }
    }

    return stat;
}

// This function is called to update the entity based on the
// input values
//
Adesk::Boolean AcRectJig::update()
{
    AcGeVector3d diaVec = mWcsPt2 - mWcsPt1;
    AcGePoint3d cenPt = mWcsPt1 + 0.5 * diaVec;
    double width = fabs(diaVec.dotProduct(mHorizDir));
    double height = fabs(diaVec.dotProduct(mVertDir));

    if (!(mLockWidth || mLockHeight))
        mpRect->setCenter(cenPt);

    if (!mLockWidth)
        mpRect->setWidth(width);

    if (!mLockHeight)
        mpRect->setHeight(height);

    updateDimData();

    return Adesk::kTrue;
}

// This function must be implemented to return a pointer to
// the entity being manipulated by the jig.
//
AcDbEntity* AcRectJig::entity() const
{
    return mpRect;
} 

AcDbDimDataPtrArray*
AcRectJig::dimData(const double dimScale)
{
    addDimData(kHorizontalDim | kVerticalDim, dimScale);

    switch (mKeyword) {
    case AcEdJig::kKW1:
        appendDimData(kHorizontalDim);
        break;

    case AcEdJig::kKW2:
        appendDimData(kVerticalDim);
        break;

    case AcEdJig::kKW3:
        appendDimData(kHorizontalDim | kVerticalDim);
        break;
    }


    return mpDimData;
}

AcDbDimDataPtrArray*
AcRectJig::dimData() const
{
    //addDimData(kHorizontalDim | kVerticalDim, 1.0);
    return mpDimData;
}

bool
AcRectJig::addDimData(int which, double dimScale)
{
    if (mpRect == NULL)
        return false;

    if (mpDimData == NULL) {
        mpDimData = new AcDbDimDataPtrArray();
    } else {
        for (int i = 0; i < mpDimData->length(); i++) {
            AcDbDimData *pData = (*mpDimData)[i];
            AppData *pAppData = (AppData*)pData->appData();
            if (pAppData)
                delete pAppData;
            delete pData;
		}
        
	    mpDimData->setLogicalLength(0);
    }

    double width = mpRect->width();
    double height = mpRect->height();
    AcGePoint3d cenPt = mpRect->center();

    AcGeVector3d vertDir = mNormal.crossProduct(mHorizDir);
    AcGePoint3d pt1, pt2, pt3, pt4, dimPt1, dimPt2;
    double horizRot = 0.0;
    //double horizRot = userToLocalAngle(mNormal, mHorizDir);

    pt1 = cenPt + 0.5 * width * mHorizDir + 0.5 * height * vertDir;
    pt2 = cenPt - 0.5 * width * mHorizDir + 0.5 * height * vertDir;
    pt3 = cenPt - 0.5 * width * mHorizDir - 0.5 * height * vertDir;
    pt4 = cenPt + 0.5 * width * mHorizDir - 0.5 * height * vertDir;

    if (which & kHorizontalDim) {
        AcDbAlignedDimension *pAlnDim1 = new AcDbAlignedDimension();
        dimPt1 = cenPt + (0.5 * height + 0.5 * dimScale) * vertDir;
        pAlnDim1->setDatabaseDefaults();
        pAlnDim1->setNormal(mNormal);
        pAlnDim1->setElevation(mElevation);
        pAlnDim1->setHorizontalRotation(-horizRot);
        pAlnDim1->setXLine1Point(pt1);
        pAlnDim1->setXLine2Point(pt2);
        pAlnDim1->setDimLinePoint(dimPt1);
        pAlnDim1->setDimtad(1);

        AcDbDimData *dimData1 = new AcDbDimData(pAlnDim1);
        AppData *appData1 = new AppData(1, dimScale);
        dimData1->setAppData(appData1);
        dimData1->setDimFocal(true);
        //dimData1->setDimInvisible(true);
        dimData1->setDimEditable(true);
        mpDimData->append(dimData1);
    }

    if (which & kVerticalDim) {
        AcDbAlignedDimension *pAlnDim2 = new AcDbAlignedDimension();
        dimPt2 = cenPt + (0.5 * width + 0.5 * dimScale) * mHorizDir;
        pAlnDim2->setDatabaseDefaults();
        pAlnDim2->setNormal(mNormal);
        pAlnDim2->setElevation(mElevation);
        pAlnDim2->setHorizontalRotation(-horizRot);
        pAlnDim2->setXLine1Point(pt1);
        pAlnDim2->setXLine2Point(pt4);
        pAlnDim2->setDimLinePoint(dimPt2);
        pAlnDim2->setDimtad(1);
        AcDbDimData *dimData2 = new AcDbDimData(pAlnDim2);
        AppData *appData2 = new AppData(2, dimScale);
        dimData2->setAppData(appData2);
        //dimData2->setDimFocal(true);
        dimData2->setDimEditable(false);
		dimData2->setDimHideIfValueIsZero(true);
        //dimData2->setDimInvisible(true);
        mpDimData->append(dimData2);
    }

    return true;
}

bool
AcRectJig::updateDimData()
{
    if (!mpRect || !mpDimData || (mpDimData->length() <= 0))
        return false;

    double width = mpRect->width();
    double height = mpRect->height();
    AcGePoint3d cenPt = mpRect->center();
    AcGeVector3d vertDir = mNormal.crossProduct(mHorizDir);
    int dimIndex1 = 0, dimIndex2 = 0;
    AcGePoint3d pt1, pt2, pt3, pt4, dimPt;
    pt1 = cenPt + 0.5 * width * mHorizDir + 0.5 * height * vertDir;
    pt2 = cenPt - 0.5 * width * mHorizDir + 0.5 * height * vertDir;
    pt3 = cenPt - 0.5 * width * mHorizDir - 0.5 * height * vertDir;
    pt4 = cenPt + 0.5 * width * mHorizDir - 0.5 * height * vertDir;

    for (int i = 0; i < mpDimData->length(); i++) {
         AcDbDimData *pData = (*mpDimData)[i];
         AppData *pDimAppData = (AppData*)pData->appData();         
         int dimIndex = pDimAppData ? pDimAppData->index() : 0;
         double dimScale = pDimAppData->dimScale();
         AcDbDimension *pDim = (AcDbDimension*)pData->dimension();

         if (pDim->isKindOf(AcDbAlignedDimension::desc())) {
             AcDbAlignedDimension *pAlnDim = AcDbAlignedDimension::cast(pDim);
             switch (dimIndex) {
             case 1:
                 dimPt = cenPt + (0.5 * height + 0.5 * dimScale) * vertDir;
                 pAlnDim->setXLine1Point(pt1);
                 pAlnDim->setXLine2Point(pt2);
                 pAlnDim->setDimLinePoint(dimPt);
                 break;

             case 2:
                 dimPt = cenPt + (0.5 * width + 0.5 * dimScale) * mHorizDir;
                 pAlnDim->setXLine1Point(pt1);
                 pAlnDim->setXLine2Point(pt4);
                 pAlnDim->setDimLinePoint(dimPt);
                 break;
             }
         }
	}

    return true;
}

Acad::ErrorStatus 
AcRectJig::setDimValue(const AcDbDimData* dimData,
                       const double dimValue)
{
    if (dimData == NULL)
        return Acad::eInvalidInput;

    AppData *pDimAppData = (AppData*)dimData->appData();
    int dimIndex = pDimAppData ? pDimAppData->index() : 0;

    switch (dimIndex) {
    case 1:
        mpRect->setWidth(dimValue);
        mLockWidth = true;
        break;

    case 2:
        mpRect->setHeight(dimValue);
        mLockHeight = true;
        break;
	}

    return Acad::eOk;
    mpRect->setWidth(dimValue);
    return Acad::eOk;
}

void
AcRectJig::keywordHandler(AcEdJig::DragStatus& kword)
{
    switch (kword) {
    case AcEdJig::kKW1:
        mKeyword = kHorizontalDim;
        break;

    case AcEdJig::kKW2:
        mKeyword = kVerticalDim;
        break;

    case AcEdJig::kKW3:
        mKeyword = kHorizontalDim | kVerticalDim;
        break;

    case AcEdJig::kKW4:
		mKeyword = kNone;
        break;
    }
}

bool
AcRectJig::appendDimData(int which, double dimScale)
{
    if (mpRect == NULL)
        return false;

    if (mpDimData == NULL) {
        mpDimData = new AcDbDimDataPtrArray();
    } 
	
    double width = mpRect->width();
    double height = mpRect->height();
    AcGePoint3d cenPt = mpRect->center();

    AcGeVector3d vertDir = mNormal.crossProduct(mHorizDir);
    AcGePoint3d pt1, pt2, pt3, pt4, dimPt1, dimPt2;
    double horizRot = 0.0;
    //double horizRot = userToLocalAngle(mNormal, mHorizDir);

    pt1 = cenPt + 0.5 * width * mHorizDir + 0.5 * height * vertDir;
    pt2 = cenPt - 0.5 * width * mHorizDir + 0.5 * height * vertDir;
    pt3 = cenPt - 0.5 * width * mHorizDir - 0.5 * height * vertDir;
    pt4 = cenPt + 0.5 * width * mHorizDir - 0.5 * height * vertDir;

    if (which & kHorizontalDim) {
        AcDbAlignedDimension *pAlnDim1 = new AcDbAlignedDimension();
        dimPt1 = cenPt - (0.5 * height + 0.5 * dimScale) * vertDir;
        pAlnDim1->setDatabaseDefaults();
        pAlnDim1->setNormal(mNormal);
        pAlnDim1->setElevation(mElevation);
        pAlnDim1->setHorizontalRotation(-horizRot);
        pAlnDim1->setXLine1Point(pt3);
        pAlnDim1->setXLine2Point(pt4);
        pAlnDim1->setDimLinePoint(dimPt1);
        pAlnDim1->setDimtad(1);

        AcDbDimData *dimData1 = new AcDbDimData(pAlnDim1);
        AppData *appData1 = new AppData(3, dimScale);
        dimData1->setAppData(appData1);
        //dimData1->setDimFocal(true);
        //dimData1->setDimInvisible(true);
        dimData1->setDimEditable(true);
        mpDimData->append(dimData1);
    }

    if (which & kVerticalDim) {
        AcDbAlignedDimension *pAlnDim2 = new AcDbAlignedDimension();
        dimPt2 = cenPt - (0.5 * width + 0.5 * dimScale) * mHorizDir;
        pAlnDim2->setDatabaseDefaults();
        pAlnDim2->setNormal(mNormal);
        pAlnDim2->setElevation(mElevation);
        pAlnDim2->setHorizontalRotation(-horizRot);
        pAlnDim2->setXLine1Point(pt2);
        pAlnDim2->setXLine2Point(pt3);
        pAlnDim2->setDimLinePoint(dimPt2);
        pAlnDim2->setDimtad(1);
        AcDbDimData *dimData2 = new AcDbDimData(pAlnDim2);
        AppData *appData2 = new AppData(4, dimScale);
        dimData2->setAppData(appData2);
        //dimData2->setDimFocal(true);
        dimData2->setDimEditable(true);
        //dimData2->setDimInvisible(true);
        mpDimData->append(dimData2);
    }

    return true;
}