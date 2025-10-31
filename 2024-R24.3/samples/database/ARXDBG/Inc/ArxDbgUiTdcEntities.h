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

#ifndef ARXDBGUITDCENTITIES_H
#define ARXDBGUITDCENTITIES_H

#include "ArxDbgUiTdcDbObjectBase.h"

/****************************************************************************
**
**	CLASS ArxDbgUiTdcEntities:
**
**	**jma
**
*************************************/

class ArxDbgUiTdcEntities : public ArxDbgUiTdcDbObjectBase {

public:
				ArxDbgUiTdcEntities(const AcDbObjectIdArray& objList,
                                bool fromBlkDef = false);
    virtual		~ArxDbgUiTdcEntities()    {}

    //{{AFX_DATA(ArxDbgUiTdcEntities)
    enum { IDD = ARXDBG_TDC_ENTS };
    CStatic		m_txtErased;
    CListCtrl	m_dataList;
    CTreeCtrl	m_entTree;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdcEntities)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcEntities)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangedEnts(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
    const AcDbObjectIdArray&	m_origEnts;
    AcDbObjectIdArray			m_treeObjIdList;		// tblentry Object Ids
    bool						m_isBlkDef;

		// helper functions
    HTREEITEM	addOneTreeItem(LPCTSTR name, const AcDbObject* obj, HTREEITEM parent, bool sort = false);
    void        addSubentitiesToTree(const AcDbEntity* ent, HTREEITEM parent);

    void        collectAttributes(const AcDbBlockReference* blkRef, AcDbObjectIdArray& subEnts);
    void        collectVertices(const AcDbEntity* ent, AcDbObjectIdArray& subEnts);

    void        displayCurrent(int index);

};


#endif    // ARXDBGUITDCENTITIES_H
