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
#ifndef ARXDBGUIDLGCLASSDICT_H
#define ARXDBGUIDLGCLASSDICT_H

#include "Res_ArxDbg.h"


/****************************************************************************
**
**	CLASS ArxDbgUiDlgClassDict:
**
**	**jma
**
*************************************/


class ArxDbgUiDlgClassDict : public CAcUiDialog {

public:
            ArxDbgUiDlgClassDict(CWnd* pParent);

    //{{AFX_DATA(ArxDbgUiDlgClassDict)
    enum { IDD = ARXDBG_DLG_CLASS_DICT };
    CListCtrl    m_classList;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiDlgClassDict)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiDlgClassDict)
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
    CStringList    m_classNameStrList;
    CStringList    m_dxfNameStrList;
    CStringList    m_appNameStrList;
    CStringList    m_proxyStrList;
	CStringList	   m_birthDwgVerList;
	CStringList    m_birthMntVerList;

        // helper functions
    void        buildColumns();
    void        buildClassList();
    void        display();
};

#endif // ARXDBGUIDLGCLASSDICT_H

