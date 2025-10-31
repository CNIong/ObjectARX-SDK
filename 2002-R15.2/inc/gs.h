// 
// (C) Copyright 1997-1999 by Autodesk, Inc. 
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

#ifndef __GS_H
#define __GS_H

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

// ****************************************************************************
// Helper classes
// ****************************************************************************

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
                        ASSERT ((m_min.x <= m_max.x && m_min.y <= m_max.y) ||
                                (m_min == AcGsDCPoint::Maximum && m_max == AcGsDCPoint::Minimum));
                        return m_min.x > m_max.x;
                    }

    bool            within (AcGsDCRect const & rightside) const {
                        ASSERT (!is_null());                        // (if *this is Null and rightside is not, does not work.
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
    unsigned char   m_red;
    unsigned char   m_green;
    unsigned char   m_blue;
    unsigned char   m_filler;
};

typedef void *      AcGsWindowingSystemID;       // i.e. -- HWND

// ****************************************************************************
// AcGsPath
// ****************************************************************************

class AcGsPath { };

// ****************************************************************************
// AcGsView
// ****************************************************************************

class AcGsView
{
public:

    enum RenderMode
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
    virtual void                setViewportClipRegion       (int                 contours, 
                                                             int const *         counts, 
                                                             AcGsDCPoint const * points)        = 0;
    virtual void                removeViewportClipRegion    (void)                              = 0;

    // Viewport Borders
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
    virtual void                setMode             (RenderMode mode)       = 0;
    virtual RenderMode          mode                (void) const            = 0;

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
    virtual void                flush               (void)                  = 0;

    // Visibility
    // 
    virtual void                hide                (void)                  = 0;
    virtual void                show                (void)                  = 0;
    virtual bool                isVisible           (void)                  = 0;

    // Viewport visibility of layers
    //
    virtual void                freezeLayer         (long layerID)          = 0;
    virtual void                thawLayer           (long layerID)          = 0;
    virtual void                clearFrozenLayers   (void)                  = 0;

    // Logical View Control
    //
    virtual void                invalidateCachedViewportGeometry (void)     = 0;

    // Selection (in device coords)
    //
    virtual AcGsPath *          selectInside          (const AcGsDCRect  &) = 0;
    virtual AcGsPath *          selectInsideOrCrossing(const AcGsDCRect  &) = 0;
    virtual AcGsPath *          selectInside          (const AcGsDCPoint &, 
                                                       int nPoints)         = 0;
    virtual AcGsPath *          selectInsideOrCrossing(const AcGsDCPoint &,         
                                                       int nPoints)         = 0;

    // Deallocate path
    //
    virtual void                release             (AcGsPath *)            = 0;

    // View-specific highlighting
    //
    virtual bool                highlight           (const AcGsPath *)      = 0;
    virtual bool                unhighlight         (const AcGsPath *)      = 0;

    // For client-friendly view manipulation
    //
    virtual void                dolly               (const AcGeVector3d & vector)   = 0;
    virtual void                dolly               (double x, double y, double z)  = 0;
    virtual void                roll                (double angle)                  = 0;
    virtual void                orbit               (double x, double y)            = 0;
    virtual void                zoom                (double factor)                 = 0;
    virtual void                pan                 (double x, double y)            = 0;

    virtual AcGsView *          clone               (bool bCloneViewParameters = true,
                                                     bool bCloneGeometry       = false)  = 0;

    // Viewing limits 
    //
    virtual bool                exceededBounds      (void)                          = 0;

    // Stereo
    virtual void                enableStereo        (bool bEnable)                  = 0;
    virtual bool                isStereoEnabled     (void) const                    = 0;
    virtual void                setStereoParameters (double     magnitude,
                                                     double     parallax)           = 0;
    virtual void                getStereoParameters (double &   magnitude, 
                                                     double &   parallax) const     = 0;
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
        kCount              // Count of RenderTypes
    };

    enum InvalidationHint
    {
        kInvalidateNone,
        kInvalidateIsolines,
        kInvalidateViewportCache,
        kInvalidateAll
    };

    virtual                    ~AcGsModel           (void) { }

    // Scene Graph Roots
    //
    virtual bool                addSceneGraphRoot   (AcGiDrawable * pRoot)      = 0;
    virtual bool                eraseSceneGraphRoot (AcGiDrawable * pRoot)      = 0;

    // Change notification
    //
    virtual void                onAdded             (AcGiDrawable * pAdded,        
                                                     AcGiDrawable * pParent)    = 0;
    virtual void                onAdded             (AcGiDrawable * pAdded,
                                                     long           parentID)   = 0;
                                                    
    virtual void                onModified          (AcGiDrawable * pModified,
                                                     AcGiDrawable * pParent)    = 0;
    virtual void                onModified          (AcGiDrawable * pModified, 
                                                     long           parentID)   = 0;
                                                    
    virtual void                onErased            (AcGiDrawable * pErased,
                                                     AcGiDrawable * pParent)    = 0;
    virtual void                onErased            (AcGiDrawable * pErased, 
                                                     long           parentID)   = 0;

    virtual void                onPaletteModified   (void) = 0;

    // Highlighting
    //
    virtual bool                highlight           (const AcGsPath *)          = 0;
    virtual bool                unhighlight         (const AcGsPath *)          = 0;
                                                    
    // Transformations                              
    //                                              
    virtual void                setTransform        (const AcGeMatrix3d &)      = 0;
    virtual AcGeMatrix3d        transform           (void) const                = 0;
                                                    
    virtual bool                getTransformAt      (const AcGsPath *, 
                                                     AcGeMatrix3d &)            = 0;
                                                    
    virtual void                setExtents          (const AcGePoint3d &,
                                                     const AcGePoint3d &)       = 0;
    // invalidation notification                    
    virtual void                invalidate          (InvalidationHint hint)     = 0;

    // AcGsView property overrides 
    //
    virtual void                setViewClippingOverride (bool bOverride)        = 0;
    virtual void                setMaterialsOverride    (bool bOverride)        = 0;
    virtual void                setRenderModeOverride   (AcGsView::RenderMode mode = 
                                                         AcGsView::kNone)       = 0;
};


// ****************************************************************************
// AcGsDevice
// ****************************************************************************

class AcGsDevice
{
public:

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
    
    virtual                    ~AcGsConfig          (void) { }
                                                    
    virtual void                driverName          (char * pszPath, int nStrLen) const = 0;
    virtual int                 driverVersion       (void) const            = 0;
    virtual int                 driverRevision      (void) const            = 0;
                                                    
    virtual void                driverPath          (char * pszPath, int nStrLen) const = 0;
    virtual void                setDriverPath       (const char * pszPath)  = 0;

    virtual void                setHandedness       (Handedness)            = 0;
    virtual Handedness          handedness          (void) const            = 0;

    virtual bool                configure           (const char * pszConfigInfo, bool bShowDialog) = 0;
};

// ****************************************************************************
// Access protocol for persistent drawables
// ****************************************************************************


typedef AcGiDrawable*    (* AcGsGetInterfaceFunc)            (long objectId,
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
};


// ****************************************************************************
// AcGsClassFactory
// ****************************************************************************

struct AcGsClientViewInfo 
{
    long viewportId;        // returned via AcGiViewport::viewportId()
    long acadWindowId;      // returned via AcGiViewport::acadWindowId()
    long viewportObjectId;  // returned via AcGiViewportDraw::viewportObjectId()
};

class AcGsClassFactory
{
public:

    virtual                    ~AcGsClassFactory(void) { }

    virtual AcGsModel *         createModel     (AcGsModel::RenderType,
                                                 long databaseId,
                                                 AcGsGetInterfaceFunc, 
                                                 AcGsReleaseInterfaceFunc)  = 0;
    virtual void                deleteModel     (AcGsModel * model)         = 0;

    virtual AcGsView *          createView      (const AcGsClientViewInfo * pInfo   = NULL,
                                                 bool bEnableLayerVisibilityPerView = false) = 0;
    virtual void                deleteView      (AcGsView * view)           = 0;

    virtual AcGsDevice *        createDevice    (AcGsWindowingSystemID id)  = 0;
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
#endif // __GS_H
