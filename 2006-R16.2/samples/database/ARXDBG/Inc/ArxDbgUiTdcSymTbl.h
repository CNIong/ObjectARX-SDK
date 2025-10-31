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

#ifndef ARXDBGUITDCSYMTBL_H
#define ARXDBGUITDCSYMTBL_H

#include "ArxDbgUiTdcDbObjectBase.h"

/****************************************************************************
**
**	CLASS ArxDbgUiTdcSymTbl:
**
**	**jma
**
*************************************/

class ArxDbgUiTdcSymTbl : public ArxDbgUiTdcDbObjectBase {

public:
                ArxDbgUiTdcSymTbl(AcDbDatabase* db);
    virtual		~ArxDbgUiTdcSymTbl()    {}

    //{{AFX_DATA(ArxDbgUiTdcSymTbl)
    enum { IDD = ARXDBG_TDC_SYMTBLS };
    CButton		m_blkEntsButton;
    CButton		m_blkRefsButton;
	CButton 	m_cbShowErased;
	CButton 	m_cbShowNested;
	CButton 	m_cbShowErasedRefs;
    CListCtrl	m_dataList;
    CTreeCtrl	m_tblTree;
    BOOL		m_showErasedBlkEnts;
    BOOL		m_showNestedBlkRefs;
    BOOL		m_showErasedBlkRefs;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdcSymTbl)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcSymTbl)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangedSymtabs(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBnBlkEnts();
    afx_msg void OnBnBlkRefs();
    afx_msg void OnCbShowNested();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
		// data members
    AcDbObjectIdArray    m_tblObjIdList;		// tblentry Object Ids
    AcDbDatabase*        m_db;					// database we are looking at

		// helper functions
    HTREEITEM	addOneTreeItem(LPCTSTR name, const AcDbObjectId& objId,
                            HTREEITEM parent, bool sortAlpha = true);
    void        addOneTable(const AcDbSymbolTable* symTbl, HTREEITEM parent);
    void        displayCurrent(int index);
	void		setBlockInfoButtons(AcDbObject* obj);
    void        collectBlkEnts(AcDbBlockTableRecord* blkTbl,
                                AcDbObjectIdArray& blkEnts,
                                bool skipErased);
};


#endif    // ARXDBGUITDCSYMTBL_H
