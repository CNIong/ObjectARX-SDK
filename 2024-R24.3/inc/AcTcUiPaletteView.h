//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// Name:            AcTcUiPaletteView.h
//
// Description:     Header for CAcTcUiPaletteView class. This class 
//                  derives from CAcTcUiCatalogView. It is  manages the tools. 
//                  The Palette View window is embedded in a tool palette 
//                  window CAdUiToolPalette which in turn is embedded in a 
//                  palette set window CAdUiToolPaletteSet.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AcTcUiCatalogView.h"

#ifndef _ADESK_MAC_
class ACTCUI_PORT CAcTcUiPaletteView : public CAcTcUiCatalogView  
{
public:
    CAcTcUiPaletteView();
    ~CAcTcUiPaletteView();

protected:
    DROPEFFECT  DragEnter           (ADUI_DRAGDATA* pDragData) override;
    DROPEFFECT  DragOver            (ADUI_DRAGDATA* pDragData) override;
    void        DragLeave           (ADUI_DRAGDATA* pDragData) override;
    DROPEFFECT  Drop                (ADUI_DRAGDATA* pDragData) override;
    DROPEFFECT  DropEx              (ADUI_DRAGDATA* pDragData) override;

protected:
    //{{AFX_VIRTUAL(CAcTcUiPaletteView)
    //}}AFX_VIRTUAL

protected:
    // Protected constructor
    CAcTcUiPaletteView(AcTcUiSystemInternals*);

protected:
    //{{AFX_MSG(CAcTcUiPaletteView)
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnInvokeCommand(UINT nID);
    afx_msg void OnPaletteRemove();
    afx_msg void OnCatalogItemSpecifyImage();
    afx_msg void OnCatalogItemRemoveImage();
    afx_msg void OnCatalogItemUpdateImage();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
#endif // Nodef _ADESK_MAC_

