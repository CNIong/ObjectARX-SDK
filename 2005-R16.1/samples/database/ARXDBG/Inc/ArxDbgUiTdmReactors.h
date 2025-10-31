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

#ifndef ARXDBGUITDMREACTORS_H
#define ARXDBGUITDMREACTORS_H

#include "Res_ArxDbg.h"

class ArxDbgUiTdcSysReactors;
class ArxDbgUiTdcTransientReactors;
class ArxDbgUiTdcPersistentReactors;
class ArxDbgTransientEntReactor;


/****************************************************************************
**
**	CLASS ArxDbgUiTdmReactors:
**
**	**jma
**
*************************************/

class ArxDbgUiTdmReactors : public CAcUiTabMainDialog {

public:
            ArxDbgUiTdmReactors(CWnd* pParent);
	virtual	~ArxDbgUiTdmReactors();

	void	attachEntTransientReactor(ArxDbgTransientEntReactor* entReactor);
	void	detachEntTransientReactor(ArxDbgTransientEntReactor* entReactor);

	void	attachEntPersistentReactor();
	void	detachEntPersistentReactor();

    //{{AFX_DATA(ArxDbgUiTdmReactors)
    enum { IDD = ARXDBG_TDM_REACTORS };
	CAdUiTab	m_tabCtrl;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdmReactors)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdmReactors)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	ArxDbgUiTdcSysReactors*			m_tdcSysReactors;
	ArxDbgUiTdcTransientReactors*	m_tdcTransientReactors;
	ArxDbgUiTdcPersistentReactors*	m_tdcPersistentReactors;

		// statics
public:
    static void cleanUpReactors();
	static bool	hasPersistentReactor(AcDbObject* obj, const AcDbObjectId& reactorId);

};

#endif // ARXDBGUITDMREACTORS_H

