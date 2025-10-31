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

#ifndef ARXDBGUITDMOBJECTS_H
#define ARXDBGUITDMOBJECTS_H

#include "Res_ArxDbg.h"

class ArxDbgUiTdcObjects;


/****************************************************************************
**
**	CLASS ArxDbgUiTdmObjects:
**
**	**jma
**
*************************************/

class ArxDbgUiTdmObjects : public CAcUiTabMainDialog {

public:
            ArxDbgUiTdmObjects(const AcDbObjectIdArray& objIds, CWnd* parent, const TCHAR* winTitle = NULL);
	virtual	~ArxDbgUiTdmObjects();

    //{{AFX_DATA(ArxDbgUiTdmObjects)
    enum { IDD = ARXDBG_TDM_ENTS };
	CAdUiTab	m_tabCtrl;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdmObjects)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdmObjects)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	CString				m_winTitle;
	ArxDbgUiTdcObjects*	m_tdcObjs;
};

#endif // ARXDBGUITDMOBJECTS_H

