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
        acedGetInput(m_keyWordPicked.GetBuffer(512));
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

