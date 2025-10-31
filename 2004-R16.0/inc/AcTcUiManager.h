//////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1982-2002 by Autodesk, Inc.
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
//////////////////////////////////////////////////////////////////////////////
//

// Name:            AcTcUiManager.h
//
// Description:     
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTCUIMANAGER_H__
#define __ACTCUIMANAGER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcTcUiToolPaletteSet.h"
#include "AcTcUi.h"

class AcTcUiSystemInternals;

class __declspec(dllexport) CAcTcUiManager  
{
public:
    CAcTcUiManager();
	virtual ~CAcTcUiManager();
    CAcTcUiToolPaletteSet* GetToolPaletteWindow(void);
    BOOL                Load                (IUnknown* pUnknown);
    BOOL                Save                (IUnknown* pUnknown);
    BOOL                SetApplicationWindow(HWND hWndApp);
    HWND                GetApplicationWindow(void);
    COleDropTarget*     GetDropTarget       (void);
    CAcTcUiToolPalette* CreatePalette       (LPCTSTR pszPalName = NULL,
                                             DWORD dwFlags = 0);
    BOOL                Export              (LPCTSTR pszFile,
                                            const AcTcUiToolPaletteArray* palettes = NULL);
    BOOL                Import              (LPCTSTR pszFile);
    BOOL                FindPalette         (const AcTcCatalogItem* pItem,
                                             CAcTcUiToolPalette** ppToolPalette) const;
    BOOL                FindPalette         (const GUID& itemId,
                                             CAcTcUiToolPalette** ppToolPalette) const;
    BOOL                ShowToolPaletteWindow(BOOL bShow = TRUE);
    BOOL                IsToolPaletteWindowVisible(void) const;

protected:
    void            *   mpImpObj;

private:
    friend class AcTcUiSystemInternals;
};


#endif //__ACTCUIMANAGER_H__
