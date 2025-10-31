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

#include "ArxDbgUiTdcClasses.h"
#include "ArxDbgUiDlgClassDict.h"
#include "ArxDbgUtils.h"
#include "ArxDbgApp.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgUiTdcClasses::ArxDbgUiTdcClasses
**
**  **jma
**
*************************************/

ArxDbgUiTdcClasses::ArxDbgUiTdcClasses()
:	CAcUiTabChildDialog(NULL, ArxDbgApp::getApp()->dllInstance()),
    m_classArray(100),
    m_placedNodes(100),
    m_treeItems(100)
{
    //{{AFX_DATA_INIT(ArxDbgUiTdcClasses)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiTdcClasses::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcClasses::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabChildDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdcClasses)
    DDX_Control(pDX, ARXDBG_TR_CLASSES, m_tblTree);
    DDX_Control(pDX, ARXDBG_LB_PROXY_FLAGS, m_lbProxyFlags);
    DDX_Control(pDX, ARXDBG_LB_PROTOCOL_EXT, m_lbProtocolExt);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcClasses message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdcClasses, CAcUiTabChildDialog)
    //{{AFX_MSG_MAP(ArxDbgUiTdcClasses)
    ON_NOTIFY(TVN_SELCHANGED, ARXDBG_TR_CLASSES, OnSelchanged)
    ON_BN_CLICKED(ARXDBG_BN_COMP_CLASSES, OnBnCompClasses)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcClasses message handlers

/****************************************************************************
**
**  ArxDbgUiTdcClasses::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdcClasses::OnInitDialog() 
{
    CAcUiTabChildDialog::OnInitDialog();

    buildClassTree();
    m_tblTree.Expand(m_tblTree.GetRootItem(), TVE_EXPAND);
    m_tblTree.SelectItem(m_tblTree.GetFirstVisibleItem());
    
    return TRUE; 
}

/****************************************************************************
**
**  ArxDbgUiTdcClasses::buildClassTree
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcClasses::buildClassTree()
{
        // get an interator over the class dictionary
    AcRxDictionary* classDict = acrxClassDictionary;
    AcRxDictionaryIterator* iter;
    if ((classDict == NULL) || ((iter = classDict->newIterator()) == NULL)) {
        ArxDbgUtils::stopAlertBox(_T("ERROR: Couldn't get class dictionary."));
        return;
    }
        // iterate over each item and get its info
    AcRxObject* classDictItem;
    AcRxClass* classObj;

    for (; !iter->done(); iter->next()) {
        classDictItem = iter->object();
        if ((classObj = AcRxClass::cast(classDictItem)) != NULL)
            m_classArray.append(classObj);
        else
            ArxDbgUtils::stopAlertBox(_T("ERROR: found non AcRxClass in class dictionary!"));
    }
    delete iter;

        // add in root node
    m_placedNodes.append(NULL);
    m_treeItems.append(TVI_ROOT);

    HTREEITEM parentItem;
    HTREEITEM newItem;
    int index;

    while (regress(index, parentItem)) {
        newItem = addTreeItem(static_cast<AcRxClass*>(m_classArray[index]), parentItem);
        m_treeItems.append(newItem);
        m_placedNodes.append(m_classArray[index]);
        m_classArray.removeAt(index);
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcClasses::regress
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdcClasses::regress(int& index, HTREEITEM& parentItem)
{
    AcRxClass* tmpClass;
    int nodeLen;

    int len = m_classArray.length();
    for (int i=0; i<len; i++) {
        if (m_classArray[i] != NULL) {
            tmpClass = static_cast<AcRxClass*>(m_classArray[i]);
            nodeLen = m_placedNodes.length();
            AcRxClass* parent = tmpClass->myParent();
            for (int j=0; j<nodeLen; j++) {
                if (parent == static_cast<AcRxClass*>(m_placedNodes[j])) {
                    index = i;
                    parentItem = static_cast<HTREEITEM>(m_treeItems[j]);
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

/****************************************************************************
**
**  ArxDbgUiTdcClasses::addTreeItem
**
**  **jma
**
*************************************/

HTREEITEM
ArxDbgUiTdcClasses::addTreeItem(AcRxClass* classObj, HTREEITEM parent)
{
    TV_ITEM tvItem;
    TV_INSERTSTRUCT tvInsert;

    const TCHAR* className = classObj->name();
    if (className == NULL)
        className = _T("");

    tvItem.mask = TVIF_TEXT | TVIF_PARAM;
    tvItem.pszText = const_cast<TCHAR*>(className);
    tvItem.cchTextMax = lstrlen(className);
    tvItem.lParam = (LPARAM)classObj;        // pointer to class
    
    tvInsert.item = tvItem;
    tvInsert.hInsertAfter = TVI_SORT;
    tvInsert.hParent = parent;

    return m_tblTree.InsertItem(&tvInsert);            
}

/****************************************************************************
**
**  ArxDbgUiTdcClasses::displayCurrent
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcClasses::displayCurrent(AcRxClass* classObj)
{
    ASSERT(classObj != NULL);

    CString str;

    SetDlgItemText(ARXDBG_TXT_CLASSNAME, classObj->name());
    if (classObj->dxfName()) {
        ArxDbgUtils::enableDlgItem(this, ARXDBG_TXT_DXF_LABEL, TRUE);
        SetDlgItemText(ARXDBG_TXT_DXFNAME, classObj->dxfName());

			// print birth version info
		int dwgVer = 0;
		int maintVer = 0;
		classObj->getClassVersion(dwgVer, maintVer);

        ArxDbgUtils::enableDlgItem(this, ARXDBG_TXT_BVERSION_LABEL, TRUE);
		ArxDbgUtils::dwgVersionToStr(static_cast<AcDb::AcDbDwgVersion>(dwgVer), str);
        SetDlgItemText(ARXDBG_TXT_BVERSION, str);

        ArxDbgUtils::enableDlgItem(this, ARXDBG_TXT_MVERSION_LABEL, TRUE);
        SetDlgItemText(ARXDBG_TXT_MVERSION, ArxDbgUtils::intToStr(maintVer, str));
    }
    else {
        ArxDbgUtils::enableDlgItem(this, ARXDBG_TXT_DXF_LABEL, FALSE);
        SetDlgItemText(ARXDBG_TXT_DXFNAME, _T(""));

        ArxDbgUtils::enableDlgItem(this, ARXDBG_TXT_BVERSION_LABEL, FALSE);
        SetDlgItemText(ARXDBG_TXT_BVERSION, _T(""));

        ArxDbgUtils::enableDlgItem(this, ARXDBG_TXT_MVERSION_LABEL, FALSE);
        SetDlgItemText(ARXDBG_TXT_MVERSION, _T(""));
    }

    if (classObj->appName()) {
        ArxDbgUtils::enableDlgItem(this, ARXDBG_TXT_APP_LABEL, TRUE);
        SetDlgItemText(ARXDBG_TXT_APPNAME, classObj->appName());
    }
    else {
        ArxDbgUtils::enableDlgItem(this, ARXDBG_TXT_APP_LABEL, FALSE);
        SetDlgItemText(ARXDBG_TXT_APPNAME, _T(""));
    }

        // list all proxy flags
    m_lbProxyFlags.ResetContent();

    int flags = classObj->proxyFlags();

    if (classObj->isDerivedFrom(AcDbEntity::desc())) {
        if (flags == AcDbProxyEntity::kNoOperation)
            m_lbProxyFlags.AddString(_T("No Operations Allowed"));
        else {
            if (flags & AcDbProxyEntity::kEraseAllowed)
                m_lbProxyFlags.AddString(_T("Erase Allowed"));
            if (flags & AcDbProxyEntity::kTransformAllowed)
                m_lbProxyFlags.AddString(_T("Transform Allowed"));
            if (flags & AcDbProxyEntity::kCloningAllowed)
                m_lbProxyFlags.AddString(_T("Cloning Allowed"));
            if (flags & AcDbProxyEntity::kColorChangeAllowed)
                m_lbProxyFlags.AddString(_T("Color Change Allowed"));
            if (flags & AcDbProxyEntity::kLayerChangeAllowed)
                m_lbProxyFlags.AddString(_T("Layer Change Allowed"));
            if (flags & AcDbProxyEntity::kLinetypeChangeAllowed)
                m_lbProxyFlags.AddString(_T("Linetype Change Allowed"));
            if (flags & AcDbProxyEntity::kLinetypeScaleChangeAllowed)
                m_lbProxyFlags.AddString(_T("Linetype Scale Change Allowed"));
            if (flags & AcDbProxyEntity::kVisibilityChangeAllowed)
                m_lbProxyFlags.AddString(_T("Visibility Change Allowed"));
        }
    }
    else {
        if (flags == AcDbProxyObject::kNoOperation)
            m_lbProxyFlags.AddString(_T("No Operations Allowed"));
        else {
            if (flags & AcDbProxyEntity::kEraseAllowed)
                m_lbProxyFlags.AddString(_T("Erase Allowed"));
            if (flags & AcDbProxyObject::kCloningAllowed)
                m_lbProxyFlags.AddString(_T("Cloning Allowed"));
            if (flags & AcDbProxyObject::kMergeIgnore)
                m_lbProxyFlags.AddString(_T("Merge Style - Ignore"));
            if (flags & AcDbProxyObject::kMergeReplace)
                m_lbProxyFlags.AddString(_T("Merge Style - Replace"));
            if (flags & AcDbProxyObject::kMergeReplace)
                m_lbProxyFlags.AddString(_T("Merge Style - Mangle"));
        }
    }
        // list all protocol extensions
    m_lbProtocolExt.ResetContent();
    AcRxObject* protocolObj;
    AcRxClass* tmpClass;

    int len = m_placedNodes.length();
    for (int i=0; i<len; i++) {
        tmpClass = static_cast<AcRxClass*>(m_placedNodes[i]);    // could be NULL because of root item in array
        if (tmpClass && (classObj != tmpClass)) {
            protocolObj =  classObj->queryX(tmpClass);
            if (protocolObj) {
                m_lbProtocolExt.AddString(protocolObj->isA()->name());
            }
        }
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcClasses::OnSelchanged
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcClasses::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    displayCurrent((AcRxClass*)(pNMTreeView->itemNew.lParam));    
    *pResult = 0;
}

/****************************************************************************
**
**  ArxDbgUiTdcClasses::OnBnCompClasses
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcClasses::OnBnCompClasses()
{
    ArxDbgUiDlgClassDict dbox(this);
    dbox.DoModal();
}
