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
// DwgSetngTab1.cpp : implementation file
//

#include "stdafx.h"
#include "DwgSetngTab1.h"
#include "adscodes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDwgSetngTab1* gpTab1;

/////////////////////////////////////////////////////////////////////////////
// CDwgSetngTab1 dialog


CDwgSetngTab1::CDwgSetngTab1(CWnd* pParent /*=NULL*/)
	: CAcUiTabChildDialog(pParent)
{
	//{{AFX_DATA_INIT(CDwgSetngTab1)
	//}}AFX_DATA_INIT
}


void CDwgSetngTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDwgSetngTab1)
	DDX_Control(pDX, IDC_EDIT_XPT, m_ctrlXPtEdit);
	DDX_Control(pDX, IDC_EDIT_YPT, m_ctrlYPtEdit);
	DDX_Control(pDX, IDC_EDIT_ZPT, m_ctrlZPtEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDwgSetngTab1, CDialog)
	//{{AFX_MSG_MAP(CDwgSetngTab1)
	ON_EN_KILLFOCUS(IDC_EDIT_XPT, OnKillfocusEditXpt)
	ON_EN_KILLFOCUS(IDC_EDIT_YPT, OnKillfocusEditYpt)
	ON_EN_KILLFOCUS(IDC_EDIT_ZPT, OnKillfocusEditZpt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDwgSetngTab1 message handlers

BOOL CDwgSetngTab1::OnInitDialog() 
{
	CAcUiTabChildDialog::OnInitDialog();
	
    SetDirty();
	
	// Must be within a 100 unit cube centered about 0,0,0
	m_ctrlXPtEdit.SetRange(-50.0, 50.0);
	m_ctrlYPtEdit.SetRange(-50.0, 50.0);
	m_ctrlZPtEdit.SetRange(-50.0, 50.0);

	m_strXPt = "0.0";
	m_strYPt = "0.0";
	m_strZPt = "0.0";

	DisplayPoint();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDwgSetngTab1::PostNcDestroy() 
{

	gpTab1 = NULL;

	CAcUiTabExtension::PostNcDestroy();
}

// Utility functions
void CDwgSetngTab1::DisplayPoint() 
{
	m_ctrlXPtEdit.SetWindowText(m_strXPt);
	m_ctrlXPtEdit.Convert();

	m_ctrlYPtEdit.SetWindowText(m_strYPt);
	m_ctrlYPtEdit.Convert();

	m_ctrlZPtEdit.SetWindowText(m_strZPt);
	m_ctrlZPtEdit.Convert();
}

void CDwgSetngTab1::OnKillfocusEditXpt() 
{
	// Get and update text the user typed in.
	m_ctrlXPtEdit.Convert();
	m_ctrlXPtEdit.GetWindowText(m_strXPt);

	if(!ValidatePoint())
	{
		m_ctrlXPtEdit.SetFocus();
	}
	
}

void CDwgSetngTab1::OnKillfocusEditYpt() 
{
	// Get and update text the user typed in.
	m_ctrlYPtEdit.Convert();
	m_ctrlYPtEdit.GetWindowText(m_strYPt);

	if(!ValidatePoint())
	{
		m_ctrlYPtEdit.SetFocus();
	}

	
}

void CDwgSetngTab1::OnKillfocusEditZpt() 
{
	// Get and update text the user typed in.
	m_ctrlZPtEdit.Convert();
	m_ctrlZPtEdit.GetWindowText(m_strZPt);
	if(!ValidatePoint())
	{
		m_ctrlZPtEdit.SetFocus();
	}
	
}


bool CDwgSetngTab1::ValidatePoint() 
{
	if (!m_ctrlXPtEdit.Validate())
		return false;

	if (!m_ctrlYPtEdit.Validate())
		return false;

	if (!m_ctrlZPtEdit.Validate())
		return false;

	return true;
}


void CDwgSetngTab1::OnMainDialogOK()
// This function is called when the main dialog OK button is pressed.
{
	::AfxMessageBox("My Tab1 notified that the main dialog OK button was pressed");
}

void CDwgSetngTab1::OnMainDialogCancel()
// This function is called when the main dialog CANCEL button is pressed.
{
    ::AfxMessageBox("My Tab1 notified that the main dialog CANCEL button was pressed");
}

BOOL CDwgSetngTab1::OnMainDialogHelp()
// This function is called when the main dialog HELP button is pressed
// and this is the active tab.
{
    ::AfxMessageBox("My Tab1 notified that the main dialog HELP button was pressed");

    // Return TRUE if handled.
    return TRUE;
}
