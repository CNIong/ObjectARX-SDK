//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//

#ifndef ARXDBG_XFORMTEST_H
#define ARXDBG_XFORMTEST_H

#include "Res_ArxDbg.h"

/****************************************************************************
**
**    CLASS XformDbox:
**
**    **jma
**
*************************************/

class XformDbox : public CDialog {

public:
                XformDbox(CWnd* pParent);
    virtual        ~XformDbox()    {}

    virtual INT_PTR    DoModal();

    //{{AFX_DATA(XformDbox)
    int        m_rotateType;
    int        m_transType;
    BOOL    m_xformCopy;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(XformDbox)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

    virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra,
                            AFX_CMDHANDLERINFO* pHandlerInfo);

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(XformDbox)
    afx_msg void OnButtonClicked();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
    UINT    m_buttonId;

        // callback functions
    void    rotate();
    void    scale();
    void    move();
    void    mirror();
    void    wcsOrigin();

        // helper functions
    void    doXform(AcDbEntity* ent, const AcGeMatrix3d& m);

        // Radio Group indices
    enum RgRotation {
        kRbUcsXAxis    = 0,
        kRbUcsYAxis,
        kRbUcsZAxis,
        kRbEcsZAxis,
    };

    enum RgTranslation {
        kRbFromTo    = 0,
        kRbUcsDisp,
    };
};

#endif    // ARXDBG_XFORMTEST_H
