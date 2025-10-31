//////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1994-2008 by Autodesk, Inc.
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

#ifndef _adui_h
#define _adui_h

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// Note: _ADUI_BUILD should be defined only when building the DLL.

#ifdef  _ADUI_BUILD
#  define   ADUI_PORT  __declspec(dllexport)
#else
#  define   ADUI_PORT  __declspec(dllimport)
#endif

class ADUI_PORT CAdUiThemeManager;    // INTERNAL USE ONLY

/////////////////////////////////////////////////////////////////////////////
// Initialize the extension DLL, register the classes, etc
// Call this exported function from your Dll or Executable once
// - an ideal location is the InitInstance() member function 

void ADUI_PORT InitAdUiDLL();

// This function shows an alert type dialog with three buttons. Caption
// string and text for each button are arguments along with a default button
// 0 based index. Returns 0 based button index or -1 on CANCEL. Button 2
// is always the CANCEL button.
int  ADUI_PORT AdUiAlertDialog (
    LPCTSTR captionText,
    LPCTSTR msg0Text,
    LPCTSTR button0Text,                      
    LPCTSTR button1Text,
    UINT defButton = 0          // Means first button is default.
);

int  ADUI_PORT AdUiDataValidationLevel ();      // INTERNAL USE ONLY

// Helper function to expand a help file name into a fully-qualified pathname.
BOOL ADUI_PORT AdUiFindContextHelpFullPath (
    LPCTSTR fileName, CString& fullPath
);

void ADUI_PORT AdUiSubstituteShellFont (CWnd& dlg, CFont& font);
CAdUiThemeManager ADUI_PORT * AdUiGetThemeManager();  // INTERNAL USE ONLY

// This function finds a suitable parent window for a dialog when none is
// explicitly supplied. The algorithm obtains the active window 
// (using GetActiveWindow) and the walks the parent hierarchy (using GetParent)
// A disabled window or the main window terminates the walk.
HWND ADUI_PORT AdUiGetSafeParentHwnd();
ADUI_PORT CWnd* AdUiGetSafeParentWnd();

/////////////////////////////////////////////////////////////////////////////
// Class prototypes

class ADUI_PORT CAdUiBaseDialog;
class ADUI_PORT CAdUiComboBox;
class ADUI_PORT CAdUiDialog;
class ADUI_PORT CAdUiDialogBar;
class ADUI_PORT CAdUiFileDialog;
class ADUI_PORT CAdUiTab;
class ADUI_PORT CAdUiTabChildDialog;
class ADUI_PORT CAdUiTabExtensionManager;
class ADUI_PORT CAdUiTabMainDialog;
class ADUI_PORT CAdUiDialogWorksheet;  // INTERNAL USE ONLY
class ADUI_PORT CAdUiDropTarget;
class ADUI_PORT CAdUiTheme;            // INTERNAL USE ONLY
class ADUI_PORT CAdUiPalette;
class ADUI_PORT CAdUiPaletteSet;
class ADUI_PORT CAdUiThemeMgrReactor;  // INTERNAL USE ONLY
class ADUI_PORT CAduiLabelEdit;  // INTERNAL USE ONLY

/////////////////////////////////////////////////////////////////////////////

#define MOVEX               0x00001
#define MOVEY               0x00002
#define MOVEXY              0x00003
#define ELASTICX            0x00010
#define ELASTICY            0x00020
#define ELASTICXY           0x00030

#pragma pack (push, 8)
typedef struct _dlgControlTag {
    DWORD       id;
    DWORD       flags;
    DWORD       pct;
} DLGCTLINFO, *PDLGCTLINFO;
#pragma pack (pop)


// For Internal use
//
namespace AdUi
{
    enum AdUiIconMode{
        kSmall = 0,
        kLarge
    };

    enum AdUiImage
    {
        kImageSmall      = 1,
        kImageLarge      = 2,

        kImageEnable     = 4,
        kImageDisable    = 8,
    };

}; 



/////////////////////////////////////////////////////////////////////////////

// WINREG.H declares HKEY, needed by aduiRegistryAccess.h
#include <winreg.h>

//// AFXOLE.H declares COleDropTarget needed by aduiDropTarget.h
#include <afxole.h>

#include "aduiRegistryAccess.h"

#include "aduiMessage.h"
#include "aduiDropTarget.h"
#include "aduiTabExtension.h"
#include "aduiTextTip.h"
#include "aduiButton.h"
#include "aduiTabCtrl.h"

#include "aduiBaseDialog.h"
#include "aduiDialog.h"
#include "aduiDialogBar.h"
#include "aduiFileDialog.h"
#include "aduiTabChildDialog.h"
#include "aduiTabMainDialog.h"

#include "aduiEdit.h"
#include "aduiHeaderCtrl.h"
#include "aduiListBox.h"
#include "aduiListCtrl.h"
#include "aduiComboBox.h"

#include "aduiDock.h"

#include "aduiVolumeDescriptor.h"
#include "aduiPathname.h"
#include "aduiPalette.h"
#include "aduiPaletteSet.h"

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif

//////////////////////////////////////////////////////////////////////////////
