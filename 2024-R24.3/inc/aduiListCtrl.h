//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//      arx/aduiListCtrl.h
//

#pragma once

#include "adui_port.h"
#include "aduiHeaderCtrl.h"     // for CAdUiHeaderCtrl

#pragma pack (push, 8)
#ifndef _ADESK_MAC_
class CAdUiDrawTipText;

/////////////////////////////////////////////////////////////////////////////
// CAdUiListCtrl window
#pragma warning(push)
#pragma warning(disable : 4275) // exported class derives from non-exported class

class ADUI_PORT CAdUiListCtrl : public CListCtrl {
    DECLARE_DYNAMIC(CAdUiListCtrl);

public:
                CAdUiListCtrl ();
                ~CAdUiListCtrl ();

// Misc.
protected:
        CPoint  m_lastMousePoint;
        int     m_tipIndex;
        int     m_tipItem;
        CRect   m_tipRect;

public:
        CAdUiHeaderCtrl m_headerCtrl;

        int     ColumnCount ();
virtual void    GetContentExtent (
                    int item, int index, LPCTSTR text, int& width, int& height
                );
        BOOL    GetItemAtPoint (CPoint& p, int& item, int& index);
        BOOL    GetSubItemRect (int item, int index, CRect& rect);
        void    GetTextExtent (LPCTSTR text, int& width, int& height);
        BOOL    IsOwnerDraw ();

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
    //{{AFX_VIRTUAL(CAdUiListCtrl)
    protected:
    void PreSubclassWindow() override;
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiListCtrl)
    afx_msg LRESULT OnAdUiMessage (WPARAM wParam, LPARAM lParam);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
#pragma warning(pop)

#endif //_ADESK_MAC_
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)

/////////////////////////////////////////////////////////////////////////////
