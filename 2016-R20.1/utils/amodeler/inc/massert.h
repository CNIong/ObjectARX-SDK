///////////////////////////////////////////////////////////////////////////////
//
// © Autodesk, Inc. 1998-2010. All rights reserved.
//
// The information contained herein is confidential, proprietary
// to Autodesk,  Inc.,  and considered a trade secret as defined
// in section 499C of the penal code of the State of California.
// Use of  this information  by  anyone  other  than  authorized
// employees of Autodesk, Inc.  is granted  only under a written
// non-disclosure agreement,  expressly  prescribing  the  scope
// and manner of such use.
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






