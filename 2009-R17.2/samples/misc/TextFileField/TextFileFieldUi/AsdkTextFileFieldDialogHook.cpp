//
//
// (C) Copyright 2002-2007 by Autodesk, Inc. 
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


#include "dbfield.h"
#include "AsdkTextFileFieldDialogHook.h"
#include "AsdkTextFileFieldOptionDialog.h"
#include "AcFdUi.h"
#include "AcFdUiFieldDialog.h"



AsdkTextFileFieldDialogHook::AsdkTextFileFieldDialogHook()
{
}

AsdkTextFileFieldDialogHook::~AsdkTextFileFieldDialogHook()
{
}

int
AsdkTextFileFieldDialogHook::GetEvaluatorIds(CStringArray& evalIds)
{
    evalIds.Add( TFEVALID );
    size_t size = evalIds.GetSize();
    ASSERT( size <= INT_MAX );
    return (int)size;
}

BOOL
AsdkTextFileFieldDialogHook::BeginFieldDialog(CAcFdUiFieldDialog* pFieldDlg, AcDbDatabase* pDb, int nContext)
{
    CAcFdUiFieldDialogHook::BeginFieldDialog(pFieldDlg, pDb, nContext);

	AsdkTextFileFieldOptionDialog* pOptionDlg = new AsdkTextFileFieldOptionDialog(this, pFieldDlg);
    ASSERT(pOptionDlg != NULL);
    SetOptionDialog(pOptionDlg);
    mpFieldDialog = pFieldDlg;
	return TRUE;
}


BOOL
AsdkTextFileFieldDialogHook::EndFieldDialog(int nRet)
{
	CAcFdUiFieldDialogHook::EndFieldDialog(nRet);
	DeleteOptionDialog();
	mpFieldDialog  = NULL;
	return TRUE;
}

BOOL
AsdkTextFileFieldDialogHook::SetFieldToEdit(AcDbField* pField)
{
    // Call the base class and set the field in the base class
    if (!CAcFdUiFieldDialogHook::SetFieldToEdit(pField))
	{
        // Invalid field
        return FALSE;
    }

    // Select the category and field
    BOOL bRet = mpFieldDialog->SelectField(TFFIELDID, TFCATID);
    ASSERT(bRet);

    // The above SelectField should have created the option 
    // dialog. Get the option dialog and initialize it with the 
    // field being edited.
    AsdkTextFileFieldOptionDialog* pOptionDlg = (AsdkTextFileFieldOptionDialog*) mpFieldDialog->GetOptionDialog();
    ASSERT(pOptionDlg != NULL);
    if (pOptionDlg != NULL)
        bRet = pOptionDlg->SetFieldToEdit(pField);

    return TRUE;
}

AcDbDatabase *
AsdkTextFileFieldDialogHook::GetDatabase(void) const
{
	return CAcFdUiFieldDialogHook::GetDatabase();
}

BOOL
AsdkTextFileFieldDialogHook::GetCategoryNames(UINT uMinUnusedCatId, CStringArray& catNames, CUIntArray& catIds)
{
	CAcFdUiFieldDialogHook::GetCategoryNames(uMinUnusedCatId, catNames, catIds);
	catNames.Add( _T("External Files") );
	catIds.Add( TFCATID );
	return TRUE;
}

BOOL 
AsdkTextFileFieldDialogHook::GetFieldNames(UINT uCatId, UINT uMinUnusedFieldId, CStringArray& fieldNames, 
										   CUIntArray& fieldIds, BOOL& bSort)
{
	if ( uCatId == TFCATID )
	{
		fieldNames.Add( TFFIELDNAME );
		fieldIds.Add( TFFIELDID );
		bSort = TRUE;
	}
	return TRUE; //CAcFdUiFieldDialogHook::GetFieldNames(uCatId, uMinUnusedFieldId, fieldNames, fieldIds, bSort);
}

BOOL
AsdkTextFileFieldDialogHook::GetOptionDialog(UINT uFieldId, CAcFdUiFieldOptionDialog*& pOptionDlg)
{
	pOptionDlg = mpOptionDialog;
	return TRUE;
}

CString
AsdkTextFileFieldDialogHook::GetPreview(LPCTSTR pszFormatType, LPCTSTR pszFormat)
{
	return CAcFdUiFieldDialogHook::GetPreview(pszFormatType, pszFormat);
}

BOOL
AsdkTextFileFieldDialogHook::UpdateFieldCode(void)
{
    ASSERT(mpFieldDialog != NULL);
    if (mpFieldDialog == NULL)
        return FALSE;

    UINT uFieldId;
    mpFieldDialog->GetCurrentField(&uFieldId, NULL);
    ASSERT(uFieldId != ACFDUI_CATEGORY_ID_ALL);
    if (uFieldId == ACFDUI_CATEGORY_ID_ALL)
        return FALSE;

    CString sFieldCode = GetFieldCode(uFieldId);

    mpFieldDialog->SetFieldCode(sFieldCode);

    return TRUE;
}

BOOL
AsdkTextFileFieldDialogHook::OnFieldSelected(UINT uFieldId)
{
    ASSERT(mpFieldDialog != NULL && mpOptionDialog != NULL);

    mpOptionDialog->OnFieldSelected(uFieldId);

    return TRUE;
}

BOOL
AsdkTextFileFieldDialogHook::CreateField(UINT uFieldId, AcDbField*& pField)
{
	CAcFdUiFieldDialogHook::CreateField(uFieldId, pField);

	CString strField, strPath;
	mpOptionDialog->GetFilePath(strPath);
	strField.Format(_T("%%<\\%s %s>%%"), TFFIELDCODE, strPath);

    pField = new AcDbField();
    pField->setFieldCode(strField);

    Acad::ErrorStatus es = pField->evaluate(AcDbField::kPreview, GetDatabase());
    if (es != Acad::eOk)
	{
		AcDbField::EvalStatus evalStatus = pField->evaluationStatus();

		CString sMsg;
		if (evalStatus == AcDbField::kEvaluatorNotFound)
			sMsg = _T("Evaluator is not found to evaluate the field");
		else
			sMsg = _T("Invalid field code");
	    
		AfxMessageBox(sMsg);

		// Set focus to field code edit box
		mpFieldDialog->GetFieldCodeEditCtrl()->SetFocus();

		delete pField;
		pField = NULL;

		return FALSE;
	}

	pField->setEvaluationOption(AcDbField::kAutomatic);

    return TRUE;
}

CString
AsdkTextFileFieldDialogHook::GetFieldCode(UINT uFieldId)
{
    // If the field code has been edited in the field code edit box we 
    // should use the edited text as field code.
    CString sFieldCode;
    ASSERT(mpFieldDialog != NULL);
    if (mpFieldDialog->IsFieldCodeDirty())
	{
        // Field code has been edited. Use the edited field code if it is 
        // not blank.
        sFieldCode = mpFieldDialog->GetFieldCode();
        sFieldCode.Trim();
        if (!sFieldCode.IsEmpty())
            return sFieldCode;
    }

	CString sFieldExpression;
	
	// Need to find some way to get the
	mpOptionDialog->GetFilePath(sFieldExpression);

	sFieldCode.Format(_T("%%<\\%s %s>%%"), TFFIELDCODE, sFieldExpression);
    sFieldCode.Trim();

    return sFieldCode;
}

void
AsdkTextFileFieldDialogHook::SetOptionDialog(AsdkTextFileFieldOptionDialog *pDialog)
{
	mpOptionDialog = pDialog;
}

void
AsdkTextFileFieldDialogHook::DeleteOptionDialog()
{
	delete mpOptionDialog;
	mpOptionDialog = NULL;
}