//
// (C) Copyright 1988-2009 by Autodesk, Inc
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
// Name:    rxmfcapi.h
//
// Remarks: This module contains the implementation for ARXMFC API.
//          You need to include windows and/or ole header files
//
//////////////////////////////////////////////////////////////////////////////

#include "AdAChar.h"
#include "AcStatusBar.h"

#ifndef AD_RXMFCAPI_H
#define AD_RXMFCAPI_H 1
#pragma pack (push, 8)

// AutoCAD WM_ACAD_KEEPFOCUS
// Create custom window message.  This message is used by the OnIdle
// handler to test if a top-level window will relinquish focus.  If
// a window handles this message and does not want to lose focus then
// it should return a TRUE result.
//   lParam & wParam not used
//   Return 1 to maintain focus else 0 if focus can be shifted.
#ifndef WM_ACAD_KEEPFOCUS
#define WM_ACAD_KEEPFOCUS  (WM_USER+0x6D01)
#endif // WM_ACAD_KEEPFOCUS

class AcDbDatabase;
class AcApStatusBar;
class CDialogBar;
class AdApplicationFrame;

//////////////////////////
// AutoCAD Window pointers
//////////////////////////
// The pointer to a window or a frame should be used only when the
// ARX apps share the SAME MFC DLL with AutoCAD.
// In some cases, when using static MFC or different MFC DLL,
// the window handle should be used instead.
//  instead of using
//      acedGetAcadDwgView()->UpdateWindow();
//      CMyDialog Mydia(acedGetAcadFrame());
//  use
//      ::UpdateWindow(acedGetAcadDwgView()->m_hWnd);
//      CMyDialog Mydia(CWnd::FromHandle(acedGetAcadFrame()->m_hWnd));
        
/* acedGetAcadWinApp
 * Returns the pointer to AutoCAD CWinApp object.
 */
CWinApp* acedGetAcadWinApp();

/* acedGetAcadDoc
 * Returns the pointer to AutoCAD CDocument object
 * There's only one document in AutoCAD.
 */
CDocument* acedGetAcadDoc();

/* acedGetAcadDwgView
 * Returns the pointer to AutoCAD CView object
 * There's only one Dwg view in AutoCAD.
 */
CView* acedGetAcadDwgView();

/* acedGetAcadFrame
 * Returns the pointer to AutoCAD CMDIFrameWnd object
 */
CMDIFrameWnd* acedGetAcadFrame();

/* acedGetAcadDockCmdLine
 * Returns the pointer to AutoCAD command line window
 */
CWnd* acedGetAcadDockCmdLine();

/* acedGetAcadTextCmdLine
 * Returns the pointer to AutoCAD Text window.
 */
CWnd* acedGetAcadTextCmdLine();

/* acedGetAcadResourceInstance()
 * Returns the Instance of AutoCAD's resource
 */
HINSTANCE acedGetAcadResourceInstance();


/* acedDwgPoint
 * used in acedCoordinate function :
 */
typedef double acedDwgPoint[3];

// AutoCAD coordinates and viewports

/* acedCoordFromPixelToWorld
 * Takes a coordinate in Window's coordinate (mouse coordinate)
 * and converts it to current viewport world coordinate
 */
void acedCoordFromPixelToWorld(const CPoint &ptIn, acedDwgPoint ptOut);

/* acedCoordFromPixelToWorld
 * Takes a coordinate in Windows' coordinate (mouse coordinate) and
 * a viewport number; and converts it to current viewport world coordinate
 */
BOOL acedCoordFromPixelToWorld(int windnum, CPoint ptIn, acedDwgPoint ptOut);

/* acedCoordFromWorldToPixel
 * Takes a coordinate in AutoCAD world coordinate and a viewport number; 
 * and converts it to Windows' coordinate.
 */
BOOL acedCoordFromWorldToPixel(int windnum, const acedDwgPoint ptIn, CPoint& ptOut);

/* acedGetWinNum
 * Takes a Windows' client coordinate and return the viewport number where 
 * the point is on
 * Returns 0 for no viewport, 1 if tilemode is off.
 * It's used with acedCoordFromWorldToPixel/acedCoordFromPixelToWorld
 */
int acedGetWinNum(int ptx, int pty);

// Progress Bar API

/* acedSetStatusBarProgressMeter
 * Creates a progress meter on AutoCAD status bar.
 * Returns 0 if it successfully creates the label and progress meter. 
 * Otherwise -1
 */
int acedSetStatusBarProgressMeter(const ACHAR* pszLabel, int nMinPos, 
                                  int nMaxPos);
/* acedSetStatusBarProgressMeter
 * Call this with a positive value within the range specified to set 
 * the current position of the status bar.  
 * Pass a negative number to add an amount to the current position (relative).
 */
int acedSetStatusBarProgressMeterPos(int nPos);

/* acedRestoreStatusBar
 * Resets AutoCAD status bar
 */
void acedRestoreStatusBar();

// Define callback function for apps that want windows messages
typedef void (* AcedWatchWinMsgFn)(const MSG*);
typedef BOOL (* AcedFilterWinMsgFn)(MSG*);
typedef void (* AcedOnIdleMsgFn) ();
typedef void (* AcedOnModalFn) (bool bModal);

// Windows messages hooks
/* Register a filter message hook into AutoCAD's Windows message loop.
 * The message passed to your application can be changed and can be blocked out.
 * If the function returns TRUE, the message WON'T be passed to other hook 
 * functions or AutoCAD at all. The message is terminated.
 * Returns TRUE if successfully registers the hook. Otherwise FALSE.
 */
BOOL acedRegisterFilterWinMsg(const AcedFilterWinMsgFn pfn);

/* acedRemoveFilterWinMsg
 * Takes a message hook function pointer and remove it 
 * Returns TRUE if successfully registers the hook. Otherwise FALSE.
 */
BOOL acedRemoveFilterWinMsg(const AcedFilterWinMsgFn pfn); 

/* acedRegisterWatchWinMsg
 * Register a hook function into AutoCAD message loop. 
 * The function can only look up AutoCAD's Windows message.
 * It can't  change or block message.
 * Returns TRUE if successfully registers the hook. Otherwise FALSE.
 */
BOOL acedRegisterWatchWinMsg(const AcedWatchWinMsgFn pfn);

/* acedRemoveWatchWinMsg
 * Takes a message hook function pointer and remove it 
 * Returns TRUE if successfully registers the hook. Otherwise FALSE.
 * 
 */
BOOL acedRemoveWatchWinMsg(const AcedWatchWinMsgFn pfn); 

/* acedRegisterOnIdleWinMsg
 * Register a hook function to be notified when AutoCAD is on idle 
 * Returns TRUE if successfully registers the hook. Otherwise FALSE.
 */
BOOL acedRegisterOnIdleWinMsg(const AcedOnIdleMsgFn pfn);

/* acedRemoveOnIdleWinMsg
 * Takes a message on idle hook function pointer and remove it 
 * Returns TRUE if successfully registers the hook. Otherwise FALSE.
 * 
 */
BOOL acedRemoveOnIdleWinMsg(const AcedOnIdleMsgFn pfn); 


/* acedRegisterOnModal
 * Register a hook function to be notified when AutoCAD displays a modal dialog.
 * Returns TRUE if successfully registers the hook. Otherwise FALSE.
 */
BOOL acedRegisterOnModal(const AcedOnModalFn pfn);

/* acedRemoveOnModal
 * Takes a hook function pointer and removes it
 * Returns TRUE if successfully registers the hook. Otherwise FALSE.
 * 
 */
BOOL acedRemoveOnModal(const AcedOnModalFn pfn); 

struct AcColorSettings {

    /* Solid background color for various contexts */
    DWORD dwGfxModelBkColor;    
    DWORD dwGfxLayoutBkColor;
    DWORD dwParallelBkColor;
    DWORD dwBEditBkColor;
    DWORD dwCmdLineBkColor;
    DWORD dwPlotPrevBkColor;

    /* Background color for 3D perspective projection */
    DWORD dwSkyGradientZenithColor;
    DWORD dwSkyGradientHorizonColor;
    DWORD dwGroundGradientOriginColor;
    DWORD dwGroundGradientHorizonColor;
    DWORD dwEarthGradientAzimuthColor; 
    DWORD dwEarthGradientHorizonColor;

    /* Crosshair color for various contexts */
    DWORD dwModelCrossHairColor;
    DWORD dwLayoutCrossHairColor;
    DWORD dwParallelCrossHairColor;
    DWORD dwPerspectiveCrossHairColor;
    DWORD dwBEditCrossHairColor;

    /* Ground plane grid major lines for various contexts */
    DWORD dwParallelGridMajorLines;
    DWORD dwPerspectiveGridMajorLines;

    /* Ground plane grid minor lines for various contexts */
    DWORD dwParallelGridMinorLines;
    DWORD dwPerspectiveGridMinorLines;

    /* Ground plane grid axis lines for various contexts */
    DWORD dwParallelGridAxisLines;
    DWORD dwPerspectiveGridAxisLines;

    /* Text window color */
    DWORD dwTextForeColor, dwTextBkColor;

    /* Command line text color */
    DWORD dwCmdLineForeColor;

    /* AutoTrack vector color for various contexts */
    // Note: dwAutoTrackingVecColor indicates autotrack vector color in model space.
    // We didn't change its name to dwModelATrackVecColor because that might break
    // existing arx app.
    DWORD dwAutoTrackingVecColor;
    DWORD dwLayoutATrackVecColor;
    DWORD dwParallelATrackVecColor;
    DWORD dwPerspectiveATrackVecColor;
    DWORD dwBEditATrackVecColor;

    /* Autosnap Marker color for various contexts */
    DWORD dwModelASnapMarkerColor;
    DWORD dwLayoutASnapMarkerColor;
    DWORD dwParallelASnapMarkerColor;
    DWORD dwPerspectiveASnapMarkerColor;
    DWORD dwBEditASnapMarkerColor;
    
    /* Drafting Tool tip color for various contexts */
    DWORD dwModelDftingTooltipColor;
    DWORD dwLayoutDftingTooltipColor;
    DWORD dwParallelDftingTooltipColor;
    DWORD dwPerspectiveDftingTooltipColor;
    DWORD dwBEditDftingTooltipColor;
        
    /* Drafting Tool tip background color for various contexts */    
    DWORD dwModelDftingTooltipBkColor;
    DWORD dwLayoutDftingTooltipBkColor;
    DWORD dwParallelDftingTooltipBkColor;
    DWORD dwPerspectiveDftingTooltipBkColor;
    DWORD dwBEditDftingTooltipBkColor;

    /* Light glyphs color for various contexts */
    DWORD dwModelLightGlyphs;
    DWORD dwLayoutLightGlyphs;
    DWORD dwParallelLightGlyphs;
    DWORD dwPerspectiveLightGlyphs;
    DWORD dwBEditLightGlyphs;

    /* Light Hotspot color for various contexts */
    DWORD dwModelLightHotspot;
    DWORD dwLayoutLightHotspot;
    DWORD dwParallelLightHotspot;
    DWORD dwPerspectiveLightHotspot;
    DWORD dwBEditLightHotspot;

    /* Light Falloff color for various contexts */
    DWORD dwModelLightFalloff;
    DWORD dwLayoutLightFalloff;
    DWORD dwParallelLightFalloff;
    DWORD dwPerspectiveLightFalloff;
    DWORD dwBEditLightFalloff;

    /* Light start limit color for various contexts */
    DWORD dwModelLightStartLimit;
    DWORD dwLayoutLightStartLimit;
    DWORD dwParallelLightStartLimit;
    DWORD dwPerspectiveLightStartLimit;
    DWORD dwBEditLightStartLimit;

    /* Light end limit color for various contexts */
    DWORD dwModelLightEndLimit;
    DWORD dwLayoutLightEndLimit;
    DWORD dwParallelLightEndLimit;
    DWORD dwPerspectiveLightEndLimit;
    DWORD dwBEditLightEndLimit;

    /* Camera glyphs color for various contexts */
    DWORD dwModelCameraGlyphs;
    DWORD dwLayoutCameraGlyphs;
    DWORD dwParallelCameraGlyphs;
    DWORD dwPerspectiveCameraGlyphs;

    /* Camera frustrum plane color for various contexts */
    DWORD dwModelCameraFrustrum;
    DWORD dwLayoutCameraFrustrum;
    DWORD dwParallelCameraFrustrum;
    DWORD dwPerspectiveCameraFrustrum;

    /* Camera clipping plane color for various contexts */
    DWORD dwModelCameraClipping;
    DWORD dwLayoutCameraClipping;
    DWORD dwParallelCameraClipping;
    DWORD dwPerspectiveCameraClipping;

    /* Flags - set if true */

    /* Flags for use tint X, Y, Z for crosshair */
    int nModelCrosshairUseTintXYZ;
    int nLayoutCrosshairUseTintXYZ;
    int nParallelCrosshairUseTintXYZ;
    int nPerspectiveCrosshairUseTintXYZ;
    int nBEditCrossHairUseTintXYZ;

    /* Flags for use tint X, Y, Z for AutoTrack Vector */
    int nModelATrackVecUseTintXYZ;
    int nLayoutATrackVecUseTintXYZ;
    int nParallelATrackVecUseTintXYZ;
    int nPerspectiveATrackVecUseTintXYZ;
    int nBEditATrackVecUseTintXYZ;

    /* Flags for use tint X, Y, Z for Drafting Tooltip Bk tint */
    int nModelDftingTooltipBkUseTintXYZ;
    int nLayoutDftingTooltipBkUseTintXYZ;
    int nParallelDftingTooltipBkUseTintXYZ;
    int nPerspectiveDftingTooltipBkUseTintXYZ;
    int nBEditDftingTooltipBkUseTintXYZ;

    /* Flags for use tint X, Y, Z for Ground plane grid major lines */
    int nParallelGridMajorLineTintXYZ;
    int nPerspectiveGridMajorLineTintXYZ;

    /* Flags for use tint X, Y, Z for Ground plane grid minor lines */
    int nParallelGridMinorLineTintXYZ;
    int nPerspectiveGridMinorLineTintXYZ;

    /* Flags for use tint X, Y, Z for Ground plane grid axis lines */
    int nParallelGridAxisLineTintXYZ;
    int nPerspectiveGridAxisLineTintXYZ;
};

// AutoCAD windows' colors
BOOL acedGetCurrentColors(AcColorSettings* pColorSettings);
BOOL acedSetCurrentColors(AcColorSettings* pColorSettings);
BOOL acedGetSystemColors(AcColorSettings* pColorSettings);

// AutoCAD MDI Child Window Frame settings
typedef struct tagChildFrmSettings {
    // More to come later
    AcColorSettings m_ColorSettings;
    bool m_bShowLayoutBar;
    bool m_bShowScrollBar;
    CDialogBar *m_pDialogBar;
    bool m_bIsBedit;
} AcChildFrmSettings;

BOOL acedGetChildFrameSettings(AcChildFrmSettings* pChildFrmSettings,
    CMDIChildWnd *pWnd);
BOOL acedSetChildFrameSettings(AcChildFrmSettings* pChildFrmSettings,
    CMDIChildWnd *pWnd);


// Custom Drag and Drop
// In order to enable custom drag&drop, you have to 
// #define _ARX_CUSTOM_DRAG_N_DROP_
// before including this header file, and you need to include <afxole.h> also.
#ifdef _ARX_CUSTOM_DRAG_N_DROP_
/* acedRegisterCustomDropTarget
 * Registers a new IDroptarget to the AutoCAD's drawing window. 
 * Only one IDropTarget can be registered at one moment.
 * AutoCAD's default Drag & Drop handling capabilities are not available 
 * until the IDroptarget is revoke.
 * This is replaced by acedStartOverrideDropTarget(). It will be removed
 * in next release.
 */
BOOL acedRegisterCustomDropTarget(IDropTarget* pItarget);
BOOL acedStartOverrideDropTarget(COleDropTarget* pTarget);

/* acedRevokeCustomDropTarget
 * Revokes the previously set IDroptarget. 
 * The default AutoCAD's handling of Drag&Drop event is restored.
 * This is replaced by acedRemoveDropTarget(). It will be removed
 * in next release.
 */
BOOL acedRevokeCustomDropTarget();
BOOL acedEndOverrideDropTarget(COleDropTarget* pTarget);

/* acedAddDropTarget
 * Add a hook to participate in DragDrop Event started not from
 * 3rd party ARX app.
 */
BOOL acedAddDropTarget(COleDropTarget* pTarget);

/* acedRemoveDropTarget
 * Remove the hook to AutoCAD DragDrop event.
 */
BOOL acedRemoveDropTarget(COleDropTarget* pTarget);

#endif // _ARX_CUSTOM_DRAG_N_DROP_

// Get Database correpont to on AutoCAD Drawing Window.
AcDbDatabase* AcApGetDatabase(CView *pView);


// AutoCAD company name for registry access.  For all except AutoCAD
// OEM, this will return "Autodesk".  For AutoCAD OEM, it is at the
// discretion of the AutoCAD OEM developer, via an entry in aoemres2.rc,
// to specify the company name for use in registry accesses.
const CString& acedGetRegistryCompany();

// Register the fact that the application with name "szAppName"
// may want to add a tab to the tabbed dialog named "szDialogName".
// This function creates the key necessary to register the added
// tab(s) if it is not there. Returns TRUE on success.
BOOL acedRegisterExtendedTab(LPCTSTR szAppName, LPCTSTR szDialogName);

// Return an HMENU given a .MNU file alias.
HMENU acedGetMenu(LPCTSTR pszAlias);

// This routine is exported primarily for use by AcUi. The routine is called
// from a dialog to determine if input is queued after an interactive command
// has been cancelled. Generally, if there's no input queued then the dialog
// will be restored, otherwise the dialog will terminate and allow the queued
// commands to be processed.
BOOL acedIsInputPending ();

BOOL acedSetIUnknownForCurrentCommand(const LPUNKNOWN);
BOOL acedGetIUnknownForCurrentCommand(LPUNKNOWN &pUnk);

/* acedGetApplicationStatusBar
 * Returns the pointer to AutoCAD Application Status Bar.
 */
AcApStatusBar* acedGetApplicationStatusBar();

/* acedShowDrawingStatusBars
 * Shows or hides the drawing status bars.
 */
BOOL acedShowDrawingStatusBars(BOOL bShow = TRUE);

/* acedDrawingStatusBarsVisible
 * Returns TRUE if the drawing status bar are visible
 * in AutoCAD, otherwise FALSE.
 */
BOOL acedDrawingStatusBarsVisible();

/* acedRegisterStatusBarMenuItem
 * Returns TRUE if the status bar item is successfully
 * registered in AutoCAD, otherwise FALSE.
 */
BOOL acedRegisterStatusBarMenuItem(AcStatusBarMenuItem* pItem,
                                   AcStatusBarMenuItem::AcStatusBarType nType);

/* acedUnregisterStatusBarMenuItem
 * Returns TRUE if the status bar item is successfully
 * unregistered in AutoCAD, otherwise FALSE.
 */
BOOL acedUnregisterStatusBarMenuItem(AcStatusBarMenuItem* pItem,
                                     AcStatusBarMenuItem::AcStatusBarType nType);

/* acedSetStatusBarPaneId
 * Sets the id of the given status bar pane.  Returns TRUE if
 * successful, otherwise FALSE.
 */
BOOL acedSetStatusBarPaneID(AcPane* pPane,
                            AcStatusBarMenuItem::AcStatusBarType nType,
                            int nID);

// More color settings.
struct AcColorSettingsEx
{
    // Light Web color for various contexts 
    DWORD dwModelLightWeb;
    DWORD dwLayoutLightWeb;
    DWORD dwParallelLightWeb;
    DWORD dwPerspectiveLightWeb;
    DWORD dwBEditLightWeb;

    // Light Web(missingfile) color for various contexts
    DWORD dwModelLightWebMissingFile;
    DWORD dwLayoutLightWebMissingFile;
    DWORD dwParallelLightWebMissingFile;
    DWORD dwPerspectiveLightWebMissingFile;
    DWORD dwBEditLightWebMissingFile;

    // Light Web shape(extend source) color for various contexts
    DWORD dwModelLightWebShape;
    DWORD dwLayoutLightWebShape;
    DWORD dwParallelLightWebShape;
    DWORD dwPerspectiveLightWebShape;
    DWORD dwBEditLightWebShape;

    // Light Web lux at distance color for various contexts
    DWORD dwModelLightWebLuxAtDist;
    DWORD dwLayoutLightWebLuxAtDist;
    DWORD dwParallelLightWebLuxAtDist;
    DWORD dwPerspectiveLightWebLuxAtDist;
    DWORD dwBEditLightWebLuxAtDist;

    /* Block editor constraints colors */
    DWORD dwBEditUnconstrainedColor;
    DWORD dwBEditPartiallyConstrainedColor;
    DWORD dwBEditFullyConstrainedColor;
    DWORD dwBEditOverConstrainedColor;
};

// AutoCAD windows' colors
BOOL acedGetCurrentColorsEx(AcColorSettings* pColorSettings, 
                           AcColorSettingsEx* pColorSettingsEx);

BOOL acedSetCurrentColorsEx(AcColorSettings* pColorSettings, 
                           AcColorSettingsEx* pColorSettingsEx);

BOOL acedGetSystemColorsEx(AcColorSettings* pColorSettings, 
                          AcColorSettingsEx* pColorSettingsEx);

// Controls whether or not file open adds the filename to the 'File' MRU list.
void acedSuppressFileMRU(bool bSuppress);

// acedGetApplicationFrame
// Returns the pointer to AutoCAD Application Frame.
AdApplicationFrame* acedGetApplicationFrame();

#pragma pack (pop)
#endif // AD_RXMFCAPI_H
