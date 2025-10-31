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

#include "ArxDbgUiPrIntDef.h"



/****************************************************************************
**
**  ArxDbgUiPrIntDef::ArxDbgUiPrIntDef
**
**  **jma
**
*************************************/

ArxDbgUiPrIntDef::ArxDbgUiPrIntDef(LPCTSTR msg, LPCTSTR keyWordList, IntType type, int def)
:   ArxDbgUiPrInt(msg, keyWordList, type),
    m_default(def)
{
}

/****************************************************************************
**
**  ArxDbgUiPrIntDef::~ArxDbgUiPrIntDef
**
**  **jma
**
*************************************/

ArxDbgUiPrIntDef::~ArxDbgUiPrIntDef()
{
}

/****************************************************************************
**
**  ArxDbgUiPrIntDef::go
**
**  **jma
**
*************************************/

ArxDbgUiPrBase::Status
ArxDbgUiPrIntDef::go()
{
    CString prompt;
    int initFlag;

        // set up prompt
    prompt.Format(_T("\n%s<%d>: "), message(), m_default);

        // set up init flag
    if (m_intType == kNoZero)
        initFlag = RSG_NOZERO;
    else if (m_intType == kNoNeg)
        initFlag = RSG_NONEG;
    else if (m_intType == kNoNegNoZero)
        initFlag = RSG_NOZERO+RSG_NONEG;
    else
        initFlag = 0;

    while (1) {
        acedInitGet(initFlag, keyWords());
        int result = acedGetInt(prompt, &m_value);

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
        else if (result == RTNONE) {
            if (m_intType == ArxDbgUiPrInt::kRange) {
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

