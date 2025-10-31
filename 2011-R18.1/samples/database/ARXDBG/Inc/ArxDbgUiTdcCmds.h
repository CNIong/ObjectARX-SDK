//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
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
