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

#ifndef ARXDBGUITDCRXOBJECTBASE_H
#define ARXDBGUITDCRXOBJECTBASE_H

#include "Res_ArxDbg.h"

/****************************************************************************
**
**	CLASS ArxDbgUiTdcRxObjectBase:
**
**	**jma
**
*************************************/

class ArxDbgUiTdcRxObjectBase : public CAcUiTabChildDialog {

public:
    virtual    ~ArxDbgUiTdcRxObjectBase()    {}

    //{{AFX_DATA(ArxDbgUiTdcRxObjectBase)
    //}}AFX_DATA


    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdcRxObjectBase)
    public:
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
            ArxDbgUiTdcRxObjectBase();    // can only be constructed by derived classes

    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcRxObjectBase)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

        // data members
    CStringList		m_fieldStrList;
    CStringList		m_valueStrList;
	CListCtrl*		m_dataListCtrl;	// pointer from derived dialog

        // helper functions
	void		buildColumns(CListCtrl& dataList);
	void		drawPropsList(CListCtrl& dataList);
    void        addToDataList(LPCTSTR field, LPCTSTR value, bool addQuotes = false);
    void        addSeperatorLine(LPCTSTR className);
};

#endif    // ARXDBGUITDCRXOBJECTBASE_H
