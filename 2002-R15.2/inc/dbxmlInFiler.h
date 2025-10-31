//
// (C) Copyright 2000 by Autodesk, Inc.
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
// DESCRIPTION: Definition of AcDbXmlInFiler

#pragma once

#include "dbmain.h"

#include "dbapserv.h"
#include "gemat3d.h"
#include "gept3dar.h"
#include "geell3d.h"
#include "gesent3d.h"

#include "acutXMLDOMNode.h"
#include "acutXMLDOMDocument.h"

class AcDbXmlSystemInternals;


class AcDbXmlInFiler
{
public:
    AcDbXmlInFiler(
        AcDbDatabase* pDb,
        const char* xmlFilename,
        const char* logFilename,
        AcDbHostApplicationProgressMeter* pMeter);
   ~AcDbXmlInFiler();

    AcDbDatabase*       database() const;
    Acad::ErrorStatus   filerStatus() const;
    void                resetFilerStatus();

    // XML DOM methods
    AcUtXMLDOMNode*     getCurrentNode();
    AcUtString          getCurrentNodeName() const;
    void                setCurrentNode(AcUtXMLDOMNode* pNode);
    bool selectNode(const AcUtXMLDOMNode* pFromNode,
        const AcUtString& forNodeName,
        AcUtXMLDOMNode*& pFoundNode);
    Acad::ErrorStatus   readAttribute(const AcUtXMLDOMElement* pElement,
        const AcUtString& attName, AcUtString& value);
    Acad::ErrorStatus   readBoolAttribute(const AcUtXMLDOMElement* pElement,
        const AcUtString& attName, bool& value);
    Acad::ErrorStatus   readAttribute(const AcUtXMLDOMElement* pElement,
        const AcUtString& attName, bool& value);
    Acad::ErrorStatus   readDoubleAttribute(const AcUtXMLDOMElement* pElement,
        const AcUtString& attName, double& value);
    Acad::ErrorStatus   readAttribute(const AcUtXMLDOMElement* pElement,
        const AcUtString& attName, double& value);
    Acad::ErrorStatus   readIntAttribute(const AcUtXMLDOMElement* pElement,
        const AcUtString& attName, int& value);
    Acad::ErrorStatus   readAttribute(const AcUtXMLDOMElement* pElement,
        const AcUtString& attName, int& value);
    Acad::ErrorStatus   readUI1Attribute(const AcUtXMLDOMElement* pElement,
        const AcUtString& attName, unsigned char& value);
    Acad::ErrorStatus   readUI2Attribute(const AcUtXMLDOMElement* pElement,
        const AcUtString& attName, unsigned short int& value);
    Acad::ErrorStatus   readAttribute(const AcUtXMLDOMElement* pElement,
        const AcUtString& attName, unsigned short int& value);
    Acad::ErrorStatus   readUI4Attribute(const AcUtXMLDOMElement* pElement,
        const AcUtString& attName, unsigned long int& value);
    Acad::ErrorStatus   readAttribute(const AcUtXMLDOMElement* pElement,
        const AcUtString& attName, unsigned long int& value);
    Acad::ErrorStatus   readDateAttribute(const AcUtXMLDOMElement* pElement,
            const AcUtString& attName, AcDbDate &dateTime);
    Acad::ErrorStatus   readAttribute(const AcUtXMLDOMElement* pElement,
            const AcUtString& attName, AcDbDate &dateTime);
    Acad::ErrorStatus   readBinaryAttribute(const AcUtXMLDOMElement* pElement,
        const AcUtString& attName, ads_binary& value);
    Acad::ErrorStatus   readAttribute(const AcUtXMLDOMElement* pElement,
        const AcUtString& attName, ads_binary& value);

    // DesignXML methods
    //
    Acad::ErrorStatus   readDataString(const AcUtString& tagName,
        AcUtString& str);
    Acad::ErrorStatus   readLength(const AcUtString& tagName, double& length);
    Acad::ErrorStatus   readAngle(const AcUtString& tagName, double& angle);
    Acad::ErrorStatus   readPoint(const AcUtString& tagName, AcGePoint3d& pt);
    Acad::ErrorStatus   readPoint(const AcUtString& tagName, AcGePoint2d& pt);
    Acad::ErrorStatus   readVector(const AcUtString& tagName, AcGeVector3d& vec);
    Acad::ErrorStatus   readVector(const AcUtString& tagName, AcGeVector2d& vec);
    Acad::ErrorStatus   readScale(const AcUtString& tagName, AcGeScale3d& scale);
    Acad::ErrorStatus   readMatrix3x3(const AcUtString& tagName, AcGeMatrix3d& mat);
    Acad::ErrorStatus   readLinearCoordinateTransform(const AcUtString& tag, 
        AcGeMatrix3d& matrix);
    Acad::ErrorStatus   readView(bool& bIsPlan, bool& bIsPerspective, 
        bool& bIsFrontClipped, bool& bIsBackClipped, bool& bIsTwisted,
        double& height, double& aspectRatio, AcGePoint3d& targetPoint, 
        AcGeVector3d& direction, double& perspectiveViewingAngle, 
        double& frontClip, double& backClip, double& worldZDisplayAngle);
    Acad::ErrorStatus   readColor(int& colorIndex);
    Acad::ErrorStatus   readTrueColor(short& v1, short& v2, short& v3,
        bool& bHasAlpha, short& alpha, AcUtString& colorSpace);
    Acad::ErrorStatus   readLink(AcUtString& link);

    // DesignXML entities
    Acad::ErrorStatus readLineSegment(
        AcGePoint3d& startPoint, AcGePoint3d& endPoint);
    Acad::ErrorStatus readLine(
        AcGePoint3d& pointOnLine, AcGeVector3d& direction);
    Acad::ErrorStatus readRay(
        AcGePoint3d& pointOnLine, AcGeVector3d& direction);
    Acad::ErrorStatus readCircle(AcGePoint3d& centerPt,
        double& radius, AcGeVector3d& normal);
    Acad::ErrorStatus readArc(AcGePoint3d& centerPt, double& radius,
        AcGeVector3d& normal, AcGeVector3d& startVector,
        double& sweepAngle, double& startAngle, double& endAngle);
    Acad::ErrorStatus readEllipse(double& minorMajorRatio, 
        double& startParameter, double& endParameter,
        AcGePoint3d& centerPt, AcGeVector3d& normal,
        AcGeVector3d& majorAxis);
    Acad::ErrorStatus readPolyline(
        AcGePoint3dArray& vertices, bool& bIsClosed);
    Acad::ErrorStatus readBSplineCurve(bool &isClosed, bool &isPeriodic,
        bool &isRational, int &degree, int &numberOfControlPoints,
        int &numberOfKnots, double &knotTol, double &controlPtTol,
        double &fitTol, AcGePoint3dArray &controlPoints,
        AcGeDoubleArray &knots, AcGeDoubleArray &weights);


    // AcDbXml methods
    Acad::ErrorStatus   readDatabase();
    Acad::ErrorStatus   readBool(const AcUtString& tagName, bool& value);
    Acad::ErrorStatus   readShort(const AcUtString& tagName, 
        const AcUtString& attName, short int& value);
    Acad::ErrorStatus   readLong(const AcUtString& tagName, 
        const AcUtString& attName, long int& value);
    Acad::ErrorStatus   readUInt8(const AcUtString& tagName, 
        const AcUtString& attName, Adesk::UInt8& value);
    Acad::ErrorStatus   readInt16(const AcUtString& tagName, 
        const AcUtString& attName, Adesk::Int16& value);
    Acad::ErrorStatus   readUInt16(const AcUtString& tagName, 
        const AcUtString& attName, Adesk::UInt16& value);
    Acad::ErrorStatus   readInt32(const AcUtString& tagName, 
        const AcUtString& attName, Adesk::Int32& value);
    Acad::ErrorStatus   readUInt32(const AcUtString& tagName, 
        const AcUtString& attName, Adesk::UInt32& value);
    Acad::ErrorStatus   readDouble(const AcUtString& tagName, 
        const AcUtString& attName, double& value);
    Acad::ErrorStatus readBinaryChunk(const AcUtString& tag,
        ads_binary& value);
    Acad::ErrorStatus readXDataElement(const AcUtString& tagName, resbuf*& pRb);
    Acad::ErrorStatus   readSymbolName(AcUtString& str);
    Acad::ErrorStatus   readThickness(double& thickness);
    Acad::ErrorStatus   readNormalVector(AcGeVector3d& normal);
    Acad::ErrorStatus readObjectId(const AcUtString& tag, AcDbObjectId& oId);
    Acad::ErrorStatus readObjectIds(const AcUtString& tag, 
        AcDbObjectIdArray& ids);
    Acad::ErrorStatus convertXmlIdToObjectId(const AcUtString& xmlId, 
        bool bCreateIfNotFound, AcDbObjectId& oId) const;

private:
    void* mpImpl;
    friend class AcDbXmlSystemInternals;
};
