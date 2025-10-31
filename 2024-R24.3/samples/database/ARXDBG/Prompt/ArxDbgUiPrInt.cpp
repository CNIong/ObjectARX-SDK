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
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxDbgUiPrInt.h"



/****************************************************************************
**
**  ArxDbgUiPrInt::ArxDbgUiPrInt
**
**  **jma
**
*************************************/

ArxDbgUiPrInt::ArxDbgUiPrInt(LPCTSTR msg, LPCTSTR keyWordList, IntType type)
:   ArxDbgUiPrBase(msg, keyWordList),
    m_intType(type),
    m_value(0),
    m_minVal(0),
    m_maxVal(0)
{
}

/****************************************************************************
**
**  ArxDbgUiPrInt::~ArxDbgUiPrInt
**
**  **jma
**
*************************************/

ArxDbgUiPrInt::~ArxDbgUiPrInt()
{
}

/****************************************************************************
**
**  ArxDbgUiPrInt::go
**
**  **jma
**
*************************************/

ArxDbgUiPrBase::Status
ArxDbgUiPrInt::go()
{
    CString prompt;
    int initFlag;

        // set up prompt
    prompt.Format(_T("\n%s: "), message());

        // set up init flag
    if (m_intType == kNoZero)
        initFlag = RSG_NONULL+RSG_NOZERO;
    else if (m_intType == kNoNeg)
        initFlag = RSG_NONULL+RSG_NONEG;
    else if (m_intType == kNoNegNoZero)
        initFlag = RSG_NONULL+RSG_NOZERO+RSG_NONEG;
    else
        initFlag = RSG_NONULL;

    while (1) {
        acedInitGet(initFlag, keyWords());
        int result = acedGetInt(prompt, &m_value);

        if (result == RTNORM) {
            if (inRange())
                return ArxDbgUiPrBase::kOk;
        }
        else if (result == RTKWORD){
            const size_t kBufSize = 512;
            acedGetInput(m_keyWordPicked.GetBuffer(kBufSize), kBufSize);
            m_keyWordPicked.ReleaseBuffer();
            return ArxDbgUiPrBase::kKeyWord;
        }
        else
            return ArxDbgUiPrBase::kCancel;
    }
}

/****************************************************************************
**
**  ArxDbgUiPrInt::setRange
**
**  **jma
**
*************************************/

void
ArxDbgUiPrInt::setRange(int minVal, int maxVal)
{
    ASSERT(maxVal >= minVal);

    m_minVal = minVal;
    m_maxVal = maxVal;
}

/****************************************************************************
**
**  ArxDbgUiPrInt::inRange
**
**  **jma
**
*************************************/

bool
ArxDbgUiPrInt::inRange()
{
    if (m_intType == ArxDbgUiPrInt::kRange) {
        if ((m_value >= m_minVal) && (m_value <= m_maxVal))
            return true;
        else {
		    acutPrintf(_T("\nValue must be in range %d to %d."), m_minVal, m_maxVal);
            return false;
        }
    }
    else
        return true;
}

/****************************************************************************
**
**  ArxDbgUiPrInt::value
**
**  **jma
**
*************************************/

int
ArxDbgUiPrInt::value()
{
    return m_value;
}

/****************************************************************************
**
**  ArxDbgUiPrInt::setType
**
**  **jma
**
*************************************/

void
ArxDbgUiPrInt::setType(IntType type)
{
    m_intType = type;
}

