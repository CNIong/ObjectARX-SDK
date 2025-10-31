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

#include "ArxDbgUiTdcInsert.h"
#include "ArxDbgUtils.h"
#include "ArxDbgApp.h"
#include "ArxDbgAppEditorReactor.h"
#include "ArxDbgUiTdmObjects.h"
#include "ArxDbgUiTdmDatabase.h"
#include "ArxDbgUiTdmTransDbClones.h"
#include "ArxDbgDocLockWrite.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
**
**  ArxDbgUiTdcInsert::ArxDbgUiTdcInsert
**
**  **jma
**
*************************************/

ArxDbgUiTdcInsert::ArxDbgUiTdcInsert()
:   CAcUiTabChildDialog(NULL, ArxDbgApp::getApp()->dllInstance())
{
    //{{AFX_DATA_INIT(ArxDbgUiTdcInsert)
    m_preserveOriginalDb = FALSE;
    m_saveAsDwg = FALSE;
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiTdcInsert::~ArxDbgUiTdcInsert
**
**  **jma
**
*************************************/

ArxDbgUiTdcInsert::~ArxDbgUiTdcInsert()
{
        // we need to delete any external databases that we allocated.
    AcDbDatabase* tmpDb;

    INT_PTR len = m_extDwgNames.GetSize();
    ASSERT( len <= INT_MAX );
    for (int i=0; i<(int)len; i++) {
        if (m_extDwgNames[i] != _T("")) {
            tmpDb = static_cast<AcDbDatabase*>(m_dbPtrs[i]);
            delete tmpDb;
        }
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcInsert::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcInsert::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabChildDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdcInsert)
    DDX_Control(pDX, ARXDBG_EB_DESTNAME1, m_ebDestName1);
    DDX_Control(pDX, ARXDBG_EB_DESTNAME2, m_ebDestName2);
    DDX_Control(pDX, ARXDBG_LB_SOURCE_DB, m_lbSourceDb);
    DDX_Control(pDX, ARXDBG_LB_DEST_DB, m_lbDestDb);
    DDX_Control(pDX, ARXDBG_PU_BLKDEFS, m_puBlockDef);
    DDX_Check(pDX, ARXDBG_CB_PRESERVE_SRC_DB, m_preserveOriginalDb);
    DDX_Check(pDX, ARXDBG_CB_SAVE_AS_DWG, m_saveAsDwg);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcInsert message handlers

BEGIN_MESSAGE_MAP(ArxDbgUiTdcInsert, CAcUiTabChildDialog)
    //{{AFX_MSG_MAP(ArxDbgUiTdcInsert)
    ON_LBN_SELCHANGE(ARXDBG_LB_SOURCE_DB, OnSourceDatabaseChanged)
    ON_LBN_SELCHANGE(ARXDBG_LB_DEST_DB, OnDestDatabaseChanged)
    ON_BN_CLICKED(ARXDBG_BN_INSERT_ALL, OnInsertDb)
    ON_BN_CLICKED(ARXDBG_BN_INSERT_AS_BLOCK, OnInsertBlkDef)
    ON_BN_CLICKED(ARXDBG_BN_TRANSFER_BLKDEF, OnTransferBlkDef)
    ON_BN_CLICKED(ARXDBG_BN_EXTDWG, OnAddExternalDwg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcInsert message handlers


/****************************************************************************
**
**  ArxDbgUiTdcInsert::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdcInsert::OnInitDialog() 
{
    CAcUiTabChildDialog::OnInitDialog();

    displayDbLists();

    return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiTdcInsert::displayDbLists
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcInsert::displayDbLists() 
{
    m_dbPtrs.setLogicalLength(0);
    m_lbSourceDb.ResetContent();
    m_lbDestDb.ResetContent();

    m_dbPtrs = acdbActiveDatabaseArray();

    CString str;
    AcDbDatabase* tmpDb;

    int len = m_dbPtrs.length();
    for (int i=0; i<len; i++) {
        tmpDb = static_cast<AcDbDatabase*>(m_dbPtrs[i]);

        ArxDbgUtils::dbToStr(tmpDb, str);
        m_lbSourceDb.AddString(str);
        m_lbDestDb.AddString(str);

        m_extDwgNames.Add(_T(""));	// add bogus dwgName to keep these in sync when we
                                    // later add external drawings.
    }

    m_lbSourceDb.SetCurSel(0);
    m_lbDestDb.SetCurSel(0);

    fillBlockList();
    setButtonModes();
}

/****************************************************************************
**
**  ArxDbgUiTdcInsert::fillBlockList
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcInsert::fillBlockList() 
{
    m_blockList.RemoveAll();

    bool isExternal;
    AcDbDatabase* curDb = getSourceDb(isExternal);
    ASSERT(curDb != NULL);

    Acad::ErrorStatus es;
    es = ArxDbgUtils::collectBlockIds(m_blockList, false, false, false, curDb);

    ASSERT(es == Acad::eOk);

    ArxDbgUtils::fillListBox(m_blockList, m_puBlockDef, 0);
}

/****************************************************************************
**
**  ArxDbgUiTdcInsert::OnSourceDatabaseChanged
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcInsert::OnSourceDatabaseChanged() 
{
    fillBlockList();
    setButtonModes();
}

/****************************************************************************
**
**  ArxDbgUiTdcInsert::OnDestDatabaseChanged
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcInsert::OnDestDatabaseChanged() 
{
    setButtonModes();
}

/****************************************************************************
**
**  ArxDbgUiTdcInsert::setButtonModes
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcInsert::setButtonModes()
{
    bool isExternal;
    AcDbDatabase* sourceDb = getSourceDb(isExternal);
    AcDbDatabase* destDb = getDestDb();

    bool allowClones;
    if (sourceDb == destDb)
        allowClones = false;
    else
        allowClones = true;

    ArxDbgUtils::enableDlgItem(this, ARXDBG_BN_INSERT_ALL, allowClones);
    ArxDbgUtils::enableDlgItem(this, ARXDBG_BN_INSERT_AS_BLOCK, allowClones);
    ArxDbgUtils::enableDlgItem(this, ARXDBG_BN_TRANSFER_BLKDEF, allowClones);
}

/****************************************************************************
**
**  ArxDbgUiTdcInsert::OnInsertDb
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcInsert::OnInsertDb() 
{
    UpdateData(TRUE);

    bool isExternal;
    AcDbDatabase* sourceDb = getSourceDb(isExternal);
    AcDbDatabase* destDb = getDestDb();
    ASSERT(sourceDb != destDb);

    Acad::ErrorStatus es;

        // lock the document we are inserting into
    ArxDbgDocLockWrite docLock(destDb);
    if (docLock.lockAndSetCurrent() != Acad::eOk)
        return;

    bool preserveSrcDb = intToBool(m_preserveOriginalDb);
    if (!preserveSrcDb && !isExternal) {
        ArxDbgUtils::alertBox(_T("Ignoring setting of \"Preserve source database\" since destroying\na database associated with a Document would be harsh."));
        preserveSrcDb = true;
    }

    // restore database to non-xref state (xes returns eOk if this
    // was necessary, and something else if it wasn't).
    Acad::ErrorStatus xes = sourceDb->restoreOriginalXrefSymbols();
    Acad::ErrorStatus xes2 = destDb->restoreOriginalXrefSymbols();
    es = destDb->insert(AcGeMatrix3d::kIdentity, sourceDb, preserveSrcDb);
    if (xes == Acad::eOk)
        xes = sourceDb->restoreForwardingXrefSymbols();
    if (xes2 == Acad::eOk)
        xes2 = destDb->restoreForwardingXrefSymbols();
    if (es == Acad::eOk) {
        ArxDbgUiTdmDatabase dbox(destDb, this, _T("Inserted Database"));
        dbox.DoModal();

        doSaveOption(destDb);

        if (isExternal && !preserveSrcDb)
            reloadRaidedExternalDwg(sourceDb);
    }
    else {
        CString str;
        str.Format(_T("Insert failed: %s"), ArxDbgUtils::rxErrorStr(es));
        ArxDbgUtils::stopAlertBox(str);
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcTransientReactors::OnInsertBlkDef
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcInsert::OnInsertBlkDef()
{
    CString blkName;
    m_ebDestName1.GetWindowText(blkName);

    if (!acdbSNValid(blkName, false)) {
        CString str;
        str.Format(_T("%s is not a valid block name."), blkName);
        ArxDbgUtils::alertBox(str);
        return;
    }

    UpdateData(TRUE);

    bool isExternal;
    AcDbDatabase* sourceDb = getSourceDb(isExternal);
    AcDbDatabase* destDb = getDestDb();
    ASSERT(sourceDb != destDb);

    Acad::ErrorStatus es;

        // lock the document we are inserting into
    ArxDbgDocLockWrite docLock(destDb);
    if (docLock.lockAndSetCurrent() != Acad::eOk)
        return;

    bool preserveSrcDb = intToBool(m_preserveOriginalDb);
    if (!preserveSrcDb && !isExternal) {
        ArxDbgUtils::alertBox(_T("Ignoring setting of \"Preserve source database\" since destroying\na database associated with a Document would be harsh."));
        preserveSrcDb = true;
    }

    AcDbObjectId blkId;
    es = destDb->insert(blkId, blkName, sourceDb, preserveSrcDb);
    if (es == Acad::eOk) {
        ArxDbgUiTdmDatabase dbox(destDb, this, _T("Inserted Database"));
        dbox.DoModal();

        doSaveOption(destDb);

        if (isExternal && !preserveSrcDb)
            reloadRaidedExternalDwg(sourceDb);
    }
    else {
        CString str;
        str.Format(_T("Insert failed: %s"), ArxDbgUtils::rxErrorStr(es));
        ArxDbgUtils::stopAlertBox(str);
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcInsert::OnTransferBlkDef
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcInsert::OnTransferBlkDef()
{
        // get the block we're suppose to be wblocking
    int index = m_puBlockDef.GetCurSel();
    ASSERT(index != CB_ERR);

    CString srcBlkName;
    AcDbObjectId blkDefId;
    if (!m_blockList.GetAtIndex(index, srcBlkName, blkDefId)) {
        ASSERT(0);
        return;
    }

        // get name of destination block name
    CString destBlkName;
    m_ebDestName2.GetWindowText(destBlkName);

    if (!acdbSNValid(destBlkName, false)) {
        CString str;
        str.Format(_T("%s is not a valid block name."), destBlkName);
        ArxDbgUtils::alertBox(str);
        return;
    }

    UpdateData(TRUE);

    bool isExternal;
    AcDbDatabase* sourceDb = getSourceDb(isExternal);
    AcDbDatabase* destDb = getDestDb();
    ASSERT(sourceDb != destDb);

        // lock the document we are inserting into
    ArxDbgDocLockWrite docLock(destDb);
    if (docLock.lockAndSetCurrent() != Acad::eOk)
        return;

        // lock the document we are inserting from
    ArxDbgDocLockWrite docLock2(sourceDb);
    if (docLock2.lock() != Acad::eOk)
        return;

    bool preserveSrcDb = intToBool(m_preserveOriginalDb);
    if (!preserveSrcDb && !isExternal) {
        ArxDbgUtils::alertBox(_T("Ignoring setting of \"Preserve source database\" since destroying\na database associated with a Document would be harsh."));
        preserveSrcDb = true;
    }

    AcDbObjectId blkId;
    Acad::ErrorStatus es;
    es = destDb->insert(blkId, srcBlkName, destBlkName, sourceDb, preserveSrcDb);
    if (es == Acad::eOk) {
        ArxDbgUiTdmDatabase dbox(destDb, this, _T("Inserted Database"));
        dbox.DoModal();

        doSaveOption(destDb);

        if (isExternal && !preserveSrcDb)
            reloadRaidedExternalDwg(sourceDb);
    }
    else {
        CString str;
        str.Format(_T("Insert failed: %s"), ArxDbgUtils::rxErrorStr(es));
        ArxDbgUtils::stopAlertBox(str);
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcInsert::OnAddExternalDwg
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcInsert::OnAddExternalDwg()
{
    CString fname;
    Acad::ErrorStatus es;
    es = ArxDbgUtils::getFileNameForRead(_T("Drawing File"), NULL, _T("dwg"),
                       fname, false, false);

    if (es == Acad::eOk) {
        if (hasDwgFile(m_extDwgNames, fname))
            ArxDbgUtils::alertBox(_T("That DWG file is already in the list."));
        else {
            AcDbDatabase* db = new AcDbDatabase(false, true);
            es = db->readDwgFile(fname);

            if (es == Acad::eOk) {
                m_dbPtrs.append(db);
                m_extDwgNames.Add(fname);

                CString str;
                ArxDbgUtils::dbToStr(db, str);
                m_lbSourceDb.AddString(str);
                m_lbDestDb.AddString(str);
            }
            else {
                CString str;
                str.Format(_T("ERROR: could not read DWG file: %s"), ArxDbgUtils::rxErrorStr(es));
                ArxDbgUtils::alertBox(str);
            }
        }
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcInsert::reloadRaidedExternalDwg
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcInsert::reloadRaidedExternalDwg(AcDbDatabase* db)
{
    AcDbDatabase* tmpDb = NULL;

    const int len = m_dbPtrs.length();
    int i=0;
    for ( ; i<len; i++) {
        tmpDb = static_cast<AcDbDatabase*>(m_dbPtrs[i]);
        if (tmpDb == db)
            break;
    }

    delete db;    // delete this old damaged database;

    db = new AcDbDatabase(false, false);
    Acad::ErrorStatus es = db->readDwgFile(m_extDwgNames[i]);
    if (es == Acad::eOk)
        m_dbPtrs[i] = db;
    else {
        CString str;
        str.Format(_T("ERROR: could not reopen drawing file: %s"), ArxDbgUtils::rxErrorStr(es));
        ArxDbgUtils::alertBox(str);

            // get this out of the lists now.
        m_dbPtrs.removeAt(i);
        m_extDwgNames.RemoveAt(i);

        m_lbSourceDb.DeleteString(i);
        m_lbDestDb.DeleteString(i);

        m_lbSourceDb.SetCurSel(0);
        m_lbDestDb.SetCurSel(0);
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcInsert::hasDwgFile
**
**  **jma
**
*************************************/

bool
ArxDbgUiTdcInsert::hasDwgFile(CStringArray& dwgFiles, const CString& str)
{
    INT_PTR len = dwgFiles.GetSize();
    for (INT_PTR i = 0; i < len; i++) {
        if (dwgFiles[i] == str)
            return true;
    }

    return false;
}

/****************************************************************************
**
**  ArxDbgUiTdcInsert::doSaveOption
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcInsert::doSaveOption(AcDbDatabase* tmpDb)
{
    UpdateData(TRUE);

    if (m_saveAsDwg) {
        CString fname;
        Acad::ErrorStatus es;
        es = ArxDbgUtils::getFileNameForWrite(_T("Save Database As"), NULL, _T("dwg"),
                                        fname, false, false);

        if (es == Acad::eOk) {
            es = tmpDb->saveAs(fname);
            if (es != Acad::eOk) {
                CString str;
                str.Format(_T("SaveAs failed: %s"), ArxDbgUtils::rxErrorStr(es));
                ArxDbgUtils::stopAlertBox(str);
            }
        }
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcInsert::getSourceDb
**
**  **jma
**
*************************************/

AcDbDatabase*
ArxDbgUiTdcInsert::getSourceDb(bool& isExternal) 
{
    isExternal = false;

    int index = m_lbSourceDb.GetCurSel();
    if (index == LB_ERR) {
        ASSERT(0);
        return NULL;
    }

    if (m_extDwgNames[index] != _T(""))
        isExternal = true;

    AcDbDatabase* curDb = static_cast<AcDbDatabase*>(m_dbPtrs[index]);
    ASSERT(curDb != NULL);
    return curDb;
}

/****************************************************************************
**
**  ArxDbgUiTdcInsert::getDestDb
**
**  **jma
**
*************************************/

AcDbDatabase*
ArxDbgUiTdcInsert::getDestDb() 
{
    int index = m_lbDestDb.GetCurSel();
    if (index == LB_ERR) {
        ASSERT(0);
        return NULL;
    }

    AcDbDatabase* curDb = static_cast<AcDbDatabase*>(m_dbPtrs[index]);
    ASSERT(curDb != NULL);
    return curDb;
}
