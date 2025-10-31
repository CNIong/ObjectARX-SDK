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

#ifndef ARXDBGUITDCIDMAP_H
#define ARXDBGUITDCIDMAP_H

#include "ArxDbgUiTdcRxObjectBase.h"

/****************************************************************************
**
**	CLASS ArxDbgUiTdcIdMap:
**
**	**jma
**
*************************************/

class ArxDbgUiTdcIdMap : public ArxDbgUiTdcRxObjectBase {

public:
				ArxDbgUiTdcIdMap(AcDbIdMapping* idMap);
    virtual		~ArxDbgUiTdcIdMap()    {}

    //{{AFX_DATA(ArxDbgUiTdcIdMap)
    enum { IDD = ARXDBG_TDC_IDMAP };
    CStatic		m_txtErased;
    CListCtrl	m_dataList;
    CListCtrl   m_lcObjList;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdcIdMap)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcIdMap)
    virtual BOOL OnInitDialog();
    virtual void OnMainDialogOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	AcDbIdMapping*		m_idMap;
    AcDbObjectIdArray	m_objIds;

		// helper functions
    void        displayCurrent();
	void		displayMapItems();
	void		buildMapItemColumns();

};

#endif    // ARXDBGUITDCIDMAP_H
