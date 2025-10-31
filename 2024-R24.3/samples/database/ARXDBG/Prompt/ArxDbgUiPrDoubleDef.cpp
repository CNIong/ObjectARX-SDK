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

#include "ArxDbgUiPrDoubleDef.h"



/****************************************************************************
**
**  ArxDbgUiPrDoubleDef::ArxDbgUiPrDoubleDef
**
**  **jma
**
*************************************/

ArxDbgUiPrDoubleDef::ArxDbgUiPrDoubleDef(LPCTSTR msg, LPCTSTR keyWordList, DoubleType type, double def)
:   ArxDbgUiPrDouble(msg, keyWordList, type)
{
    m_default = def;
}

/****************************************************************************
**
**  ArxDbgUiPrDoubleDef::~ArxDbgUiPrDoubleDef
**
**  **jma
**
*************************************/

ArxDbgUiPrDoubleDef::~ArxDbgUiPrDoubleDef()
{
}

/****************************************************************************
**
**  ArxDbgUiPrDoubleDef::go
**
**  **jma
**
*************************************/

ArxDbgUiPrBase::Status
ArxDbgUiPrDoubleDef::go()
{
    CString prompt;
    TCHAR defStr[512];
    int initFlag;

        // set up prompt
    acdbRToS(m_default, m_unit, m_precision, defStr);
    prompt.Format(_T("\n%s<%s>: "), message(), defStr);

        // set up init flag
    if (m_doubleType == kNoZero)
        initFlag = RSG_NOZERO;
    else if (m_doubleType == kNoNeg)
        initFlag = RSG_NONEG;
    else if (m_doubleType == kNoNegNoZero)
        initFlag = RSG_NOZERO+RSG_NONEG;
    else
        initFlag = 0;

    int result;
    while (1) {
        acedInitGet(initFlag, keyWords());
        result = acedGetReal(prompt, &m_value);

        if (result == RTNORM){
            if (inRange())
                return ArxDbgUiPrBase::kOk;
        }
        else if (result == RTKWORD) {
            const size_t kBufSize = 512;
            acedGetInput(m_keyWordPicked.GetBuffer(kBufSize), kBufSize);
            m_keyWordPicked.ReleaseBuffer();
            return ArxDbgUiPrBase::kKeyWord;
        }
        else if (result == RTNONE) {
            if (m_doubleType == ArxDbgUiPrDouble::kRange) {
                ASSERT(m_minVal != m_maxVal);    // make sure they set ranges!
                ASSERT((m_default >= m_minVal) && (m_default <= m_maxVal));
            }
            m_value = m_default;
            return ArxDbgUiPrBase::kOk;
        }
        else
            return ArxDbgUiPrBase::kCancel;
    }
}

