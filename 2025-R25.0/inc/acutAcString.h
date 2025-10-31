//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2024 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
//
//  DESCRIPTION:
//
//  This header file contains helper function for legacy functions that return an allocated ACHAR buffer.
//

#pragma once
#include "AcDbCore2dDefs.h"
#include "acadstrc.h"
#include "AcString.h"

ACDBCORE2D_PORT Acad::ErrorStatus acutNewString(const ACHAR* pInput, ACHAR*& pOutput);

template <class ObjType> inline Acad::ErrorStatus acutGetAcStringConvertToAChar(
    const ObjType* pObj,
    Acad::ErrorStatus(ObjType::* pFunc)(AcString&) const,
    ACHAR*& pOutput)
{
    AcString sOutput;
    const Acad::ErrorStatus es = (pObj->*pFunc)(sOutput);
    if (es != Acad::eOk) {
        pOutput = nullptr;
        return es;
    }
    return ::acutNewString(sOutput.kwszPtr(), pOutput);
}

template <class ObjType> inline ACHAR* acutGetAcStringConvertToAChar(
    const ObjType* pObj,
    Acad::ErrorStatus(ObjType::* pFunc)(AcString&) const)
{
    AcString sOutput;
    const Acad::ErrorStatus es = (pObj->*pFunc)(sOutput);
    ACHAR* pRet = nullptr;
    if (es == Acad::eOk)
        ::acutNewString(sOutput.kwszPtr(), pRet);
    return pRet;
}

// Helper functions to take result of a query returning AcString and convert it to ACHAR
inline ACHAR* acutAcStringToAChar(const AcString& s, Acad::ErrorStatus es)
{
    ACHAR* pBuf = nullptr;
    if (es == Acad::eOk)
        ::acutNewString(s.kwszPtr(), pBuf);
    return pBuf;
}

inline Acad::ErrorStatus acutAcStringToAChar(const AcString& s, ACHAR*& pBuf,
    Acad::ErrorStatus es)
{
    pBuf = nullptr;
    if (es != Acad::eOk)
        return es;
    return ::acutNewString(s.kwszPtr(), pBuf);
}

// Takes an ADS return code, such as RTNORM or RTERROR, which was presumably
// returned by another acedXXX() call.  (See adscodes.h for ADS return codes RT*.)
// Returns that ADS code, unless an error is found
//
// Copies the input string into the dest buffer if it fits
// nSizeDest is length of dest buffer in widechars
//
// If not enough room for entire string plus null terminator, then the string
// is truncated and ADS_RTINPUTTRUNCATED is returned
//
// For internal use by deprecated ACHAR-based functions
//
inline int acutCopyAdsResultStr(int nAdsResult, const wchar_t *pIn,
                                wchar_t *pDestBuf, size_t nSizeDest)
{
    // Duplicate some return codes from adscodes.h
    const int acedADS_RTNORM = 5100;
    const int acedADS_RTERROR = -5001;
    const int acedADS_RTINPUTTRUNCATED = -5008;
    if (pDestBuf == nullptr || nSizeDest == 0)
        return acedADS_RTERROR;         // invalid input
    *pDestBuf = L'\0';                  // init dest buf to empty

    if (nAdsResult != acedADS_RTNORM)
        return nAdsResult;              // on errors, return an empty buffer

    if (pIn == nullptr)                 // invalid input
        return acedADS_RTERROR;

    // Copy string until done or run out of buffer
    for (;;pIn++, pDestBuf++) {
        *pDestBuf = *pIn;
        if (*pDestBuf == L'\0')
            break;                      // normal end of copy
        nSizeDest--;
        if (nSizeDest == 0) {           // ran out of dest room
            nAdsResult = acedADS_RTINPUTTRUNCATED;
            *pDestBuf = L'\0';          // overwrite last char to null terminate
            break;
        }
    }
    return nAdsResult;
}


