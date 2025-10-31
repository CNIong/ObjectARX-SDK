//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

//
// Name:            AcFStream.h
//
// Description:     Wrapper classes for std:ofstream and std::ifstream.
//
//////////////////////////////////////////////////////////////////////////////

// Note: 1. this header should be included *after* fstream headers
//        

#pragma once

#ifdef _ADESK_MAC_
#include <malloc/malloc.h>
#else
#include "malloc.h"             // for _alloca()
#endif
#include "AdAChar.h"
#include "AdCharFmt.h"

#ifdef ASSERT
#define AcFStream_Assert ASSERT
#elif defined assert
#define AcFStream_Assert assert
#else
#define AcFStream_Assert(T)
#endif

#ifdef UNICODE
inline int AcFStream_wideToMulti(const wchar_t *pSrc, int nSrcSize,
                                 char *pDest, int nDestSize);
inline std::locale AcFStream_curLocale();
#endif

class AcIfstream : public
#ifndef UNICODE
                        std::ifstream {
#else
                        std::wifstream {
#endif
  public:
    AcIfstream() {};
    AcIfstream(const ACHAR *pName);
#ifdef UNICODE
    void open(const wchar_t *pName);
    void open(const wchar_t *pName, ios_base::openmode nMode);
#endif
};

class AcOfstream : public
#ifndef UNICODE
                        std::ofstream {
#else
                        std::wofstream {
#endif
  public:
    AcOfstream() {};
    AcOfstream(const ACHAR *pName);
#ifdef UNICODE
    void open(const wchar_t *pName);
    void open(const wchar_t *pName, ios_base::openmode nMode);
#endif

};

#ifndef UNICODE
inline AcIfstream::AcIfstream(const ACHAR *pName) : std::ifstream(pName)
{
}
inline AcOfstream::AcOfstream(const ACHAR *pName) : std::ofstream(pName)
{
}
#else
inline AcIfstream::AcIfstream(const ACHAR *pName)
{
    this->open(pName);
}

inline AcOfstream::AcOfstream(const ACHAR *pName)
{
    this->open(pName);
}

inline std::locale AcFStream_curLocale()
{
#ifdef _ADESK_WINDOWS_
    char buf[100];
    sprintf_s(buf, 100, ".%d", GetACP());

    // Only set LC_CTYPE, because we don't want it to start
    // formatting numbers with comma separators, etc
    return std::locale(buf, LC_CTYPE);
#else
    STUB_WARNING(AcFStream_curLocale);
    return std::locale();
#endif
}

inline int AcFStream_wideToMulti(const wchar_t *pSrc, int nSrcSize,
                                 char *pDest, int nDestSize)
{
    return ::WideCharToMultiByte(
                        CP_ACP,
#if defined(WINVER) && (WINVER >= 0x0500)
                        // This function is currently only being used to
                        // convert filenames from widechar to ansi.  So
                        // we want it to fail if we can't get an exact
                        // mapping.
                        WC_NO_BEST_FIT_CHARS,
#else
                        0,
#endif
                        pSrc,
                        nSrcSize,
                        pDest,
                        nDestSize,
                        NULL,   // lpDefaultChar
                        NULL);  // lpUsedDefaultChar
}


inline void AcIfstream::open(const wchar_t *pName)
{
#ifdef _ADESK_WINDOWS_
    this->std::wifstream::open(pName);
    this->imbue(AcFStream_curLocale());
#else
    STUB_WARNING(AcIfstream::open);
#endif
}

inline void AcIfstream::open(const wchar_t *pName, ios_base::openmode nMode)
{
#ifdef  _ADESK_WINDOWS_
    this->std::wifstream::open(pName, nMode);
    this->imbue(AcFStream_curLocale());
#else
     STUB_WARNING(AcIfstream::open);
#endif
}

inline void AcOfstream::open(const wchar_t *pName)
{
#ifdef _ADESK_WINDOWS_
    this->std::wofstream::open(pName);
    this->imbue(AcFStream_curLocale());
#else
    STUB_WARNING(AcOfstream::open);
#endif
}

inline void AcOfstream::open(const wchar_t *pName, ios_base::openmode nMode)
{
#ifdef _ADESK_WINDOWS_
    this->std::wofstream::open(pName, nMode);
    this->imbue(AcFStream_curLocale());
#else
    STUB_WARNING(AcOfstream::open);
#endif
}

#endif

