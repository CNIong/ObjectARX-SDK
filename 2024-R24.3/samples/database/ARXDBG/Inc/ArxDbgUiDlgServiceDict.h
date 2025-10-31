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

#ifndef ARXDBGUIDLGSERVICEDICT_H
#define ARXDBGUIDLGSERVICEDICT_H

#include "Res_ArxDbg.h"

/****************************************************************************
**
**	CLASS ArxDbgUiDlgServiceDict:
**
**	**jma
**
*************************************/

class ArxDbgUiDlgServiceDict : public CAcUiDialog {

public:
                ArxDbgUiDlgServiceDict(CWnd* pParent);

    //{{AFX_DATA(ArxDbgUiDlgServiceDict)
    enum { IDD = ARXDBG_DLG_SERV_DICT };
    CListCtrl    m_lcServices;
    //}}AFX_DATA


    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiDlgServiceDict)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiDlgServiceDict)
    virtual BOOL OnInitDialog();
    afx_msg void OnAdd();
    afx_msg void OnRemove();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
    CStringArray        m_keyStrs;
    CStringArray        m_classStrs;
    CStringArray        m_idStrs;
    CStringArray        m_depStrs;
    AcDbVoidPtrArray    m_servicePtrs;

        // helper functions
    void            buildColumns();
    void            buildServiceList();
    void            display();
    AcRxService*    getCurrentService();
    void            updateDependencyStrings();

};


#endif    // ARXDBGUIDLGSERVICEDICT_H
