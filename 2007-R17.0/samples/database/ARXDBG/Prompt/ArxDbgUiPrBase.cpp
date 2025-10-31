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

#include "ArxDbgUiPrBase.h"



/****************************************************************************
**
**  ArxDbgUiPrBase::ArxDbgUiPrBase
**
**  **jma
**
*************************************/

ArxDbgUiPrBase::ArxDbgUiPrBase(LPCTSTR msg, LPCTSTR keyWordList)
:	m_keyWords(keyWordList),
	m_message(msg)
{
    ASSERT(msg != NULL);
}

/****************************************************************************
**
**  ArxDbgUiPrBase::~ArxDbgUiPrBase
**
**  **jma
**
*************************************/

ArxDbgUiPrBase::~ArxDbgUiPrBase()
{
}

/****************************************************************************
**
**  ArxDbgUiPrBase::keyWords
**
**  **jma
**
*************************************/

LPCTSTR
ArxDbgUiPrBase::keyWords() const
{
   return m_keyWords;
}

/****************************************************************************
**
**  ArxDbgUiPrBase::setKeyWords
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUiPrBase::setKeyWords(LPCTSTR keyWordList)
{
    ASSERT(keyWordList != NULL);

	m_keyWords = keyWordList;

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgUiPrBase::message
**
**  **jma
**
*************************************/

LPCTSTR
ArxDbgUiPrBase::message() const
{
   return m_message;
}

/****************************************************************************
**
**  ArxDbgUiPrBase::setMessage
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUiPrBase::setMessage(LPCTSTR msg)
{
    m_message = msg;
    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgUiPrBase::keyWordPicked
**
**  **jma
**
*************************************/

LPCTSTR
ArxDbgUiPrBase::keyWordPicked() const
{
    ASSERT(m_keyWordPicked.IsEmpty() == false);
    return m_keyWordPicked;
}

/****************************************************************************
**
**  ArxDbgUiPrBase::isKeyWordPicked
**
**  **jma
**
*************************************/

bool
ArxDbgUiPrBase::isKeyWordPicked(LPCTSTR keyWordMatch)
{
    ASSERT(m_keyWordPicked.IsEmpty() == false);
    ASSERT(keyWordMatch != NULL);

    if (m_keyWordPicked == keyWordMatch)
        return true;
    else
        return false;
}
