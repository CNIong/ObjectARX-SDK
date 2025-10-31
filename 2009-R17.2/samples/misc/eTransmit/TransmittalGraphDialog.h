//
//
// (C) Copyright 2003-2006 by Autodesk, Inc. 
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
//-----------------------------------------------------------------------------
#if !defined(ARX__TRANSMITTALGRAPHDIALOG_H__20030915_151839)
#define ARX__TRANSMITTALGRAPHDIALOG_H__20030915_151839

//-----------------------------------------------------------------------------
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//-----------------------------------------------------------------------------
class CTransmittalGraphDialog : public CAcUiDialog {
	DECLARE_DYNAMIC (CTransmittalGraphDialog)

public:
	CTransmittalGraphDialog (ITransmittalFile *graphRoot, CWnd* pParent =NULL, HINSTANCE hInstance =NULL);

	//{{AFX_DATA(CTransmittalGraphDialog)
	enum { IDD = IDD_TRANSMITTAL_GRAPH };
	CTreeCtrl	m_treeGraph;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTransmittalGraphDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// recursively tranverses through the ITransmittalFile graph
	HRESULT traverseTransmittalDependents (HTREEITEM treeRoot, ITransmittalFile *graphRoot);
protected:
	//{{AFX_MSG(CTransmittalGraphDialog)
	afx_msg BOOL OnInitDialog();
	afx_msg LRESULT OnAcadKeepFocus(WPARAM, LPARAM);
	afx_msg void OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	// root graph node point for ITransmittalFile
	ITransmittalFile *m_graphRoot;
	// to hold image list for a few treecontrol images
	CImageList m_imageList;

	DECLARE_MESSAGE_MAP()
} ;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //----- !defined(ARX__TRANSMITTALGRAPHDIALOG_H__20030915_151839)
