//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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

#include "stdafx.h"
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
ArxDbgLayoutManagerReactor::layoutCreated(const char* newLayoutName, const AcDbObjectId& layoutId)
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
ArxDbgLayoutManagerReactor::layoutToBeRemoved(const char* layoutName, const AcDbObjectId& layoutId)
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
ArxDbgLayoutManagerReactor::layoutRemoved(const char* layoutName, const AcDbObjectId& layoutId)
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
ArxDbgLayoutManagerReactor::abortLayoutRemoved(const char* layoutName, const AcDbObjectId& layoutId)
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
ArxDbgLayoutManagerReactor::layoutToBeCopied(const char* layoutName, const AcDbObjectId& oldLayoutId)
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
ArxDbgLayoutManagerReactor::layoutCopied(const char* oldLayoutName,
				const AcDbObjectId& oldLayoutId,
				const char* newLayoutName,
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
ArxDbgLayoutManagerReactor::abortLayoutCopied(const char* layoutName, const AcDbObjectId& layoutId)
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
ArxDbgLayoutManagerReactor::layoutToBeRenamed(const char* oldName,
				const char* newName, const AcDbObjectId& layoutId)
{
	printReactorMessage(_T("Layout To Be Renamed"), oldName, newName);
}

/****************************************************************************
**
**  ArxDbgLayoutManagerReactor::layoutRenamed
**
**  **jma
**
*************************************/

void
ArxDbgLayoutManagerReactor::layoutRenamed(const char* oldName,
				const char* newName, const AcDbObjectId& layoutId)
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
ArxDbgLayoutManagerReactor::abortLayoutRename(const char* oldName,
				const char* newName, const AcDbObjectId& layoutId)
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
ArxDbgLayoutManagerReactor::layoutSwitched(const char* newLayoutname, const AcDbObjectId& newLayoutId)
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
ArxDbgLayoutManagerReactor::plotStyleTableChanged(const char* newTableName, const AcDbObjectId& layoutId)
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
ArxDbgLayoutManagerReactor::printReactorMessage(LPCTSTR event, const char* layoutName) const
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
ArxDbgLayoutManagerReactor::printReactorMessage(LPCTSTR event, const char* layoutName1,
												const char* layoutName2) const
{
    acutPrintf(_T("\n%-15s : [%s, \"%s\" --> \"%s\"] "), _T("[LAYOUT REACTOR]"), event, layoutName1, layoutName2);
}

