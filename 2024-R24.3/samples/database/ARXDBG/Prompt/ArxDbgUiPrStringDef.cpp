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

#include "ArxDbgUiPrStringDef.h"



/****************************************************************************
**
**  ArxDbgUiPrStringDef::ArxDbgUiPrStringDef
**
**  **jma
**
*************************************/

ArxDbgUiPrStringDef::ArxDbgUiPrStringDef(LPCTSTR msg, LPCTSTR def, bool allowSpaces)
:   ArxDbgUiPrString(msg, allowSpaces),
    m_default(def)
{
    ASSERT(def != NULL);
}

/****************************************************************************
**
**  ArxDbgUiPrStringDef::~ArxDbgUiPrStringDef
**
**  **jma
**
*************************************/

ArxDbgUiPrStringDef::~ArxDbgUiPrStringDef()
{
}

/****************************************************************************
**
**  ArxDbgUiPrStringDef::go
**
**  **jma
**
*************************************/

ArxDbgUiPrBase::Status
ArxDbgUiPrStringDef::go()
{
    CString prompt;
    TCHAR val[512];
    int result;

    prompt.Format(_T("\n%s<%s>: "), message(), m_default);

    if (m_allowSpaces == Adesk::kTrue)
        result = acedGetString(1, prompt, val);
    else
        result = acedGetString(0, prompt, val);

    if (result == RTNORM) {
        if (val[0] == _T('\0'))
            m_value = m_default;
        else
            m_value = val;
        return ArxDbgUiPrBase::kOk;
    }
    else
        return ArxDbgUiPrBase::kCancel;
}

