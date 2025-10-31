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

// PlotNotificationsDialog.cpp : implementation file
//
#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "PlotNotificationsDialog.h"




// CPlotNotificationsDialog dialog

IMPLEMENT_DYNAMIC(CPlotNotificationsDialog, CDialog)
CPlotNotificationsDialog::CPlotNotificationsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPlotNotificationsDialog::IDD, pParent)
{
}

CPlotNotificationsDialog::~CPlotNotificationsDialog()
{
}

void CPlotNotificationsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLOTNOTIFICATIONLIST, m_NotificationsList);
}


BEGIN_MESSAGE_MAP(CPlotNotificationsDialog, CDialog)
	ON_BN_CLICKED(IDC_CLEAR, OnBnClickedClear)
END_MESSAGE_MAP()


// CPlotNotificationsDialog message handlers

BOOL CPlotNotificationsDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPlotNotificationsDialog::OnBnClickedClear()
{
	m_NotificationsList.ResetContent();
}
