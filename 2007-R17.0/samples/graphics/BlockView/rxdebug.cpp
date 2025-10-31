#include "StdAfx.h"
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
//#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#ifdef _DEBUG

#include "rxdebug.h"



#ifndef _WINBASE_
//extracted from winbase.h so that
//we don't have to pull in the whole
//header
extern "C"
void
_stdcall
OutputDebugStringA(
    const TCHAR* lpOutputString
    );

extern "C"
void
_stdcall
OutputDebugStringW(
    const unsigned short* lpOutputString
    );
#ifdef UNICODE
#define OutputDebugString  OutputDebugStringW
#else
#define OutputDebugString  OutputDebugStringA
#endif // !UNICODE

#endif //_WINBASE

//VC8:resolved the redefinition error, macro is already defined in stdlib.h
#ifdef _countof
#undef _countof
#endif 

// determine number of elements in an array (not bytes)
#define _countof(array) (sizeof(array)/sizeof(array[0]))

inline void _cdecl RxTrace(const TCHAR* lpszFormat, ...)
{
    va_list args;
    va_start(args, lpszFormat);
    int nBuf;
    TCHAR szBuffer[512];
    nBuf = _vsnwprintf_s(szBuffer, _countof(szBuffer), lpszFormat, args);
    // was there an error?
    RXASSERT(nBuf >= 0);
    ::OutputDebugString(szBuffer);
    va_end(args);
}

#endif //_DEBUG, entire file
