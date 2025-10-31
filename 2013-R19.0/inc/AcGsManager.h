// 
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2012 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// MODULE:      AcGsManager.h
// PURPOSE:     Interface of Exported AutoCAD-GS-ARX-DB glue code
//

#ifndef __ACGSMANAGER_H__
#define __ACGSMANAGER_H__
#pragma pack (push, 8)


class AcDbViewportTableRecord;
class AcGiDrawable;
class AcGsClassFactory;
class AcGsView;
class AcGsModel;
class AcGsDevice;
struct AcGsClientViewInfo;

// ****************************************************************************
// AcGsManager

class AcGsManager
{
public:
                                AcGsManager             (void) { }
    virtual                    ~AcGsManager             (void) { }

    virtual AcGsModel *         createAutoCADModel      (void)                          = 0;
    virtual AcGsView *          createAutoCADViewport   (AcDbViewportTableRecord * vp)  = 0;    // creates a view of {vp, DBmodel}
    virtual AcGsView *          createAutoCADView       (AcGiDrawable * drawable)       = 0;    // creates a view with {Drawable, DBModel} 
                                                                                                // pair selected for viewing, connected to
                                                                                                // AutoCAD's GUI Device
    virtual AcGsDevice *        createAutoCADDevice     (HWND hWnd)                     = 0;
    virtual AcGsDevice *        createAutoCADOffScreenDevice()                          = 0;

    virtual void                destroyAutoCADModel     (AcGsModel  * model)            = 0;
    virtual void                destroyAutoCADView      (AcGsView   * view)             = 0;
    virtual void                destroyAutoCADDevice    (AcGsDevice * device)           = 0;
    
    virtual AcGsClassFactory *  getGSClassFactory       (void)                          = 0;
    virtual AcGsModel        *  getDBModel              (void)                          = 0;
    virtual AcGsDevice       *  getGUIDevice            (void)                          = 0;

    Adesk::ULongPtr             viewportIdFromClientInfo        (const AcGsClientViewInfo& info) const;
    Adesk::Int16                acadWindowIdFromClientInfo      (const AcGsClientViewInfo& info) const;
    AcDbObjectId                viewportObjectIdFromClientInfo  (const AcGsClientViewInfo& info) const;
};



#pragma pack (pop)
#endif // __ACGSMANAGER_H__
