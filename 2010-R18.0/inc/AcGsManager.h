// 
// (C) Copyright 1997-2006 by Autodesk, Inc. 
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
};


#pragma pack (pop)
#endif // __ACGSMANAGER_H__
