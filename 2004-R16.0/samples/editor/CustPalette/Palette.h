//
//
// (C) Copyright 2000-2002 by Autodesk, Inc. 
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


//-----------------------------------------------------------------------------
#if !defined(ARX__PALETTE)
#define ARX__PALETTE

//-----------------------------------------------------------------------------
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxctl.h"
#include "aduiPalette.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CPicClip wrapper class for the PicClip ActiveX control

class CPicClip : public CWnd
{
protected:
	DECLARE_DYNCREATE(CPicClip)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x27395f85, 0xc0c, 0x101b, { 0xa3, 0xc9, 0x8, 0x0, 0x2b, 0x2f, 0x49, 0xfb } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
	pPersist, bStorage, bstrLicKey); }

	// Operations
public:
	void SetPicture(LPDISPATCH newValue);
};

/////////////////////////////////////////////////////////////////////////////
// Custom Palette class

class CMyPalette : public CAdUiPalette 
{ 
	DECLARE_DYNCREATE(CMyPalette)
public:
	CMyPalette();
	virtual ~CMyPalette();

	// Brush to paint control's background color
	CBrush *m_Brush;

	// Data items
	CString str[2];
	int integer[2];
	double real[2];

	// Controls in the palette
	//CAdUiComboBox *pCombo;
	CComboBox *pCombo;
	CAcUiStringEdit *pStringEdit;
	CAcUiNumericEdit *pIntEdit;
	CAcUiNumericEdit *pRealEdit;
	// Static texts
	CStatic *pTextLabel;
	CStatic *pDataLabel;
	CStatic  *pStrLabel;
	CStatic  *pIntLabel;
	CStatic  *pRealLabel;

	public:
    // Load the data from xml.
    virtual BOOL Load(IUnknown* pUnk);
    // Save the data to xml.
    virtual BOOL Save(IUnknown* pUnk);
    // Called by the palette set when the palette is made active
    virtual void OnSetActive();
	//Called by AutoCAD to steal focus from the palette
	virtual bool CanFrameworkTakeFocus();

protected:
    // Default "SetCursor" implementation
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnComboChange();
	afx_msg void OnStringChange();
	afx_msg void OnIntChange();
	afx_msg void OnRealChange();

	// Method to add/delete MFC controls to palette
	void addControls();
	void deleteControls();
	
private:
	//Utility functions to add and get the child node from the parent XML-DOM node
	BOOL AddChildNode(MSXML::IXMLDOMNode* pNode, LPCTSTR pszChildNodeName, short nNodeType, MSXML::IXMLDOMNode** ppChild);
	BOOL GetChildNode(MSXML::IXMLDOMNode* pNode, LPCTSTR pszNodeName, MSXML::IXMLDOMNode** ppChild);

	// ActiveX control
	CPicClip mClipCtrl;
	CPictureHolder pictholder;
	CBitmap bitmap;
};


#endif //----- !defined(ARX__PALETTE)
