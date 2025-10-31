// (C) Copyright 1999 by Autodesk, Inc. 
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

#if !defined(AFX_ASDKACUIDIALOGSAMPLE_H__5A964FBA_3201_11D2_8C8D_0040054247F9__INCLUDED_)
#define AFX_ASDKACUIDIALOGSAMPLE_H__5A964FBA_3201_11D2_8C8D_0040054247F9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"
#include <dbsymtb.h>
#include <dbapserv.h>
#include <adslib.h>
#include <adui.h>
#include <acui.h>

// AsdkAcUiDialogSample.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AsdkAcUiDialogSample dialog

class AsdkAcUiDialogSample : public CAcUiDialog
{
// Construction
public:
    AsdkAcUiDialogSample(CWnd* pParent = NULL);   // standard constructor
    void DisplayPoint();
    bool ValidatePoint();

    void DisplayAngle();
    bool ValidateAngle();

    void DisplayBlocks();
    void DisplayRegApps();

    CString m_strAngle;
    CString m_strXPt;
    CString m_strYPt;
    CString m_strZPt;

// Dialog Data
    //{{AFX_DATA(AsdkAcUiDialogSample)
    enum { IDD = IDD_DIALOG1 };
    CAcUiSymbolComboBox m_ctrlRegAppComboBox;
    CAcUiListBox    m_ctrlBlockListBox;
    CAcUiPickButton m_ctrlPickButton;
    CAcUiPickButton m_ctrlAngleButton;
    CAcUiAngleEdit  m_ctrlAngleEdit;
    CAcUiNumericEdit m_ctrlXPtEdit;
    CAcUiNumericEdit m_ctrlYPtEdit;
    CAcUiNumericEdit m_ctrlZPtEdit;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(AsdkAcUiDialogSample)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(AsdkAcUiDialogSample)
    afx_msg void OnButtonPoint();
    virtual BOOL OnInitDialog();
    afx_msg void OnButtonAngle();
    afx_msg void OnKillfocusComboRegapps();
    virtual void OnOK();
    afx_msg void OnKillfocusEditAngle();
    afx_msg void OnKillfocusEditXpt();
    afx_msg void OnKillfocusEditYpt();
    afx_msg void OnKillfocusEditZpt();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASDKACUIDIALOGSAMPLE_H__5A964FBA_3201_11D2_8C8D_0040054247F9__INCLUDED_)
