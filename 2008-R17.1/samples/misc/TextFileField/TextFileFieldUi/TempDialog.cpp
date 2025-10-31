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
// TempDialog.cpp : implementation file
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "TextFileFieldUI.h"
#include "TempDialog.h"




// TempDialog dialog

IMPLEMENT_DYNAMIC(TempDialog, CDialog)
TempDialog::TempDialog(CWnd* pParent /*=NULL*/)
	: CDialog(TempDialog::IDD, pParent)
{
}

TempDialog::~TempDialog()
{
}

void TempDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TempDialog, CDialog)
	ON_BN_CLICKED(ID_BROWSE, OnBnClickedBrowse)
END_MESSAGE_MAP()


// TempDialog message handlers

void TempDialog::OnBnClickedBrowse()
{
	// TODO: Add your control notification handler code here
}
