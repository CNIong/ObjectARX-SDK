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

#ifndef ARXDBGUIDLGREACTORS_H
#define ARXDBGUIDLGREACTORS_H

#include "Res_ArxDbg.h"

/****************************************************************************
**
**	CLASS ArxDbgUiDlgReactors:
**
**	**jma
**
*************************************/

class ArxDbgUiDlgReactors : public CAcUiDialog {

public:
				ArxDbgUiDlgReactors(CWnd* parent, AcDbObject* obj);
    virtual		~ArxDbgUiDlgReactors()    {}

    //{{AFX_DATA(ArxDbgUiDlgReactors)
    enum { IDD = ARXDBG_DLG_REACTORS };
    CListBox    m_transList;
    CListBox    m_persistList;
    //}}AFX_DATA


    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiDlgReactors)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:

    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiDlgReactors)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    AcDbObject*    m_objPtr;
};


#endif  // ARXDBGUIDLGREACTORS_H
