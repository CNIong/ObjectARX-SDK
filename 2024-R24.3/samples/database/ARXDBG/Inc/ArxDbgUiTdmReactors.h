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

