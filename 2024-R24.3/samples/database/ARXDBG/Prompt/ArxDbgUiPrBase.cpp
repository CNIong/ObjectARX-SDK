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
