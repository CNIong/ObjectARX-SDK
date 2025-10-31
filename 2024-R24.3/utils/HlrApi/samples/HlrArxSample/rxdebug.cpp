//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#ifdef _DEBUG

#include "rxdebug.h"

#ifndef _WINBASE_
//extracted from winbase.h so that
//we don't have to pull in the whole
//header
// Unicode: Leaving as char type because A and W functions are both available
extern "C"
void
_stdcall
OutputDebugStringA(
    const char* lpOutputString
    );

extern "C"
void
_stdcall
OutputDebugStringW(
    const unsigned short* lpOutputString
    );
#define OutputDebugString  OutputDebugStringW

#endif //_WINBASE

//VC8:resolved the redefinition error, macro is already defined in stdlib.h
#ifdef _countof
#undef _countof
#endif 


// determine number of elements in an array (not bytes)
#define _countof(array) (sizeof(array)/sizeof(array[0]))

inline void _cdecl RxTrace(const ACHAR* lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);
	int nBuf;
	ACHAR szBuffer[512];
	nBuf = _vsnwprintf_s(szBuffer, _countof(szBuffer), lpszFormat, args);
	// was there an error?
	RXASSERT(nBuf >= 0);
    ::OutputDebugString(szBuffer);
	va_end(args);
}

#endif //_DEBUG, entire file
