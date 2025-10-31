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

#ifndef ARXDBGUITDCLONGTRANS_H
#define ARXDBGUITDCLONGTRANS_H

#include "ArxDbgUiTdcDbObjectBase.h"

/****************************************************************************
**
**	CLASS ArxDbgUiTdcLongTrans:
**
**	**jma
**
*************************************/

class ArxDbgUiTdcLongTrans : public ArxDbgUiTdcDbObjectBase {

public:
                ArxDbgUiTdcLongTrans(AcDbLongTransaction* lt);
    virtual		~ArxDbgUiTdcLongTrans()    {}

    //{{AFX_DATA(ArxDbgUiTdcLongTrans)
    enum { IDD = ARXDBG_TDC_LONG_TRANS };
    CListCtrl	m_dataList;
    CTreeCtrl	m_tblTree;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdcLongTrans)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcLongTrans)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangedSymtabs(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg virtual void OnDxf();
    afx_msg virtual void OnExtdict();
    afx_msg virtual void OnReactors();
    afx_msg virtual void OnXdata();
    afx_msg virtual void OnDatabase();
    afx_msg virtual void OnDocument();
    afx_msg virtual void OnShowIdMap();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
		// data members
	AcDbLongTransaction*	m_longTrans;
	AcDbObjectIdArray		m_objIdList;

		// helper functions
    HTREEITEM		addOneTreeItem(LPCTSTR name, const AcDbObjectId& objId,
								HTREEITEM parent, bool sortAlpha = true);
    void			displayCurrent(int index);

	virtual bool	getReferencedObjects(AcDbObjectIdArray& hardPointerIds,
										 AcDbObjectIdArray& softPointerIds,
										 AcDbObjectIdArray& hardOwnershipIds,
										 AcDbObjectIdArray& softOwnershipIds);
};


#endif    // ARXDBGUITDCLONGTRANS_H
