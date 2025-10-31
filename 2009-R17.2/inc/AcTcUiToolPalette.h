//////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1982-2004 by Autodesk, Inc.
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

// Name:            AcTcUiToolPalette.h
//
// Description:     Header for CAcTcUiToolPalette class. This class 
//                  implements the tool palette window and derives from 
//                  CAdUiPalette. The tool palette window is embedded in 
//                  CAdUiToolPaletteSet window and embeds a tool tray 
//                  window CAcUiCatalogView.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTCUITOOLPALETTE_H__
#define __ACTCUITOOLPALETTE_H__


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcTcUi.h"
#include "aduiPalette.h"
#include "AcTcUiPaletteView.h"

class CAcTcUiImpToolPalette;
class AcTcUiSystemInternals;
class CAcTcUiScheme;

class ACTCUI_PORT CAcTcUiToolPalette : public CAdUiPalette
{
    friend CAcTcUiImpToolPalette;

    DECLARE_DYNCREATE(CAcTcUiToolPalette);

public:
    CAcTcUiToolPalette();
    virtual ~CAcTcUiToolPalette();
    
    CAcTcUiPaletteView* GetView             (void);

public:
    // Base class overrides
    virtual BOOL        Create              (CAdUiPaletteSet* pParent);
    BOOL                Create              (DWORD dwStyle, 
                                             LPCTSTR pszName, 
                                             CAdUiPaletteSet* pParent,
                                             DWORD dwPaletteStyle = 0);
    virtual BOOL        Load                (IUnknown* pUnk);
    virtual bool        CanFrameworkTakeFocus();
    virtual BOOL        Save                (IUnknown* pUnk);
    virtual BOOL        Import              (IUnknown* pUnk, LPCTSTR pszRefPath);
    virtual BOOL        Export              (IUnknown* pUnk, LPCTSTR pszRefPath);
    virtual BOOL        OnKillActive        (void);
    virtual BOOL        GetMinimumSize      (CSize& size);
    virtual void        OnSetActive         (void);
    virtual BOOL        NameEditValidation  (CEdit* pEdit);
    virtual BOOL        Paste               (IDataObject* pDataObject, 
                                             int iIndex = -1,
                                             AcTcCatalogItemArray* pNewTools = NULL);
    virtual BOOL        CanPaste            (IDataObject* pDataObject);
    BOOL                SetView             (CAcTcUiPaletteView* pView);
    CAcTcUiScheme*      GetScheme           (void) const;

protected:
    //{{AFX_VIRTUAL(CAcTcUiToolPalette)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcTcUiToolPalette)
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG
    afx_msg LRESULT OnDragEnter(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnDragOver(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnDragLeave(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnDrop(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnDropEx(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnUpdate(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnEndNameEdit(WPARAM, LPARAM);
    DECLARE_MESSAGE_MAP()

protected:
    void            *   mpImpObj;           // Imp object CAcTcUiImpToolPalette

private:
    friend class AcTcUiSystemInternals;
};


#endif //__ACTCUITOOLPALETTE_H__
