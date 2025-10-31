//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef ARXDBGUIDLGOBJECTID_H
#define ARXDBGUIDLGOBJECTID_H

#include "Res_ArxDbg.h"

/****************************************************************************
**
**	CLASS ArxDbgUiDlgObjectId:
**
**	**jma
**
*************************************/

class ArxDbgUiDlgObjectId : public CAcUiDialog {

public:
				ArxDbgUiDlgObjectId(const AcDbObjectId& objId, CWnd* parent);
    virtual		~ArxDbgUiDlgObjectId()    {}

    //{{AFX_DATA(ArxDbgUiDlgObjectId)
    enum { IDD = ARXDBG_DLG_OBJECT_ID_INFO };
    CListCtrl    m_dataList;
    //}}AFX_DATA


    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiDlgObjectId)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    void    display();
    void    buildColumns();

    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiDlgObjectId)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
		// data members
    AcDbObjectId    m_objId;
    CStringList		m_fieldStrList;
    CStringList		m_valueStrList;

		// helper functions
	void		drawPropsList();
    void        addToDataList(LPCTSTR field, LPCTSTR value, bool addQuotes = false);
};


#endif	//ARXDBGUIDLGOBJECTID_H
