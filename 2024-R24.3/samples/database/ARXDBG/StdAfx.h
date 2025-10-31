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
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
    #pragma message("Building debug version of this module to be used with non-debug/Prod AutoCAD")
    #define DEBUG_THIS_ONLY
    #undef _DEBUG
#endif

#pragma warning(disable: 4275)

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC OLE automation classes
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>            // MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#pragma warning(push)
#pragma warning(disable:4265)//disable missing virtual destructor warning
#include <afxdao.h>         // MFC DAO database classes
#pragma warning(pop) // C4265
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>            // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <math.h>
#include "AcadStdafx.h"

// Turn on the _DEBUG symbol if it was defined, before including
// non-MFC header files.
//
#ifdef DEBUG_THIS_ONLY
    #define _DEBUG
    #undef DEBUG_THIS_ONLY
#endif

inline bool
intToBool(int intBoolVal)
{
    return (intBoolVal == 0) ? false : true;
}

inline int
boolToInt(bool boolVal)
{
    return (boolVal == false) ? 0 : 1;
}

#include "Ac64BitHelpers.h"




