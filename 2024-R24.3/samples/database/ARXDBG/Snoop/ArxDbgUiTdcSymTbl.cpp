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

#include "ArxDbgUiTdcSymTbl.h"
#include "ArxDbgUtils.h"
#include "ArxDbgUiTdmEntities.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
**
**  ArxDbgUiTdcSymTbl::ArxDbgUiTdcSymTbl
**
**  **jma
**
*************************************/

ArxDbgUiTdcSymTbl::ArxDbgUiTdcSymTbl(AcDbDatabase* db)
:   m_db(db)
{
    //{{AFX_DATA_INIT(ArxDbgUiTdcSymTbl)
    m_showErasedBlkEnts = FALSE;
    m_showNestedBlkRefs = FALSE;
    m_showErasedBlkRefs = FALSE;
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiTdcSymTbl::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcSymTbl::DoDataExchange(CDataExchange* pDX)
{
    ArxDbgUiTdcDbObjectBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdcSymTbl)
    DDX_Control(pDX, ARXDBG_BN_BLKENTS, m_blkEntsButton);
    DDX_Control(pDX, ARXDBG_BN_BLKREFS, m_blkRefsButton);
    DDX_Control(pDX, ARXDBG_CB_SHOW_ERASED, m_cbShowErased);
    DDX_Control(pDX, ARXDBG_CB_SHOW_NESTED, m_cbShowNested);
    DDX_Control(pDX, ARXDBG_CB_SHOW_ERASED_REFS, m_cbShowErasedRefs);
    DDX_Control(pDX, ARXDBG_LC_SYMTBL_VALUES, m_dataList);
    DDX_Control(pDX, ARXDBG_TREE_SYMTABS, m_tblTree);
    DDX_Check(pDX, ARXDBG_CB_SHOW_ERASED, m_showErasedBlkEnts);
    DDX_Check(pDX, ARXDBG_CB_SHOW_NESTED, m_showNestedBlkRefs);
    DDX_Check(pDX, ARXDBG_CB_SHOW_ERASED_REFS, m_showErasedBlkRefs);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcSymTbl message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdcSymTbl, ArxDbgUiTdcDbObjectBase)
    //{{AFX_MSG_MAP(ArxDbgUiTdcSymTbl)
    ON_NOTIFY(TVN_SELCHANGED, ARXDBG_TREE_SYMTABS, OnSelchangedSymtabs)
    ON_BN_CLICKED(ARXDBG_BN_BLKENTS, OnBnBlkEnts)
    ON_BN_CLICKED(ARXDBG_BN_BLKREFS, OnBnBlkRefs)
    ON_BN_CLICKED(ARXDBG_CB_SHOW_NESTED, OnCbShowNested)
    ON_BN_CLICKED(ARXDBG_CB_SHOW_ERASED_REFS, OnCbShowNested)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcSymTbl message handlers

/****************************************************************************
**
**  ArxDbgUiTdcSymTbl::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdcSymTbl::OnInitDialog() 
{
    ArxDbgUiTdcDbObjectBase::OnInitDialog();

    Acad::ErrorStatus es;
    HTREEITEM treeItem;

    AcDbBlockTable* blockTbl;
    es = m_db->getBlockTable(blockTbl, AcDb::kForRead);
    ASSERT(es == Acad::eOk);
    if (es == Acad::eOk) {
        treeItem = addOneTreeItem(_T("Block Table"), blockTbl->objectId(), TVI_ROOT);
        addOneTable(blockTbl, treeItem);
        blockTbl->close();
        m_tblTree.SelectItem(treeItem);        // make this one the currently selected one
    }

    AcDbDimStyleTable* dimStyleTbl;
    es = m_db->getDimStyleTable(dimStyleTbl, AcDb::kForRead);
    ASSERT(es == Acad::eOk);
    if (es == Acad::eOk) {
        treeItem = addOneTreeItem(_T("Dimension Style Table"), dimStyleTbl->objectId(), TVI_ROOT);
        addOneTable(dimStyleTbl, treeItem);
        dimStyleTbl->close();
    }

    AcDbLayerTable* layerTbl;
    es = m_db->getLayerTable(layerTbl, AcDb::kForRead);
    ASSERT(es == Acad::eOk);
    if (es == Acad::eOk) {
        treeItem = addOneTreeItem(_T("Layer Table"), layerTbl->objectId(), TVI_ROOT);
        addOneTable(layerTbl, treeItem);
        layerTbl->close();
    }

    AcDbLinetypeTable* linetypeTbl;
    es = m_db->getLinetypeTable(linetypeTbl, AcDb::kForRead);
    ASSERT(es == Acad::eOk);
    if (es == Acad::eOk) {
        treeItem = addOneTreeItem(_T("Linetype Table"), linetypeTbl->objectId(), TVI_ROOT);
        addOneTable(linetypeTbl, treeItem);
        linetypeTbl->close();
    }

    AcDbRegAppTable* appTbl;
    es = m_db->getRegAppTable(appTbl, AcDb::kForRead);
    ASSERT(es == Acad::eOk);
    if (es == Acad::eOk) {
        treeItem = addOneTreeItem(_T("RegApp Table"), appTbl->objectId(), TVI_ROOT);
        addOneTable(appTbl, treeItem);
        appTbl->close();
    }

    AcDbTextStyleTable* textStyleTbl;
    es = m_db->getTextStyleTable(textStyleTbl, AcDb::kForRead);
    ASSERT(es == Acad::eOk);
    if (es == Acad::eOk) {
        treeItem = addOneTreeItem(_T("Text Style Table"), textStyleTbl->objectId(), TVI_ROOT);
        addOneTable(textStyleTbl, treeItem);
        textStyleTbl->close();
    }

    AcDbViewTable* viewTbl;
    es = m_db->getViewTable(viewTbl, AcDb::kForRead);
    ASSERT(es == Acad::eOk);
    if (es == Acad::eOk) {
        treeItem = addOneTreeItem(_T("View Table"), viewTbl->objectId(), TVI_ROOT);
        addOneTable(viewTbl, treeItem);
        viewTbl->close();
    }

    AcDbViewportTable* viewportTbl;
    es = m_db->getViewportTable(viewportTbl, AcDb::kForRead);
    ASSERT(es == Acad::eOk);
    if (es == Acad::eOk) {
        treeItem = addOneTreeItem(_T("Viewport Table"), viewportTbl->objectId(), TVI_ROOT);
        addOneTable(viewportTbl, treeItem);
        viewportTbl->close();
    }

    AcDbUCSTable* ucsTbl;
    es = m_db->getUCSTable(ucsTbl, AcDb::kForRead);
    ASSERT(es == Acad::eOk);
    if (es == Acad::eOk) {
        treeItem = addOneTreeItem(_T("UCS Table"), ucsTbl->objectId(), TVI_ROOT);
        addOneTable(ucsTbl, treeItem);
        ucsTbl->close();
    }

	buildColumns(m_dataList);
    displayCurrent(0);
    
    return TRUE; 
}

/****************************************************************************
**
**  ArxDbgUiTdcSymTbl::displayCurrent
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcSymTbl::displayCurrent(int index)
{
		// remove any previous entries
    m_fieldStrList.RemoveAll();
    m_valueStrList.RemoveAll();

    ASSERT((index >= 0) && (index < m_tblObjIdList.length()));
    m_currentObjId = m_tblObjIdList[index];

    CString str;

    AcDbObject* obj = NULL;
    Acad::ErrorStatus es = acdbOpenObject(obj, m_currentObjId, AcDb::kForRead);
    setExtensionButtons(obj);
	setBlockInfoButtons(obj);

    if (es == Acad::eOk) {
		display(obj);
        obj->close();
    }

	drawPropsList(m_dataList);
}

/****************************************************************************
**
**  ArxDbgUiTdcSymTbl::setBlockInfoButtons
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcSymTbl::setBlockInfoButtons(AcDbObject* obj) 
{
    AcDbBlockTableRecord* blkRec;
    if ((blkRec = AcDbBlockTableRecord::cast(obj)) != NULL) {
        m_blkEntsButton.ShowWindow(SW_SHOW);
        m_blkRefsButton.ShowWindow(SW_SHOW);
        m_cbShowErased.ShowWindow(SW_SHOW);
        m_cbShowNested.ShowWindow(SW_SHOW);
        m_cbShowErasedRefs.ShowWindow(SW_SHOW);

			// disable refs button if there aren't any
		BOOL enableBlkRefs = FALSE;

		Acad::ErrorStatus es;
		AcDbObjectIdArray refIds;
		es = blkRec->getBlockReferenceIds(refIds, !m_showNestedBlkRefs);

		if ((es == Acad::eOk) && (refIds.isEmpty() == false))
			enableBlkRefs = TRUE;
		else {
			if (m_showErasedBlkRefs) {
				es = blkRec->getErasedBlockReferenceIds(refIds);
				if ((es == Acad::eOk) && (refIds.isEmpty() == false))
					enableBlkRefs = TRUE;
			}
		}

		m_blkRefsButton.EnableWindow(enableBlkRefs);
	}
    else {
        m_blkEntsButton.ShowWindow(SW_HIDE);
        m_blkRefsButton.ShowWindow(SW_HIDE);
        m_cbShowErased.ShowWindow(SW_HIDE);
        m_cbShowNested.ShowWindow(SW_HIDE);
        m_cbShowErasedRefs.ShowWindow(SW_HIDE);
	}
}

/****************************************************************************
**
**  ArxDbgUiTdcSymTbl::OnSelchangedSymtabs
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcSymTbl::OnSelchangedSymtabs(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    displayCurrent(static_cast<int>(pNMTreeView->itemNew.lParam));    
    *pResult = 0;
}

/****************************************************************************
**
**  ArxDbgUiTdcSymTbl::addOneTreeItem
**
**  **jma
**
*************************************/

HTREEITEM
ArxDbgUiTdcSymTbl::addOneTreeItem(LPCTSTR name, const AcDbObjectId& objId, HTREEITEM parent, bool sort)
{
    m_tblObjIdList.append(objId);    // keep track of the objectId for each entry
    int index = m_tblObjIdList.length() - 1;
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
**  ArxDbgUiTdcSymTbl::addOneTable
**      iterate over the table and collect all the names contained
**  within it.
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcSymTbl::addOneTable(const AcDbSymbolTable* symTbl, HTREEITEM parent)
{
        // get an iterator over this symbol Table
    AcDbSymbolTableIterator* tblIter;
    Acad::ErrorStatus es = symTbl->newIterator(tblIter);
    if (symTbl->isKindOf(AcDbLayerTable::desc()))
        static_cast<AcDbLayerTableIterator*>(tblIter)->setSkipHidden(false);
    ASSERT(tblIter != NULL);
    if (es != Acad::eOk) {
        ArxDbgUtils::rxErrorAlert(es);
        return;
    }
        // don't sort AcDbViewportTable names, so we know which one is current
    bool sortAlpha = (symTbl->isKindOf(AcDbViewportTable::desc())) ? false : true;

        // walk table and just collect all the names of the entries
    AcDbSymbolTableRecord* tblRec;
    const TCHAR* symName;
    HTREEITEM curItem;
    for (; !tblIter->done(); tblIter->step()) {
        es = tblIter->getRecord(tblRec, AcDb::kForRead);
        if (es == Acad::eOk) {
            tblRec->getName(symName);
            curItem = addOneTreeItem(symName, tblRec->objectId(), parent, sortAlpha);
            tblRec->close();
        }
        else
            ArxDbgUtils::rxErrorMsg(es);
    }
    delete tblIter;
}

/****************************************************************************
**
**	ArxDbgUiTdcSymTbl::OnBnBlkEnts
**
**	**jma
**
*************************************/

void
ArxDbgUiTdcSymTbl::OnBnBlkEnts() 
{
    UpdateData(TRUE);    // make sure value of check box is updated

    AcDbObjectIdArray blkEnts;
    AcDbBlockTableRecord* blkRec;
    Acad::ErrorStatus es = acdbOpenObject(blkRec, m_currentObjId, AcDb::kForRead);
    if (es == Acad::eOk) {
        collectBlkEnts(blkRec, blkEnts, !m_showErasedBlkEnts);
        blkRec->close();
        if (blkEnts.isEmpty())
            ArxDbgUtils::alertBox(_T("There are no entities within this block."));
        else {
			CString str, blkName;
			ArxDbgUtils::symbolIdToName(m_currentObjId, blkName);
			str.Format(_T("Entities In Block \"%s\""), blkName);

			ArxDbgUiTdmEntities dbox(blkEnts, true, this, str);
            dbox.DoModal();
        }
    }
    else
        ArxDbgUtils::rxErrorAlert(es);
}

/****************************************************************************
**
**	ArxDbgUiTdcSymTbl::OnBnBlkRefs
**
**	**jma
**
*************************************/

void
ArxDbgUiTdcSymTbl::OnBnBlkRefs() 
{
    UpdateData(TRUE);    // make sure value of check box is updated

    AcDbObjectIdArray refEnts;
    AcDbBlockTableRecord* blkRec;
    Acad::ErrorStatus es = acdbOpenObject(blkRec, m_currentObjId, AcDb::kForRead);
    if (es == Acad::eOk) {
		es = blkRec->getBlockReferenceIds(refEnts, !m_showNestedBlkRefs);

			// collect erased refs if they want those too
		if (m_showErasedBlkRefs) {
			AcDbObjectIdArray erasedRefEnts;
			es = blkRec->getErasedBlockReferenceIds(erasedRefEnts);
			if (es == Acad::eOk)
				refEnts.append(erasedRefEnts);
		}

        blkRec->close();

		if (es != Acad::eOk) {
			ArxDbgUtils::rxErrorAlert(es);
			return;
		}

        if (refEnts.isEmpty())
            ArxDbgUtils::alertBox(_T("There are no references to this block."));
        else {
			CString str, blkName;
			ArxDbgUtils::symbolIdToName(m_currentObjId, blkName);
			str.Format(_T("References To Block \"%s\""), blkName);

            ArxDbgUiTdmEntities dbox(refEnts, false, this, str);
            dbox.DoModal();
        }
    }
    else
        ArxDbgUtils::rxErrorAlert(es);
}

/****************************************************************************
**
**	ArxDbgUiTdcSymTbl::collectBlkEnts
**
**	**jma
**
*************************************/

void
ArxDbgUiTdcSymTbl::collectBlkEnts(AcDbBlockTableRecord* blkTbl,
                    AcDbObjectIdArray& blkEnts, bool skipErased)
{
    Acad::ErrorStatus es;
    AcDbObjectId objId;
    AcDbBlockTableRecordIterator* iter;

    es = blkTbl->newIterator(iter, true, skipErased);
    if (es != Acad::eOk) {
        ArxDbgUtils::rxErrorMsg(es);
        return;
    }
    for (; !iter->done(); iter->step(true, skipErased)) {
        es = iter->getEntityId(objId);
        if (es == Acad::eOk)
            blkEnts.append(objId);
    }

    delete iter;
}

/****************************************************************************
**
**	ArxDbgUiTdcSymTbl::OnCbShowNested
**
**	**jma
**
*************************************/

void
ArxDbgUiTdcSymTbl::OnCbShowNested() 
{
    UpdateData(TRUE);    // make sure value of check box is updated

	AcDbObject* obj = openCurrentItem();
	setBlockInfoButtons(obj);
	if (obj)
		obj->close();
}