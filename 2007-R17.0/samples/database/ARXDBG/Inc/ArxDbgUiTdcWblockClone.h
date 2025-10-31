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

#ifndef ARXDBGUITDCWBLOCKCLONE_H
#define ARXDBGUITDCWBLOCKCLONE_H

#include "Res_ArxDbg.h"
#include "ArxDbgCloneSet.h"
#include "SdStrObjId.h"

/****************************************************************************
**
**	CLASS ArxDbgUiTdcWblockClone:
**
**	**jma
**
*************************************/

class ArxDbgUiTdcWblockClone : public CAcUiTabChildDialog {

public:
				ArxDbgUiTdcWblockClone();
    virtual		~ArxDbgUiTdcWblockClone()    {}

    //{{AFX_DATA(ArxDbgUiTdcWblockClone)
    enum { IDD = ARXDBG_TDC_WBLOCK };
	CListBox			m_lbSourceDb;
	CListBox			m_lbDestDb;
    CAcUiPickButton		m_pickPtButton;
	BOOL				m_doForceCopy;
	BOOL				m_saveAsDwg;
	int					m_puBlockDefIndex;
	CComboBox			m_puBlockDef;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdcWblockClone)
    public:
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    //}}AFX_VIRTUAL

protected:

    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcWblockClone)
    afx_msg void OnWblockObjects();
    afx_msg void OnWblockBlkDef();
    afx_msg void OnWblockAll();
    afx_msg void OnPickBasePt();
	afx_msg void OnSourceDatabaseChanged();
	afx_msg void OnDestDatabaseChanged();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	AcDbVoidPtrArray	m_dbPtrs;
	ArxDbgCloneSet&		m_cloneSet;
	AcGePoint3d			m_basePt;
	SdStrObjIdList		m_blockList;

        // helper functions
	void			setButtonModes();
	void			displayDbLists();
	void			fillBlockList();
	AcDbDatabase*	getSourceDb();
	AcDbDatabase*	getDestDb();
	void			doSaveOption(AcDbDatabase* tmpDb);
	void			doInsertOption(AcDbDatabase* tmpDb);
	void			divideCloneSet(const AcDbObjectIdArray& cloneSet,
                            AcDbObjectIdArray& nonEntSet,
                            AcDbObjectIdArray& okToCloneSet);
};

#endif    // ARXDBGUITDCWBLOCKCLONE_H
