//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//      arxsdk/aduiToolBar.h
//
// DESCRIPTION:
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "adui_port.h"
#include "aduiToolBarCtrl.h"    // for ADUI_TBSTYLE_AUTOSTRETCH

///////////////////////////////////////////////////////////////////////////////
/// class CAdUiToolBar
///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// CAdUiToolBar class is a toolbar control that supports automatic scaling when button images are added.
/// </summary>
/// <remarks>
/// For automatic scaling to work, the control must have been created with the <c>ADUI_TBSTYLE_AUTOSTRETCH</c> style.
/// </remarks>
class ADUI_PORT CAdUiToolBar : public CToolBar
{
    DECLARE_DYNAMIC(CAdUiToolBar)
public:
    /// <summary>
    /// Constructs a CAdUiToolBar object.
    /// </summary>
    CAdUiToolBar();

    /// <summary>
    /// Destroys this CAdUiToolBar object.
    /// </summary>
    ~CAdUiToolBar();

    /// <summary>
    /// Call this member function to load the toolbar specified by lpszResourceName.
    /// </summary>
    /// <param name="lpszResourceName">Pointer to the resource name of the toolbar to be loaded.</param>
    /// <returns>Nonzero if successful; otherwise 0.</returns>
    BOOL LoadToolBar(LPCTSTR lpszResourceName);

    /// <summary>
    /// Call this member function to load the toolbar specified by nIDResource.
    /// </summary>
    /// <param name="nIDResource">Resource ID of the toolbar to be loaded.</param>
    /// <returns>Nonzero if successful; otherwise 0.</returns>
    BOOL LoadToolBar(UINT nIDResource);

protected:
    //{{AFX_MSG
    afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

