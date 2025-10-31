//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2003-2006  by Autodesk, Inc.
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
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE. AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
//////////////////////////////////////////////////////////////////////////////
//
// Name:            AcFdUiFieldDialogHook.h
//
// Description:     
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcFdUi.h"
#include "DbField.h"
#include <afxtempl.h>


class AcTcUiSystemInternals;
class CAcFdUiFieldDialog;
class CAcFdUiFieldOptionDialog;
class CAcFdUiImpFieldDialog;
class CAcFdUiFieldDialogHook;


typedef CTypedPtrArray<CPtrArray, CAcFdUiFieldDialogHook*>  AcFdUiFieldDialogHookArray;


class ACFDUI_PORT CAcFdUiFieldDialogHook : public CObject
{
public:
    CAcFdUiFieldDialogHook(void);
    ~CAcFdUiFieldDialogHook(void);

    // For internal use only
    virtual BOOL    CreateInstance          (CAcFdUiFieldDialogHook*& pHook);

    virtual int     GetEvaluatorIds         (CStringArray& evalIds);
    virtual BOOL    BeginFieldDialog        (CAcFdUiFieldDialog* pFieldDlg, 
                                             AcDbDatabase* pDb, 
                                             int nContext);
    virtual BOOL    EndFieldDialog          (int nRet);
    virtual BOOL    SetFieldToEdit          (AcDbField* pField);
    AcDbDatabase *  GetDatabase             (void) const;
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

protected:
    void            *   mpImpObj;

private:
    friend class AcFdUiSystemInternals;
};

