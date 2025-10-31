// (C) Copyright 2005-2006 by Autodesk, Inc. 
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
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__8D69099A_556D_11D2_9F8D_000000000000__INCLUDED_)
#define AFX_STDAFX_H__8D69099A_556D_11D2_9F8D_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef WINVER
#define WINVER 0x500
#endif

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#if defined(_DEBUG) && !defined(_NONPROD)
#define _DEBUG_WAS_DEFINED
#undef _DEBUG
#endif

#include <afxwin.h>         // MFC core and standard components

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#if defined(_DEBUG_WAS_DEFINED)
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif

#endif // !defined(AFX_STDAFX_H__8D69099A_556D_11D2_9F8D_000000000000__INCLUDED_)
