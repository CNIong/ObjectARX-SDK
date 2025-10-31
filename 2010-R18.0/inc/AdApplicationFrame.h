//////////////////////////////////////////////////////////////////////////////
//
//
// (C) Copyright 2008-2009 Autodesk, Inc. All rights reserved.
//
// **** CONFIDENTIAL MATERIAL ****
//
// The information contained herein is confidential, proprietary to
// Autodesk, Inc., and considered a trade secret. Use of this information
// by anyone other than authorized employees of Autodesk, Inc. is granted
// only under a written nondisclosure agreement, expressly prescribing
// the scope and manner of such use.
//
//////////////////////////////////////////////////////////////////////////////
//
// Name:    AdApplicationFrame.h - Main window frame.
//
// Remarks: 
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __AD_APPFRAME_H__
#define __AD_APPFRAME_H__

#include <list>
#include "AdExportDef.h"

// forward declarations
class AdImpApplicationFrame;
class AdImpMenuBar;
class AdVisualElementBase;

class ADAF_PORT AdColorTheme;
class ADAF_PORT AdApplicationFrameReactor;
class ADAF_PORT AdMenuBar;


/// <summary>
/// The callback provided by the application that integrates the
/// application frame. 
/// </summary>                                                  
typedef LRESULT (*LPFNAPPFRAMECALLBACK)(UINT nIndex, void* pUserData, void *pContextData);

/// <summary>
/// The tooltip information that will be used for
/// kAd_ToolTip_Show when the application frame invokes the
/// application callback register with AddFrameCallback. 
/// </summary>                                             
class ADAF_PORT AdCallDataTooltipInfo
{
public:

    AdCallDataTooltipInfo(int nToolType, wchar_t* pBtnStr);

    int GetToolType();
    void SetToolType(int nToolType);
    wchar_t* GetButtonText();
    void SetButtonText(wchar_t* pBtnStr);

private:
    /// <summary>
    /// Default constructor is intentionally forbidden. 
    /// </summary>                                      
    AdCallDataTooltipInfo();
    /// <summary>
    // Copy constructor and assignment operator are forbidden intentionally.
    /// </summary>
    AdCallDataTooltipInfo(const AdCallDataTooltipInfo& callDataTooltipInfo);
    AdCallDataTooltipInfo& operator=(const AdCallDataTooltipInfo& callDataTooltipInfo);

    /// <summary> Type id of tool, refer to enum Ad_AppFrame_ToolTipId
    /// </summary>
    int m_nToolType;

    /// <summary> The string to be displayed as Tooltip content. </summary>
    wchar_t *m_pBtnStr;
};


//////////////////////////////////////////////////////////////////
// Application Frame

/// <summary>
/// This class represents ApplicationFrame in the AppFrame
/// component. 
/// </summary>                                            
class ADAF_PORT AdApplicationFrame
{
public:
    /// <summary>
    /// Size constants for the Autodesk Application Frame.
    /// </summary>                                                  
    enum Ad_AppFrame_Const 
    {
        kAdApplicationStatusBarHeight_Min = 24,                     // Minimum height of Application Status Bar
        kAdDefaultDpi = 96
    };

    /// <summary>
    /// The state of DocumentControl's host window. 
    /// </summary>                                  
    enum Ad_HostWindow_States 
    {
        kAd_DocumentActivated = 1,
        kAd_MenuSelect        = 2,
        kAd_MDIStateChanged   = 3,
        kAd_WindowPosChanged  = 4,
        kAd_SessionInit       = 5,
        kAd_SessionDone       = 6,
        kAd_SettingChanged    = 7,
        kAd_MDIMetricsChanged = 8,
        kAd_SetWindowText     = 9,
        kAd_VisibilityChanged = 10,
        kAd_GetWindowText     = 11,
        kAd_GetWindowTextLen  = 12,
        kAd_SysColorChanged   = 13
    };

    /// <summary>
    /// VisualElement's index order for the Autodesk Application
    /// Frame. 
    /// </summary>                                              
    enum Ad_AppFrame_ToolTipId 
    {
        kAd_ToolId_ApplicationButton    = 1000,
    };

    /// <summary>
    /// Callback ID list for the AppFrame. 
    /// </summary>                         
    enum Ad_Callback_Index 
    {
        kAd_ApplicationButton_IsOpen,
        kAd_ApplicationButton_ShowSmallButton,
        kAd_ToolTip_Close,
        kAd_ToolTip_Show,
        kAd_MenuBar_Show,
        kAd_MenuBar_ExecuteMenuItem,
        kAd_WorkSpaceInfo,
        kAd_GetProductName,
        kAd_Ribbon_IsDockedTop,
        kAd_ACAD_InPlotPreview,
        kAd_ACAD_GetDataSource,
        kAd_RecalcLayout,
        kAd_StayActive,
        kAd_GetMDIClient,
        kAd_MDIGetActive,
        kAd_SkipStandardBackgroundDraw,
        kAd_SkipProductNameUpdate
    };

    /// <summary>
    /// Defines the Client application character set, this defaults to Unicode
    /// </summary>                                          
    enum Ad_Product_Character_Set
    {
        kAd_Unicode,
        kAd_MBCS
    };

    static AdApplicationFrame* CreateInstance(HWND hWndMainFrame);

    virtual ~AdApplicationFrame();

    bool Initialize();

    void SessionInitialized();

    AdMenuBar* GetMenuBar();

    void SetDocumentName(LPCWSTR wszDocumentName);

    bool SetProductLogo(HBITMAP hBitmap);
    bool SetBrand(HBITMAP hBitmap);
    bool SetProductIcon(HICON hIcon);
    bool SetMainMenu(HMENU hMainMenu);
    bool SetMainFrame(HWND hWndMainFrame);
    bool SetMainFrameRect(RECT rectMainFrame);
    bool SetProductCharacterSet(Ad_Product_Character_Set charSet);
    bool SetProductName(LPCWSTR lpszName);
    bool SetApplicationButton(HBITMAP hBitmap, 
        HBITMAP hHotBitmap, HBITMAP hSelectedBitmap);
    bool SetSmallApplicationButton(HBITMAP hBitmap, 
        HBITMAP hHotBitmap, HBITMAP hSelectedBitmap);

    bool IsMenuBarVisible();
    void ShowMenuBar(bool bShow = true);

    void UpdateApplicationButton();
    bool IsApplicationButtonEnabled() const;
    void EnableApplicationButton(bool bEnable = true);

    void ForceFrameRepaint(HWND hWnd);

    unsigned long GetFrameStates();
    unsigned long SetFrameStates(unsigned long dwFrameStates);

    bool AddFrameReactor(AdApplicationFrameReactor *pFrameReactor);
    bool RemoveFrameReactor(AdApplicationFrameReactor *pFrameReactor);

    LPFNAPPFRAMECALLBACK AddFrameCallback(LPFNAPPFRAMECALLBACK pfnCallback, void* pUserData);

    bool TranslateMainFrameMessage(MSG *pMessage);
    BOOL PreTranslateMessageHandler(MSG* pMsg);

    LRESULT ProcessMainFrameMessage(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
    bool HostWindowStateChanged(UINT nState, WPARAM wParam, LPARAM lParam);

    HWND GetAppFrameHwnd();

    HWND GetQuickAccessToolBarHwnd();
    void ShowQuickAccessToolBar(bool bShow);

    HWND GetInfoCenterControl();
    bool SetInfoCenterControl(HWND hControl);
    void EnableInfoCtrCtrl(BOOL bEnable);
    void UpdateInfoCenterControl();


    int GetDocumentControlHeight() const;

    void TrackPopupByMenuCmd(int nIndex);
    void EnableMenuBar(bool bEnable);

protected:
    AdApplicationFrame(HWND hWndMainFrame); 

    // Data members

    /// <summar>
    /// Member pointer to the single instance of the application frame; there can be only one per application.
    /// </summary>
    static AdApplicationFrame *spAppFrame;

    /// <summary>
    /// Member pointer to the implementation class for the application frame.
    /// </summary>
    AdImpApplicationFrame *mpImpAppFrame;

    /// <summary>
    /// Member pointer to the menu bar.
    /// </summary>
    AdMenuBar *mpAdMenuBar;

};
#endif
