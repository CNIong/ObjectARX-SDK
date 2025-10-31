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

#ifndef ARXDBGUITDMREFERENCES_H
#define ARXDBGUITDMREFERENCES_H

#include "Res_ArxDbg.h"

class ArxDbgUiTdcReferences;


/****************************************************************************
**
**	CLASS ArxDbgUiTdmReferences:
**
**	**jma
**
*************************************/

class ArxDbgUiTdmReferences : public CAcUiTabMainDialog {

public:
            ArxDbgUiTdmReferences(const AcDbObjectIdArray& hardPointerIds,
								  const AcDbObjectIdArray& softPointerIds,
								  const AcDbObjectIdArray& hardOwnershipIds,
								  const AcDbObjectIdArray& softOwnershipIds,
								  CWnd* parent, const TCHAR* winTitle = NULL);
	virtual	~ArxDbgUiTdmReferences();

    //{{AFX_DATA(ArxDbgUiTdmReferences)
    enum { IDD = ARXDBG_TDM_ENTS };
	CAdUiTab	m_tabCtrl;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdmReferences)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdmReferences)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	CString					m_winTitle;
	ArxDbgUiTdcReferences*	m_tdcRefs;
};

#endif // ARXDBGUITDMREFERENCES_H

