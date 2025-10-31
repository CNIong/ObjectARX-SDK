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

