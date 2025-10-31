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

#include "ArxDbgUiPrPoint.h"
#include "ArxDbgUtils.h"
#include "SdSysVar.h"



/****************************************************************************
**
**  ArxDbgUiPrPoint::init
**      handle the common work for the constructors
**
**  **jma
**
*************************************/

void
ArxDbgUiPrPoint::init()
{
    m_value = AcGePoint3d::kOrigin;
    m_useDashedLine = false;
    m_noLimCheck = false;
    m_allowNone = false;
}

/****************************************************************************
**
**  ArxDbgUiPrPoint::ArxDbgUiPrPoint
**
**  **jma
**
*************************************/

ArxDbgUiPrPoint::ArxDbgUiPrPoint(LPCTSTR msg, LPCTSTR keyWordList)
:   ArxDbgUiPrBase(msg, keyWordList),
    m_basePt(AcGePoint3d::kOrigin),
    m_useBasePt(false)
{
    init();
}

/****************************************************************************
**
**  ArxDbgUiPrPoint::ArxDbgUiPrPoint
**
**  **jma
**
*************************************/

ArxDbgUiPrPoint::ArxDbgUiPrPoint(LPCTSTR msg, LPCTSTR keyWordList, const AcGePoint3d& basePt)
:   ArxDbgUiPrBase(msg, keyWordList),
    m_basePt(basePt),
    m_useBasePt(true)
{
    init();
}

/****************************************************************************
**
**  ArxDbgUiPrPoint::~ArxDbgUiPrPoint
**
**  **jma
**
*************************************/

ArxDbgUiPrPoint::~ArxDbgUiPrPoint()
{
}

/****************************************************************************
**
**  ArxDbgUiPrPoint::go
**
**  **jma
**
*************************************/

ArxDbgUiPrBase::Status
ArxDbgUiPrPoint::go()
{
    CString prompt;
    int result;
    ads_point adsPt;
    int initFlag = 0;

    if (m_allowNone == Adesk::kFalse)
        initFlag += RSG_NONULL;
    if (m_noLimCheck == Adesk::kTrue)
        initFlag += RSG_NOLIM;
    if (m_useDashedLine == Adesk::kTrue)
        initFlag += RSG_DASH;

    prompt.Format(_T("\n%s: "), message());

    acedInitGet(initFlag, keyWords());
    if (m_useBasePt)
        result = acedGetPoint(asDblArray(m_basePt), prompt, adsPt);
    else
        result = acedGetPoint(NULL, prompt, adsPt);

    if (result == RTNORM){
        m_value = asPnt3d(adsPt);
        setSysVar(_T("LASTPOINT"), m_value);
        return ArxDbgUiPrBase::kOk;
    }
    else if (result == RTNONE){
        ASSERT(m_allowNone == Adesk::kTrue);
        return ArxDbgUiPrBase::kNone;
    }
    else if (result == RTKWORD){
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
**  ArxDbgUiPrPoint::value
**
**  **jma
**
*************************************/

const AcGePoint3d&
ArxDbgUiPrPoint::value() const
{
    return m_value;
}

/****************************************************************************
**
**  ArxDbgUiPrPoint::basePt
**
**  **jma
**
*************************************/

const AcGePoint3d&
ArxDbgUiPrPoint::basePt() const
{
    return m_basePt;
}

/****************************************************************************
**
**  ArxDbgUiPrPoint::setBasePt
**
**  **jma
**
*************************************/

void
ArxDbgUiPrPoint::setBasePt(const AcGePoint3d& basePt)
{
    m_basePt = basePt;
    m_useBasePt = true;
}

/****************************************************************************
**
**  ArxDbgUiPrPoint::setUseBasePt
**
**  **jma
**
*************************************/

void
ArxDbgUiPrPoint::setUseBasePt(bool useIt)
{
    m_useBasePt = useIt;
}

/****************************************************************************
**
**  ArxDbgUiPrPoint::setUseDashedLine
**
**  **jma
**
*************************************/

void
ArxDbgUiPrPoint::setUseDashedLine(bool useIt)
{
    m_useDashedLine = useIt;
}

/****************************************************************************
**
**  ArxDbgUiPrPoint::setNoLimitsCheck
**
**  **jma
**
*************************************/

void
ArxDbgUiPrPoint::setNoLimitsCheck(bool noCheck)
{
    m_noLimCheck = noCheck;
}

/****************************************************************************
**
**  ArxDbgUiPrPoint::setAllowNone
**
**  **jma
**
*************************************/

void
ArxDbgUiPrPoint::setAllowNone(bool allowIt)
{
    m_allowNone = allowIt;
}


