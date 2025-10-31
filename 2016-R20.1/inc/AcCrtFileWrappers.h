//
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
// Name:            AcCrtFileWrappers.h
//
// Description:     Wrapper classes for clib FILE functions
//
//////////////////////////////////////////////////////////////////////////////

//        

#pragma once

#include "stdio.h"      // for fopen, FILE, fprintf, etc
#include <malloc.h>     // for _alloca
#include "AdCharFmt.h"
#include "casuppress.h"

#pragma warning(push)
#pragma warning(disable:4996)

#ifdef ASSERT
#define AcFILE_Assert ASSERT
#elif defined assert
#define AcFILE_Assert assert
#elif defined _ASSERTE
#define AcFILE_Assert _ASSERTE
#else
#define AcFILE_Assert(T)
#endif

class AcFILE {
  public:
    // fwrite() expands LF's for us, so we set the formatter's mode
    // to not do the LF expansion.
    AcFILE()
        : mpFILE(NULL),
          mChFmtr(AdCharFormatter::kAnsi,
                  false,        // useCIF
                  false)        // expandLF
    {}
    AcFILE(FILE *pFILE)
        : mpFILE(pFILE),
          mChFmtr(AdCharFormatter::kAnsi,
                  false,        // useCIF
                  false)        // expandLF
    {}
    ~AcFILE() {
        AcFILE_Assert(this->mpFILE == NULL);
    }
    FILE * fopen(const TCHAR *pName, const TCHAR *pMode);
    FILE * fsopen(const TCHAR *pName, const TCHAR *pMode, int shflag);
    void attach(FILE *pFILE);
    FILE * detach();
    int fclose();
    int fputs(const TCHAR *pStr);
    TCHAR * fgets(TCHAR *pBuf, int nChars);
    int fprintf(const TCHAR *pFmtStr, ...);
    int vfprintf(const TCHAR *pFmtStr, va_list va);
    int fscanf(const TCHAR *pFmtStr, ...);
    int fputc(TCHAR c);
    int ungetc(TCHAR c);
    int fgetc();
    bool isOpen() const { return this->mpFILE != NULL; }
    FILE * pFILE() const { return this->mpFILE; }

    unsigned getCharFormat() const { return this->mChFmtr.getFormat(); }
    unsigned setCharFormat(unsigned nFmt) {
            return this->mChFmtr.setFormat(nFmt); }
    bool getUseCIF() const { return this->mChFmtr.getUseCIF(); }
    bool setUseCIF(bool bUseCIF) {
            return this->mChFmtr.setUseCIF(bUseCIF); }
    bool getExpandLF() const { return this->mChFmtr.getExpandLF(); }
    bool setExpandLF(bool bExpandLF) {
            return this->mChFmtr.setExpandLF(bExpandLF); }

    bool readBOM();
    bool writeBOM();

  private:

    #ifdef UNICODE
      bool parseAnsiOrCIF(wchar_t &wch);
      bool parseUtf8(wchar_t &wch);
      bool parseUtf16(wchar_t &wch);
      int  fputsWorker(const wchar_t* pSrc, int nOptions);
    #endif

    FILE *mpFILE;
    AdCharFormatter mChFmtr;
};


// instance methods
inline FILE * AcFILE::fopen(const TCHAR *pName, const TCHAR *pMode)
{
    AcFILE_Assert(this->mpFILE == NULL);
    this->mpFILE = ::_tfopen(pName, pMode);
    return this->mpFILE;
}

inline FILE * AcFILE::fsopen(const TCHAR *pName, const TCHAR *pMode, int shflag)
{
    AcFILE_Assert(this->mpFILE == NULL);
    this->mpFILE = ::_tfsopen(pName, pMode, shflag);
    return this->mpFILE;
}

inline void AcFILE::attach(FILE *pFILE)
{
    AcFILE_Assert(this->mpFILE == NULL);
    this->mpFILE = pFILE;
}

inline FILE * AcFILE::detach()
{
    FILE *pRet = this->mpFILE;
    this->mpFILE = NULL;
    return pRet;
}

inline int AcFILE::fclose()
{
    int nRet = 0;
    if (this->mpFILE != NULL) {
        nRet = ::fclose(this->mpFILE);
        this->mpFILE = NULL;
    }
    return nRet;
}

inline int AcFILE::fputs(const TCHAR *pStr)
{
    AcFILE_Assert(this->mpFILE != NULL);
#ifndef UNICODE
    return ::fputs(pStr, this->mpFILE);
#else
    return fputsWorker(pStr, 0);
#endif
}

inline TCHAR * AcFILE::fgets(TCHAR *pBuf, int nChars)
{
    AcFILE_Assert(this->mpFILE != NULL);
    // Need room for null, so it doesn't make sense to pass
    // a count of 1 or less.
    AcFILE_Assert(nChars > 1);
#ifndef UNICODE
    return ::fgets(pBuf, nChars, this->mpFILE);
#else
    // We don't know how many widechars the ansi chars
    // will turn into, so we have to read them one
    // at a time.  Read until we hit newline, eof
    // or nChars.
    TCHAR *pSavePtr = pBuf;
    for (;;) {
        if (nChars <= 1)
            break;
        const int ch = this->fgetc();
        if (ch == EOF)  // -1
            break;
        AcFILE_Assert((ch & ~0xffff) == 0);  // only low 16 bits set
        AcFILE_Assert((wchar_t)ch == ch);
        *pSavePtr = (wchar_t)ch;
        pSavePtr++;
        if (ch == '\n')
            break;   // stop reading after newline
        nChars--;
    }
    *pSavePtr = 0;

    if (pSavePtr == pBuf)
        return NULL;

    return pBuf;
#endif
}

inline int AcFILE::fprintf(const TCHAR *pFmtStr, ...)
{
    AcFILE_Assert(this->mpFILE != NULL);
    va_list va;
    va_start(va, pFmtStr);
    return this->vfprintf(pFmtStr, va);
}

inline int AcFILE::vfprintf(const TCHAR *pFmtStr, va_list va)
{
#ifndef UNICODE
    return ::vfprintf(this->mpFILE, pFmtStr, va);
#else
    // Note: we have to format the entire string into a widechar
    // buffer first, then convert that to ansi.

    int nChar = ::_vscwprintf(pFmtStr, va);

    wchar_t* wBuf = new wchar_t[nChar + 1];
    ::wmemset(wBuf, 0, nChar + 1);
    ::vswprintf_s(wBuf,nChar + 1, pFmtStr, va);
    AcFILE_Assert(wBuf[nChar] == 0);

    int iRet = fputsWorker(wBuf, 1);
    delete [] wBuf;
    return iRet;
#endif
}

#ifndef _ADESK_MAC_
inline int AcFILE::fscanf(const TCHAR *pFmtStr, ...)
{
    AcFILE_Assert(this->mpFILE != NULL);

    // TODO: Remove this, it's meant to shut the compiler up.
    pFmtStr = NULL;

    // UNICODE: TODO: SPAGO: There is no existing client of fscanf 
    // method. Implement this method when time allows/need arises.
}
#endif

inline int AcFILE::fputc(TCHAR c)
{
    AcFILE_Assert(this->mpFILE != NULL);
#ifndef UNICODE
    return ::fputc(c, this->mpFILE);
#else
    char chBuf[8];  // CIF is 7 bytes, utf-32 cr-lf might be 8
    const unsigned nBytes = this->mChFmtr.wcharToBytes(c, chBuf,
                                                       sizeof(chBuf));
    AcFILE_Assert(nBytes >= 1);
    AcFILE_Assert(nBytes <= 8);  // worst case is utf-32 cr-lf?
    const unsigned nNumWrote = (unsigned)fwrite(chBuf, 1,
                                                nBytes, this->mpFILE);
    if (nNumWrote == nBytes)
        return c;   // return the char written
    else
        return -1;  // error
#endif
}

inline int AcFILE::ungetc(TCHAR c)
{
    AcFILE_Assert(this->mpFILE != NULL);
#ifndef UNICODE
    return ::ungetc(c, this->mpFILE);
#else
    char chBuf[8];  // CIF is 7 bytes, utf-32 cr-lf might be 8
    const unsigned nBytes = this->mChFmtr.wcharToBytes(c, chBuf,
                                                       sizeof(chBuf));
    AcFILE_Assert(nBytes >= 1);
    AcFILE_Assert(nBytes <= 8);
    // Note: for now we can only unget a single char.  So if
    // the wide char got converted to CIF or double-byte,
    // we fail.  Todo: fix this if it's really needed.
    if (nBytes == 1 && ::ungetc(chBuf[0], this->mpFILE) == chBuf[0])
        return c;   // on success, return the char passed in
    else
        return -1;
#endif
}

inline int AcFILE::fgetc()
{
    AcFILE_Assert(this->mpFILE != NULL);
#ifndef UNICODE
    return ::fgetc(this->mpFILE);
#else
    wchar_t wchLocal = L'\0';
    switch(this->getCharFormat())
    {
        case AdCharFormatter::kAnsi:
            if (parseAnsiOrCIF(wchLocal))
                return wchLocal;
            return EOF;
            break;

        case AdCharFormatter::kUtf8:
            if (parseUtf8(wchLocal))
                return wchLocal;
            return EOF;
            break;

        case AdCharFormatter::kUtf16LE:
        case AdCharFormatter::kUtf16BE:
            if (parseUtf16(wchLocal))
                return wchLocal;
            return EOF;
            break;

        case AdCharFormatter::kUtf32LE:
        case AdCharFormatter::kUtf32BE:
            AcFILE_Assert(false); // Implement me!
            return EOF;
            break;
    }

    AcFILE_Assert(false); // Should never reach here!
    return EOF;
#endif
}

inline bool AcFILE::readBOM()
{
    AcFILE_Assert(this->mpFILE != NULL);
    const long lFilePos = ::ftell(this->mpFILE);
    AcFILE_Assert(lFilePos == 0L);
    if (lFilePos != 0L)
        return false; // Can't do this unless we're at start of file.

    unsigned short nVal;
    if (::fread(&nVal, 1, 2, this->mpFILE) == 2) {
        if (nVal == 0xfeff) {
            this->setCharFormat(AdCharFormatter::kUtf16LE);
            return true;
        }
        if (nVal == 0xfffe) {
            this->setCharFormat(AdCharFormatter::kUtf16BE);
            return true;
        }
        if (nVal == 0xbbef) {
            unsigned char nByte3;
            if (::fread(&nByte3, 1, 1, this->mpFILE) == 1) {
                if (nByte3 == 0xbf) {
                    this->setCharFormat(AdCharFormatter::kUtf8);
                    return true;
                }
            }
        }
        else if (nVal == 0 || nVal == 0xfeff) {
            unsigned nVal2;
            if (::fread(&nVal2, 1, 2, this->mpFILE) == 2) {
                if (nVal == 0 && nVal2 == 0xfffe) {
                    this->setCharFormat(AdCharFormatter::kUtf32BE);
                    return true;
                }
                else if (nVal == 0xfeff && nVal2 == 0) {
                    this->setCharFormat(AdCharFormatter::kUtf32LE);
                    return true;
                }
            }
        }
    }

    // If got here, then no BOM found, so reset 
    // to file beginning. Leave format what it was.
    ::rewind(this->mpFILE);
    return false;
}

inline bool AcFILE::writeBOM()
{
    AcFILE_Assert(this->mpFILE != NULL);
    if (this->mpFILE == NULL)
        return false; // There must be an associated file.

    const long lFilePos = ::ftell(this->mpFILE);
    AcFILE_Assert(lFilePos == 0L);
    if (lFilePos != 0L)
        return false; // Can't do this unless we're at start of file.

    unsigned nBom = 0;
    const int cbBomSize = AdCharFormatter::getBOM(nBom, 
                                this->getCharFormat());
    if (cbBomSize == 0) // AdcharFormatter::getBOM would
        return false;   // have brought up an assertion.

    const int cbWritten = (int) ::fwrite(&nBom,         // BOM to be written.
                                         1,             // Item size.
                                         cbBomSize,     // Item count.
                                         this->mpFILE); // File pointer.

    AcFILE_Assert(cbWritten == cbBomSize);
    if (cbWritten != cbBomSize)
    {
        ::rewind(this->mpFILE);
        return false;
    }

    return true;
}

#ifdef UNICODE

inline bool AcFILE::parseAnsiOrCIF(wchar_t &wch)
{
    AcFILE_Assert(this->getCharFormat() == AdCharFormatter::kAnsi);
    wch = L'\0';

    // Read in a single character from file.
    unsigned char cFirstChar = 0;
    int nBytesRead = (int)::fread(&cFirstChar, 1, 1, this->mpFILE);
    if (nBytesRead <= 0)
        return false; // Error or EOF condition.

    if (cFirstChar > 0x7f) // Possible double-byte character.
    {
        char chBuf[2] = {0};
        wchar_t wchLocal = 0;
        chBuf[0] = ((char) cFirstChar);

        const BOOL bIsDBCS = ::IsDBCSLeadByteEx(CP_ACP, cFirstChar);
        if (bIsDBCS != FALSE) // Attempt to read in the second character.
        {
            unsigned char cSecondChar = 0;
            nBytesRead = (int)::fread(&cSecondChar, 1, 1, this->mpFILE);
            if (nBytesRead <= 0)
                return false; // Error or EOF condition.
            chBuf[1] = ((char) cSecondChar);
        }

        // TODO: Handle the cases of surrogate pairs.
        const int nRet = ::MultiByteToWideChar(
                            CP_ACP,               // Conversion code page.
                            MB_ERR_INVALID_CHARS, // Do we want this?
                            chBuf,                // DBCS character.
                            bIsDBCS ? 2 : 1,      // DBCS byte count.
                            &wchLocal,            // Converted wide character.
                            1);                   // Single wide character.

        AcFILE_Assert(nRet == 1); // If fails, do we need lang. pack installed?
        wch = (nRet == 1) ? wchLocal : L'?';
        return true;
    }

    AcFILE_Assert(cFirstChar <= 0x7f);

    wch = ((wchar_t) cFirstChar);
    if (cFirstChar == '\r' && (this->mChFmtr.getExpandLF())) {
        unsigned char cNewLinePair = 0; // Any pairing '\n'?
        nBytesRead = (int)::fread(&cNewLinePair, 1, 1, this->mpFILE);
        if (nBytesRead <= 0) // '\r' at the end of file, odd...
            return true;     // but we are taking it as it is anyway.
        if (cNewLinePair != '\n') {
            ::fseek(this->mpFILE, -1L, SEEK_CUR);
            return true; // Return '\r' untranslated.
        }

        wch = L'\n'; // Translate to new line character.
        return true;
    }

    // If CIF not desired, return any character.
    if (cFirstChar != '\\' || (this->getUseCIF()) == false)
        return true;

    // When we get here, it means that there is possible CIF string 
    // ahead of us. we will read in more from the underlying file...
    char chBuffer[8] = {0};
    chBuffer[0] = '\\';

    // Attempt to read 6 more bytes from file. This function might 
    // not be reading as many bytes as we want but that's not what 
    // we care right now, leave it to AdCharFormatter::isCIFString.
    nBytesRead = (int) ::fread(&chBuffer[1],  // Input buffer.
                               1,             // Unit data size.
                               6,             // Unit count.
                               this->mpFILE); // FILE pointer.

    // If it's a CIF sequence, parse into wch.
    if (AdCharFormatter::isCIFString(chBuffer))
    {
        AdCharFormatter::parseCIF(chBuffer, wch);
        return true;
    }

    // It was not CIF, we read too much, undo that.
    if (nBytesRead > 0)
        ::fseek(this->mpFILE, -nBytesRead, SEEK_CUR);

    wch = L'\\';
    return true;
}

inline bool AcFILE::parseUtf8(wchar_t &wch)
{
    AcFILE_Assert(this->getUseCIF() == false);

    // Read in a single character from file.
    unsigned char cCharacter = 0;
    int nBytesRead = (int) ::fread(&cCharacter, 1, 1, this->mpFILE);
    if (nBytesRead <= 0)
        return false; // Error or EOF condition.

    if (cCharacter <= 0x7f)
    {
        wch = cCharacter;
        if (cCharacter == '\r' && mChFmtr.getExpandLF()) {
            unsigned char cNewLine = 0;
            nBytesRead = (int) ::fread(&cNewLine, 1, 1, this->mpFILE);
            if (nBytesRead <= 0)    // '\r' at the end of file...
                return true;        // ... weird but we'll take it anyway.
            if (cNewLine != '\n') { // Not a new line character!
                ::fseek(this->mpFILE, -1L, SEEK_CUR);
                return true; // Return '\r' untranslated.
            }
            wch = L'\n'; // Translated to new line character.
        }
        return true; // Single byte UTF8 character.
    }

    int nByteCount;
    char chBuffer[4] = {0};
    chBuffer[0] = ((char) cCharacter);
    if ((chBuffer[0] & 0xe0) == 0xc0)
        nByteCount = 2; // 110xxxxx = 2-byte code
    else if((chBuffer[0] & 0xf0) == 0xe0)
        nByteCount = 3; // 1110xxxx = 3-byte code
    else if((chBuffer[0] & 0xf8) == 0xf0)
        nByteCount = 4; // 11110xxx = 4-byte code
    else
    {
        // Adding this assert for now, to help with
        // debugging.  Maybe we'll have to relax it if
        // we find we commonly hit malformed data...
        AcFILE_Assert(false);
        return false; // Malformed UTF8 character?
    }

    // Attempt to read one or more bytes from file...
    nBytesRead = (int) ::fread(&chBuffer[1],   // Input buffer.
                               1,              // Unit data size.
                               nByteCount - 1, // Unit count.
                               this->mpFILE);  // FILE pointer.

    AcFILE_Assert(nBytesRead == nByteCount - 1);
    if (nBytesRead < nByteCount - 1)
        return false; // Malformed UTF8 character.

    const int nCvted = MultiByteToWideChar(CP_UTF8,     // Conversion code page.
                                           0,           // Flags must be 0 for UTF8.
                                           chBuffer,    // Input UTF8 string.
                                           nByteCount,  // Byte count in UTF8 string.
                                           &wch,        // Destination wide character.
                                           1);          // Expect a single wide char.

    AcFILE_Assert(nCvted == 1);
    return nCvted == 1;
}

inline bool AcFILE::parseUtf16(wchar_t &wch)
{
    wchar_t wchLocal = 0;
    int nBytesRead = (int) ::fread(&wchLocal, 1, 2, this->mpFILE);
    if (nBytesRead <= 0)
        return false; // Error or EOF condition.

    const unsigned nFormat = this->mChFmtr.getFormat();
    if (nFormat == AdCharFormatter::kUtf16BE)
        wchLocal = (wchLocal >> 8) | (wchLocal << 8);

    wch = wchLocal;
    if (wchLocal == L'\r' && mChFmtr.getExpandLF()) {
        wchar_t wchNewLine = L'\n';
        nBytesRead = (int) ::fread(&wchNewLine, 1, 2, this->mpFILE);
        if (nBytesRead <= 0)        // '\r' at the end of file...
            return true;            // ... weird but we'll take it.

        if (nFormat == AdCharFormatter::kUtf16BE)
            wchNewLine = (wchNewLine >> 8) | (wchNewLine << 8);
        if (wchNewLine != L'\n') {  // Not a new line character.
            ::fseek(this->mpFILE, -2L, SEEK_CUR);
            return true; // Return '\r' untranslated.
        }
        wch = L'\n'; // Translated to new line character.
    }

    return true;
}

// This helper function writes data to the file depending on the value of 
// nOptions. In case of fputs zero is returned when successful and incase 
// of fprintf the return value is the number of bytes.
// 
inline int AcFILE::fputsWorker(const wchar_t* pSrc, int nOptions)
{
    AcFILE_Assert(this->mpFILE != NULL);
    AcFILE_Assert(pSrc != NULL);

    int nNumInput = 0;
    for (;;) {
        const wchar_t wch = *pSrc;
        if (wch == 0)
            break;
        char chBuf[8];  // CIF is 7 bytes, utf-32 cr-lf might be 8
        const unsigned nBytes = this->mChFmtr.wcharToBytes(wch, chBuf,
                                                           sizeof(chBuf));
        AcFILE_Assert(nBytes >= 1);
        AcFILE_Assert(nBytes <= 8);
        const unsigned nNumWrote = (unsigned)fwrite(chBuf, 1,
                                                    nBytes, this->mpFILE);
        if (nNumWrote != nBytes)
            return -1;  // error (out of disk space?)
        nNumInput++;
        pSrc++;
    }

    if (nOptions == 0)          // called from puts
        return 0;               // 0 indicates success, apparently
    else if (nOptions == 1)     // called from printf
        return nNumInput;
    else {
        AcFILE_Assert(false);
    }

    return -1;
}

#endif // UNICODE defined.
#pragma warning(pop) 

