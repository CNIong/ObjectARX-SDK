//////////////////////////////////////////////////////////////////////////////
//
//                 (C) Copyright 2002-2006 by Autodesk, Inc.
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
#ifndef ACUIDLGWORKSHEET_H
#define ACUIDLGWORKSHEET_H

#include "aduiDIalogWorksheet.h"


// CAcUiDialogWorksheet.h : header file
//

///////////////////////////////////////////////////////////////////////////////
//
//  Introduction:
//
//  Basics:
//
//
//  Include File:
//  CAcUiDialogWorksheet.h
//
///////////////////////////////////////////////////////////////////////////////

class ACUI_PORT CAcUiDialogWorksheet : public CAdUiDialogWorksheet
{
    DECLARE_DYNAMIC(CAcUiDialogWorksheet);
    
// Construction
public:
    CAcUiDialogWorksheet(UINT ID, CWnd* pParent = NULL, HINSTANCE hResInst=NULL);   // standard constructor
    ~CAcUiDialogWorksheet();

    // Dialog Data
    //{{AFX_DATA(CAcUiDialogWorksheet)
    enum { IDD = 0 };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAcUiDialogWorksheet)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CAcUiDialogWorksheet)
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg void OnNcPaint();
    afx_msg BOOL OnNcActivate(BOOL bActive);
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg BOOL OnEraseBkgnd(CDC *pDC);
    afx_msg void OnNcLButtonDown( UINT nHitTest, CPoint point );
    afx_msg void OnNcLButtonUp( UINT nHitTest, CPoint point );
    afx_msg void OnNcMouseMove(UINT nHitTest,CPoint point);
    afx_msg void OnMouseMove(UINT nHitTest,CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
#if _MSC_VER<1400
    afx_msg UINT OnNcHitTest(CPoint point);
#else
    afx_msg LRESULT OnNcHitTest(CPoint point);
#endif
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg void OnSysColorChange();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif /* ACUIDLGWORKSHEET_H */
