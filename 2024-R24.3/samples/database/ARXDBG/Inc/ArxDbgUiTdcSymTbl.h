//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

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
