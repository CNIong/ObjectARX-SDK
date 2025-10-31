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


