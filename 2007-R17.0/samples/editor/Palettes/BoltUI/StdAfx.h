//
//
// (C) Copyright 2003-2006 by Autodesk, Inc. 
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
//
// StdAfx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__D985296F_4394_4D9B_A5A7_0198E6D5E00C__INCLUDED_)
#define AFX_STDAFX_H__D985296F_4394_4D9B_A5A7_0198E6D5E00C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef WINVER
#define WINVER 0x500
#endif

#pragma warning(disable: 4786)

#define PI 3.1415926535879793
#define PI2 6.28318530718

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

// 'DEBUG workaround' below prevents the MFC or ATL #include-s 
// from pulling in "afx.h" that would force the debug CRT through
// #pragma-s.

#if defined(_DEBUG) && !defined(_FULLDEBUG_)
#define _DEBUG_WAS_DEFINED
#undef _DEBUG
#pragma message ("     Compiling MFC header files in release mode.")
#endif
//-----------------------------------------------------------------------------

#include <afxwin.h>				//----- MFC core and standard components
#include <afxext.h>				//----- MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>				//----- MFC OLE classes
#include <afxodlgs.h>			//----- MFC OLE dialog classes
#include <afxdisp.h>			//----- MFC Automation classes
#endif //----- _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>				//----- MFC ODBC database classes
#endif //----- _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>				//----- MFC DAO database classes
#endif //----- _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>			//----- MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>				//----- MFC support for Windows Common Controls
#endif //----- _AFX_NO_AFXCMN_SUPPORT

//-----------------------------------------------------------------------------
#include <AtlBase.h>
#include <AtlCom.h>
#include "comutil.h"
using namespace ATL ;

// AutoCAD MFC Extensions:
#include "adui.h"
#include "acui.h"
#include "acuiComboBox.h"
#include "acuiDialog.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif

extern HINSTANCE _hdllInstance ;
#include "rxdebug.h"
// RX Includes
#include "axpnt3d.h"
#include "axpnt2d.h"
#include "acdb.h"               // acdb definitions
#include "rxregsvc.h"           // ARX linker
#include "dbapserv.h"           // Host application services
#include "aced.h"               // aced stuff
#include "adslib.h"             // RXADS definitions
#include "acdocman.h"           // MDI document manager
#include "AcExtensionModule.h"  // Utility class for extension dlls

#include "dbptrar.h"            // void pointer array        
#include "acadi.h"             // AutoCAD Automation interfaces
#include "axlock.h"             // Document locking class (no operation in ObjectDBX)
#include "axboiler.h"
#include "AcTc_i.h"
#include "axtempl.h"
#include "AcTc.h"
#include "clipdata.h"

#include "..\boltWrapper\boltWrapper.h"
#include "..\boltObject\asdkBolt.h"

#ifdef _FULLDEBUG_
#pragma message ("Warning! You should better not run this application in a Standard AutoCAD release.")
#pragma message ("         Due to the memory managment constraints.")
#endif

#endif // !defined(AFX_STDAFX_H__D985296F_4394_4D9B_A5A7_0198E6D5E00C__INCLUDED)
