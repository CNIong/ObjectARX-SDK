//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

class AcDbViewportTableRecord;
class AcGiDrawable;
class AcGsGraphicsKernel;
class AcGsKernelDescriptor;
class AcGsView;
class AcGsModel;
class AcGsDevice;
class AcGsConfig;
struct AcGsClientViewInfo;

#ifndef DRAWBRIDGE_API
#define DRAWBRIDGE_API __declspec(dllimport)
#endif // DRAWBRIDGE_API

class AcGsManager
{
public:
                                AcGsManager                 (void) { }
    virtual                    ~AcGsManager                 (void) { }

    virtual AcGsModel          *createAutoCADModel          (AcGsGraphicsKernel &)                            = 0;

    // creates a view of {vp, DBmodel}
    virtual AcGsView           *createAutoCADViewport       (AcGsGraphicsKernel &, AcDbViewportTableRecord *) = 0;

    // creates a view with {Drawable, DBModel} pair selected for viewing, connected to AutoCAD's GUI Device
    virtual AcGsView           *createAutoCADView           (AcGsGraphicsKernel &, AcGiDrawable *)            = 0;

    virtual AcGsDevice         *createAutoCADDevice         (AcGsGraphicsKernel &, HWND hWnd)                 = 0;
    virtual AcGsDevice         *createAutoCADOffScreenDevice(AcGsGraphicsKernel &)                            = 0;

    virtual void                destroyAutoCADModel         (AcGsModel  *)                                    = 0;
    virtual void                destroyAutoCADView          (AcGsView   *)                                    = 0;
    virtual void                destroyAutoCADDevice        (AcGsDevice *)                                    = 0;

    virtual AcGsModel          *getDBModel                  (AcGsGraphicsKernel &)                            = 0;
    virtual AcGsDevice         *getGUIDevice                (AcGsGraphicsKernel &)                            = 0;

    // Global methods
    static DRAWBRIDGE_API AcGsGraphicsKernel *acquireGraphicsKernel(const AcGsKernelDescriptor &);
    static DRAWBRIDGE_API void                releaseGraphicsKernel(AcGsGraphicsKernel *);
    static DRAWBRIDGE_API AcGsConfig         *getConfig            (void);
};

class AcGsManager2 : public AcGsManager
{
public:

    /// <summary>
    /// Gets an offscreen device for the specificed kernel. An offscreen device is created if
    /// none exists and cached for subsequent use. Currently only supports the k3DRapidRTRendering
    /// kernel. 
    /// </summary>
    /// <returns>
    /// Returns a valid device if successful. 
    /// </returns>
    virtual AcGsDevice         *getOffScreenDevice          (AcGsGraphicsKernel &)                            = 0;

    /// <summary>
    /// Gets an offscreen view for the specificed kernel. The view is connectd to the offscreen device. 
    /// It is created on demand and cached, however its lifetime is ephemeral and not guaranteed past 
    /// the next call to this function with different AcGsClientViewInfo parameters. Currently only 
    /// supports the k3DRapidRTRendering kernel. 
    /// </summary>
    /// <returns>
    /// Returns a valid offscreen view if successful. 
    /// </returns>
    virtual AcGsView           *getOffScreenView            (AcGsGraphicsKernel &, AcGsClientViewInfo &)      = 0;
};
