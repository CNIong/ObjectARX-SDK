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

#ifndef ARXDBGUITDCDOCS_H
#define ARXDBGUITDCDOCS_H

#include "Res_ArxDbg.h"
#include "ArxDbgUiTdcRxObjectBase.h"

/****************************************************************************
**
**	CLASS ArxDbgUiTdcDocs:
**
**	**jma
**
*************************************/

class ArxDbgUiTdcDocs : public ArxDbgUiTdcRxObjectBase {

public:
				ArxDbgUiTdcDocs();
				ArxDbgUiTdcDocs(AcApDocument* doc);	// just show a specific document
    virtual		~ArxDbgUiTdcDocs()    {}

    //{{AFX_DATA(ArxDbgUiTdcDocs)
    enum { IDD = ARXDBG_TDC_DOCS };
    CListBox	m_docList;
    CListCtrl	m_dataList;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdcDocs)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcDocs)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangeDocs();
    afx_msg void OnDatabase();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
		// data members
    AcDbVoidPtrArray	m_docPtrs;
    int                 m_curIndex;

		// helper functions
	void		fillListBox(int defIndex);
    void        displayCurrent(int index);
};

#endif    // ARXDBGUITDCDOCS_H
