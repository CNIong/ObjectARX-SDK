//////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1994-2002 by Autodesk, Inc.
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
//////////////////////////////////////////////////////////////////////////////

#ifndef _acuiDock_h
#define _acuiDock_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CAcUiDockFrame window - INTERNAL USE ONLY

class ACUI_PORT CAcUiDockFrame : public CAdUiDockFrame {
    DECLARE_DYNCREATE(CAcUiDockFrame);

public:
	            CAcUiDockFrame ();
virtual         ~CAcUiDockFrame ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiDockFrame)
	//}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiDockFrame)
    afx_msg LRESULT OnACADKeepFocus (WPARAM wParam, LPARAM lParam);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAcUiDockControlBar window

class ACUI_PORT CAcUiDockControlBar : public CAdUiDockControlBar {
    DECLARE_DYNCREATE(CAcUiDockControlBar);

public:
    CAcUiDockControlBar () {}

protected:
    virtual bool CanFrameworkTakeFocus ();
};

/////////////////////////////////////////////////////////////////////////////
// CAcUiPaletteSetDockFrame window - INTERNAL USE ONLY

class ACUI_PORT CAcUiPaletteSetDockFrame : public CAdUiPaletteSetDockFrame {
    DECLARE_DYNCREATE(CAcUiPaletteSetDockFrame);

public:
	            CAcUiPaletteSetDockFrame ();
virtual         ~CAcUiPaletteSetDockFrame ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiPaletteSetDockFrame)
	//}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiPaletteSetDockFrame)
    afx_msg LRESULT OnACADKeepFocus (WPARAM wParam, LPARAM lParam);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

//////////////////////////////////////////////////////////////////////////////
