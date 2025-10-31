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

#include "ArxDbgGsReactor.h"



//ACRX_NO_CONS_DEFINE_MEMBERS(ArxDbgGsReactor, AcGsReactor);	TBD: not derived off of AcRxObject yet!

/****************************************************************************
**
**  ArxDbgGsReactor::ArxDbgGsReactor
**
**  **jma
**
*************************************/

ArxDbgGsReactor::ArxDbgGsReactor()
{
// TBD: this isn't really good enough... it needs to get all CViews, not just
// the one that is current... will finish off later.
	AcGsClassFactory* gsFactory = acgsGetGsManager()->getGSClassFactory();
    if (gsFactory)
		gsFactory->addReactor(this);
}

/****************************************************************************
**
**  ArxDbgGsReactor::~ArxDbgGsReactor
**
**  **jma
**
*************************************/

ArxDbgGsReactor::~ArxDbgGsReactor()
{
	AcGsClassFactory* gsFactory = acgsGetGsManager()->getGSClassFactory();
    if (gsFactory)
		gsFactory->removeReactor(this);
}

/****************************************************************************
**
**  ArxDbgGsReactor::viewWasCreated
**
**  **jma
**
*************************************/

void
ArxDbgGsReactor::viewWasCreated(AcGsView* pView)
{
	printReactorMessage(_T("View Was Created"));
}

/****************************************************************************
**
**  ArxDbgGsReactor::viewToBeDestroyed
**
**  **jma
**
*************************************/

void
ArxDbgGsReactor::viewToBeDestroyed(AcGsView* pView)
{
	printReactorMessage(_T("View To Be Destroyed"));
}

/****************************************************************************
**
**  ArxDbgGsReactor::gsToBeUnloaded
**
**  **jma
**
*************************************/

void
ArxDbgGsReactor::gsToBeUnloaded(AcGsClassFactory* pClassFactory)
{
	printReactorMessage(_T("GS To Be Unloaded"));
}

/****************************************************************************
**
**  ArxDbgGsReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgGsReactor::printReactorMessage(LPCTSTR event) const
{
    acutPrintf(_T("\n%-15s : [%s] "), _T("[GS REACTOR]"), event);
}
