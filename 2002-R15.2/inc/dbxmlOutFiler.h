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
// DESCRIPTION: Definition of AcDbXmlOutFiler

#pragma once


#include "dbapserv.h"
#include "gemat3d.h"
#include "gept3dar.h"
#include "geell3d.h"
#include "gesent3d.h"

#include "acutXMLDOMNode.h"
#include "acutXMLDOMDocument.h"


class AcDbXmlOutFiler
{
public:
    AcDbXmlOutFiler(AcDbDatabase* pDb, const char* xmlFilename,
        const char* logFilename, AcDbHostApplicationProgressMeter* pMeter);
   ~AcDbXmlOutFiler();

    AcDbDatabase* database() const;
    bool isDefaulting() const;
    Acad::ErrorStatus filerStatus() const;
    void              resetFilerStatus();

    // XML DOM methods
    AcUtXMLDOMDocument* xmlDocument();
    AcUtXMLDOMNode* getCurrentNode();
    Acad::ErrorStatus appendNode(const AcUtXMLDOMNode* pNode);
    Acad::ErrorStatus pushNode(const AcUtXMLDOMNode*& pNode);
    Acad::ErrorStatus pushNode(const AcUtString& tag);
    Acad::ErrorStatus pushNode(const AcUtString& tag, AcUtXMLDOMNode*& pNode);
    Acad::ErrorStatus pushNode(const AcUtString& tag, 
        const AcUtString& nameSpaceURI, AcUtXMLDOMNode*& pNode);
    Acad::ErrorStatus popNode();
    Acad::ErrorStatus popNode(AcUtXMLDOMNode*& pNode);
    Acad::ErrorStatus appendBoolAttribute(bool val,
        const AcUtString& attName, AcUtXMLDOMElement* pElement);
    Acad::ErrorStatus appendAttribute(bool val,
        const AcUtString& attName, AcUtXMLDOMElement* pElement);
    Acad::ErrorStatus appendIntAttribute(int val,
        const AcUtString& attName, AcUtXMLDOMElement* pElement);
    Acad::ErrorStatus appendAttribute(int val,
        const AcUtString& attName, AcUtXMLDOMElement* pElement);
    Acad::ErrorStatus appendULongAttribute(unsigned long int val,
        const AcUtString& attName, AcUtXMLDOMElement* pElement);
    Acad::ErrorStatus appendAttribute(unsigned long int val,
        const AcUtString& attName, AcUtXMLDOMElement* pElement);
    Acad::ErrorStatus appendDoubleAttribute(double val,
        const AcUtString& attName, AcUtXMLDOMElement* pElement);
    Acad::ErrorStatus appendAttribute(double val,
        const AcUtString& attName, AcUtXMLDOMElement* pElement);
    Acad::ErrorStatus appendAttribute(const AcUtString& attValue,
        const AcUtString& attName, AcUtXMLDOMElement* pElement);
    Acad::ErrorStatus appendDateAttribute(const AcDbDate& dateTime, 
        const AcUtString& attName, AcUtXMLDOMElement* pElement);
    Acad::ErrorStatus appendAttribute(const AcDbDate& dateTime, 
        const AcUtString& attName, AcUtXMLDOMElement* pElement);
    Acad::ErrorStatus appendBinaryAttribute(const ads_binary& val,
        const AcUtString& attName, AcUtXMLDOMElement* pElement);


    // DesignXML methods
    //
    Acad::ErrorStatus writeDataString(const AcUtString& tag, 
        const AcUtString& str);
    Acad::ErrorStatus writeLength(const AcUtString& tag, 
        double value);
    Acad::ErrorStatus writeAngle(const AcUtString& tag, 
        double value);
    Acad::ErrorStatus writePoint(const AcUtString& tag, 
        const AcGePoint2d& pt);
    Acad::ErrorStatus writePoint(const AcUtString& tag, 
        const AcGePoint3d& pt);
    Acad::ErrorStatus writeVector(const AcUtString& tag, 
        const AcGeVector2d& vec);
    Acad::ErrorStatus writeVector(const AcUtString& tag, 
        const AcGeVector3d& vec);
    Acad::ErrorStatus writeScale(const AcUtString& tag, 
        const AcGeScale3d& scale);
    Acad::ErrorStatus writeMatrix3x3(const AcUtString& tag, 
        const AcGeMatrix3d& matrix);
    Acad::ErrorStatus writeLinearCoordinateTransform(const AcUtString& tag, 
        const AcGeMatrix3d& matrix);
    Acad::ErrorStatus writeView(
        bool bIsPlan, bool bIsPerspective, 
        bool bIsFrontClipped, bool bIsBackClipped, bool bIsTwisted,
        double height, double aspectRatio, const AcGePoint3d& targetPoint, 
        const AcGeVector3d& direction, double perspectiveViewingAngle, 
        double frontClip, double backClip, double worldZDisplayAngle);
    Acad::ErrorStatus writeColor(int colorIndex);
    Acad::ErrorStatus writeTrueColor(short v1, short v2, short v3,
        bool bHasAlpha, short alpha, const AcUtString& colorSpace);
    Acad::ErrorStatus writeLink(const AcUtString& link);

    // DesignXML entities
    Acad::ErrorStatus writeLineSegment(
        const AcGePoint3d& startPoint, const AcGePoint3d& endPoint);
    Acad::ErrorStatus writeLine(
        const AcGePoint3d& pointOnLine, const AcGeVector3d& direction);
    Acad::ErrorStatus writeRay(
        const AcGePoint3d& pointOnLine, const AcGeVector3d& direction);
    Acad::ErrorStatus writeCircle(
        const AcGePoint3d& centerPoint, double radius,
        const AcGeVector3d& normal);
    Acad::ErrorStatus writeArc(
        const AcGePoint3d& centerPoint, double radius,
        const AcGeVector3d& normal,
        double startAngle, double endAngle);
    Acad::ErrorStatus writeEllipse(
        double minorMajorRatio, double startParameter, double endParameter,
        AcUtString& quadraticCurveType, AcGePoint3d& center,
        AcGeVector3d& majorAxis, AcGeVector3d& normal);
    Acad::ErrorStatus writePolyline(
        const AcGePoint3dArray& vertices, bool isClosed);
    Acad::ErrorStatus writeBSplineCurve(int degree,
        bool isRational, bool isClosed, bool isPeriodic,
        AcGePoint3dArray& controlPoints, AcGeDoubleArray& knots,
        AcGeDoubleArray& weights, double fitTol,
        double controlPtTol, double knotTol);


    // AcDbXml methods
    Acad::ErrorStatus writeDatabase(AcDbDatabase* pDb);
    Acad::ErrorStatus saveToFile();

    Acad::ErrorStatus writeThickness(double val);
    Acad::ErrorStatus writeNormalVector(const AcGeVector3d& vec);
    Acad::ErrorStatus writeSymbolName(const AcUtString& str);
    Acad::ErrorStatus writeXDataElement(const AcUtString& tag, 
        const resbuf& value);
    Acad::ErrorStatus writeBool(const AcUtString& tag, bool value);
    Acad::ErrorStatus writeInt32(const AcUtString& tag, 
        Adesk::Int32 value);
    Acad::ErrorStatus writeInt16(const AcUtString& tag, 
        Adesk::Int16 value);
    Acad::ErrorStatus writeUInt32(const AcUtString& tag, 
        Adesk::UInt32 value);
    Acad::ErrorStatus writeUInt16(const AcUtString& tag, 
        Adesk::UInt16 value);
    Acad::ErrorStatus writeUInt8(const AcUtString& tag, 
        Adesk::UInt8 value);
    Acad::ErrorStatus writeDouble(const AcUtString& tag, 
        double value);
    Acad::ErrorStatus writeDouble(const AcUtString& tag, 
        const AcUtString& attName, double value);
    Acad::ErrorStatus writeBinaryChunk(const AcUtString& tag,
        const ads_binary& value);
    Acad::ErrorStatus writeBoolean(const AcUtString& tag, 
        Adesk::Boolean value);


    Acad::ErrorStatus writeSoftOwnershipId(const AcUtString& tag, 
        const AcDbObjectId& id);
    Acad::ErrorStatus writeSoftOwnershipIds(const AcUtString& tag, 
        const AcDbObjectIdArray& ids);
    Acad::ErrorStatus writeHardOwnershipId(const AcUtString& tag, 
        const AcDbObjectId& id);
    Acad::ErrorStatus writeHardOwnershipIds(const AcUtString& tag, 
        const AcDbObjectIdArray& ids);
    Acad::ErrorStatus writeSoftPointerId(const AcUtString& tag, 
        const AcDbObjectId& id);
    Acad::ErrorStatus writeSoftPointerIds(const AcUtString& tag, 
        const AcDbObjectIdArray& ids);
    Acad::ErrorStatus writeHardPointerId(const AcUtString& tag, 
        const AcDbObjectId& id);
    Acad::ErrorStatus writeHardPointerIds(const AcUtString& tag, 
        const AcDbObjectIdArray& ids);

private:
    void* mpImpl;
    friend class AcDbXmlSystemInternals;
};
