//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#if !defined(AFX_CONTROLSDLG_H__EA061227_3F44_11D3_8D68_0060B0CDE437__INCLUDED_)
#define AFX_CONTROLSDLG_H__EA061227_3F44_11D3_8D68_0060B0CDE437__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ControlsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CControlsDlg dialog

class CControlsDlg : public CDialog
{
// Construction
public:
	CControlsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CControlsDlg)
	enum { IDD = IDD_CONTROLS };
	CEdit	mEdit;
	BOOL	mBlock;
	BOOL	mCleanUp;
	BOOL	mEntity;
	BOOL	mHandlePoints;
	BOOL	mHideTangents;
	BOOL	mIsoLines;
	BOOL	mProcessAll;
	BOOL	mProgress;
	BOOL	mProject;
	BOOL	mReuse;
	BOOL	mShowAll;
	BOOL	mSubentity;
	BOOL	mUnite;
	BOOL	mHonorInternals;
	BOOL	mMeshSilhouettes;
	//}}AFX_DATA
	int mnControls ;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CControlsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBlock();
	afx_msg void OnEntity();
	afx_msg void OnProcessall();
	afx_msg void OnProgress();
	afx_msg void OnProject();
	afx_msg void OnShowall();
	afx_msg void OnUnite();
	afx_msg void OnCleanup();
	afx_msg void OnHandlepoints();
	afx_msg void OnHidetangents();
	afx_msg void OnIsolines();
	afx_msg void OnReuse();
	afx_msg void OnSubentity();
	virtual void OnOK();
	afx_msg void OnHonorinternals();
	afx_msg void OnMeshsilhouettes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLSDLG_H__EA061227_3F44_11D3_8D68_0060B0CDE437__INCLUDED_)
