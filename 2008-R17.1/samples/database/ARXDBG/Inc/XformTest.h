//
// (C) Copyright 1998-2007 by Autodesk, Inc. 
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
