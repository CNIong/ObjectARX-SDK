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

#ifndef ARXDBGUITDCOBJECTS_H
#define ARXDBGUITDCOBJECTS_H

#include "ArxDbgUiTdcDbObjectBase.h"

/****************************************************************************
**
**	CLASS ArxDbgUiTdcObjects:
**
**	**jma
**
*************************************/

class ArxDbgUiTdcObjects : public ArxDbgUiTdcDbObjectBase {

public:
				ArxDbgUiTdcObjects(const AcDbObjectIdArray& objList);
    virtual		~ArxDbgUiTdcObjects()    {}

    //{{AFX_DATA(ArxDbgUiTdcObjects)
    enum { IDD = ARXDBG_TDC_OBJS };
    CStatic		m_txtErased;
    CListCtrl	m_dataList;
    CListBox   	m_lbObjList;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdcObjects)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcObjects)
    virtual BOOL OnInitDialog();
	virtual void OnSelchangedObjs();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
    const AcDbObjectIdArray&	m_objList;

		// helper functions
    void        displayCurrent(int index);

};

#endif    // ARXDBGUITDCOBJECTS_H
