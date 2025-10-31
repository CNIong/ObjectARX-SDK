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

#include "ArxDbgGsReactor.h"

//ACRX_NO_CONS_DEFINE_MEMBERS(ArxDbgGsReactor, AcGsReactor); TBD: not derived off of AcRxObject yet!

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

    struct resbuf rb;
    if (ads_getvar(L"CVPORT", &rb) == RTNORM) {
        AcGsView* pView = acgsGetCurrent3dAcGsView(rb.resval.rint);
        if (pView) {
            m_pGraphicsKernel = &pView->graphicsKernel();
            m_pGraphicsKernel->addReactor(this);
        }
    }
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
    if (m_pGraphicsKernel) {
        m_pGraphicsKernel->removeReactor(this);
    }
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
ArxDbgGsReactor::gsToBeUnloaded(AcGsGraphicsKernel* pGraphicsKernel)
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
