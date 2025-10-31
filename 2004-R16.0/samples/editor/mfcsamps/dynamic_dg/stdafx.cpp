// stdafx.cpp : source file that includes just the standard includes
//	MFCTemplate.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

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

#include "stdafx.h"

#ifdef _DEBUG_WAS_DEFINED
    #define _DEBUG
    #undef _DEBUG_WAS_DEFINED
#endif
