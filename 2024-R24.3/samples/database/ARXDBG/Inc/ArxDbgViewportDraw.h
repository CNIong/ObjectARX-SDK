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

#ifndef ARXDBG_VIEWPORTDRAW_H
#define ARXDBG_VIEWPORTDRAW_H

#include "ArxDbgWorldDraw.h"

class ArxDbgGiViewportGeometry;

/******************************************************************************
**
**    CLASS ArxDbgGiViewportDraw:
**
**    **jma
**
****************************/

class ArxDbgGiViewportDraw : public AcGiViewportDraw {

public:
    ACRX_DECLARE_MEMBERS(ArxDbgGiViewportDraw);

                        ArxDbgGiViewportDraw();
    virtual                ~ArxDbgGiViewportDraw();

    virtual AcGiRegenType            regenType() const;
    virtual Adesk::Boolean            regenAbort() const;
    virtual AcGiSubEntityTraits&    subEntityTraits() const;
    virtual AcGiViewportGeometry&    geometry() const;
    virtual Adesk::Boolean            isDragging() const;
    virtual double                    deviation(const AcGiDeviationType, const AcGePoint3d&) const;
    virtual Adesk::UInt32            numberOfIsolines() const;

    virtual    AcGiViewport&        viewport() const;
    virtual Adesk::UInt32        sequenceNumber() const;
    virtual Adesk::Boolean        isValidId(const Adesk::ULongPtr acgiId) const;
    virtual AcDbObjectId        viewportObjectId() const;

        // extra functions for our class
    void    setRegenType(AcGiRegenType newType)    { m_regenType = newType; }
    void    setDeviation(double dev)            { m_deviation = dev; }
    void    setIsolines(Adesk::UInt32 isolines)    { m_isolines = isolines; }
    void    setIsDragging(Adesk::Boolean drag)    { m_isDragging = drag; }

    void    setInitialProps(AcDbEntity* ent);

private:
    ArxDbgGiViewportGeometry*    m_geom;
    ArxDbgGiSubEntityTraits*    m_traits;
    AcGiViewport*                m_viewport;
    AcGiRegenType                m_regenType;
    double                        m_deviation;
    Adesk::UInt32                m_isolines;
    Adesk::Boolean                m_isDragging;
    Adesk::Int32                m_seqNum;

        // helper functions
    void    printViewportDrawMsg(LPCTSTR event) const;
};


/******************************************************************************
**
**    CLASS ArxDbgGiViewportGeometry:
**
**    **jma
**
****************************/

class ArxDbgGiViewportGeometry : public AcGiViewportGeometry {

public:

    ACRX_DECLARE_MEMBERS(ArxDbgGiViewportGeometry);

                    ArxDbgGiViewportGeometry()        {}
    virtual            ~ArxDbgGiViewportGeometry()    {}

    virtual void    getModelToWorldTransform(AcGeMatrix3d&) const;
    virtual void    getWorldToModelTransform(AcGeMatrix3d&) const;

    virtual Adesk::Boolean    circle(const AcGePoint3d& center,
                                    const double radius,
                                    const AcGeVector3d& normal) const;
    virtual Adesk::Boolean    circle(const AcGePoint3d&, const AcGePoint3d&,
                                    const AcGePoint3d&) const;

    virtual Adesk::Boolean    circularArc(const AcGePoint3d& center,
                                const double radius, const AcGeVector3d& normal,
                                const AcGeVector3d& startVector,
                                const double sweepAngle,
                                const AcGiArcType arcType = kAcGiArcSimple) const;

    virtual Adesk::Boolean    circularArc(const AcGePoint3d& start,
                                const AcGePoint3d& point,
                                const AcGePoint3d& end,
                                const AcGiArcType arcType = kAcGiArcSimple) const;

    virtual Adesk::Boolean    polyline(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pVertexList,
                                const AcGeVector3d* pNormal = NULL) const;

    virtual Adesk::Boolean    polygon(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pVertexList) const;

    virtual Adesk::Boolean    mesh(const Adesk::UInt32 rows,
                                const Adesk::UInt32 columns,
                                const AcGePoint3d* pVertexList,
                                const AcGiEdgeData* pEdgeData = NULL,
                                const AcGiFaceData* pFaceData = NULL,
                                const AcGiVertexData* pVertexData = NULL,
                                const bool bAutoGenerateNormals = true) const;

    virtual Adesk::Boolean    shell(const Adesk::UInt32 nbVertex,
                                const AcGePoint3d* pVertexList,
                                const Adesk::UInt32 faceListSize,
                                const Adesk::Int32* pFaceList,
                                const AcGiEdgeData* pEdgeData = NULL,
                                const AcGiFaceData* pFaceData = NULL,
                                const AcGiVertexData* pVertexData = NULL,
                                const struct resbuf* pResBuf = NULL,
                                const bool bAutoGenerateNormals = true) const;

    virtual Adesk::Boolean    text(const AcGePoint3d& position,
                                const AcGeVector3d& normal,
                                const AcGeVector3d& direction,
                                const double height,
                                const double width,
                                const double oblique,
                                const TCHAR* pMsg) const;
    virtual Adesk::Boolean    text(const AcGePoint3d& position,
                                const AcGeVector3d& normal,
                                const AcGeVector3d& direction,
                                const TCHAR* pMsg,
                                const Adesk::Int32 length,
                                const Adesk::Boolean raw,
                                const AcGiTextStyle& pTextStyle) const;

    virtual Adesk::Boolean    xline(const AcGePoint3d&, const AcGePoint3d&) const;

    virtual Adesk::Boolean    ray(const AcGePoint3d& start, const AcGePoint3d&) const;

    virtual Adesk::Boolean    pline(const AcDbPolyline& lwBuf,
                                    Adesk::UInt32 fromIndex = 0,
                                    Adesk::UInt32 numSegs = 0) const;

        // signatures different from AcGiWorldDraw
    virtual Adesk::Boolean    polylineEye(const Adesk::UInt32 nbPoints,
                                    const AcGePoint3d* pPoints) const;
    virtual Adesk::Boolean    polygonEye(const Adesk::UInt32 nbPoints,
                                    const AcGePoint3d* pPoints) const;

    virtual Adesk::Boolean    polylineDc(const Adesk::UInt32 nbPoints,
                                    const AcGePoint3d* pPoints) const;
    virtual Adesk::Boolean    polygonDc(const Adesk::UInt32 nbPoints,
                                    const AcGePoint3d* pPoints) const;

    virtual Adesk::Boolean  rasterImageDc(
                                    const AcGePoint3d& origin,
                                    const AcGeVector3d& u,
                                    const AcGeVector3d& v,
                                    const AcGeMatrix2d& pixelToDc,
                                    AcDbObjectId entityId,
                                    AcGiImageOrg imageOrg,
                                    Adesk::UInt32 imageWidth,
                                    Adesk::UInt32 imageHeight,
                                    Adesk::Int16 imageColorDepth,
                                    Adesk::Boolean transparency) const;

    virtual Adesk::Boolean  ownerDrawDc(long vpnumber, 
                                    long left, long top, 
                                    long right, long bottom, 
                                    const OwnerDraw* pOwnerDraw) const;


    virtual Adesk::Boolean edge (const AcArray<AcGeCurve2d*>& edge) const;

        // helper functions
    void        printGeomMsg(LPCTSTR event) const;
};




#endif    // ARXDBG_VIEWPORTDRAW_H
