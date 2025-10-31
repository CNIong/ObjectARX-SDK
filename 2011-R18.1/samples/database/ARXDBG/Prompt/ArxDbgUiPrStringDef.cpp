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

