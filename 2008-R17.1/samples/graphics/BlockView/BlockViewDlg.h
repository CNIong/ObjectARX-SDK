//
// (C) Copyright 2002-2007 by Autodesk, Inc. 
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

#if !defined(AFX_TESTDLG_H__7DC11027_C827_11D2_B89C_080009DCA551__INCLUDED_)
#define AFX_TESTDLG_H__7DC11027_C827_11D2_B89C_080009DCA551__INCLUDED_

#include "GsPreviewCtrl.h"	// Added by ClassView
#include "resource.h"
#include "afxwin.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BlockViewDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBlockViewDlg dialog

class CBlockViewDlg : public CAcUiDialog
{
// Construction
public:
	CBlockViewDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBlockViewDlg)
	enum { IDD = IDD_BLOCKVIEW };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlockViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBlockViewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddentity();
	afx_msg void OnAddtempentity();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedRemapcolors();
	afx_msg void OnBnClickedStandardcolors();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CGsPreviewCtrl mPreviewCtrl;
	AcDbDatabase *mCurrentDwg;

	//////////////////////////////////////////////////////////////////////////////
	// takes a drawing and updates the GsView with it
	Acad::ErrorStatus InitDrawingControl (AcDbDatabase *pDb, const TCHAR *space = ACDB_MODEL_SPACE);
	// resets the view to the passed AcDbDatabase
	// util function to toggle the tick for a specific menu item
	bool toggleCheckMenuItem(UINT resId);
	// util functions for setting the tick for a specific menu item
	void setMenuCheck(UINT resId, UINT nCheck=MF_CHECKED);
	void setMenuUnCheck(UINT resId);
	AcDbObjectId CBlockViewDlg::setVisualStyleCurrent(ACHAR *name);
	const ACHAR* getVisualStyleLocalName(AcDbObjectId vsId);

	// view mode of the AcGsView
	CComboBox m_viewMode;
  void InitVisualStyleCombo();

	afx_msg void OnCbnSelchangeViewmode();
	afx_msg void OnFileOutput();
	afx_msg void OnFileAcGsConfig();
	afx_msg void OnFileOpen();
	afx_msg void OnShowlinetypes();
	afx_msg void OnShowSectioning();
	afx_msg void OnRenderertypeKdefault();
	afx_msg void OnRenderertypeKsoftware();
	afx_msg void OnRenderertypeKsoftwareNewViewsOnly();
	afx_msg void OnRenderertypeKfullRender();
	afx_msg void OnRenderertypeKselectionRender();
	afx_msg void OnZoomWindow();
	afx_msg void OnZoomExtents();
public:
  afx_msg void OnSettingsVisualstyle();
  AcGeMatrix3d m_viewMatrix;

  // - take into account previous temporary entities
  AcDbExtents m_tempExt;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__7DC11027_C827_11D2_B89C_080009DCA551__INCLUDED_)
