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
// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently
#ifdef _DEBUG
#define WAS_DEBUG
#undef _DEBUG
#endif

#if !defined(AFX_STDAFX_H__800F70A4_6DE9_11D2_A7A6_0060B0872457__INCLUDED_)
#define AFX_STDAFX_H__800F70A4_6DE9_11D2_A7A6_0060B0872457__INCLUDED_

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

// Please ignore this in the future. AXBOILER.H will be fixed so this
// preprocessor definition is not required.
// #define _ATL_NO_UUIDOF // needed still for OPM.

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

#include "acadi.h"
#include "dbmain.h"
#include "dbents.h"
#include "dbsymtb.h"
#include "dbobjptr.h"
#include "rxregsvc.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__800F70A4_6DE9_11D2_A7A6_0060B0872457__INCLUDED)
#ifdef WAS_DEBUG
#define _DEBUG
#undef WAS_DEBUG
#endif
