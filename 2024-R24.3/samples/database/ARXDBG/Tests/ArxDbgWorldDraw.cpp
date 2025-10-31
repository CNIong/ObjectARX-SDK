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
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif


#include "ArxDbgWorldDraw.h"
#include "ArxDbgUtils.h"



BOOL    ArxDbgGiWorldDraw::m_showWorldDrawMsg = FALSE;
BOOL    ArxDbgGiWorldDraw::m_showGeomMsg = TRUE;
BOOL    ArxDbgGiWorldDraw::m_showSubentsMsg = TRUE;
BOOL    ArxDbgGiWorldDraw::m_showDetailsMsg = FALSE;


ACRX_NO_CONS_DEFINE_MEMBERS(ArxDbgGiContext, AcGiContext)
ACRX_NO_CONS_DEFINE_MEMBERS(ArxDbgGiWorldDraw, AcGiWorldDraw)
ACRX_NO_CONS_DEFINE_MEMBERS(ArxDbgGiWorldGeometry, AcGiWorldGeometry)
ACRX_NO_CONS_DEFINE_MEMBERS(ArxDbgGiSubEntityTraits, AcGiSubEntityTraits)

/****************************************************************************
**
**  ArxDbgGiContext::isPsOut
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiContext::isPsOut() const
{
    return Adesk::kFalse;
}

/****************************************************************************
**
**  ArxDbgGiContext::isPlotGeneration
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiContext::isPlotGeneration() const
{
    return Adesk::kFalse;
}

/****************************************************************************
**
**  ArxDbgGiContext::database
**
**  **jma
**
*************************************/

AcDbDatabase*
ArxDbgGiContext::database() const
{
    return acdbHostApplicationServices()->workingDatabase();    // TBD: ??
}

/****************************************************************************
**
**  ArxDbgGiContext::isBoundaryClipping
**
**  **jma
**
*************************************/

bool
ArxDbgGiContext::isBoundaryClipping() const
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


/****************************************************************************
**
**  ArxDbgGiWorldDraw::ArxDbgGiWorldDraw
**
**  **jma
**
*************************************/

ArxDbgGiWorldDraw::ArxDbgGiWorldDraw()
:   m_regenType(kAcGiStandardDisplay),
    m_isDragging(Adesk::kFalse),
    m_deviation(0.5),
    m_isolines(16)
{
    m_geom = new ArxDbgGiWorldGeometry;
    m_traits = new ArxDbgGiSubEntityTraits;
    m_context = new ArxDbgGiContext;
}

/****************************************************************************
**
**  ArxDbgGiWorldDraw::~ArxDbgGiWorldDraw
**
**  **jma
**
*************************************/

ArxDbgGiWorldDraw::~ArxDbgGiWorldDraw()
{
    delete m_geom;
    delete m_traits;
    delete m_context;
}

/****************************************************************************
**
**  ArxDbgGiWorldDraw::rawGeometry
**
**  **jma
**
*************************************/

AcGiGeometry*
ArxDbgGiWorldDraw::rawGeometry() const
{
    printWorldDrawMsg(_T("--> rawGeometry()"));
    return m_geom;
}

/****************************************************************************
**
**  ArxDbgGiWorldDraw::geometry
**
**  **jma
**
*************************************/

AcGiWorldGeometry&
ArxDbgGiWorldDraw::geometry() const
{
    printWorldDrawMsg(_T("--> geometry()"));
    return *m_geom;
}

/****************************************************************************
**
**  ArxDbgGiWorldDraw::context
**
**  **jma
**
*************************************/

AcGiContext*
ArxDbgGiWorldDraw::context()
{
    printWorldDrawMsg(_T("--> context()"));
    return m_context;
}

/****************************************************************************
**
**  ArxDbgGiWorldDraw::regenType
**
**  **jma
**
*************************************/

AcGiRegenType
ArxDbgGiWorldDraw::regenType() const
{
    printWorldDrawMsg(_T("--> regenType()"));
    return(m_regenType);
}

/****************************************************************************
**
**  ArxDbgGiWorldDraw::regenAbort
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiWorldDraw::regenAbort() const
{
    printWorldDrawMsg(_T("--> regenAbort()"));
    return(Adesk::kFalse);
}

/****************************************************************************
**
**  ArxDbgGiWorldDraw::subEntityTraits
**
**  **jma
**
*************************************/

AcGiSubEntityTraits&
ArxDbgGiWorldDraw::subEntityTraits() const
{
    printWorldDrawMsg(_T("--> subEntityTraits()"));
    return *m_traits;
}

/****************************************************************************
**
**  ArxDbgGiWorldDraw::isDragging
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiWorldDraw::isDragging() const
{
    printWorldDrawMsg(_T("--> isDragging()"));
    return(m_isDragging);
}

/****************************************************************************
**
**  ArxDbgGiWorldDraw::deviation
**
**  **jma
**
*************************************/

double
ArxDbgGiWorldDraw::deviation(const AcGiDeviationType devType, const AcGePoint3d& samplePt) const
{
    printWorldDrawMsg(_T("--> deviation(devType, samplePt)"));
    if (m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("DEV TYPE"), deviationTypeToStr(devType, str));
        printParamMsg(_T("SAMPLE PT"), ArxDbgUtils::ptToStr(samplePt, str));
    }
    return(m_deviation);
}

/****************************************************************************
**
**  ArxDbgGiWorldDraw::numberOfIsolines
**
**  **jma
**
*************************************/

Adesk::UInt32
ArxDbgGiWorldDraw::numberOfIsolines() const
{
    printWorldDrawMsg(_T("--> numberOfIsolines()"));
    return(m_isolines);
}

/****************************************************************************
**
**  ArxDbgGiWorldDraw::printWorldDrawMsg
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldDraw::printWorldDrawMsg(LPCTSTR event) const
{
    if (m_showWorldDrawMsg)
        acutPrintf(_T("\n%-15s : %s "), _T("WorldDraw"), event);
}

/****************************************************************************
**
**  ArxDbgGiWorldDraw::setInitialProps
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldDraw::setInitialProps(AcDbEntity* ent)
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
**  ArxDbgGiSubEntityTraits::setColor
**
**  **jma
**
*************************************/

void
ArxDbgGiSubEntityTraits::setColor(const Adesk::UInt16 color)
{
    m_color = color;

    CString str;
    str.Format(_T("--> setColor() = %d"), static_cast<int>(color));
    printSubentMsg(str);
}

/****************************************************************************
**
**  ArxDbgGiSubEntityTraits::setTrueColor
**
**  **jma
**
*************************************/

void
ArxDbgGiSubEntityTraits::setTrueColor(const AcCmEntityColor& color)
{
    m_trueColor = color;

    printSubentMsg(_T("--> setTrueColor"));
}

/****************************************************************************
**
**  ArxDbgGiSubEntityTraits::setLayer
**
**  **jma
**
*************************************/

void
ArxDbgGiSubEntityTraits::setLayer(const AcDbObjectId layerId)
{
    m_layerId = layerId;

    CString layerName;
    ArxDbgUtils::symbolIdToName(layerId, layerName);

    CString str;
    str.Format(_T("--> setLayer() = %s"),
                            static_cast<const TCHAR*>(layerName));
    printSubentMsg(str);
}

/****************************************************************************
**
**  ArxDbgGiSubEntityTraits::setLineType
**
**  **jma
**
*************************************/

void
ArxDbgGiSubEntityTraits::setLineType(const AcDbObjectId linetypeId)
{
    m_ltypeId = linetypeId;

    CString ltypeName;
    ArxDbgUtils::symbolIdToName(linetypeId, ltypeName);

    CString str;
    str.Format(_T("--> setLineType() = %s"),
                            static_cast<const TCHAR*>(ltypeName));
    printSubentMsg(str);
}

/****************************************************************************
**
**  ArxDbgGiSubEntityTraits::setLineWeight
**
**  **jma
**
*************************************/

void
ArxDbgGiSubEntityTraits::setLineWeight(const AcDb::LineWeight lw)
{
    m_lineWt = lw;

    CString str, str2;
    str.Format(_T("--> setLineWeight() = %s"), ArxDbgUtils::lineWeightTypeToStr(lw, str2));

    printSubentMsg(str);
}

/****************************************************************************
**
**  ArxDbgGiSubEntityTraits::setLineTypeScale
**
**  **jma
**
*************************************/

void
ArxDbgGiSubEntityTraits::setLineTypeScale(double ltScale)
{
    m_ltypeScale = ltScale;

    CString str, str2;
    str.Format(_T("--> setLineTypeScale() = %s"), ArxDbgUtils::doubleToStr(ltScale, str2));

    printSubentMsg(str);
}

/****************************************************************************
**
**  ArxDbgGiSubEntityTraits::setThickness
**
**  **jma
**
*************************************/

void
ArxDbgGiSubEntityTraits::setThickness(double thick)
{
    m_thickness = thick;

    CString str, str2;
    str.Format(_T("--> setThickness() = %s"), ArxDbgUtils::doubleToStr(thick, str2));

    printSubentMsg(str);
}

/****************************************************************************
**
**  ArxDbgGiSubEntityTraits::setSelectionMarker
**
**  **jma
**
*************************************/

void
ArxDbgGiSubEntityTraits::setSelectionMarker(const Adesk::LongPtr markerId)
{
    CString str;
    str.Format(_T("--> setSelectionMarker() = %Id"), markerId);
    printSubentMsg(str);
}

/****************************************************************************
**
**  ArxDbgGiSubEntityTraits::setFillType
**
**  **jma
**
*************************************/

void
ArxDbgGiSubEntityTraits::setFillType(const AcGiFillType fillType)
{
    CString str, str2;
    str.Format(_T("--> setFillType() = %s"),
                            fillTypeToStr(fillType, str2));
    printSubentMsg(str);
}

/****************************************************************************
**
**  ArxDbgGiSubEntityTraits::printSubentMsg
**
**  **jma
**
*************************************/

void
ArxDbgGiSubEntityTraits::printSubentMsg(LPCTSTR event) const
{
    if (ArxDbgGiWorldDraw::m_showSubentsMsg)
        acutPrintf(_T("\n%-15s : %s "), _T("SubEntTraits"), event);
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


/****************************************************************************
**
**  ArxDbgGiWorldGeometry::getModelToWorldTransform
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldGeometry::getModelToWorldTransform(AcGeMatrix3d&) const
{
    printGeomMsg(_T("--> getModelToWorldTransform()"));
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::getWorldToModelTransform
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldGeometry::getWorldToModelTransform(AcGeMatrix3d&) const
{
    printGeomMsg(_T("--> getWorldToModelTransform()"));
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::setModelToWorldTransform
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldGeometry::setModelToWorldTransform(const AcGeMatrix3d&)
{
    printGeomMsg(_T("--> setModelToWorldTransform()"));
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::pushModelTransform
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiWorldGeometry::pushModelTransform(const AcGeVector3d & vNormal)
{
    printGeomMsg(_T("--> pushModelTransform(const AcGeVector3d)"));

    return Adesk::kTrue;
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::pushModelTransform
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiWorldGeometry::pushModelTransform(const AcGeMatrix3d & xMat)
{
    printGeomMsg(_T("--> pushModelTransform(const AcGeMatrix3d)"));

    return Adesk::kTrue;
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::popModelTransform
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiWorldGeometry::popModelTransform()
{
    printGeomMsg(_T("--> popModelTransform()"));

    return Adesk::kTrue;
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::draw
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiWorldGeometry::draw(AcGiDrawable*) const
{
    printGeomMsg(_T("--> draw()"));

    return Adesk::kTrue;
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::pushClipBoundary
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiWorldGeometry::pushClipBoundary(AcGiClipBoundary* pBoundary)
{
    printGeomMsg(_T("--> pushClipBoundary()"));

    return Adesk::kTrue;
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::popClipBoundary
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldGeometry::popClipBoundary()
{
    printGeomMsg(_T("--> popClipBoundary()"));
}

Adesk::Boolean
ArxDbgGiWorldGeometry::image   (
                const AcGiImageBGRA32& imageSource,
                const AcGePoint3d& position,
                const AcGeVector3d& u,
                const AcGeVector3d& v,
                AcGiGeometry::TransparencyMode transparencyMode
                ) const
{
    printGeomMsg(_T("--> image(imageSource,position,width,height,transparencyMode"));
    return Adesk::kFalse;
}

Adesk::Boolean 
ArxDbgGiWorldGeometry::rowOfDots   (
                int count,
                const AcGePoint3d&     start,
                const AcGeVector3d&     step
                ) const
{
    printGeomMsg(_T("--> rowOfDots(count,start,step)"));
    return Adesk::kFalse;
}


Adesk::Boolean 
ArxDbgGiWorldGeometry::ellipticalArc   (
                 const AcGePoint3d&         center,
                 const AcGeVector3d&        normal,
                 double                     majorAxisLength,
                 double                     minorAxisLength,
                 double                     startDegreeInRads,
                 double                     endDegreeInRads,
                 double                     tiltDegreeInRads,
                 AcGiArcType                arcType) const
{
    printGeomMsg(_T("--> ellipticalArc(center,normal,majorAxisLength,")
        _T("minorAxisLength,startDegreeInRads,endDegreeInRads,tiltDegreeInRads,arcType)"));
    return Adesk::kFalse;
}

AcGeMatrix3d 
ArxDbgGiWorldGeometry::pushPositionTransform (AcGiPositionTransformBehavior behavior, const AcGePoint3d& offset)
{
    printGeomMsg(_T("--> pushPositionTransform(behavior,offset)"));
    return AcGeMatrix3d::kIdentity;
}

AcGeMatrix3d 
ArxDbgGiWorldGeometry::pushPositionTransform (AcGiPositionTransformBehavior behavior, const AcGePoint2d& offset)
{
    printGeomMsg(_T("--> pushPositionTransform(behavior,offset)"));
    return AcGeMatrix3d::kIdentity;
}

AcGeMatrix3d 
ArxDbgGiWorldGeometry::pushScaleTransform (AcGiScaleTransformBehavior behavior, const AcGePoint3d& extents)
{
    printGeomMsg(_T("--> pushScaleTransform(behavior,extents)"));
    return AcGeMatrix3d::kIdentity;
}

AcGeMatrix3d 
ArxDbgGiWorldGeometry::pushScaleTransform (AcGiScaleTransformBehavior behavior, const AcGePoint2d& extents)
{
    printGeomMsg(_T("--> pushScaleTransform(behavior,extents)"));
    return AcGeMatrix3d::kIdentity;
}

AcGeMatrix3d 
ArxDbgGiWorldGeometry::pushOrientationTransform (AcGiOrientationTransformBehavior behavior)
{
    printGeomMsg(_T("--> pushOrientationTransform(behavior)"));
    return AcGeMatrix3d::kIdentity;
}
/****************************************************************************
**
**  ArxDbgGiWorldGeometry::setExtents
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldGeometry::setExtents(AcGePoint3d* pNewExtents) const
{
    printGeomMsg(_T("--> setExtents(pNewExtents)"));
    if (ArxDbgGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("EXTMIN"), ArxDbgUtils::ptToStr(pNewExtents[0], str));
        printParamMsg(_T("EXTMAX"), ArxDbgUtils::ptToStr(pNewExtents[1], str));
    }
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::circle
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiWorldGeometry::circle(const AcGePoint3d& center, const double radius,
                            const AcGeVector3d& normal) const
{
    printGeomMsg(_T("--> circle(center, radius, normal)"));
    ArxDbgGiWorldGeometry::printCircle(center, radius, normal);
    return Adesk::kFalse;
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::circle
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiWorldGeometry::circle(const AcGePoint3d& p1, const AcGePoint3d& p2,
                        const AcGePoint3d& p3) const
{
    printGeomMsg(_T("--> circle(pt1, pt2, pt3)"));
    ArxDbgGiWorldGeometry::printCircle(p1, p2, p3);
    return Adesk::kFalse;
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::circularArc
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiWorldGeometry::circularArc(const AcGePoint3d& center, const double radius,
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
**  ArxDbgGiWorldGeometry::circularArc
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiWorldGeometry::circularArc(const AcGePoint3d& pt1, const AcGePoint3d& pt2,
                        const AcGePoint3d& pt3, const AcGiArcType arcType) const
{
    printGeomMsg(_T("--> circularArc(pt1, pt2, pt3, arcType)"));
    ArxDbgGiWorldGeometry::printArc(pt1, pt2, pt3, arcType);
    return Adesk::kFalse;
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::polyline
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiWorldGeometry::polyline(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pVertexList,
                                const AcGeVector3d* pNormal,
                                Adesk::LongPtr lBaseSubEntMarker) const
{
    printGeomMsg(_T("--> polyline(numPoints, ptArray, normal, baseSubEntMarker)"));
    ArxDbgGiWorldGeometry::printPolyline(nbPoints, pVertexList, pNormal);
    return Adesk::kFalse;
}

Adesk::Boolean 
ArxDbgGiWorldGeometry::polyline (const AcGiPolyline& polylineObj) const
{
    printGeomMsg(_T("--> polyline(polyline)"));

    return polyline(polylineObj.points(), polylineObj.vertexList(),
                    polylineObj.normal(), polylineObj.baseSubEntMarker());
}

Adesk::Boolean 
ArxDbgGiWorldGeometry::polyPolyline (Adesk::UInt32 nbPolylines,
                                  const AcGiPolyline * pPolylines) const
{
    printGeomMsg(_T("--> polylines(nbPolylines, pPolylines)"));

    Adesk::Boolean bAborting = false;

    for (Adesk::UInt32 i = 0; i < nbPolylines && !bAborting; ++i) 
        bAborting = polyline(pPolylines[i]);

    return bAborting;
}


/****************************************************************************
**
**  ArxDbgGiWorldGeometry::polygon
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiWorldGeometry::polygon(const Adesk::UInt32 nbPoints,
                    const AcGePoint3d* pVertexList) const
{
    printGeomMsg(_T("--> polygon(numPoints, ptArray)"));
    ArxDbgGiWorldGeometry::printPolygon(nbPoints, pVertexList);
    return Adesk::kFalse;
}

Adesk::Boolean 
ArxDbgGiWorldGeometry::polyPolygon   (
                                      const Adesk::UInt32 numPolygonIndices,
                                      const Adesk::UInt32* numPolygonPositions,
                                      const AcGePoint3d* polygonPositions,
                                      const Adesk::UInt32* numPolygonPoints,
                                      const AcGePoint3d* polygonPoints,
                                      const AcCmEntityColor* outlineColors,
                                      const AcGiLineType* outlineTypes,
                                      const AcCmEntityColor* fillColors,
                                      const AcCmTransparency* fillOpacities) const
{
    printGeomMsg(_T("--> polyPolygon (numPolygonIndices,numPolygonPositions,polygonPositions,numPolygonPoints,outlineColors,outlineTypes,fillColors,fillOpacities)"));
    return Adesk::kFalse;
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::mesh
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiWorldGeometry::mesh(const Adesk::UInt32 rows,
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
**  ArxDbgGiWorldGeometry::shell
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiWorldGeometry::shell(const Adesk::UInt32 nbVertex,
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
**  ArxDbgGiWorldGeometry::text
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiWorldGeometry::text(const AcGePoint3d& position,
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
**  ArxDbgGiWorldGeometry::text
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiWorldGeometry::text(const AcGePoint3d& position,
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
**  ArxDbgGiWorldGeometry::xline
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiWorldGeometry::xline(const AcGePoint3d& a, const AcGePoint3d& b) const
{
    printGeomMsg(_T("--> xline(pt1, pt2)"));
    ArxDbgGiWorldGeometry::printXline(a, b);
    return Adesk::kFalse;
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::ray
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiWorldGeometry::ray(const AcGePoint3d& start, const AcGePoint3d& other) const
{
    printGeomMsg(_T("--> ray(start, otherPt)"));
    ArxDbgGiWorldGeometry::printRay(start, other);
    return Adesk::kFalse;
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::pline
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgGiWorldGeometry::pline(const AcDbPolyline& lwBuf,
                        Adesk::UInt32 fromIndex, Adesk::UInt32 numSegs) const
{
    printGeomMsg(_T("--> pline(AcDbPolyline&, fromIndex, numSegs)"));
    ArxDbgGiWorldGeometry::printPline(lwBuf, fromIndex, numSegs);
    return Adesk::kFalse;
}

Adesk::Boolean ArxDbgGiWorldGeometry::edge (const AcArray<AcGeCurve2d*>& edge) const
{
    printGeomMsg(_T("--> edge(edge)"));
    return Adesk::kFalse;
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::printGeomMsg
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldGeometry::printGeomMsg(LPCTSTR event) const
{
    if (ArxDbgGiWorldDraw::m_showGeomMsg)
        acutPrintf(_T("\n%-15s : %s "), _T("WorldGeometry"), event);
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::printCircle
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldGeometry::printCircle(const AcGePoint3d& center,
                                const double radius,
                                const AcGeVector3d& normal)
{
    if (ArxDbgGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("CENTER PT"), ArxDbgUtils::ptToStr(center, str));
        printParamMsg(_T("RADIUS"), ArxDbgUtils::doubleToStr(radius, str));
        printParamMsg(_T("NORMAL"), ArxDbgUtils::vectorToStr(normal, str));
    }
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::printCircle
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldGeometry::printCircle(const AcGePoint3d& p1,
                                const AcGePoint3d& p2,
                                const AcGePoint3d& p3)
{
    if (ArxDbgGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("PT 1"), ArxDbgUtils::ptToStr(p1, str));
        printParamMsg(_T("PT 2"), ArxDbgUtils::ptToStr(p2, str));
        printParamMsg(_T("PT 3"), ArxDbgUtils::ptToStr(p3, str));
    }
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::printArc
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldGeometry::printArc(const AcGePoint3d& center,
                                const double radius, const AcGeVector3d& normal,
                                const AcGeVector3d& startVector,
                                const double sweepAngle,
                                const AcGiArcType arcType)
{
    if (ArxDbgGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("CENTER"), ArxDbgUtils::ptToStr(center, str));
        printParamMsg(_T("RADIUS"), ArxDbgUtils::doubleToStr(radius, str));
        printParamMsg(_T("NORMAL"), ArxDbgUtils::vectorToStr(normal, str));
        printParamMsg(_T("START VEC"), ArxDbgUtils::vectorToStr(startVector, str));
        printParamMsg(_T("SWEEP ANG"), ArxDbgUtils::angleToStr(sweepAngle, str));
        printParamMsg(_T("ARC TYPE"), arcTypeToStr(arcType, str));
    }
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::printArc
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldGeometry::printArc(const AcGePoint3d& pt1,
                                const AcGePoint3d& pt2,
                                const AcGePoint3d& pt3,
                                const AcGiArcType arcType)
{
    if (ArxDbgGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("PT 1"), ArxDbgUtils::ptToStr(pt1, str));
        printParamMsg(_T("PT 2"), ArxDbgUtils::ptToStr(pt2, str));
        printParamMsg(_T("PT 3"), ArxDbgUtils::ptToStr(pt3, str));
        printParamMsg(_T("ARC TYPE"), arcTypeToStr(arcType, str));
    }
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::printPolyline
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldGeometry::printPolyline(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pVertexList,
                                const AcGeVector3d* pNormal)
{
    if (ArxDbgGiWorldDraw::m_showDetailsMsg) {
        CString str;

        ArxDbgGiWorldGeometry::printPtArray(nbPoints, pVertexList);

        if (pNormal)
            printParamMsg(_T("NORMAL"), ArxDbgUtils::vectorToStr(*pNormal, str));
    }
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::printPolygon
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldGeometry::printPolygon(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pVertexList)
{
    if (ArxDbgGiWorldDraw::m_showDetailsMsg) {
        ArxDbgGiWorldGeometry::printPtArray(nbPoints, pVertexList);
    }
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::printMesh
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldGeometry::printMesh(const Adesk::UInt32 rows,
                                const Adesk::UInt32 columns,
                                const AcGePoint3d* pVertexList,
                                const AcGiEdgeData* pEdgeData,
                                const AcGiFaceData* pFaceData,
                                const AcGiVertexData* pVertexData)
{
    if (ArxDbgGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("ROWS"), ArxDbgUtils::intToStr(rows, str));
        printParamMsg(_T("COLUMNS"), ArxDbgUtils::intToStr(columns, str));

        ArxDbgGiWorldGeometry::printPtArray(rows*columns, pVertexList);

        if (pEdgeData)
            printParamMsg(_T("EDGE DATA"), _T("Not NULL"));
        else
            printParamMsg(_T("EDGE DATA"), _T("NULL"));

        if (pFaceData)
            printParamMsg(_T("FACE DATA"), _T("Not NULL"));
        else
            printParamMsg(_T("FACE DATA"), _T("NULL"));

        if (pVertexData)
            printParamMsg(_T("VERT DATA"), _T("Not NULL"));
        else
            printParamMsg(_T("VERT DATA"), _T("NULL"));
    }
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::printShell
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldGeometry::printShell(const Adesk::UInt32 nbVertex,
                                const AcGePoint3d* pVertexList,
                                const Adesk::UInt32 faceListSize,
                                const Adesk::Int32* pFaceList,
                                const AcGiEdgeData* pEdgeData,
                                const AcGiFaceData* pFaceData,
                                const AcGiVertexData* pVertexData,
                                const struct resbuf* pResBuf)
{
    if (ArxDbgGiWorldDraw::m_showDetailsMsg) {
        CString str, str2;

        ArxDbgGiWorldGeometry::printPtArray(nbVertex, pVertexList);

        printParamMsg(_T("FACE LIST SIZE"), ArxDbgUtils::intToStr(faceListSize, str));
        for (int j=0; j < static_cast<int>(faceListSize); j++) {
            str2.Format(_T("FACE LIST [%d]"), j);
            printParamMsg(str2, ArxDbgUtils::intToStr(pFaceList[j], str));
        }

        if (pEdgeData)
            printParamMsg(_T("EDGE DATA"), _T("Not NULL"));
        else
            printParamMsg(_T("EDGE DATA"), _T("NULL"));

        if (pFaceData)
            printParamMsg(_T("FACE DATA"), _T("Not NULL"));
        else
            printParamMsg(_T("FACE DATA"), _T("NULL"));

        if (pVertexData)
            printParamMsg(_T("VERT DATA"), _T("Not NULL"));
        else
            printParamMsg(_T("VERT DATA"), _T("NULL"));
    }
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::printText
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldGeometry::printText(const AcGePoint3d& position,
                                const AcGeVector3d& normal,
                                const AcGeVector3d& direction,
                                const double height,
                                const double width,
                                const double oblique,
                                const TCHAR* pMsg)
{
    if (ArxDbgGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("POSITION"), ArxDbgUtils::ptToStr(position, str));
        printParamMsg(_T("NORMAL"), ArxDbgUtils::vectorToStr(normal, str));
        printParamMsg(_T("DIRECTION"), ArxDbgUtils::vectorToStr(direction, str));
        printParamMsg(_T("HEIGHT"), ArxDbgUtils::doubleToStr(height, str));
        printParamMsg(_T("WDITH"), ArxDbgUtils::doubleToStr(width, str));
        printParamMsg(_T("OBLIQUE"), ArxDbgUtils::angleToStr(oblique, str));
        printParamMsg(_T("MSG"), pMsg);
    }
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::printText
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldGeometry::printText(const AcGePoint3d& position,
                                const AcGeVector3d& normal,
                                const AcGeVector3d& direction,
                                const TCHAR* pMsg,
                                const Adesk::Int32 length,
                                const Adesk::Boolean raw,
                                const AcGiTextStyle& pTextStyle)
{
    if (ArxDbgGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("POSITION"), ArxDbgUtils::ptToStr(position, str));
        printParamMsg(_T("NORMAL"), ArxDbgUtils::vectorToStr(normal, str));
        printParamMsg(_T("DIRECTION"), ArxDbgUtils::vectorToStr(direction, str));
        printParamMsg(_T("MSG"), pMsg);
        printParamMsg(_T("LENGTH"), ArxDbgUtils::intToStr(length, str));
        printParamMsg(_T("RAW"), ArxDbgUtils::booleanToStr(raw, str));
    }
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::printRay
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldGeometry::printRay(const AcGePoint3d& start, const AcGePoint3d& other)
{
    if (ArxDbgGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("START PT"), ArxDbgUtils::ptToStr(start, str));
        printParamMsg(_T("OTHER PT"), ArxDbgUtils::ptToStr(other, str));
    }
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::printXline
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldGeometry::printXline(const AcGePoint3d& a, const AcGePoint3d& b)
{
    if (ArxDbgGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("PT1"), ArxDbgUtils::ptToStr(a, str));
        printParamMsg(_T("PT2"), ArxDbgUtils::ptToStr(b, str));
    }
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::printPline
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldGeometry::printPline(const AcDbPolyline& lwBuf,
                                    Adesk::UInt32 fromIndex,
                                    Adesk::UInt32 numSegs)
{
    if (ArxDbgGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("FROM INDEX"), ArxDbgUtils::intToStr(fromIndex, str));
        printParamMsg(_T("NUM SEGS"), ArxDbgUtils::intToStr(numSegs, str));
    }
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::printPtArray
**
**  **jma
**
*************************************/

void
ArxDbgGiWorldGeometry::printPtArray(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pVertexList)
{
    CString str;
    printParamMsg(_T("NUM PTS"), ArxDbgUtils::intToStr(nbPoints, str));

    CString str2;
    for (int i=0;i<static_cast<int>(nbPoints);i++) {
        str2.Format(_T("PT [%d]"), i);
        printParamMsg(str2, ArxDbgUtils::ptToStr(pVertexList[i], str));
    }
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////// GLOBAL FUNCS ////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**  arcTypeToStr
**
**  **jma
**
*************************************/

LPCTSTR
arcTypeToStr(AcGiArcType type, CString& str)
{
    if (type == kAcGiArcSimple)
        str = _T("kAcGiArcSimple");
    else if (type == kAcGiArcSector)
        str = _T("kAcGiArcSector");
    else if (type == kAcGiArcChord)
        str = _T("kAcGiArcChord");
    else {
        ASSERT(0);
        str = _T("UNKNOWN");
    }

    return(str);
}

/****************************************************************************
**
**  ArxDbgGiWorldGeometry::fillTypeToStr
**
**  **jma
**
*************************************/

LPCTSTR
fillTypeToStr(AcGiFillType fillType, CString& str)
{
    if (fillType == kAcGiFillAlways)
        str = _T("kAcGiFillAlways");
    else if (fillType == kAcGiFillNever)
        str = _T("kAcGiFillNever");
    else {
        ASSERT(0);
        str = _T("UNKNOWN");
    }
    return(str);
}

/****************************************************************************
**
**  deviationTypeToStr:
**
**  **jma
**
*************************************/

LPCTSTR
deviationTypeToStr(AcGiDeviationType devType, CString& str)
{
    if (devType == kAcGiMaxDevForCircle)
        str = _T("kAcGiMaxDevForCircle");
    else if (devType == kAcGiMaxDevForCurve)
        str = _T("kAcGiMaxDevForCurve");
    else if (devType == kAcGiMaxDevForBoundary)
        str = _T("kAcGiMaxDevForBoundary");
    else if (devType == kAcGiMaxDevForFacet)
        str = _T("kAcGiMaxDevForFacet");
    else if (devType == kAcGiMaxDevForIsoline)
        str = _T("kAcGiMaxDevForIsoline");
    else {
        ASSERT(0);
        str = _T("UNKNOWN");
    }
    return(str);
}

/****************************************************************************
**
**  printParamMsg
**
**  **jma
**
*************************************/

void
printParamMsg(LPCTSTR tag, LPCTSTR msg)
{
    if (ArxDbgGiWorldDraw::m_showDetailsMsg)
        acutPrintf(_T("\n  %-13s : %s "), tag, msg);
}
