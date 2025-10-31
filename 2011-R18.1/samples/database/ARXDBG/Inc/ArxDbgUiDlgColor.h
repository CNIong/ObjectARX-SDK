//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
//

#ifndef ARXDBGUIDLGCOLOR_H
#define ARXDBGUIDLGCOLOR_H

#include "Res_ArxDbg.h"

#define WM_COLOR_CHANGED    (WM_USER + 100)    // custom message


/****************************************************************************
**
**	CLASS ArxDbgUiDlgColor:
**		just used to test color, not to get/set from an entity
**
**	**jma
**
*************************************/

class ArxDbgUiDlgColor : public CAcUiDialog {

public:
                ArxDbgUiDlgColor(CWnd* pParent);
    virtual		~ArxDbgUiDlgColor();

    //{{AFX_DATA(AecUiPpColor)
    enum { IDD = ARXDBG_DLG_COLOR };
    CStatic    m_colorSwatch;
    //}}AFX_DATA

    // ClassWizard generate virtual function overrides
    //{{AFX_VIRTUAL(AecUiPpColor)
    public:
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiDlgColor)
    afx_msg void OnByblock();
    afx_msg void OnBylayer();
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // member data
    CRect    m_colorTiles[256];         // Array of rects for each color tile in the palette
    CRect    m_fullPaletteRectTop;      // Windows rectangle of full palette region top
    CRect    m_fullPaletteRectBottom;	// Windows rectangle of full palette region bottom
    CRect    m_standardColorsRect;      // Windows rectangle of standard colors region
    CRect    m_grayColorsRect;          // Windows rectangle of gray colors region
    CRect    m_currentColorRect;        // Windows rectangle of current color
    int      m_currentIndex;

        // helper functions
    void    display();
    BOOL    pickedColorSwatch(CPoint& point);
    void    initColorTileRects();
    void    calculateRectSize(UINT controlId, CRect& rect, double gridX, double gridY,
                        long& sizeX, long& sizeY, long& bookEndGapX, long& bookEndGapY);
    BOOL    setToAcadColorPalette(CDC* dc);
    void    drawCurrentColorSwatch(CDC* dc);
};


#endif    // ARXDBGUIDLGCOLOR_H
