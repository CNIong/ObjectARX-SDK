//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


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
