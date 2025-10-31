//////////////////////////////////////////////////////////////////////////////
//
//               (C) Copyright 1994-2007 by Autodesk, Inc.
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

#ifndef _aduiHeaderCtrl_h
#define _aduiHeaderCtrl_h
#pragma pack (push, 8)

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CAdUiHeaderCtrl window
#pragma warning(push)
#pragma warning(disable : 4275)
class ADUI_PORT CAdUiHeaderCtrl : public CHeaderCtrl {
    DECLARE_DYNAMIC(CAdUiHeaderCtrl)

public:
                CAdUiHeaderCtrl ();
virtual         ~CAdUiHeaderCtrl ();

// Misc.
protected:
        // store the last mouse point recorded
        CPoint  m_lastMousePoint;
        int     m_tipItem;
        CRect   m_tipRect;

public:
virtual void    GetContentExtent (
                    int item, LPCTSTR text, int& width, int& height
                );
        int     GetItemAtPoint (CPoint& p);
        BOOL    GetItemRect (int idx, CRect& rItem);
        BOOL    GetText (int idx, CString& text);
        void    GetTextExtent (LPCTSTR text, int& width, int& height);
        BOOL    IsOwnerDraw (int idx);

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

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiHeaderCtrl)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiHeaderCtrl)
    afx_msg LRESULT OnAdUiMessage (WPARAM wParam, LPARAM lParam);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
#pragma warning(pop)
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

/////////////////////////////////////////////////////////////////////////////
