#ifndef _ACGI_H
#define _ACGI_H 1
//
// (C) Copyright 1994-2006 by Autodesk, Inc. 
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
#define ACGI_SERVICES  ACRX_T(/*MSG0*/"AcGiServices")

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

// scale filter method to use
typedef enum {
    kDefaultScaleFilter,
    kNearestScaleFilter,
    kBellScaleFilter,
    kMitchellScaleFilter,
    kTriangleScaleFilter,
    kCubicScaleFilter,
    kBsplineScaleFilter,
    kLanczos3ScaleFilter
} AcGiScaleFilterType;

// rotation filter method to use
typedef enum {
    kDefaultRotationFilter,
    kInterpolatedRotationFilter,
    kNearestRotationFilter,
} AcGiRotationFilterType;

// how to interpret nRasterRatio
typedef enum {
    kDefaultScale,                  // classic scaling scheme
    kRelativeScale,                 // relative to original image, do rotation
    kUnTransformedScale             // original pixels, unscaled, unrotated
} AcGiScaleType;

enum AcGiEdgeStyleMaskValues {
    kAcGiNoEdgeStyleMask = 0,
    kAcGiJitterMask      = 1,
    kAcGiOverhangMask    = 2,
    kAcGiEdgeColorMask   = 4
};
typedef unsigned int AcGiEdgeStyleMask;

#include "rxobject.h"
#include "AdAChar.h"
#include "dbpl.h"
#include "gemat3d.h"
#include "gemat2d.h"
#include "gepnt2d.h"
#include "dbcolor.h"
#include "acdb.h"
#include "AcGiStyleAttributes.h"
#include "assert.h"

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
    void *           mpImageId;              // image id ptr
    Adesk::Int16     mIsCancelled;           // boolean: user cancelled
    Adesk::Int16     mHasFailed;             // boolean: request failed
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

    AcGiRequestScanLines()
        : mPixelMinX          (0)
        , mPixelMinY          (0)
        , mPixelMaxX          (0)
        , mPixelMaxY          (0)
        , mpImageId           (0)
        , mImageOrg           (kAcGiBitonal)
        , mImageOrient        (kAcGiXLeftToRightTopFirst)
        , mWindowId           (0)
        , mColorDepth         (8)
        , mPaletteIncarnation (0)
        , mpPalette           (0)
        , mIsDisplay          (0)
        , mRasterRatio        (1.0)
        , mPaletteType        (kFromDevice)
        , mpDataBuffer        (0)
        , mRowWidth           (0)
        , mpBoundaryPoints    (0)
        , mnContours          (0)
        , mpCounts            (0)
        , mScalingType        (kDefaultScale)
        , mScaleFilterType    (kDefaultScaleFilter)
        , mRotationFilterType (kDefaultRotationFilter)
        , mnTotalChunks       (0)
        , mnThisChunk         (0)
    {
    }

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
    ImagePaletteType    mPaletteType;
    void *              mpDataBuffer;
    Adesk::Int32        mRowWidth;
    Adesk::Int32        mNumRows;
    Adesk::Int32 const *mpBoundaryPoints;        // array of x,y pairs
    Adesk::UInt32       mnContours;              // number of contours 
    Adesk::Int32 const *mpCounts;                // pt count for each contour
    AcGiScaleType          mScalingType;
    AcGiScaleFilterType    mScaleFilterType;
    AcGiRotationFilterType mRotationFilterType;
    short                  mnTotalChunks;       // how many chunks will be requested
    short                  mnThisChunk;         // 1 based count of chunks
};

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

class OwnerDraw3d
{
public:
    virtual ~OwnerDraw3d(void) {};
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
class AcGiContextImp;
class AcGiContext;
class AcGiCommonDraw;
class AcGiGeometry;
class AcCmEntityColor;
struct TextParams;
struct FontInfo;
class AcGiMapper;
class AcGiViewportTraits;
class AcGiVisualStyleTraits;
class AcGiEdgeStyle;
class AcGiContextualColors;

typedef void (*AcGiWorldSegmentCallback)(const AcGePoint3d *);

bool acgiIsValidClipBoundary(const AcGePoint2dArray& pts);


class AcGiContext : public AcRxObject
//
// The base class for drawing contexts
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiContext);

    virtual Adesk::Boolean          isPsOut() const = 0;
    virtual Adesk::Boolean          isPlotGeneration() const = 0;
    virtual AcDbDatabase *          database() const = 0;
    virtual bool             isBoundaryClipping() const = 0;

    // If your object requires to be redrawn for translation
    // transforms (MOVE) you can force the system to rerequest 
    // graphics for all objects in the current drag, including
    // yourself. Use this option only if you really need to. 
    // E.g. If your object needs to update for each step in a 
    // MOVE drag
    // 
    virtual void          disableFastMoveDrag() const{};

    // Returns false if this is root level entity, e.g. a line in modelspace
    // and true if the object is contained within another object like a
    // block for example.
    //
    virtual bool isNesting() const { return false; }

    virtual AcCmEntityColor   effectiveColor() const { return AcCmEntityColor(); }
    virtual AcDb::LineWeight  byBlockLineWeight() const { return AcDb::kLnWt000; }
    virtual AcDbObjectId      byBlockPlotStyleNameId() const { return NULL; }
    virtual AcDbObjectId      byBlockMaterialId() const { return AcDbObjectId::kNull; }

    virtual bool supportsTrueTypeText() { return false; }
    virtual bool supportsOwnerDraw() {return false;}
    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    // These APIs is provided for internal use only, do not use them
    // in external applications
    //
    virtual AcGiContextImp * getImpPtr() { return NULL; }
    virtual const AcGiContextImp * getConstImpPtr() const { return NULL; }
    //
    // End of Internal use only API
    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

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
    virtual int getTrueTypeBoundingBox(AcGePoint3d const & location,
                                       const wchar_t * text, 
                                       int length, TextParams const * tp, 
                                       AcGePoint3d * bbox, float * char_widths)
                                        { return 0; }
    
    virtual int getTrueTypeTextExtents(ACHAR const *,unsigned int,double,
                                       int,int,
                                       int,short,short,double,double,
                                       AcGePoint2d &,AcGePoint2d &) 
                                       { return -1; }

    virtual int setTrueTypeTransform(const AcGePoint3d &,const AcGeVector3d &,
                                     double,double,double,bool,bool) 
                                     { return 0; }

    virtual int drawTrueTypeText(const ACHAR *,double,int,bool,
                                 const TextParams &,unsigned int){ return 0; }
    virtual int restoreTrueTypeTransform() { return 0; }
    virtual void bypassHiddenLineRemoval() { return; }
    virtual int setTextStyle(int);
    virtual long loadTrueTypeFont(const ACHAR *,bool,bool,int,int,FontInfo &)
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
    virtual AcGiGeometry *   rawGeometry() const = 0;
    virtual Adesk::Boolean          isDragging() const = 0;

    // This function operates against the current active viewport
    //
    virtual double                deviation(const AcGiDeviationType, 
                                            const AcGePoint3d&) const = 0;
    virtual Adesk::UInt32           numberOfIsolines() const = 0;
    
    virtual AcGiContext *      context() = 0;

    virtual bool               secondaryCall() const { return false; }
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
                                  AcGePoint2d& pixelArea,
                                  bool includePerspective = true) const = 0;

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
    virtual double linetypeScaleMultiplier() const = 0;

    // If the calculated total pattern length of a linetyped object is less
    // than this (value in drawing units). Then a continuous pattern is used
    // instead. Several factors affect the linetype pattern length.
    // linetypeScaleMultiplier() is one of them. Note: If you set this value
    // high you could completely prevent the use of linetypes.
    //
    virtual double linetypeGenerationCriteria() const = 0;

    // Returns true if the layer is not frozen in this viewport and not globally
    // frozen. Indicating that geometry on this layer should be regenerated.
    //
    virtual Adesk::Boolean layerVisible(const AcDbObjectId & idLayer) const { return Adesk::kTrue; }

    virtual AcGeVector3d viewDir() const { return AcGeVector3d::kZAxis; }

    // Provides access to color information that is context-sensitive.
    //
    virtual const AcGiContextualColors* contextualColors() const { return NULL; }
};

class AcGiContextualColors : public AcRxObject
{
//
// This class returns color information for objects that can have different colors
// in different display contexts.
//
public:
    ACRX_DECLARE_MEMBERS(AcGiContextualColors);

    // Access to colors.
    virtual Adesk::UInt32 gridMajorLines() const = 0;
    virtual Adesk::UInt32 gridMinorLines() const = 0;
    virtual Adesk::UInt32 gridAxisLines() const = 0;
    virtual int gridMajorLineTintXYZ() const = 0;
    virtual int gridMinorLineTintXYZ() const = 0;
    virtual int gridAxisLineTintXYZ() const = 0;

    virtual Adesk::UInt32 lightGlyphs() const = 0;
    virtual Adesk::UInt32 lightHotspot() const = 0;
    virtual Adesk::UInt32 lightFalloff() const = 0;
    virtual Adesk::UInt32 lightStartLimit() const = 0;
    virtual Adesk::UInt32 lightEndLimit() const = 0;

    virtual Adesk::UInt32 cameraGlyphs() const = 0;
    virtual Adesk::UInt32 cameraFrustrum() const = 0;
    virtual Adesk::UInt32 cameraClipping() const = 0;

    // Access to context parameters.
    virtual void setContextFlags(Adesk::UInt32 flg, bool set = true) = 0;
    virtual bool flagsSet(Adesk::UInt32 flg) const = 0;
};


/* AutoCAD reserves a block of 64K marker ids for custom use. The range from INT_MIN thu INT_MIN+65535
   Callers of setSelectionMarker should not use this range except for the values below.
   The value of 0 has special meaning and indicates no selection marker.
*/
#define AcGiSelectionMarkerACADReserveStart         (-2147483647 - 1)   // INT_MIN without using limits.h
#define AcGiSelectionMarkerACADReserveEnd           (AcGiSelectionMarkerACADReserveStart + 65535)

#define AcGiSelectionMarkerACADSelectionPreviewOff  (AcGiSelectionMarkerACADReserveStart + 1)   // turn off selection preview display
#define AcGiSelectionMarkerACADSelectionPreviewOn   (AcGiSelectionMarkerACADReserveStart + 2)   // turn on selection preview display

class AcGiSubEntityTraits: public AcRxObject 
//
// This class applies attributes to subsequently drawn AcGi geometry
// primitives.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiSubEntityTraits);

    enum DrawFlags
    {
        kNoDrawFlags        =   0,
        kDrawBackfaces      =   1,
    };

    enum ShadowFlags
    {
        kShadowsCastAndReceive  = 0x00,
        kShadowsDoesNotCast     = 0x01,
        kShadowsDoesNotReceive  = 0x02,
        kShadowsIgnore          = kShadowsDoesNotCast | kShadowsDoesNotReceive,
    };

    // Set properties of drawn objects.
    //
    virtual void              setColor              (const Adesk::UInt16 color) = 0;
    virtual void              setTrueColor          (const AcCmEntityColor& color) = 0;
    virtual void              setLayer              (const AcDbObjectId layerId) = 0;
    virtual void              setLineType           (const AcDbObjectId linetypeId) = 0;
    virtual void              setSelectionMarker    (const Adesk::Int32 markerId) = 0;
    virtual void              setFillType           (const AcGiFillType) = 0;
    virtual void              setLineWeight         (const AcDb::LineWeight lw) = 0;
    virtual void              setLineTypeScale      (double dScale = 1.0) = 0;
    virtual void              setThickness          (double dThickness) = 0;
    virtual void              setVisualStyle        (const AcDbObjectId visualStyleId);
    virtual Acad::ErrorStatus setEdgeStyleOverride  (AcGiEdgeStyleMask mask, const AcGiEdgeStyle& edgeStyle);
    virtual void              setPlotStyleName      (AcDb::PlotStyleNameType type, const AcDbObjectId & id = AcDbObjectId::kNull) {}
    virtual void              setMaterial           (const AcDbObjectId materialId);
    virtual void              setMapper             (const AcGiMapper * mapper);
    virtual void              setSectionable        (bool bSectionable);
    virtual Acad::ErrorStatus setDrawFlags          (Adesk::UInt32 flags);
    virtual Acad::ErrorStatus setShadowFlags        (ShadowFlags flags);
    virtual void              setSelectionGeom      (bool bSelectionflag);

    // Return current settings.
    //
    virtual Adesk::UInt16           color               (void) const = 0;
    virtual AcCmEntityColor         trueColor           (void) const = 0;
    virtual AcDbObjectId            layerId             (void) const = 0;
    virtual AcDbObjectId            lineTypeId          (void) const = 0;
    virtual AcGiFillType            fillType            (void) const = 0;
    virtual AcDb::LineWeight        lineWeight          (void) const = 0;
    virtual double                  lineTypeScale       (void) const = 0;
    virtual double                  thickness           (void) const = 0;
    virtual AcDbObjectId            visualStyle         (void) const;
    virtual Acad::ErrorStatus       edgeStyleOverride   (AcGiEdgeStyleMask& mask, AcGiEdgeStyle& edgeStyle) const;
    virtual AcDb::PlotStyleNameType getPlotStyleNameId  (AcDbObjectId& idResult) const { return AcDb::kPlotStyleNameByLayer ; }
    virtual AcDbObjectId            materialId          (void) const;
    virtual const AcGiMapper *      mapper              (void) const;
    virtual bool                    sectionable         (void) const;
    virtual Adesk::UInt32           drawFlags           (void) const;
    virtual ShadowFlags             shadowFlags         (void) const;
    virtual bool                    selectionGeom       (void) const;
};

inline void 
AcGiSubEntityTraits::setMaterial(const AcDbObjectId materialId)
{
}

inline AcDbObjectId  
AcGiSubEntityTraits::materialId(void) const
{
    return AcDbObjectId::kNull;
}

inline
void AcGiSubEntityTraits::setMapper (const AcGiMapper * mapper)
{
}

inline const AcGiMapper * 
AcGiSubEntityTraits::mapper (void) const
{
    return NULL;
}

inline void 
AcGiSubEntityTraits::setVisualStyle(AcDbObjectId visualStyleId)
{
}

inline AcDbObjectId
AcGiSubEntityTraits::visualStyle(void) const
{
    return AcDbObjectId::kNull;
}

inline Acad::ErrorStatus 
AcGiSubEntityTraits::setEdgeStyleOverride (AcGiEdgeStyleMask mask, const AcGiEdgeStyle& edgeStyle)
{
    return Acad::eNotImplementedYet;
}

inline Acad::ErrorStatus 
AcGiSubEntityTraits::edgeStyleOverride (AcGiEdgeStyleMask& mask, AcGiEdgeStyle& edgeStyle) const
{
    return Acad::eNotImplementedYet;
}

inline void 
AcGiSubEntityTraits::setSectionable(bool bSectionable)
{
}

inline bool 
AcGiSubEntityTraits::sectionable(void) const
{
    return false;
}

inline Acad::ErrorStatus
AcGiSubEntityTraits::setDrawFlags (Adesk::UInt32 flags)
{
    return Acad::eNotImplementedYet;
}

inline Adesk::UInt32 
AcGiSubEntityTraits::drawFlags (void) const
{
    return 0;
}

inline Acad::ErrorStatus 
AcGiSubEntityTraits::setShadowFlags (ShadowFlags flags)
{
    return Acad::eNotImplementedYet;
}

inline AcGiSubEntityTraits::ShadowFlags
AcGiSubEntityTraits::shadowFlags (void) const
{
    return kShadowsCastAndReceive;
}

inline void
AcGiSubEntityTraits::setSelectionGeom ( bool )
{
}

inline bool 
AcGiSubEntityTraits::selectionGeom ( void ) const
{
    return false;
}


class AcGiDrawableTraits: public AcGiSubEntityTraits 
//
// This class applies attributes to all AcGi geometry primitives
// for this drawable. This class is available to a drawable only during
// the setAttributes() call.
//
{ 
public:

    friend class            AcDbLayerTableRecord;

    ACRX_DECLARE_MEMBERS(AcGiDrawableTraits);
    
    // Rather than using individual calls to the settings it is more efficient
    // to make this single call for an entity.
    //
    virtual void setupForEntity(AcDbEntity * pEntity);

    // Drawables that emit light can add one or more to the model. A unique
    // object id must be used for each light, though an object may pass
    // in its own object id.
    // This implementation ignores light information, so derived classes
    // must override this method in order to collect and use the illumination.
    //
    virtual void addLight(const AcDbObjectId& lightId);

protected:

    enum LayerFlags {
        kNone       = 0x00,
        kOff        = 0x01,
        kFrozen     = 0x02,
        kZero       = 0x04
    };

    virtual void    setLayerFlags       (Adesk::UInt8 flags)        { };
};

// Default implementation does nothing with the illumination data.
//
inline void 
AcGiDrawableTraits::addLight(const AcDbObjectId& lightId)
{
}


class AcGiNonEntityTraits : public AcGiDrawableTraits
// 
// This class implements empty AcGiDrawableTraits and AcGiSubEntityTraits
// interfaces, to allow non-entity drawables such as materials to elaborate 
// their unique properties through AcGiDrawableTraits
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiNonEntityTraits);

    // AcGiDrawableTraits interface
    virtual void                setupForEntity      (AcDbEntity* pEntity);
    virtual void                addLight(const AcDbObjectId& id);

    // AcGiSubEntityTraits interface
    virtual void                setColor            (const Adesk::UInt16 color);
    virtual Adesk::UInt16       color               (void) const;
    virtual void                setTrueColor        (const AcCmEntityColor& color);
    virtual AcCmEntityColor     trueColor           (void) const;
    virtual void                setLayer            (const AcDbObjectId layerId);
    virtual AcDbObjectId        layerId             (void) const;
    virtual void                setLineType         (const AcDbObjectId linetypeId);
    virtual AcDbObjectId        lineTypeId          (void) const;
    virtual void                setSelectionMarker  (const Adesk::Int32 markerId);
    virtual void                setFillType         (const AcGiFillType fillType);
    virtual AcGiFillType        fillType            (void) const;
    virtual void                setLineWeight       (const AcDb::LineWeight lw);
    virtual AcDb::LineWeight    lineWeight          (void) const;
    virtual void                setThickness        (double thickness);
    virtual double              thickness           (void) const;
    virtual void                setLineTypeScale    (double dScale);
    virtual double              lineTypeScale       (void) const;
    virtual void                setMaterial         (const AcDbObjectId matId);
    virtual AcDbObjectId        materialId          (void) const;
    virtual void                setSelectionGeom    (bool bSelectionflag);
    virtual bool                selectionGeom       ( void ) const;
};

inline void 
AcGiNonEntityTraits::setupForEntity (AcDbEntity* pEntity)
{
    assert(false);
}

inline void 
AcGiNonEntityTraits::addLight(const AcDbObjectId& id)
{
    assert(false);
}

inline void 
AcGiNonEntityTraits::setColor (const Adesk::UInt16 color)     
{
    assert(false);
}

inline Adesk::UInt16 
AcGiNonEntityTraits::color (void) const      
{ 
    assert(false);
    return 0; 
}

inline void 
AcGiNonEntityTraits::setTrueColor (const AcCmEntityColor& color)  
{ 
    assert(false);
}

inline AcCmEntityColor 
AcGiNonEntityTraits::trueColor (void) const
{ 
    assert(false);
    return AcCmEntityColor(); 
}

inline void 
AcGiNonEntityTraits::setLayer (const AcDbObjectId layerId)    
{ 
    assert(false);
}

inline AcDbObjectId 
AcGiNonEntityTraits::layerId (void) const      
{ 
    assert(false);
    return AcDbObjectId::kNull; 
}

inline void 
AcGiNonEntityTraits::setLineType (const AcDbObjectId linetypeId)
{  
    assert(false);
}

inline AcDbObjectId AcGiNonEntityTraits::lineTypeId (void) const      
{ 
    assert(false);
    return  AcDbObjectId::kNull; 
}

inline void 
AcGiNonEntityTraits::setMaterial(const AcDbObjectId matId)
{  
    assert(false);
}

inline AcDbObjectId AcGiNonEntityTraits::materialId (void) const      
{ 
    assert(false);
    return  AcDbObjectId::kNull; 
}

inline void 
AcGiNonEntityTraits::setSelectionMarker (const Adesk::Int32 markerId)   
{ 
    assert(false);
}

inline void 
AcGiNonEntityTraits::setFillType (const AcGiFillType fillType)   
{ 
    assert(false);
}

inline AcGiFillType 
AcGiNonEntityTraits::fillType (void) const      
{ 
    assert(false);
    return kAcGiFillAlways;
}

inline void 
AcGiNonEntityTraits::setLineWeight (const AcDb::LineWeight lw)     
{ 
    assert(false);
}

inline AcDb::LineWeight 
AcGiNonEntityTraits::lineWeight (void) const      
{ 
    assert(false);
    return AcDb::kLnWt000; 
}

inline void 
AcGiNonEntityTraits::setThickness (double thickness)
{ 
    assert(false);
}

inline double 
AcGiNonEntityTraits::thickness (void) const      
{ 
    assert(false);
    return 0.0; 
}

inline void 
AcGiNonEntityTraits::setLineTypeScale (double dScale)   
{  
    assert(false);
}

inline double 
AcGiNonEntityTraits::lineTypeScale (void) const      
{ 
    assert(false);
    return 0.0; 
}

inline void
AcGiNonEntityTraits::setSelectionGeom ( bool )
{
    assert(false);
}

inline bool 
AcGiNonEntityTraits::selectionGeom ( void ) const
{
    assert(false);
    return false;
}

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
                                 const AcGiVertexData* pVertexData = NULL,
                                 const bool bAutoGenerateNormals = true
                                 ) const = 0;

    virtual Adesk::Boolean  shell(const Adesk::UInt32 nbVertex,
                                 const AcGePoint3d* pVertexList,
                                 const Adesk::UInt32 faceListSize,
                                 const Adesk::Int32* pFaceList,
                                 const AcGiEdgeData* pEdgeData = NULL,
                                 const AcGiFaceData* pFaceData = NULL,
                                 const AcGiVertexData* pVertexData = NULL,
                                 const struct resbuf* pResBuf = NULL,
                                 const bool bAutoGenerateNormals = true
                                 ) const = 0;
      
    virtual Adesk::Boolean  text(const AcGePoint3d& position,
                                 const AcGeVector3d& normal,
                                 const AcGeVector3d& direction,
                                 const double height,
                                 const double width,
                                 const double oblique,
                                 const ACHAR* pMsg) const = 0;

    virtual Adesk::Boolean  text(const AcGePoint3d& position,
                                 const AcGeVector3d& normal,
                                 const AcGeVector3d& direction,
                                 const ACHAR* pMsg,
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

    virtual Adesk::Boolean  draw(AcGiDrawable*) const = 0;

    // If you push a clip boundary onto the stack you must pop it;
    //
    virtual Adesk::Boolean          pushClipBoundary(AcGiClipBoundary * pBoundary) = 0;
    virtual void                    popClipBoundary() = 0;
    virtual Adesk::Boolean   worldLine(const AcGePoint3d pnts[2]) {
                                        AcGePoint3d polyPnts[2];
                                        AcGeMatrix3d mat;
                                        getWorldToModelTransform(mat);
                                        polyPnts[0] = mat * pnts[0];
                                        polyPnts[1] = mat * pnts[1];
                                        return polyline(2, polyPnts);
                                    };
    // array of points
    virtual Adesk::Boolean  polypoint( const Adesk::UInt32 nbPoints,
                                       const AcGePoint3d* pVertexList,
                                       const AcGeVector3d* pNormal = NULL,
                                       const Adesk::Int32 *pSubEntMarkers = NULL ) const {
                                           AcGePoint3d pline[2];
                                           Adesk::Boolean retval = Adesk::kFalse;
                                           for (Adesk::UInt32 i = 0; i < nbPoints; i++) {
                                               pline[1] = pline[0] = pVertexList[i];
                                               retval = polyline(2, pline, pNormal ? &pNormal[i] : NULL, pSubEntMarkers ? pSubEntMarkers[i] : -1);
                                               if (retval)
                                                   return retval;
                                           }
                                           return retval;
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
    virtual void startAttributesSegment() {};
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

    virtual Adesk::Boolean  ownerDraw3d(
                AcGePoint3d&               minBounds,
                AcGePoint3d&               maxBounds,
                OwnerDraw3d*               pOwnerDraw
                ) const  { return Adesk::kFalse; };
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
    virtual void            setTrueColors(const AcCmEntityColor *colors);
    virtual void            setLayers(const AcDbObjectId *layers);
    virtual void            setLineTypes(const AcDbObjectId *linetypes);
    virtual void            setSelectionMarkers(const Adesk::Int32* pSelectionMarkers);
    virtual void            setVisibility(const Adesk::UInt8* pVisibility);

    virtual short*          colors() const;
    virtual AcCmEntityColor* trueColors() const;
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
    virtual void            setTrueColors(const AcCmEntityColor *colors);
    virtual void            setLayers(const AcDbObjectId *layers);
    virtual void            setSelectionMarkers(const Adesk::Int32* pSelectionMarkers);
    virtual void            setNormals(const AcGeVector3d* pNormals);
    virtual void            setVisibility(const Adesk::UInt8* vis);
    virtual void            setMaterials(const AcDbObjectId * materials);
    virtual void            setMappers(const AcGiMapper * mappers);

    virtual short*          colors() const;
    virtual AcCmEntityColor* trueColors() const;
    virtual AcDbObjectId*   layerIds() const;
    virtual Adesk::Int32*   selectionMarkers() const;
    virtual AcGeVector3d*   normals() const;
    virtual Adesk::UInt8*   visibility() const;
    virtual AcDbObjectId*   materials() const; // TODO Randy Kintzley 09/27/2005 how is this used? Should it be renamed to materialIds()?
    virtual AcGiMapper*     mappers() const; 

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
    virtual void setTrueColors(const AcCmEntityColor *colors);
    virtual AcCmEntityColor* trueColors() const;

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
        const ACHAR*  fontName, 
        const ACHAR*  bigFontName, 
        const double textSize, 
        const double xScale, 
        const double obliqueAngle, 
        const double trPercent,

        const Adesk::Boolean isBackward,
        const Adesk::Boolean isUpsideDown,
        const Adesk::Boolean isVertical, 

        const Adesk::Boolean isOverlined,
        const Adesk::Boolean isUnderlined,
        
        const ACHAR*          styleName = NULL);

    // Unicode: change from char to int, since in the implementation, the returned
    // result is actually bitmask indicating some status result.
    virtual int loadStyleRec() const;
    virtual void setTextSize(const double size);
    virtual void setXScale(const double xScale);
    virtual void setObliquingAngle(const double obliquingAngle);

    virtual void setTrackingPercent(const double trPercent);

    virtual void setBackward(const Adesk::Boolean isBackward);
    virtual void setUpsideDown(const Adesk::Boolean isUpsideDown);
    virtual void setVertical(const Adesk::Boolean isVertical);

    virtual void setUnderlined(const Adesk::Boolean isUnderlined);
    virtual void setOverlined(const Adesk::Boolean isOverlined);

    virtual void setFileName(const ACHAR * fontName);
    virtual void setBigFontFileName(const ACHAR * bigFontFileName);

    virtual double textSize() const;
    virtual double xScale() const;
    virtual double obliquingAngle() const;

    virtual double trackingPercent() const;

    virtual Adesk::Boolean isBackward() const;
    virtual Adesk::Boolean isUpsideDown() const;
    virtual Adesk::Boolean isVertical() const;

    virtual Adesk::Boolean isUnderlined() const;
    virtual Adesk::Boolean isOverlined() const;

    virtual const ACHAR * fileName() const;
    virtual const ACHAR * bigFontFileName() const;

    virtual AcGePoint2d extents(const ACHAR * pStr, 
                const Adesk::Boolean penups,
                const int len,
                const Adesk::Boolean raw,
                AcGiWorldDraw *ctxt = NULL) const;

    virtual const ACHAR * styleName() const;
    virtual Acad::ErrorStatus setStyleName(const ACHAR *);
    
    virtual Acad::ErrorStatus setFont(const ACHAR * pTypeface,
                                      Adesk::Boolean bold,
                                      Adesk::Boolean italic,
                                      int charset, int pitchAndFamily);
    // Unicode: change pTypeface to AcString?
    virtual Acad::ErrorStatus font(ACHAR *& pTypeface, Adesk::Boolean& bold, 
                Adesk::Boolean& italic, int& charset, int& pitchAndFamily) const;

    virtual Acad::ErrorStatus  extentsBox(  const ACHAR * pStr, 
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
