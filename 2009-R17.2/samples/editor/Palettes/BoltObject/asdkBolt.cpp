//
//
// (C) Copyright 2003-2008 by Autodesk, Inc. 
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
/////////////////////////////////////////////
// asdkBolt custom object.
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

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

    alignment=AcGeVector3d(1,0,0); // Draw on XY plane
    position=AcGePoint3d(0,0,0);

    // Default Values...
    headSides=6;
    headHeight=2.0f;
    shaftLength=10.0f;
    threadLength=3.0f;
    threadWidth=.2f;
    headDiameter=5.0f;
    shaftDiameter=3.0f;
    calculatePnts();
    _tcscpy_s(materialName, _countof(materialName),_T("Stainless"));
    _tcscpy_s(partNumber, _countof(partNumber),_T("unassigned"));
}

asdkBolt::~asdkBolt()
{
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
        pFiler->readItem(&alignment);
        pFiler->readItem(&position);
        TCHAR *pString=NULL;
        pFiler->readString(&pString);
        _tcscpy_s(partNumber, _countof(partNumber),pString);
        pFiler->readString(&pString);
        _tcscpy_s(materialName, _countof(materialName),pString);
        calculatePnts();// Calculate the bolt when the parameters are reinstated.
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
    pFiler->writeItem(alignment);
    pFiler->writeItem(position);
    pFiler->writeString(partNumber);
    pFiler->writeString(materialName);
    return pFiler->filerStatus();
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
                                           Adesk::GsMarker gsSelectionMark,
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

    // Transform all points
    for(int i = 0; i < 5; i ++ ) {
        headPnts[i].transformBy(xform);
    }
    for(int i = 0; i < 4; i ++ ) {
        shaftPnts[i].transformBy(xform);
    }
    for(int i = 0; i < 2; i ++ ) {
        thread[i].transformBy(xform);
    }

    // transform position
    position.transformBy(xform);

    return Acad::eOk;
}


Acad::ErrorStatus asdkBolt::subClose()
{
    return AcDbObject::subClose();
}


Adesk::Boolean asdkBolt::worldDraw(AcGiWorldDraw* mode)
{
    assertReadEnabled();

    drawHead(mode);
    drawShaft(mode);
    drawThread(mode);

    return AcDbEntity::worldDraw(mode);
}

void asdkBolt::list() const
{
    assertReadEnabled();
    // TODO: implement this function.

    AcDbEntity::list();
}

const CLSID CLSID_Bolt = {0x9CB206D1,0x6D16,0x4514,{0xB1,0xFA,0x53,0x6B,0x34,0xCF,0x5D,0x74}};

Acad::ErrorStatus asdkBolt::getClassID(CLSID* pClsid) const
{
    assertReadEnabled();
    // TODO: implement this function.
    *pClsid = CLSID_Bolt;
    return Acad::eOk;

}


void asdkBolt::calculatePnts()
{
    // find vector on XY plane perpendicular to alignment
    AcGeVector3d vec, normal(0,0,1);
    vec = normal.crossProduct(alignment);
    vec.normalize();

    // calculate head vertices
    headPnts[0] = position + vec * headDiameter/2;
    headPnts[1] = headPnts[0] + (alignment.normalize()) * headHeight;
    headPnts[2] = headPnts[1] - vec * headDiameter;
    headPnts[3] = headPnts[2] - alignment * headHeight;
    headPnts[4] = headPnts[0];

    // calculate shaft vertices
    shaftPnts[0] = position + vec * shaftDiameter/2 + (alignment.normalize()) * headHeight;
    shaftPnts[1] = shaftPnts[0] + alignment * shaftLength;
    shaftPnts[2] = shaftPnts[1] - vec * shaftDiameter;
    shaftPnts[3] = shaftPnts[2] - alignment * shaftLength;

    // calculate vertices of single thread
    thread[0] = position + 
                vec * shaftDiameter/2 + 
                (alignment.normalize()) * (headHeight + shaftLength);
    thread[1] = thread[0] - vec * shaftDiameter;

}

void asdkBolt::drawHead(AcGiWorldDraw* wD)
{	
    wD->geometry().polyline(5, headPnts);
}

void asdkBolt::drawShaft(AcGiWorldDraw* wD)
{
    wD->geometry().polyline(4, shaftPnts);
}

void asdkBolt::drawThread(AcGiWorldDraw* wD)
{
    int n_thread = (int)(threadLength / threadWidth);
    
    AcGePoint3d tmp[2];
    tmp[0] = thread[0];
    tmp[1] = thread[1];

    // calculate and draw each thread
    for(int i = 0; i <= n_thread; i++) {
       wD->geometry().polyline(2, tmp);
       tmp[0] = tmp[0] - alignment * threadWidth;
       tmp[1] = tmp[1] - alignment * threadWidth;

    }
}

    // get methods
    AcGeVector3d asdkBolt::getAlignment() const  
    {
        assertReadEnabled();
        return alignment;
    }

    double asdkBolt::getHeadDiameter() const
    {
        assertReadEnabled();
        return headDiameter;
    }

    double asdkBolt::getHeadHeight() const
    {
        assertReadEnabled();
        return headHeight;
    }

    int asdkBolt::getHeadSides()    const  
    {
        assertReadEnabled();
        return headSides;
    }

    // Material name
    ///

    AcGePoint3d	asdkBolt::getPosition()      const  
    {
        assertReadEnabled();
        return position;
    }

    double asdkBolt::getShaftDiameter() const
    {
        assertReadEnabled();
        return shaftDiameter;
    }

    double asdkBolt::getShaftLength() const
    {
        assertReadEnabled();
        return shaftLength;
    }

    double asdkBolt::getThreadLength() const
    {
        assertReadEnabled();
        return threadLength;
    }

    double asdkBolt::getThreadWidth() const
    {
        assertReadEnabled();
        return threadWidth;
    }

    //////////////////////////////////////////////////////////
    // Set Methods
    //////////////////////////////////////////////////////////

    void asdkBolt::setAlignment(AcGeVector3d& align)      
    {
        assertWriteEnabled();
        alignment = align.normalize();
        calculatePnts();
    }

    void asdkBolt::setHeadDiameter(double hD) 
    {
        assertWriteEnabled();
        headDiameter = hD;
        calculatePnts();
    }

    void asdkBolt::setHeadHeight(double hH) 
    {
        assertWriteEnabled();
        headHeight = hH;
        calculatePnts();
    }

    void asdkBolt::setHeadSides(int hS) 
    {
        assertWriteEnabled();
        headSides = hS;
    }

    void asdkBolt::setMaterialName(TCHAR *mN)
    {
        assertWriteEnabled();
        _tcscpy_s(materialName, _countof(materialName),mN);
    }

    void asdkBolt::getMaterialName(TCHAR *mN, size_t sizemN)
    {
        assertReadEnabled();
        _tcscpy_s(mN,sizemN,materialName);
    }

    void asdkBolt::setPosition(AcGePoint3d& pos)        
    {
        assertWriteEnabled();
        position = pos;
        calculatePnts();
    }

    void asdkBolt::setShaftDiameter(double sD) 
    {
        assertWriteEnabled();
        shaftDiameter = sD;
        calculatePnts();
    }

    void asdkBolt::setShaftLength(double sL) 
    {
        assertWriteEnabled();
        shaftLength = sL;
        calculatePnts();
    }

    void asdkBolt::setPartNumber(TCHAR *pN)
    {
        assertWriteEnabled();
        _tcscpy_s(partNumber, _countof(partNumber),pN);
    }

    void asdkBolt::getPartNumber(TCHAR *pN, size_t sizepN)
    {
        assertReadEnabled();
        _tcscpy_s(pN,sizepN,partNumber);
    }

    void asdkBolt::setThreadLength(double tL) 
    {
        assertWriteEnabled();
        threadLength = tL;
        calculatePnts();
    }

    void asdkBolt::setThreadWidth(double tW) 
    {
        assertWriteEnabled();
        threadWidth = tW;
        calculatePnts();
    }

