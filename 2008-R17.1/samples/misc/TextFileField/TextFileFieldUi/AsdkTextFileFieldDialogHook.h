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
#pragma once

#include "AcFdUiFieldDialogHook.h"
#include "AsdkTextFileFieldOptionDialog.h"

// Must be shared definitions with AsdkTextFileEvaluator.h
//
#define TFEVALID		_T("textfile")
#define TFFIELDCODE		_T("textfile")
#define TFDATAID		_T("TextFileData")

// Specific to this project
//
#define TFFIELDID		123
#define TFCATID			1234
#define TFFIELDNAME		_T("Text File Field")

class AsdkTextFileFieldDialogHook : public CAcFdUiFieldDialogHook
{
public:
	AsdkTextFileFieldDialogHook(void);
	virtual ~AsdkTextFileFieldDialogHook(void);

    virtual int     GetEvaluatorIds         (CStringArray& evalIds);
    virtual BOOL    BeginFieldDialog        (CAcFdUiFieldDialog* pFieldDlg, 
                                             AcDbDatabase* pDb, 
                                             int nContext);
    virtual BOOL    EndFieldDialog          (int nRet);
    virtual BOOL    SetFieldToEdit          (AcDbField* pField);
    virtual BOOL    GetCategoryNames        (UINT uMinUnusedCatId,
                                             CStringArray& catNames, 
                                             CUIntArray& catIds);
	virtual BOOL    GetFieldNames           (UINT uCatId, 
											 UINT uMinUnusedFieldId,
											 CStringArray& fieldNames, 
											 CUIntArray& fieldIds,
											 BOOL& bSort);
    virtual BOOL    GetOptionDialog         (UINT uFieldId, 
                                             CAcFdUiFieldOptionDialog*& pOptionDlg);
    virtual CString GetPreview              (LPCTSTR pszFormatType, 
                                             LPCTSTR pszFormat);
    virtual BOOL    UpdateFieldCode         (void);
    virtual BOOL    OnFieldSelected         (UINT uFieldId);
    virtual BOOL    CreateField             (UINT uFieldId, 
                                             AcDbField*& pField);

    AcDbDatabase *  GetDatabase             (void) const;
	CString			GetFieldCode			(UINT uFieldId);

    void			SetOptionDialog			(AsdkTextFileFieldOptionDialog *pDialog);
	void			DeleteOptionDialog		();

private:
    CAcFdUiFieldDialog *					mpFieldDialog;
	AsdkTextFileFieldOptionDialog *			mpOptionDialog;
};