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

#include "ArxDbgTransactionReactor.h"
#include "ArxDbgUtils.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxDbgTransactionReactor, AcTransactionReactor);

/****************************************************************************
**
**  ArxDbgTransactionReactor::ArxDbgTransactionReactor
**
**  **jma
**
*************************************/

ArxDbgTransactionReactor::ArxDbgTransactionReactor()
{
}

/****************************************************************************
**
**  ArxDbgTransactionReactor::~ArxDbgTransactionReactor
**
**  **jma
**
*************************************/

ArxDbgTransactionReactor::~ArxDbgTransactionReactor()
{
}

/****************************************************************************
**
**  ArxDbgTransactionReactor::transactionAboutToStart
**
**  **jma
**
*************************************/

void
ArxDbgTransactionReactor::transactionAboutToStart(int& numTransactions, AcDbTransactionManager* transactionManagerPtr)
{
    printReactorMessage(_T("Transaction About To Start"), numTransactions, transactionManagerPtr);
}

/****************************************************************************
**
**  ArxDbgTransactionReactor::transactionAboutToEnd
**
**  **jma
**
*************************************/

void
ArxDbgTransactionReactor::transactionAboutToEnd(int& numTransactions, AcDbTransactionManager* transactionManagerPtr)
{
    printReactorMessage(_T("Transaction About To End"), numTransactions, transactionManagerPtr);
}

/****************************************************************************
**
**  ArxDbgTransactionReactor::transactionAboutToAbort
**
**  **jma
**
*************************************/

void
ArxDbgTransactionReactor::transactionAboutToAbort(int& numTransactions, AcDbTransactionManager* transactionManagerPtr)
{
    printReactorMessage(_T("Transaction About To Abort"), numTransactions, transactionManagerPtr);
}

/****************************************************************************
**
**  ArxDbgTransactionReactor::transactionStarted
**
**  **jma
**
*************************************/

void
ArxDbgTransactionReactor::transactionStarted(int& numTransactions, AcDbTransactionManager* transactionManagerPtr)
{
    printReactorMessage(_T("Transaction Started"), numTransactions, transactionManagerPtr);
}

/****************************************************************************
**
**  ArxDbgTransactionReactor::transactionEnded
**
**  **jma
**
*************************************/

void
ArxDbgTransactionReactor::transactionEnded(int& numTransactions, AcDbTransactionManager* transactionManagerPtr)
{
    printReactorMessage(_T("Transaction Ended"), numTransactions, transactionManagerPtr);
}

/****************************************************************************
**
**  ArxDbgTransactionReactor::transactionAborted
**
**  **jma
**
*************************************/

void
ArxDbgTransactionReactor::transactionAborted(int& numTransactions, AcDbTransactionManager* transactionManagerPtr)
{
    printReactorMessage(_T("Transaction Aborted"), numTransactions, transactionManagerPtr);
}

/****************************************************************************
**
**  ArxDbgTransactionReactor::endCalledOnOutermostTransaction
**
**  **jma
**
*************************************/

void
ArxDbgTransactionReactor::endCalledOnOutermostTransaction(int& numTransactions, AcDbTransactionManager* transactionManagerPtr)
{
    printReactorMessage(_T("End Called On Outermost Transaction"), numTransactions, transactionManagerPtr);
}

/****************************************************************************
**
**  ArxDbgTransactionReactor::objectIdSwapped
**
**  **jma
**
*************************************/

void
ArxDbgTransactionReactor::objectIdSwapped(const AcDbObject* pTransResObj, const AcDbObject* pOtherObj, AcDbTransactionManager* transactionManagerPtr)
{
    printReactorMessage(_T("ObjectId Swapped"), pTransResObj, pOtherObj, transactionManagerPtr);
}

/****************************************************************************
**
**  ArxDbgTransactionReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgTransactionReactor::printReactorMessage(LPCTSTR event, int numTransactions) const
{
    acutPrintf(_T("\n%-15s : [%d --> %s] "), _T("[TRANSACT REACTOR]"), numTransactions, event);
}

/****************************************************************************
**
**  ArxDbgTransactionReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgTransactionReactor::printReactorMessage(LPCTSTR event, int numTransactions,
							AcDbTransactionManager* transactionManagerPtr) const
{
	CString str;

    acutPrintf(_T("\n%-15s : [%d --> %s] (TrMgr = %s)"), _T("[TRANSACT REACTOR]"),
			numTransactions, event, ArxDbgUtils::ptrToStr(transactionManagerPtr, str));
}

/****************************************************************************
**
**  ArxDbgTransactionReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgTransactionReactor::printReactorMessage(LPCTSTR event, const AcDbObject* obj1,
							const AcDbObject* obj2,
							AcDbTransactionManager* transactionManagerPtr) const
{
	CString str, str2;

    acutPrintf(_T("\n%-15s : [%s] (TrMgr = %s)"), _T("[TRANSACT REACTOR]"),
			event, ArxDbgUtils::ptrToStr(transactionManagerPtr, str));
	acutPrintf(_T("\n    SWAPPED: %s --> %s"),
			ArxDbgUtils::objToClassAndHandleStr(obj1, str),
			ArxDbgUtils::objToClassAndHandleStr(obj2, str2));
					
}


