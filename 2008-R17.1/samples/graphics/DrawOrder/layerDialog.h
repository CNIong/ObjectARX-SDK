//
//
// (C) Copyright 2002-2006 by Autodesk, Inc. 
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
// layerDialog.h: declearation file of layerDialog


#pragma once
#include "afxwin.h"
#include "resource.h"
#include "sorttab.h"

// layerDialog dialog

class layerDialog : public CDialog
{
	DECLARE_DYNAMIC(layerDialog)

public:
	layerDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~layerDialog();
	bool displayLayerOrder(AcDbObjectIdArray &layers, CUIntArray* iRepeats);
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedButtonEntorder();
	afx_msg void OnBnClickedButtonLayerorder();
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnBnClickedButtonok();
	afx_msg void OnLbnSelchangeLayerlist();
	BOOL PreTranslateMessage(MSG* pMsg);
// Dialog Data
	enum { IDD = IDD_LAYERDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	CToolTipCtrl m_tooltipCtrl;
	DECLARE_MESSAGE_MAP()
	
private:
	bool refreshList(void);
	CDragListBox m_layerList;
	CButton m_entOrderBtn;
	CButton m_layerOrderBtn;
	


public:
	void ApplyLayerOrder(void);
};
