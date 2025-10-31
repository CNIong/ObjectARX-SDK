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

#include "ArxDbgUiPrKeyWordDef.h"



/****************************************************************************
**
**  ArxDbgUiPrKeyWordDef::ArxDbgUiPrKeyWordDef
**
**  **jma
**
*************************************/

ArxDbgUiPrKeyWordDef::ArxDbgUiPrKeyWordDef(LPCTSTR msg, LPCTSTR keyWordList, LPCTSTR def)
:   ArxDbgUiPrKeyWord(msg, keyWordList),
    m_default(def)
{
    ASSERT(def != NULL);
}

/****************************************************************************
**
**  ArxDbgUiPrKeyWordDef::~ArxDbgUiPrKeyWordDef
**
**  **jma
**
*************************************/

ArxDbgUiPrKeyWordDef::~ArxDbgUiPrKeyWordDef()
{
}

/****************************************************************************
**
**  ArxDbgUiPrKeyWordDef::go
**
**  **jma
**
*************************************/

ArxDbgUiPrBase::Status
ArxDbgUiPrKeyWordDef::go()
{
    CString prompt;

    prompt.Format(_T("\n%s<%s>: "), message(), m_default);

    acedInitGet(0, keyWords());
    const size_t kBufSize = 512;
    int result = acedGetKword(prompt, m_keyWordPicked.GetBuffer(kBufSize), kBufSize);
    m_keyWordPicked.ReleaseBuffer();

    if (result == RTNORM) {
        return ArxDbgUiPrBase::kOk;
    }
    else if (result == RTNONE) {
        if (keyWordMatch() == Adesk::kTrue)
            return ArxDbgUiPrBase::kOk;
        else
            return ArxDbgUiPrBase::kCancel;
    }
    else
        return ArxDbgUiPrBase::kCancel;
}

/****************************************************************************
**
**  ArxDbgUiPrKeyWordDef::keyWordMatch
**      Find the full keyword for this default, in case the default
**  was an abbreviation (like "Y" for "Yes").
**
**  **jma
**
*************************************/

bool
ArxDbgUiPrKeyWordDef::keyWordMatch()
{
    CString kword;
    CString keyWordList = keyWords();
    int defLen = m_default.GetLength();
    int kwordLen = keyWordList.GetLength();
    int i = 0;
    while (1) {
            // parse out an individual keyword
        kword.Empty();
        while ((i < kwordLen) && (keyWordList[i] != _T(' ')))
            kword += keyWordList[i++];

            // see if it matches the default
        if (!_tcsncmp(kword, m_default, defLen)) {
            m_keyWordPicked = kword;
            return true;
        }
        if (i >= kwordLen) {
            ASSERT(0);    // should never happen
            return false;
        }
        else {
            while (keyWordList[i] == _T(' ')) // chew any whitespace between words
                i++;
        }
    }
}

