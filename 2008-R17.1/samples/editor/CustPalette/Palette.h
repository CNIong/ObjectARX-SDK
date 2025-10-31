//
//
// (C) Copyright 2000-2006 by Autodesk, Inc. 
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


#pragma once

//-----------------------------------------------------------------------------
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxctl.h"
#include "aduiPalette.h"
#include "resource.h"


/////////////////////////////////////////////////////////////////////////////
// Custom Palette class

class CDataPalette : public CAdUiPalette 
{ 
	DECLARE_DYNCREATE(CDataPalette)
public:
	CDataPalette();
	virtual ~CDataPalette();

	// Brush to paint static control background color
	CBrush m_Brush;
	
	// Data items
	CString str[2];
	int integer[2];
	double real[2];

	// Controls in the palette
	CComboBox m_Combo;
	CAcUiStringEdit  m_StringEdit;
	CAcUiNumericEdit m_IntEdit;
	CAcUiNumericEdit m_RealEdit;
	// Static texts
	CStatic  m_TextLabel;
	CStatic  m_DataLabel;
	CStatic  m_StrLabel;
	CStatic  m_IntLabel;
	CStatic  m_RealLabel;

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
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate (LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy(); 
	afx_msg LRESULT OnCtlColorStatic(WPARAM wParam, LPARAM lParam);
	afx_msg void OnComboChange();
	afx_msg void OnStringChange();
	afx_msg void OnIntChange();
	afx_msg void OnRealChange();

private:
	// Load and save palette information
	void LoadPalette();
	void SavePalette();
};

