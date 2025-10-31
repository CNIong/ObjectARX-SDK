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
/////////////////////////////////////////////////////////////////////////////

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
