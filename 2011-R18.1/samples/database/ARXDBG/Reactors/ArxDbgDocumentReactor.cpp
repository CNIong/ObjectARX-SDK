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

#include "ArxDbgDocumentReactor.h"
#include "ArxDbgUtils.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxDbgDocumentReactor, AcApDocManagerReactor);

/****************************************************************************
**
**  ArxDbgDocumentReactor::ArxDbgDocumentReactor
**
**  **jma
**
*************************************/

ArxDbgDocumentReactor::ArxDbgDocumentReactor()
{
    acDocManager->addReactor(this);
}

/****************************************************************************
**
**  ArxDbgDocumentReactor::~ArxDbgDocumentReactor
**
**  **jma
**
*************************************/

ArxDbgDocumentReactor::~ArxDbgDocumentReactor()
{
    acDocManager->removeReactor(this);
}

/****************************************************************************
**
**  ArxDbgDocumentReactor::showDetails
**
**  **jma
**
*************************************/

bool
ArxDbgDocumentReactor::showDetails() const
{
	return m_showDetails;
}

/****************************************************************************
**
**  ArxDbgDocumentReactor::setShowDetails
**
**  **jma
**
*************************************/

void
ArxDbgDocumentReactor::setShowDetails(bool showThem)
{
	m_showDetails = showThem;
}

/****************************************************************************
**
**  ArxDbgDocumentReactor::documentCreateStarted
**
**  **jma
**
*************************************/

void
ArxDbgDocumentReactor::documentCreateStarted(AcApDocument* doc)
{
    printReactorMessage(doc, _T("Document Create Started"));
}

/****************************************************************************
**
**  ArxDbgDocumentReactor::documentCreated
**
**  **jma
**
*************************************/

void
ArxDbgDocumentReactor::documentCreated(AcApDocument* doc)
{
    printReactorMessage(doc, _T("Document Created"));
}

/****************************************************************************
**
**  ArxDbgDocumentReactor::documentToBeDestroyed
**
**  **jma
**
*************************************/

void
ArxDbgDocumentReactor::documentToBeDestroyed(AcApDocument* doc)
{
    printReactorMessage(doc, _T("Document To Be Destroyed"));
}

/****************************************************************************
**
**  ArxDbgDocumentReactor::documentCreateCanceled
**
**  **jma
**
*************************************/

void
ArxDbgDocumentReactor::documentCreateCanceled(AcApDocument* doc)
{
    printReactorMessage(doc, _T("Document Create Canceled"));
}

/****************************************************************************
**
**  ArxDbgDocumentReactor::documentLockModeWillChange
**
**  **jma
**
*************************************/

void
ArxDbgDocumentReactor::documentLockModeWillChange(AcApDocument* doc,
                AcAp::DocLockMode myCurrentMode,
                AcAp::DocLockMode myNewMode,
                AcAp::DocLockMode currentMode,
                const TCHAR* pGlobalCmdName)
{
    printReactorMessage(doc, _T("Document Lock Mode Will Change"));

	if (m_showDetails) {
		CString str1;

		acutPrintf(_T("\n    MyCurMode:  %s"), ArxDbgUtils::docLockModeToStr(myCurrentMode, str1));
		acutPrintf(_T("\n    MyNewMode:  %s"), ArxDbgUtils::docLockModeToStr(myNewMode, str1));
		acutPrintf(_T("\n    CurMode:    %s"), ArxDbgUtils::docLockModeToStr(currentMode, str1));
		acutPrintf(_T("\n    CmdName:    %s"), pGlobalCmdName);
	}
}

/****************************************************************************
**
**  ArxDbgDocumentReactor::documentLockModeChangeVetoed
**
**  **jma
**
*************************************/

void
ArxDbgDocumentReactor::documentLockModeChangeVetoed(AcApDocument* doc,
                const TCHAR* pGlobalCmdName)
{
	CString msg;
	msg.Format(_T("Document Lock Mode Change Vetoed, CmdName = %s"), pGlobalCmdName);
    printReactorMessage(doc, msg);
}

/****************************************************************************
**
**  ArxDbgDocumentReactor::documentLockModeChanged
**
**  **jma
**
*************************************/

void
ArxDbgDocumentReactor::documentLockModeChanged(AcApDocument* doc,
                AcAp::DocLockMode myPreviousMode,
                AcAp::DocLockMode myCurrentMode,
                AcAp::DocLockMode currentMode,
                const TCHAR* pGlobalCmdName)
{
    printReactorMessage(doc, _T("Document Lock Mode Changed"));

	if (m_showDetails) {
		CString str1;

		acutPrintf(_T("\n    MyPrevMode: %s"), ArxDbgUtils::docLockModeToStr(myPreviousMode, str1));
		acutPrintf(_T("\n    MyCurMode:  %s"), ArxDbgUtils::docLockModeToStr(myCurrentMode, str1));
		acutPrintf(_T("\n    CurMode:    %s"), ArxDbgUtils::docLockModeToStr(currentMode, str1));
		acutPrintf(_T("\n    CmdName:    %s"), pGlobalCmdName);
	}
}

/****************************************************************************
**
**  ArxDbgDocumentReactor::documentBecameCurrent
**
**  **jma
**
*************************************/

void
ArxDbgDocumentReactor::documentBecameCurrent(AcApDocument* doc)
{
    printReactorMessage(doc, _T("Document Became Current"));
}

/****************************************************************************
**
**  ArxDbgDocumentReactor::documentToBeActivated
**
**  **jma
**
*************************************/

void
ArxDbgDocumentReactor::documentToBeActivated(AcApDocument* doc)
{
    printReactorMessage(doc, _T("Document To Be Activated"));
}

/****************************************************************************
**
**  ArxDbgDocumentReactor::documentToBeDeactivated
**
**  **jma
**
*************************************/

void
ArxDbgDocumentReactor::documentToBeDeactivated(AcApDocument* doc)
{
    printReactorMessage(doc, _T("Document To Be De-activated"));
}

/****************************************************************************
**
**  ArxDbgDocumentReactor::documentActivationModified
**
**  **jma
**
*************************************/

void
ArxDbgDocumentReactor::documentActivationModified(bool bActivation)
{
	CString msg, str;
	msg.Format(_T("Document Activation Modified (Activation = %s)"),
					ArxDbgUtils::booleanToStr(bActivation, str));
    printReactorMessage(msg);
}

/****************************************************************************
**
**  ArxDbgDocumentReactor::documentActivated
**
**  **jma
**
*************************************/

void
ArxDbgDocumentReactor::documentActivated(AcApDocument* doc)
{
    printReactorMessage(doc, _T("Document Activated"));
}

/****************************************************************************
**
**  ArxDbgDocumentReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgDocumentReactor::printReactorMessage(AcApDocument* doc, LPCTSTR event) const
{
    CString str2;
    str2.Format(_T("<DOC REACTOR: %s>"), doc->docTitle());

    acutPrintf(_T("\n%-15s : [%s] "), str2, event);
}

/****************************************************************************
**
**  ArxDbgDocumentReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgDocumentReactor::printReactorMessage(LPCTSTR event) const
{
    CString str2 = _T("<DOC REACTOR: >");

    acutPrintf(_T("\n%-15s : [%s] "), str2, event);
}


