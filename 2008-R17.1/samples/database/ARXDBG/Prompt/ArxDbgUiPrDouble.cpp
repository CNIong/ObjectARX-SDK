//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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
            acedGetInput(m_keyWordPicked.GetBuffer(512));
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
