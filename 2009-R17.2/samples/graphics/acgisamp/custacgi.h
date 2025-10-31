#ifndef CUSTACGI_H
#define CUSTACGI_H 1

// (C) Copyright 1996-2008 by Autodesk, Inc. 
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
// CUSTACGI.H

#include "acgi.h"
#include "tchar.h"

class AsdkShellData {

//  Class to store the trapped shell Data.  A pointer to this
//  class is obtained from the AsdkCustomWorldDraw class which
//  fills the data for this class.

public:
    AsdkShellData();
    ~AsdkShellData();

//  setFaceData function will allocate memory for the mpFaceData
//  member.
    virtual Acad::ErrorStatus setFaceData(int colorIndex);

    unsigned int    numberOfFaces();
    unsigned int    numberOfEdges();
    
//  Member Data

    Adesk::UInt32       mNumVertices;
    AcGePoint3d*        mpVertexList;
    Adesk::UInt32       mFaceListSize;
    Adesk::Int32*       mpFaceList;
    AcGiEdgeData*       mpEdgeData;
    AcGiFaceData*       mpFaceData;
    AcGiVertexData*     mpVertexData;
};

class  AsdkCustomWorldDraw : public AcGiWorldDraw {
// Custom worldDraw object is sent in a call to the 
// entitiy's worldDraw function.  The entity will then
// end up calling the worldGeometry class's shell function.
// In this case, the AsdkCustomWorldGeometry's shell member
// function will be called.
 
public:
    ACRX_DECLARE_MEMBERS(AsdkCustomWorldDraw);
    AsdkCustomWorldDraw();
    virtual ~AsdkCustomWorldDraw();

    virtual AcGiRegenType           regenType() const;
    virtual Adesk::Boolean          regenAbort() const;
    virtual AcGiSubEntityTraits&    subEntityTraits() const;
    virtual AcGiGeometry *          rawGeometry() const;
    virtual AcGiWorldGeometry&      geometry() const;
    virtual Adesk::Boolean          isDragging() const;
    virtual double                  deviation(const AcGiDeviationType, 
                          const AcGePoint3d&) const;
    virtual Adesk::UInt32           numberOfIsolines() const;
    virtual AcGiContext *           context();

    AsdkShellData*          shellData();
    void                    setDeviation(double);

// some member data
private:
    AsdkShellData*          mpShellData;
    AcGiSubEntityTraits*    mpSubEntityTraits;
    AcGiWorldGeometry*      mpWorldGeometry;
    AcGiContext*            mpContext;
    double                  mDeviation;

};

class AsdkCustomContext : public AcGiContext
// AcGiContext abstracts out the commonality between 
// AcGiViewportDraw and AcGiWorldDraw. This allows you 
// to code graphics routines in terms of AcGiContext that 
// will work in either case. To maintain their original signatures,
// AcGiWorldDraw and AcGiViewportDraw now derive from AcGiContext.
// Only the database member function is implemented.  
{
public:
    ACRX_DECLARE_MEMBERS(AsdkCustomContext);
    AsdkCustomContext();
    virtual ~AsdkCustomContext();

    Adesk::Boolean          isPsOut() const;
    Adesk::Boolean          isPlotGeneration() const;
    AcDbDatabase *          database() const;
    bool          isBoundaryClipping() const;

};

class AsdkCustomWorldGeometry: public AcGiWorldGeometry2 
//
// This class contains the view independent, model coordinate,
// 3D geometry methods for our custom world geometry class. 
// Only the shell member function is implemented.  Within it
// the shell Data is trapped and stored inside the 
// AsdkCustomWorldDraw's mpShellData member.
//

{ 

public:
    ACRX_DECLARE_MEMBERS(AsdkCustomWorldGeometry);
    AsdkCustomWorldGeometry(AsdkCustomWorldDraw* pWorldDraw);
    ~AsdkCustomWorldGeometry();

    virtual void getModelToWorldTransform(AcGeMatrix3d &pMatrix) const;
    virtual void getWorldToModelTransform(AcGeMatrix3d &pMatrix) const;
    virtual void setExtents(AcGePoint3d *pNewExtents) const;

    virtual Adesk::Boolean  circle(const AcGePoint3d& center,
                const double radius,
                const AcGeVector3d& normal
                ) const;

    virtual Adesk::Boolean  circle(const AcGePoint3d& pt1,
                const AcGePoint3d& pt2,
                const AcGePoint3d& pt3
                ) const;

    virtual Adesk::Boolean  circularArc(const AcGePoint3d& center,
                const double radius,
                const AcGeVector3d& normal,
                const AcGeVector3d& startVector,
                const double sweepAngle,
                const AcGiArcType arcType = kAcGiArcSimple
                ) const;

    virtual Adesk::Boolean  circularArc(const AcGePoint3d& start,
                const AcGePoint3d& point,
                const AcGePoint3d& end,
                const AcGiArcType arcType = kAcGiArcSimple
                ) const;
      
    virtual Adesk::Boolean  polyline(const Adesk::UInt32 nbPoints,
                   const AcGePoint3d* pVertexList,
                   const AcGeVector3d* pNormal = NULL,
                   Adesk::LongPtr lBaseSubEntMarker = -1) const;
      
    virtual Adesk::Boolean  polygon(const Adesk::UInt32 nbPoints,
                const AcGePoint3d* pVertexList
                ) const;

    virtual Adesk::Boolean  mesh(const Adesk::UInt32 rows,
                const Adesk::UInt32 columns,
                const AcGePoint3d* pVertexList,
                const AcGiEdgeData* pEdgeData = NULL,
                const AcGiFaceData* pFaceData = NULL,
                const AcGiVertexData* pVertexData = NULL,
                const bool bAutoGenerateNormals = true
                ) const;

    virtual Adesk::Boolean  shell(const Adesk::UInt32 nbVertex,
                                 const AcGePoint3d* pVertexList,
                                 const Adesk::UInt32 faceListSize,
                                 const Adesk::Int32* pFaceList,
                                 const AcGiEdgeData* pEdgeData = NULL,
                                 const AcGiFaceData* pFaceData = NULL,
                                 const AcGiVertexData* pVertexData = NULL,
                                 const struct resbuf* pResBuf = NULL,
                                 const bool bAutoGenerateNormals = true
                                 ) const;
 
      
    virtual Adesk::Boolean  text(const AcGePoint3d& position,
                const AcGeVector3d& normal,
                const AcGeVector3d& direction,
                const double height,
                const double width,
                const double oblique,
                const TCHAR* pMsg
                ) const;

    virtual Adesk::Boolean  text(const AcGePoint3d& position,
                const AcGeVector3d& normal,
                const AcGeVector3d& direction,
                const TCHAR* pMsg,
                const Adesk::Int32 length,
                const Adesk::Boolean raw,
                const AcGiTextStyle &pTextStyle
                ) const;

    virtual Adesk::Boolean  xline(const AcGePoint3d& one_xline_point,
                const AcGePoint3d& a_different_xline_point
                ) const;

    virtual Adesk::Boolean  ray(const AcGePoint3d& rays_starting_point,
                const AcGePoint3d& a_different_ray_point
                ) const;
    virtual Adesk::Boolean  pline(const AcDbPolyline& lwBuf,
                                  Adesk::UInt32 fromIndex = 0,
                                  Adesk::UInt32 numSegs = 0
                                  ) const;

    virtual Adesk::Boolean pushModelTransform(const AcGeVector3d & vNormal);// Uses arbitrary Axis algorythm
    virtual Adesk::Boolean pushModelTransform(const AcGeMatrix3d & xMat);
    virtual Adesk::Boolean popModelTransform();

    virtual Adesk::Boolean  draw(AcGiDrawable*) const;
    // If you push a clip boundary onto the stack you must pop it;
    virtual Adesk::Boolean  pushClipBoundary(AcGiClipBoundary * pBoundary);
    /*NEW*/virtual void     popClipBoundary();
    virtual void pushPositionTransform (AcGiPositionTransformBehavior behavior, const AcGePoint2d& offset); 

    virtual void pushScaleTransform(AcGiScaleTransformBehavior behavior, const AcGePoint2d& extents); 

    virtual void pushOrientationTransform(AcGiOrientationTransformBehavior behavior);

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
                 bool                       isPie 
                 ) const;

    Adesk::Boolean symbol  (
                 AcGiSymbolType type,
                 const Adesk::UInt32 nbPoints,
                 const AcGePoint3d* pPoints,
                 const AcCmEntityColor& outlineColor,
                 const AcCmEntityColor& fillColor
                 ) const;
private:
    AsdkCustomWorldDraw*    mpCustomWorldDraw;
    // Back pointer stored to the WorldDraw object.  This class
    // uses it to store the ShellData when the shell member
    // function is called.
};


class AsdkCustomSubEntityTraits: public AcGiSubEntityTraits 
//
// This class applies attributes to subsequently drawn AcGi geometry
// primitives.
//

{ 
public:
    ACRX_DECLARE_MEMBERS(AsdkCustomSubEntityTraits);
    AsdkCustomSubEntityTraits();
    ~AsdkCustomSubEntityTraits();

    virtual void setColor(const Adesk::UInt16 color);
    virtual void setTrueColor(const AcCmEntityColor& color);
    virtual void setLayer(const AcDbObjectId layerId);
    virtual void setLineType(const AcDbObjectId linetypeId);
    virtual void setSelectionMarker(const Adesk::LongPtr markerId);
    virtual void setFillType(const AcGiFillType fillType);
    virtual void setLineWeight(const AcDb::LineWeight lw);
    virtual void setLineTypeScale(double dScale = 1.0);


    virtual Adesk::UInt16       color() const;
    virtual AcCmEntityColor     trueColor() const;
    virtual AcDbObjectId        layerId() const;
    virtual AcDbObjectId        lineTypeId() const;
    virtual AcGiFillType        fillType() const;
    virtual AcDb::LineWeight    lineWeight() const;
    virtual double              lineTypeScale() const;

    virtual void   setThickness(double dThickness);
    virtual double thickness() const;

private:
    Adesk::UInt16   mColorIndex;
    AcCmEntityColor mTrueColor;
    AcDbObjectId    mLayerId;
    AcDbObjectId    mLinetypeId;
    Adesk::LongPtr  mMarkerId;
    AcGiFillType    mFillType;
    AcDb::LineWeight  mLineWeight;
    double mLineTypeScale;
    double mThickness;
};

#endif
