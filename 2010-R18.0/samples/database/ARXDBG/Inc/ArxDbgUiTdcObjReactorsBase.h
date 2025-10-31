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

#ifndef ARXDBGUITDCOBJREACTORSBASE_H
#define ARXDBGUITDCOBJREACTORSBASE_H

#include "Res_ArxDbg.h"

/****************************************************************************
**
**  CLASS ArxDbgUiTdcObjReactorsBase:
**
**  **jma
**
*************************************/

class ArxDbgUiTdcObjReactorsBase : public CAcUiTabChildDialog {

public:
                    ArxDbgUiTdcObjReactorsBase();
    virtual         ~ArxDbgUiTdcObjReactorsBase()    {}

    //{{AFX_DATA(ArxDbgUiTdcObjReactorsBase)
    CAcUiSelectButton	m_attachEntButton;
    CAcUiSelectButton	m_detachEntButton;
    CAcUiBitmapButton	m_detachSelectedEntsButton;
    CAcUiBitmapButton	m_detachSelectedObjsButton;
	CListBox			m_lbObjList;
	CListBox			m_lbEntList;
    CEdit				m_ebHandle;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdcTransientReactors)
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcTransientReactors)
    afx_msg void OnObjAttach();
    afx_msg void OnEntAttach();
    afx_msg void OnEntDetach();
    afx_msg void OnEntDetachSelected();
    afx_msg void OnObjDetachSelected();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

	virtual	void	getAttachedObjects(AcDbObjectIdArray& objIds)  = 0;
	virtual void	getAttachedEntities(AcDbObjectIdArray& objIds) = 0;

	virtual void	attachObjReactors(const AcDbObjectIdArray& objIds) = 0;
	virtual void	attachEntReactors() = 0;
	virtual void	detachEntReactors() = 0;
	virtual void	detachSelectedEnts(const AcDbObjectIdArray& objIds) = 0;
	virtual void	detachSelectedObjs(const AcDbObjectIdArray& objIds) = 0;

private:
		// data members
	AcDbObjectIdArray	m_objsAttached;
	AcDbObjectIdArray	m_entsAttached;

		// helper functions
	void	displayObjList();
	void	displayEntList();
	void	setButtonModes();

public:
    static void doStateDbox(const AcDbObject* obj, LPCTSTR dboxTitle = NULL);
    static void doStateDbox(const AcDbObjectId& objId, LPCTSTR dboxTitle = NULL);
};

#endif // ARXDBGUITDCOBJREACTORSBASE_H

