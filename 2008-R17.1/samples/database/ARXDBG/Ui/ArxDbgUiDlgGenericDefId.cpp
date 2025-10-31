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

#include "ArxDbgUiDlgGenericDefId.h"
#include "ArxDbgApp.h"
#include "AcadStr.h"
#include "ArxDbgUtils.h"
#include "ArxDbgDbDictRecord.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**	ArxDbgUiDlgGenericDefId::ArxDbgUiDlgGenericDefId
**
**	**jma
**
*************************************/

ArxDbgUiDlgGenericDefId::ArxDbgUiDlgGenericDefId(CWnd* parent,
                                SdStrObjIdList& entries,
                                const AcDbObjectId& currentValue,
                                bool allowNone)
:   CAcUiDialog(ArxDbgUiDlgGenericDefId::IDD, parent, ArxDbgApp::getApp()->dllInstance()),
    m_entries(entries),
    m_hasVaries(false),
    m_hasNone(allowNone),
    m_curIndex(0)
{
	if (allowNone == false) {
		ASSERT(entries.Count() != 0);
	}

    //{{AFX_DATA_INIT(ArxDbgUiDlgGenericDefId)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT

    if (allowNone)
        m_entries.AddTail(AcadString::none, AcDbObjectId::kNull);

    int index;
    if (m_entries.GetIndexFor(currentValue, index))
        m_curIndex = index;
}

/****************************************************************************
**
**	ArxDbgUiDlgGenericDefId::ArxDbgUiDlgGenericDefId
**
**	**jma
**
*************************************/

ArxDbgUiDlgGenericDefId::ArxDbgUiDlgGenericDefId(CWnd* parent,
                                SdStrObjIdList& entries,
                                const AcDbObjectIdArray& currentValues,
                                bool allowNone)
:   CAcUiDialog(ArxDbgUiDlgGenericDefId::IDD, parent, ArxDbgApp::getApp()->dllInstance()),
    m_entries(entries),
    m_hasVaries(false),
    m_hasNone(allowNone),
    m_curIndex(0)
{
	if (allowNone == false) {
		ASSERT(entries.Count() != 0);
	}

    //{{AFX_DATA_INIT(ArxDbgUiDlgGenericDefId)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT

        // walk through array and see if they all match or if they vary
    AcDbObjectId tmpId;
    int len = currentValues.length();
    for (int i=0; i<len; i++) {
        if (i == 0)
            tmpId = currentValues[i];
        else {
            if (tmpId != currentValues[i]) {
                m_hasVaries = TRUE;
                break;
            }
        }
    }
        // if it varied, add a new entry into list and make this the
        // current index
    if (m_hasVaries) {
        m_entries.AddTail(AcadString::varies1, AcDbObjectId::kNull);
        tmpId = AcDbObjectId::kNull;
    }
        // if it didn't vary and allowNone was on, then current selection
        // will be *NONE*
    if (allowNone)
        m_entries.AddTail(AcadString::none, AcDbObjectId::kNull);

        // get index for current entry
    int index;
    if (m_entries.GetIndexFor(tmpId, index))
        m_curIndex = index;
}

/****************************************************************************
**
**	ArxDbgUiDlgGenericDefId::~ArxDbgUiDlgGenericDefId
**
**	**jma
**
*************************************/

ArxDbgUiDlgGenericDefId::~ArxDbgUiDlgGenericDefId()
{
        // if we added our bogus entries, get rid of them now.
    int index;

    if (m_entries.GetIndexFor(AcadString::varies1, index))
        m_entries.RemoveAt(index);

    if (m_entries.GetIndexFor(AcadString::none, index))
        m_entries.RemoveAt(index);
}

/****************************************************************************
**
**	ArxDbgUiDlgGenericDefId::DoDataExchange
**
**	**jma
**
*************************************/

void
ArxDbgUiDlgGenericDefId::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiDlgGenericDefId)
    DDX_Control(pDX, ARXDBG_LC_DEF_IDS, m_lcDefIds);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgGenericDefId message map

BEGIN_MESSAGE_MAP(ArxDbgUiDlgGenericDefId, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxDbgUiDlgGenericDefId)
    ON_NOTIFY(LVN_ITEMCHANGED, ARXDBG_LC_DEF_IDS, OnListItemchanged)
    ON_NOTIFY(NM_DBLCLK, ARXDBG_LC_DEF_IDS, OnDblclickList)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgGenericDefId message handlers


/****************************************************************************
**
**	ArxDbgUiDlgGenericDefId::OnInitDialog
**
**	**jma
**
*************************************/

BOOL
ArxDbgUiDlgGenericDefId::OnInitDialog()
{
    CAcUiDialog::OnInitDialog();

    buildColumns();
    fillList();

    ArxDbgUtils::setCurSel(m_lcDefIds, m_curIndex);
    m_lcDefIds.SetFocus();

        // set overridden title for this dialog box
    if (m_title.IsEmpty() == FALSE)
        SetWindowText(m_title);

    SetDlgItemText(ARXDBG_TXT_PROMPT, m_prompt);

    return FALSE;   // we already set the focus
}

/****************************************************************************
**
**	ArxDbgUiDlgGenericDefId::OnListItemchanged
**
**	**jma
**
*************************************/

void
ArxDbgUiDlgGenericDefId::OnListItemchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

        // if the item selection has changed, update the index
    if (pNMListView->uNewState & LVIS_SELECTED) {
        if (pNMListView->iItem != -1)
            m_curIndex = pNMListView->iItem;    // record new index while we are here
    }

    *pResult = 0;
}

/****************************************************************************
**
**    ArxDbgUiDlgGenericDefId::buildColumns
**
**    **jma
**
*************************************/

void
ArxDbgUiDlgGenericDefId::buildColumns()
{
        // get the width of the window
    CRect lvRect;
    m_lcDefIds.GetClientRect(lvRect);

    int col1_width = static_cast<int>(lvRect.Width() * .40);    // entry name
    int col2_width = static_cast<int>(lvRect.Width() * .60);    // description

        // initialize the columns
    LV_COLUMN lvc;
    lvc.mask = LVCF_WIDTH | LVCF_SUBITEM | LVCF_TEXT;
    lvc.cx = col1_width;
    lvc.pszText = _T("Name");
    lvc.iSubItem = 0;
    m_lcDefIds.InsertColumn(0, &lvc);

    lvc.cx = col2_width;
    lvc.iSubItem = 1;
    lvc.pszText = _T("Description");
    m_lcDefIds.InsertColumn(1, &lvc);
}

/****************************************************************************
**
**    ArxDbgUiDlgGenericDefId::fillList
**
**    **jma
**
*************************************/

void
ArxDbgUiDlgGenericDefId::fillList()
{
    ArxDbgDbDictRecord* rec;
    CString nameStr;
    AcDbObjectId objId;
    Acad::ErrorStatus es;

    SdStrObjIdListIterator iter(m_entries);
    for (int row=0; !iter.done(); iter.next(), row++) {
        iter.item(nameStr, objId);
        if (objId == AcDbObjectId::kNull) {     // *VARIES* or *NONE* case
            m_lcDefIds.InsertItem(row, nameStr);
            m_lcDefIds.SetItemText(row, 1, _T(""));
        }
        else {
                // if we can open it as a dict record, display the description
            es = acdbOpenObject(rec, objId, AcDb::kForRead);
            if (es == Acad::eOk) {
                m_lcDefIds.InsertItem(row, nameStr);
                m_lcDefIds.SetItemText(row, 1, rec->description());
                rec->close();
            }
            else {
                m_lcDefIds.InsertItem(row, nameStr);        // Acad object, no description
                m_lcDefIds.SetItemText(row, 1, _T(""));
            }
        }
    }
}

/****************************************************************************
**
**	ArxDbgUiDlgGenericDefId::OnDblclickList
**
**	**jma
**
*************************************/

void
ArxDbgUiDlgGenericDefId::OnDblclickList(NMHDR* pNMHDR, LRESULT* pResult)
{
    EndDialog(TRUE);
    *pResult = 0;
}

/****************************************************************************
**
**	ArxDbgUiDlgGenericDefId::getSelectedName
**
**	**jma
**
*************************************/

LPCTSTR
ArxDbgUiDlgGenericDefId::getSelectedName (CString& name) const
{
    AcDbObjectId id;
    if (m_entries.GetAtIndex(m_curIndex, name, id))
        return name;
    else
        return NULL;
}

/****************************************************************************
**
**	ArxDbgUiDlgGenericDefId::getSelectedId
**
**	**jma
**
*************************************/

AcDbObjectId
ArxDbgUiDlgGenericDefId::getSelectedId() const
{
    CString str;
    AcDbObjectId id;
    if (m_entries.GetAtIndex(m_curIndex, str, id))
        return id;
    else
        return AcDbObjectId::kNull;
}

/****************************************************************************
**
**	ArxDbgUiDlgGenericDefId::isVaries
**
**	**jma
**
*************************************/

bool
ArxDbgUiDlgGenericDefId::isVaries() const
{
    CString str;
    AcDbObjectId id;
    if (m_entries.GetAtIndex(m_curIndex, str, id)) {
        if ((id == AcDbObjectId::kNull) && (str.Compare(AcadString::varies1) == 0))
            return true;
    }
    return false;
}

/****************************************************************************
**
**	ArxDbgUiDlgGenericDefId::isNone
**
**	**jma
**
*************************************/

bool
ArxDbgUiDlgGenericDefId::isNone() const
{
    CString str;
    AcDbObjectId id;
    if (m_entries.GetAtIndex(m_curIndex, str, id)) {
        if ((id == AcDbObjectId::kNull) && (str.Compare(AcadString::none) == 0))
            return true;
    }
    return false;
}


