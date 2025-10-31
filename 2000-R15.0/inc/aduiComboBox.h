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
//////////////////////////////////////////////////////////////////////////////

#ifndef _aduiComboBox_h
#define _aduiComboBox_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CAdUiComboBox window
//
// This is the main Combo Box itself

class ADUI_PORT CAdUiComboBox : public CComboBox {
    DECLARE_DYNAMIC(CAdUiComboBox)

public:
                CAdUiComboBox ();
virtual         ~CAdUiComboBox ();

// Fixed MFC Routines
public:
        // Use GetLBString() to circumvent GetLBText() errors.
        void    GetLBString (int nIndex, CString& rString);

// Misc.
protected:
        CPoint  m_lastMousePoint;
        CRect   m_tipRect;

public:
virtual void    GetContentExtent (LPCTSTR text, int& width, int& height);
        void    GetTextExtent (LPCTSTR text, int& width, int& height);
        BOOL    IsOwnerDraw ();
        BOOL    IsStatic ();

// AdUi message handlers
protected:
        CWnd    *m_aduiParent;

virtual ADUI_REPLY DoAdUiMessage (
                    ADUI_NOTIFY notifyCode, UINT controlId, LPARAM lParam
                );
virtual void    OnDrawTip (CDC& dc);
virtual BOOL    OnDrawTipText (CAdUiDrawTipText& dtt);
virtual ADUI_REPLY OnGetTipSupport (CPoint& p);
virtual BOOL    OnGetTipRect (CRect& r);
virtual BOOL    OnGetTipText (CString& text);
virtual BOOL    OnHitTipRect (CPoint& p);
public:
        CWnd    *GetAdUiParent ();
        void    SetAdUiParent (CWnd *w);

// Subclassed controls
protected:
        BOOL    m_bAutoDeleteEBox       : 1;    // set to automatically delete
        BOOL    m_bAutoDeleteLBox       : 1;    //  the edit or listbox controls
        BOOL    m_bSubclassedControls   : 1;    // set when all children are found
        CAdUiEdit *m_pComboEBox;                // the child edit control (if any)
        CAdUiListBox *m_pComboLBox;             // the list box

public:
        CAdUiEdit *GetEditBox ();
        void    SetEditBox (CAdUiEdit *control, BOOL autoDelete);
        CAdUiListBox *GetListBox ();
        void    SetListBox (CAdUiListBox *control, BOOL autoDelete);

// Validation style for subclassed EditBox
public:
        DWORD   GetStyleMask ();
        BOOL    IsStyleMaskSet (DWORD mask);
        void    SetStyleMask (DWORD mask);

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiComboBox)
    //}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAdUiComboBox)
    afx_msg LONG OnAdUiMessage (WPARAM wParam, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

/////////////////////////////////////////////////////////////////////////////
