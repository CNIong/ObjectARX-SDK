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

#include "ArxDbgLongTransactionReactor.h"
#include "ArxDbgUtils.h"
#include "ArxDbgUiTdmLongTrans.h"
#include "ArxDbgUiTdmObjects.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxDbgLongTransactionReactor, AcApLongTransactionReactor);

/****************************************************************************
**
**  ArxDbgLongTransactionReactor::ArxDbgLongTransactionReactor
**
**  **jma
**
*************************************/

ArxDbgLongTransactionReactor::ArxDbgLongTransactionReactor()
:	m_showDetails(false)
{
    acapLongTransactionManager->addReactor(this);
}

/****************************************************************************
**
**  ArxDbgLongTransactionReactor::~ArxDbgLongTransactionReactor
**
**  **jma
**
*************************************/

ArxDbgLongTransactionReactor::~ArxDbgLongTransactionReactor()
{
    acapLongTransactionManager->removeReactor(this);
}

/****************************************************************************
**
**  ArxDbgLongTransactionReactor::showDetails
**
**  **jma
**
*************************************/

bool
ArxDbgLongTransactionReactor::showDetails() const
{
	return m_showDetails;
}

/****************************************************************************
**
**  ArxDbgLongTransactionReactor::setShowDetails
**
**  **jma
**
*************************************/

void
ArxDbgLongTransactionReactor::setShowDetails(bool showThem)
{
	m_showDetails = showThem;
}

/****************************************************************************
**
**  ArxDbgLongTransactionReactor::beginCheckOut
**
**  **jma
**
*************************************/

void
ArxDbgLongTransactionReactor::beginCheckOut(AcDbLongTransaction& lt, AcDbObjectIdArray& originList)
{
	printReactorMessage(lt, _T("Begin Check Out"));

	if (m_showDetails) {
		ArxDbgUiTdmObjects dbox(originList, acedGetAcadDwgView(), _T("Original Check-Out Set"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxDbgLongTransactionReactor::endCheckOut
**
**  **jma
**
*************************************/

void
ArxDbgLongTransactionReactor::endCheckOut(AcDbLongTransaction& lt)
{
	printReactorMessage(lt, _T("End Check Out"));
}

/****************************************************************************
**
**  ArxDbgLongTransactionReactor::beginCheckIn
**
**  **jma
**
*************************************/

void
ArxDbgLongTransactionReactor::beginCheckIn(AcDbLongTransaction& lt)
{
	printReactorMessage(lt, _T("Begin Check In"));
}

/****************************************************************************
**
**  ArxDbgLongTransactionReactor::endCheckIn
**
**  **jma
**
*************************************/

void
ArxDbgLongTransactionReactor::endCheckIn(AcDbLongTransaction& lt)
{
	printReactorMessage(lt, _T("End Check In"));
}

/****************************************************************************
**
**  ArxDbgLongTransactionReactor::abortLongTransaction
**
**  **jma
**
*************************************/

void
ArxDbgLongTransactionReactor::abortLongTransaction(AcDbLongTransaction& lt)
{
	printReactorMessage(lt, _T("Abort Long Transaction"));
}

/****************************************************************************
**
**  ArxDbgLongTransactionReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgLongTransactionReactor::printReactorMessage(AcDbLongTransaction& lt, LPCTSTR event) const
{
    CString str;

	TCHAR* transName = NULL;
    Acad::ErrorStatus es = lt.getLongTransactionName(transName);
	if (es == Acad::eOk) {
		str = transName;
		acutDelString(transName);
	}
	else {
		str = ArxDbgUtils::rxErrorStr(es);
	}

    acutPrintf(_T("\n%-15s : <%-18s: %s> "), _T("<LONG TRANS REACTOR>"), event, str);

	if (m_showDetails) {
		ArxDbgUiTdmLongTrans dbox(&lt, acedGetAcadDwgView(), event);
		dbox.DoModal();
	}
}

