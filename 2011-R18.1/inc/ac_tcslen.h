
//
//  (C) Copyright 2006-2009 by Autodesk, Inc.  All rights reserved.
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

#ifdef _tcslen
#undef _tcslen
#endif

#ifdef UNICODE
#define _tcslen ac_wcslen
#else
#define _tcslen ac_strlen
#endif

#define wcslen ac_wcslen
#define strlen ac_strlen

#if defined ASSERT
#define AcTcsLen_Assert ASSERT
#elif defined(assert)
#define AcTcsLen_Assert assert
#elif defined(_ASSERTE)
#define AcTcsLen_Assert _ASSERTE
#elif defined ATLASSERT
#define AcTcsLen_Assert ATLASSERT
#else
#define AcTcsLen_Assert(x)
#endif

// use inline to prevent multiple definition errors.
__declspec(noinline) inline unsigned __stdcall ac_wcslen(const wchar_t * s)
{
    unsigned n = 0;
    while (*s != L'\0') {
        s++;
        n++;
        AcTcsLen_Assert(n < 0x7FFFFFFE);  // 2G-1 sanity check
    }
    return n;
}

__declspec(noinline) inline unsigned __stdcall ac_strlen(const char * s)
{
    unsigned n = 0;
    while (*s != '\0') {
        s++;
        n++;
        AcTcsLen_Assert(n < 0x7FFFFFFE);  //  2G-1 sanity check
    }
    return n;
}

