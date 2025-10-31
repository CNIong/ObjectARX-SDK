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

#include "ArxDbgDLinkerReactor.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxDbgDLinkerReactor, AcRxDLinkerReactor);

/****************************************************************************
**
**  ArxDbgDLinkerReactor::ArxDbgDLinkerReactor
**
**  **jma
**
*************************************/

ArxDbgDLinkerReactor::ArxDbgDLinkerReactor()
{
    acrxDynamicLinker->addReactor(this);
}

/****************************************************************************
**
**  ArxDbgDLinkerReactor::~ArxDbgDLinkerReactor
**
**  **jma
**
*************************************/

ArxDbgDLinkerReactor::~ArxDbgDLinkerReactor()
{
    acrxDynamicLinker->removeReactor(this);
}

/****************************************************************************
**
**  ArxDbgDLinkerReactor::rxAppWillBeLoaded
**
**  **jma
**
*************************************/

void
ArxDbgDLinkerReactor::rxAppWillBeLoaded(const TCHAR* moduleName)
{
    printReactorMessage(_T("ARX App Will Be Loaded"), moduleName);
}

/****************************************************************************
**
**  ArxDbgDLinkerReactor::rxAppLoaded
**
**  **jma
**
*************************************/

void
ArxDbgDLinkerReactor::rxAppLoaded(const TCHAR* moduleName)
{
    printReactorMessage(_T("ARX App Loaded"), moduleName);
}

/****************************************************************************
**
**  ArxDbgDLinkerReactor::rxAppLoadAborted
**
**  **jma
**
*************************************/

void
ArxDbgDLinkerReactor::rxAppLoadAborted(const TCHAR* moduleName)
{
    printReactorMessage(_T("ARX App Load Aborted"), moduleName);
}

/****************************************************************************
**
**  ArxDbgDLinkerReactor::rxAppWillBeUnloaded
**
**  **jma
**
*************************************/

void
ArxDbgDLinkerReactor::rxAppWillBeUnloaded(const TCHAR* moduleName)
{
    printReactorMessage(_T("ARX App Will Be Unloaded"), moduleName);
}

/****************************************************************************
**
**  ArxDbgDLinkerReactor::rxAppUnloaded
**
**  **jma
**
*************************************/

void
ArxDbgDLinkerReactor::rxAppUnloaded(const TCHAR* moduleName)
{
    printReactorMessage(_T("ARX App Unloaded"), moduleName);
}

/****************************************************************************
**
**  ArxDbgDLinkerReactor::rxAppUnloadAborted
**
**  **jma
**
*************************************/

void
ArxDbgDLinkerReactor::rxAppUnloadAborted(const TCHAR* moduleName)
{
    printReactorMessage(_T("ARX App Unload Aborted"), moduleName);
}

/****************************************************************************
**
**  ArxDbgDLinkerReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgDLinkerReactor::printReactorMessage(LPCTSTR event, const TCHAR* moduleName) const
{
    acutPrintf(_T("\n%-15s : [%s = %s] "), _T("[DLINKER REACTOR]"), event, moduleName);
}
