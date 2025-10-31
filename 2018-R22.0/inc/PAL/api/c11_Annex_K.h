//  Copyright 2017 Autodesk, Inc.  All rights reserved.
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
#include "mini_adpcore.h"
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
#include <cstdlib>
#include <stdio.h>
#include <type_traits>

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

template<size_t N> errno_t wcscpy_s(wchar_t(&s1)[N], const wchar_t * s2)
{
    return wcscpy_s(s1, N, s2);
}

inline errno_t wcsncpy_s(wchar_t* s1, rsize_t s1Size, const wchar_t* s2, rsize_t s2Num)
{
    wcsncpy(s1, s2, s2Num);
    return 0;
}

template<size_t N> errno_t wcsncpy_s(wchar_t(&s1)[N], const wchar_t * s2, rsize_t s2Num)
{
    wcsncpy(s1, s2, s2Num);
    return 0;
}

inline errno_t wcscat_s(wchar_t * s1, rsize_t s1max, const wchar_t * s2)
{
    wcscat(s1, s2);
    return 0;
}

inline errno_t wcsncat_s(wchar_t* s1, rsize_t s1Size, const wchar_t* s2, rsize_t s2Num)
{
    wcsncat(s1, s2, s2Num);
    return 0;
}

inline int sprintf_s(char* s, rsize_t n, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    int retVal = vsnprintf(s, n, format, args);
    va_end(args);
    return retVal;
}

inline int swprintf_s(wchar_t * s, rsize_t n, const wchar_t * format, ...)
{
    va_list args;
    va_start(args, format);
    int retVal =  vswprintf(s, n, format, args);
    va_end(args);
    return retVal;
}

template<size_t N> int swprintf_s(wchar_t(&s)[N], const wchar_t * format, ...)
{
    va_list args;
    va_start(args, format);
    int retVal =  vswprintf(s, N, format, args);
    va_end(args);
    return retVal;
}

template<size_t N> int vswprintf_s(wchar_t(&s)[N], const wchar_t* format, va_list args)
{
    return vswprintf(s, N, format, args);
}

inline int vswprintf_s(wchar_t* s, size_t N, const wchar_t* format, va_list args)
{
    return vswprintf(s, N, format, args);
}

class guard {};

template<bool condition>
struct condition_switch;

template <typename First, typename... Others>
int swscanf_helper(const wchar_t* buf, const wchar_t* format, First first, Others... others)
{
    return condition_switch<std::is_integral<First>::value>::work(buf, format, first, others...);
}

template <typename... Args>
int swscanf_helper(const wchar_t* buf, const wchar_t* format, guard, Args... args)
{
    return swscanf(buf, format, args...);
}

template<>
struct condition_switch<true>
{
    template <typename First, typename... Others>
    static int work(const wchar_t* buf, const wchar_t* format, First first, Others... others)
    {
        return swscanf_helper(buf, format, others...);
    }
};

template<>
struct condition_switch<false>
{
    template <typename First, typename... Others>
    static int work(const wchar_t* buf, const wchar_t* format, First first, Others... others)
    {
        return swscanf_helper(buf, format, others..., first);
    }
};

template <typename... Args>
int swscanf_s(const wchar_t* buf, const wchar_t* format, Args... args)
{
    // for swscanf_s, %c, %s, and %[ conversion specifiers each expect two arguments(buffer and buffer size)
    // on windows, if give swscanf_s a parameter of incorrect type, compiler will report warning
    // so it should be safe to filter all parameters of integral type, then pass the rest to swscanf
    return swscanf_helper(buf, format, args..., guard());
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
inline errno_t localtime_s(std::tm* st, const std::time_t* timer)
{
    // Emscripten does not support localtime_s
    return localtime_r(timer, st) != nullptr ? 0 : 1;
}

inline errno_t fopen_s(FILE**      _Stream,
    char const* _FileName,
    char const* _Mode)
{
    if (_Stream) {
        *_Stream = fopen(_FileName, _Mode);
    }
    return 0;
}
#endif
