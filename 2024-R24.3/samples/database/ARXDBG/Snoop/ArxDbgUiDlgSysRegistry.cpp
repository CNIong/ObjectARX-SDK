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

#include "ArxDbgUiDlgSysRegistry.h"
#include "ArxDbgUtils.h"
#include "ArxDbgApp.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgUiDlgSysRegistry::ArxDbgUiDlgSysRegistry
**
**  **jma
**
*************************************/

ArxDbgUiDlgSysRegistry::ArxDbgUiDlgSysRegistry(CWnd* pParent)
:   CAcUiDialog(ArxDbgUiDlgSysRegistry::IDD, pParent, ArxDbgApp::getApp()->dllInstance())
{
    //{{AFX_DATA_INIT(ArxDbgUiDlgSysRegistry)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiDlgSysRegistry::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgSysRegistry::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiDlgSysRegistry)
    DDX_Control(pDX, ARXDBG_TR_SYS_REG, m_tree);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgSysRegistry message map

BEGIN_MESSAGE_MAP(ArxDbgUiDlgSysRegistry, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxDbgUiDlgSysRegistry)
    ON_NOTIFY(TVN_SELCHANGED, ARXDBG_TR_SYS_REG, OnSelchangedSysReg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgSysRegistry message handlers


/****************************************************************************
**
**  ArxDbgUiDlgSysRegistry::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiDlgSysRegistry::OnInitDialog() 
{
    CAcUiDialog::OnInitDialog();

    addTreeItem(_T("ARX System Registry"), acrxSysRegistry(), TVI_ROOT);
    displayCurrent(0);
    
    return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiDlgSysRegistry::OnSelchangedSysReg
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgSysRegistry::OnSelchangedSysReg(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    displayCurrent(static_cast<int>(pNMTreeView->itemNew.lParam));    
    
    *pResult = 0;
}

/****************************************************************************
**
**  ArxDbgUiDlgSysRegistry::addTreeItem
**
**  **jma
**
*************************************/

HTREEITEM
ArxDbgUiDlgSysRegistry::addTreeItem(LPCTSTR name, AcRxObject* obj, HTREEITEM parent)
{
    ASSERT(name != NULL);
    ASSERT(obj != NULL);

    m_objList.append(static_cast<void*>(obj));    // keep track of the object for each entry
    int index = m_objList.length() - 1;
    ASSERT(index >= 0);

    TV_ITEM    tvItem;
    TV_INSERTSTRUCT tvInsert;

    tvItem.mask = TVIF_TEXT | TVIF_PARAM;
    tvItem.pszText = const_cast<LPTSTR>(name);
    tvItem.cchTextMax = lstrlen(name);
    tvItem.lParam = (LPARAM)index;        //index of object
    
    tvInsert.item = tvItem;
    tvInsert.hInsertAfter = TVI_SORT;
    tvInsert.hParent = parent;

    HTREEITEM newItem = m_tree.InsertItem(&tvInsert);
    AcRxDictionary* dict = AcRxDictionary::cast(obj);
    if (dict) {
        AcRxDictionaryIterator* iter = dict->newIterator();
        for (; !iter->done(); iter->next()) {
            addTreeItem(iter->key(), iter->object(), newItem);
        }
    }
    return newItem;
}

/****************************************************************************
**
**  ArxDbgUiDlgSysRegistry::displayCurrent
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgSysRegistry::displayCurrent(int index)
{
    ASSERT((index >= 0) && (index < m_objList.length()));
    AcRxObject* obj = static_cast<AcRxObject*>(m_objList[index]);

    SetDlgItemText(ARXDBG_TXT_CLASS, ArxDbgUtils::objToClassStr(obj));
}


