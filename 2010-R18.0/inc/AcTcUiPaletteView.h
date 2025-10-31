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


class ACTCUI_PORT CAcTcUiPaletteView : public CAcTcUiCatalogView  
{
public:
    CAcTcUiPaletteView();
    virtual ~CAcTcUiPaletteView();

protected:
    virtual DROPEFFECT  DragEnter           (ADUI_DRAGDATA* pDragData);
    virtual DROPEFFECT  DragOver            (ADUI_DRAGDATA* pDragData);
    virtual void        DragLeave           (ADUI_DRAGDATA* pDragData);
    virtual DROPEFFECT  Drop                (ADUI_DRAGDATA* pDragData);
    virtual DROPEFFECT  DropEx              (ADUI_DRAGDATA* pDragData);

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

