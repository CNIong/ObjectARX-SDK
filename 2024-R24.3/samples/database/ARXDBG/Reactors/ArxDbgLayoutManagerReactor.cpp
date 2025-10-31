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

#include "ArxDbgLayoutManagerReactor.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxDbgLayoutManagerReactor, AcDbLayoutManagerReactor);

/****************************************************************************
**
**  ArxDbgLayoutManagerReactor::ArxDbgLayoutManagerReactor
**
**  **jma
**
*************************************/

ArxDbgLayoutManagerReactor::ArxDbgLayoutManagerReactor()
{
	acdbHostApplicationServices()->layoutManager()->addReactor(this);
}

/****************************************************************************
**
**  ArxDbgLayoutManagerReactor::~ArxDbgLayoutManagerReactor
**
**  **jma
**
*************************************/

ArxDbgLayoutManagerReactor::~ArxDbgLayoutManagerReactor()
{
	acdbHostApplicationServices()->layoutManager()->removeReactor(this);
}

/****************************************************************************
**
**  ArxDbgLayoutManagerReactor::layoutCreated
**
**  **jma
**
*************************************/

void
ArxDbgLayoutManagerReactor::layoutCreated(const TCHAR* newLayoutName, const AcDbObjectId& layoutId)
{
	printReactorMessage(_T("Layout Created"), newLayoutName);
}

/****************************************************************************
**
**  ArxDbgLayoutManagerReactor::layoutToBeRemoved
**
**  **jma
**
*************************************/

void
ArxDbgLayoutManagerReactor::layoutToBeRemoved(const TCHAR* layoutName, const AcDbObjectId& layoutId)
{
	printReactorMessage(_T("Layout To Be Removed"), layoutName);
}

/****************************************************************************
**
**  ArxDbgLayoutManagerReactor::layoutRemoved
**
**  **jma
**
*************************************/

void
ArxDbgLayoutManagerReactor::layoutRemoved(const TCHAR* layoutName, const AcDbObjectId& layoutId)
{
	printReactorMessage(_T("Layout Removed"), layoutName);
}

/****************************************************************************
**
**  ArxDbgLayoutManagerReactor::abortLayoutRemoved
**
**  **jma
**
*************************************/

void
ArxDbgLayoutManagerReactor::abortLayoutRemoved(const TCHAR* layoutName, const AcDbObjectId& layoutId)
{
	printReactorMessage(_T("Abort Layout Removed"), layoutName);
}

/****************************************************************************
**
**  ArxDbgLayoutManagerReactor::layoutToBeCopied
**
**  **jma
**
*************************************/

void
ArxDbgLayoutManagerReactor::layoutToBeCopied(const TCHAR* layoutName, const AcDbObjectId& oldLayoutId)
{
	printReactorMessage(_T("Layout To Be Copied"), layoutName);
}

/****************************************************************************
**
**  ArxDbgLayoutManagerReactor::layoutCopied
**
**  **jma
**
*************************************/

void
ArxDbgLayoutManagerReactor::layoutCopied(const TCHAR* oldLayoutName,
				const AcDbObjectId& oldLayoutId,
				const TCHAR* newLayoutName,
				const AcDbObjectId& newLayoutId)
{
	printReactorMessage(_T("Layout Copied"), oldLayoutName, newLayoutName);
}

/****************************************************************************
**
**  ArxDbgLayoutManagerReactor::abortLayoutCopied
**
**  **jma
**
*************************************/

void
ArxDbgLayoutManagerReactor::abortLayoutCopied(const TCHAR* layoutName, const AcDbObjectId& layoutId)
{
	printReactorMessage(_T("Abort Layout Copied"), layoutName);
}

/****************************************************************************
**
**  ArxDbgLayoutManagerReactor::layoutToBeRenamed
**
**  **jma
**
*************************************/

void
ArxDbgLayoutManagerReactor::layoutToBeRenamed(const TCHAR* oldName,
				const TCHAR* newName, const AcDbObjectId& layoutId)
{
	printReactorMessage(_T("Layout To Be Renamed"), oldName, newName);
}

/****************************************************************************
**
**  ArxDbgLayoutManagerReactor::layoutsReordered
**
**  **jma
**
*************************************/

void
ArxDbgLayoutManagerReactor::layoutsReordered()
{
	printReactorMessage(_T("Layouts Reordered"), _T("All"));
}

/****************************************************************************
**
**  ArxDbgLayoutManagerReactor::layoutRenamed
**
**  **jma
**
*************************************/

void
ArxDbgLayoutManagerReactor::layoutRenamed(const TCHAR* oldName,
				const TCHAR* newName, const AcDbObjectId& layoutId)
{
	printReactorMessage(_T("Layout Renamed"), oldName, newName);
}

/****************************************************************************
**
**  ArxDbgLayoutManagerReactor::abortLayoutRename
**
**  **jma
**
*************************************/

void
ArxDbgLayoutManagerReactor::abortLayoutRename(const TCHAR* oldName,
				const TCHAR* newName, const AcDbObjectId& layoutId)
{
	printReactorMessage(_T("Abort Layout Rename"), oldName, newName);
}

/****************************************************************************
**
**  ArxDbgLayoutManagerReactor::layoutSwitched
**
**  **jma
**
*************************************/

void
ArxDbgLayoutManagerReactor::layoutSwitched(const TCHAR* newLayoutname, const AcDbObjectId& newLayoutId)
{
	printReactorMessage(_T("Layout Switched"), newLayoutname);
}

/****************************************************************************
**
**  ArxDbgLayoutManagerReactor::plotStyleTableChanged
**
**  **jma
**
*************************************/

void
ArxDbgLayoutManagerReactor::plotStyleTableChanged(const TCHAR* newTableName, const AcDbObjectId& layoutId)
{
	printReactorMessage(_T("Plot Style Table Changed"), newTableName);
}

/****************************************************************************
**
**  ArxDbgLayoutManagerReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgLayoutManagerReactor::printReactorMessage(LPCTSTR event, const TCHAR* layoutName) const
{
    acutPrintf(_T("\n%-15s : [%s, \"%s\"] "), _T("[LAYOUT REACTOR]"), event, layoutName);
}

/****************************************************************************
**
**  ArxDbgLayoutManagerReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgLayoutManagerReactor::printReactorMessage(LPCTSTR event, const TCHAR* layoutName1,
												const TCHAR* layoutName2) const
{
    acutPrintf(_T("\n%-15s : [%s, \"%s\" --> \"%s\"] "), _T("[LAYOUT REACTOR]"), event, layoutName1, layoutName2);
}

