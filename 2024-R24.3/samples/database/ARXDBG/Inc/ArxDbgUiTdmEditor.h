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

#ifndef ARXDBGUITDMEDITOR_H
#define ARXDBGUITDMEDITOR_H

#include "Res_ArxDbg.h"

class ArxDbgUiTdcDocs;
class ArxDbgUiTdcClasses;
class ArxDbgUiTdcCmds;
class ArxDbgUiTdcHostAppSrv;

/****************************************************************************
**
**	CLASS ArxDbgUiTdmEditor:
**
**	**jma
**
*************************************/

class ArxDbgUiTdmEditor : public CAcUiTabMainDialog {

public:
            ArxDbgUiTdmEditor(CWnd* pParent);
            ArxDbgUiTdmEditor(CWnd* pParent, AcApDocument* doc); // when only want to see the Doc's page
	virtual	~ArxDbgUiTdmEditor();

    //{{AFX_DATA(ArxDbgUiTdmEditor)
    enum { IDD = ARXDBG_TDM_EDITOR };
	CAdUiTab	m_tabCtrl;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdmEditor)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdmEditor)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	ArxDbgUiTdcDocs*		m_tdcDocs;
	ArxDbgUiTdcClasses*		m_tdcClasses;
	ArxDbgUiTdcCmds*		m_tdcCommands;
	ArxDbgUiTdcHostAppSrv*	m_tdcHostAppSrv;
};

#endif // ARXDBGUITDMEDITOR_H

