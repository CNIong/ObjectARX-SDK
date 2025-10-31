//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2003-2007  by Autodesk, Inc.
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
// Name:            AcFdUiFieldDialog.h
//
// Description:     
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "adui.h"
#include "AcFdUi.h"


class AcFdUiSystemInternals;
class CAcFdUiFieldOptionDialog;
class CAcFdUiImpFieldDialog;


// Field dialog context flags
#define ACFDUI_FD_CREATE_FIELD         1
#define ACFDUI_FD_EDIT_FIELD           2


class ACFDUI_PORT CAcFdUiFieldDialog : public CAdUiDialog
{
    friend CAcFdUiImpFieldDialog;

    DECLARE_DYNAMIC(CAcFdUiFieldDialog)

public:
    CAcFdUiFieldDialog(CWnd* pParent = NULL);
    virtual ~CAcFdUiFieldDialog();

    INT_PTR         DoModal                 (AcDbField*& pField, 
                                             BOOL bEdit, 
                                             AcDbDatabase* pDb);
    AcDbField   *   GetFieldToEdit          (void) const;
    BOOL            SetFieldCodeReadOnly    (BOOL bReadOnly = TRUE);
    CString         GetFieldCode            (void) const;
    BOOL            SetFieldCode            (LPCTSTR pszExpr);
    BOOL            IsFieldCodeDirty        (void);
    CEdit       *   GetFieldCodeEditCtrl    (void);
    BOOL            GetCurrentField         (UINT* pFieldId, 
                                             UINT* pCatId) const;
    BOOL            SelectField             (UINT uFieldId, 
                                             UINT uCatId);
    CAcFdUiFieldOptionDialog* GetOptionDialog(void) const;

public:
    // Base class overrides
    void            BeginEditorCommand      (void);
    void            CompleteEditorCommand   (BOOL restoreDialogs = TRUE);
    void            CancelEditorCommand     (void);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()

protected:
    virtual BOOL    OnInitDialog            (void);
    virtual void    OnOK                    (void);
    virtual void    OnCancel                (void);

    afx_msg void    OnCbnSelChangeCategoryList(void);
    afx_msg void    OnLbnSelChangeFieldNameList(void);
    afx_msg void    OnEnChangeFieldCode     (void);
    afx_msg void    OnDialogHelp            (void);
    afx_msg LRESULT OnFormatChanged         (WPARAM wParam, 
                                             LPARAM lParam);
    afx_msg LRESULT OnBeginFormatExDialog   (WPARAM wParam, 
                                             LPARAM lParam);
    afx_msg LRESULT OnEndFormatExDialog     (WPARAM wParam, 
                                             LPARAM lParam);

protected:
    void            *   mpImpObj;

private:
    friend class AcFdUiSystemInternals;    
};
