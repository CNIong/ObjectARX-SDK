//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license
//  agreement provided at the time of installation or download, or which
//  otherwise accompanies this software in either electronic or hard copy form.
//
//////////////////////////////////////////////////////////////////////////////

//
//  DESCRIPTION:  Header for Rx application definitions and C++
//                access to AutoCAD Graphics System.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _ACGS_H
#define _ACGS_H

#include "adesk.h"
#include "stdlib.h"
#include "AdAChar.h"
#include "acgitransient.h"
#include "AcCoreDefs.h"
#include "acgidefs.h"

#pragma pack (push, 8)

Adesk::Boolean acgsGetDisplayInfo           (int & drawingWidth,
                                             int & drawingHeight,
                                             int & aspectWidth,
                                             int & aspectHeight);

Adesk::Boolean acgsGetViewportInfo          (int   viewportNumber,
                                             int & left,
                                             int & bottom,
                                             int & right,
                                             int & top);

class AcGiDrawable;

// This class is returned to the user by acgsGetScreenShot, below.
class AcGsScreenShot {      // pure virtual, abstract
    public:
    virtual Adesk::Boolean getSize          (int & width,
                                             int & height,
                                             int & depth) const = 0;

    virtual Adesk::Boolean getColorMap      (int             index,
                                             Adesk::UInt8 & red,
                                             Adesk::UInt8 & green,
                                             Adesk::UInt8 & blue) const = 0;

    virtual void const * getScanline        (int offsetFromLeft,
                                             int offsetFromTop) const = 0;

#ifdef new
#define DISABLING_LEAK_CHECK
#undef new
#endif
    void * operator new (size_t size); // static

    // Be sure to delete your screen shot when you are through with it.
    void operator delete (void * p);   // static

#ifndef PRODUCTION
        void * operator new (size_t size, const char *, int) { return operator new(size); }
#if _MSC_VER >= 1200
        // vc6 requires matching delete for each new
        void operator delete (void * p, const char *, int) { delete p; }
#endif // vc6
#endif // PRODUCTION

#ifdef DISABLING_LEAK_CHECK
#define new DEBUG_NEW
#undef DISABLING_LEAK_CHECK
#endif

    AcGsScreenShot();
    virtual ~AcGsScreenShot () = 0;
};

// Compatibility definition
//
#define ScreenShot AcGsScreenShot

AcGsScreenShot * acgsGetScreenShot          (int          viewportNumber);

void acgsSetViewportRenderFlag              (int          viewportNumber);

Adesk::Boolean acgsDisplayImage             (int          viewportNumber,
                                             Adesk::Int32 originLeft,
                                             Adesk::Int32 originTop,
                                             int          imageWidth,
                                             int          imageHeight,
                                             void const * imageData,
                                             int          hasTransparency);

Adesk::Boolean acgsRemoveAnonymousGraphics  (int viewportNumber);


typedef void (*acgsCustomUpdateMethod)      (void * pParm, int left, int right, int bottom, int top);
Adesk::Boolean acgsSetCustomUpdateMethod    (acgsCustomUpdateMethod custom_update_method, void * pParm);

ACCORE_PORT void acgsRedrawShortTermGraphics (int minx, int miny, int maxx, int maxy);


struct AcGs
{
    enum LinePattern      { eSolid                         = 0,
                            eDashed                        = 1,
                            eDotted                        = 2,
                            eDashDot                       = 3,
                            eShortDash                     = 4,
                            eMediumDash                    = 5,
                            eLongDash                      = 6,
                            eDoubleShortDash               = 7,
                            eDoubleMediumDash              = 8,
                            eDoubleLongDash                = 9,
                            eMediumLongDash                = 10,
                            eMediumDashShortDashShortDash  = 11,
                            eLongDashShortDash             = 12,
                            eLongDashDotDot                = 13,
                            eLongDashDot                   = 14,
                            eMediumDashDotShortDashDot     = 15,
                            eSparseDot                     = 16,
                            eDefaultLinePattern            = eDotted };
};

ACCORE_PORT void                acgsSetHighlightColor       (Adesk::UInt16 colorIndex);
ACCORE_PORT Adesk::UInt16       acgsGetHighlightColor       (void);
ACCORE_PORT void                acgsSetHighlightLinePattern (AcGs::LinePattern pattern);
ACCORE_PORT AcGs::LinePattern   acgsGetHighlightLinePattern (void);
ACCORE_PORT void                acgsSetHighlightLineWeight  (Adesk::UInt16 weight);
ACCORE_PORT Adesk::UInt16       acgsGetHighlightLineWeight  (void);
ACCORE_PORT void                acgsSetHighlightStyle       (AcGiHighlightStyle style);
ACCORE_PORT AcGiHighlightStyle  acgsGetHighlightStyle       (void);

class AcGsView;
class AcGsModel;
class AcGsManager;

Adesk::Boolean  acgsSetViewParameters         (int viewportNumber, const AcGsView * pView,
                                               bool bRegenRequired, bool bRescaleRequired,
                                               bool bSyncRequired = false);
Adesk::Boolean  acgsGetViewParameters         (int viewportNumber, AcGsView * pView);
Adesk::Boolean  acgsSetLensLength             (int viewportNumber, const double & lensLength);
Adesk::Boolean  acgsGetLensLength             (int viewportNumber, double & lensLength);
void            acgsWriteViewToUndoController (int viewportNumber);
Adesk::Boolean  acgsSetView2D                 (int viewportNumber);

ACCORE_PORT AcGsView *acgsGetCurrentAcGsView(int vpNum);                                    // return nullptr if none exists.
ACCORE_PORT AcGsView *acgsGetCurrent3dAcGsView(int vpNum);                                  // return nullptr if none exists.

ACCORE_PORT AcGsView *acgsObtainAcGsView(int vpNum, const class AcGsKernelDescriptor &);    // create if necessary.
AcGsModel *acgsGetGsModel(AcGiTransientDrawingMode mode, int subDrawingMode, int viewportNumber);

class CView;

// Pass in NULL to get the AcGsManager associated with the current MDI Client Window;
// otherwise, be sure that the passed in view is really an AutoCAD MDI Client window.
AcGsManager *   acgsGetGsManager            (CView * pView = NULL);

class AcGeVector3d;
Adesk::Boolean  acgsGetOrthoViewParameters  (int viewportNumber,
                                             AcDb::OrthographicView view,
                                             AcGeVector3d * pViewDir,
                                             AcGeVector3d * pUpVector);

// Use acgsCreate2DViewLimitManager and acgsDestroy2DViewLimitManager to
// create and destroy instances of this pure virtual, abstract class
class AcGs2DViewLimitManager
{
public:
    virtual                ~AcGs2DViewLimitManager  (void) { }
    virtual bool            testView                (AcGePoint3d const & target,
                                                     double              dFieldHeight)  = 0;
};

AcGs2DViewLimitManager *    acgsCreate2DViewLimitManager  (int viewportNumber);
void                        acgsDestroy2DViewLimitManager (AcGs2DViewLimitManager * pLimitManager);

Adesk::Boolean              acgsDrawableModified (AcGiDrawable *pDrawable,
                                                  AcGiDrawable *pParentDrawable);
Adesk::Boolean              acgsDrawableErased   (AcGiDrawable *pDrawable,
                                                  AcGiDrawable *pParentDrawable);
ACCORE_PORT Adesk::Boolean  acgsDrawableCached   (AcGiDrawable *pDrawable);

#pragma pack (pop)
#endif // _ACGS_H
