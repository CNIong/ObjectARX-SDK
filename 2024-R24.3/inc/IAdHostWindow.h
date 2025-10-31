//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
  
//
// IAcApWindow - Provides the interface definition for a generic window 
// in the application
#pragma once

#ifndef  ADHOSTWINDOW_H
#define ADHOSTWINDOW_H

class IAdHostWindow  
{
public:
    using WindowHandle = HWND;
    // The window identifier. This will generally be a platform or 
    // application dependent identifier for the window.
    virtual WindowHandle windowHandle() const = 0;

};

#endif //ACAPWINDOW_H
