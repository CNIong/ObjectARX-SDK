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

#include "ArxDbgUiPrCorner.h"



/****************************************************************************
**
**  ArxDbgUiPrCorner::ArxDbgUiPrCorner
**
**  **jma
**
*************************************/

ArxDbgUiPrCorner::ArxDbgUiPrCorner(LPCTSTR msg, LPCTSTR keyWordList, const AcGePoint3d& basePt)
:   ArxDbgUiPrBase(msg, keyWordList),
    m_basePt(basePt),
    m_value(AcGePoint3d::kOrigin),
	m_useDashedLine(false),
	m_noLimCheck(false)
{
}

/****************************************************************************
**
**  ArxDbgUiPrCorner::~ArxDbgUiPrCorner
**
**  **jma
**
*************************************/

ArxDbgUiPrCorner::~ArxDbgUiPrCorner()
{
}

/****************************************************************************
**
**  ArxDbgUiPrCorner::go
**
**  **jma
**
*************************************/

ArxDbgUiPrBase::Status
ArxDbgUiPrCorner::go()
{
    CString prompt;
    int result;
    ads_point adsPt;
    int initFlag = RSG_NONULL;

    if (m_noLimCheck == true)
        initFlag += RSG_NOLIM;
    if (m_useDashedLine == true)
        initFlag += RSG_DASH;

    prompt.Format(_T("\n%s: "), message());

    acedInitGet(initFlag, keyWords());
    result = acedGetCorner(asDblArray(m_basePt), prompt, adsPt);

    if (result == RTNORM) {
        m_value = asPnt3d(adsPt);
        return ArxDbgUiPrBase::kOk;
    }
    else if (result == RTKWORD) {
        const size_t kBufSize = 512;
        acedGetInput(m_keyWordPicked.GetBuffer(kBufSize), kBufSize);
        m_keyWordPicked.ReleaseBuffer();
        return ArxDbgUiPrBase::kKeyWord;
    }
    else
        return ArxDbgUiPrBase::kCancel;
}

/****************************************************************************
**
**  ArxDbgUiPrCorner::setBasePt
**
**  **jma
**
*************************************/

void
ArxDbgUiPrCorner::setBasePt(const AcGePoint3d& basePt)
{
    m_basePt = basePt;
}

/****************************************************************************
**
**  ArxDbgUiPrCorner::setUseDashedLine
**
**  **jma
**
*************************************/

void
ArxDbgUiPrCorner::setUseDashedLine(bool useIt)
{
    m_useDashedLine = useIt;
}

/****************************************************************************
**
**  ArxDbgUiPrCorner::setNoLimitsCheck
**
**  **jma
**
*************************************/

void
ArxDbgUiPrCorner::setNoLimitsCheck(bool noCheck)
{
    m_noLimCheck = noCheck;
}

/****************************************************************************
**
**  ArxDbgUiPrCorner::value
**
**  **jma
**
*************************************/

const AcGePoint3d&
ArxDbgUiPrCorner::value()
{
    return m_value;
}

