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


// Check if the build is DEBUG version and it's intended
// to be used with Non-DEBUG AutoCAD.
// In this case, for MFC header files, we need to undefine
// _DEBUG symbol
// Read this project readme.txt for more detail
 #if defined( _DEBUG) && !defined(DEBUG_AUTOCAD)
    #pragma message("Building debug version of dynamic.arx to be used with non-debug/Prod AutoCAD")
    #define _DEBUG_WAS_DEFINED
    #undef _DEBUG
#endif

#ifndef WINVER
#define WINVER 0x601
#endif

#include <afxwin.h>
#include "modal.h"

#ifdef _DEBUG_WAS_DEFINED
    #define _DEBUG
    #undef _DEBUG_WAS_DEFINED
#endif
