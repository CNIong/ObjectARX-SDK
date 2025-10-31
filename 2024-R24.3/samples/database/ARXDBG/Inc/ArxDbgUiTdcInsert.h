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

#ifndef ARXDBGUITDCINSERT_H
#define ARXDBGUITDCINSERT_H

#include "Res_ArxDbg.h"
#include "ArxDbgCloneSet.h"
#include "SdStrObjId.h"

/****************************************************************************
**
**	CLASS ArxDbgUiTdcInsert:
**
**	**jma
**
*************************************/

class ArxDbgUiTdcInsert : public CAcUiTabChildDialog {

public:
				ArxDbgUiTdcInsert();
    virtual		~ArxDbgUiTdcInsert();

    //{{AFX_DATA(ArxDbgUiTdcInsert)
    enum { IDD = ARXDBG_TDC_INSERT };
	CListBox			m_lbSourceDb;
	CListBox			m_lbDestDb;
	BOOL				m_preserveOriginalDb;
	BOOL				m_saveAsDwg;
	CComboBox			m_puBlockDef;
	CEdit				m_ebDestName1;
	CEdit				m_ebDestName2;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdcInsert)
    public:
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    //}}AFX_VIRTUAL

protected:

    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcInsert)
    afx_msg void OnInsertDb();
    afx_msg void OnInsertBlkDef();
    afx_msg void OnTransferBlkDef();
	afx_msg void OnSourceDatabaseChanged();
	afx_msg void OnDestDatabaseChanged();
	afx_msg void OnAddExternalDwg();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
    AcArray<AcDbDatabase*>	m_dbPtrs;
	CStringArray		m_extDwgNames;
	SdStrObjIdList		m_blockList;

        // helper functions
	void			setButtonModes();
	void			displayDbLists();
	void			fillBlockList();
	AcDbDatabase*	getSourceDb(bool& isExternal);
	AcDbDatabase*	getDestDb();
	void			doSaveOption(AcDbDatabase* tmpDb);
	bool			hasDwgFile(CStringArray& dwgFiles, const CString& str);
	void			reloadRaidedExternalDwg(AcDbDatabase* db);
};

#endif    // ARXDBGUITDCINSERT_H
