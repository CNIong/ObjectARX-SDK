//////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1994-1999 by Autodesk, Inc.
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
// DESCRIPTION:
//
//   Declarations for various button classes
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _acuiButton_h
#define _acuiButton_h

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// Owner-draw Button

class ACUI_PORT CAcUiOwnerDrawButton : public CAdUiOwnerDrawButton {
	DECLARE_DYNAMIC(CAcUiOwnerDrawButton)

public:
	            CAcUiOwnerDrawButton ();
virtual         ~CAcUiOwnerDrawButton ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiOwnerDrawButton)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiOwnerDrawButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Bitmap Button

class ACUI_PORT CAcUiBitmapButton : public CAdUiBitmapButton {
	DECLARE_DYNAMIC(CAcUiBitmapButton)

public:
	            CAcUiBitmapButton ();
virtual         ~CAcUiBitmapButton ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiBitmapButton)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiBitmapButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Static-Style Bitmap Button

class ACUI_PORT CAcUiBitmapStatic : public CAdUiBitmapStatic {
	DECLARE_DYNAMIC(CAcUiBitmapStatic)

public:
	            CAcUiBitmapStatic ();
virtual         ~CAcUiBitmapStatic ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiBitmapStatic)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiBitmapStatic)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Drag&Drop Site

class ACUI_PORT CAcUiDropSite : public CAdUiDropSite {
	DECLARE_DYNAMIC(CAcUiDropSite)

public:
	            CAcUiDropSite ();
virtual         ~CAcUiDropSite ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiDropSite)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiDropSite)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// "Pick-a-point" Button

class ACUI_PORT CAcUiPickButton : public CAdUiBitmapButton {
	DECLARE_DYNAMIC(CAcUiPickButton)

public:
	            CAcUiPickButton ();
virtual         ~CAcUiPickButton ();

// Bitmap Button routines
protected:
virtual BOOL    OnLoadBitmap (LPCTSTR strResId);

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiPickButton)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiPickButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// "Make-A-Selection" Button

class ACUI_PORT CAcUiSelectButton : public CAcUiPickButton {
	DECLARE_DYNAMIC(CAcUiSelectButton)

public:
	            CAcUiSelectButton ();
virtual         ~CAcUiSelectButton ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiSelectButton)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiSelectButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Tool-Style Button

class ACUI_PORT CAcUiToolButton : public CAdUiToolButton {
	DECLARE_DYNAMIC(CAcUiToolButton)

public:
	            CAcUiToolButton ();
virtual         ~CAcUiToolButton ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiToolButton)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiToolButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif

//////////////////////////////////////////////////////////////////////////////
