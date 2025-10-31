//////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1982-2007 by Autodesk, Inc.
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

// Name:            AcTcUiScheme.h
//
// Description:     
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTCUISCHEME_H__
#define __ACTCUISCHEME_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcTcUiToolPaletteSet.h"
#include "AcTcUi.h"

class AcTcUiSystemInternals;

class ACTCUI_PORT CAcTcUiScheme : public CObject
{
public:
    enum RefreshScope {
        kAllPalettes                    = (0x1 << 0),
        kRefreshEnabledPalettes         = (0x1 << 1),
        kAutoRefreshEnabledPalettes     = (0x1 << 2),
    };

    enum ShowOption {
        kShow                           = (0x1 << 0),
        kHide                           = (0x1 << 1),
		kSaveState						= (0x1 << 2),
        kRestoreState                   = (0x1 << 3),
    };

    CAcTcUiScheme(AcTcScheme* pScheme);
	virtual ~CAcTcUiScheme();

    BOOL                Load                (IUnknown* pUnknown);
    BOOL                Save                (IUnknown* pUnknown);
    BOOL                Unload              (void);
    CAcTcUiToolPaletteSet* CreatePaletteSet (LPCTSTR pszPalSetName);
    CAcTcUiToolPaletteSet* GetPaletteSet    (void);
    BOOL                FindPalette         (const AcTcCatalogItem* pItem, 
                                             CAcTcUiToolPalette** ppToolPalette) const;
    BOOL                FindPalette         (const AcTcCatalogItem* pItem, 
                                             CAcTcUiToolPalette** ppToolPalette,
                                             CAcTcUiToolPaletteSet** ppToolPaletteSet) const;
    BOOL                FindPalette         (const GUID& itemId,
                                             CAcTcUiToolPalette** ppToolPalette) const;
    BOOL                FindPalette         (const GUID& itemId,
                                             CAcTcUiToolPalette** ppToolPalette,
                                             CAcTcUiToolPaletteSet** ppToolPaletteSet) const;
    BOOL                Export              (LPCTSTR pszFile);
    BOOL                Export              (LPCTSTR pszFile,
                                             const AcTcUiToolPaletteArray* palettes);
    BOOL                Import              (LPCTSTR pszFile);
    BOOL                Refresh             (RefreshScope nScope);
    BOOL                Refresh             (RefreshScope nScope,
                                             DWORD dwRefreshFlag);
    BOOL                Show                (ShowOption nOption,
											 LONG_PTR lKey);

protected:
    void            *   mpImpObj;

private:
    friend class AcTcUiSystemInternals;
};


#endif //__ACTCUISCHEME_H__
