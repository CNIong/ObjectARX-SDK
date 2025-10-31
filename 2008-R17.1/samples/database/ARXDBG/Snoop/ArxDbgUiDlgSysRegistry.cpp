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


