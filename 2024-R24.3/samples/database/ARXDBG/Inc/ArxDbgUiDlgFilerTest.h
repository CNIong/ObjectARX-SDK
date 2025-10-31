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

#ifndef ARXDBGUIDLGFILERTEST_H
#define ARXDBGUIDLGFILERTEST_H

#include "Res_ArxDbg.h"

/****************************************************************************
**
**	CLASS ArxDbgUiDlgFilerTest:
**
**	**jma
**
*************************************/

class ArxDbgUiDlgFilerTest : public CAcUiDialog {

public:
                ArxDbgUiDlgFilerTest(CWnd* pParent);

    AcDb::FilerType        indexToFilerType(int index);

    //{{AFX_DATA(ArxDbgUiDlgFilerTest)
    enum { IDD = ARXDBG_DLG_FILER_TEST };
    int        m_puFilerTypeIndex;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiDlgFilerTest)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiDlgFilerTest)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif // ARXDBGUIDLGFILERTEST_H
