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
    int result = acedGetKword(prompt, m_keyWordPicked.GetBuffer(512));
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


