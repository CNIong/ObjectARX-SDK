//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
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
