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

#include "ArxDbgUiPrAngleDef.h"



/****************************************************************************
**
**  ArxDbgUiPrAngleDef::ArxDbgUiPrAngleDef
**
**  **jma
**
*************************************/

ArxDbgUiPrAngleDef::ArxDbgUiPrAngleDef(LPCTSTR msg, LPCTSTR keyWordList, AngleType type, double def)
:   ArxDbgUiPrAngle(msg, keyWordList, type)
{
    m_default = def;
}

/****************************************************************************
**
**  ArxDbgUiPrAngleDef::ArxDbgUiPrAngleDef
**
**  **jma
**
*************************************/

ArxDbgUiPrAngleDef::ArxDbgUiPrAngleDef(LPCTSTR msg, LPCTSTR keyWordList, AngleType type,
            const AcGePoint3d& basePt, double def)
:   ArxDbgUiPrAngle(msg, keyWordList, type, basePt)
{
    m_default = def;
}

/****************************************************************************
**
**  ArxDbgUiPrAngleDef::~ArxDbgUiPrAngleDef
**
**  **jma
**
*************************************/

ArxDbgUiPrAngleDef::~ArxDbgUiPrAngleDef()
{
}

/****************************************************************************
**
**  ArxDbgUiPrAngleDef::go
**
**  **jma
**
*************************************/

ArxDbgUiPrBase::Status
ArxDbgUiPrAngleDef::go()
{
    CString prompt;
    TCHAR defStr[512];
    int initFlag;

        // set up prompt
    acdbAngToS(m_default, m_unit, m_precision, defStr);
    prompt.Format(_T("\n%s<%s>: "), message(), defStr);

        // set up init flag
    if (m_angType == kNoZero)
        initFlag = RSG_NOZERO;
    else
        initFlag = 0;

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
        else if(result == RTKWORD) {
            const size_t kBufSize = 512;
            acedGetInput(m_keyWordPicked.GetBuffer(kBufSize), kBufSize);
            m_keyWordPicked.ReleaseBuffer();
            return ArxDbgUiPrBase::kKeyWord;
        }
        else if (result == RTNONE) {
            if (m_angType == ArxDbgUiPrAngle::kRange) {
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


