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

#ifndef ARXDBGUITDMTRANSDBCLONES_H
#define ARXDBGUITDMTRANSDBCLONES_H

#include "Res_ArxDbg.h"
#include "ArxDbgCloneSet.h"

class ArxDbgUiTdcCloneSet;
class ArxDbgUiTdcWblockClone;
class ArxDbgUiTdcInsert;


/****************************************************************************
**
**	CLASS ArxDbgUiTdmTransDbClones:
**
**	**jma
**
*************************************/

class ArxDbgUiTdmTransDbClones : public CAcUiTabMainDialog {

public:
            ArxDbgUiTdmTransDbClones(CWnd* parent, const TCHAR* winTitle = NULL);
	virtual	~ArxDbgUiTdmTransDbClones();

	void	addToCloneSet(ArxDbgCloneSet& cloneSet);	// ugly hacks since child dialogs can't call BeginEditorCommand()
	void	getBasePoint(AcGePoint3d& basePt);

    //{{AFX_DATA(ArxDbgUiTdmTransDbClones)
    enum { IDD = ARXDBG_TDM_TRANSDB_CLONES };
	CAdUiTab	m_tabCtrl;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdmTransDbClones)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdmTransDbClones)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	CString					m_winTitle;
	ArxDbgUiTdcCloneSet*	m_tdcCloneSet;
	ArxDbgUiTdcWblockClone*	m_tdcWblockClone;
	ArxDbgUiTdcInsert*		m_tdcInsert;
};

#endif // ARXDBGUITDMTRANSDBCLONES_H

