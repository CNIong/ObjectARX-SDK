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

#ifndef ARXDBGUITDCHOSTAPPSRV_H
#define ARXDBGUITDCHOSTAPPSRV_H

#include "Res_ArxDbg.h"
#include "ArxDbgUiTdcRxObjectBase.h"

/****************************************************************************
**
**	CLASS ArxDbgUiTdcHostAppSrv:
**
**	**jma
**
*************************************/

class ArxDbgUiTdcHostAppSrv : public ArxDbgUiTdcRxObjectBase {

public:
				ArxDbgUiTdcHostAppSrv();
    virtual		~ArxDbgUiTdcHostAppSrv();

    //{{AFX_DATA(ArxDbgUiTdcHostAppSrv)
    enum { IDD = ARXDBG_TDC_HOSTAPPSERV };
    CListCtrl	m_dataList;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdcHostAppSrv)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcHostAppSrv)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
		// data members

		// helper functions
    void        displayCurrent();

};


#endif    // ARXDBGUITDCHOSTAPPSRV_H
