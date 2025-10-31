//  Copyright 2016 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form
//
//Description:
//Shim header to provide trivial emulation of C 11 Annex K functions on platforms
//that do not support it.
//
#pragma once

#define __STDC_WANT_LIB_EXT1__ 1
#include <wchar.h>
#include <string.h>

#if defined(__STDC_LIB_EXT1__) || defined(_MSC_VER) && !defined(_ADESK_MAC_)
//Visual C++ 2015 provides these functions
//other platforms could use https://code.google.com/p/slibc/
//
//this branch is empty on purpose
//
#elif defined (_ADESK_MAC_)
// mac already emulates these
#include <assert.h>
#include "ms_crtdef.h"
#include "ms_new.h" 
#include "ms_string.h"
#include "ms_tchar.h"
#include "ms_stdio.h"
#include "ms_math.h"
#include <ctime>
//use MSVC signature instead of standard. The standard looks like this:
//struct tm *gmtime_s(const time_t * restrict timer,struct tm * restrict result);
inline int gmtime_s(std::tm* st, const std::time_t*timer)
{
    return gmtime_r(timer, st) != nullptr ? 0 : 1;
}
#else
#include <stdarg.h>
#include <ctime>
typedef int errno_t;
typedef size_t rsize_t;
inline errno_t memcpy_s(void * s1, rsize_t s1max, const void * s2, rsize_t n)
{
    memcpy(s1, s2, n);
    return 0;
}
inline errno_t memmove_s(void *s1, rsize_t s1max, const void *s2, rsize_t n)
{
    memmove(s1, s2, n);
    return 0;
}
inline errno_t strcpy_s(char * s1, rsize_t s1max, const char * s2)
{
    strcpy(s1, s2);
    return 0;
}
inline errno_t wcscpy_s(wchar_t * s1, rsize_t s1max, const wchar_t * s2)
{
    wcscpy(s1, s2);
    return 0;
}
inline errno_t wcscat_s(wchar_t * s1, rsize_t s1max, const wchar_t * s2)
{
    wcscat(s1, s2);
    return 0;
}
inline int swprintf_s(wchar_t * s, rsize_t n, const wchar_t * format, ...)
{
    va_list args;
    va_start(args, format);
    return vswprintf(s, n, format, args);
}
inline int swscanf_s(const wchar_t * s, const wchar_t * format, ...)
{
    va_list args;
    va_start(args, format);
    return vswscanf(s, format, args);
}
//we omit the s1max parameter to match the non-standard MSVC signature. -szilvaa 7/1/2015
inline wchar_t *wcstok_s(wchar_t * s1, /*rsize_t * s1max,*/ const wchar_t * s2, wchar_t ** ptr)
{
    return wcstok(s1, s2, ptr);
}
//use MSVC signature instead of standard. The standard looks like this:
//struct tm *gmtime_s(const time_t * restrict timer,struct tm * restrict result);
inline errno_t gmtime_s(std::tm* st, const std::time_t* timer)
{
    return gmtime_r(timer, st) != nullptr ? 0 : 1;
}
inline int localtime_s(std::tm* st, const std::time_t* timer)
{
    // Emscripten does not support localtime_s
    return localtime_r(timer, st) != nullptr ? 0 : 1;
}
#endif
