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

#ifndef ARXDBG_TBLMAKETEST_H
#define ARXDBG_TBLMAKETEST_H

#include "Res_ArxDbg.h"

/****************************************************************************
**
**    CLASS TblMakeDbox:
**
**    **jma
**
*************************************/

class TblMakeDbox : public CDialog {

public:
                TblMakeDbox(CWnd* pParent);

    virtual INT_PTR    DoModal();

    // Dialog Data
    //{{AFX_DATA(TblMakeDbox)
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA


    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(TblMakeDbox)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

    virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra,
                AFX_CMDHANDLERINFO* pHandlerInfo);

protected:

    // Generated message map functions
    //{{AFX_MSG(TblMakeDbox)
    afx_msg void OnButtonClicked();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
    int    m_buttonId;

        // callback functions
    void    makeNamedBlock();
    void    makeAnonymousBlock();
    void    makeDimstyle();
    void    makeLayer();
    void    makeLinetype();
    void    makeTextstyle();
    void    makeAppid();
    void    makeUcs();
    void    makeView();
    void    makeViewport();

    BOOL    setSymbolName(AcDbSymbolTableRecord* newRec, LPCTSTR newName);
    BOOL    addToSymbolTableAndClose(AcDbSymbolTableRecord* symRec);
};

#endif    // ARXDBG_TBLMAKETEST_H
