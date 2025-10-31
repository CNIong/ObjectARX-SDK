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

#include "ArxDbgUiTdcDocs.h"
#include "ArxDbgUtils.h"
#include "ArxDbgUiTdmDatabase.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
**
**  ArxDbgUiTdcDocs::ArxDbgUiTdcDocs
**
**  **jma
**
*************************************/

ArxDbgUiTdcDocs::ArxDbgUiTdcDocs()
:   m_curIndex(0)
{
		// get all document pointers
    AcApDocumentIterator* iter = acDocManager->newAcApDocumentIterator();
    if (iter) {
        AcApDocument* tmpDoc;
        for (; !iter->done(); iter->step()) {
            tmpDoc = iter->document();
			if (tmpDoc)
				m_docPtrs.append(tmpDoc);
        }
        delete iter;
    }

    //{{AFX_DATA_INIT(ArxDbgUiTdcDocs)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiTdcDocs::ArxDbgUiTdcDocs
**
**  **jma
**
*************************************/

ArxDbgUiTdcDocs::ArxDbgUiTdcDocs(AcApDocument* doc)
:   m_curIndex(0)
{
	ASSERT(doc != NULL);

	m_docPtrs.append(doc);

    //{{AFX_DATA_INIT(ArxDbgUiTdcDocs)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiTdcDocs::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDocs::DoDataExchange(CDataExchange* pDX)
{
    ArxDbgUiTdcRxObjectBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdcDocs)
    DDX_Control(pDX, ARXDBG_LB_DOCS, m_docList);
    DDX_Control(pDX, ARXDBG_LC_DATA, m_dataList);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcDocs message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdcDocs, ArxDbgUiTdcRxObjectBase)
    //{{AFX_MSG_MAP(ArxDbgUiTdcDocs)
    ON_LBN_SELCHANGE(ARXDBG_LB_DOCS, OnSelchangeDocs)
    ON_BN_CLICKED(ARXDBG_BN_DATABASE, OnDatabase)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcDocs message handlers

/****************************************************************************
**
**  ArxDbgUiTdcDocs::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdcDocs::OnInitDialog() 
{
    ArxDbgUiTdcRxObjectBase::OnInitDialog();

	fillListBox(m_curIndex);

	buildColumns(m_dataList);
    displayCurrent(m_curIndex);

    return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiTdcDocs::fillListBox
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDocs::fillListBox(int defIndex)
{
    m_docList.ResetContent();

	AcApDocument* tmpDoc;
	CString str;

	int len = m_docPtrs.length();
	for (int i=0; i<len; i++) {
		tmpDoc = static_cast<AcApDocument*>(m_docPtrs[i]);
		str = tmpDoc->docTitle();

		if ((acDocManager->curDocument() == tmpDoc) && (acDocManager->mdiActiveDocument() == tmpDoc))
			str += _T("  (Current/MDI Active)");
		else if (acDocManager->curDocument() == tmpDoc)
			str += _T("  (Current)");
		else if (acDocManager->mdiActiveDocument() == tmpDoc)
			str += _T("  (MDI Active)");

		m_docList.AddString(str);
    }

    int retCode = m_docList.SetCurSel(defIndex);
    ASSERT(retCode != LB_ERR);
}

/****************************************************************************
**
**  ArxDbgUiTdcDocs::displayCurrent
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDocs::displayCurrent(int index)
{
		// remove any previous entries
    m_fieldStrList.RemoveAll();
    m_valueStrList.RemoveAll();

    ASSERT((index >= 0) && (index < m_docPtrs.length()));

	CString str;
	AcApDocument* doc = static_cast<AcApDocument*>(m_docPtrs[index]);

    addToDataList(_T("File Name"), doc->fileName(), true);
    addToDataList(_T("Document Title"), doc->docTitle(), true);
    addToDataList(_T("Database"), ArxDbgUtils::dbToStr(doc->database(), str));
    addToDataList(_T("MFC CDocument"), ArxDbgUtils::ptrToStr(doc->cDoc(), str));
    addToDataList(_T("Transaction Manager"), ArxDbgUtils::ptrToStr(doc->transactionManager(), str));
    addToDataList(_T("Context Pointer"), ArxDbgUtils::ptrToStr(doc->contextPtr(), str));
    addToDataList(_T("Format For Save"), ArxDbgUtils::saveFormatToStr(doc->formatForSave(), str));
    addToDataList(_T("Lock Mode"), ArxDbgUtils::docLockModeToStr(doc->lockMode(), str));
    addToDataList(_T("My Lock Mode"), ArxDbgUtils::docLockModeToStr(doc->myLockMode(), str));
    addToDataList(_T("Is Quiescent"), ArxDbgUtils::booleanToStr(doc->isQuiescent(), str));
    addToDataList(_T("Is Read Only"), ArxDbgUtils::booleanToStr(doc->isReadOnly(), str));

		// print out all the lisp apps that are loaded with this document
	CString unloadStr;
    int lispAppCount = doc->GetCountOfLispList();
	if (lispAppCount > 0) {
		addSeperatorLine(_T("LISP Apps"));

		AcLispAppInfo* appInfo;
		for (int i=0; i<lispAppCount; i++) {
			appInfo = doc->GetItemOfLispList(i);
			if (appInfo) {
				if (appInfo->bUnloadable)
					unloadStr = _T("Unloadable");
				else
					unloadStr = _T("Not Unloadable");

				addToDataList(appInfo->appFileName, unloadStr);
			}
		}
	}

	drawPropsList(m_dataList);
}

/****************************************************************************
**
**  ArxDbgUiTdcDocs::OnSelchangeDocs
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDocs::OnSelchangeDocs()
{
    int index = m_docList.GetCurSel();

    if (index != LB_ERR) {
		m_curIndex = index;
		displayCurrent(m_curIndex);
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDocs::OnDatabase
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDocs::OnDatabase() 
{
    ASSERT((m_curIndex >= 0) && (m_curIndex < m_docPtrs.length()));

	AcApDocument* doc = static_cast<AcApDocument*>(m_docPtrs[m_curIndex]);

    ArxDbgUiTdmDatabase dbox(doc->database(), this, doc->docTitle());
    dbox.DoModal();
}

