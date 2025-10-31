//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2003  by Autodesk, Inc.
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
// Name:            AcFdUiFieldFormatDialog.h
//
// Description:     
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AcFdUiFieldOptionDialog.h"

class AcTcUiSystemInternals;
class CAcFdUiFieldDialogHook;
class CAcFdUiFieldFormatList;


class ACFDUI_PORT CAcFdUiFieldFormatDialog : public CAcFdUiFieldOptionDialog
{
	DECLARE_DYNAMIC(CAcFdUiFieldFormatDialog)

public:
	CAcFdUiFieldFormatDialog(CAcFdUiFieldDialogHook* pDialogHook,
        CAcFdUiFieldDialog* pFieldDlg);
	virtual ~CAcFdUiFieldFormatDialog();

    virtual BOOL 	Create					(CWnd* pParent);

    CAcFdUiFieldFormatList* GetFormatList	(void);
    CString			GetFormatType			(void) const;
    BOOL			SetFormatType			(LPCTSTR pszFormatType);
    int				GetCurrentFormat		(CString& sDisplayName, 
											 CString& sFormatString) const;
    BOOL			SetCurrentFormat		(LPCTSTR pszDisplayName, 
											 LPCTSTR pszFormatString);
    BOOL			SetFormatPreviewReadOnly(BOOL bReadOnly = TRUE);
    BOOL			SetFormatPreviewLabel	(LPCTSTR pszText);

protected:
	virtual void    DoDataExchange          (CDataExchange* pDX);
    afx_msg void    OnDestroy               (void);
    afx_msg void    OnLbnSelChangeFormatList(void);
    afx_msg void 	OnEnChangePreview		(void);
    afx_msg void    OnBnClickedFilenameOnly (void);
    afx_msg void    OnBnClickedPathOnly     (void);
    afx_msg void    OnBnClickedPathAndFilename(void);
    afx_msg void    OnBnClickedIncludeExtension(void);
    afx_msg void    OnCbnSelChangeDecimalSeparator(void);
    afx_msg void    OnBnClickedPointX       (void);
    afx_msg void    OnBnClickedPointY       (void);
    afx_msg void    OnBnClickedPointZ       (void);

	DECLARE_MESSAGE_MAP()

protected:
    void            *   mpImpObj;

private:
    friend class AcFdUiSystemInternals;    
};
