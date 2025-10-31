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
            acedGetInput(m_keyWordPicked.GetBuffer(512));
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


