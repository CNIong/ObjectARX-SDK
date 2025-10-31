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
// Name:            AcFdUiFormatList.h
//
// Description:     
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AcFdUi.h"

class AcTcUiSystemInternals;


class ACFDUI_PORT CAcFdUiFormatList : public CAdUiListBox
{
	DECLARE_DYNAMIC(CAcFdUiFormatList)

public:
	CAcFdUiFormatList(void);
	virtual ~CAcFdUiFormatList(void);

    void			SetRootKey              (LPCTSTR pszKey);
    void			SetPersistency			(BOOL bPersist);
    CString			GetFormatType			(void) const;
    BOOL			SetFormatType			(LPCTSTR pszFormatType);
    int				GetCurrentFormat		(CString& sDisplayName, 
											 CString& sFormatString) const;
    BOOL			SetCurrentFormat		(LPCTSTR pszDisplayName, 
											 LPCTSTR pszFormatString);
    BOOL			Refresh					(void);

protected:
    afx_msg int     OnCreate                (LPCREATESTRUCT lpCreateStruct);
    afx_msg void 	OnDestroy				(void);

	DECLARE_MESSAGE_MAP()

protected:
    void            *   mpImpObj;

private:
    friend class AcFdUiSystemInternals;    
};
