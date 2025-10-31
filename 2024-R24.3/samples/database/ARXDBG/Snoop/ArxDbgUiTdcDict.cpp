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

#include "ArxDbgUiTdcDict.h"
#include "ArxDbgUtils.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgUiTdcDict::ArxDbgUiTdcDict
**
**  **jma
**
*************************************/

ArxDbgUiTdcDict::ArxDbgUiTdcDict(const AcDbObjectId& dictId, bool isExtDict)
:   m_isRoot(!isExtDict),
    m_curIndex(0)
{
    m_rootObjId = dictId;

    //{{AFX_DATA_INIT(ArxDbgUiTdcDict)
    m_dictIsHardOwner = FALSE;
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiTdcDict::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDict::DoDataExchange(CDataExchange* pDX)
{
    ArxDbgUiTdcDbObjectBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdcDict)
    DDX_Control(pDX, ARXDBG_TREE_DICT, m_dictTree);
    DDX_Control(pDX, ARXDBG_LC_DICT_VALUES, m_dataList);
    DDX_Check(pDX, ARXDBG_CB_HARDOWNER, m_dictIsHardOwner);
    DDX_Control(pDX, ARXDBG_PU_MERGESTYLE, m_puMergeStyle);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcDict message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdcDict, ArxDbgUiTdcDbObjectBase)
    //{{AFX_MSG_MAP(ArxDbgUiTdcDict)
    ON_BN_CLICKED(ARXDBG_CB_HARDOWNER, OnSetHardOwner)
    ON_CBN_SELENDOK(ARXDBG_PU_MERGESTYLE, OnMergeStyleChanged)
    ON_NOTIFY(TVN_SELCHANGED, ARXDBG_TREE_DICT, OnSelchangedDict)
    ON_NOTIFY(TVN_ENDLABELEDIT, ARXDBG_TREE_DICT, OnEndlabeleditTreeDict)
    ON_NOTIFY(TVN_KEYDOWN, ARXDBG_TREE_DICT, OnKeydownTreeDict)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcDict message handlers

/****************************************************************************
**
**  ArxDbgUiTdcDict::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdcDict::OnInitDialog() 
{
    ArxDbgUiTdcDbObjectBase::OnInitDialog();

    HTREEITEM rootItem;
    if (m_isRoot)
        rootItem = addOneTreeItem(_T("<Root Dictionary>"), m_rootObjId, TVI_ROOT);
    else
        rootItem = addOneTreeItem(_T("<Extension Dictionary>"), m_rootObjId, TVI_ROOT);

    addOneDictionary(m_rootObjId, rootItem);
    m_dictTree.SelectItem(rootItem);    // make this one the currently selected one

	buildColumns(m_dataList);
    displayCurrent(m_curIndex);    // 0

    m_dictTree.Expand(m_dictTree.GetRootItem(), TVE_EXPAND);

    return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiTdcDict::addOneTreeItem
**
**  **jma
**
*************************************/

HTREEITEM
ArxDbgUiTdcDict::addOneTreeItem(LPCTSTR name, const AcDbObjectId& objId, HTREEITEM parent)
{
    m_dictObjIdList.append(objId);    // keep track of the objectId for each entry
    int index = m_dictObjIdList.length() - 1;
    ASSERT(index >= 0);

    TV_ITEM    tvItem;
    TV_INSERTSTRUCT tvInsert;

    tvItem.mask = TVIF_TEXT | TVIF_PARAM;
    tvItem.pszText = const_cast<TCHAR*>(name);
    tvItem.cchTextMax = lstrlen(name);
    tvItem.lParam = (LPARAM)index;        //index of AcDbObjectId
    
    tvInsert.item = tvItem;
    tvInsert.hInsertAfter = TVI_LAST;
    tvInsert.hParent = parent;

    return m_dictTree.InsertItem(&tvInsert);            
}

/****************************************************************************
**
**  ArxDbgUiTdcDict::addOneDictionary
**      iterate over the dictionary and collect all the names contained
**  within it.
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDict::addOneDictionary(const AcDbObjectId& dictId, HTREEITEM parent)
{
    AcDbDictionary* dict;
    Acad::ErrorStatus es;
    es = acdbOpenObject(dict, dictId, AcDb::kForRead);
    if (es != Acad::eOk)
        return;

        // get an iterator over this dictionary
    AcDbDictionaryIterator* dictIter = dict->newIterator();
    ASSERT(dictIter != NULL);

        // walk dictionary and just collect all the names
        // of the entries
    HTREEITEM curItem;
    for (; !dictIter->done(); dictIter->next()) {
        curItem = addOneTreeItem(dictIter->name(), dictIter->objectId(), parent);
        addOneDictionary(dictIter->objectId(), curItem);
    }
    delete dictIter;
    dict->close();
}

/****************************************************************************
**
**  ArxDbgUiTdcDict::displayCurrent
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDict::displayCurrent(int index)
{
		// remove any previous entries
    m_fieldStrList.RemoveAll();
    m_valueStrList.RemoveAll();

    ASSERT((index >= 0) && (index < m_dictObjIdList.length()));
    m_currentObjId = m_dictObjIdList[index];

    AcDbObject* obj = NULL;
    Acad::ErrorStatus es = acdbOpenObject(obj, m_currentObjId, AcDb::kForRead);
    setExtensionButtons(obj);
	setDictInfoButtons(obj);

    if (es == Acad::eOk) {
		display(obj);
        obj->close();
    }
    else {
        ArxDbgUtils::rxErrorAlert(es);
    }

	drawPropsList(m_dataList);
}

/****************************************************************************
**
**  ArxDbgUiTdcDict::setDictInfoButtons
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDict::setDictInfoButtons(AcDbObject* obj)
{
    AcDbDictionary* dict;
    if ((dict = AcDbDictionary::cast(obj)) != NULL) {
		m_dictIsHardOwner = dict->isTreatElementsAsHard();

		UpdateData(FALSE);	// update checkbox

		m_puMergeStyle.SetCurSel(drcToIndex(dict->mergeStyle()));	// update pop-up

        ArxDbgUtils::hideDlgItem(this, ARXDBG_CB_HARDOWNER, FALSE);
        ArxDbgUtils::hideDlgItem(this, ARXDBG_PU_MERGESTYLE, FALSE);
        ArxDbgUtils::hideDlgItem(this, ARXDBG_TXT_MERGESTYLE_LABEL, FALSE);
	}
    else {
        ArxDbgUtils::hideDlgItem(this, ARXDBG_CB_HARDOWNER, TRUE);
        ArxDbgUtils::hideDlgItem(this, ARXDBG_PU_MERGESTYLE, TRUE);
        ArxDbgUtils::hideDlgItem(this, ARXDBG_TXT_MERGESTYLE_LABEL, TRUE);
	}
}

/****************************************************************************
**
**  ArxDbgUiTdcDict::OnSelchangedDict
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDict::OnSelchangedDict(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    m_curIndex = (int)(pNMTreeView->itemNew.lParam);
    displayCurrent(m_curIndex);
    *pResult = 0;
}

/****************************************************************************
**
**  ArxDbgUiTdcDict::OnEndlabeleditTreeDict
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDict::OnEndlabeleditTreeDict(NMHDR* pNMHDR, LRESULT* pResult) 
{
    TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
    *pResult = 0;

    if (pTVDispInfo->item.mask & TVIF_TEXT) {
        HTREEITEM item = m_dictTree.GetSelectedItem();
        if (item == NULL)
            return;

        CString oldName = m_dictTree.GetItemText(item);
        CString newName = pTVDispInfo->item.pszText;

            // if it hasn't changed, don't do anything
        if (newName.CompareNoCase(oldName) == 0)
            return;

        if (renameCurrentItem(oldName, newName)) {
                // set new item name and re-sort entries in this node of tree
            m_dictTree.SetItem(&(pTVDispInfo->item));
            m_dictTree.SortChildren(m_dictTree.GetParentItem(item));
        }
    }    
}

/****************************************************************************
**
**  ArxDbgUiTdcDict::OnKeydownTreeDict
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDict::OnKeydownTreeDict(NMHDR* pNMHDR, LRESULT* pResult) 
{
    TV_KEYDOWN* pTVKeyDown = (TV_KEYDOWN*)pNMHDR;

    if (pTVKeyDown->wVKey == VK_DELETE) {
        CString itemName = m_dictTree.GetItemText(m_dictTree.GetSelectedItem());
        CString msg;
        msg.Format(_T("Are you sure you want to delete entry \"%s\"?"), itemName);
        if (ArxDbgUtils::yesNoAlert(msg, IDNO) == IDYES)
            deleteCurrentItem();
    }
    
    *pResult = 0;
}

/****************************************************************************
**
**  ArxDbgUiTdcDict::renameCurrentItem
**
**  **jma
**
*************************************/

bool
ArxDbgUiTdcDict::renameCurrentItem(LPCTSTR oldName, LPCTSTR newName)
{
    bool retStatus = false;

    Acad::ErrorStatus es;
    AcDbObject* obj = openCurrentItem();
    if (obj == NULL)
        return retStatus;

        // get owner dictionary for this item
    AcDbObjectId ownerId = obj->ownerId();
    obj->close();

    AcDbDictionary* ownerDict;
    es = acdbOpenObject(ownerDict, obj->ownerId(), AcDb::kForWrite);

    if (es == Acad::eOk) {
        if (ownerDict->setName(oldName, newName) == Adesk::kFalse)
            ArxDbgUtils::stopAlertBox(_T("Could not set entry to that name!"));
        else
            retStatus = true;    // everything worked

        ownerDict->close();
    }
    else {
        ArxDbgUtils::stopAlertBox(_T("Couldn't rename that entry!"));
        ArxDbgUtils::rxErrorAlert(es);
    }

    return retStatus;
}

/****************************************************************************
**
**  ArxDbgUiTdcDict::deleteCurrentItem
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDict::deleteCurrentItem()
{
    AcDbObject* obj = openCurrentItem();
    if (obj == NULL)
        return;

        // get owner dictionary and objectId of this entry
    AcDbObjectId entryId = obj->objectId();
    AcDbObjectId ownerId = obj->ownerId();
    obj->close();

    Acad::ErrorStatus es;
    AcDbDictionary* ownerDict;
    es = acdbOpenObject(ownerDict, ownerId, AcDb::kForWrite);
    if (es == Acad::eOk) {
        es = ownerDict->remove(entryId);
        ownerDict->close();
        if (es == Acad::eOk) {
            HTREEITEM item = m_dictTree.GetSelectedItem();
            ASSERT(item);
            if (item)
                m_dictTree.DeleteItem(item);
        }
        else {
            ArxDbgUtils::stopAlertBox(_T("Couldn't remove this item!"));
            ArxDbgUtils::rxErrorAlert(es);
        }
    }
    else {
        ArxDbgUtils::stopAlertBox(_T("Couldn't open parent dictionary of this item!"));
        ArxDbgUtils::rxErrorAlert(es);
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDict::OnSetHardOwner
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDict::OnSetHardOwner()
{
	UpdateData(TRUE);	// get current value of checkbox

    AcDbObject* obj = openCurrentItem();
    if (obj) {
        AcDbDictionary* dict = AcDbDictionary::cast(obj);
        if (dict) {
            dict->upgradeOpen();
            dict->setTreatElementsAsHard(intToBool(m_dictIsHardOwner));
        }
        obj->close();
        displayCurrent(m_curIndex);
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDict::OnMergeStyleChanged
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDict::OnMergeStyleChanged()
{
	int index = m_puMergeStyle.GetCurSel();
	ASSERT(index != CB_ERR);

    AcDbObject* obj = openCurrentItem();
    if (obj) {
        AcDbDictionary* dict = AcDbDictionary::cast(obj);
        if (dict) {
            dict->upgradeOpen();
            dict->setMergeStyle(indexToDrc(index));
        }
        obj->close();
        displayCurrent(m_curIndex);
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDict::indexToDrc
**
**  **jma
**
*************************************/

AcDb::DuplicateRecordCloning
ArxDbgUiTdcDict::indexToDrc(int index) const
{
	if (index == 0)
		return AcDb::kDrcIgnore;
	else if (index == 1)
		return AcDb::kDrcReplace;
	else if (index == 2)
		return AcDb::kDrcMangleName;
	else {
		ASSERT(0);
		return AcDb::kDrcIgnore;
	}
}

/****************************************************************************
**
**  ArxDbgUiTdcDict::drcToIndex
**
**  **jma
**
*************************************/

int
ArxDbgUiTdcDict::drcToIndex(AcDb::DuplicateRecordCloning drc) const
{
	if (drc == AcDb::kDrcNotApplicable) {
		ASSERT(0);
		return 0;	// ignore
	}
	else if (drc == AcDb::kDrcIgnore) {
		return 0;
	}
	else if (drc == AcDb::kDrcReplace) {
		return 1;
	}
	else if (drc == AcDb::kDrcXrefMangleName) {
		ASSERT(0);
		return 0;
	}
	else if (drc == AcDb::kDrcMangleName) {
		return 2;
	}
	else if (drc == AcDb::kDrcUnmangleName) {
		ASSERT(0);
		return 0;
	}
	else {
		ASSERT(0);
		return 0;
	}
}
