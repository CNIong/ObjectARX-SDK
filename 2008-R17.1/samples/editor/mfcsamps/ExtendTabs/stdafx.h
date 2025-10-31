// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
// (C) Copyright 1998-2006 by Autodesk, Inc.
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__3BB6F2C7_6373_11D2_B731_0080C72A6EDF__INCLUDED_)
#define AFX_STDAFX_H__3BB6F2C7_6373_11D2_B731_0080C72A6EDF__INCLUDED_

	#if defined(_DEBUG) && !defined(DEBUG_THIS_ONLY)
	#define DEBUG_THIS_ONLY
	#undef _DEBUG
	#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef WINVER
#define WINVER 0x500
#endif

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxdllx.h>

	#ifdef DEBUG_THIS_ONLY
	#undef DEBUG_THIS_ONLY
	#define _DEBUG
	#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__3BB6F2C7_6373_11D2_B731_0080C72A6EDF__INCLUDED_)
