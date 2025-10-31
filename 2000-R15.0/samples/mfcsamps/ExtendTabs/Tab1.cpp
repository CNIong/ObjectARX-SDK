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
// Tab1.cpp : implementation file
//

#include "stdafx.h"
#include "Tab1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTab1 dialog


CTab1::CTab1(CWnd* pParent /*=NULL*/)
	: CAcUiTabChildDialog(pParent)
{
	//{{AFX_DATA_INIT(CTab1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTab1::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabChildDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTab1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTab1, CAcUiTabChildDialog)
	//{{AFX_MSG_MAP(CTab1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTab1 message handlers

BOOL CTab1::OnInitDialog() 
{
	CAcUiTabChildDialog::OnInitDialog();
	
	
    SetDirty();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTab1::OnOK()
{
    CAcUiTabChildDialog::OnOK();
}

void CTab1::OnMainDialogOK()
// This function is called when the main dialog OK button is pressed.
{
	::AfxMessageBox("Tab1 notified that the main dialog OK button was pressed");
}

void CTab1::OnMainDialogCancel()
// This function is called when the main dialog CANCEL button is pressed.
{
    ::AfxMessageBox("Tab1 notified that the main dialog CANCEL button was pressed");
}

BOOL CTab1::OnMainDialogHelp()
// This function is called when the main dialog HELP button is pressed
// and this is the active tab.
{
    ::AfxMessageBox("Tab1 notified that the main dialog HELP button was pressed");

    // Return TRUE if handled.
    return TRUE;
}
