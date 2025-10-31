//
// (C) Copyright 1998-2002,2004 by Autodesk, Inc. 
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

//Implements AcRectangle
// FILE: acrect.cpp
//#include <afxwin.h>
#include "acmain.h"
#include "acrect.h"
#include "dbxutil.h"
#include <tchar.h>

static double 
userToLocalAngle(const AcGeVector3d& normal,
                 const AcGeVector3d& ucsXdir);

///	Class AcRectangle Definition

ACRX_DXF_DEFINE_MEMBERS(AcRectangle,AcDbEntity,AcDb::kDHL_CURRENT,AcDb::kMReleaseCurrent,
						AcDbProxyEntity::kNoOperation, ACRECT,ACRECT);


AcRectangle::AcRectangle()
{
    mNormal.set(0,0,1);
    mHorizDir.set(1,0,0);
    mWidth = 0.0;	
    mHeight = 0.0;
    mCenter.set(0,0,0);
}

AcRectangle::~AcRectangle()
{
}


AcRectangle::AcRectangle(AcGeVector3d& normVec, AcGeVector3d& horzDir, 
                         AcGePoint3d &cenPt, double width, double height)
  : mNormal(normVec), mHorizDir(horzDir), mCenter(cenPt), 
    mWidth(width), mHeight(height)
{
}

double AcRectangle::width() const
{
    return mWidth;
}

void AcRectangle::setWidth(double value)
{
    mWidth = value;
}

double AcRectangle::height() const
{
    return mHeight;
}

void AcRectangle::setHeight(double value)
{
    mHeight = value;
}

double AcRectangle::elevation() const
{
    return mElevation;
}

void AcRectangle::setElevation(double value)
{
    mElevation = value;
}

AcGePoint3d AcRectangle::center() const
{
    return mCenter;
}

void AcRectangle::setCenter(const AcGePoint3d& cenPt)
{
    mCenter = cenPt;
}

AcGeVector3d AcRectangle::normal() const
{
    return mNormal;
}

void AcRectangle::setNormal(const AcGeVector3d& normVec)
{
    mNormal = normVec;
}

AcGeVector3d AcRectangle::horizDir() const
{
    return mHorizDir;
}

void AcRectangle::setHorizDir(const AcGeVector3d& horizVec)
{
    mHorizDir = horizVec;
}

void AcRectangle::list() const
{
    assertReadEnabled();
	AcDbEntity::list();

    AcGeMatrix3d ucsToWcsMat, wcsToUcsMat;
    acdbUcsMatrix(ucsToWcsMat);
    wcsToUcsMat = ucsToWcsMat.inverse();
    AcGePoint3d cenPt = mCenter;
    cenPt.transformBy(wcsToUcsMat);

    acutPrintf(_T("\nWidth:  %f"), mWidth);
    acutPrintf(_T("\nHeight: %f"), mHeight);
    acutPrintf(_T("\nCenter: X= %f, Y= %f, Z= %f"), cenPt.x, cenPt.y, cenPt.z);
    acutPrintf(_T("\nNormal: X= %f, Y= %f, Z= %f"), mNormal.x, mNormal.y, mNormal.z);
    acutPrintf("\n");
}

Acad::ErrorStatus AcRectangle::transformBy(const AcGeMatrix3d& xform)
{
    assertWriteEnabled();

    if (!xform.isUniScaledOrtho())
        return Acad::eCannotScaleNonUniformly;

    AcGeScale3d sc;
    sc.extractScale(xform);
    mWidth *= sc.sx;
    mHeight *= sc.sx;
    mNormal.transformBy(xform);
    mHorizDir.transformBy(xform);
    mCenter.transformBy(xform);
    mNormal.normalize();
    mHorizDir.normalize();
    return Acad::eOk;
}

Acad::ErrorStatus AcRectangle::dwgInFields(AcDbDwgFiler* pFiler)
{
    assertWriteEnabled();
    Acad::ErrorStatus es;

    // Call dwgInFields from AcDbEntity
    if ((es = AcDbEntity::dwgInFields(pFiler)) != Acad::eOk) {
        return es;
	}

    pFiler->readItem(&mNormal);
    pFiler->readItem(&mHorizDir);
    pFiler->readItem(&mCenter);
    pFiler->readItem(&mWidth);
    pFiler->readItem(&mHeight);
    return pFiler->filerStatus();
}	


Acad::ErrorStatus AcRectangle::dwgOutFields(AcDbDwgFiler* pFiler) const
{
    assertReadEnabled();
    Acad::ErrorStatus es;

    if ((es = AcDbEntity::dwgOutFields(pFiler)) != Acad::eOk) {
        return es;
	}

    pFiler->writeItem(mNormal);
    pFiler->writeItem(mHorizDir);
    pFiler->writeItem(mCenter);
    pFiler->writeItem(mWidth);
    pFiler->writeItem(mHeight);
    return pFiler->filerStatus();
}


Acad::ErrorStatus AcRectangle::dxfInFields(AcDbDxfFiler* pFiler)
{
	assertWriteEnabled();

	if ((AcDbEntity::dxfInFields(pFiler) != Acad::eOk) ||
	    !pFiler->atSubclassData(_T("AcRectangle")))
		return pFiler->filerStatus();

	return pFiler->filerStatus();
}


Acad::ErrorStatus AcRectangle::dxfOutFields(AcDbDxfFiler* pFiler) const
{
	assertReadEnabled();
	Acad::ErrorStatus es;

	if ((es = AcDbEntity::dxfOutFields(pFiler)) != Acad::eOk)
		return es;

	return pFiler->filerStatus();
}

	
Adesk::Boolean    
AcRectangle::worldDraw(AcGiWorldDraw* pWorld)
{
    AcGePoint3d pts[5];
    AcGeVector3d vertDir = mNormal.crossProduct(mHorizDir);
    pts[0] = mCenter + 0.5 * mWidth * mHorizDir + 0.5 * mHeight * vertDir;
    pts[1] = mCenter - 0.5 * mWidth * mHorizDir + 0.5 * mHeight * vertDir;
    pts[2] = mCenter - 0.5 * mWidth * mHorizDir - 0.5 * mHeight * vertDir;
    pts[3] = mCenter + 0.5 * mWidth * mHorizDir - 0.5 * mHeight * vertDir;
    pts[4] = pts[0];
    pWorld->geometry().polyline(5, pts);
    return Adesk::kTrue;
}


Acad::ErrorStatus 
AcRectangle::getGripPoints(AcGePoint3dArray& gripPoints, AcDbIntArray&,
			  AcDbIntArray&) const
{
	return Acad::eOk;
}


Acad::ErrorStatus 
AcRectangle::moveGripPointsAt(const AcDbIntArray &indices,
                              const AcGeVector3d& offset)
{
    return Acad::eOk;
}

Acad::ErrorStatus   
AcRectangle::getGripPoints(AcDbGripDataPtrArray& grips, 
                           const double curViewUnitSize, 
                           const int gripSize,
                           const AcGeVector3d& curViewDir, 
                           const int bitflags) const
{
	assertReadEnabled();
#define MODULE_ID ACCMENTITYCOLOR_CPP_

	Adesk::UInt32 r(0); 
	Adesk::UInt32 g(0); 
	Adesk::UInt32 b(0); 

	r =AcCmEntityColor::mLUT[1][0];
	g =AcCmEntityColor::mLUT[1][1];
	b =AcCmEntityColor::mLUT[1][2];


    AppData *appData0 = new AppData(0);
    AppData *appData1 = new AppData(1);
    AppData *appData2 = new AppData(2);
    AppData *appData3 = new AppData(3);
    AppData *appData4 = new AppData(4);

    AcGePoint3d pts[5];
    AcGeVector3d vertDir = mNormal.crossProduct(mHorizDir);
    pts[0] = mCenter;
    pts[1] = mCenter + 0.5 * mWidth * mHorizDir + 0.5 * mHeight * vertDir;
    pts[2] = mCenter - 0.5 * mWidth * mHorizDir + 0.5 * mHeight * vertDir;
    pts[3] = mCenter - 0.5 * mWidth * mHorizDir - 0.5 * mHeight * vertDir;
    pts[4] = mCenter + 0.5 * mWidth * mHorizDir - 0.5 * mHeight * vertDir;

	// Setting for the center grip point
    AcDbGripData *pGripData0 = new AcDbGripData();
	pGripData0->setGripPoint(pts[0]);
	pGripData0->setAppData(appData0);
    //pGripData0->setHoverDimensionFunc(hoverDimensionCbackFunc);
    //pGripData0->setHotGripDimensionFunc(hotGripDimensionCbackFunc);
	grips.append(pGripData0);

    // Setting for the top-right grip point
    AcDbGripData *pGripData1 = new AcDbGripData();
	pGripData1->setGripPoint(pts[1]);
	pGripData1->setAppData(appData1);
    pGripData1->setHoverDimensionFunc(hoverDimensionCbackFunc);
    pGripData1->setHotGripDimensionFunc(hotGripDimensionCbackFunc);
	pGripData1->setViewportDraw(GripViewportDrawfunc);
	pGripData1->setDrawAtDragImageGripPoint(true);

	grips.append(pGripData1);

    // Setting for the top-left grip point
    AcDbGripData *pGripData2 = new AcDbGripData();
	pGripData2->setGripPoint(pts[2]);
	pGripData2->setAppData(appData2);
    pGripData2->setHoverDimensionFunc(hoverDimensionCbackFunc);
    pGripData2->setHotGripDimensionFunc(hotGripDimensionCbackFunc);
	pGripData2->setViewportDraw(GripViewportDrawfunc);
	pGripData2->setDrawAtDragImageGripPoint(true);
	grips.append(pGripData2);

    // Setting for the bottom-left grip point
    AcDbGripData *pGripData3 = new AcDbGripData();
	pGripData3->setGripPoint(pts[3]);
	pGripData3->setAppData(appData3);
    pGripData3->setHoverDimensionFunc(hoverDimensionCbackFunc);
    pGripData3->setHotGripDimensionFunc(hotGripDimensionCbackFunc);
	grips.append(pGripData3);
	
    // Setting for the bottom-right grip point
    AcDbGripData *pGripData4 = new AcDbGripData();
	pGripData4->setGripPoint(pts[4]);
	pGripData4->setAppData(appData4);
    pGripData4->setHoverDimensionFunc(hoverDimensionCbackFunc);
    pGripData4->setHotGripDimensionFunc(hotGripDimensionCbackFunc);
	grips.append(pGripData4);

	return Acad::eOk;
}

Acad::ErrorStatus
AcRectangle::moveGripPointsAt(const AcDbVoidPtrArray& appData,
                              const AcGeVector3d& offset,
                              const int bitflags)
{
    assertWriteEnabled();
	if (!appData.length())
		return Acad::eInvalidInput;

    AcGePoint3d pt1, pt2;
    AcGeVector3d diaVec;

    AppData *pAppData = (AppData*)appData[0];
    int gripID = pAppData->index();
    AcGeVector3d vertDir = mNormal.crossProduct(mHorizDir);
	
    switch(gripID) {
    case 0:
        mCenter += offset;
        break;

    case 1:
        pt1 = mCenter + 0.5 * mWidth * mHorizDir + 0.5 * mHeight * vertDir;
        pt2 = mCenter - 0.5 * mWidth * mHorizDir - 0.5 * mHeight * vertDir;
        pt1 += offset;
        diaVec = pt1 - pt2;
        mCenter += 0.5 * offset;
        mWidth = fabs(diaVec.dotProduct(mHorizDir));
        mHeight = fabs(diaVec.dotProduct(vertDir));
        break;

    case 2:
        pt1 = mCenter - 0.5 * mWidth * mHorizDir + 0.5 * mHeight * vertDir;
        pt2 = mCenter + 0.5 * mWidth * mHorizDir - 0.5 * mHeight * vertDir;
        pt1 += offset;
        diaVec = pt1 - pt2;
        mCenter += 0.5 * offset;
        mWidth = fabs(diaVec.dotProduct(mHorizDir));
        mHeight = fabs(diaVec.dotProduct(vertDir));
        break;

    case 3:
        pt1 = mCenter - 0.5 * mWidth * mHorizDir - 0.5 * mHeight * vertDir;
        pt2 = mCenter + 0.5 * mWidth * mHorizDir + 0.5 * mHeight * vertDir;
        pt1 += offset;
        diaVec = pt1 - pt2;
        mCenter += 0.5 * offset;
        mWidth = fabs(diaVec.dotProduct(mHorizDir));
        mHeight = fabs(diaVec.dotProduct(vertDir));
        break;
	
    case 4:
        pt1 = mCenter + 0.5 * mWidth * mHorizDir - 0.5 * mHeight * vertDir;
        pt2 = mCenter - 0.5 * mWidth * mHorizDir + 0.5 * mHeight * vertDir;
        pt1 += offset;
        diaVec = pt1 - pt2;
        mCenter += 0.5 * offset;
        mWidth = fabs(diaVec.dotProduct(mHorizDir));
        mHeight = fabs(diaVec.dotProduct(vertDir));
        break;
	}

    // Update dynamic dimensions
    //
    AcDbDimDataPtrArray *pDimDataArr = NULL;
    if (pAppData)
        pDimDataArr = pAppData->dimData();

    updateDimensions(pDimDataArr);

    return Acad::eOk;

}
void
AcRectangle::GripViewportDrawfunc(AcDbGripData				 *pThis,
								  AcGiViewportDraw			 *pVd,
								  const AcDbObjectId			 &entId,
								  AcDbGripOperations::DrawType type,
								  AcGePoint3d					 *cursor,
								  int							 gripSize)
{
	double radius(0.2);
	AcGeVector3d normal(0,0,1);
	AcGePoint3d ep = pThis->gripPoint();

	Adesk::UInt16 setColor =pVd->subEntityTraits().color();
	pVd->subEntityTraits().setColor(255);
	if ( type == AcDbGripOperations::kDragImageGrip )
		{
	pVd->geometry().circle(*cursor,radius, normal);
		}
	else
		{
	pVd->geometry().circle(ep,radius, normal);
		}

}

bool 
AcRectangle::updateDimensions(AcDbDimDataPtrArray* pDimData)
{
    if (!pDimData || (pDimData->length() <= 0))
        return false;		

    int numDims = pDimData->length();
    AcDbObjectId entId = objectId();
    AcGeVector3d vertDir = mNormal.crossProduct(mHorizDir);

    AcGePoint3d pt1, pt2, pt3, pt4, dimPt, textPt;
    pt1 = mCenter + 0.5 * mWidth * mHorizDir + 0.5 * mHeight * vertDir;
    pt2 = mCenter - 0.5 * mWidth * mHorizDir + 0.5 * mHeight * vertDir;
    pt3 = mCenter - 0.5 * mWidth * mHorizDir - 0.5 * mHeight * vertDir;
    pt4 = mCenter + 0.5 * mWidth * mHorizDir - 0.5 * mHeight * vertDir; 

    AcDbObjectId ownerId;

    for (int i = 0; i < numDims; i++) {
         AcDbDimData *pData = (*pDimData)[i];
         ownerId = pData->ownerId();
         if (!entId.isNull() && (entId != ownerId))
             continue;

         AppData *pDimAppData = (AppData*)pData->appData();
         int dimIndex = pDimAppData ? pDimAppData->index() : 0;
         double dimScale = pDimAppData->dimScale();
         AcDbDimension *pDim = (AcDbDimension*)pData->dimension();

         if (pDim->isKindOf(AcDbAlignedDimension::desc())) {
             AcDbAlignedDimension *pAlnDim = AcDbAlignedDimension::cast(pDim);
             //pAlnDim->setDimjust(1);

             switch (dimIndex) {
             case 1:
                 textPt = pt2 + 1.0 * vertDir;
                 dimPt = mCenter + (0.5 * mHeight + 0.5 * dimScale) * vertDir;
                 pAlnDim->setXLine1Point(pt1);
                 pAlnDim->setXLine2Point(pt2);
                 pAlnDim->setDimLinePoint(dimPt);
                 //pAlnDim->setTextPosition(textPt);
                 break;

             case 2:
				 textPt = pt1 + 1.0 * mHorizDir;
                 dimPt = mCenter + (0.5 * mWidth + 0.5 * dimScale) * mHorizDir;
                 pAlnDim->setXLine1Point(pt1);
                 pAlnDim->setXLine2Point(pt4);
                 pAlnDim->setDimLinePoint(dimPt);
                 //pAlnDim->setTextPosition(textPt);
                 break;

             case 3:
				 textPt = pt2 + 1.0 * vertDir;
                 dimPt = mCenter + (0.5 * mHeight + 0.5 * dimScale) * vertDir;
                 pAlnDim->setXLine1Point(pt1);
                 pAlnDim->setXLine2Point(pt2);
                 pAlnDim->setDimLinePoint(dimPt);
                 //pAlnDim->setTextPosition(textPt);
                 break;

             case 4:
				 textPt = pt1 + 1.0 * mHorizDir;
                 dimPt = mCenter + (0.5 * mWidth + 0.5 * dimScale) * mHorizDir;
                 pAlnDim->setXLine1Point(pt1);
                 pAlnDim->setXLine2Point(pt4);
                 pAlnDim->setDimLinePoint(dimPt);
                 //pAlnDim->setTextPosition(textPt);
                 break;

             case 5:
                 dimPt = mCenter + (0.5 * mHeight + 0.5 * dimScale) * vertDir;
                 pAlnDim->setXLine1Point(pt1);
                 pAlnDim->setXLine2Point(pt2);
                 pAlnDim->setDimLinePoint(dimPt);
                 break;

             case 6:
                 dimPt = mCenter - (0.5 * mWidth + 0.5 * dimScale) * mHorizDir;
                 pAlnDim->setXLine1Point(pt2);
                 pAlnDim->setXLine2Point(pt3);
                 pAlnDim->setDimLinePoint(dimPt);
                 break;

             case 7:
                 dimPt = mCenter - (0.5 * mWidth + 0.5 * dimScale) * mHorizDir;
                 pAlnDim->setXLine1Point(pt2);
                 pAlnDim->setXLine2Point(pt3);
                 pAlnDim->setDimLinePoint(dimPt);
                 break;

             case 8:
                 dimPt = mCenter - (0.5 * mHeight + 0.5 * dimScale) * vertDir;
                 pAlnDim->setXLine1Point(pt3);
                 pAlnDim->setXLine2Point(pt4);
                 pAlnDim->setDimLinePoint(dimPt);
                 break;

             case 9:
                 dimPt = mCenter - (0.5 * mHeight + 0.5 * dimScale) * vertDir;
                 pAlnDim->setXLine1Point(pt3);
                 pAlnDim->setXLine2Point(pt4);
                 pAlnDim->setDimLinePoint(dimPt);
                 break;

             case 10:
                 dimPt = mCenter + (0.5 * mWidth + 0.5 * dimScale) * mHorizDir;
                 pAlnDim->setXLine1Point(pt4);
                 pAlnDim->setXLine2Point(pt1);
                 pAlnDim->setDimLinePoint(dimPt);
                 break;
             }
         }
    }

    return true;
}

//========================================================================
//
// Dynamic dimensions callback functions implementation
//
//========================================================================

void
AcRectangle::hoverDimensionCbackFunc(AcDbGripData* pGrip,
                                     const AcDbObjectId& objId,
                                     double dimScale,
                                     AcDbDimDataPtrArray& dimDataArr)
{
    gripDimensionCbackFuncGuts(pGrip, objId, dimScale, dimDataArr, true);
}

void
AcRectangle::hotGripDimensionCbackFunc(AcDbGripData* pGrip, 
                                       const AcDbObjectId& objId,
                                       double dimScale,
                                       AcDbDimDataPtrArray& dimDataArr)
{
    gripDimensionCbackFuncGuts(pGrip, objId, dimScale, dimDataArr, false);
}


void
AcRectangle::gripDimensionCbackFuncGuts(AcDbGripData* pGrip, 
                                        const AcDbObjectId& objId,
                                        double dimScale,
                                        AcDbDimDataPtrArray& dimDataArr,
                                        bool isHover)
{
    if (pGrip == NULL)
        return;

    AppData *pAppData = (AppData*)pGrip->appData();
    int gripID = pAppData ? pAppData->index() : -1;
    if ((gripID < 0) || (gripID > 4))
        return;

    AcDbEntity *pEnt = NULL;
	if (acdbOpenAcDbEntity(pEnt, objId, AcDb::kForRead) != Acad::eOk)
        return;

    AcRectangle *pRect = AcRectangle::cast(pEnt);
    if (pRect == NULL) {
        pEnt->close();
        return;
    }

    AcGeVector3d mHorizDir = pRect->horizDir();
    AcGeVector3d mNormal = pRect->normal();
    AcGeVector3d vertDir = mNormal.crossProduct(mHorizDir);
    AcGePoint3d mCenter = pRect->center();
    double mWidth = pRect->width();
    double mHeight = pRect->height();
    double mElevation = pRect->elevation();
    pRect->close();

    int dimIndex1 = 0, dimIndex2 = 0;
    AcGePoint3d pt1, pt2, pt3, pt4, dimPt1, dimPt2;
    double horizRot = userToLocalAngle(mNormal, mHorizDir);
    pt1 = mCenter + 0.5 * mWidth * mHorizDir + 0.5 * mHeight * vertDir;
    pt2 = mCenter - 0.5 * mWidth * mHorizDir + 0.5 * mHeight * vertDir;
    pt3 = mCenter - 0.5 * mWidth * mHorizDir - 0.5 * mHeight * vertDir;
    pt4 = mCenter + 0.5 * mWidth * mHorizDir - 0.5 * mHeight * vertDir;

    AcDbAlignedDimension *pAlnDim1 = new AcDbAlignedDimension();
    pAlnDim1->setDatabaseDefaults();
    pAlnDim1->setNormal(mNormal);
    pAlnDim1->setElevation(mElevation);
    //pAlnDim1->setDimtad(1);
    pAlnDim1->setHorizontalRotation(-horizRot);

    AcDbAlignedDimension *pAlnDim2 = new AcDbAlignedDimension();
    pAlnDim2->setDatabaseDefaults();
    pAlnDim2->setNormal(mNormal);
    pAlnDim2->setElevation(mElevation);
    //pAlnDim2->setDimtad(1);
    pAlnDim2->setHorizontalRotation(-horizRot);

    if (isHover) {
        AcCmColor dimColor;
        dimColor.setColorIndex(8);  // gray    
        pAlnDim1->setDimclrd(dimColor);
        pAlnDim1->setDimclre(dimColor);
        pAlnDim1->setDimclrt(dimColor);
        pAlnDim2->setDimclrd(dimColor);
        pAlnDim2->setDimclre(dimColor);
        pAlnDim2->setDimclrt(dimColor);
	}

    switch (gripID) {
    case 1:
        dimIndex1 = 3;
        dimPt1 = mCenter + (0.5 * mHeight + 0.5 * dimScale) * vertDir;
        pAlnDim1->setXLine1Point(pt1);
        pAlnDim1->setXLine2Point(pt2);
        pAlnDim1->setDimLinePoint(dimPt1);

        dimIndex2 = 4;  
        dimPt2 = mCenter + (0.5 * mWidth + 0.5 * dimScale) * mHorizDir;
        pAlnDim2->setXLine1Point(pt1);
        pAlnDim2->setXLine2Point(pt4);
        pAlnDim2->setDimLinePoint(dimPt2);
        break;

    case 2:
        dimIndex1 = 5;
        dimPt1 = mCenter + (0.5 * mHeight + 0.5 * dimScale) * vertDir;
        pAlnDim1->setXLine1Point(pt1);
        pAlnDim1->setXLine2Point(pt2);
        pAlnDim1->setDimLinePoint(dimPt1);

        dimIndex2 = 6;
        dimPt2 = mCenter - (0.5 * mWidth + 0.5 * dimScale) * mHorizDir;
        pAlnDim2->setXLine1Point(pt2);
        pAlnDim2->setXLine2Point(pt3);
        pAlnDim2->setDimLinePoint(dimPt2);
        break;

    case 3:
        dimIndex1 = 7;
        dimPt1 = mCenter - (0.5 * mWidth + 0.5 * dimScale) * mHorizDir;
        pAlnDim1->setXLine1Point(pt2);
        pAlnDim1->setXLine2Point(pt3);
        pAlnDim1->setDimLinePoint(dimPt1);

        dimIndex2 = 8;
        dimPt2 = mCenter - (0.5 * mHeight + 0.5 * dimScale) * vertDir;
        pAlnDim2->setXLine1Point(pt3);
        pAlnDim2->setXLine2Point(pt4);
        pAlnDim2->setDimLinePoint(dimPt2);
        break;

    case 4:
        dimIndex1 = 9;
        dimPt1 = mCenter - (0.5 * mHeight + 0.5 * dimScale) * vertDir;
        pAlnDim1->setXLine1Point(pt3);
        pAlnDim1->setXLine2Point(pt4);
        pAlnDim1->setDimLinePoint(dimPt1);

        dimIndex2 = 10;
        dimPt2 = mCenter + (0.5 * mWidth + 0.5 * dimScale) * mHorizDir;
        pAlnDim2->setXLine1Point(pt4);
        pAlnDim2->setXLine2Point(pt1);
        pAlnDim2->setDimLinePoint(dimPt2);
        break;
    }
	unsigned int ibitFlags = AcDbDimData::kDimFocal & ~AcDbDimData::kDimEditable ;
    AcDbDimData *dimData1 = new AcDbDimData(pAlnDim1);
    AppData *pDimAppData1 = new AppData(dimIndex1, dimScale);
    dimData1->setAppData(pDimAppData1);
    dimData1->setOwnerId(objId);
    dimData1->setDimFocal(true);
	  //dimData1->setBitFlags(ibitFlags);	
    dimData1->setDimEditable(false);
	dimData1->setDimValueFunc(AcRectangle::setDimValueCbackFunc);

    AcDbDimData *dimData2 = new AcDbDimData(pAlnDim2);
    AppData *pDimAppData2 = new AppData(dimIndex2, dimScale);
    dimData2->setAppData(pDimAppData2);
    dimData2->setOwnerId(objId);
	dimData2->setDimFocal(true);
    dimData2->setDimEditable(false);
	dimData2->setDimHideIfValueIsZero(true);
	dimData2->setDimValueFunc(setDimValueCbackFunc);

    dimDataArr.append(dimData1);
    dimDataArr.append(dimData2);

    if(pAppData) {
        pAppData->resetDimData();
        pAppData->appendDimData(dimData1);
        pAppData->appendDimData(dimData2);
    }
}

AcGeVector3d  
AcRectangle::setDimValueCbackFunc(AcDbDimData* pThis, 
                                  AcDbEntity* pEnt, 
                                  double value,
								  const AcGeVector3d& offset)
{
    if ((pThis == NULL) || (pEnt == NULL))
        return offset;
	
    pEnt->assertWriteEnabled();

    AppData *pDimAppData = (AppData*)pThis->appData();
    if (pDimAppData == NULL)
        return offset;

    int dimId = pDimAppData->index();
    if ((dimId < 1) || (dimId > 10))
        return offset;

    AcRectangle *pRect = AcRectangle::cast(pEnt);
    if (pRect == NULL)
        return offset;

    AcGePoint3d pt1, pt2, pt3, pt4, dimPt;
    AcGeVector3d diaVec;
    AcGeVector3d mHorizDir = pRect->horizDir();
    AcGeVector3d mNormal = pRect->normal();
    AcGeVector3d vertDir = mNormal.crossProduct(mHorizDir);
    AcGePoint3d mCenter = pRect->center();
    double mWidth = pRect->width();
    double mHeight = pRect->height();
    pt1 = mCenter + 0.5 * mWidth * mHorizDir + 0.5 * mHeight * vertDir;
    pt2 = mCenter - 0.5 * mWidth * mHorizDir + 0.5 * mHeight * vertDir;
    pt3 = mCenter - 0.5 * mWidth * mHorizDir - 0.5 * mHeight * vertDir;
    pt4 = mCenter + 0.5 * mWidth * mHorizDir - 0.5 * mHeight * vertDir;

    switch (dimId) {
    case 1:
        mCenter = mCenter + value * mHorizDir;
        pRect->setCenter(mCenter);
        break;

    case 2:
        mCenter = mCenter + value * vertDir;
        pRect->setCenter(mCenter);
        break;
        
    case 3:
        pt1 = pt2 + value * mHorizDir;
        diaVec = pt1 - pt3;
        mCenter = pt3 + 0.5 * diaVec;
        mWidth = fabs(diaVec.dotProduct(mHorizDir));
        mHeight = fabs(diaVec.dotProduct(vertDir));
        pRect->setCenter(mCenter);
        pRect->setWidth(mWidth);
        pRect->setHeight(mHeight);
        break;

    case 4:
        pt1 = pt4 + value * vertDir;
        diaVec = pt1 - pt3;
        mCenter = pt3 + 0.5 * diaVec;
        mWidth = fabs(diaVec.dotProduct(mHorizDir));
        mHeight = fabs(diaVec.dotProduct(vertDir));
        pRect->setCenter(mCenter);
        pRect->setWidth(mWidth);
        pRect->setHeight(mHeight);
        break;

    case 5:
        pt2 = pt1 - value * mHorizDir;
        diaVec = pt2 - pt4;
        mCenter = pt4 + 0.5 * diaVec;
        mWidth = fabs(diaVec.dotProduct(mHorizDir));
        mHeight = fabs(diaVec.dotProduct(vertDir));
        pRect->setCenter(mCenter);
        pRect->setWidth(mWidth);
        pRect->setHeight(mHeight);
        break;

    case 6:
        pt2 = pt3 + value * vertDir;
        diaVec = pt2 - pt4;
        mCenter = pt4 + 0.5 * diaVec;
        mWidth = fabs(diaVec.dotProduct(mHorizDir));
        mHeight = fabs(diaVec.dotProduct(vertDir));
        pRect->setCenter(mCenter);
        pRect->setWidth(mWidth);
        pRect->setHeight(mHeight);
        break;

    case 7:
        pt3 = pt2 - value * vertDir;
        diaVec = pt3 - pt1;
        mCenter = pt1 + 0.5 * diaVec;
        mWidth = fabs(diaVec.dotProduct(mHorizDir));
        mHeight = fabs(diaVec.dotProduct(vertDir));
        pRect->setCenter(mCenter);
        pRect->setWidth(mWidth);
        pRect->setHeight(mHeight);
        break;

    case 8:
        pt3 = pt4 - value * mHorizDir;
        diaVec = pt3 - pt1;
        mCenter = pt1 + 0.5 * diaVec;
        mWidth = fabs(diaVec.dotProduct(mHorizDir));
        mHeight = fabs(diaVec.dotProduct(vertDir));
        pRect->setCenter(mCenter);
        pRect->setWidth(mWidth);
        pRect->setHeight(mHeight);
        break;

    case 9:
        pt4 = pt3 + value * mHorizDir;
        diaVec = pt4 - pt2;
        mCenter = pt2 + 0.5 * diaVec;
        mWidth = fabs(diaVec.dotProduct(mHorizDir));
        mHeight = fabs(diaVec.dotProduct(vertDir));
        pRect->setCenter(mCenter);
        pRect->setWidth(mWidth);
        pRect->setHeight(mHeight);
        break;

    case 10:
        pt4 = pt1 - value * vertDir;
        diaVec = pt4 - pt2;
        mCenter = pt2 + 0.5 * diaVec;
        mWidth = fabs(diaVec.dotProduct(mHorizDir));
        mHeight = fabs(diaVec.dotProduct(vertDir));
        pRect->setCenter(mCenter);
        pRect->setWidth(mWidth);
        pRect->setHeight(mHeight);
        break;
	}

    return offset;
}


bool 
AcRectangle::gripWorldDrawFunc(AcDbGripData* pThis,
                               AcGiWorldDraw* pWd,
                               const AcDbObjectId& entId, 
                               AcDbGripOperations::DrawType type, 
                               AcGePoint3d* cursor)
{
	static const Adesk::UInt16 kYellow =50;
    AcGeVector3d gripNormal(0, 0, 1);
	AcGePoint3d point = pThis->gripPoint();
	pWd->subEntityTraits().setFillType(kAcGiFillAlways);
	pWd->subEntityTraits().setThickness(3);
	pWd->subEntityTraits().setColor(kYellow);
	pWd->geometry().circle(point,0.2, gripNormal);
	return true;
}

void
AcRectangle::gripStatus(const AcDb::GripStat status)
{
    switch (status) {
	case AcDb::kDimDataToBeDeleted:
        break;

    default:
        break;
	}
}


//===================================================================
double userToLocalAngle(const AcGeVector3d& normal,
                        const AcGeVector3d& ucsXdir)
{
    AcGeMatrix3d wcsToLcs = AcGeMatrix3d::worldToPlane(normal);
    AcGeVector3d xDir = ucsXdir;
    xDir.transformBy(wcsToLcs);
    double angle = atan2(xDir.y, xDir.x);
    return angle;
    //return fixAngle(angle);
} 
 