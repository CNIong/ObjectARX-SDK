//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxDbgUiPrAngle.h"



/****************************************************************************
**
**  ArxDbgUiPrAngle::init
**      handle the common work for the constructors
**
**  **jma
**
*************************************/

void
ArxDbgUiPrAngle::init()
{
    m_value = 0.0;
    m_minVal = 0.0;
    m_maxVal = 0.0;
    m_useDashedLine = false;
    m_unit = -1;		// use current setting
    m_precision = -1;	// use current setting
    m_allowNone = false;
}

/****************************************************************************
**
**  ArxDbgUiPrAngle::ArxDbgUiPrAngle
**
**  **jma
**
*************************************/

ArxDbgUiPrAngle::ArxDbgUiPrAngle(LPCTSTR msg, LPCTSTR keyWordList, AngleType type)
:   ArxDbgUiPrBase(msg, keyWordList),
    m_angType(type),
    m_basePt(AcGePoint3d::kOrigin),
    m_useBasePt(false)
{
    init();
}

/****************************************************************************
**
**  ArxDbgUiPrAngle::ArxDbgUiPrAngle
**
**  **jma
**
*************************************/

ArxDbgUiPrAngle::ArxDbgUiPrAngle(LPCTSTR msg, LPCTSTR keyWordList, AngleType type, const AcGePoint3d& basePt)
:   ArxDbgUiPrBase(msg, keyWordList),
    m_angType(type),
    m_basePt(basePt),
    m_useBasePt(true)
{
    init();
}

/****************************************************************************
**
**  ArxDbgUiPrAngle::~ArxDbgUiPrAngle
**
**  **jma
**
*************************************/

ArxDbgUiPrAngle::~ArxDbgUiPrAngle()
{
}

/****************************************************************************
**
**  ArxDbgUiPrAngle::go
**
**  **jma
**
*************************************/

ArxDbgUiPrBase::Status
ArxDbgUiPrAngle::go()
{
    CString prompt;
    int initFlag = 0;

        // set up prompt
    prompt.Format(_T("\n%s: "), message());

        // set up init flag
    if (m_allowNone == false)
        initFlag += RSG_NONULL;

    if (m_angType == kNoZero)
        initFlag += RSG_NOZERO;

    int result;
    while (1) {
        acedInitGet(initFlag, keyWords());
        if (m_useBasePt)
            result = acedGetOrient(asDblArray(m_basePt), prompt, &m_value);
        else
            result = acedGetOrient(NULL, prompt, &m_value);

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
**  ArxDbgUiPrAngle::setRange
**
**  **jma
**
*************************************/

void
ArxDbgUiPrAngle::setRange(double minVal, double maxVal)
{
    ASSERT(maxVal >= minVal);

    m_minVal = minVal;
    m_maxVal = maxVal;
}

/****************************************************************************
**
**  ArxDbgUiPrAngle::inRange
**
**  **jma
**
*************************************/

bool
ArxDbgUiPrAngle::inRange()
{
    if (m_angType == ArxDbgUiPrAngle::kRange) {
        ASSERT(m_minVal != m_maxVal);    // make sure they set ranges!
        if ((m_value >= m_minVal)&&(m_value <= m_maxVal))
            return true;
        else {
            TCHAR str1[512], str2[512];
            acdbAngToS(m_minVal, m_unit, m_precision, str1);
            acdbAngToS(m_maxVal, m_unit, m_precision, str2);
            acutPrintf(_T("\nValue must be in range %s to %s."), str1, str2);
            return false;
        }
    }
    else
        return true;
}

/****************************************************************************
**
**  ArxDbgUiPrAngle::value
**
**  **jma
**
*************************************/

double
ArxDbgUiPrAngle::value()
{
    return m_value;
}

/****************************************************************************
**
**  ArxDbgUiPrAngle::setAngleType
**
**  **jma
**
*************************************/

void
ArxDbgUiPrAngle::setAngleType(AngleType newType)
{
    m_angType = newType;
}

/****************************************************************************
**
**  ArxDbgUiPrAngle::setBasePt
**
**  **jma
**
*************************************/

void
ArxDbgUiPrAngle::setBasePt(const AcGePoint3d& basePt)
{
    m_basePt = basePt;
    m_useBasePt = true;
}

/****************************************************************************
**
**  ArxDbgUiPrAngle::setUseBasePt
**
**  **jma
**
*************************************/

void
ArxDbgUiPrAngle::setUseBasePt(bool useIt)
{
    m_useBasePt = useIt;
}

/****************************************************************************
**
**  ArxDbgUiPrAngle::setUseDashedLine
**
**  **jma
**
*************************************/

void
ArxDbgUiPrAngle::setUseDashedLine(bool useIt)
{
    m_useDashedLine = useIt;
}

/****************************************************************************
**
**  ArxDbgUiPrAngle::setUnit
**
**  **jma
**
*************************************/

void
ArxDbgUiPrAngle::setUnit(int unit)
{
    m_unit = unit;
}

/****************************************************************************
**
**  ArxDbgUiPrAngle::setPrecision
**
**  **jma
**
*************************************/

void
ArxDbgUiPrAngle::setPrecision(int precision)
{
    m_precision = precision;
}

/****************************************************************************
**
**  ArxDbgUiPrAngle::setAllowNone
**
**  **jma
**
*************************************/

void
ArxDbgUiPrAngle::setAllowNone(bool allowIt)
{
    m_allowNone = allowIt;
}

