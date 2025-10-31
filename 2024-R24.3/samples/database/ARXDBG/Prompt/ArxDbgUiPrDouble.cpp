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

#include "ArxDbgUiPrDouble.h"



/****************************************************************************
**
**  ArxDbgUiPrDouble::ArxDbgUiPrDouble
**
**  **jma
**
*************************************/

ArxDbgUiPrDouble::ArxDbgUiPrDouble(LPCTSTR msg, LPCTSTR keyWordList, DoubleType type)
:   ArxDbgUiPrBase(msg, keyWordList),
    m_doubleType(type),
    m_value(0.0),
    m_minVal(0.0),
    m_maxVal(0.0),
    m_unit(-1),
    m_precision(-1)
{
}

/****************************************************************************
**
**  ArxDbgUiPrDouble::~ArxDbgUiPrDouble
**
**  **jma
**
*************************************/

ArxDbgUiPrDouble::~ArxDbgUiPrDouble()
{
}

/****************************************************************************
**
**  ArxDbgUiPrDouble::go
**
**  **jma
**
*************************************/

ArxDbgUiPrBase::Status
ArxDbgUiPrDouble::go()
{
    CString prompt;
    int initFlag;

        // set up prompt
    prompt.Format(_T("\n%s: "), message());

        // set up init flag
    if (m_doubleType == kNoZero)
        initFlag = RSG_NONULL+RSG_NOZERO;
    else if (m_doubleType == kNoNeg)
        initFlag = RSG_NONULL+RSG_NONEG;
    else if (m_doubleType == kNoNegNoZero)
        initFlag = RSG_NONULL+RSG_NOZERO+RSG_NONEG;
    else
        initFlag = RSG_NONULL;

    int result;
    while (1) {
        acedInitGet(initFlag, keyWords());
        result = acedGetReal(prompt, &m_value);

        if (result == RTNORM) {
            if (inRange())
                return ArxDbgUiPrBase::kOk;
        }
        else if (result == RTKWORD) {
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
**  ArxDbgUiPrDouble::setRange
**
**  **jma
**
*************************************/

void
ArxDbgUiPrDouble::setRange(double minVal, double maxVal)
{
    ASSERT(maxVal >= minVal);

    m_minVal = minVal;
    m_maxVal = maxVal;
}

/****************************************************************************
**
**  ArxDbgUiPrDouble::inRange
**
**  **jma
**
*************************************/

bool
ArxDbgUiPrDouble::inRange()
{
    if (m_doubleType == ArxDbgUiPrDouble::kRange) {
        ASSERT(m_minVal != m_maxVal);    // make sure they set ranges!
        if ((m_value >= m_minVal)&&(m_value <= m_maxVal))
            return true;
        else {
            TCHAR str1[512], str2[512];
            acdbRToS(m_minVal, m_unit, m_precision, str1);
            acdbRToS(m_maxVal, m_unit, m_precision, str2);
            acutPrintf(_T("\nValue must be in range %s to %s."), str1, str2);
            return false;
        }
    }
    else
        return true;
}

/****************************************************************************
**
**  ArxDbgUiPrDouble::value
**
**  **jma
**
*************************************/

double
ArxDbgUiPrDouble::value()
{
    return m_value;
}

/****************************************************************************
**
**  ArxDbgUiPrDouble::setDoubleType
**
**  **jma
**
*************************************/

void
ArxDbgUiPrDouble::setDoubleType(DoubleType newType)
{
    m_doubleType = newType;
}

/****************************************************************************
**
**  ArxDbgUiPrDouble::setUnit
**
**  **jma
**
*************************************/

void
ArxDbgUiPrDouble::setUnit(int unit)
{
    m_unit = unit;
}

/****************************************************************************
**
**  ArxDbgUiPrDouble::setPrecision
**
**  **jma
**
*************************************/

void
ArxDbgUiPrDouble::setPrecision(int precision)
{
    m_precision = precision;
}
