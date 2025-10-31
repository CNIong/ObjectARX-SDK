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
// Name:            AcFdUiFieldOptionDialog.h
//
// Description:     
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AdUi.h"
#include "AcFdUi.h"

class AcTcUiSystemInternals;
class CAcFdUiFieldDialog;
class CAcFdUiFieldDialogHook;
class CAcFdUiImpFieldDialog;
class AcDbField;


class ACFDUI_PORT CAcFdUiFieldOptionDialog : public CAdUiDialog
{
    friend CAcFdUiFieldDialog;
    friend CAcFdUiImpFieldDialog;

    DECLARE_DYNAMIC(CAcFdUiFieldOptionDialog)

public:
    CAcFdUiFieldOptionDialog(CAcFdUiFieldDialogHook* pDialogHook, CAcFdUiFieldDialog* pFieldDlg, 
        UINT nIDTemplate, HINSTANCE hDialogResource = NULL);
    virtual ~CAcFdUiFieldOptionDialog();

    CAcFdUiFieldDialogHook* GetFieldDialogHook(void) const;
    CAcFdUiFieldDialog* GetFieldDialog      (void) const;
    virtual BOOL    Create                  (CWnd* pParent);

public:
    // Base class overrides
    virtual BOOL    Create                  (LPCTSTR lpszTemplateName, 
                                             CWnd* pParent = NULL);
    virtual BOOL    Create                  (UINT nIDTemplate, 
                                             CWnd* pParent = NULL);

protected:
    virtual BOOL    OnSetActive             (void);
    virtual BOOL    OnKillActive            (void);
    virtual BOOL    OnFieldSelected         (UINT uNewFieldId);

protected:
    // Base class overrides
    virtual void    OnOK                    (void);
    virtual void    OnCancel                (void);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    afx_msg LRESULT OnFormatChanged         (WPARAM wParam, 
                                             LPARAM lParam);
    afx_msg LRESULT OnBeginFormatExDialog   (WPARAM wParam, 
                                             LPARAM lParam);
    afx_msg LRESULT OnEndFormatExDialog     (WPARAM wParam, 
                                             LPARAM lParam);
    DECLARE_MESSAGE_MAP()

protected:
    void            *   mpImpObj;

private:
    friend class AcFdUiSystemInternals;    
};
