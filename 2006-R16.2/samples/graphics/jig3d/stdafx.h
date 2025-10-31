// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__8D69099A_556D_11D2_9F8D_000000000000__INCLUDED_)
#define AFX_STDAFX_H__8D69099A_556D_11D2_9F8D_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
