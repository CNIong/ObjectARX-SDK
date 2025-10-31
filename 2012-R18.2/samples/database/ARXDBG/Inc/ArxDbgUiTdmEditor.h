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

