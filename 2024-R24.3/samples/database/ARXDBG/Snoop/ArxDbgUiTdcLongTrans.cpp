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

#include "ArxDbgUiTdcLongTrans.h"
#include "ArxDbgUtils.h"
#include "ArxDbgUiDlgDxf.h"
#include "ArxDbgUiTdmDatabase.h"
#include "ArxDbgUiDlgReactors.h"
#include "ArxDbgUiDlgXdata.h"
#include "ArxDbgUiTdmEditor.h"
#include "ArxDbgUiTdmIdMap.h"
#include "ArxDbgReferenceFiler.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
**
**  ArxDbgUiTdcLongTrans::ArxDbgUiTdcLongTrans
**
**  **jma
**
*************************************/

ArxDbgUiTdcLongTrans::ArxDbgUiTdcLongTrans(AcDbLongTransaction* lt)
:	m_longTrans(lt)
{
    //{{AFX_DATA_INIT(ArxDbgUiTdcLongTrans)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiTdcLongTrans::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcLongTrans::DoDataExchange(CDataExchange* pDX)
{
    ArxDbgUiTdcDbObjectBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdcLongTrans)
    DDX_Control(pDX, ARXDBG_LC_VALUES, m_dataList);
    DDX_Control(pDX, ARXDBG_TREE_OBJS, m_tblTree);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcLongTrans message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdcLongTrans, ArxDbgUiTdcDbObjectBase)
    //{{AFX_MSG_MAP(ArxDbgUiTdcLongTrans)
    ON_NOTIFY(TVN_SELCHANGED, ARXDBG_TREE_OBJS, OnSelchangedSymtabs)
    ON_BN_CLICKED(ARXDBG_BN_DATABASE, OnDatabase)
    ON_BN_CLICKED(ARXDBG_BN_IDMAP, OnShowIdMap)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcLongTrans message handlers

/****************************************************************************
**
**  ArxDbgUiTdcLongTrans::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdcLongTrans::OnInitDialog() 
{
    ArxDbgUiTdcDbObjectBase::OnInitDialog();

    HTREEITEM treeItem;

    treeItem = addOneTreeItem(_T("Long Transaction"), m_longTrans->objectId(), TVI_ROOT);
    m_tblTree.SelectItem(treeItem);        // make this one the currently selected one

	buildColumns(m_dataList);
    displayCurrent(0);

		// disable IdMap button if there isn't one.
	AcDbIdMapping* idMap = m_longTrans->activeIdMap();
	if (idMap == NULL)
		ArxDbgUtils::enableDlgItem(this, ARXDBG_BN_IDMAP, FALSE);
    
    return TRUE; 
}

/****************************************************************************
**
**  ArxDbgUiTdcLongTrans::displayCurrent
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcLongTrans::displayCurrent(int index)
{
		// remove any previous entries
    m_fieldStrList.RemoveAll();
    m_valueStrList.RemoveAll();

    ASSERT((index >= 0) && (index < m_objIdList.length()));
    m_currentObjId = m_objIdList[index];

	// TBD: index is ignored right now because we only have one item

    CString str;

    setExtensionButtons(m_longTrans);

	display(m_longTrans);

	drawPropsList(m_dataList);
}

/****************************************************************************
**
**  ArxDbgUiTdcLongTrans::OnSelchangedSymtabs
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcLongTrans::OnSelchangedSymtabs(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    displayCurrent(static_cast<int>(pNMTreeView->itemNew.lParam));    
    *pResult = 0;
}

/****************************************************************************
**
**  ArxDbgUiTdcLongTrans::addOneTreeItem
**
**  **jma
**
*************************************/

HTREEITEM
ArxDbgUiTdcLongTrans::addOneTreeItem(LPCTSTR name, const AcDbObjectId& objId, HTREEITEM parent, bool sort)
{
    m_objIdList.append(objId);    // keep track of the objectId for each entry
    int index = m_objIdList.length() - 1;
    ASSERT(index >= 0);

    TV_ITEM    tvItem;
    TV_INSERTSTRUCT tvInsert;

    tvItem.mask = TVIF_TEXT | TVIF_PARAM;
    tvItem.pszText = const_cast<TCHAR*>(name);
    tvItem.cchTextMax = lstrlen(name);
    tvItem.lParam = (LPARAM)index;        //index of AcDbObjectId
    
    tvInsert.item = tvItem;
    if (sort)
        tvInsert.hInsertAfter = TVI_SORT;
    else
        tvInsert.hInsertAfter = TVI_LAST;
    tvInsert.hParent = parent;

    return m_tblTree.InsertItem(&tvInsert);            
}

/****************************************************************************
**
**  ArxDbgUiTdcLongTrans::OnDxf
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcLongTrans::OnDxf() 
{
	Acad::ErrorStatus es = m_longTrans->downgradeOpen();
	if (es == Acad::eOk) {
		ArxDbgUiDlgDxf dbox(this, m_longTrans);
		dbox.DoModal();

		es = m_longTrans->upgradeOpen();
		if (es != Acad::eOk)
			ArxDbgUtils::rxErrorAlert(es);
	}
	else
		ArxDbgUtils::rxErrorAlert(es);
}

/****************************************************************************
**
**  ArxDbgUiTdcLongTrans::OnExtdict
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcLongTrans::OnExtdict() 
{
    AcDbObjectId extDictId = m_longTrans->extensionDictionary();

    ArxDbgUiTdmDatabase dbox(extDictId, this, _T("Extension Dictionary"));
	dbox.DoModal();
}

/****************************************************************************
**
**  ArxDbgUiTdcLongTrans::OnReactors
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcLongTrans::OnReactors() 
{
    ArxDbgUiDlgReactors dbox(this, m_longTrans);
    dbox.DoModal();
}

/****************************************************************************
**
**  ArxDbgUiTdcLongTrans::OnXdata
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcLongTrans::OnXdata() 
{
    ArxDbgUiDlgXdata dbox(this, m_longTrans);
    dbox.DoModal();
}

/****************************************************************************
**
**  ArxDbgUiTdcLongTrans::OnDatabase
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcLongTrans::OnDatabase() 
{
	AcDbDatabase* db = m_longTrans->database();

	if (db != NULL) {
		ArxDbgUiTdmDatabase dbox(db, this, _T("Database For Object"));
		dbox.DoModal();
	}
	else {
		ASSERT(0);	// button should have been disabled!
	}
}

/****************************************************************************
**
**  ArxDbgUiTdcLongTrans::OnDocument
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcLongTrans::OnDocument() 
{
	AcDbDatabase* db = m_longTrans->database();

	AcApDocument* doc = acDocManager->document(db);
	if (doc) {
		ArxDbgUiTdmEditor dbox(this, doc);
		dbox.DoModal();
	}
	else {
		ASSERT(0);	// this button should have been disabled!
	}
}

/****************************************************************************
**
**  ArxDbgUiTdcLongTrans::getReferencedObjects
**
**  **jma
**
*************************************/

bool
ArxDbgUiTdcLongTrans::getReferencedObjects(AcDbObjectIdArray& hardPointerIds,
										   AcDbObjectIdArray& softPointerIds,
										   AcDbObjectIdArray& hardOwnershipIds,
										   AcDbObjectIdArray& softOwnershipIds) 
{
	ArxDbgReferenceFiler filer;
	m_longTrans->dwgOut(&filer);

	hardPointerIds = filer.m_hardPointerIds;
	softPointerIds = filer.m_softPointerIds;
	hardOwnershipIds = filer.m_hardOwnershipIds;
	softOwnershipIds = filer.m_softOwnershipIds;

	return true;
}

/****************************************************************************
**
**  ArxDbgUiTdcLongTrans::OnShowIdMap
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcLongTrans::OnShowIdMap() 
{
	AcDbIdMapping* idMap = m_longTrans->activeIdMap();

	if (idMap) {
		ArxDbgUiTdmIdMap dbox(idMap, this);
		dbox.DoModal();
	}
	else {
		ASSERT(0);	// this button should have been disabled!
	}
}


