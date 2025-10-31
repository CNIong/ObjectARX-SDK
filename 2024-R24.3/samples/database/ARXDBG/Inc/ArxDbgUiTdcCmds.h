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

#ifndef ARXDBGUITDCCMDS_H
#define ARXDBGUITDCCMDS_H

#include "Res_ArxDbg.h"
#include "ArxDbgUiTdcRxObjectBase.h"

/****************************************************************************
**
**	CLASS ArxDbgUiTdcCmds:
**
**	**jma
**
*************************************/

class ArxDbgUiTdcCmds : public ArxDbgUiTdcRxObjectBase {

public:
				ArxDbgUiTdcCmds();
    virtual		~ArxDbgUiTdcCmds();

    //{{AFX_DATA(ArxDbgUiTdcCmds)
    enum { IDD = ARXDBG_TDC_COMMANDS };
    CTreeCtrl	m_cmdTree;
    CListCtrl	m_dataList;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdcCmds)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcCmds)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangedCmd(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
		// data members
	AcEdCommand*		m_curCmdPtr;
	CMapStringToPtr		m_cmdMap;

		// helper functions
	HTREEITEM	addCmdTreeItem(LPCTSTR name, void* objPtr, HTREEITEM parent, bool sort);
    void        displayCurrent();

	void		buildCmdGroupMap();
	void		deleteCmdGroupMap();
};


#endif    // ARXDBGUITDCCMDS_H
