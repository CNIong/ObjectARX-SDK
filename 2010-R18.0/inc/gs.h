// 
// (C) Copyright 1997-2009 by Autodesk, Inc. 
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
// MODULE:      gs.h
// PURPOSE:     Graphics System Interface
//

#pragma once

#include "AcArray.h"
#include "AdAChar.h"
#include "gept3dar.h"
#include "dbid.h"

// ****************************************************************************
// Forward declarations
// ****************************************************************************

class AcGiDrawable;
class AcGeMatrix3d;
class AcGePoint3d;
class AcGeVector3d;
class AcGePoint2d;

class AcGsView;
class AcGsModel;
class AcGsDevice;
class AcGsConfig;
class AcGsReactor;
class AcGsClassFactory;
class AcGiVisualStyle;
class AcGiContextualColors;

namespace Atil
{
    class Image;
};

// ****************************************************************************
// Helper classes
// ****************************************************************************

namespace GS 
{
    // Error Codes
    enum ErrorStatus {
        kSuccess,
        kOutOfRange,
        kInvalidInput
    };

    enum DeviceType {
        kScreenDevice =         0,
        kOffScreenDevice =      1,
        kSelectionDevice =      2
    };

    enum HighlightStyle {
        kHighlightDashed =               0,
        kHighlightThicken =              1,
        kHighlightDashedAndThicken =     2,
        kHighlightCustom =               3,
        kHighlightDim =                  4,
        kHighlightThickDim =             5
    };


};

// copied (with modification) from limits.h to avoid extra #includes
#define SCALAR_MIN     (-2147483647 - 1) // minimum (signed) int value
#define SCALAR_MAX       2147483647      // maximum (signed) int value
#pragma pack (push, 8)

class AcGsDCPoint 
{
public:
    enum            MaxFlag { Maximum };
    enum            MinFlag { Minimum };

                    AcGsDCPoint (void) { }
                    AcGsDCPoint (long xin, long yin) : x (xin), y (yin) { }

                    AcGsDCPoint (MaxFlag) { x = SCALAR_MAX; y = SCALAR_MAX; }
                    AcGsDCPoint (MinFlag) { x = SCALAR_MIN; y = SCALAR_MIN; }

    void            operator=   (MaxFlag) { x = SCALAR_MAX; y = SCALAR_MAX; }
    void            operator=   (MinFlag) { x = SCALAR_MIN; y = SCALAR_MIN; }

    void            operator=   (AcGsDCPoint const & r)              { x =  r.x;   y =  r.y; }
    bool            operator==  (AcGsDCPoint const & r) const { return x == r.x && y == r.y; }
    bool            operator!=  (AcGsDCPoint const & r) const { return x != r.x || y != r.y; }

    long            x;
    long            y;
};

class AcGsDCRect 
{
public:
    enum            NullFlag { Null    };

                    AcGsDCRect (void) { }
                    AcGsDCRect (AcGsDCPoint const & min, AcGsDCPoint const & max)
                        : m_min (min)
                        , m_max (max) { }
                    AcGsDCRect (long l, long r, long b, long t)
                        : m_min (l,b)
                        , m_max (r,t) { }
                    AcGsDCRect (NullFlag) { set_null(); }

    AcGsDCRect &    operator= (AcGsDCRect const & other) {
                        m_min = other.m_min;
                        m_max = other.m_max;
                        return *this;
                    }
    void            operator|= (AcGsDCRect const & rightside) {
                        if (m_min.x > rightside.m_min.x)            
                            m_min.x = rightside.m_min.x;            
                        if (m_max.x < rightside.m_max.x)            
                            m_max.x = rightside.m_max.x;

                        if (m_min.y > rightside.m_min.y)
                            m_min.y = rightside.m_min.y;
                        if (m_max.y < rightside.m_max.y)
                            m_max.y = rightside.m_max.y;
                    }
    void            operator&= (AcGsDCRect const & rightside) {
                        if (m_min.x < rightside.m_min.x)
                            m_min.x = rightside.m_min.x;            
                        if (m_max.x > rightside.m_max.x)            
                            m_max.x = rightside.m_max.x;

                        if (m_min.y < rightside.m_min.y)
                            m_min.y = rightside.m_min.y;
                        if (m_max.y > rightside.m_max.y)
                            m_max.y = rightside.m_max.y;

                        if (m_min.x > m_max.x || m_min.y > m_max.y)
                            *this = Null;
                    }
    bool            operator== (AcGsDCRect const & rightside) const {
                        return m_min == rightside.m_min &&
                               m_max == rightside.m_max;    
                    }
    bool            operator!= (AcGsDCRect const & rightside) const {
                        return !(*this == rightside);
                    }

    void            set_null (void) {                   
                        m_min = AcGsDCPoint::Maximum;   
                        m_max = AcGsDCPoint::Minimum;   
                    }                                   

    bool            is_null (void) const {// should be either valid or properly null
#ifdef ASSERT
                        ASSERT ((m_min.x <= m_max.x && m_min.y <= m_max.y) ||
                                (m_min == AcGsDCPoint::Maximum && m_max == AcGsDCPoint::Minimum));
#endif
                        return m_min.x > m_max.x;
                    }

    bool            within (AcGsDCRect const & rightside) const {
#ifdef ASSERT
                        ASSERT (!is_null());                        // (if *this is Null and rightside is not, does not work.
#endif
                        return m_min.x >= rightside.m_min.x &&      //  if *this is non-Null and right is Null, works.
                               m_min.y >= rightside.m_min.y &&      //  if both are Null, does not work.)
                               m_max.x <= rightside.m_max.x &&
                               m_max.y <= rightside.m_max.y;
                    }

    AcGsDCPoint     m_min;
    AcGsDCPoint     m_max;
};

struct AcGsColor
{
    unsigned char   m_red;    // unicode safe
    unsigned char   m_green;
    unsigned char   m_blue;
    unsigned char   m_filler;
};

typedef void *      AcGsWindowingSystemID;       // i.e. -- HWND


// ****************************************************************************
// AcGsNode
// ****************************************************************************

class AcGsNode
{
public:
    virtual AcGiDrawable *  drawable        (void) const = 0;
    virtual void            setDrawableNull (void)       = 0;
};


// ****************************************************************************
// AcGsView
// ****************************************************************************

class AcGsView
{
public:

    // Use AcDbVisualStyle or AcGiVisualStyle
    ADESK_DEPRECATED enum RenderMode
    {
        k2DOptimized,               // Standard AutoCAD 2D Display
        kBoundingBox,               // Bounding Box (when simpler than the geometry)
        kWireframe,                 // Same display as k2Doptimized (but using the 3D Pipeline)
        kHiddenLine,                // Wireframe display with hidden lines removed
        kFlatShaded,                // Faceted - constant color per face
        kGouraudShaded,             // Smooth shaded - colors interpolated between vertices
        kFlatShadedWithWireframe,   // Faceted with wireframe overlayed
        kGouraudShadedWithWireframe,// Smooth shaded with wireframe overlayed
        kCount,
        kNone = kCount
    };

    enum Projection
    {
        kParallel,
        kPerspective
    };

    enum SelectionMode
    {
        kWindow,
        kCrossing,
        kFence,
        kWPoly,
        kCPoly,
    };

    enum DefaultLightingType
    {
        kOneLight,
        kTwoLights,
        kBackLight
    };

    virtual                    ~AcGsView            (void) { }

    // Viewport size & position in normalized device coords and screen coords
    //
    virtual void                setViewport         (const AcGePoint2d & lowerLeft,
                                                     const AcGePoint2d & upperRight)            = 0;
    virtual void                setViewport         (const AcGsDCRect  & screen_rect)           = 0;
    virtual void                getViewport         (      AcGePoint2d & lowerLeft,
                                                           AcGePoint2d & upperRight)  const     = 0;
    virtual void                getViewport         (      AcGsDCRect  & screen_rect) const     = 0;


    // Non-Rectangular Viewports
    //
    virtual void                setViewportClipRegion       (int                 contours, 
                                                             int const *         counts, 
                                                             AcGsDCPoint const * points)        = 0;
    virtual void                removeViewportClipRegion    (void)                              = 0;

    // Viewport Borders
    //
    virtual void                setViewportBorderProperties (AcGsColor const &   color,
                                                             int                 weight)        = 0;
    virtual void                getViewportBorderProperties (AcGsColor &         color,
                                                             int &               weight) const  = 0;

    virtual void                setViewportBorderVisibility (bool                bVisible)      = 0;
    virtual bool                isViewportBorderVisible     (void) const                        = 0;

    // View transformation
    //
    virtual void                setView             (const AcGePoint3d &  position,
                                                     const AcGePoint3d &  target,
                                                     const AcGeVector3d&  upVector,
                                                     double               fieldWidth,
                                                     double               fieldHeight,
                                                     Projection           projection = kParallel) = 0;

    virtual AcGePoint3d         position            (void) const            = 0;
    virtual AcGePoint3d         target              (void) const            = 0;
    virtual AcGeVector3d        upVector            (void) const            = 0;
    virtual bool                isPerspective       (void) const            = 0;
    virtual double              fieldWidth          (void) const            = 0;
    virtual double              fieldHeight         (void) const            = 0;

    // Clip Planes
    //
    virtual void                setEnableFrontClip  (bool enable)           = 0;
    virtual bool                isFrontClipped      (void) const            = 0;
    virtual void                setFrontClip        (double distance)       = 0;
    virtual double              frontClip           (void) const            = 0;

    virtual void                setEnableBackClip   (bool enable)           = 0;
    virtual bool                isBackClipped       (void) const            = 0;
    virtual void                setBackClip         (double distance)       = 0;
    virtual double              backClip            (void) const            = 0;
    
    // Matrix
    //
    virtual AcGeMatrix3d        viewingMatrix       (void) const            = 0;
    virtual AcGeMatrix3d        projectionMatrix    (void) const            = 0;
    virtual AcGeMatrix3d        screenMatrix        (void) const            = 0;
    virtual AcGeMatrix3d        worldToDeviceMatrix (void) const            = 0;
    virtual AcGeMatrix3d        objectToDeviceMatrix(void) const            = 0;

    // Render mode
    //
    // Use AcGiSubEntityTraits::setVisualStyle or AcGsView::setVisualStyle
    ADESK_DEPRECATED virtual void       setMode     (RenderMode mode)       = 0;
    // Use AcGiSubEntityTraits::visualStyle or AcGsView::visualStyle
    ADESK_DEPRECATED virtual RenderMode mode        (void) const            = 0;

    // Drawables
    //
    virtual bool                add                 (AcGiDrawable * drawable, 
                                                     AcGsModel    * model)    = 0;
    virtual bool                erase               (AcGiDrawable * drawable) = 0;
    virtual void                eraseAll            (void)                    = 0;

    // Validation
    //
    virtual void                invalidate          (void)                  = 0;
    virtual void                invalidate          (const AcGsDCRect &rect)= 0;
    virtual bool                isValid             (void) const            = 0;

    // Updates
    //
    virtual void                update              (void)                  = 0;
    virtual void                beginInteractivity  (double fFrameRateInHz) = 0;
    virtual void                endInteractivity    (void)                  = 0;
    virtual bool                isInteractive       (void) const            = 0;
    virtual void                flush               (void)                  = 0;

    // Degradation
    //
    virtual void                setMaximumUpgrade   (int step)              = 0;
    virtual int                 maximumUpgrade      (void)                  = 0;
    virtual void                setMinimumDegrade   (int step)              = 0;
    virtual int                 minimumDegrade      (void)                  = 0;

    // Visibility
    // 
    virtual void                hide                (void)                  = 0;
    virtual void                show                (void)                  = 0;
    virtual bool                isVisible           (void)                  = 0;

    // Viewport visibility of layers
    //
    virtual void                freezeLayer         (LONG_PTR layerID)      = 0;
    virtual void                thawLayer           (LONG_PTR layerID)      = 0;
    virtual void                clearFrozenLayers   (void)                  = 0;

    // Logical View Control
    //
    virtual void                invalidateCachedViewportGeometry (void)     = 0;

    // For client-friendly view manipulation
    //
    virtual void                dolly               (const AcGeVector3d & vector)   = 0;
    virtual void                dolly               (double x, double y, double z)  = 0;
    virtual void                roll                (double angle)                  = 0;
    virtual void                orbit               (double x, double y)            = 0;
    virtual void                zoom                (double factor)                 = 0;
    virtual void                zoomExtents         (const AcGePoint3d& minPoint, 
                                                     const AcGePoint3d& maxPoint)   = 0;
    virtual void                zoomWindow          (const AcGePoint2d& lowerLeft, 
                                                     const AcGePoint2d& upperRight) = 0;
    virtual void                pan                 (double x, double y)            = 0;

    virtual bool                pointInView         (const AcGePoint3d& pnt)        = 0;
    virtual bool                extentsInView       (const AcGePoint3d& minPoint, 
                                                     const AcGePoint3d& maxPoint)   = 0;

    virtual AcGsView *          clone               (bool bCloneViewParameters = true,
                                                     bool bCloneGeometry       = false)  = 0;

    // Viewing limits 
    //
    virtual bool                exceededBounds      (void)                          = 0;

    // Stereo
    //
    virtual void                enableStereo        (bool bEnable)                  = 0;
    virtual bool                isStereoEnabled     (void) const                    = 0;
    virtual void                setStereoParameters (double     magnitude,
                                                     double     parallax)           = 0;
    virtual void                getStereoParameters (double &   magnitude, 
                                                     double &   parallax) const     = 0;

    // Off-screen Rendering
    //
    virtual void                getSnapShot         (Atil::Image       * pOutput,
                                                     AcGsDCPoint const & offset)    = 0;

    virtual bool                RenderToImage       (Atil::Image* pOutput,
                                                     AcGiDrawable* pSettings,
                                                     void* pProgressMonitor,
                                                     const AcGsDCRect & rectScreen,
                                                     bool bReuseScene = false)      = 0;

    // Device mapping
    virtual AcGsDevice *        getDevice(void) const = 0;

    // Visual Style
    virtual void                setVisualStyle      (const AcDbObjectId visualStyleId)      = 0;
    virtual AcDbObjectId        visualStyle         (void) const                            = 0;
    virtual void                setVisualStyle      (const AcGiVisualStyle &visualStyle)    = 0;
    virtual bool                visualStyle         (AcGiVisualStyle &visualStyle) const    = 0;

    // Background
    virtual void                setBackground       (const AcDbObjectId backgroundId)       = 0;
    virtual AcDbObjectId        background          (void) const                            = 0;

    // Default lighting
    virtual void                enableDefaultLighting (bool bEnable, 
                                                       DefaultLightingType type = kTwoLights) = 0;

    virtual void                getNumPixelsInUnitSquare(const AcGePoint3d& givenWorldpt,          // Pixel information.
                                                               AcGePoint2d& pixelArea,
                                                               bool includePerspective = true) const = 0;      
                                                                                    
};


// ****************************************************************************
// AcGsModel
// ****************************************************************************

class AcGsModel
{
public:

    enum RenderType
    {  
        kMain,              // Use main Z-buffer
        kSprite,            // Use alternate Z-buffer, for sprites
        kDirect,            // Render into frame buffer without the z-test
        kHighlight,         // Render directly onto the device (skipping the frame buffer and the z-test)
        kHighlightSelection,// Render directly onto the device in selection highlight style (internal only)
        kDirectTopmost,     // Render above all other render types except contrast, and render without the z-test
        kContrast,          // Render directly onto the device in contrast style, for transients
        kCount              // Count of RenderTypes
    };

    enum InvalidationHint
    {
        kInvalidateNone,
        kInvalidateIsolines,
        kInvalidateViewportCache,
        kInvalidateAll,
        kInvalidateAllStatic,
        kInvalidateFacets,
        kInvalidateFills,
        kInvalidateLinetypes,
        kInvalidateMaterials,
        kInvalidateLayers,
        kInvalidateXrefs,
    };

    virtual                    ~AcGsModel           (void) { }

    // Scene graph roots
    //
    virtual bool                addSceneGraphRoot   (AcGiDrawable * pRoot)      = 0;
    virtual bool                eraseSceneGraphRoot (AcGiDrawable * pRoot)      = 0;

    // Change notification
    //
    virtual void                onAdded             (AcGiDrawable * pAdded,        
                                                     AcGiDrawable * pParent)    = 0;
    virtual void                onAdded             (AcGiDrawable * pAdded,
                                                     LONG_PTR       parentID)   = 0;
                                                    
    virtual void                onModified          (AcGiDrawable * pModified,
                                                     AcGiDrawable * pParent)    = 0;
    virtual void                onModified          (AcGiDrawable * pModified, 
                                                     LONG_PTR       parentID)   = 0;
                                                    
    virtual void                onErased            (AcGiDrawable * pErased,
                                                     AcGiDrawable * pParent)    = 0;
    virtual void                onErased            (AcGiDrawable * pErased, 
                                                     LONG_PTR       parentID)   = 0;

    virtual void                onPaletteModified   (void) = 0;

    // Transformations                              
    //                                              
    virtual void                setTransform        (const AcGeMatrix3d &)      = 0;
    virtual AcGeMatrix3d        transform           (void) const                = 0;
    virtual void                setExtents          (const AcGePoint3d &,
                                                     const AcGePoint3d &)       = 0;

    // Invalidation notification                    
    //
    virtual void                invalidate          (InvalidationHint hint)     = 0;

    // View overrides 
    //
    virtual void setViewClippingOverride (bool bOverride)      = 0;

    // Use AcGsModel::setVisualStyle instead
    ADESK_DEPRECATED virtual void setRenderModeOverride (AcGsView::RenderMode mode =
                                                         AcGsView::kNone)       = 0;

    // Visual style
    //
    virtual void                setVisualStyle      (const AcDbObjectId visualStyleId)      = 0;
    virtual AcDbObjectId        visualStyle         (void) const                            = 0;
    virtual void                setVisualStyle      (const AcGiVisualStyle &visualStyle)    = 0;
    virtual bool                visualStyle         (AcGiVisualStyle &visualStyle) const    = 0;

    // Background
    virtual void                setBackground       (const AcDbObjectId backgroundId)       = 0;
    virtual AcDbObjectId        background          (void) const                            = 0;

    // Linetypes
    //
    virtual void                enableLinetypes     (bool bEnable)              = 0;
    virtual bool                linetypesEnabled    (void) const                = 0;

    // Sectioning
    //
    virtual void                setEnableSectioning      (bool enable)          = 0;
    virtual bool                isSectioningEnabled      (void) const           = 0;
    virtual bool                setSectioning            (const AcGePoint3dArray & pts, 
                                                          const AcGeVector3d &     upVector) = 0;
    virtual bool                setSectioning            (const AcGePoint3dArray & pts, 
                                                          const AcGeVector3d &     upVector, 
                                                          double                   top, 
                                                          double                   bottom)   = 0;
    virtual void                setSectioningVisualStyle (const AcDbObjectId visualStyleId)  = 0;

    // Render Type
    //
    virtual RenderType          renderType               (void)                     = 0;

    // Shadowing
    //
    virtual double              shadowPlaneLocation      (void) const               = 0;
    virtual void                setShadowPlaneLocation   (double planeLocationZ)    = 0;

    // Selection
    //
    virtual void                setSelectable            (bool bEnable)             = 0;
    virtual bool                selectable               (void) const               = 0;
};


// ****************************************************************************
// AcGsDevice
// ****************************************************************************

class AcGsDevice
{
public:

    enum RendererType
    {
        kDefault,
        kSoftware,
        kSoftwareNewViewsOnly,
        kFullRender,
        kSelectionRender
    };

    virtual                    ~AcGsDevice          (void) { }
                                                    
    // Validation                                   
    //                                              
    virtual void                invalidate          (void)                  = 0;
    virtual void                invalidate          (const AcGsDCRect &rect)= 0;
    virtual bool                isValid             (void) const            = 0;
                                                                            
    // Updates                                                              
    //
    // Pass in a rectangle to know which region on the device was updated by the GS
    virtual void                update              (AcGsDCRect* pUpdatedRect = NULL) = 0;

    // Change notification
    //
    virtual void                onSize              (int width, int height) = 0;
    virtual void                onRealizeForegroundPalette (void)           = 0;
    virtual void                onRealizeBackgroundPalette (void)           = 0;
    virtual void                onDisplayChange     (int nBitsPerPixel,     
                                                     int nXRes,             
                                                     int nYRes)             = 0;
    // View connections                                                     
    //                                                                      
    virtual bool                add                 (AcGsView * view)       = 0;
    virtual bool                erase               (AcGsView * view)       = 0;
    virtual void                eraseAll            (void)                  = 0;
                                                                            
    virtual bool                setBackgroundColor  (AcGsColor color)       = 0;
    virtual AcGsColor           getBackgroundColor  (void)                  = 0;
                                                    
    virtual void                setLogicalPalette   (const AcGsColor * palette, 
                                                     int nCount)            = 0;
    virtual void                setPhysicalPalette  (const AcGsColor * palette, 
                                                     int nCount)            = 0;

    // Off-screen Rendering
    virtual void                getSnapShot         (Atil::Image       * pOutput,
                                                     AcGsDCPoint const & offset) = 0;
    // Device Renderer type
    virtual void                setDeviceRenderer   (RendererType type)     = 0;
    virtual RendererType        getDeviceRenderer   (void)                  = 0;
};


// ****************************************************************************
// AcGsConfig
// ****************************************************************************

class AcGsConfig
{
public:

    enum Handedness
    {
        kLeft,
        kRight
    };    
    
    enum Quality
    {
        kLowQuality,
        kMediumQuality,
        kHighQuality
    };

    enum DegradationChannel
    {
        kViewportDraw,        // Viewport draw objects On to Off
        kLineAntialias,       // Line antialias On to Off
        kLighting,            // User lighting to Default lighting
        kTransparencyQuality, // Transparency quality High to Medium then Medium to Low
        kShadowsFull,         // Full Shadows to Ground Shadows
        kTransparency,        // Transparency On to Off
        kDiscardBackfaces,    // Discard Backfaces Off to On
        kShadowsGround,       // Ground Shadows to Shadows Off
        kEdgeStyles,          // Any Edge Style On to All Edge Styles Off
        kFacetEdges,          // Facet Edges to Isolines
        kFastSilhouette,      // Fast silhouettes On to Off
        kTextures,            // Textures On to Off
        kMaterials,           // Materials On to Off
        kLightingQuality,     // Lighting Quality Per-Vertex to Per-Face
        kBackgrounds,         // Backgrounds On to Off
        kIntersectEdges,      // Face Intersect Edges On to Off
        kFaceted,             // Faceted to Wireframe
        kWireframe,           // Wireframe to Bounding box
        kDegradationChannels
    };

    enum HardwareFeature { 
        kHwAcceleration,
        kHwGeometryAccel,
        kHwAntiAliasing,
        kHwGooch,
        kHwShadows,
        kHwTextureCompression,
        kHwPhong,
        kHw2DHwAcceleration,
        kHwDisable2DPreClip,
        kHwFeatures  
    };

    virtual                    ~AcGsConfig                      (void) { }
                                            
    // dialog, read & write registry
    virtual bool                configure                       (const ACHAR * pszConfigInfo, 
                                                                 bool bShowDialog)              = 0;
    virtual bool                saveSettings                    (void)                          = 0;

    // hardware & software drivers
    virtual void                driverName                      (ACHAR * pszPath, 
                                                                 int nStrLen) const             = 0;
    virtual int                 driverVersion                   (void) const                    = 0;
    virtual int                 driverRevision                  (void) const                    = 0;
    virtual void                driverPath                      (ACHAR *        pszPath, 
                                                                 int            nStrLen) const  = 0;
    virtual void                setDriverPath                   (const ACHAR *  pszPath)        = 0;

    virtual void                currentDisplayDriver            (ACHAR *        pszPath,
                                                                 int            nPathStrLen,
                                                                 ACHAR *        pszDriver,
                                                                 int            nDriverStrLen,
                                                                 bool &         bHardwareAccelerated)  = 0;

    virtual void                hardwareAcceleratedDriver       (ACHAR *        pszPath,
                                                                 int            nPathStrLen,
                                                                 ACHAR *        pszDriver,
                                                                 int            nDriverStrLen)  = 0;
    virtual void                setHardwareAcceleratedDriver    (const ACHAR *  pszPath,
                                                                 const ACHAR *  pszDriver)      = 0;

    virtual void                defaultHardwareAcceleratedDriver(ACHAR *        pszPath,
                                                                 int            nPathStrLen,
                                                                 ACHAR *        pszDriver,
                                                                 int            nDriverStrLen)  = 0;
    virtual void                hardwareAcceleratedDrivers      (ACHAR *        pszPath,
                                                                 int            nPathStrLen,
                                                                 ACHAR **       pszDrivers,
                                                                 int            nDrivers)       = 0;
    virtual int                 numHardwareAcceleratedDrivers   (void)                          = 0;

    // level of detail & dynamic tessellation
    virtual void                setDynamicTessellation          (bool bDynamicTessellation)     = 0;
    virtual bool                dynamicTessellation             (void)                          = 0;

    virtual GS::ErrorStatus     setMaxLODs                      (int nLevels)                   = 0;
    virtual int                 maxLODs                         (void)                          = 0;

    virtual GS::ErrorStatus     setSurfaceTessellationTol       (int surfaceTessellationTol)    = 0;
    virtual int                 surfaceTessellationTol          (void)                          = 0;

    virtual GS::ErrorStatus     setCurveTessellationTol         (int curveTessellationTol)      = 0;
    virtual int                 curveTessellationTol            (void)                          = 0;

    // adaptive degradation
    virtual int                 frameRate                       (void)                          = 0;
    virtual GS::ErrorStatus     setFrameRate                    (int nFramesPerSecond)          = 0;

    virtual void                setAdaptiveDegradation          (bool bAdaptiveDegradation)     = 0;
    virtual bool                adaptiveDegradation             (void)                          = 0;

    virtual int                 degradationChainPosition        (DegradationChannel channel)    = 0;
    virtual DegradationChannel  degradationChannelAt            (int position)                  = 0;
    virtual void                shiftDegradationChainPosition   (DegradationChannel channel,
                                                                 bool bShiftDown)               = 0;
    virtual bool                canDegradeChannel               (DegradationChannel channel)    = 0;
    virtual void                setCanDegradeChannel            (DegradationChannel channel,
                                                                 bool bDegrade)                 = 0;

    // performance
    virtual void                setUseDisplayLists              (bool bUseDisplayLists)         = 0;  // internal use
    virtual bool                useDisplayLists                 (void)                          = 0;

    virtual void                setRedrawOnWindowExpose         (bool bRedrawWindowExpose)      = 0;  // internal use
    virtual bool                redrawOnWindowExpose            (void)                          = 0;

    // display options
    virtual Handedness          handedness                      (void) const                    = 0;
    virtual void                setHandedness                   (Handedness)                    = 0;

    virtual bool                discardBackFaces                (void)                          = 0;
    virtual void                setDiscardBackFaces             (bool bDiscardBackFaces)        = 0;

    virtual Quality             transparency                    (void)                          = 0;
    virtual void                setTransparency                 (Quality quality)               = 0;

    // hardware features
    virtual bool                isFeatureEnabled                (HardwareFeature feature)       = 0;
    virtual void                setFeatureEnabled               (HardwareFeature feature,
                                                                 bool bEnable = true)           = 0;
    virtual bool                isFeatureAvailable              (HardwareFeature feature)       = 0;
    virtual bool                isFeatureRecommended            (HardwareFeature feature)       = 0;
};

class AcGsConfig2 : public AcGsConfig
{
public:
    virtual bool                generateVertexNormals           (void) const                    = 0;
    virtual void                setGenerateVertexNormals        (bool bEnable)                  = 0;
};

// ****************************************************************************
// Access protocol for persistent drawables
// ****************************************************************************

typedef AcGiDrawable*    (* AcGsGetInterfaceFunc)            (LONG_PTR objectId,
                                                              bool bNeedsValidation);   // does id need validation?
typedef void             (* AcGsReleaseInterfaceFunc)        (AcGiDrawable*);


// ****************************************************************************
// AcGsReactor
// ****************************************************************************

class AcGsReactor
{
public:
                                AcGsReactor                 (void)  { }
    virtual                    ~AcGsReactor                 (void)  { } 
    virtual void                viewWasCreated              (AcGsView * pView)  { }
    virtual void                viewToBeDestroyed           (AcGsView * pView)  { }
    virtual void                gsToBeUnloaded              (AcGsClassFactory * pClassFactory) { }
    virtual void                configWasModified           (void) { }
};


// ****************************************************************************
// AcGsDrawablePath
// ****************************************************************************

struct AcGsDrawableLink 
{
    LONG_PTR id;
    AcGiDrawable *pDrawable;
    AcGsNode *pNode;
};

typedef AcArray<AcGsDrawableLink> AcGsDrawablePath;


// ****************************************************************************
// AcGsClassFactory
// ****************************************************************************

struct AcGsClientViewInfo
{
    AcGsClientViewInfo()
        : viewportId(0)
        , acadWindowId(0)
        , viewportObjectId(0)
        , contextColors(NULL) { }

    LONG_PTR viewportId;        // returned via AcGiViewport::viewportId()
    LONG_PTR acadWindowId;      // returned via AcGiViewport::acadWindowId()
    LONG_PTR viewportObjectId;  // returned via AcGiViewportDraw::viewportObjectId()
    AcGiContextualColors* contextColors; // returned via AcGiViewport::contextualColors()
};

class AcGsClassFactory
{
public:

    virtual                    ~AcGsClassFactory(void) { }

    virtual AcGsModel *         createModel     (AcGsModel::RenderType,
                                                 LONG_PTR databaseId,
                                                 AcGsGetInterfaceFunc, 
                                                 AcGsReleaseInterfaceFunc)  = 0;
    virtual void                deleteModel     (AcGsModel * model)         = 0;

    virtual AcGsView *          createView      (const AcGsClientViewInfo * pInfo   = NULL,
                                                 bool bEnableLayerVisibilityPerView = false) = 0;
    virtual void                deleteView      (AcGsView * view)           = 0;

    virtual AcGsDevice *        createDevice    (AcGsWindowingSystemID id,
                                                 GS::DeviceType deviceType = GS::kScreenDevice)  = 0;
    virtual AcGsDevice *        createOffScreenDevice(void)                 = 0;
    virtual void                deleteDevice    (AcGsDevice * device)       = 0;

    virtual AcGsConfig *        getConfig       (void)                      = 0;
    virtual void                releaseConfig   (AcGsConfig * config)       = 0;

    virtual void                addReactor      (AcGsReactor * pReactor)    = 0;
    virtual void                removeReactor   (AcGsReactor * pReactor)    = 0;
};


// ****************************************************************************
// Driver (DLL) entry points
// ****************************************************************************

typedef AcGsClassFactory *    (* AcGsCreateClassFactoryFunc)(void);
typedef void                  (* AcGsDeleteClassFactoryFunc)(AcGsClassFactory *);

#define ACGS_CREATE_CLASS_FACTORY "CreateClassFactory"
#define ACGS_DELETE_CLASS_FACTORY "DeleteClassFactory"

#pragma pack (pop)
