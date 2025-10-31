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

#include "ArxDbgUiPrKeyWord.h"



/****************************************************************************
**
**  ArxDbgUiPrKeyWord::ArxDbgUiPrKeyWord
**
**  **jma
**
*************************************/

ArxDbgUiPrKeyWord::ArxDbgUiPrKeyWord(LPCTSTR msg, LPCTSTR keyWordList)
:   ArxDbgUiPrBase(msg, keyWordList),
    m_allowNone(false)
{
}

/****************************************************************************
**
**  ArxDbgUiPrKeyWord::~ArxDbgUiPrKeyWord
**
**  **jma
**
*************************************/

ArxDbgUiPrKeyWord::~ArxDbgUiPrKeyWord()
{
}

/****************************************************************************
**
**  ArxDbgUiPrKeyWord::go
**
**  **jma
**
*************************************/

ArxDbgUiPrBase::Status
ArxDbgUiPrKeyWord::go()
{
    CString prompt;

    prompt.Format(_T("\n%s: "), message());

    int initFlag = 0;
    if (m_allowNone == false)
        initFlag += RSG_NONULL;

    acedInitGet(initFlag, keyWords());
    const size_t kBufSize = 512;
    int result = acedGetKword(prompt, m_keyWordPicked.GetBuffer(kBufSize), kBufSize);
    m_keyWordPicked.ReleaseBuffer();

    if (result == RTNORM)
        return ArxDbgUiPrBase::kOk;
    else if (result == RTNONE) {
        ASSERT(m_allowNone == Adesk::kTrue);
        return ArxDbgUiPrBase::kNone;
    }
    else
        return ArxDbgUiPrBase::kCancel;
}

/****************************************************************************
**
**  ArxDbgUiPrKeyWord::value
**
**  **jma
**
*************************************/

LPCTSTR
ArxDbgUiPrKeyWord::value()
{
    return ArxDbgUiPrBase::keyWordPicked();
}

/****************************************************************************
**
**  ArxDbgUiPrKeyWord::setAllowNone
**
**  **jma
**
*************************************/

void
ArxDbgUiPrKeyWord::setAllowNone(bool allowIt)
{
    m_allowNone = allowIt;
}


