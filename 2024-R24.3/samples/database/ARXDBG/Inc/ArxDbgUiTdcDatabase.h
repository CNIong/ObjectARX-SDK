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

#ifndef ARXDBGUITDCDATABASE_H
#define ARXDBGUITDCDATABASE_H

#include "ArxDbgUiTdcDbObjectBase.h"


/****************************************************************************
**
**	CLASS ArxDbgUiTdcDatabase:
**
**	**jma
**
*************************************/

class ArxDbgUiTdcDatabase : public ArxDbgUiTdcRxObjectBase {

public:
				ArxDbgUiTdcDatabase(AcDbDatabase* db);
    virtual		~ArxDbgUiTdcDatabase() {}

    //{{AFX_DATA(ArxDbgUiTdcDatabase)
    enum { IDD = ARXDBG_TDC_DBMISC };
    CStatic     m_frPreview;
    CListCtrl	m_dataList;
    //}}AFX_DATA


    // ClassWizard generate virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdcDatabase)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcDatabase)
    afx_msg void OnPaint();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
		// data members
    AcDbDatabase*	m_db;

		// helper functions
	void		display();

};

#endif    // ARXDBGUITDCDATABASE_H
