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
