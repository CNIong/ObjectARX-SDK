// (C) Copyright 1993-2006 by Autodesk, Inc.
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

#ifndef __AFXWIN_H__
	#error include _T('stdafx.h') before including this file for PCH
#endif

#include <actrans.h>
#include <afxcmn.h>
#include <afxext.h>
#include <adui.h>
#include <acui.h>


#include "resource.h"
#include "..\CurveText_DB\CurveText.h"

/////////////////////////////////////////////////////////////////////////////
// CCurveTextDia dialog

class CCurveTextDia : public CAcUiDialog
{
public:
	CCurveTextDia(CWnd* pParent = NULL);
	void setPoint(bool isStartPoint);
	AsdkCurveText* getCurveText(AcDb::OpenMode mode);
	AsdkCurveText* getCurveText(AcDbObjectId oId, AcDb::OpenMode mode);

	// Dialog Data
	//{{AFX_DATA(CCurveTextDia)
	enum { IDD = IDD_POLYTEXT };
	CButton				m_resetPoint_button;
	CButton				m_endPoint_Button;
	CButton				m_startPoint_button;
	CButton				m_position_button;
	CAcUiNumericEdit	m_edit_size;
	CButton				m_Fit_Button;
	CAcUiStringEdit		m_editString;
	CButton				m_reverse_button;
	CButton				m_repeat_button;
	CButton				m_showText_button;
	CButton				m_show_button;
	CAcUiNumericEdit	m_editSpace;
	CComboBox			m_combo;
	double				m_size;
	CString				m_string;
	BOOL				m_showCurve;
	BOOL				m_showText;
	double				m_startDist;
	double				m_length;
	double				m_space;
	BOOL				m_fit;
	CString				m_style;
	int					m_position;
	BOOL				m_dynamic;
	BOOL				m_repeat;
	BOOL				m_reverse;
	//}}AFX_DATA

	AcDbObjectId m_styleId;
	AcDbObjectIdArray curveTextIdArray;
	AcTransaction *pTrans;
	void updatePosition();
	void copyGlobalState();
	void updateGlobalState();

protected:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurveTextDia)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CCurveTextDia)
	afx_msg void OnStartPoint();
	afx_msg void OnEndPoint();
	virtual BOOL OnInitDialog();
	afx_msg void OnResetPoint();
	afx_msg void OnCheckFit();
	afx_msg void OnAbove();
	afx_msg void OnBelow();
	afx_msg void OnCheckShow();
	afx_msg void OnCheckShowtext();
	afx_msg void OnMiddle();
	afx_msg void OnChangeEditSize();
	afx_msg void OnChangeEditString();
	afx_msg void OnSelchangeComboStyle();
	afx_msg void OnCheckDynamic();
	afx_msg void OnChangeEditSpace();
	afx_msg void OnCheckRepeattext();
	afx_msg void OnCheckReverse();
	afx_msg void OnKillfocusEditSize();
	//}}AFX_MSG

	void updateObject();

	DECLARE_MESSAGE_MAP()
};
