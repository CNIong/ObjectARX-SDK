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
