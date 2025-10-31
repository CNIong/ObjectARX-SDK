
//
//  (C) Copyright 2006-2007 by Autodesk, Inc.  All rights reserved.
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
#pragma once

// replace _tcslen and wcslen with ac_wcslen, which returns unsigned
#include "ac_tcslen.h"
#include "adesk.h"

#define Ac64Assert AcTcsLen_Assert

#ifndef _WIN64

#ifdef GetWindowLongPtr
#undef GetWindowLongPtr
#endif
// The WinUser.h definitions omits the (LONG_PTR) casts, which can
// cause warnings in the 32-bit build with /Wp64
//
inline LONG_PTR __stdcall GetWindowLongPtr(HWND h, int n)
{
    return static_cast<LONG_PTR>(::GetWindowLong(h, n));
}

#ifdef SetWindowLongPtr
#undef SetWindowLongPtr
#endif
inline LONG_PTR __stdcall SetWindowLongPtr(HWND h, int n, LONG_PTR v)
{
    const long nLongV = static_cast<long>(v);
    return static_cast<LONG_PTR>(::SetWindowLong(h, n, nLongV));
}

inline LONG_PTR __stdcall SetWindowLongPtr(HWND h, int n, void * v)
{
    const LONG_PTR vPtr = reinterpret_cast<LONG_PTR>(v);
    return ::SetWindowLongPtr(h, n, vPtr);  // call above overload
}

#ifdef GetClassLongPtr
#undef GetClassLongPtr
#endif

inline ULONG_PTR __stdcall GetClassLongPtr(HWND h, int n)
{
   return static_cast<ULONG_PTR>(::GetClassLong(h, n));
}

#ifdef SetClassLongPtr
#undef SetClassLongPtr
#endif

inline ULONG_PTR __stdcall SetClassLongPtr(HWND h, int n, LONG_PTR v)
{
    const long vLong = static_cast<long>(v);
    return static_cast<ULONG_PTR>(::SetClassLong(h, n, vLong));
}

inline ULONG_PTR __stdcall SetClassLongPtr(HWND h, int n, void * v)
{
    const ULONG_PTR vPtr = reinterpret_cast<ULONG_PTR>(v);
    return ::SetClassLongPtr(h, n, vPtr);  // call above overload
}

// The msvc definition of this in stddef.h has a (size_t) cast on a
// pointer which causes a /Wp64 warning.  So we insert a (UINT_PTR)
// cast in between.  And then we go ahead and cast down to unsigned,
// since we know that member offsets will never exceed 4G.
//
#ifdef offsetof
#undef offsetof
#endif

#define offsetof(s,m) static_cast<unsigned>( \
             reinterpret_cast<UINT_PTR> (\
                 &reinterpret_cast<const volatile char&>( \
                     reinterpret_cast<const s *>(0)->m )))

#else  // !_WIN64

// The msvc definition of this in windef.h has a (WORD) cast on a 
// DWORD_PTR that is shifted right 16 bits. This might cause Run 
// Time check failure #1 when RTTC is enabled, if the bits in the
// range from 16 to 64 are not all equal to 0 before the (WORD) 
// cast. Here, we forcibly set bits at position from 16 to 64 
// all to be 0.
//
#ifdef HIWORD
#undef HIWORD
#endif
// note: we leave in one C-style (DWORD_PTR) cast, because we don't know
// if v is an integer type (requiring static_cast) or a pointer type
// (requiring reinterpret_cast).
#define HIWORD(v) (static_cast<WORD>((((DWORD_PTR)(v) >> 16) & 0xFFFF)))

#endif // _WIN64

// The msvc definition of this in windef.h is bad in both 32-bit and
// 64-bit builds, triggering a Runtime Check assert.
// #define HIBYTE(w)           ((BYTE)((DWORD_PTR)(w) >> 8))
#ifdef  HIBYTE
#undef HIBYTE
#endif
#define HIBYTE(w)           LOBYTE((DWORD_PTR)(w) >> 8)

#pragma warning(push)
#pragma warning(disable:4100)//disable unreferenced formal parameter warning
inline int AcIntPtrToInt(Adesk::LongPtr nVal, Adesk::LongPtr nLimit = /*16M*/0x1000000)
{
    Ac64Assert(nVal < nLimit);
    Ac64Assert(nVal > -nLimit);   // it's a signed value, so assert at both ends of the range
    const int nRet = static_cast<int>(nVal);
    Ac64Assert(nRet == nVal);    // a little redundant, but make sure no bits are lost
    return nRet;
}

inline unsigned int AcUIntPtrToUInt(Adesk::ULongPtr nVal, Adesk::ULongPtr nLimit = /*16M*/0x1000000)
{
    Ac64Assert(nVal < nLimit);
    const unsigned int nRet = static_cast<unsigned int>(nVal);
    Ac64Assert(nRet == nVal);    // a little redundant, but make sure no bits are lost
    return nRet;
}
#pragma warning(pop)

// provide a polymophic function to parse INT_PTR string.
inline Adesk::LongPtr __stdcall AcStrToIntPtr(const wchar_t * s)
{
#ifdef _WIN64
    return _wtoi64(s);
#else
    return _wtoi(s);
#endif
}
