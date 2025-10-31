//
// (C) Copyright 2002-2008 by Autodesk, Inc. 
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

//-----------------------------------------------------------------------------
//----- AsdkTransientEntity.cpp : Implementation of AsdkTransientEntity
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "AsdkTransientEntity.h"
#include "atlimage.h"
extern void colorToStr(int color, CString& str, bool convertStandard);
extern void dxfToStr(const resbuf* rb, CString& dxfCodeStr, CString& valueStr);
extern void FindPixleRatio(double &dX);
BOOL GetTooltipDataFromBlockReference(AcDbBlockReference *pRef, CString &strImageName, CString &strImageDescription);



AsdkTransientEntity::AsdkTransientEntity () 
{
	m_pTooltiptext = new AcDbMText();
	m_tooltipTextStyle = ::AcDbObjectId::kNull;
	m_pTooltiptext->setDatabaseDefaults();
}

AsdkTransientEntity::~AsdkTransientEntity ()
{
	if(m_pTooltiptext != NULL)
		delete m_pTooltiptext;

	m_pTooltiptext = NULL;
}

Adesk::Boolean AsdkTransientEntity::isPersistent(void) const
{
    return Adesk::kFalse;
}

AcDbObjectId AsdkTransientEntity::id(void) const
{
    return AcDbObjectId::kNull;
}

// Graphics cache
void AsdkTransientEntity::setGsNode(AcGsNode * gsnode)
{
    mpGsNode = gsnode;
}

AcGsNode* AsdkTransientEntity::gsNode(void) const
{
    return mpGsNode;
}

double AsdkTransientEntity::findHeightOfText(const AcGeMatrix3d &mat)
{
	AcGePoint3d point1;
	AcGePoint3d point2;

	struct resbuf rb;
	acedGetVar(L"SCREENSIZE", &rb);

	acedCoordFromPixelToWorld(CPoint(10,0), asDblArray(point1));
	acedCoordFromPixelToWorld(CPoint(10, rb.resval.rpoint[1]), asDblArray(point2));

	point2.transformBy(mat);
	point1.transformBy(mat);
	double dHeight = ::acutDistance(asDblArray(point2),asDblArray(point1)) / (rb.resval.rpoint[1] - 10);
	dHeight = dHeight * 10;
	return dHeight;
}

Adesk::UInt32 AsdkTransientEntity::setAttributes(AcGiDrawableTraits *traits)
{
	return AcGiDrawable::kDrawableBlockDependentViewportDraw;
}

Adesk::Boolean AsdkTransientEntity::worldDraw (AcGiWorldDraw *mode)
{
	//------ Returning Adesk::kFalse here will force viewportDraw() call
	return (Adesk::kFalse) ;
}
void AsdkTransientEntity::viewportDraw (AcGiViewportDraw *mode)
{
	if(m_entityObjectId == AcDbObjectId::kNull)
	{
		return;
	}
	AcDbEntity * pEnt = NULL;

	CString strImageName = _T("");
	CString strImageDescription = _T("");
	//Show the image with block reference
	if ( Acad::eOk != acdbOpenAcDbEntity(pEnt, m_entityObjectId, AcDb::kForRead))
	{
		return ;
	}

	::AcDbBlockReference *pRef = AcDbBlockReference::cast(pEnt);

	if(pRef == NULL)
	{
		pEnt->close();
		return;
	}

	if(GetTooltipDataFromBlockReference(pRef, strImageName, strImageDescription) == FALSE)
	{
		pRef->close();
		return ;
	}

	//try to load image
	CImage ObjectImage;
	HRESULT hr = ObjectImage.Load(strImageName);
	if(FAILED(hr))
	{
		pEnt->close();
		return ;
	}

	int nWidth = ObjectImage.GetWidth();
	int nHeight = ObjectImage.GetHeight();


	//Draw text below
	//get the hight of the text

	AcGeMatrix3d mat;
	mode->viewport().getEyeToModelTransform(mat);


	double dHeight = findHeightOfText(mat);
	double dRatio = 0;
	FindPixleRatio(dRatio);

	AcGePoint3d TextEndPoint;
	double dTotalDistance =  nWidth * dRatio;
	

	//Text insertion point
	AcGePoint3d point1;
	AcGePoint3dArray boundingBox;

	m_pTooltiptext->transformBy(mat);

	if(m_tooltipTextStyle != AcDbObjectId::kNull)
	{
		m_pTooltiptext->setTextStyle(m_tooltipTextStyle);
	}

	m_pTooltiptext->setUseBackgroundColor(false);
	m_pTooltiptext->setBackgroundFill(true);
	AcCmColor bkcolor;
	bkcolor.setRGB(173,255,214);
	m_pTooltiptext->setBackgroundFillColor(bkcolor);
	bkcolor.setRGB(0,0,0);
	m_pTooltiptext->setColor(bkcolor);
	m_pTooltiptext->setWidth(dTotalDistance);
	m_pTooltiptext->setTextHeight(dHeight);
	m_pTooltiptext->setBackgroundScaleFactor(1.5);
	m_pTooltiptext->setLocation (m_currentMousePoint);
	m_pTooltiptext->setContents(strImageDescription);
	m_pTooltiptext->getBoundingPoints(boundingBox);
	point1 = boundingBox.at(2);

	//get lower left cormer for image draw
	m_pTooltiptext->viewportDraw(mode);

	mode->viewport().getModelToEyeTransform(mat);
	m_pTooltiptext->transformBy(mat);

	//Draw the image
	AcGiViewportGeometry2 &newGeometry = (AcGiViewportGeometry2 &)mode->geometry();
	AcGiImageBGRA32 imageSource;

	AcGiPixelBGRA32 *pAcGiPixelBGRA32 = new AcGiPixelBGRA32[ObjectImage.GetHeight() * (ObjectImage.GetWidth() + 10)];
	AcGiPixelBGRA32 *pAcGiPixel = pAcGiPixelBGRA32;
	
	int nHeightIndex = 0;
	while(nHeightIndex < nHeight)
	{
		int nWidthIndex  = 0;
		while(nWidthIndex  < nWidth)
		{
			COLORREF pixleColor = ObjectImage.GetPixel(nWidthIndex, nHeightIndex);
			pAcGiPixelBGRA32->setRGBA(pixleColor);
			pAcGiPixelBGRA32++;
			nWidthIndex++;
		}

		//SET THE EXTRA WIDTH TO WHITE COLOR
		nWidthIndex = 0;
		COLORREF whiteColor = COLORREF(RGB(255,255,255));
		while(nWidthIndex < 10)
		{
			pAcGiPixelBGRA32->setRGBA(whiteColor);
			pAcGiPixelBGRA32++;
			nWidthIndex++;

		}
		nHeightIndex++;
	}

	AcGePoint3d DCSCurrentPoint;
	CPoint DevicePoint; 

	struct resbuf rb;
	acedGetVar(L"SCREENSIZE", &rb);
	double HeightInPixle = rb.resval.rpoint[1];

	acedCoordFromWorldToPixel(mode->viewport().acadWindowId(), asDblArray(point1), DevicePoint);
	DCSCurrentPoint.x = DevicePoint.x - (0.5 * 10); //10 PIXLE IS HEIGHT OF TEXT
	DCSCurrentPoint.y = HeightInPixle - DevicePoint.y - (0.5 * 10);
	DCSCurrentPoint.z = 0;

	imageSource.setImage(ObjectImage.GetWidth() + 10, ObjectImage.GetHeight(), pAcGiPixel);
    newGeometry.pushPositionTransform(kAcGiScreenPosition, AcGePoint2d(0, 0));
	Adesk::Boolean bool1 = newGeometry.image(imageSource,
                                             DCSCurrentPoint,
                                             AcGeVector3d(1.0 * imageSource.width(), 0, 0),
                                             AcGeVector3d(0, -1.0 * imageSource.height(), 0), AcGiGeometry::kTransparencyOff);
    newGeometry.popModelTransform();
	
	delete []pAcGiPixel;

	pEnt->close(); 

}


void AsdkTransientEntity::setPriviewEntityId(const AcDbObjectId &id)
{
	m_entityObjectId = id;
}


AcDbObjectId AsdkTransientEntity::getPriviewEntityId()
{
	return m_entityObjectId;
}

void AsdkTransientEntity::setCurrentMousePoint(const AcGePoint3d &point)
{
	m_currentMousePoint = point;
}

AcGePoint3d AsdkTransientEntity::getCurrentMousePoint()
{
	return m_currentMousePoint;
}


void AsdkTransientEntity::setViewportsForTransientGraphics(AcArray<int> viewportNumbers)
{
	m_viewportNumbers = viewportNumbers;
}


void AsdkTransientEntity::getViewportsForTransientGraphics(AcArray<int> &viewportNumbers)
{
	viewportNumbers = m_viewportNumbers;
}

void AsdkTransientEntity::setTooltipTextStyle(const AcDbObjectId &id)
{
	m_tooltipTextStyle = id;
}

AcDbObjectId AsdkTransientEntity::getTooltipTextStyle()
{
	return m_tooltipTextStyle;
}
