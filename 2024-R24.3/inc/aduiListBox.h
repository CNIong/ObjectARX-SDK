//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//      arxsdk/aduiListBox.h
//

#pragma once

#include "adui_port.h"

#pragma pack (push, 8)
#ifndef _ADESK_MAC_

class CAdUiComboBox;
class CAdUiDrawTipText;

/////////////////////////////////////////////////////////////////////////////
// CAdUiListBox window
#pragma warning(push)
#pragma warning(disable : 4275) // exported class derives from non-exported class
class ADUI_PORT CAdUiListBox : public CListBox {
    DECLARE_DYNAMIC(CAdUiListBox);

public:
                CAdUiListBox ();
                ~CAdUiListBox ();

// Misc.
protected:
        CPoint  m_lastMousePoint;
        int     m_tipItem;
        CRect   m_tipRect;

public:
virtual void    GetContentExtent (
                    int item, LPCTSTR text, int& width, int& height
                );
        int     GetItemAtPoint (CPoint& p);
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

// Subclassed ComboLBox support
protected:
        BOOL    m_bComboBoxDraw;
        CAdUiComboBox *m_pComboBox;

public:
        CAdUiComboBox *GetComboBox ();
        void    SetComboBox (CAdUiComboBox *control);
        BOOL    GetComboBoxDraw ();
        void    SetComboBoxDraw (BOOL comboBoxDraw);

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiListBox)
    int  CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct) override;
    void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct) override;
    void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
    void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) override;
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiListBox)
    afx_msg LRESULT OnAdUiMessage (WPARAM wParam, LPARAM lParam);
    afx_msg void OnDestroy();
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
