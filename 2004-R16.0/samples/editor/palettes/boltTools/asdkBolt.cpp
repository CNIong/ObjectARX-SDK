//
//
// (C) Copyright 2002 by Autodesk, Inc. 
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
//
/////////////////////////////////////////////
// asdkBolt custom object.

#include "StdAfx.h"
#include "StdArx.h"
#include "dbproxy.h"
#include "geassign.h"
#include "acgi.h"

#define VERSION_ASDKBOLT 1


//{{AFX_ARX_MACRO
ACRX_DXF_DEFINE_MEMBERS(asdkBolt, AcDbEntity,
						 AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,
                        AcDbProxyEntity::kNoOperation,
						 ASDKBOLT, asdkboltObject);
//}}AFX_ARX_MACRO


// Constructor / Destructor

asdkBolt::asdkBolt()
{
	//{{AFX_ARX_DATA_INIT(asdkBolt)
	//}}AFX_ARX_DATA_INIT

	pHead=NULL;
	pShaft=NULL;
	alignment=AcGeVector3d(0,0,1);
	position=AcGePoint3d(0,0,0);

	pHead=new AcDb3dSolid;
	pShaft=new AcDb3dSolid;

	// Default Values...
	headSides=6;
	headHeight=2.0f;
	shaftLength=10.0f;
	threadLength=3.0f;
	threadWidth=.2f;
	headDiameter=5.0f;
	shaftDiameter=3.0f;

	createSolids();

}

asdkBolt::~asdkBolt()
{
	delete pHead;
	delete pShaft;
}


Acad::ErrorStatus asdkBolt::dwgInFields(AcDbDwgFiler* pFiler)
{
	assertWriteEnabled();
	Acad::ErrorStatus es;

	// Call dwgInFields from AcDbEntity
	if ((es = AcDbEntity::dwgInFields(pFiler)) != Acad::eOk) {
		return es;
	}

	// Read version number.
	Adesk::UInt16 version;
	pFiler->readItem(&version);
	if (version > VERSION_ASDKBOLT)
		return Acad::eMakeMeProxy;

	// Read the data members.
	switch (version)
	{
	case (1):
		pFiler->readItem(&headDiameter);
		pFiler->readItem(&headHeight);
		pFiler->readInt32((Adesk::Int32*)&headSides);
		pFiler->readItem(&shaftDiameter);
		pFiler->readItem(&shaftLength);
		pFiler->readItem(&threadLength);
		pFiler->readItem(&threadWidth);
		pFiler->readBytes(&transformation.entry,128);
		pFiler->readItem(&alignment);
		pFiler->readItem(&position);

		pHead->dwgInFields(pFiler);
		pShaft->dwgInFields(pFiler);
						
		break;
	}


	return pFiler->filerStatus();
}

Acad::ErrorStatus asdkBolt::dwgOutFields(AcDbDwgFiler* pFiler) const
{
	assertReadEnabled();
	Acad::ErrorStatus es;

	// Call dwgOutFields from AcDbEntity
	if ((es = AcDbEntity::dwgOutFields(pFiler)) != Acad::eOk) {
		return es;
	}

	// Write version number.
	pFiler->writeItem((Adesk::UInt16) VERSION_ASDKBOLT);

	// Write the data members.
	pFiler->writeItem(headDiameter);
	pFiler->writeItem(headHeight);
	pFiler->writeInt32(headSides);
	pFiler->writeItem(shaftDiameter);
	pFiler->writeItem(shaftLength);
	pFiler->writeItem(threadLength);
	pFiler->writeItem(threadWidth);
	pFiler->writeBytes(transformation.entry,128);
	pFiler->writeItem(alignment);
	pFiler->writeItem(position);

	pHead->dwgOutFields(pFiler);
	pShaft->dwgOutFields(pFiler);

	if(visibility()==AcDb::kVisible)
		int j=1;
	char *layername;
	layername=layer();
    
	int color=colorIndex();
	color=pHead->colorIndex();
	color=pShaft->colorIndex();

	return pFiler->filerStatus();
}

Acad::ErrorStatus asdkBolt::moveGripPointsAt(const AcDbIntArray& indices,
                                             const AcGeVector3d& offset)
{
	assertWriteEnabled();
	// TODO: implement this function.

	return AcDbEntity::moveGripPointsAt(indices, offset);
}

Acad::ErrorStatus asdkBolt::getGripPoints(AcGePoint3dArray& gripPoints,
                                          AcDbIntArray& osnapModes,
                                          AcDbIntArray& geomIds) const
{
	assertReadEnabled();
	gripPoints.append(position);
	return Acad::eOk;
}

Acad::ErrorStatus asdkBolt::getOsnapPoints(AcDb::OsnapMode osnapMode,
                                           int gsSelectionMark,
                                           const AcGePoint3d& pickPoint,
                                           const AcGePoint3d& lastPoint,
                                           const AcGeMatrix3d& viewXform,
                                           AcGePoint3dArray& snapPoints,
                                           AcDbIntArray& geomIds) const
{
	assertReadEnabled();
	snapPoints.append(position);
	return Acad::eOk;
}

Acad::ErrorStatus asdkBolt::transformBy(const AcGeMatrix3d& xform)
{
	assertWriteEnabled();
	
	pHead->transformBy(xform);
	pShaft->transformBy(xform);
	
	transformation=xform*transformation;
	position.transformBy(xform);
	alignment.transformBy(xform);
	return Acad::eOk;
}


Acad::ErrorStatus asdkBolt::subClose()
{
	if(isWriteEnabled())
	{
		if(pHead)
			//pHead->setColorIndex(colorIndex());
			pHead->setColorIndex(1);
		if(pShaft)
			//pShaft->setColorIndex(colorIndex());
			pShaft->setColorIndex(1);
	}
	return Acad::eOk;
}

Adesk::Boolean asdkBolt::worldDraw(AcGiWorldDraw* mode)
{
	acutPrintf("\nworldDraw\n");
	assertReadEnabled();
	if(pHead)
		pHead->worldDraw(mode);
	if(pShaft)
		pShaft->worldDraw(mode);

	AcGeVector3d vec=alignment;
	vec.normalize();// Don't normalize alignment, or we'll get out of sync with OPM
	
	for(int c=0;c<(int)(threadLength/threadWidth);c++)
		mode->geometry().circle(position+vec*(headHeight+shaftLength-threadWidth*c),
			shaftDiameter/2+.05,vec);
	return AcDbEntity::worldDraw(mode);
}

void asdkBolt::list() const
{
	assertReadEnabled();
	// TODO: implement this function.

	AcDbEntity::list();
}


void asdkBolt::createSolids()
{
	Acad::ErrorStatus es;
	if(pHead) {
		delete pHead;
		pHead = new AcDb3dSolid;
	}
	if(pShaft) {
		delete pShaft;
		pShaft = new AcDb3dSolid;
	}

	pHead->setDatabaseDefaults();
	pShaft->setDatabaseDefaults();
	
	// Create the Bolt Head
	// Perimeter = 2n r sin(Pi/n)=2n r tan(Pi/n)
	double edgeLength=(2*headSides * headDiameter * sin(PI/headSides))/headSides;
	double inscribedDiameter=sqrt(pow(edgeLength/2,2)+pow(headDiameter/2,2));
	double vertexAngle=PI2/headSides;

	AcDb3dPolyline *pPoly=new AcDb3dPolyline;
	pPoly->setDatabaseDefaults();
	double startAngle=vertexAngle/2;
	for(int c=0;c<headSides;c++)
	{
		AcDb3dPolylineVertex *pVertex=new AcDb3dPolylineVertex(AcGePoint3d(sin(startAngle)*inscribedDiameter,cos(startAngle)*inscribedDiameter,0));
		pPoly->appendVertex(pVertex);
		startAngle+=vertexAngle;
	}
	pPoly->makeClosed();
	
	AcDbVoidPtrArray curves,regions,shaftRegions,shaftCurves;
	curves.append(pPoly);

	// Error here!!
	es=AcDbRegion::createFromCurves(curves,regions);// Create the region...note:	static member function.
	es=pHead->extrude((AcDbRegion*)(regions[0]),headHeight,0);
	//delete regions[0];
	delete pPoly;
		
	// Now make the shaft...
	AcDbCircle *pCircle=new AcDbCircle(AcGePoint3d(0,0,headHeight),AcGeVector3d(0,0,1),shaftDiameter/2);
	shaftCurves.append(pCircle);
	es=AcDbRegion::createFromCurves(shaftCurves,shaftRegions);// Create the region...note:	static member function.
	es=pShaft->extrude((AcDbRegion*)(shaftRegions[0]),shaftLength,0);
	//delete shaftRegions[0];
	delete pCircle;
}


const CLSID CLSID_Bolt = {0x9CB206D1,0x6D16,0x4514,{0xB1,0xFA,0x53,0x6B,0x34,0xCF,0x5D,0x74}};

Acad::ErrorStatus asdkBolt::getClassID(CLSID* pClsid) const
{
	assertReadEnabled();
	// TODO: implement this function.
	*pClsid = CLSID_Bolt;
	return Acad::eOk;

}


void asdkBolt::updateSolids()
{
	pHead->transformBy(transformation);
	pShaft->transformBy(transformation);
}
