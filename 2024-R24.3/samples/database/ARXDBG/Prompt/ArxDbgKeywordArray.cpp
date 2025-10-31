//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxDbgKeywordArray.h"
#include "AcExtensionModule.h"



/****************************************************************************
**
**  ArxDbgKeywordInfo::ArxDbgKeywordInfo
**
**  **jma
**
*************************************/

ArxDbgKeywordInfo::ArxDbgKeywordInfo(const CString& localKword,
                               const CString& globalKword,
                               const CString& optionStr)
:   m_localKword(localKword),
    m_globalKword(globalKword),
    m_optionStr(optionStr),
    m_isVisible(true),
    m_isEnabled(true),
    m_isDefault(false)
{
    ASSERT(localKword.IsEmpty() == FALSE);
    ASSERT(globalKword.IsEmpty() == FALSE);
    ASSERT(optionStr.IsEmpty() == FALSE);
}

/****************************************************************************
**
**  ArxDbgKeywordInfo::~ArxDbgKeywordInfo
**
**  **jma
**
*************************************/

ArxDbgKeywordInfo::~ArxDbgKeywordInfo()
{
}

/****************************************************************************
**
**  ArxDbgKeywordInfo::localKeyword
**
**  **jma
**
*************************************/

const CString&
ArxDbgKeywordInfo::localKeyword() const
{
    return m_localKword;
}

/****************************************************************************
**
**  ArxDbgKeywordInfo::setLocalKeyword
**
**  **jma
**
*************************************/

void
ArxDbgKeywordInfo::setLocalKeyword(const CString& kword)
{
    m_localKword = kword;
}

/****************************************************************************
**
**  ArxDbgKeywordInfo::globalKeyword
**
**  **jma
**
*************************************/

const CString&
ArxDbgKeywordInfo::globalKeyword() const
{
    return m_globalKword;
}

/****************************************************************************
**
**  ArxDbgKeywordInfo::setGlobalKeyword
**
**  **jma
**
*************************************/

void
ArxDbgKeywordInfo::setGlobalKeyword(const CString& kword)
{
    m_globalKword = kword;
}

/****************************************************************************
**
**  ArxDbgKeywordInfo::optionStr
**
**  **jma
**
*************************************/

const CString&
ArxDbgKeywordInfo::optionStr() const
{
    return m_optionStr;
}

/****************************************************************************
**
**  ArxDbgKeywordInfo::setOptionStr
**
**  **jma
**
*************************************/

void
ArxDbgKeywordInfo::setOptionStr(const CString& str)
{
    m_optionStr = str;
}

/****************************************************************************
**
**  ArxDbgKeywordInfo::isVisible
**
**  **jma
**
*************************************/

bool
ArxDbgKeywordInfo::isVisible() const
{
    return m_isVisible;
}

/****************************************************************************
**
**  ArxDbgKeywordInfo::setIsVisible
**
**  **jma
**
*************************************/

void
ArxDbgKeywordInfo::setIsVisible(bool itIs)
{
    m_isVisible = itIs;
}

/****************************************************************************
**
**  ArxDbgKeywordInfo::isEnabled
**
**  **jma
**
*************************************/

bool
ArxDbgKeywordInfo::isEnabled() const
{
    return m_isEnabled;
}

/****************************************************************************
**
**  ArxDbgKeywordInfo::setIsEnabled
**
**  **jma
**
*************************************/

void
ArxDbgKeywordInfo::setIsEnabled(bool itIs)
{
    m_isEnabled = itIs;
}

/****************************************************************************
**
**  ArxDbgKeywordInfo::isDefault
**
**  **jma
**
*************************************/

bool
ArxDbgKeywordInfo::isDefault() const
{
    return m_isDefault;
}

/****************************************************************************
**
**  ArxDbgKeywordInfo::setIsDefault
**
**  **jma
**
*************************************/

void
ArxDbgKeywordInfo::setIsDefault(bool itIs)
{
    m_isDefault = itIs;
}



/////////////////////////////////////////////////////////////////////////////
/////////////////////////// ARXDBG KEYWORD ARRAY ////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**  ArxDbgKeywordArray::ArxDbgKeywordArray
**
**  **jma
**
*************************************/

ArxDbgKeywordArray::ArxDbgKeywordArray(HINSTANCE resDllInstance)
:   m_resDllHandle(resDllInstance)
{
}

/****************************************************************************
**
**  ArxDbgKeywordArray::~ArxDbgKeywordArray
**
**  **jma
**
*************************************/

ArxDbgKeywordArray::~ArxDbgKeywordArray()
{
    deleteAll();
}

/****************************************************************************
**
**  ArxDbgKeywordArray::count
**
**  **jma
**
*************************************/

int
ArxDbgKeywordArray::count() const
{
    return m_keywordArray.length();
}

/****************************************************************************
**
**  ArxDbgKeywordArray::append
**
**  **jma
**
*************************************/

void
ArxDbgKeywordArray::append(LPCTSTR localKword, LPCTSTR globalKword,
                                bool isVisible,
                                bool isEnabled)
{
    ArxDbgKeywordInfo* tmpInfo = new ArxDbgKeywordInfo(localKword, globalKword, localKword);
    tmpInfo->setIsVisible(isVisible);
    tmpInfo->setIsEnabled(isEnabled);

    m_keywordArray.append(tmpInfo);
}

/****************************************************************************
**
**  ArxDbgKeywordArray::append
**
**  **jma
**
*************************************/

void
ArxDbgKeywordArray::append(UINT localKwordResId, LPCTSTR globalKword,
                                    bool isVisible,
                                    bool isEnabled)
{
	CAcModuleResourceOverride(m_resDllInstance);
    CString str;
	str.LoadString(localKwordResId);

    ArxDbgKeywordInfo* tmpInfo = new ArxDbgKeywordInfo(str, globalKword, str);
    tmpInfo->setIsVisible(isVisible);
    tmpInfo->setIsEnabled(isEnabled);

    m_keywordArray.append(tmpInfo);
}

/****************************************************************************
**
**  ArxDbgKeywordArray::append
**
**  **jma
**
*************************************/

void
ArxDbgKeywordArray::append(LPCTSTR localKword, LPCTSTR globalKword,
                                LPCTSTR optionStr,
                                bool isVisible,
                                bool isEnabled)
{
    ArxDbgKeywordInfo* tmpInfo = new ArxDbgKeywordInfo(localKword, globalKword, optionStr);
    tmpInfo->setIsVisible(isVisible);
    tmpInfo->setIsEnabled(isEnabled);

    m_keywordArray.append(tmpInfo);
}

/****************************************************************************
**
**  ArxDbgKeywordArray::append
**
**  **jma
**
*************************************/

void
ArxDbgKeywordArray::append(UINT localKwordResId, LPCTSTR globalKword,
                                    UINT optionStrId,
                                    bool isVisible,
                                    bool isEnabled)
{
	CAcModuleResourceOverride(m_resDllInstance);

    CString localKwordStr;
	localKwordStr.LoadString(localKwordResId);

    CString optionStr;
	optionStr.LoadString(optionStrId);

    ArxDbgKeywordInfo* tmpInfo = new ArxDbgKeywordInfo(localKwordStr, globalKword, optionStr);
    tmpInfo->setIsVisible(isVisible);
    tmpInfo->setIsEnabled(isEnabled);

    m_keywordArray.append(tmpInfo);
}

/****************************************************************************
**
**  ArxDbgKeywordArray::deleteAll
**
**  **jma
**
*************************************/

void
ArxDbgKeywordArray::deleteAll()
{
    ArxDbgKeywordInfo* tmpInfo;

    int len = m_keywordArray.length();
    for (int i=0; i<len; i++) {
        tmpInfo = static_cast<ArxDbgKeywordInfo*>(m_keywordArray[i]);
        delete tmpInfo;
    }

    m_keywordArray.setLogicalLength(0);
}

/****************************************************************************
**
**  ArxDbgKeywordArray::getAt
**
**  **jma
**
*************************************/

ArxDbgKeywordInfo*
ArxDbgKeywordArray::getAt(int index)
{
    return static_cast<ArxDbgKeywordInfo*>(m_keywordArray[index]);
}

/****************************************************************************
**
**  ArxDbgKeywordArray::find
**
**  **jma
**
*************************************/

bool
ArxDbgKeywordArray::find(LPCTSTR kwordPicked, int& indexFoundAt)
{
    ArxDbgKeywordInfo* tmpInfo;
    int len = m_keywordArray.length();
    for (int i=0; i<len; i++) {
        tmpInfo = static_cast<ArxDbgKeywordInfo*>(m_keywordArray[i]);

        if (_tcscmp(kwordPicked, tmpInfo->globalKeyword()) == 0) {
            ASSERT(tmpInfo->isEnabled());

            indexFoundAt = i;
            return true;
        }
    }

    return false;
}

/****************************************************************************
**
**  ArxDbgKeywordArray::findByJigIndex
**      jig indexes for kwords only account for enabled ones.  So,
**  go through the array and find out the actual index that corresponds
**  to what the jig thinks the kword is.
**
**  **jma
**
*************************************/

bool
ArxDbgKeywordArray::findByJigIndex(int jigIndex, int& actualIndex)
{
    int enabledKwordCount = 0;

    ArxDbgKeywordInfo* tmpInfo;
    int len = m_keywordArray.length();
    for (int i=0; i<len; i++) {
        tmpInfo = static_cast<ArxDbgKeywordInfo*>(m_keywordArray[i]);

        if (tmpInfo->isEnabled()) {
                // jig kword indexes start at 1, not 0, so increment first
            enabledKwordCount++;

            if (jigIndex == enabledKwordCount) {
                actualIndex = i;
                return true;
            }
        }
    }

    return false;
}

/****************************************************************************
**
**  ArxDbgKeywordArray::getActualIndexRange
**
**  **jma
**
*************************************/

bool
ArxDbgKeywordArray::getActualIndexRange(int& startIndex, int& endIndex)
{
    int actualEnd = m_keywordArray.length() - 1;

    if (startIndex == -1)
        startIndex = 0;
    if (endIndex == -1)
        endIndex = actualEnd;

    if (endIndex < startIndex) {    // equal is OK, but not less than
        ASSERT(0);
        return false;
    }
    if ((startIndex > actualEnd) || (endIndex > actualEnd)) {
        ASSERT(0);
        return false;
    }

    return true;
}

/****************************************************************************
**
**  ArxDbgKeywordArray::setEnabled
**
**  **jma
**
*************************************/

void
ArxDbgKeywordArray::setEnabled(bool isEnabled, int startIndex, int endIndex)
{
    if (getActualIndexRange(startIndex, endIndex) == false)
        return;

    ArxDbgKeywordInfo* tmpInfo;
    for (int i=startIndex; i<=endIndex; i++) {
        tmpInfo = static_cast<ArxDbgKeywordInfo*>(m_keywordArray[i]);
        tmpInfo->setIsEnabled(isEnabled);

            // setEnable will control visibility as well...
			// if you want the keyword enabled but invisible, you need to call
			// setIsVisible after setEnabled.
        tmpInfo->setIsVisible(isEnabled);
    }
}

/****************************************************************************
**
**  ArxDbgKeywordArray::setVisible
**
**  **jma
**
*************************************/

void
ArxDbgKeywordArray::setVisible(bool isVisible, int startIndex, int endIndex)
{
    if (getActualIndexRange(startIndex, endIndex) == false)
        return;

    ArxDbgKeywordInfo* tmpInfo;
    for (int i=startIndex; i<=endIndex; i++) {
        tmpInfo = static_cast<ArxDbgKeywordInfo*>(m_keywordArray[i]);
        tmpInfo->setIsVisible(isVisible);
    }
}

/****************************************************************************
**
**  ArxDbgKeywordArray::setAsDefault
**      set this item as the lone default
**
**  **jma
**
*************************************/

void
ArxDbgKeywordArray::setAsDefault(int index)
{
    ArxDbgKeywordInfo* tmpInfo;
    int len = m_keywordArray.length();
    for (int i=0; i<len; i++) {
        tmpInfo = static_cast<ArxDbgKeywordInfo*>(m_keywordArray[i]);
        if (i == index)
            tmpInfo->setIsDefault(true);
        else
            tmpInfo->setIsDefault(false);
    }
}

/****************************************************************************
**
**  ArxDbgKeywordArray::makeKeywordList
**
**  **jma
**
*************************************/

void
ArxDbgKeywordArray::makeKeywordList(CString& str)
{
    str.Empty();

    CString localKwords, globalKwords;

    bool isFirst = true;

    ArxDbgKeywordInfo* tmpInfo;
    int len = m_keywordArray.length();
    for (int i=0; i<len; i++) {
        tmpInfo = static_cast<ArxDbgKeywordInfo*>(m_keywordArray[i]);
        if (tmpInfo->isEnabled()) {
            if (isFirst == Adesk::kFalse) {
                localKwords += _T(" ");   // add seperator space
                globalKwords += _T(" ");  // add seperator space
            }
            else
                isFirst = false;

            localKwords += tmpInfo->localKeyword();
            globalKwords += tmpInfo->globalKeyword();
        }
    }

		// see documentation for acedGetKeyword() for an explanation of how to do
		// local and global keywords
    str.Format(_T("%s _ %s"), static_cast<LPCTSTR>(localKwords), static_cast<LPCTSTR>(globalKwords));
}

/****************************************************************************
**
**  ArxDbgKeywordArray::makeOptionsList
**
**  **jma
**
*************************************/

void
ArxDbgKeywordArray::makeOptionsList(CString& str)
{
    str.Empty();

    CString opsStr;

    bool isFirst = true;

    ArxDbgKeywordInfo* tmpInfo;
    int len = m_keywordArray.length();
    for (int i=0; i<len; i++) {
        tmpInfo = static_cast<ArxDbgKeywordInfo*>(m_keywordArray[i]);

        if (tmpInfo->isDefault()) {
            ASSERT(0);  // shouldn't have called this function!
            continue;
        }

        if (tmpInfo->isEnabled() && tmpInfo->isVisible()) {
            if (isFirst == false)
                opsStr += _T("/");   // add seperator
            else
                isFirst = false;

            opsStr += tmpInfo->optionStr();
        }
    }
        // Wrap options within square brackets "[op1/op2]" for rt-click menu support
    if (!opsStr.IsEmpty()) {
        str.Format(_T("[%s]"), static_cast<LPCTSTR>(opsStr));
    }
}

/****************************************************************************
**
**  ArxDbgKeywordArray::makeOptionsList
**
**  **jma
**
*************************************/

void
ArxDbgKeywordArray::makeOptionsList(CString& optionsStr, CString& defaultStr, bool includeDefInOptions)
{
    optionsStr.Empty();
    defaultStr.Empty();

    CString opsStr;

    bool isFirst = true;

    ArxDbgKeywordInfo* tmpInfo;
    int len = m_keywordArray.length();
    for (int i=0; i<len; i++) {
        tmpInfo = static_cast<ArxDbgKeywordInfo*>(m_keywordArray[i]);

        if (tmpInfo->isDefault()) {
            defaultStr = tmpInfo->localKeyword();

            if (includeDefInOptions == false) {
                continue;
            }
            else {
                ASSERT(tmpInfo->isEnabled());
            }
        }

        if (tmpInfo->isEnabled() && tmpInfo->isVisible()) {
            if (isFirst == false)
                opsStr += _T("/");   // add seperator
            else
                isFirst = false;

            opsStr += tmpInfo->optionStr();
        }
    }
        // Wrap options within square brackets "[op1/op2]" for rt-click menu support
    if (!opsStr.IsEmpty()) {
        optionsStr.Format(_T("[%s]"), static_cast<LPCTSTR>(opsStr));
    }
}
