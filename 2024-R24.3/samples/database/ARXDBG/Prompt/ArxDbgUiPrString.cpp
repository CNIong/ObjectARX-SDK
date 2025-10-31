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

#include "ArxDbgUiPrString.h"



/****************************************************************************
**
**  ArxDbgUiPrString::ArxDbgUiPrString
**
**  **jma
**
*************************************/

ArxDbgUiPrString::ArxDbgUiPrString(LPCTSTR msg, bool allowSpaces)
:   ArxDbgUiPrBase(msg, NULL),
	m_allowSpaces(allowSpaces)
{
}

/****************************************************************************
**
**  ArxDbgUiPrString::~ArxDbgUiPrString
**
**  **jma
**
*************************************/

ArxDbgUiPrString::~ArxDbgUiPrString()
{
}

/****************************************************************************
**
**  ArxDbgUiPrString::go
**
**  **jma
**
*************************************/

ArxDbgUiPrBase::Status
ArxDbgUiPrString::go()
{
    CString prompt;
    TCHAR val[512];
    int result;

    prompt.Format(_T("\n%s: "), message());

    if (m_allowSpaces == true)
        result = acedGetString(1, prompt, val);
    else
        result = acedGetString(0, prompt, val);

    if (result == RTNORM) {
        m_value = val;
        return ArxDbgUiPrBase::kOk;
    }
    else
        return ArxDbgUiPrBase::kCancel;
}

/****************************************************************************
**
**  ArxDbgUiPrString::value
**
**  **jma
**
*************************************/

LPCTSTR
ArxDbgUiPrString::value()
{
    return m_value;
}

/****************************************************************************
**
**  ArxDbgUiPrString::keyWords
**
**  **jma
**
*************************************/

LPCTSTR
ArxDbgUiPrString::keyWords() const
{
    return _T("");
}

/****************************************************************************
**
**  ArxDbgUiPrString::setKeyWords
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUiPrString::setKeyWords(LPCTSTR keyWordList)
{
    return Acad::eNotApplicable;
}

/****************************************************************************
**
**  ArxDbgUiPrString::keyWordPicked
**
**  **jma
**
*************************************/

LPCTSTR
ArxDbgUiPrString::keyWordPicked()
{
    return NULL;
}

/****************************************************************************
**
**  ArxDbgUiPrString::isKeyWordPicked
**
**  **jma
**
*************************************/

bool
ArxDbgUiPrString::isKeyWordPicked(LPCTSTR matchKeyWord)
{
    return false;
}


