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

#ifndef ARXDBG_WORLDDRAW_H
#define ARXDBG_WORLDDRAW_H

class ArxDbgGiWorldGeometry;
class ArxDbgGiSubEntityTraits;

/******************************************************************************
**
**  CLASS ArxDbgGiContext:
**
**  **jma
**
****************************/

class ArxDbgGiContext : public AcGiContext {

public:
    ACRX_DECLARE_MEMBERS(ArxDbgGiContext);

    virtual Adesk::Boolean      isPsOut() const;
    virtual Adesk::Boolean      isPlotGeneration() const;
    virtual AcDbDatabase*       database() const;
    virtual bool                isBoundaryClipping() const;
};


/******************************************************************************
**
**  CLASS ArxDbgGiCommonDraw:
**
**  **jma
**
****************************/

class ArxDbgGiWorldDraw : public AcGiWorldDraw {

public:
    ACRX_DECLARE_MEMBERS(ArxDbgGiWorldDraw);

                        ArxDbgGiWorldDraw();
    virtual             ~ArxDbgGiWorldDraw();

    virtual AcGiRegenType           regenType() const;
    virtual Adesk::Boolean          regenAbort() const;
    virtual AcGiSubEntityTraits&    subEntityTraits() const;
    virtual AcGiGeometry*           rawGeometry() const;
    virtual AcGiWorldGeometry&      geometry() const;
    virtual Adesk::Boolean          isDragging() const;
    virtual double                  deviation(const AcGiDeviationType, const AcGePoint3d&) const;
    virtual Adesk::UInt32           numberOfIsolines() const;

    virtual AcGiContext*            context();

        // extra functions for our class
    void    setRegenType(AcGiRegenType newType)     { m_regenType = newType; }
    void    setDeviation(double dev)                { m_deviation = dev; }
    void    setIsolines(Adesk::UInt32 isolines)     { m_isolines = isolines; }
    void    setIsDragging(Adesk::Boolean drag)      { m_isDragging = drag; }

    void    setInitialProps(AcDbEntity* ent);

        // statics to control the message level and allow other classes
        // to access it without alot of trouble for this simple test case
    static    BOOL    m_showWorldDrawMsg;
    static    BOOL    m_showGeomMsg;
    static    BOOL    m_showSubentsMsg;
    static    BOOL    m_showDetailsMsg;

private:
    ArxDbgGiWorldGeometry*      m_geom;
    ArxDbgGiSubEntityTraits*    m_traits;
    ArxDbgGiContext*            m_context;
    AcGiRegenType               m_regenType;
    double                      m_deviation;
    Adesk::UInt32               m_isolines;
    Adesk::Boolean              m_isDragging;

        // helper functions
    void    printWorldDrawMsg(LPCTSTR event) const;
};


/******************************************************************************
**
**    CLASS ArxDbgGiWorldGeometry:
**
**    **jma
**
****************************/

class ArxDbgGiWorldGeometry : public AcGiWorldGeometry {

public:

    ACRX_DECLARE_MEMBERS(ArxDbgGiWorldGeometry);

                    ArxDbgGiWorldGeometry()     {}
    virtual         ~ArxDbgGiWorldGeometry()    {}

    virtual void    getModelToWorldTransform(AcGeMatrix3d&) const;
    virtual void    getWorldToModelTransform(AcGeMatrix3d&) const;
    virtual void    setModelToWorldTransform(const AcGeMatrix3d&);

    virtual Adesk::Boolean  pushModelTransform(const AcGeVector3d& vNormal);// Uses arbitrary Axis algorythm
    virtual Adesk::Boolean  pushModelTransform(const AcGeMatrix3d& xMat);
    virtual Adesk::Boolean  popModelTransform();

    virtual Adesk::Boolean  draw(AcGiDrawable*) const;

    virtual Adesk::Boolean  pushClipBoundary(AcGiClipBoundary* pBoundary);
    virtual void            popClipBoundary();

    virtual void    setExtents(AcGePoint3d* pNewExtents) const;


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
                                       const AcGeVector3d* pNormal = NULL,
                                       Adesk::LongPtr lBaseSubEntMarker = -1) const;

    virtual Adesk::Boolean    polyline(const AcGiPolyline& polylineObj) const;

    virtual Adesk::Boolean    polyPolyline (Adesk::UInt32 nbPolylines,
                                            const AcGiPolyline* pPolylines) const;

    virtual Adesk::Boolean    polygon(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pVertexList) const;

    virtual Adesk::Boolean  polyPolygon(const Adesk::UInt32 numPolygonIndices,
                                const Adesk::UInt32* numPolygonPositions,
                                const AcGePoint3d* polygonPositions,
                                const Adesk::UInt32* numPolygonPoints,
                                const AcGePoint3d* polygonPoints,
                                const AcCmEntityColor* outlineColors = NULL,
                                const AcGiLineType* outlineTypes = NULL,
                                const AcCmEntityColor* fillColors = NULL,
                                const AcCmTransparency* fillOpacities = NULL
                                ) const;

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

    virtual AcGeMatrix3d pushPositionTransform (AcGiPositionTransformBehavior behavior, const AcGePoint3d& offset); 

    virtual AcGeMatrix3d pushPositionTransform (AcGiPositionTransformBehavior behavior, const AcGePoint2d& offset); 

    virtual AcGeMatrix3d pushScaleTransform(AcGiScaleTransformBehavior behavior, const AcGePoint3d& extents); 

    virtual AcGeMatrix3d pushScaleTransform(AcGiScaleTransformBehavior behavior, const AcGePoint2d& extents); 

    virtual AcGeMatrix3d pushOrientationTransform(AcGiOrientationTransformBehavior behavior);

    virtual Adesk::Boolean image   (
                const AcGiImageBGRA32& imageSource,
                const AcGePoint3d& position,
                const AcGeVector3d& u,
                const AcGeVector3d& v,
                TransparencyMode transparencyMode = kTransparency8Bit
                ) const;

    virtual Adesk::Boolean rowOfDots   (
                int count,
                const AcGePoint3d&     start,
                const AcGeVector3d&     step
                ) const;

    virtual Adesk::Boolean ellipticalArc  (
                 const AcGePoint3d&         center,
                 const AcGeVector3d&        normal,
                 double                     majorAxisLength,
                 double                     minorAxisLength,
                 double                     startDegreeInRads,
                 double                     endDegreeInRads,
                 double                     tiltDegreeInRads,
                 AcGiArcType                arcType
                 ) const;

    virtual Adesk::Boolean edge (const AcArray<AcGeCurve2d*>& edge) const;

        // helper functions
    void        printGeomMsg(LPCTSTR event) const;

        // static so that WorldDraw and Viewport draw can use the same routines
        // If someone had only derived ViewportDraw off of WorldDraw.....
    static    void printCircle(const AcGePoint3d& center, const double radius, const AcGeVector3d& normal);
    static    void printCircle(const AcGePoint3d&, const AcGePoint3d&, const AcGePoint3d&);
    static    void printArc(const AcGePoint3d& center,
                                const double radius, const AcGeVector3d& normal,
                                const AcGeVector3d& startVector,
                                const double sweepAngle,
                                const AcGiArcType arcType);
    static    void printArc(const AcGePoint3d& start,
                                const AcGePoint3d& point,
                                const AcGePoint3d& end,
                                const AcGiArcType arcType);
    static    void printPolyline(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pVertexList,
                                const AcGeVector3d* pNormal);
    static    void printPolygon(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pVertexList);
    static    void printMesh(const Adesk::UInt32 rows,
                                const Adesk::UInt32 columns,
                                const AcGePoint3d* pVertexList,
                                const AcGiEdgeData* pEdgeData,
                                const AcGiFaceData* pFaceData,
                                const AcGiVertexData* pVertexData);
    static    void printShell(const Adesk::UInt32 nbVertex,
                                const AcGePoint3d* pVertexList,
                                const Adesk::UInt32 faceListSize,
                                const Adesk::Int32* pFaceList,
                                const AcGiEdgeData* pEdgeData,
                                const AcGiFaceData* pFaceData,
                                const AcGiVertexData* pVertexData,
                                const struct resbuf* pResBuf);
    static    void printText(const AcGePoint3d& position,
                                const AcGeVector3d& normal,
                                const AcGeVector3d& direction,
                                const double height,
                                const double width,
                                const double oblique,
                                const TCHAR* pMsg);
    static    void printText(const AcGePoint3d& position,
                                const AcGeVector3d& normal,
                                const AcGeVector3d& direction,
                                const TCHAR* pMsg,
                                const Adesk::Int32 length,
                                const Adesk::Boolean raw,
                                const AcGiTextStyle& pTextStyle);
    static    void printRay(const AcGePoint3d& start, const AcGePoint3d&);
    static    void printXline(const AcGePoint3d&, const AcGePoint3d&);
    static    void printPline(const AcDbPolyline& lwBuf,
                                    Adesk::UInt32 fromIndex = 0,
                                    Adesk::UInt32 numSegs = 0);
    static    void printPtArray(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pVertexList);
};



/******************************************************************************
**
**  CLASS ArxDbgGiSubEntityTraits:
**
**  **csa
**
****************************/

class ArxDbgGiSubEntityTraits : public AcGiSubEntityTraits {

public:
    ACRX_DECLARE_MEMBERS(ArxDbgGiSubEntityTraits);

                    ArxDbgGiSubEntityTraits()   {}
    virtual         ~ArxDbgGiSubEntityTraits()  {}

        // Set properties of drawn objects.
    virtual void    setColor(const Adesk::UInt16 color);
    virtual void    setTrueColor(const AcCmEntityColor& color);
    virtual void    setLayer(const AcDbObjectId layerId);
    virtual void    setLineType(const AcDbObjectId linetypeId);
    virtual void    setSelectionMarker(const Adesk::LongPtr markerId);
    virtual void    setFillType(const AcGiFillType);
    virtual void    setLineWeight(const AcDb::LineWeight lw);
    virtual void    setLineTypeScale(double ltScale);
    virtual void    setThickness(double dThickness);

        // Return current settings.
    virtual Adesk::UInt16       color() const           { return m_color; }
    virtual AcCmEntityColor     trueColor() const       { return m_trueColor; }
    virtual AcDbObjectId        layerId() const         { return m_layerId; }
    virtual AcDbObjectId        lineTypeId() const      { return m_ltypeId; }
    virtual AcDb::LineWeight    lineWeight() const      { return m_lineWt; }
    virtual AcGiFillType        fillType() const        { return m_filltype; }
    virtual double              thickness() const       { return m_thickness; }
    virtual double              lineTypeScale() const   { return m_ltypeScale; }

private:
    Adesk::UInt16       m_color;
    AcCmEntityColor     m_trueColor;
    AcDbObjectId        m_layerId;
    AcDbObjectId        m_ltypeId;
    AcDb::LineWeight    m_lineWt;
    AcGiFillType        m_filltype;
    double              m_thickness;
    double              m_ltypeScale;

        // helper functions
    void        printSubentMsg(LPCTSTR event) const;

};


// global functions
LPCTSTR    arcTypeToStr(AcGiArcType arcType, CString& str);
LPCTSTR    fillTypeToStr(AcGiFillType fillType, CString& str);
LPCTSTR    deviationTypeToStr(AcGiDeviationType devType, CString& str);

void    printParamMsg(LPCTSTR tag, LPCTSTR msg);


#endif    // ARXDBG_WORLDDRAW_H
