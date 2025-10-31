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

#ifndef ARXDBGUITDCCLONESET_H
#define ARXDBGUITDCCLONESET_H

#include "Res_ArxDbg.h"
#include "ArxDbgCloneSet.h"

/****************************************************************************
**
**	CLASS ArxDbgUiTdcCloneSet:
**
**	**jma
**
*************************************/

class ArxDbgUiTdcCloneSet : public CAcUiTabChildDialog {

public:
				ArxDbgUiTdcCloneSet();
    virtual		~ArxDbgUiTdcCloneSet()    {}

    //{{AFX_DATA(ArxDbgUiTdcCloneSet)
    enum { IDD = ARXDBG_TDC_CLONESET };
	CListBox			m_lbObjList;
	CListBox			m_lbDbList;
    CAcUiSelectButton	m_selectButton;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdcCloneSet)
    public:
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    //}}AFX_VIRTUAL

protected:

    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcCloneSet)
    afx_msg void OnShow();
    afx_msg void OnBrowse();
    afx_msg void OnRemove();
    afx_msg void OnRemoveAll();
    afx_msg void OnSelect();
    afx_msg void OnObjectsChanged();
    afx_msg void OnDatabaseChanged();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	AcDbVoidPtrArray	m_dbPtrs;
	AcDbObjectIdArray	m_objIds;
	ArxDbgCloneSet&		m_cloneSet;

        // helper functions
	void	setButtonModes();
	void	displayDbList();
	void	displayObjList();
	int		getIndexFor(AcDbDatabase* db);
};

#endif    // ARXDBGUITDCCLONESET_H
