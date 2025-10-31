//
//
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
// CUSTACGI.CPP


#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "custacgi.h"
#include "dbapserv.h"



//  Implementation of AsdkShellData class

AsdkShellData::AsdkShellData() 
  : mpVertexList(NULL),
    mpEdgeData(NULL),
    mpFaceData(NULL),
    mpFaceList(NULL),
    mpVertexData(NULL)
{
}

AsdkShellData::~AsdkShellData() 
{
    delete [] mpVertexList;
    delete mpEdgeData;
    delete mpFaceData;
    delete [] mpFaceList;
    delete mpVertexData;
}

unsigned int AsdkShellData::numberOfFaces() 
{
    //  Get number of faces:
    unsigned int numFaces = 0;
    Adesk::Int32*  pTempFaceList = mpFaceList;

    for (unsigned int i = 0; i < mFaceListSize; ) {
        ++numFaces;
        unsigned int facePoints = *pTempFaceList;
        pTempFaceList += (facePoints + 1);
        i += (facePoints + 1);
    }
    return numFaces;
}

unsigned int AsdkShellData::numberOfEdges() 
{
    int numEdges = 0;

    for (unsigned int i = 0; i < mFaceListSize; ) {
        numEdges += mpFaceList[i];
        i += mpFaceList[i + 1];
    }
    return numEdges;
}

Acad::ErrorStatus AsdkShellData::setFaceData(int colorIndex) 
{
//  If user overrides this function they must obey the following
//  contract.  
//  1.  Allocate memory for AcGiFaceData and point it to mpFaceData
//  2.  Allocate memory for all elements of AcGiFaceData.
//  They are free to set any value to the members of AcGiFaceData.
//  For example, the colors need not be the same for all faces as
//  is shown in this example.

    unsigned int numberFaces = numberOfFaces();

    short* pColors = new short[numberFaces];

    for (unsigned int i = 0; i < numberFaces; ++i)
        pColors[i] = colorIndex;

    // Set data members for AcgiFaceData to the above.
    mpFaceData = new AcGiFaceData;
    mpFaceData->setColors(pColors);
            
    return Acad::eOk;

}

//  Implementation of AsdkCustomSubEntityTraits object

ACRX_NO_CONS_DEFINE_MEMBERS(AsdkCustomSubEntityTraits,AcGiSubEntityTraits)

AsdkCustomSubEntityTraits::AsdkCustomSubEntityTraits()
{
    ads_printf(_T("\nCustomSubEntityTraits::CustomSubEntityTraits"));
    mColorIndex = 5;
    mMarkerId = 1;
    mFillType = kAcGiFillAlways;
}

AsdkCustomSubEntityTraits::~AsdkCustomSubEntityTraits() 
{
    ads_printf(_T("\nCustomSubEntityTraits::~CustomSubEntityTraits"));
}

void AsdkCustomSubEntityTraits::setColor(const Adesk::UInt16 color)
{
    ads_printf(_T("\nCustomSubEntityTraits::setColor"));
    mColorIndex = color;
}

void AsdkCustomSubEntityTraits::setTrueColor(const AcCmEntityColor& color)
{
    ads_printf(_T("\nCustomSubEntityTraits::setTrueColor"));
    mTrueColor = color;
}

void AsdkCustomSubEntityTraits::setLayer(const AcDbObjectId layerId)
{
    ads_printf(_T("\nCustomSubEntityTraits::setLayer"));
    mLayerId = layerId;
}

void AsdkCustomSubEntityTraits::setLineType(const AcDbObjectId linetypeId)
{
    ads_printf(_T("\nCustomSubEntityTraits::setLineType"));
    mLinetypeId = linetypeId;
}

void AsdkCustomSubEntityTraits::setSelectionMarker(const Adesk::LongPtr markerId)
{
    ads_printf(_T("\nCustomSubEntityTraits::setSelectionMarker"));
    mMarkerId = markerId;
}

void AsdkCustomSubEntityTraits::setFillType(const AcGiFillType fillType)
{
    ads_printf(_T("\nCustomSubEntityTraits::setFillType"));
    mFillType = fillType;
}

void AsdkCustomSubEntityTraits::setLineWeight(const AcDb::LineWeight lw)
{
    ads_printf(_T("\nCustomSubEntityTraits::setLineWeight"));
    mLineWeight = lw;
}


void AsdkCustomSubEntityTraits::setLineTypeScale(double dScale)
{
    ads_printf(_T("\nCustomSubEntityTraits::setLineTypeScale"));
    mLineTypeScale = dScale;
}


Adesk::UInt16       AsdkCustomSubEntityTraits::color() const
{
    ads_printf(_T("\nCustomSubEntityTraits::color"));
    return mColorIndex;
}

AcCmEntityColor     AsdkCustomSubEntityTraits::trueColor() const
{
    ads_printf(_T("\nCustomSubEntityTraits::trueColor"));
    return mTrueColor;
}

AcDbObjectId        AsdkCustomSubEntityTraits::layerId() const
{
    ads_printf(_T("\nCustomSubEntityTraits::layerId"));
    return mLayerId;
}

AcDbObjectId        AsdkCustomSubEntityTraits::lineTypeId() const
{
    ads_printf(_T("\nCustomSubEntityTraits::lineTypeId"));
    return mLinetypeId;
}

AcGiFillType        AsdkCustomSubEntityTraits::fillType() const
{
    ads_printf(_T("\nCustomSubEntityTraits::fillType"));
    return  mFillType;
}

AcDb::LineWeight    AsdkCustomSubEntityTraits::lineWeight() const
{
    ads_printf(_T("\nCustomSubEntityTraits::lineWeight"));
    return mLineWeight;
}

double              AsdkCustomSubEntityTraits::lineTypeScale() const
{
    ads_printf(_T("\nCustomSubEntityTraits::lineTypeScale"));
    return mLineTypeScale;
}

void   AsdkCustomSubEntityTraits::setThickness(double dThickness)
{
    ads_printf(_T("\nCustomSubEntityTraits::setThickness"));
    mThickness = dThickness;
}

double AsdkCustomSubEntityTraits::thickness() const
{
    ads_printf(_T("\nCustomSubEntityTraits::thickness"));
    return mThickness;
}


//  Implementation of AsdkCustomContext

ACRX_NO_CONS_DEFINE_MEMBERS(AsdkCustomContext,AcGiContext)

AsdkCustomContext::AsdkCustomContext()
{
}

AsdkCustomContext::~AsdkCustomContext()
{
}

Adesk::Boolean     AsdkCustomContext::isPsOut() const
{
    return Adesk::kFalse;
}
Adesk::Boolean     AsdkCustomContext::isPlotGeneration() const
{
    return Adesk::kFalse;
}

AcDbDatabase *     AsdkCustomContext::database() const
{
    return acdbHostApplicationServices()->workingDatabase();
}

bool     AsdkCustomContext::isBoundaryClipping() const
{
    return false;
}

//  Implementation of CustomWorldGeometry

ACRX_NO_CONS_DEFINE_MEMBERS(AsdkCustomWorldGeometry,AcGiWorldGeometry2)
AsdkCustomWorldGeometry::AsdkCustomWorldGeometry(AsdkCustomWorldDraw* pWorldDraw)
{
    mpCustomWorldDraw = pWorldDraw;  // store a back pointer to worldDraw object that instantiates
                                    // this worldGeometry object.
}

AsdkCustomWorldGeometry::~AsdkCustomWorldGeometry()
{
    ads_printf(_T("\nCustomWorldGeometry::~CustomWorldGeometry"));
}

void AsdkCustomWorldGeometry::getModelToWorldTransform(AcGeMatrix3d &pMatrix) const
{
    ads_printf(_T("\nCustomWorldGeometry::getModelToWorldTransform"));
    return;
}
void AsdkCustomWorldGeometry::getWorldToModelTransform(AcGeMatrix3d &pMatrix) const
{
    ads_printf(_T("\nCustomWorldGeometry::getWorldToModelTransform"));
    return;
}
void AsdkCustomWorldGeometry::setExtents(AcGePoint3d *pNewExtents) const
{
    ads_printf(_T("\nCustomWorldGeometry::setExtents"));
    return;
}

Adesk::Boolean  AsdkCustomWorldGeometry::circle(const AcGePoint3d& center,
                const double radius,
                const AcGeVector3d& normal
                ) const
{ 
    ads_printf(_T("\nCustomWorldGeometry::circle"));
    return Adesk::kFalse;
}

Adesk::Boolean  AsdkCustomWorldGeometry::circle(const AcGePoint3d& pt1,
                const AcGePoint3d& pt2,
                const AcGePoint3d& pt3
                ) const
{
    ads_printf(_T("\nCustomWorldGeometry::circle"));
    return Adesk::kFalse;
}

Adesk::Boolean  AsdkCustomWorldGeometry::circularArc(const AcGePoint3d& center,
                const double radius,
                const AcGeVector3d& normal,
                const AcGeVector3d& startVector,
                const double sweepAngle,
                const AcGiArcType arcType
                ) const
{
    ads_printf(_T("\nCustomWorldGeometry::circularArc"));
    return Adesk::kFalse;
}

Adesk::Boolean  AsdkCustomWorldGeometry::circularArc(const AcGePoint3d& start,
                const AcGePoint3d& point,
                const AcGePoint3d& end,
                const AcGiArcType arcType
                ) const
{
    ads_printf(_T("\nCustomWorldGeometry::circularArc"));
    return Adesk::kFalse;
}
      
Adesk::Boolean  AsdkCustomWorldGeometry::polyline(const Adesk::UInt32 nbPoints,
                         const AcGePoint3d* pVertexList,
                   const AcGeVector3d* pNormal,
                   Adesk::LongPtr lBaseSubEntMarker) const
{
    ads_printf(_T("\nCustomWorldGeometry::polyline"));
    return Adesk::kFalse;
}
      
Adesk::Boolean  AsdkCustomWorldGeometry::polygon(const Adesk::UInt32 nbPoints,
                const AcGePoint3d* pVertexList
                ) const
{
    ads_printf(_T("\nCustomWorldGeometry::polygon"));
    return Adesk::kFalse;
}

Adesk::Boolean  AsdkCustomWorldGeometry::mesh(const Adesk::UInt32 rows,
                const Adesk::UInt32 columns,
                const AcGePoint3d* pVertexList,
                const AcGiEdgeData* pEdgeData,
                const AcGiFaceData* pFaceData,
                const AcGiVertexData* pVertexData,
                const bool bAutoGenerateNormals
                ) const
{
    ads_printf(_T("\nCustomWorldGeometry::mesh"));
    return Adesk::kFalse;
}


Adesk::Boolean  AsdkCustomWorldGeometry::shell(const Adesk::UInt32 nbVertex,
                                 const AcGePoint3d* pVertexList,
                                 const Adesk::UInt32 faceListSize,
                                 const Adesk::Int32* pFaceList,
                                 const AcGiEdgeData* pEdgeData,
                                 const AcGiFaceData* pFaceData ,
                                 const AcGiVertexData* pVertexData,
                                 const struct resbuf* pResBuf,
                                 const bool bAutoGenerateNormals
                                 ) const
 
{
    ads_printf(_T("\nCustomWorldGeometry::shell"));

    //  Duplicate the incoming edgeData and assign the same to AsdkShellData's edgedata.

    mpCustomWorldDraw->shellData()->mNumVertices = nbVertex;  // Add number of vertices to AsdkShellData

    mpCustomWorldDraw->shellData()->mpVertexList = new AcGePoint3d[nbVertex]; // allocate memory for vertex array
    
    for (unsigned int i = 0; i < nbVertex; i++) {           //  Add all the vertices to AsdkShellData
        mpCustomWorldDraw->shellData()->mpVertexList[i] = (*pVertexList);
        ++pVertexList;
    }

    mpCustomWorldDraw->shellData()->mFaceListSize = faceListSize;

    mpCustomWorldDraw->shellData()->mpFaceList = new Adesk::Int32[faceListSize];
    for (unsigned int k = 0; k < faceListSize; k++) {
        mpCustomWorldDraw->shellData()->mpFaceList[k] = (*pFaceList);
        ++pFaceList;
    }

    return Adesk::kFalse;
}
      
Adesk::Boolean  AsdkCustomWorldGeometry::text(const AcGePoint3d& position,
                const AcGeVector3d& normal,
                const AcGeVector3d& direction,
                const double height,
                const double width,
                const double oblique,
                const TCHAR* pMsg
                ) const
{
    ads_printf(_T("\nCustomWorldGeometry::text"));
    return Adesk::kFalse;
}

Adesk::Boolean  AsdkCustomWorldGeometry::text(const AcGePoint3d& position,
                const AcGeVector3d& normal,
                const AcGeVector3d& direction,
                const TCHAR* pMsg,
                const Adesk::Int32 length,
                const Adesk::Boolean raw,
                const AcGiTextStyle &pTextStyle
                ) const
{
    ads_printf(_T("\nCustomWorldGeometry::text"));
    return Adesk::kFalse;
}

Adesk::Boolean  AsdkCustomWorldGeometry::xline(const AcGePoint3d& one_xline_point,
                const AcGePoint3d& a_different_xline_point
                ) const
{
    ads_printf(_T("\nCustomWorldGeometry::xline"));
    return Adesk::kFalse;
}

Adesk::Boolean  AsdkCustomWorldGeometry::pline(const AcDbPolyline& lwBuf,
                                  Adesk::UInt32 fromIndex,
                                  Adesk::UInt32 numSegs
                                  ) const
{
    ads_printf(_T("\nCustomWorldGeometry::xline"));
    return Adesk::kFalse;
}



Adesk::Boolean  AsdkCustomWorldGeometry::ray(const AcGePoint3d& rays_starting_point,
                const AcGePoint3d& a_different_ray_point
                ) const
{
    ads_printf(_T("\nCustomWorldGeometry::ray"));
    return Adesk::kFalse;
}


Adesk::Boolean AsdkCustomWorldGeometry::pushModelTransform(const AcGeVector3d & vNormal)
{
    ads_printf(_T("\nCustomWorldGeometry::pushModelTransfrom (vec)"));
    return Adesk::kFalse;
}

Adesk::Boolean AsdkCustomWorldGeometry::pushModelTransform(const AcGeMatrix3d & xMat)
{
    ads_printf(_T("\nCustomWorldGeometry::pushModelTransfrom (mat)"));
    return Adesk::kFalse;
}

Adesk::Boolean AsdkCustomWorldGeometry::popModelTransform()
{
    ads_printf(_T("\nCustomWorldGeometry::popModelTransform"));
    return Adesk::kFalse;
}

Adesk::Boolean  AsdkCustomWorldGeometry::draw(AcGiDrawable*) const
{
    ads_printf(_T("\nCustomWorldGeometry::draw"));
    return Adesk::kFalse;
}

Adesk::Boolean  AsdkCustomWorldGeometry::pushClipBoundary(AcGiClipBoundary * pBoundary)
{
    ads_printf(_T("\nCustomWorldGeometry::pushClipBoundary"));
    return Adesk::kFalse;
}

void            AsdkCustomWorldGeometry::popClipBoundary()
{
    ads_printf(_T("\nCustomWorldGeometry::popClipBoundary"));
}

Adesk::Boolean
AsdkCustomWorldGeometry::image   (
                const AcGiImageBGRA32& imageSource,
                const AcGePoint3d& position,
                const AcGeVector3d& u,
                const AcGeVector3d& v,
                AcGiGeometry::TransparencyMode transparencyMode
                ) const
{
    ads_printf(_T("\nCustomWorldGeometry::image"));
    return Adesk::kFalse;
}

Adesk::Boolean 
AsdkCustomWorldGeometry::rowOfDots   (
                int count,
                const AcGePoint3d&     start,
                const AcGeVector3d&     step
                ) const
{
    ads_printf(_T("\nCustomWorldGeometry::rowOfDots"));
    return Adesk::kFalse;
}

Adesk::Boolean 
AsdkCustomWorldGeometry::ellipticalArc   (
                 const AcGePoint3d&         center,
                 const AcGeVector3d&        normal,
                 double                     majorAxisLength,
                 double                     minorAxisLength,
                 double                     startDegreeInRads,
                 double                     endDegreeInRads,
                 double                     tiltDegreeInRads,
                 bool                       isPie ) const
{
    ads_printf(_T("\nCustomWorldGeometry::ellipticalArc"));
    return Adesk::kFalse;
}

Adesk::Boolean 
AsdkCustomWorldGeometry::symbol  (
                 AcGiSymbolType type,
                 const Adesk::UInt32 nbPoints,
                 const AcGePoint3d* pPoints,
                 const AcCmEntityColor& outlineColor,
                 const AcCmEntityColor& fillColor
                 ) const
{
    ads_printf(_T("\nCustomWorldGeometry::grip"));
    return Adesk::kFalse;
}

void 
AsdkCustomWorldGeometry::pushPositionTransform (AcGiPositionTransformBehavior behavior, const AcGePoint2d& offset)
{
    ads_printf(_T("\nCustomWorldGeometry::pushPositionTransform"));
}


void 
AsdkCustomWorldGeometry::pushScaleTransform (AcGiScaleTransformBehavior behavior, const AcGePoint2d& extents)
{
    ads_printf(_T("\nCustomWorldGeometry::pushScaleTransform"));
}

void 
AsdkCustomWorldGeometry::pushOrientationTransform (AcGiOrientationTransformBehavior behavior)
{
    ads_printf(_T("\nCustomWorldGeometry::pushOrientationTransform"));
}
//  Implementation of CustomWorldDraw class

ACRX_NO_CONS_DEFINE_MEMBERS(AsdkCustomWorldDraw,AcGiWorldDraw)

AsdkCustomWorldDraw::AsdkCustomWorldDraw()
 : mDeviation(0.1) 
{
    ads_printf(_T("\nCustomWorldDraw::CustomWorldDraw"));
    mpShellData = new AsdkShellData;
    mpContext         = new AsdkCustomContext;
    mpSubEntityTraits = new AsdkCustomSubEntityTraits;
    mpWorldGeometry   = new AsdkCustomWorldGeometry(this);
}

AsdkCustomWorldDraw::~AsdkCustomWorldDraw()
{
    ads_printf(_T("\nCustomWorldDraw::~CustomWorldDraw"));
    delete mpSubEntityTraits;
    delete mpWorldGeometry;
    delete mpContext;
    // Once the worldDraw object gets ShellData, the custom
    // draw entity will hold its pointer.  Hence mpShellData
    // is not deleted here, it is deleted by the CustomDrawEntity's
    // destructor.
}

AcGiRegenType           AsdkCustomWorldDraw::regenType() const
{
    ads_printf(_T("\nCustomWorldDraw::regenType"));
    return kAcGiHideOrShadeCommand;
}

Adesk::Boolean          AsdkCustomWorldDraw::regenAbort() const
{
    ads_printf(_T("\nCustomWorldDraw::regenAbort"));
    return Adesk::kFalse;
}

AcGiSubEntityTraits&    AsdkCustomWorldDraw::subEntityTraits() const
{
    ads_printf(_T("\nCustomWorldDraw::subEntityTraits"));
    return *mpSubEntityTraits;
}

AcGiGeometry *          AsdkCustomWorldDraw::rawGeometry() const
{
    ads_printf(_T("\nCustomWorldDraw::rawGeometry"));
    return mpWorldGeometry;
}

AcGiWorldGeometry&      AsdkCustomWorldDraw::geometry() const
{
    ads_printf(_T("\nCustomWorldDraw::geometry"));
    return *mpWorldGeometry;
}

Adesk::Boolean          AsdkCustomWorldDraw::isDragging() const
{
    ads_printf(_T("\nCustomWorldDraw::isDragging"));
    return Adesk::kFalse;
}

double                  AsdkCustomWorldDraw::deviation(const AcGiDeviationType, 
                          const AcGePoint3d&) const
{
    ads_printf(_T("\nCustomWorldDraw::deviation"));
    return mDeviation;
}

Adesk::UInt32           AsdkCustomWorldDraw::numberOfIsolines() const
{
    ads_printf(_T("\nCustomWorldDraw::numberOfIsolines"));
    return 1;
}

AcGiContext *  AsdkCustomWorldDraw::context()
{
    ads_printf(_T("\nCustomWorldDraw::context"));
    return mpContext;
}

AsdkShellData* AsdkCustomWorldDraw::shellData()
{
    return mpShellData;
}

void AsdkCustomWorldDraw::setDeviation(double dev)
{
    mDeviation = dev;
}
