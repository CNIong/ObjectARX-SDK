//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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

#ifndef ARXDBGUIDLGSYSREGISTRY_H
#define ARXDBGUIDLGSYSREGISTRY_H

#include "Res_ArxDbg.h"

/****************************************************************************
**
**  CLASS ArxDbgUiDlgSysRegistry:
**
**  **jma
**
*************************************/

class ArxDbgUiDlgSysRegistry : public CAcUiDialog {

public:
                ArxDbgUiDlgSysRegistry(CWnd* pParent);
    virtual     ~ArxDbgUiDlgSysRegistry()    {}

    //{{AFX_DATA(ArxDbgUiDlgSysRegistry)
    enum { IDD = ARXDBG_DLG_SYSREGISTRY };
    CTreeCtrl    m_tree;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiDlgSysRegistry)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiDlgSysRegistry)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangedSysReg(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    AcDbVoidPtrArray    m_objList;

    HTREEITEM           addTreeItem(LPCTSTR name, AcRxObject* obj, HTREEITEM parent);
    void                displayCurrent(int index);

};

#endif    // ARXDBGUIDLGSYSREGISTRY_H
