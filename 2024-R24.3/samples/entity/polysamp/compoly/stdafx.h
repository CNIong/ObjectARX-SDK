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

#if !defined(AFX_STDAFX_H__45C7F02C_CD9A_11D1_A2BD_080009DC639A__INCLUDED_)
#define AFX_STDAFX_H__45C7F02C_CD9A_11D1_A2BD_080009DC639A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef WINVER
#define WINVER 0x601
#endif

#define STRICT

#define _WIN32_WINNT 0x0601
#define _ATL_APARTMENT_THREADED


#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

#include "axdb.h"
#include "dbmain.h"
#include "dbents.h"
#include "dbsymtb.h"
#include "dbobjptr.h"
#include "rxregsvc.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__45C7F02C_CD9A_11D1_A2BD_080009DC639A__INCLUDED)

//- This line allows us to get rid of the .def file in ARX projects
#if !defined(_WIN64) && !defined (_AC64)
#pragma comment(linker, "/export:_acrxGetApiVersion,PRIVATE")
#else
#pragma comment(linker, "/export:acrxGetApiVersion,PRIVATE")
#endif


