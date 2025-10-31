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

#ifndef ARXDBGUITDCDICT_H
#define ARXDBGUITDCDICT_H

#include "Res_ArxDbg.h"
#include "ArxDbgUiTdcDbObjectBase.h"

/****************************************************************************
**
**	CLASS ArxDbgUiTdcDict:
**
**	**jma
**
*************************************/

class ArxDbgUiTdcDict : public ArxDbgUiTdcDbObjectBase {

public:
				ArxDbgUiTdcDict(const AcDbObjectId& dictId, bool isExtDict);
    virtual		~ArxDbgUiTdcDict()    {}

    //{{AFX_DATA(ArxDbgUiTdcDict)
    enum { IDD = ARXDBG_TDC_DICTS };
    CTreeCtrl	m_dictTree;
    CListCtrl	m_dataList;
    BOOL		m_dictIsHardOwner;
    CComboBox	m_puMergeStyle;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdcDict)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcDict)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangedDict(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnEndlabeleditTreeDict(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKeydownTreeDict(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnSetHardOwner();
    afx_msg void OnMergeStyleChanged();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
		// data members
    AcDbObjectIdArray	m_dictObjIdList;    // "stack" of dictionary Object Ids
    AcDbObjectId        m_rootObjId;
    bool                m_isRoot;
    int                 m_curIndex;

		// helper functions
    HTREEITEM	addOneTreeItem(LPCTSTR name, const AcDbObjectId& objId, HTREEITEM parent);
    void        addOneDictionary(const AcDbObjectId& dictId, HTREEITEM parent);
	void		setDictInfoButtons(AcDbObject* obj);
    void        displayCurrent(int index);
    bool        renameCurrentItem(LPCTSTR oldName, LPCTSTR newName);
    void        deleteCurrentItem();

	AcDb::DuplicateRecordCloning	indexToDrc(int index) const;
	int								drcToIndex(AcDb::DuplicateRecordCloning drc) const;
};

#endif    // ARXDBGUITDCDICT_H
