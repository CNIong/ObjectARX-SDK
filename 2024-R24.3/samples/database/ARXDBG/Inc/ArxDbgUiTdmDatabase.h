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

#ifndef ARXDBGUITDMDATABASE_H
#define ARXDBGUITDMDATABASE_H

#include "Res_ArxDbg.h"

class ArxDbgUiTdcSymTbl;
class ArxDbgUiTdcDict;
class ArxDbgUiTdcDatabase;


/****************************************************************************
**
**	CLASS ArxDbgUiTdmDatabase:
**
**	**jma
**
*************************************/

class ArxDbgUiTdmDatabase : public CAcUiTabMainDialog {

public:
            ArxDbgUiTdmDatabase(AcDbDatabase* db, CWnd* parent, const TCHAR* winTitle = NULL);
			ArxDbgUiTdmDatabase(const AcDbObjectId& dictId, CWnd* parent, const TCHAR* winTitle = NULL);	// when you just want page for extension dict
	virtual	~ArxDbgUiTdmDatabase();

    //{{AFX_DATA(ArxDbgUiTdmDatabase)
    enum { IDD = ARXDBG_TDM_DATABASE };
	CAdUiTab	m_tabCtrl;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdmDatabase)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdmDatabase)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	AcDbDatabase*			m_db;
	CString					m_winTitle;
	ArxDbgUiTdcSymTbl*		m_tdcSymTbl;
	ArxDbgUiTdcDict*		m_tdcDicts;
	ArxDbgUiTdcDatabase*	m_tdcDb;
};

#endif // ARXDBGUITDMDATABASE_H

