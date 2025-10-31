/////////////////////////////////////////////////////////////////////////////
//
//                 (C) Copyright 2001-2008 by Autodesk, Inc.
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
/////////////////////////////////////////////////////////////////////////////
//
// *****************************
// *** FOR INTERNAL USE ONLY ***
// *****************************
//
// Purpose:
//
// Encapsulates the theme of the UI elements. It contains the colors of 
// different elements of the window, fonts, etc. The palette and other 
// window classes can get the UI look from this theme. The theme can contain 
// different set of values for different UI windows. For example it can have 
// one set of colors and fonts for all the dialogs and another set of colors 
// and fonts for all the palettes
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _ADUI_THEME_H_
#define _ADUI_THEME_H_

#include <afxtempl.h>
#include "AdAChar.h"

#define PROPERTY_PALETTE_THEME  ACRX_T(/*MSG0*/"PropertyPalette")
#define TOOL_PALETTE_THEME      ACRX_T(/*MSG0*/"ToolPalette")
#define OWNDERDRAW_BUTTON_THEME ACRX_T(/*MSG0*/"OwnerDrawButton")
#define DIALOG_WORKSHEET_THEME  ACRX_T(/*MSG0*/"DialogWorksheet")
#define PALETTE_SET_THEME       ACRX_T(/*MSG0*/"PaletteSet")
#define DESIGN_CENTER_THEME     ACRX_T(/*MSG0*/"DesignCenter")   // Constant theme for all apps, dom't override
#define TOOL_PANEL_THEME        ACRX_T(/*MSG0*/"ToolPanel")
#define DOCKBAR_THEME           ACRX_T(/*MSG0*/"DockBar")   
#define DOCKCONTROLBAR_THEME    ACRX_T(/*MSG0*/"DockControlBar")   
#define ANCHORBAR_THEME         ACRX_T(/*MSG0*/"AnchorBar")   
#define ACTIVE_THEME            ACRX_T(/*MSG0*/"ACTIVETHEME")


typedef enum {
    
    kUnknownElements = -1,

    // Theme fonts
    kPaletteFontCaption,
    kPaletteFontTab,
    kPaletteFontToolTip,
    kPaletteFont,
    kWorksheetFont,
    kWorksheetFontCaption,
    kInspectorItemFont,
    kInspectorRootFont,

    // Theme colors

    // Palette Set Colors
    kPaletteBackground,
    kPaletteCaptionBackground,
    kPaletteCaptionInactive,
    kPaletteCaptionText,
    kPaletteCaptionInactiveText,
    kPaletteTabText,
    kPaletteTabBackground,
    kPaletteBorder,
    kPaletteTabShadow,
    kPaletteTabHighlight,
    kPaletteTabTextHilite,
    kPaletteTabSelectHilite,
    kPaletteToolTip,
    kPaletteToolTipText,
    kPaletteButtonText,
    kPaletteButtonTextDisabled,
    kPaletteButtonBorder,
    kPaletteItemText,
    kPaletteScrollBackground,
    kPaletteScrollThumb,
    kPaletteScrollArrow,

    // Worksheets
    kWorksheetBackground,
    kWorksheetCaptionBackground,
    kWorksheetCaptionText,
    kWorksheet3DBtnShadow,
    kWorksheetButtonText,
    kWorksheetButtonTextDisabled,
    kWorksheetScrollBackground,
    kWorksheetScrollThumb,
    kWorksheetBorder,
    kWorksheetGripHighlight,

    // Property Inspectors
    kInspector,
    kInspectorTop,
    kInspectorCat,
    kInspectorItem,
    kInspectorBorder,
    kInspectorBorderItem,
    kInspectorTextTop,
    kInspectorTextCat,
    kInspectorTextItem,
    kInspectorFGHighlight,
    kInspectorBGHighlight,
    kInspector3dShadow,
    kInspectorControl,
    kInspectorCatChevron1,
    kInspectorCatChevron2,
    kInspectorSubChevron,

    // Panel Colors
    kPanelBackground,
    kPanelSashBackground,
    kPanelBorder,
    kControlBorder,
    kControlBackground,  
    kDisabledControlBorder,
    kControlSupport,

    // Extra Palette Set Colors
    kPaletteFrameInnerBorder,
    kPaletteFrameOuterBorder,
    kPaletteFrameBackground,
    kPaletteFrameShadow,
    kInspectorTopGradient1,
    kInspectorTopGradient2,
    kPaletteScrollBackgroundBorder,
    kPaletteScrollBackgroundGradient1,
    kPaletteScrollBackgroundGradient2,
    kPaletteScrollSliderInactive,
    kPaletteScrollSliderActiveOuterBorder,
    kPaletteScrollSliderActiveOuterGradient1,
    kPaletteScrollSliderActiveOuterGradient2,
    kPaletteScrollSliderActiveOuterGradient3,
    kPaletteScrollSliderActiveOuterGradient4,
    kPaletteScrollSliderActiveInnerGradient1,
    kPaletteScrollSliderActiveInnerGradient2,
    kInspectorClosedOuterBorder,
    kInspectorOpenOuterBorder,
    kInspectorInnerBorder,

    // Anchor Bar Colors
    kAnchorBarOuterBorder,
    kAnchorBarEmbossRightBottom,
    kAnchorBarEmbossLeftTop,
    kAnchorBarInnerHighlight,
    kAnchorBarGradient1,
    kAnchorBarGradient2,
    kAnchorBarActiveTitleBackground,
    kAnchorBarCaptionText,
    
    // Other Colors
    kGrabBarDotDark,
    kGrabBarDotLight,
    kControlBarTitleBackground,
    
    // Application Frame Window Colors
    kAppFrameBorder,
    kAppFrameOuterBorder,

} AdUiThemeElement;


class CAdUiThemeModifiedReactor
{
public:
    virtual void ThemeModified(const CAdUiTheme * pTheme, AdUiThemeElement element) = 0;
};


class ADUI_PORT CAdUiTheme
{
    friend class CAdUiThemeManager;

public:
    // Returns the color of the specified display element. 
    COLORREF GetColor (AdUiThemeElement nDisplayElement) const;
    // Sets the color of the specified display element
    BOOL SetColor(AdUiThemeElement nDisplayElement, COLORREF crColor);

    BOOL SetFont(AdUiThemeElement nDisplayElement,LOGFONT *plf=NULL);
    BOOL GetFont(AdUiThemeElement nDisplayElement,LOGFONT *plf) const;
    BOOL GetFont(AdUiThemeElement nDisplayElement,CFont *& pFont) const;

    BOOL GetData(int nElement, DWORD& dwData) const;
    void SetData(int nElement, const DWORD& dwData);
    BOOL GetData(int nElement, CString& sData) const;
    void SetData(int nElement, const CString& sData);
    void* GetDataPtr(int nElement) const;
    void SetDataPtr(int nElement, void* pData);

    // Methods for registering a theme client with the theme for "Theme modified" notifications
    BOOL RegisterReactor(CAdUiThemeModifiedReactor * pReactor);
    BOOL UnregisterReactor(CAdUiThemeModifiedReactor * pReactor);

    void SuspendModifiedNotifications() { m_nModNotificationsSuspended++; }
    void ResumeModifiedNotifications();
    void SendModifiedNotification() const;
    bool UsesActiveThemeColors(){return m_bUsesActiveThemeColors;}


    void IncrementRefCount() { m_nRefCount++; }

    // assignment operator
    CAdUiTheme& operator=(const CAdUiTheme *pTheme);
    
private:
    CAdUiTheme();
    virtual ~CAdUiTheme();
    void InitWithActiveThemeColors();

    void SendThemeModifiedNotifications(AdUiThemeElement nElement) const;

    void CheckXP();
    
    COLORREF GetActiveThemeColor(AdUiThemeElement nElement) const;
    
    // Are XP themes supported (FUTURE USE!)
    BOOL UsesXP() { return m_bUsesXPThemes; };

    void DecrementRefCount() { m_nRefCount--; }
    int RefCount() { return m_nRefCount; }

    int    m_nRefCount;
    bool   m_bUsesActiveThemeColors;
    CTypedPtrArray<CPtrArray, CAdUiThemeModifiedReactor*> m_arrayModReactors;
    int m_nModNotificationsSuspended;
    CMap<int, int, DWORD, DWORD> m_mapDwordValues;
    CMap<int, int, CString, CString> m_mapStringValues;
    CMap<int, int, void*, void*> m_mapPointerValues;

    LOGFONT             m_lfWorksheet;
    LOGFONT             m_lfWorksheetCaption;
    LOGFONT             m_lfPaletteCaption;
    LOGFONT             m_lfInspectorItem;
    LOGFONT             m_lfInspectorRoot;
    LOGFONT             m_lfPaletteTab;
    LOGFONT             m_lfPalette;
    LOGFONT             m_lfPaletteToolTip;
    
    // Palettes
    COLORREF            m_crPaletteBkgnd;
    COLORREF            m_crPaletteCaptionBkgnd;
    COLORREF            m_crPaletteCaptionInactive;
    COLORREF            m_crPaletteCaptionText;
    COLORREF            m_crPaletteCaptionInactiveText;
    COLORREF            m_crPaletteItemText;
    COLORREF            m_crPaletteTabText;
    COLORREF            m_crPaletteTabBackground;
    COLORREF            m_crPaletteBorder;
    COLORREF            m_crPaletteTabShadow;
    COLORREF            m_crPaletteTabHighlight;
    COLORREF            m_crPaletteTabSelectHilite;
    COLORREF            m_crPaletteTabTextHilite;
    COLORREF            m_crPaletteScrollBackground;
    COLORREF            m_crPaletteScrollThumb;
    COLORREF            m_crPaletteScrollArrow;
    COLORREF            m_crPaletteButtonBorder;
    COLORREF            m_crPaletteButtonText;
    COLORREF            m_crPaletteButtonTextDisabled;
    COLORREF            m_crPaletteToolTip;
    COLORREF            m_crPaletteToolTipText;
  
    // Worksheets
    COLORREF            m_crWorksheetBkgnd;
    COLORREF            m_crWorksheetCaptionBkgnd;
    COLORREF            m_crWorksheetCaptionText;
    COLORREF            m_crWorksheetBtnShadow;
    COLORREF            m_crWorksheetBtnText;
    COLORREF            m_crWorksheetBtnTextDisabled;
    COLORREF            m_crWorksheetScroll;
    COLORREF            m_crWorksheetScrollThumb;
    COLORREF            m_crWorksheetBorder;
    COLORREF            m_crWorksheetGripHighlight;

    // Property inspectors
    COLORREF            m_crInspector;
    COLORREF            m_crInspectorTop;
    COLORREF            m_crInspectorCat;
    COLORREF            m_crInspectorItem;
    COLORREF            m_crInspectorBorder;
    COLORREF            m_crInspectorBorderItem;
    COLORREF            m_crInspectorTextTop;
    COLORREF            m_crInspectorTextCat;
    COLORREF            m_crInspectorTextItem;
    COLORREF            m_crInspectorFGHighlight;
    COLORREF            m_crInspectorBGHighlight;
    COLORREF            m_crInspector3dShadow;    
    COLORREF            m_crInspectorControl;
    COLORREF            m_crInspectorCatChevron1;
    COLORREF            m_crInspectorCatChevron2;
    COLORREF            m_crInspectorSubChevron;

    // Panel colors
    COLORREF            m_crPanelBackground;
    COLORREF            m_crPanelSashBackground;
    COLORREF            m_crPanelBorder;
    COLORREF            m_crControlBorder;
    COLORREF            m_crControlBackground;  
    COLORREF            m_crDisabledControlBorder;
    COLORREF            m_crControlSupport;  

    // Extra palette set colors
    COLORREF            m_crPaletteFrameInnerBorder;
    COLORREF            m_crPaletteFrameOuterBorder;
    COLORREF            m_crPaletteFrameBackground;
    COLORREF            m_crPaletteFrameShadow;
    COLORREF            m_crInspectorTopGradient1;
    COLORREF            m_crInspectorTopGradient2;

    COLORREF            m_crPaletteScrollBackgroundBorder;
    COLORREF            m_crPaletteScrollBackgroundGradient1;
    COLORREF            m_crPaletteScrollBackgroundGradient2;
    COLORREF            m_crPaletteScrollSliderInactive;
    COLORREF            m_crPaletteScrollSliderActiveOuterBorder;
    COLORREF            m_crPaletteScrollSliderActiveOuterGradient1;
    COLORREF            m_crPaletteScrollSliderActiveOuterGradient2;
    COLORREF            m_crPaletteScrollSliderActiveOuterGradient3;
    COLORREF            m_crPaletteScrollSliderActiveOuterGradient4;
    COLORREF            m_crPaletteScrollSliderActiveInnerGradient1;
    COLORREF            m_crPaletteScrollSliderActiveInnerGradient2;
    COLORREF            m_crInspectorClosedOuterBorder;
    COLORREF            m_crInspectorOpenOuterBorder;
    COLORREF            m_crInspectorInnerBorder;

    // Achor bar colors
    COLORREF            m_crAnchorBarOuterBorder;
    COLORREF            m_crAnchorBarEmbossRightBottom;
    COLORREF            m_crAnchorBarEmbossLeftTop;
    COLORREF            m_crAnchorBarInnerHighlight;
    COLORREF            m_crAnchorBarGradient1;
    COLORREF            m_crAnchorBarGradient2;
    COLORREF            m_crAnchorBarActiveTitleBackground;
    COLORREF            m_crAnchorBarCaptionText;
    
    // Other control colors
    COLORREF            m_crGrabBarDotDark;
    COLORREF            m_crGrabBarDotLight;
    COLORREF            m_crControlBarTitleBackground;

    // Application frame colors
    COLORREF            m_crAppFrameBorder;
    COLORREF            m_crAppFrameOuterBorder;

    BOOL                m_bUsesXPThemes;    
    
};

#endif // ifndef _ADUI_THEME_H_

