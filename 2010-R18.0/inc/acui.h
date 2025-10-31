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

#ifndef _acui_h
#define _acui_h

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// Note: _ACUI_BUILD should be defined only when building the DLL.

#ifdef  _ACUI_BUILD
#  define   ACUI_PORT  __declspec(dllexport)
#else
#  define   ACUI_PORT  __declspec(dllimport)
#endif

/////////////////////////////////////////////////////////////////////////////
// Initialize the extension DLL, register the classes, etc
// Call this exported function from your Dll or Executable once
// - an ideal location is the InitInstance() member function 

ACUI_PORT void InitAcUiDLL();

/////////////////////////////////////////////////////////////////////////////

ACUI_PORT HINSTANCE AcUiAppResourceInstance ();
ACUI_PORT LPCTSTR AcUiContextHelpFileName();
ACUI_PORT BOOL AcUiEnableToolTips ();
ACUI_PORT BOOL AcUiFindContextHelpFullPath (
    LPCTSTR fileName, CString& fullPath
);
ACUI_PORT BOOL AcUiIsInputPending ();
ACUI_PORT CWnd * AcUiMainWindow ();
ACUI_PORT void AcUiRootKey (CString& rootKey);

#include "acuiButton.h"
#include "acuiDialogWorksheet.h"
#include "acuiDialog.h"
#include "acuiTabCtrl.h"

typedef CAdUiRegistryAccess         CAcUiRegistryAccess;
typedef CAdUiRegistryDeleteAccess   CAcUiRegistryDeleteAccess;
typedef CAdUiRegistryWriteAccess    CAcUiRegistryWriteAccess;
typedef CAcUiTabChildDialog         CAcUiTabExtension;

/////////////////////////////////////////////////////////////////////////////

#include "aced.h"

#include "acuiDock.h"
#include "acuiEdit.h"
#include "acuiHeaderCtrl.h"
#include "acuiListBox.h"
#include "acuiListCtrl.h"
#include "acuiComboBox.h"
#include "acuiString.h"
#include "acuiPathname.h"
#include "acuiNavDialog.h"
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif

//////////////////////////////////////////////////////////////////////////////
