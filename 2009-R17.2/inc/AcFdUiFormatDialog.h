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
// Name:            AcFdUiFormatDialog.h
//
// Description:     
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "adui.h"
#include "AcFdUi.h"

class AcTcUiSystemInternals;
class CAcFdUiFormatList;


// Messages sent by the format dialog
#define ACFDUI_UM_FORMAT_CHANGED        (WM_APP + 100)
#define ACFDUI_UM_BEGIN_FORMATEX_DIALOG (WM_APP + 101)
#define ACFDUI_UM_END_FORMATEX_DIALOG   (WM_APP + 102)


// Dialog styles. This decides which flavor of the format dialog is 
// displayed.
// Display preview, format list
#define ACFDUI_FDSTYLE_SIMPLE       (0x1 << 1)
// Display preview, format list, file name options, help text
#define ACFDUI_FDSTYLE_FILENAME     (0x1 << 2)
// Display preview, format list, decimal separator
#define ACFDUI_FDSTYLE_DOUBLE       (0x1 << 3)
// Display preview, format list, decimal separator, list separtor, 
// point formatting options
#define ACFDUI_FDSTYLE_DOUBLE_POINT (0x1 << 4)
// Display all the options
#define ACFDUI_FDSTYLE_ALL          (0x1 << 5)


class ACFDUI_PORT CAcFdUiFormatDialog : public CAdUiDialog
{
	DECLARE_DYNAMIC(CAcFdUiFormatDialog)

public:
	CAcFdUiFormatDialog(CWnd* pParent, BOOL bNew);
	virtual ~CAcFdUiFormatDialog();

    virtual BOOL 	Create					(CWnd* pParent);

    CAcFdUiFormatList* GetFormatList	(void);
    CString			GetFormatType			(void) const;
    BOOL			SetFormatType			(LPCTSTR pszFormatType);
    int				GetCurrentFormat		(CString& sDisplayName, 
											 CString& sFormatString,
                                             CString& sVersion) const;
    BOOL			SetCurrentFormat		(LPCTSTR pszDisplayName, 
											 LPCTSTR pszFormatString);
    BOOL			SetFormatPreviewReadOnly(BOOL bReadOnly = TRUE);
    BOOL			SetFormatPreviewLabel	(LPCTSTR pszText);
    BOOL            SetFormatPreviewText    (LPCTSTR pszPreviewText, 
                                             const AcValue& fieldValue);
    BOOL            SetDialogStyle          (int nStyle);

protected:
	virtual void    DoDataExchange          (CDataExchange* pDX);
    afx_msg void    OnDestroy               (void);
    afx_msg void    OnLbnSelChangeFormatList(void);
    afx_msg void 	OnEnChangePreview		(void);
    afx_msg void    OnBnClickedFilenameOnly (void);
    afx_msg void    OnBnClickedPathOnly     (void);
    afx_msg void    OnBnClickedPathAndFilename(void);
    afx_msg void    OnBnClickedIncludeExtension(void);
    afx_msg void    OnBnClickedFormatEx     (void);
    afx_msg void    OnCbnSelChangePrecision (void);
    afx_msg void    OnCbnSelChangeDecimalSeparator(void);
    afx_msg void    OnCbnSelChangeListSeparator(void);
    afx_msg void    OnCbnEditChangeListSeparator(void);
    afx_msg void    OnBnClickedPointX       (void);
    afx_msg void    OnBnClickedPointY       (void);
    afx_msg void    OnBnClickedPointZ       (void);
    afx_msg void    OnBnClickedAppendSymbol (void);
    afx_msg void    OnCbnSelChangeCurrencySymbol(void);
    afx_msg void    OnLbnSelChangeNegativeNumberList(void);

	DECLARE_MESSAGE_MAP()

protected:
    void            *   mpImpObj;

private:
    friend class AcFdUiSystemInternals;    
};
