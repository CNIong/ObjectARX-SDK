//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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

#ifndef ARXDBGUITDMIDMAP_H
#define ARXDBGUITDMIDMAP_H

#include "Res_ArxDbg.h"

class ArxDbgUiTdcIdMap;


/****************************************************************************
**
**	CLASS ArxDbgUiTdmIdMap:
**
**	**jma
**
*************************************/

class ArxDbgUiTdmIdMap : public CAcUiTabMainDialog {

public:
            ArxDbgUiTdmIdMap(AcDbIdMapping* idMap, CWnd* parent, const TCHAR* winTitle = NULL);
	virtual	~ArxDbgUiTdmIdMap();

    //{{AFX_DATA(ArxDbgUiTdmIdMap)
    enum { IDD = ARXDBG_TDM_IDMAP };
	CAdUiTab	m_tabCtrl;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdmIdMap)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdmIdMap)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	CString				m_winTitle;
	ArxDbgUiTdcIdMap*	m_tdcIdMap;
};

#endif // ARXDBGUITDMIDMAP_H

