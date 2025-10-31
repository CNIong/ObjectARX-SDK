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

// Name:            AcTcUiToolPaletteGroup.h
//
// Description:     Header for CAcTcUiToolPaletteGroup class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AcTcUiToolPalette.h"


class CAcTcUiImpToolPaletteGroup;
class CAcTcUiImpToolPaletteSet;


class ACTCUI_PORT CAcTcUiToolPaletteGroup : public CObject
{
    DECLARE_DYNAMIC(CAcTcUiToolPaletteGroup);

public:
    CAcTcUiToolPaletteGroup();
    virtual ~CAcTcUiToolPaletteGroup();

    BOOL            Reset                   (void);
    CString         GetName                 (void) const;
    BOOL            SetName                 (LPCTSTR pszName);
    CString         GetDescription          (void) const;
    BOOL            SetDescription          (LPCTSTR pszDesc);
    BOOL            IsItemPalette           (int iIndex) const;
    int             AddItem                 (CAcTcUiToolPalette* pPalette);
    int             AddItem                 (CAcTcUiToolPaletteGroup* pGroup);
    int             InsertItem              (int iIndex, 
                                             CAcTcUiToolPalette* pPalette);
    int             InsertItem              (int iIndex, 
                                             CAcTcUiToolPaletteGroup* pGroup);
    int             GetItemCount            (void) const;
    BOOL            GetItem                 (int iIndex, 
                                             CAcTcUiToolPalette*& pPalette) const;
    BOOL            GetItem                 (int iIndex, 
                                             CAcTcUiToolPaletteGroup*& pGroup) const;
    BOOL            DeleteItem              (CAcTcUiToolPalette* pPalette, 
                                             BOOL bRecursive = FALSE);
    BOOL            DeleteItem              (CAcTcUiToolPaletteGroup* pGroup);
    BOOL            RemoveItem              (CAcTcUiToolPalette* pPalette, 
                                             BOOL bRecursive = FALSE);
    BOOL            RemoveItem              (CAcTcUiToolPaletteGroup* pGroup);
    BOOL            DeleteAllPalettes       (void);
    BOOL            DeleteAllItems          (void);
    int             GetActivePalette        (void) const;
    BOOL            SetActivePalette        (int nIndex);
    BOOL            GetCustomData           (IUnknown** ppUnknown);
    virtual BOOL    Load                    (IUnknown* pUnk);
    virtual BOOL    Save                    (IUnknown* pUnk);
    virtual BOOL    Clone                   (CAcTcUiToolPaletteGroup*& pClone);
    CAcTcUiToolPaletteGroup* FindGroup      (LPCTSTR pszGroup, 
                                             BOOL bRecursive = TRUE);
    CAcTcUiToolPalette* FindPalette         (LPCTSTR pszPalName, 
                                             CAcTcUiToolPaletteGroup** ppGroup, 
                                             BOOL bRecursive = TRUE) const;

protected:
    void            *   mpImpObj;

private:
    friend class AcTcUiSystemInternals;
};

