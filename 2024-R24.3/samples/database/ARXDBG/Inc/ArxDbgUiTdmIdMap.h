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

#ifndef ARXDBGUITDMIDMAP_H
#define ARXDBGUITDMIDMAP_H

#include "Res_ArxDbg.h"

class ArxDbgUiTdcIdMap;


/****************************************************************************
**
**	CLASS ArxDbgUiTdmIdMap:
**
**	**jma
**
*************************************/

class ArxDbgUiTdmIdMap : public CAcUiTabMainDialog {

public:
            ArxDbgUiTdmIdMap(AcDbIdMapping* idMap, CWnd* parent, const TCHAR* winTitle = NULL);
	virtual	~ArxDbgUiTdmIdMap();

    //{{AFX_DATA(ArxDbgUiTdmIdMap)
    enum { IDD = ARXDBG_TDM_IDMAP };
	CAdUiTab	m_tabCtrl;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdmIdMap)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdmIdMap)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	CString				m_winTitle;
	ArxDbgUiTdcIdMap*	m_tdcIdMap;
};

#endif // ARXDBGUITDMIDMAP_H

