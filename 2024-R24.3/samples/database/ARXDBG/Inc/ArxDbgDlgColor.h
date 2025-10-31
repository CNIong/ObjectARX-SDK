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

#ifndef ARXDBGDLGCOLOR_H
#define ARXDBGDLGCOLOR_H

#include "Res_ArxDbg.h"

#define WM_COLOR_CHANGED    (WM_USER + 100)    // custom message


/****************************************************************************
**
**    CLASS ArxDbgDlgColor:
**        just used to test color, not to get/set from an entity
**
**    **jma
**
*************************************/

class ArxDbgDlgColor : public CDialog {

public:
                ArxDbgDlgColor(CWnd* pParent);
    virtual        ~ArxDbgDlgColor();

// Dialog Data
    //{{AFX_DATA(AecUiPpColor)
    CStatic    m_colorSwatch;
    //}}AFX_DATA


// Overrides
    // ClassWizard generate virtual function overrides
    //{{AFX_VIRTUAL(AecUiPpColor)
    public:
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgDlgColor)
    afx_msg void OnByblock();
    afx_msg void OnBylayer();
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // member data
    CRect    m_colorTiles[256];            // Array of rects for each color tile in the palette
    CRect    m_fullPaletteRectTop;        // Windows rectangle of full palette region top
    CRect    m_fullPaletteRectBottom;    // Windows rectangle of full palette region bottom
    CRect    m_standardColorsRect;        // Windows rectangle of standard colors region
    CRect    m_grayColorsRect;            // Windows rectangle of gray colors region
    CRect    m_currentColorRect;            // Windows rectangle of current color
    int        m_currentIndex;

        // helper functions
    void    display();
    BOOL    pickedColorSwatch(CPoint& point);
    void    initColorTileRects();
    void    calculateRectSize(UINT controlId, CRect& rect, double gridX, double gridY,
                        long& sizeX, long& sizeY, long& bookEndGapX, long& bookEndGapY);
    BOOL    setToAcadColorPalette(CDC* dc);
    void    drawCurrentColorSwatch(CDC* dc);
};


#endif    // ARXDBGDLGCOLOR_H
