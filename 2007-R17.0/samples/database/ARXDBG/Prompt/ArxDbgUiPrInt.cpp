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

