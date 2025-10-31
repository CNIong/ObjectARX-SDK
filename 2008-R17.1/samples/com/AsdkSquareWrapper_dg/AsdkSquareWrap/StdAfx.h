// (C) Copyright 1999-2006 by Autodesk, Inc. 
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
#define WINVER 0x500
#endif

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
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
