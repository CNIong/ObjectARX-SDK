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
