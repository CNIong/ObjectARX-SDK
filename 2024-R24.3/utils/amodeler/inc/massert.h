///////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form. 
//
// DESCRIPTION:
//
// Our own assert function. We can set a break point inside the assertFunction
// so that the execution will stop just before the assertion kills the process 
// and we can investigate all variables at that point. We can also choose not 
// to kill the process at that time.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_MASSERT_H
#define AMODELER_INC_MASSERT_H


#include <tchar.h>

AMODELER_NAMESPACE_BEGIN


#ifdef _DEBUG

#define MASSERT(x) AMODELER_NAMESPACE::assertFunction(x, _T(__FILE__), __LINE__, _T(#x))
#define FAIL       AMODELER_NAMESPACE::assertFunction(0, _T(__FILE__), __LINE__, _T("FAIL"))

#else

#define MASSERT(x)
#define FAIL
#endif


DllImpExp extern void assertFunction(int ex, const wchar_t* file, int line, const wchar_t* str = 0);


AMODELER_NAMESPACE_END
#endif






