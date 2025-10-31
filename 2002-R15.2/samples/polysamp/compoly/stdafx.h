// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
// (C) Copyright 1998 by Autodesk, Inc.
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__45C7F02C_CD9A_11D1_A2BD_080009DC639A__INCLUDED_)
#define AFX_STDAFX_H__45C7F02C_CD9A_11D1_A2BD_080009DC639A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if defined(_DEBUG) && !defined(_DEBUG_AUTOCAD)
#define _DEBUG_WAS_DEFINED
#undef _DEBUG
#endif 

#define STRICT

#ifdef _DEBUG
    #define _ATL_DEBUG_QI
    #define _ATL_DEBUG_REFCOUNT
#endif

#define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED


#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

#include "acad15.h"
#include "dbmain.h"
#include "dbents.h"
#include "dbsymtb.h"
#include "dbobjptr.h"
#include "rxregsvc.h"

#if defined(_DEBUG_WAS_DEFINED)
#undef _DEBUG_WAS_DEFINED
#define _DEBUG
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__45C7F02C_CD9A_11D1_A2BD_080009DC639A__INCLUDED)
