//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif


#include "ArxDbgViewportDraw.h"
#include "ArxDbgUtils.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxDbgGiViewportDraw,AcGiViewportDraw)
ACRX_NO_CONS_DEFINE_MEMBERS(ArxDbgGiViewportGeometry,AcGiViewportGeometry)

/****************************************************************************
**
**    ArxDbgGiViewportDraw::ArxDbgGiViewportDraw
**
**    **jma
**
*************************************/

ArxDbgGiViewportDraw::ArxDbgGiViewportDraw()
:    m_regenType(kAcGiStandardDisplay),
    m_isDragging(Adesk::kFalse),
    m_deviation(0.5),
    m_isolines(16),
    m_seqNum(0)
{
    m_geom = new ArxDbgGiViewportGeometry;
    m_traits = new ArxDbgGiSubEntityTraits;
    //m_viewport = new AcGiViewport;
}

/****************************************************************************
**
**    ArxDbgGiViewportDraw::~ArxDbgGiViewportDraw
**
**    **jma
**
*************************************/

ArxDbgGiViewportDraw::~ArxDbgGiViewportDraw()
{
    delete m_geom;
    delete m_traits;
//    delete m_viewport;
}

/****************************************************************************
**
**    ArxDbgGiViewportDraw::geometry
**
**    **jma
**
*************************************/

AcGiViewportGeometry&
ArxDbgGiViewportDraw::geometry() const
{
    printViewportDrawMsg(_T("--> geometry()"));
    return *m_geom;
}

/****************************************************************************
**
**    ArxDbgGiViewportDraw::regenType
**
**    **jma
**
*************************************/

AcGiRegenType
ArxDbgGiViewportDraw::regenType() const
{
    printViewportDrawMsg(_T("--> regenType()"));
    return(m_regenType);
}

/****************************************************************************
**
**    ArxDbgGiViewportDraw::regenAbort
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportDraw::regenAbort() const
{
    printViewportDrawMsg(_T("--> regenAbort()"));
    return(Adesk::kFalse);
}

/****************************************************************************
**
**    ArxDbgGiViewportDraw::subEntityTraits
**
**    **jma
**
*************************************/

AcGiSubEntityTraits&
ArxDbgGiViewportDraw::subEntityTraits() const
{
    printViewportDrawMsg(_T("--> subEntityTraits()"));
    return *m_traits;
}

/****************************************************************************
**
**    ArxDbgGiViewportDraw::isDragging
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportDraw::isDragging() const
{
    printViewportDrawMsg(_T("--> isDragging()"));
    return(m_isDragging);
}

/****************************************************************************
**
**    ArxDbgGiViewportDraw::deviation
**
**    **jma
**
*************************************/

double
ArxDbgGiViewportDraw::deviation(const AcGiDeviationType devType, const AcGePoint3d& samplePt) const
{
    printViewportDrawMsg(_T("--> deviation(devType, samplePt)"));
    if (ArxDbgGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("DEV TYPE"), deviationTypeToStr(devType, str));
        printParamMsg(_T("SAMPLE PT"), ArxDbgUtils::ptToStr(samplePt, str));
    }
    return(m_deviation);
}

/****************************************************************************
**
**    ArxDbgGiViewportDraw::numberOfIsolines
**
**    **jma
**
*************************************/

Adesk::UInt32
ArxDbgGiViewportDraw::numberOfIsolines() const
{
    printViewportDrawMsg(_T("--> numberOfIsolines()"));
    return(m_isolines);
}

/****************************************************************************
**
**    ArxDbgGiViewportDraw::viewport
**
**    **jma
**
*************************************/

AcGiViewport&
ArxDbgGiViewportDraw::viewport() const
{
    printViewportDrawMsg(_T("--> viewport()"));
    return(*m_viewport);
}

/****************************************************************************
**
**    ArxDbgGiViewportDraw::sequenceNumber
**
**    **jma
**
*************************************/

Adesk::UInt32
ArxDbgGiViewportDraw::sequenceNumber() const
{
    printViewportDrawMsg(_T("--> sequenceNumber()"));
    return(m_seqNum);
}

/****************************************************************************
**
**    ArxDbgGiViewportDraw::isValidId
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportDraw::isValidId(const Adesk::ULongPtr acgiId) const
{
    printViewportDrawMsg(_T("--> isValidId()"));
    return(Adesk::kTrue);    // what else to do??
}

/****************************************************************************
**
**    ArxDbgGiViewportDraw::viewportObjectId
**
**    **jma
**
*************************************/

AcDbObjectId
ArxDbgGiViewportDraw::viewportObjectId() const
{
    printViewportDrawMsg(_T("--> viewportObjectId()"));
    return(AcDbObjectId::kNull);
}

/****************************************************************************
**
**    ArxDbgGiViewportDraw::printViewportDrawMsg
**
**    **jma
**
*************************************/

void
ArxDbgGiViewportDraw::printViewportDrawMsg(LPCTSTR event) const
{
    if (ArxDbgGiWorldDraw::m_showWorldDrawMsg)
        acutPrintf(_T("\n%-15s : %s "), _T("ViewportDraw"), event);
}

/****************************************************************************
**
**    ArxDbgGiViewportDraw::setInitialProps
**
**    **jma
**
*************************************/

void
ArxDbgGiViewportDraw::setInitialProps(AcDbEntity* ent)
{
        // temporarily disable messaging
    BOOL tmpFlag = ArxDbgGiWorldDraw::m_showSubentsMsg;
    ArxDbgGiWorldDraw::m_showSubentsMsg = FALSE;

    m_traits->setLayer(ent->layerId());
    m_traits->setColor(ent->colorIndex());
    m_traits->setLineType(ent->linetypeId());

    ArxDbgGiWorldDraw::m_showSubentsMsg = tmpFlag;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////



/****************************************************************************
**
**    ArxDbgGiViewportGeometry::getModelToWorldTransform
**
**    **jma
**
*************************************/

void
ArxDbgGiViewportGeometry::getModelToWorldTransform(AcGeMatrix3d&) const
{
    printGeomMsg(_T("--> getModelToWorldTransform()"));
}

/****************************************************************************
**
**    ArxDbgGiViewportGeometry::getWorldToModelTransform
**
**    **jma
**
*************************************/

void
ArxDbgGiViewportGeometry::getWorldToModelTransform(AcGeMatrix3d&) const
{
    printGeomMsg(_T("--> getWorldToModelTransform()"));
}

/****************************************************************************
**
**    ArxDbgGiViewportGeometry::circle
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportGeometry::circle(const AcGePoint3d& center, const double radius,
                            const AcGeVector3d& normal) const
{
    printGeomMsg(_T("--> circle(center, radius, normal)"));
    ArxDbgGiWorldGeometry::printCircle(center, radius, normal);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxDbgGiViewportGeometry::circle
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportGeometry::circle(const AcGePoint3d& p1, const AcGePoint3d& p2,
                        const AcGePoint3d& p3) const
{
    printGeomMsg(_T("--> circle(pt1, pt2, pt3)"));
    ArxDbgGiWorldGeometry::printCircle(p1, p2, p3);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxDbgGiViewportGeometry::circularArc
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportGeometry::circularArc(const AcGePoint3d& center, const double radius,
                        const AcGeVector3d& normal, const AcGeVector3d& startVector,
                        const double sweepAngle, const AcGiArcType arcType) const
{
    printGeomMsg(_T("--> circularArc(center, radius, normal, startVec, sweepAngle, arcType)"));
    ArxDbgGiWorldGeometry::printArc(center, radius, normal, startVector,
                                sweepAngle, arcType);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxDbgGiViewportGeometry::circularArc
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportGeometry::circularArc(const AcGePoint3d& pt1, const AcGePoint3d& pt2,
                        const AcGePoint3d& pt3, const AcGiArcType arcType) const
{
    printGeomMsg(_T("--> circularArc(pt1, pt2, pt3, arcType)"));
    ArxDbgGiWorldGeometry::printArc(pt1, pt2, pt3, arcType);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxDbgGiViewportGeometry::polyline
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportGeometry::polyline(const Adesk::UInt32 nbPoints,
                        const AcGePoint3d* pVertexList,
                        const AcGeVector3d* pNormal) const
{
    printGeomMsg(_T("--> polyline(numPoints, ptArray, normal)"));
    ArxDbgGiWorldGeometry::printPolyline(nbPoints, pVertexList, pNormal);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxDbgGiViewportGeometry::polygon
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportGeometry::polygon(const Adesk::UInt32 nbPoints,
                    const AcGePoint3d* pVertexList) const
{
    printGeomMsg(_T("--> polygon(numPoints, ptArray)"));
    ArxDbgGiWorldGeometry::printPolygon(nbPoints, pVertexList);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxDbgGiViewportGeometry::mesh
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportGeometry::mesh(const Adesk::UInt32 rows,
                    const Adesk::UInt32 columns,
                    const AcGePoint3d* pVertexList,
                    const AcGiEdgeData* pEdgeData,
                    const AcGiFaceData* pFaceData,
                    const AcGiVertexData* pVertexData,
                    const bool bAutoGenerateNormals) const
{
    printGeomMsg(_T("--> mesh(rows, cols, pts, edges, faces, vertexData)"));
    ArxDbgGiWorldGeometry::printMesh(rows, columns, pVertexList,
                            pEdgeData, pFaceData, pVertexData);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxDbgGiWorldGeometry::shell
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportGeometry::shell(const Adesk::UInt32 nbVertex,
                        const AcGePoint3d* pVertexList,
                        const Adesk::UInt32 faceListSize,
                        const Adesk::Int32* pFaceList,
                        const AcGiEdgeData* pEdgeData,
                        const AcGiFaceData* pFaceData,
                        const AcGiVertexData* pVertexData,
                        const struct resbuf* pResBuf,
                        const bool bAutoGenerateNormals) const
{
    printGeomMsg(_T("--> shell(nbVertex, pts, faceListSize, faceList, edges, faces, vertexData, resbuf)"));
    ArxDbgGiWorldGeometry::printShell(nbVertex, pVertexList, faceListSize, pFaceList,
                            pEdgeData, pFaceData, pVertexData, pResBuf);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxDbgGiViewportGeometry::text
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportGeometry::text(const AcGePoint3d& position,
                        const AcGeVector3d& normal,
                        const AcGeVector3d& direction,
                        const double height,
                        const double width,
                        const double oblique,
                        const TCHAR* pMsg) const
{
    printGeomMsg(_T("--> text(position, normal, dir, ht, wd, obliq, msg)"));
    ArxDbgGiWorldGeometry::printText(position, normal, direction, height, width,
                            oblique, pMsg);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxDbgGiViewportGeometry::text
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportGeometry::text(const AcGePoint3d& position,
                        const AcGeVector3d& normal,
                        const AcGeVector3d& direction,
                        const TCHAR* pMsg,
                        const Adesk::Int32 length,
                        const Adesk::Boolean raw,
                        const AcGiTextStyle& pTextStyle) const
{
    printGeomMsg(_T("--> text(position, normal, msg, len, raw, textStyle)"));
    ArxDbgGiWorldGeometry::printText(position, normal, direction, pMsg, length,
                            raw, pTextStyle);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxDbgGiViewportGeometry::xline
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportGeometry::xline(const AcGePoint3d& a, const AcGePoint3d& b) const
{
    printGeomMsg(_T("--> xline(pt1, pt2)"));
    ArxDbgGiWorldGeometry::printXline(a, b);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxDbgGiViewportGeometry::ray
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportGeometry::ray(const AcGePoint3d& start, const AcGePoint3d& other) const
{
    printGeomMsg(_T("--> ray(start, otherPt)"));
    ArxDbgGiWorldGeometry::printRay(start, other);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxDbgGiViewportGeometry::pline
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportGeometry::pline(const AcDbPolyline& lwBuf,
                        Adesk::UInt32 fromIndex, Adesk::UInt32 numSegs) const
{
    printGeomMsg(_T("--> pline(AcDbPolyline&, fromIndex, numSegs)"));
    ArxDbgGiWorldGeometry::printPline(lwBuf, fromIndex, numSegs);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxDbgGiViewportGeometry::polylineEye
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportGeometry::polylineEye(const Adesk::UInt32 nbPoints,
                                    const AcGePoint3d* pPoints) const
{
    printGeomMsg(_T("--> polylineEye(numPoints, ptArray)"));
    if (ArxDbgGiWorldDraw::m_showDetailsMsg) 
        ArxDbgGiWorldGeometry::printPtArray(nbPoints, pPoints);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxDbgGiViewportGeometry::polygonEye
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportGeometry::polygonEye(const Adesk::UInt32 nbPoints,
                                    const AcGePoint3d* pPoints) const
{
    printGeomMsg(_T("--> polygonEye(numPoints, ptArray)"));
    if (ArxDbgGiWorldDraw::m_showDetailsMsg) 
        ArxDbgGiWorldGeometry::printPtArray(nbPoints, pPoints);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxDbgGiViewportGeometry::polylineDc
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportGeometry::polylineDc(const Adesk::UInt32 nbPoints,
                                    const AcGePoint3d* pPoints) const
{
    printGeomMsg(_T("--> polylineDc(numPoints, ptArray)"));
    if (ArxDbgGiWorldDraw::m_showDetailsMsg) 
        ArxDbgGiWorldGeometry::printPtArray(nbPoints, pPoints);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxDbgGiViewportGeometry::polygonDc
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportGeometry::polygonDc(const Adesk::UInt32 nbPoints,
                                    const AcGePoint3d* pPoints) const
{
    printGeomMsg(_T("--> polygonDc(numPoints, ptArray)"));
    if (ArxDbgGiWorldDraw::m_showDetailsMsg) 
        ArxDbgGiWorldGeometry::printPtArray(nbPoints, pPoints);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxDbgGiViewportGeometry::rasterImageDc
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportGeometry::rasterImageDc(
                                    const AcGePoint3d& origin,
                                    const AcGeVector3d& u,
                                    const AcGeVector3d& v,
                                    const AcGeMatrix2d& pixelToDc,
                                    AcDbObjectId entityId,
                                    AcGiImageOrg imageOrg,
                                    Adesk::UInt32 imageWidth,
                                    Adesk::UInt32 imageHeight,
                                    Adesk::Int16 imageColorDepth,
                                    Adesk::Boolean transparency) const
{
    printGeomMsg(_T("--> rasterImageDc()"));

    if (ArxDbgGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("ORIGIN"), ArxDbgUtils::ptToStr(origin, str));
        printParamMsg(_T("U"), ArxDbgUtils::vectorToStr(u, str));
        printParamMsg(_T("V"), ArxDbgUtils::vectorToStr(v, str));
        printParamMsg(_T("PIXEL2DC MAT"), _T("Not Yet..."));
        printParamMsg(_T("ENTITY ID"), _T("Not Yet..."));
        printParamMsg(_T("IMAGE ORG"), _T("Not Yet..."));
        printParamMsg(_T("IMAGE WDITH"), ArxDbgUtils::intToStr(imageWidth, str));
        printParamMsg(_T("IMAGE HEIGHT"), ArxDbgUtils::intToStr(imageHeight, str));
        printParamMsg(_T("COLOR DEPTH"), ArxDbgUtils::intToStr(imageColorDepth, str));
        printParamMsg(_T("TRANSPARENCY"), ArxDbgUtils::booleanToStr(transparency, str));
    }
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxDbgGiViewportGeometry::ownerDrawDc
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiViewportGeometry::ownerDrawDc(long vpnumber, 
                                    long left, long top, 
                                    long right, long bottom, 
                                    const OwnerDraw* pOwnerDraw) const
{
    printGeomMsg(_T("--> ownerDrawDc()"));

    if (ArxDbgGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("VPNUMBER"), ArxDbgUtils::intToStr(vpnumber, str));
        printParamMsg(_T("LEFT"), ArxDbgUtils::intToStr(left, str));
        printParamMsg(_T("TOP"), ArxDbgUtils::intToStr(top, str));
        printParamMsg(_T("RIGHT"), ArxDbgUtils::intToStr(right, str));
        printParamMsg(_T("BOTTOM"), ArxDbgUtils::intToStr(bottom, str));
    }
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxDbgGiViewportGeometry::printGeomMsg
**
**    **jma
**
*************************************/

void
ArxDbgGiViewportGeometry::printGeomMsg(LPCTSTR event) const
{
    if (ArxDbgGiWorldDraw::m_showGeomMsg)
        acutPrintf(_T("\n%-15s : %s "), _T("VportGeometry"), event);
}

Adesk::Boolean ArxDbgGiViewportGeometry::edge (const AcArray<AcGeCurve2d*>& edge) const
{
    printGeomMsg(_T("--> edge(edge)"));
    return Adesk::kFalse;
}
