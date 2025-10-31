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

#ifndef ARXDBGUIDLGDXF_H
#define ARXDBGUIDLGDXF_H

#include "Res_ArxDbg.h"

/****************************************************************************
**
**	CLASS ArxDbgUiDlgDxf:
**
**	**jma
**
*************************************/

class ArxDbgUiDlgDxf : public CAcUiDialog {

public:
				ArxDbgUiDlgDxf(CWnd* parent, AcDbObject* obj);
    virtual		~ArxDbgUiDlgDxf()    {}

    //{{AFX_DATA(ArxDbgUiDlgDxf)
    enum { IDD = ARXDBG_DLG_DXF };
    CListCtrl    m_dxfList;
    //}}AFX_DATA


    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiDlgDxf)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
            ArxDbgUiDlgDxf(CWnd* parent, AcDbObject* obj, UINT dlgId);

    void    displayRbChain(resbuf* dxfData);
    void    buildColumns();

    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiDlgDxf)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    AcDbObject*    m_objPtr;
};


#endif
