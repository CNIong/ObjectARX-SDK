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
    int result = acedGetKword(prompt, m_keyWordPicked.GetBuffer(512));
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

