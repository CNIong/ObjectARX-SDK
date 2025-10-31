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

#ifndef ARXDBGUITDMLONGTRANS_H
#define ARXDBGUITDMLONGTRANS_H

#include "Res_ArxDbg.h"

class ArxDbgUiTdcLongTrans;


/****************************************************************************
**
**	CLASS ArxDbgUiTdmLongTrans:
**
**	**jma
**
*************************************/

class ArxDbgUiTdmLongTrans : public CAcUiTabMainDialog {

public:
            ArxDbgUiTdmLongTrans(AcDbLongTransaction* longTrans, CWnd* parent, const TCHAR* winTitle = NULL);
	virtual	~ArxDbgUiTdmLongTrans();

    //{{AFX_DATA(ArxDbgUiTdmLongTrans)
    enum { IDD = ARXDBG_TDM_DATABASE };
	CAdUiTab	m_tabCtrl;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdmLongTrans)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdmLongTrans)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	CString					m_winTitle;
	ArxDbgUiTdcLongTrans*	m_tdcLongTrans;
};

#endif // ARXDBGUITDMLONGTRANS_H

