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
#include "StdAfx.h"
//
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif


#include "AdUi.h"
#include "AcFdUi.h"
#include "dbfield.h"
#include "AsdkTextFileFieldOptionDialog.h"
#include "AsdkTextFileFieldDialogHook.h"

#include "resource.h"



class CAcFdUiFieldDialogHook;

IMPLEMENT_DYNAMIC(AsdkTextFileFieldOptionDialog, CAcFdUiFieldOptionDialog)

void AsdkTextFileFieldOptionDialog::DoDataExchange(CDataExchange* pDX)
{
	CAcFdUiFieldOptionDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(AsdkTextFileFieldOptionDialog, CAcFdUiFieldOptionDialog)
	ON_BN_CLICKED(ID_BROWSE, OnBnClickedBrowse)
END_MESSAGE_MAP()

void
AsdkTextFileFieldOptionDialog::OnBnClickedBrowse()
{
	struct resbuf *pResBuf;
    int ret = acedGetFileNavDialog (_T("Select text file"), _T(""), _T("txt"), _T("Browse Text File"), 0, &pResBuf);

	if ( ret == 5100 && pResBuf->restype == 5005 )
	{
		SetFilePath(pResBuf->resval.rstring);
		acutRelRb(pResBuf);	
	}
	
}

AsdkTextFileFieldOptionDialog::AsdkTextFileFieldOptionDialog(CAcFdUiFieldDialogHook* pDialogHook,
															 CAcFdUiFieldDialog* pFieldDlg)
	: CAcFdUiFieldOptionDialog(pDialogHook, pFieldDlg, IDD_TEXTFILEDIALOG, NULL)// GetLocalResource() )
{
}

AsdkTextFileFieldOptionDialog::~AsdkTextFileFieldOptionDialog()
{
}

CAcFdUiFieldDialogHook*
AsdkTextFileFieldOptionDialog::GetFieldDialogHook() const
{
	return CAcFdUiFieldOptionDialog::GetFieldDialogHook();
}

CAcFdUiFieldDialog*
AsdkTextFileFieldOptionDialog::GetFieldDialog() const
{
	return CAcFdUiFieldOptionDialog::GetFieldDialog();
}

BOOL
AsdkTextFileFieldOptionDialog::Create(CWnd* pParent)
{
	CAcFdUiFieldOptionDialog::Create(pParent);

	CAcModuleResourceOverride resOverride;

    // The dialog should have resizing border style during creation to 
    // enable control resizing support in base class. After creation we 
    // can remove the border.
    BOOL bRet = CAcFdUiFieldOptionDialog::Create(IDD_TEXTFILEDIALOG, pParent);

    if (!bRet)
        return FALSE;

    // The dialog would have been created with popup style. It should have 
    // child style. Remove the popup style and add child style. Also 
    // remove the thick frame border which was added to get the resizing 
    // support from base class.
    DWORD dwStyle = GetStyle();
    dwStyle |= WS_CHILD;
    dwStyle &= ~WS_POPUP;
    dwStyle &= ~WS_THICKFRAME;
    SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);

    // The above SetWindowLong call resets the parent to desktop window. 
    // Set the parent again.
    SetParent((CWnd*) pParent);

    return TRUE;
}

BOOL
AsdkTextFileFieldOptionDialog::UpdateFieldCode(void)
{
    // Update the field code in the field dialog
    AsdkTextFileFieldDialogHook* pDialogHook = (AsdkTextFileFieldDialogHook*) GetFieldDialogHook();
    ASSERT(pDialogHook != NULL);
    if (pDialogHook == NULL)
        return FALSE;

    pDialogHook->UpdateFieldCode();

    return TRUE;
}

BOOL
AsdkTextFileFieldOptionDialog::SetFieldToEdit(AcDbField* pDbField)
{
    ASSERT(pDbField != NULL);
    if (pDbField == NULL)
        return FALSE;

    //CString sFormat = pDbField->getFormat();
    AcFdFieldValue val;
	Acad::ErrorStatus es = pDbField->getData(TFDATAID,&val);
	assert( es == Acad::eOk );
	if ( es == Acad::eOk )
	{
   		const TCHAR *sValue;
		
		if( val.dataType() != AcFdFieldValue::kString )
			return AcDbField::kInvalidCode;
		else
		{
			val.get(sValue);
			SetFilePath(sValue);
		}
	}
    return TRUE;
}

void
AsdkTextFileFieldOptionDialog::GetFilePath(CString &path) const
{
	GetDlgItemText(IDC_TEXTFILEEDIT, path);
}

void
AsdkTextFileFieldOptionDialog::SetFilePath(CString path)
{
	SetDlgItemText(IDC_TEXTFILEEDIT, path);

	UpdateFieldCode();
}

