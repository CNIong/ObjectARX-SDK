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
#if !defined(AFX_WHIPMDICHILDWND_H__CF06E003_373E_11D2_B730_444553540001__INCLUDED_)
#define AFX_WHIPMDICHILDWND_H__CF06E003_373E_11D2_B730_444553540001__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WhipMdiChildWnd.h : header file
//

#include "whip.h"
/////////////////////////////////////////////////////////////////////////////
// CWhipMdiChildWnd frame

class CWhipMdiChildWnd : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CWhipMdiChildWnd)
public:
	CWhipMdiChildWnd(); 
	virtual ~CWhipMdiChildWnd();
// Attributes
private:

	CWhip* m_pWhip;
	CString m_csDwfFileName;
// Operations
public:
	void SetDwfFileName(CString &dwfName)
	{
		m_csDwfFileName = dwfName;
	}
	void ResetStreamName(CString &dwfName)
	{
		m_csDwfFileName = dwfName;
		m_pWhip->SetStreamName(m_csDwfFileName);
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWhipMdiChildWnd)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, const RECT& rect = rectDefault, CMDIFrameWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWhipMdiChildWnd)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WHIPMDICHILDWND_H__CF06E003_373E_11D2_B730_444553540001__INCLUDED_)
