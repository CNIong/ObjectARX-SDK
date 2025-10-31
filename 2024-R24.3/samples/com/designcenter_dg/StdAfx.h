//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__C5559132_A4EA_11D2_A7DA_0060B0872457__INCLUDED_)
#define AFX_STDAFX_H__C5559132_A4EA_11D2_A7DA_0060B0872457__INCLUDED_


#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#define WAS_DEBUG
#undef _DEBUG
#endif


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef WINVER
#define WINVER 0x601
#endif

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif
#define _ATL_APARTMENT_THREADED

#include <afxwin.h>
#include <afxdisp.h>

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

#include <atlwin.h> 

#ifdef DEBUG_WAS_DEFINED
#undef DEBUG_WAS_DEFINED
#define _DEBUG
#endif


// ObjectARX includes...
#include <adslib.h>
#include <dbmain.h>
#include <dbsymtb.h>
#include <dbmtext.h>
#include <acdocman.h>
#include <aced.h>
#include <rxregsvc.h>


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__C5559132_A4EA_11D2_A7DA_0060B0872457__INCLUDED)
