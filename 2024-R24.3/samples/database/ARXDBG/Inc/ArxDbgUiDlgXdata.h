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

#ifndef ARXDBGUIDLGXDATA_H
#define ARXDBGUIDLGXDATA_H

#include "ArxDbgUiDlgDxf.h"
#include "ArxDbgXdata.h"

/****************************************************************************
**
**	CLASS ArxDbgUiDlgXdata:
**
**	**jma
**
*************************************/

class ArxDbgUiDlgXdata : public ArxDbgUiDlgDxf {

public:
				ArxDbgUiDlgXdata(CWnd* parent, AcDbObject* obj);
    virtual		~ArxDbgUiDlgXdata()    {}

    //{{AFX_DATA(ArxDbgUiDlgXdata)
    enum { IDD = ARXDBG_DLG_XDATA };
    CComboBox    m_appPopUp;
    //}}AFX_DATA


    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiDlgXdata)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiDlgXdata)
    virtual BOOL OnInitDialog();
    afx_msg void OnAppNameSelected();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    ArxDbgAppXdataList    m_xdata;
};


#endif  // ARXDBGUIDLGXDATA_H
