//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#ifndef ARXDBGUITDCOPTIONS_H
#define ARXDBGUITDCOPTIONS_H

#include "Res_ArxDbg.h"

/****************************************************************************
**
**  CLASS ArxDbgUiTdcOptions:
**
**  **jma
**
*************************************/

class ArxDbgUiTdcOptions : public CAcUiTabChildDialog {

public:
		ArxDbgUiTdcOptions(CWnd* pParent = NULL);

	//{{AFX_DATA(ArxDbgUiTdcOptions)
	enum { IDD = ARXDBG_TDC_OPTIONS };
	BOOL	m_showDwgFilerMsgs;
	BOOL	m_showWblockCloneDetails;
	BOOL	m_showDeepCloneDetails;
	BOOL	m_doDictInsertByHand;
	//}}AFX_DATA

public:
    virtual void OnMainDialogOK();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ArxDbgUiTdcOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	// Generated message map functions
	//{{AFX_MSG(ArxDbgUiTdcOptions)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // ARXDBGUITDCOPTIONS_H
