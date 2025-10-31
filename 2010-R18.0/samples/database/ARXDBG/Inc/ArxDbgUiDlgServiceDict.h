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
