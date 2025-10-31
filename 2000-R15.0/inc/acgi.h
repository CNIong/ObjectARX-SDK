#ifndef _ACGI_H
#define _ACGI_H 1
//
// (C) Copyright 1994-1999 by Autodesk, Inc. 
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
// This is the Graphics Interface for view independent and dependent
// elaboration of AcDb Entities.
//
// The AutoCAD Graphics Interface (AcGi) is a set of objects comprising 
// an API for elaborating the graphics representation of new AutoCAD
// entitites.  These objects support many geometric primitives, 
// transformation matrix querying, and graphical attributes. 

// Required for RX
//
#define ACGI_SERVICES  /*MSG0*/"AcGiServices"


// These are the current kinds of viewport regeneration modes.
// This mode is not settable by the user, but it can be queried 
// in case you need to take different actions for different
// regeneration modes.
//
typedef enum {
    eAcGiRegenTypeInvalid = 0,
    kAcGiStandardDisplay = 2,
    kAcGiHideOrShadeCommand,
    kAcGiRenderCommand,
    kAcGiForExplode,
    kAcGiSaveWorldDrawForProxy
} AcGiRegenType;

// No longer supported and will be removed
//
#define kAcGiSaveWorldDrawForR12 kAcGiForExplode 

// These are the current face filling modes
//
typedef enum {
     kAcGiFillAlways = 1,
     kAcGiFillNever
} AcGiFillType;

// These are the edge visibility types
//
typedef enum {
    kAcGiInvisible = 0,
    kAcGiVisible,
    kAcGiSilhouette
} AcGiVisibility;

// These are the types of arcs
//
typedef enum {
    kAcGiArcSimple = 0,                 // just the arc (not fillable)
    kAcGiArcSector,                     // area bounded by the arc and its center of curvature
    kAcGiArcChord                       // area bounded by the arc and its end points
} AcGiArcType;

// These are the possible types of vertex orientation 
// 
typedef enum {
    kAcGiCounterClockwise = -1,
    kAcGiNoOrientation = 0,
    kAcGiClockwise = 1
} AcGiOrientationType;

// This signifies how to calculate maximum deviation for tesselation
//
typedef enum {
    kAcGiMaxDevForCircle = 0,
    kAcGiMaxDevForCurve,
    kAcGiMaxDevForBoundary,
    kAcGiMaxDevForIsoline,
    kAcGiMaxDevForFacet
} AcGiDeviationType;

// Raster image organization
//
typedef enum {
    kAcGiBitonal,
    kAcGiPalette,
    kAcGiGray,
    kAcGiRGBA,
    kAcGiBGRA,
    kAcGiARGB,
    kAcGiABGR,
    kAcGiBGR,
    kAcGiRGB                              
} AcGiImageOrg;

// Raster image orientation
//
typedef enum {
    kAcGiXLeftToRightTopFirst,
    kAcGiXLeftToRightBottomFirst,
    kAcGiXRightToLeftTopFirst,
    kAcGiXRightToLeftBottomFirst,
    kAcGiYTopToBottomLeftFirst,
    kAcGiYTopToBottomRightFirst,
    kAcGiYBottomToTopLeftFirst,
    kAcGiYBottomToTopRightFirst
} AcGiImageOrient;

#include "rxobject.h"
#include "dbpl.h"
#include "gemat3d.h"
#include "gemat2d.h"
#include "gepnt2d.h"
#include "dbcolor.h"
#include "acdb.h"

#pragma pack (push, 8)

struct AcGiSentScanLines 
{
    enum IsmRequestStatus {
        eOk,                           // No Failure.
        eInvalidInput,                 // unknown image organization
        eInvalidColorDepth,            // mColorDepth to big or too small for request
        eInvalidPixelRequest,          // IefAffine (matrix scaling) failed for some reason
        eInvalidDeliveryMethod,        // Frame buffer delivery + compression - not valid
        eNoValidCompressors,           // no compressors for image data
        eInsufficientMemory            // low memory conditions.. very bad 
    };

    Adesk::Int8 *    mpPixelBuffer;          // one pointer per scan line
    Adesk::UInt32    mRowBytes;              // number of bytes per scan line
    void *  	     mpImageId;              // image id ptr
    Adesk::Int16     mIsCancelled;           // boolean: user cancelled
    Adesk::Int16     mHasFailed;             // boolean: request failed
    char *           mpCompressionModes;
    Adesk::UInt32    mBytes;
    IsmRequestStatus mRequestStatus;

};

struct AcGiRequestScanLines 
{
    enum IEDitherMethod 
    {
        kIEAnyPalette,
        kCustomDithering,
        kCustomDitheringMethod
    };

    enum IEColorSystem
    {
        kBitonal,
        kCMY,
        kCMYK,
        kRGB
    };

    enum ImagePaletteType
    {
        kFromDevice,
        kFromIeWholeImage
    };

    Adesk::UInt32       mPixelMinX;             // requested pixel corners
    Adesk::UInt32       mPixelMinY;
    Adesk::UInt32       mPixelMaxX;
    Adesk::UInt32       mPixelMaxY;
    AcGePoint2d         mLowerLeft;             // requested lower left corner
    AcGePoint2d         mUpperRight;            // requested upper right corner
    void *              mpImageId;              // image handle
    AcGiImageOrg        mImageOrg;              // enum type: palette, RGB 
    AcGiImageOrient     mImageOrient;           // enum type
    Adesk::Int16        mWindowId;              // acad window id
    Adesk::Int16        mColorDepth;            // bits per pixel
    union {
        Adesk::Int16 mBackgroundIndex;
        Adesk::Int8 mBackgroundRGB[3];
    }                   mBackgroundColor;       // current background color
    union {
        Adesk::Int16 mTransparentIndex;
        Adesk::Int8 mTransparentRGB[3];
    } mTransparentColor;                        // current background color
    union {
        Adesk::Int16 mEntityIndex;
        Adesk::Int8 mEntityRGB[3];
    }                   mEntityColor;           // bitonal image foregrnd color
    Adesk::Int32        mPaletteIncarnation;    // unique palette indentifier
    Adesk::Int8 *       mpPalette;              // pointer to 256 RGB triples
    Adesk::Int16        mIsDisplay;             // boolean: TRUE=dsply, FALSE=hrdcpy
    double              mRasterRatio;           // raster resolution
    AcGeMatrix2d        mPixelToDc;             // source pixel-to-dc transform
    char *              mpCompressionModes;
    ImagePaletteType    mPaletteType;
    void *              mpDataBuffer;
    Adesk::Int32        mRowWidth;
	Adesk::Int32		mNumRows;
    Adesk::Int32 const *mpBoundaryPoints;        // array of x,y pairs
    Adesk::UInt32       mnContours;              // number of contours 
    Adesk::Int32 const *mpCounts;                // pt count for each contour
};

/*NEW*/
struct AcGiClipBoundary
{
    AcGeVector3d        m_vNormal;
    AcGePoint3d         m_ptPoint;
    AcGePoint2dArray    m_aptPoints;    

    AcGeMatrix3d        m_xToClipSpace;// Transformation from model to clip space
    AcGeMatrix3d        m_xInverseBlockRefXForm; // Xform from block space to world

    Adesk::Boolean      m_bClippingFront;
    Adesk::Boolean      m_bClippingBack;
    double              m_dFrontClipZ;
    double              m_dBackClipZ;

    Adesk::Boolean      m_bDrawBoundary;
};

// To be removed
typedef enum AcGiColorIntensity 
{
    kAcGiMinColorIntensity = 0x0,
    kAcGiColorIntensity1   = 0x1,
    kAcGiColorIntensity2   = 0x2,
    kAcGiColorIntensity3   = 0x3,
    kAcGiColorIntensity4   = 0x4,
    kAcGiColorIntensity5   = 0x5,
    kAcGiColorIntensity6   = 0x6,
    kAcGiMaxColorIntensity = 0x7 
};


class AcGiSubEntityTraits;
class AcGiDrawableTraits;
class AcGiSubEntityTraitsImp;
class AcGiWorldGeometry;
class AcGiViewport;
class AcGiViewportGeometry;
class AcGiImpEdgeData;
class AcGiImpFaceData;
class AcGiImpVertexData;
class AcGiImpTextStyle;
class AcGiTextStyle;
class AcGiEdgeData;
class AcGiFaceData;
class AcGiVertexData;
class OwnerDraw;
/*NEW*/class AcGiContext;
/*NEW*/class AcGiCommonDraw;
/*NEW*/class AcGiGeometry;
/*NEW*/class AcCmEntityColor;
/*NEW*/struct TextParams;
/*NEW*/struct FontInfo;

typedef void (*AcGiWorldSegmentCallback)(const AcGePoint3d *);

/*NEW*/
class AcGiContext : public AcRxObject
//
// The base class for drawing contexts
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiContext);

    // These new methods will be made pure virtual
	//
	virtual Adesk::Boolean          isPsOut() const = 0;
    virtual Adesk::Boolean          isPlotGeneration() const = 0;
    virtual AcDbDatabase *          database() const = 0;
    /*NEW*/virtual bool             isBoundaryClipping() const = 0;

    // If your object requires to be redrawn for translation
    // transforms (MOVE) you can force the system to rerequest 
    // graphics for all objects in the current drag, including
    // yourself. Use this option only if you really need to. 
    // E.g. If your object needs to update for each step in a 
    // MOVE drag
    // 
    /*NEW*/virtual void          disableFastMoveDrag() const{};

    // Returns false if this is root level entity, e.g. a line in modelspace
    // and true if the object is contained within another object like a
    // block for example.
    //
    /*NEW*/virtual bool isNesting() const { return false; }

    /*NEW*/virtual AcCmEntityColor   effectiveColor() const { return AcCmEntityColor(); }
    /*NEW*/virtual AcDb::LineWeight  byBlockLineWeight() const { return AcDb::LineWeight::kLnWt000; }
    /*NEW*/virtual AcDbObjectId      byBlockPlotStyleNameId() const { return NULL; }

    /*NEW*/virtual bool supportsTrueTypeText() { return false; }

protected:

    friend class AcGiTextHook;
    friend class CShFont;
    friend class AcDbImpText;

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    // These APIs is provided for internal use only, do not use them
    // in external applications
    //
    virtual AcGiWorldSegmentCallback wSegTaker() const { return NULL; }
    virtual int getTrueTypeBoundingBox(AcGePoint3d const & location, unsigned short const * text, 
                                       int length, TextParams const * tp, 
                                       AcGePoint3d * bbox, float * char_widths)
                                        { return 0; }
    
    virtual int getTrueTypeTextExtents(char const *,unsigned int,double,int,int,
                                       int,short,short,double,double,
                                       AcGePoint2d &,AcGePoint2d &) 
                                       { return -1; }

    virtual int setTrueTypeTransform(const AcGePoint3d &,const AcGeVector3d &,
                                     double,double,double,bool,bool) 
                                     { return 0; }

    virtual int drawTrueTypeText(const char *,double,int,bool,
                                 const TextParams &,unsigned int){ return 0; }
    virtual int restoreTrueTypeTransform() { return 0; }
    virtual void bypassHiddenLineRemoval() { return; }
    virtual int setTextStyle(int);
    virtual long loadTrueTypeFont(const char *,bool,bool,int,int,FontInfo &)
                                  { return 0; }
    //
    // End of Internal use only API
    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
};

class AcGiCommonDraw : public AcRxObject
//
// The base class for drawing contexts
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiCommonDraw);
    virtual AcGiRegenType           regenType() const = 0;
    virtual Adesk::Boolean          regenAbort() const = 0;
    virtual AcGiSubEntityTraits&    subEntityTraits() const = 0;
    /*NEW*/virtual AcGiGeometry *   rawGeometry() const = 0;
    virtual Adesk::Boolean          isDragging() const = 0;

	// This function operates against the current active viewport
	//
    virtual double                deviation(const AcGiDeviationType, 
                                            const AcGePoint3d&) const = 0;
    virtual Adesk::UInt32           numberOfIsolines() const = 0;
	
    /*NEW*/virtual AcGiContext *      context() = 0;
};

class AcGiWorldDraw: public AcGiCommonDraw
//
// This class provides an API for generating graphics
// in model coordinates.  These graphics cannot be
// controlled by any viewport, as can AcGiViewportDraw.
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiWorldDraw);
    virtual AcGiWorldGeometry&      geometry() const = 0;
};

class AcGiViewportDraw: public AcGiCommonDraw 
//
// This class provides an API for generating graphics
// that can be sent to a particular viewport.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiViewportDraw);
    virtual AcGiViewport&        viewport() const = 0;
    virtual AcGiViewportGeometry& geometry() const = 0;
    virtual Adesk::UInt32        sequenceNumber() const = 0;
    virtual Adesk::Boolean       isValidId(const Adesk::UInt32 acgiId) const =0;
    virtual AcDbObjectId         viewportObjectId() const = 0;
};

class AcGiViewport: public AcRxObject 
//
// This class returns viewport info.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiViewport);

    // Get various view transformations.
    //
    virtual void getModelToEyeTransform(AcGeMatrix3d&) const = 0;
    virtual void getEyeToModelTransform(AcGeMatrix3d&) const = 0;
    virtual void getWorldToEyeTransform(AcGeMatrix3d&) const = 0;
    virtual void getEyeToWorldTransform(AcGeMatrix3d&) const = 0;

    // Perspective information.
    //
    virtual Adesk::Boolean isPerspective() const = 0;
    virtual Adesk::Boolean doPerspective(AcGePoint3d&) const = 0;
    virtual Adesk::Boolean doInversePerspective(AcGePoint3d&) const = 0;

    // Pixel information.
    //
    virtual void getNumPixelsInUnitSquare(const AcGePoint3d& givenWorldpt,
                                  AcGePoint2d& pixelArea) const = 0;

    // Camera information.
    //
    virtual void getCameraLocation(AcGePoint3d& location) const = 0;
    virtual void getCameraTarget(AcGePoint3d& target) const = 0;
    virtual void getCameraUpVector(AcGeVector3d& upVector) const = 0;

    // Viewport information.
    //
    virtual Adesk::UInt32 viewportId() const = 0;
    virtual Adesk::Int16  acadWindowId() const = 0;
    virtual void getViewportDcCorners(AcGePoint2d& lower_left,
                                      AcGePoint2d& upper_right) const = 0;

	// Clipping
	//
    virtual Adesk::Boolean getFrontAndBackClipValues(Adesk::Boolean& clip_front,
                                         Adesk::Boolean& clip_back,
                                         double& front,
                                         double& back) const = 0;

    // The factor returned here affects the linetype scaling in this viewport
    // 1.0 is the default. Returning a value of 2 will ensure
    // that the pattern is twice as big as per default.
    //
    /*NEW*/virtual double linetypeScaleMultiplier() const = 0;

    // If the calculated total pattern length of a linetyped object is less
    // than this (value in drawing units). Then a continuous pattern is used
    // instead. Several factors affect the linetype pattern length.
    // linetypeScaleMultiplier() is one of them. Note: If you set this value
    // high you could completely prevent the use of linetypes.
    //
    /*NEW*/virtual double linetypeGenerationCriteria() const = 0;

    // Returns true if the layer is not frozen in this viewport and not globally
    // frozen. Indicating that geometry on this layer should be regenerated.
    //
    /*NEW*/virtual Adesk::Boolean layerVisible(const AcDbObjectId & idLayer) const { return Adesk::kTrue; }

    /*NEW*/virtual AcGeVector3d viewDir() const { return AcGeVector3d::kZAxis; }

};

class AcGiSubEntityTraits: public AcRxObject 
//
// This class applies attributes to subsequently drawn AcGi geometry
// primitives.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiSubEntityTraits);

    // Set properties of drawn objects.
    //
    virtual void setColor(const Adesk::UInt16 color) = 0;
    /*NEW*/virtual void setTrueColor(const AcCmEntityColor& color) = 0;
    virtual void setLayer(const AcDbObjectId layerId) = 0;
    virtual void setLineType(const AcDbObjectId linetypeId) = 0;
    virtual void setSelectionMarker(const Adesk::Int32 markerId) = 0;
    virtual void setFillType(const AcGiFillType) = 0;
    /*NEW*/virtual void setLineWeight(const AcDb::LineWeight lw) = 0;
    /*NEW*/virtual void setLineTypeScale(double dScale = 1.0) = 0;
    /*NEW*/virtual void setThickness(double dThickness) = 0;
    /*NEW*/virtual void setPlotStyleName(AcDb::PlotStyleNameType type , const AcDbObjectId & id = AcDbObjectId::kNull) {}

    // Return current settings.
    //
    virtual Adesk::UInt16       color() const = 0;
    /*NEW*/virtual AcCmEntityColor trueColor() const = 0;
    virtual AcDbObjectId        layerId() const = 0;
    virtual AcDbObjectId        lineTypeId() const = 0;
    virtual AcGiFillType        fillType() const = 0;
    /*NEW*/virtual AcDb::LineWeight       lineWeight() const = 0;
    /*NEW*/virtual double lineTypeScale() const = 0;
    /*NEW*/virtual double thickness() const = 0;
    /*NEW*/virtual AcDb::PlotStyleNameType     getPlotStyleNameId(AcDbObjectId& idResult) const { return AcDb::kPlotStyleNameByLayer ; }
};

/*NEW*/
class AcGiDrawableTraits: public AcGiSubEntityTraits 
//
// This class applies attributes to all AcGi geometry primitives.
// for this drawable. This class is available to a drawable only during
// the setAttributes() call
//
{ 
public:

    friend class            AcDbLayerTableRecord;

    ACRX_DECLARE_MEMBERS(AcGiDrawableTraits);
    
    // Rather than using individual calls to the settings it is more efficient
    // to do make this single call for an entity.
    //
    virtual void setupForEntity(AcDbEntity * pEntity);

protected:

    enum LayerFlags {
        kNone       = 0x00,
        kOff        = 0x01,
        kFrozen     = 0x02,
        kZero       = 0x04
    };

    virtual void    setLayerFlags       (Adesk::UInt8 flags)        { };
};



/*NEW*/
class AcGiGeometry: public AcRxObject
//
// The base class for geometry toolkits
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiGeometry);

    // Coordinate transformations.
    //
    virtual void getModelToWorldTransform(AcGeMatrix3d&) const = 0;
    virtual void getWorldToModelTransform(AcGeMatrix3d&) const = 0;

    virtual Adesk::Boolean pushModelTransform(const AcGeVector3d & vNormal) = 0;// Uses arbitrary Axis algorythm
    virtual Adesk::Boolean pushModelTransform(const AcGeMatrix3d & xMat) = 0;
    virtual Adesk::Boolean popModelTransform() = 0;


    // For drawing various primitives.
    //
    virtual Adesk::Boolean  circle(const AcGePoint3d& center,
                                   const double radius,
                                   const AcGeVector3d& normal) const = 0;

    virtual Adesk::Boolean  circle(const AcGePoint3d&, const AcGePoint3d&,
                                   const AcGePoint3d&) const = 0;

    virtual Adesk::Boolean  circularArc(const AcGePoint3d& center,
                                   const double radius,
                                   const AcGeVector3d& normal,
                                   const AcGeVector3d& startVector,
                                   const double sweepAngle,
                                   const AcGiArcType arcType = kAcGiArcSimple) const = 0;

    virtual Adesk::Boolean  circularArc(const AcGePoint3d& start,
                                   const AcGePoint3d& point,
                                   const AcGePoint3d& end,
                                   const AcGiArcType arcType = kAcGiArcSimple) const = 0;
      
    virtual Adesk::Boolean  polyline(const Adesk::UInt32 nbPoints,
                                   const AcGePoint3d* pVertexList,
                  				   const AcGeVector3d* pNormal = NULL,
                                   Adesk::Int32 lBaseSubEntMarker = -1) const = 0;
      
    virtual Adesk::Boolean  polygon(const Adesk::UInt32 nbPoints,
                                   const AcGePoint3d* pVertexList) const = 0;

    virtual Adesk::Boolean  mesh(const Adesk::UInt32 rows,
                                 const Adesk::UInt32 columns,
                                 const AcGePoint3d* pVertexList,
                                 const AcGiEdgeData* pEdgeData = NULL,
                                 const AcGiFaceData* pFaceData = NULL,
                                 const AcGiVertexData* pVertexData = NULL
                                 ) const = 0;

    virtual Adesk::Boolean  shell(const Adesk::UInt32 nbVertex,
                                 const AcGePoint3d* pVertexList,
                                 const Adesk::UInt32 faceListSize,
                                 const Adesk::Int32* pFaceList,
                                 const AcGiEdgeData* pEdgeData = NULL,
                                 const AcGiFaceData* pFaceData = NULL,
                                 const AcGiVertexData* pVertexData = NULL,
                                 const struct resbuf* pResBuf = NULL
                                 ) const = 0;
      
    virtual Adesk::Boolean  text(const AcGePoint3d& position,
                                 const AcGeVector3d& normal,
                                 const AcGeVector3d& direction,
                                 const double height,
                                 const double width,
                                 const double oblique,
                                 const char* pMsg) const = 0;

    virtual Adesk::Boolean  text(const AcGePoint3d& position,
                                 const AcGeVector3d& normal,
                                 const AcGeVector3d& direction,
                                 const char* pMsg,
                                 const Adesk::Int32 length,
                                 const Adesk::Boolean raw,
                                 const AcGiTextStyle &pTextStyle
                                 ) const = 0;

    virtual Adesk::Boolean  xline(const AcGePoint3d&,
                                  const AcGePoint3d&) const = 0;

    virtual Adesk::Boolean  ray(const AcGePoint3d&,
                                const AcGePoint3d&) const = 0;

    virtual Adesk::Boolean  pline(const AcDbPolyline& lwBuf,
                                  Adesk::UInt32 fromIndex = 0,
                                  Adesk::UInt32 numSegs = 0
                                  ) const = 0;

    /*NEW*/virtual Adesk::Boolean  draw(AcGiDrawable*) const = 0;

    // If you push a clip boundary onto the stack you must pop it;
    //
    /*NEW*/virtual Adesk::Boolean          pushClipBoundary(AcGiClipBoundary * pBoundary) = 0;
    /*NEW*/virtual void                    popClipBoundary() = 0;
    /*NEW*/virtual Adesk::Boolean   worldLine(const AcGePoint3d pnts[2]) {
                                        AcGePoint3d polyPnts[2];
    	                                AcGeMatrix3d mat;
	                                    getWorldToModelTransform(mat);
	                                    polyPnts[0] = mat * pnts[0];
	                                    polyPnts[1] = mat * pnts[1];
	                                    return polyline(2, polyPnts);
                                    };
};

class AcGiWorldGeometry: public AcGiGeometry 
//
// This class contains the view independent, model coordinate,
// 3D geometry methods.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiWorldGeometry);

    virtual void setExtents(AcGePoint3d *pNewExtents) const = 0;

    // If this drawable is a block and has AcDbAttributes it must call
    // this method exactly once before sending the attributes to 
    // draw(). Once this is called the object may draw only attributes
    // and no more primitives
    // The attributes must be the last objects rendered
    //
    /*NEW*/ virtual void startAttributesSegment() {};
};

class AcGiViewportGeometry: public AcGiGeometry 
//
// This class contains the view dependent, model and drawing coordinate,
// 3D geometry methods.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiViewportGeometry);

    virtual Adesk::Boolean  polylineEye(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pPoints) const = 0;
    virtual Adesk::Boolean  polygonEye(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pPoints) const = 0;

    virtual Adesk::Boolean  polylineDc(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pPoints) const = 0;
    virtual Adesk::Boolean  polygonDc(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pPoints) const = 0;

    enum ImageSource {
        kFromDwg,
        kFromOleObject,
        kFromRender
    };

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
                Adesk::Boolean transparency,
                ImageSource source,
				const AcGeVector3d& unrotatedU,
				const AcGiImageOrg origionalImageOrg,
				const AcGeMatrix2d& unrotatedPixelToDc,
				const Adesk::UInt32 unrotatedImageWidth,
				const Adesk::UInt32 unrotatedImageHeight
                ) const = 0;

    virtual Adesk::Boolean  ownerDrawDc(
                long                       vpnumber, 
                long                       left, 
                long                       top, 
                long                       right, 
                long                       bottom, 
                const OwnerDraw*           pOwnerDraw
                ) const = 0;
};

class AcGiEdgeData: public AcRxObject 
//
// This class contains arrays of edge attributes for meshes and shells.
//
// NOTE:
//   Setting an 'improper' size array of color, layers, etc.
//   will cause unpredictable or fatal results.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiEdgeData);

    ~AcGiEdgeData();
    AcGiEdgeData();

    virtual void            setColors(const short *colors);
    virtual void            setLayers(const AcDbObjectId *layers);
    virtual void            setLineTypes(const AcDbObjectId *linetypes);
    virtual void            setSelectionMarkers(const Adesk::Int32* pSelectionMarkers);
    virtual void            setVisibility(const Adesk::UInt8* pVisibility);

    virtual short*          colors() const;
    virtual AcDbObjectId*   layerIds() const;
    virtual AcDbObjectId*   linetypeIds() const;
    virtual Adesk::Int32*   selectionMarkers() const;
    virtual Adesk::UInt8*   visibility() const;

private:
    AcGiImpEdgeData *mpAcGiImpEdgeData;
};

class AcGiFaceData: public AcRxObject 
//
// This class contains arrays of face attributes for meshes and shells.
//
// NOTE:
//   Setting an 'improper' size array of color, layers, etc.
//   will cause unpredictable or fatal results.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiFaceData);

    ~AcGiFaceData();
    AcGiFaceData();
    virtual void            setColors(const short *colors);
    virtual void            setLayers(const AcDbObjectId *layers);
    virtual void            setSelectionMarkers(const Adesk::Int32* pSelectionMarkers);
    virtual void            setNormals(const AcGeVector3d* pNormals);
    virtual void            setVisibility(const Adesk::UInt8* vis);

    virtual short*          colors() const;
    virtual AcDbObjectId*   layerIds() const;
    virtual Adesk::Int32*   selectionMarkers() const;
    virtual AcGeVector3d*   normals() const;
    virtual Adesk::UInt8*   visibility() const;
private:
    AcGiImpFaceData *mpAcGiImpFaceData;
};

class AcGiVertexData: public AcRxObject 
//
// This class contains arrays of vertex attributes for meshes and shells.
//
// NOTE:
//   Setting an 'improper' size array of color, layers, etc.
//   will cause unpredictable or fatal results.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiVertexData);
    ~AcGiVertexData();
    AcGiVertexData();
    virtual void setNormals(const AcGeVector3d* pNormals);
    virtual AcGeVector3d* normals() const;
    virtual void setOrientationFlag(const AcGiOrientationType oflag); 
    virtual AcGiOrientationType orientationFlag() const;

private:
    AcGiImpVertexData *mpAcGiImpVertexData;
};

class AcGiTextStyle: public AcRxObject 
// 
// This class contains methods to create and modify a text
// style object
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiTextStyle);
    ~AcGiTextStyle();
    AcGiTextStyle();

    AcGiTextStyle(
        const char*  fontName, 
        const char*  bigFontName, 
        const double textSize, 
        const double xScale, 
        const double obliqueAngle, 
        const double trPercent,

        const Adesk::Boolean isBackward,
        const Adesk::Boolean isUpsideDown,
        const Adesk::Boolean isVertical, 

        const Adesk::Boolean isOverlined,
        const Adesk::Boolean isUnderlined,
        
        const char*          styleName = NULL);

    virtual char loadStyleRec() const;
    virtual void setTextSize(const double size);
    virtual void setXScale(const double xScale);
    virtual void setObliquingAngle(const double obliquingAngle);

    virtual void setTrackingPercent(const double trPercent);

    virtual void setBackward(const Adesk::Boolean isBackward);
    virtual void setUpsideDown(const Adesk::Boolean isUpsideDown);
    virtual void setVertical(const Adesk::Boolean isVertical);

    virtual void setUnderlined(const Adesk::Boolean isUnderlined);
    virtual void setOverlined(const Adesk::Boolean isOverlined);

    virtual void setFileName(const char* fontName);
    virtual void setBigFontFileName(const char* bigFontFileName);

    virtual double textSize() const;
    virtual double xScale() const;
    virtual double obliquingAngle() const;

    virtual double trackingPercent() const;

    virtual Adesk::Boolean isBackward() const;
    virtual Adesk::Boolean isUpsideDown() const;
    virtual Adesk::Boolean isVertical() const;

    virtual Adesk::Boolean isUnderlined() const;
    virtual Adesk::Boolean isOverlined() const;

    virtual const char* fileName() const;
    virtual const char* bigFontFileName() const;

    virtual AcGePoint2d extents(const char* pStr, 
                const Adesk::Boolean penups,
                const int len,
                const Adesk::Boolean raw,
                AcGiWorldDraw *ctxt = NULL) const;

    virtual const char* styleName() const;
    virtual Acad::ErrorStatus setStyleName(const char*);
    
    virtual Acad::ErrorStatus setFont(const char* pTypeface, Adesk::Boolean bold,
                Adesk::Boolean italic, int charset, int pitchAndFamily);
    virtual Acad::ErrorStatus font(char*& pTypeface, Adesk::Boolean& bold, 
                Adesk::Boolean& italic, int& charset, int& pitchAndFamily) const;

    virtual Acad::ErrorStatus  extentsBox(  const char* pStr, 
                                            const Adesk::Boolean penups,
                                            const int len,
                                            const Adesk::Boolean raw,
                                            AcGePoint2d &extMin,
                                            AcGePoint2d &extMax,
                                            AcGiWorldDraw *ctxt = NULL) const;

    virtual void setTrackKerning(double trackPercent) const;

    virtual bool preLoaded() const;
    virtual void setPreLoaded(bool);

private:
    AcGiImpTextStyle *mpAcGiImpTextStyle;
};

#pragma pack (pop)

#endif
