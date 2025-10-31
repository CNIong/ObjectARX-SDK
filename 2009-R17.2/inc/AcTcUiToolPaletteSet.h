//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 1982-2008 by Autodesk, Inc.
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

// Name:            CAcTcUiToolPaletteSet.h
//
// Description:     Header for CAcTcUiToolPaletteSet class. This class 
//                  implements the tool palette window and derives from 
//                  CAdUiPalette. The tool palette window is embedded in 
//                  CAdUiToolPaletteSet window and embeds a tool tray 
//                  window CAcUiCatalogView.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTCUITOOLPALETTESET_H__
#define __ACTCUITOOLPALETTESET_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcTcUi.h"
#include "aduiPaletteSet.h"
#include "AcTcUiToolPalette.h"
#include "AcTcUiToolPaletteGroup.h"


class CAcTcUiImpToolPaletteSet;
class CAcTcUiScheme;

class ACTCUI_PORT CAcTcUiToolPaletteSet : public CAdUiPaletteSet
{
    friend CAcTcUiImpToolPaletteSet;

    DECLARE_DYNCREATE(CAcTcUiToolPaletteSet);

public:
    virtual ~CAcTcUiToolPaletteSet();

    virtual BOOL        Load                (IUnknown* pUnk);
    virtual BOOL        Save                (IUnknown* pUnk);
    virtual BOOL        Import              (IUnknown* pUnk, LPCTSTR pszRefPath);
    virtual BOOL        Export              (IUnknown* pUnk, LPCTSTR pszRefPath);
    virtual BOOL        HitTest             (CPoint pt, UINT& nFlag, 
                                             DWORD& dwData);
    int                 AddPalette          (CAdUiPalette* pPalette);
    int                 InsertPalette       (int iIndex, CAdUiPalette* pPalette);
    BOOL                RemovePalette       (CAdUiPalette* pPalette);
    BOOL                RemovePalette       (int iIndex);
    virtual void        TitleBarLocationUpdated(AdUiTitleBarLocation newLoc);
    CAcTcUiToolPaletteGroup* GetToolPaletteGroup(BOOL bCreate = FALSE);
    CAcTcUiToolPaletteGroup* GetAllPalettesGroup(void);
    CAcTcUiToolPaletteGroup* GetActivePaletteGroup(void);
    BOOL                GetActivePaletteGroup(LPTSTR pszGroup, 
                                              int cbSize) const;
    BOOL                SetActivePaletteGroup(CAcTcUiToolPaletteGroup* pGroup);
    BOOL                SetActivePaletteGroup(LPCTSTR pszGroup);
    CAcTcUiScheme*      GetScheme           (void) const;
    BOOL                Show                (void);
    BOOL                Show                (BOOL bShow);
    BOOL                SetActivePalette    (CAdUiPalette* pPalette);
    BOOL                SetActivePalette    (int nPaletteIndex);
    BOOL                SetActivePalette    (LPCTSTR pszPalName,
                                             BOOL bSearchOnlyCurrentGroup) const;
    CAcTcUiToolPalette* FindPalette         (LPCTSTR pszPalName,
                                             CAcTcUiToolPaletteGroup** ppGroup,
                                             BOOL bSearchOnlyCurrentGroup) const;

protected:
    // Protected constructor
    CAcTcUiToolPaletteSet();

protected:
    virtual BOOL        AddContextMenuItems (CMenu *pMenu, 
                                             int nHitFlag,
                                             int nRightClkTab = 0);
    virtual void        ThemeModified       (AdUiThemeElement element);
    virtual void        OnTabDrag           (CPtrArray & arrayPalettes);
    virtual BOOL        OnBeginDrag         (COleDataSource* pDataSource,
                                             CPtrArray & arrayPalettes);
    virtual void        OnEndDrag           (DROPEFFECT dropEffect);
    virtual BOOL        OnBeginMove         (COleDataSource* pDataSource,
                                             CPtrArray & arrayPalettes);
    virtual void        OnEndMove           (DROPEFFECT dropEffect);
    virtual BOOL        OnRenderData        (LPFORMATETC lpFormatEtc,
                                             LPSTGMEDIUM lpStgMedium);
    virtual void        OnTearOff           (CAdUiPaletteSet* pSet);
    virtual void        DestroyStackedPaletteSet(void);

protected:
    //{{AFX_VIRTUAL(CAcTcUiToolPaletteSet)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
    afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
    afx_msg void OnRemovePaletteSet();
    afx_msg void OnRemoveActivePalette();
    afx_msg void OnRemovePalette();
    afx_msg void OnViewOptions();
    afx_msg void OnSelectPaletteGroup( UINT nID );
    afx_msg void OnShowCustomizeDialog();
    afx_msg void OnShowCustomizeDialogCUI();
    afx_msg void OnNewPalette();
    afx_msg void OnPaste();
    afx_msg void OnPaletteProperties();
    afx_msg void OnRefreshPaletteSet();
    afx_msg void OnRefreshActivePalette();
    afx_msg void OnClose();
    afx_msg void OnMoveUp();
    afx_msg void OnMoveDown();
    afx_msg void OnInvokeCommand(UINT nID);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcTcUiToolPaletteSet)
    //}}AFX_MSG
    afx_msg LRESULT OnDragEnter(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnDragOver(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnDrop(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnDropEx(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnDragLeave(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnUpdate(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnRenderData(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()

protected:
    void            *   mpImpObj;           // Imp object CAcTcUiImpToolPaletteSet

private:
    friend class AcTcUiSystemInternals;

};


#endif //__ACTCUITOOLPALETTESET_H__
