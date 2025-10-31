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

#include "ArxDbgUiDlgObjState.h"
#include "ArxDbgUtils.h"
#include "ArxDbgApp.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgUiDlgObjState::ArxDbgUiDlgObjState
**
**  **jma
**
*************************************/

ArxDbgUiDlgObjState::ArxDbgUiDlgObjState(CWnd* parent, const AcDbObjectId& objId, LPCTSTR dboxTitle)
:   CAcUiDialog(ArxDbgUiDlgObjState::IDD, parent, ArxDbgApp::getApp()->dllInstance()),
    m_obj(NULL),
    m_objId(objId),
    m_wasOpenOnConstruct(false),
    m_dboxTitle(dboxTitle),
	m_bUpgradedFromNotify(false)
{
    //{{AFX_DATA_INIT(ArxDbgUiDlgObjState)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT

    SetPersistency(FALSE);
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::ArxDbgUiDlgObjState
**
**  **jma
**
*************************************/

ArxDbgUiDlgObjState::ArxDbgUiDlgObjState(CWnd* parent, AcDbObject* obj, LPCTSTR dboxTitle)
:   CAcUiDialog(ArxDbgUiDlgObjState::IDD, parent, ArxDbgApp::getApp()->dllInstance()),
    m_obj(obj),
    m_objId(obj->objectId()),
    m_wasOpenOnConstruct(true),
    m_dboxTitle(dboxTitle)
{
    //{{AFX_DATA_INIT(ArxDbgUiDlgObjState)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::~ArxDbgUiDlgObjState
**
**  **jma
**
*************************************/

ArxDbgUiDlgObjState::~ArxDbgUiDlgObjState()
{
    if (m_wasOpenOnConstruct == false) {
            // if left open, the next person to try to access it
            // fails miserably, so try to close it all the way
        if (m_obj != NULL) {
            Acad::ErrorStatus es = Acad::eOk;
            while (!m_obj->isReallyClosing()) {
                es = m_obj->cancel();
                if (es == Acad::eCloseWasNotifying)
                    return;
                if (es != Acad::eOk)
                    ArxDbgUtils::rxErrorAlert(es);
                else
                    acutPrintf(_T("\nCalling obj->cancel()."));
            }
            es = m_obj->cancel();
            if (es == Acad::eCloseWasNotifying)
                return;

            if (es != Acad::eOk)
                ArxDbgUtils::rxErrorAlert(es);
            else
                acutPrintf(_T("\nCalling obj->cancel()."));
        }
    }
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjState::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiDlgObjState)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgObjState message map

BEGIN_MESSAGE_MAP(ArxDbgUiDlgObjState, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxDbgUiDlgObjState)
    ON_BN_CLICKED(ARXDBG_BN_CLOSE, OnCloseObj)
    ON_BN_CLICKED(ARXDBG_BN_CANCEL, OnCancelObj)
    ON_BN_CLICKED(ARXDBG_BN_CLOSE_PAGE, OnCloseAndPageObj)
    ON_BN_CLICKED(ARXDBG_BN_DOWNGRADE_TO_N, OnDowngradeToNotify)
    ON_BN_CLICKED(ARXDBG_BN_DOWNGRADE_W, OnDowngradeWrite)
    ON_BN_CLICKED(ARXDBG_BN_ERASE, OnEraseObj)
    ON_BN_CLICKED(ARXDBG_BN_UNERASE, OnUneraseObj)
    ON_BN_CLICKED(ARXDBG_BN_MODIFY, OnModifyObj)
    ON_BN_CLICKED(ARXDBG_BN_NOTIFY, OnOpenForNotify)
    ON_BN_CLICKED(ARXDBG_BN_READ, OnOpenForRead)
    ON_BN_CLICKED(ARXDBG_BN_UPGRADE_FROM_N, OnUpgradeFromNotify)
    ON_BN_CLICKED(ARXDBG_BN_UPGRADE_TO_W, OnUpgradeToWrite)
    ON_BN_CLICKED(ARXDBG_BN_WRITE, OnOpenForWrite)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgObjState message handlers

/****************************************************************************
**
**  ArxDbgUiDlgObjState::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiDlgObjState::OnInitDialog() 
{
    CAcUiDialog::OnInitDialog();

    if (m_dboxTitle)
        SetWindowText(m_dboxTitle);
    
    display();
    
    return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::objIsOpen
**
**  **jma
**
*************************************/

bool
ArxDbgUiDlgObjState::objIsOpen()
{
    if (m_obj == NULL) {
        ArxDbgUtils::stopAlertBox(_T("The object is not open."));
        return false;
    }
    else
        return true;
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::objIsOpenForWrite
**
**  **jma
**
*************************************/

bool
ArxDbgUiDlgObjState::objIsOpenForWrite()
{
    if (!objIsOpen())
        return false;

    if (m_obj->isWriteEnabled())
        return true;
    else {
        ArxDbgUtils::stopAlertBox(_T("The object must be open for write."));
        return false;
    }
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::open
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjState::open(AcDb::OpenMode openMode)
{
    Acad::ErrorStatus es;
    es = acdbOpenObject(m_obj, m_objId, openMode);
    if (es != Acad::eOk)
        ArxDbgUtils::rxErrorAlert(es);
    else {
        if (openMode == AcDb::kForRead)
            SetDlgItemText(ARXDBG_TXT_ERRMSG, _T("Opened For Read"));
        else if (openMode == AcDb::kForWrite)
            SetDlgItemText(ARXDBG_TXT_ERRMSG, _T("Opened For Write"));
        else
            SetDlgItemText(ARXDBG_TXT_ERRMSG, _T("Opened For Notify"));
    }
    display();
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::doErase
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjState::doErase(bool reallyErase)
{
    if (!objIsOpenForWrite())
        return;

    Acad::ErrorStatus es;
    es = m_obj->erase(reallyErase);
    if (es != Acad::eOk)
        ArxDbgUtils::rxErrorAlert(es);
    else {
        if (reallyErase == Adesk::kTrue)
            SetDlgItemText(ARXDBG_TXT_ERRMSG, _T("Erased"));
        else
            SetDlgItemText(ARXDBG_TXT_ERRMSG, _T("Un-Erased"));
    }
    display();
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::display
**      display the current state of the entity
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjState::display()
{
    CString str;
    LPCTSTR unknown = _T("N/A");

    if ((m_obj != NULL) && m_obj->isReadEnabled()){
        SetDlgItemText(ARXDBG_TXT_CLASS, ArxDbgUtils::objToClassStr(m_obj));
        SetDlgItemText(ARXDBG_TXT_NEWOBJ, ArxDbgUtils::booleanToStr(m_obj->isNewObject(), str));
        SetDlgItemText(ARXDBG_TXT_READ_ENABLED, ArxDbgUtils::booleanToStr(m_obj->isReadEnabled(), str));
        SetDlgItemText(ARXDBG_TXT_WRITE_ENABLED, ArxDbgUtils::booleanToStr(m_obj->isWriteEnabled(), str));
        SetDlgItemText(ARXDBG_TXT_NOTIFY_ENABLED, ArxDbgUtils::booleanToStr(m_obj->isNotifyEnabled(), str));
        SetDlgItemText(ARXDBG_TXT_MODIFIED, ArxDbgUtils::booleanToStr(m_obj->isModified(), str));
        SetDlgItemText(ARXDBG_TXT_MOD_XDATA, ArxDbgUtils::booleanToStr(m_obj->isModifiedXData(), str));
        SetDlgItemText(ARXDBG_TXT_MOD_GRAPHICS, ArxDbgUtils::booleanToStr(m_obj->isModifiedGraphics(), str));
        SetDlgItemText(ARXDBG_TXT_PROXY, ArxDbgUtils::booleanToStr(m_obj->isAProxy(), str));
        SetDlgItemText(ARXDBG_TXT_TRANS_RESIDENT, ArxDbgUtils::booleanToStr(m_obj->isTransactionResident(), str));
        SetDlgItemText(ARXDBG_TXT_ERASED, ArxDbgUtils::booleanToStr(m_obj->isErased(), str));
        SetDlgItemText(ARXDBG_TXT_ERASE_TOGGLED, ArxDbgUtils::booleanToStr(m_obj->isEraseStatusToggled(), str));
        SetDlgItemText(ARXDBG_TXT_NOTIFYING, ArxDbgUtils::booleanToStr(m_obj->isNotifying(), str));
        SetDlgItemText(ARXDBG_TXT_UNDOING, ArxDbgUtils::booleanToStr(m_obj->isUndoing(), str));
        SetDlgItemText(ARXDBG_TXT_CANCELLING, ArxDbgUtils::booleanToStr(m_obj->isCancelling(), str));
        SetDlgItemText(ARXDBG_TXT_REALLY_CLOSING, ArxDbgUtils::booleanToStr(m_obj->isReallyClosing(), str));
        SetDlgItemText(ARXDBG_TXT_ERRMSG, _T("Object pointer is valid"));
    }
    else {
        SetDlgItemText(ARXDBG_TXT_CLASS, unknown);
        SetDlgItemText(ARXDBG_TXT_NEWOBJ, unknown);
        SetDlgItemText(ARXDBG_TXT_READ_ENABLED, unknown);
        SetDlgItemText(ARXDBG_TXT_WRITE_ENABLED, unknown);
        SetDlgItemText(ARXDBG_TXT_NOTIFY_ENABLED, unknown);
        SetDlgItemText(ARXDBG_TXT_MODIFIED, unknown);
        SetDlgItemText(ARXDBG_TXT_MOD_XDATA, unknown);
        SetDlgItemText(ARXDBG_TXT_MOD_GRAPHICS, unknown);
        SetDlgItemText(ARXDBG_TXT_PROXY, unknown);
        SetDlgItemText(ARXDBG_TXT_TRANS_RESIDENT, unknown);
        SetDlgItemText(ARXDBG_TXT_ERASED, unknown);
        SetDlgItemText(ARXDBG_TXT_ERASE_TOGGLED, unknown);
        SetDlgItemText(ARXDBG_TXT_NOTIFYING, unknown);
        SetDlgItemText(ARXDBG_TXT_UNDOING, unknown);
        SetDlgItemText(ARXDBG_TXT_CANCELLING, unknown);
        SetDlgItemText(ARXDBG_TXT_REALLY_CLOSING, unknown);
        SetDlgItemText(ARXDBG_TXT_ERRMSG, _T("Object pointer not valid, use object Id"));
    }
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::OnOpenForRead
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjState::OnOpenForRead() 
{
    open(AcDb::kForRead);
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::OnOpenForWrite
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjState::OnOpenForWrite() 
{
    open(AcDb::kForWrite);
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::OnOpenForNotify
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjState::OnOpenForNotify() 
{
    open(AcDb::kForNotify);
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::OnModifyObj
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjState::OnModifyObj() 
{
    if (!objIsOpenForWrite())
        return;

    AcDbEntity* entPtr;
    if ((entPtr = AcDbEntity::cast(m_obj)) == NULL) {
        ArxDbgUtils::stopAlertBox(_T("This test requires an AcDbEntity."));
        return;
    }

    Acad::ErrorStatus es;
    int color = entPtr->colorIndex();
    if (color >= 255)
        es = entPtr->setColorIndex(1);
    else
        es = entPtr->setColorIndex(color+1);

    if (es != Acad::eOk)
        ArxDbgUtils::rxErrorAlert(es);
    else
        ArxDbgUtils::alertBox(_T("The color index was incremented as a test for modification."));

    display();
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::OnUpgradeToWrite
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjState::OnUpgradeToWrite() 
{
    if (!objIsOpen())
        return;

    Acad::ErrorStatus es;
    es = m_obj->upgradeOpen();
    if (es != Acad::eOk)
        ArxDbgUtils::rxErrorAlert(es);
    else
        SetDlgItemText(ARXDBG_TXT_ERRMSG, _T("Upgraded To Write"));

    display();
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::OnDowngradeWrite
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjState::OnDowngradeWrite() 
{
    if (!objIsOpen())
        return;

    Acad::ErrorStatus es;
    es = m_obj->downgradeOpen();
    if (es != Acad::eOk)
        ArxDbgUtils::rxErrorAlert(es);
    else
        SetDlgItemText(ARXDBG_TXT_ERRMSG, _T("Downgraded From Write"));

    display();
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::OnUpgradeFromNotify
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjState::OnUpgradeFromNotify() 
{
    if (!objIsOpen())
        return;

    Acad::ErrorStatus es;
    es = m_obj->upgradeFromNotify(m_bWasWritable);
    if (es != Acad::eOk)
        ArxDbgUtils::rxErrorAlert(es);
	else {
        SetDlgItemText(ARXDBG_TXT_ERRMSG, _T("Upgraded From Notify"));
		m_bUpgradedFromNotify =true ;
	}

    display();
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::OnDowngradeToNotify
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjState::OnDowngradeToNotify() 
{
    if (!objIsOpen())
        return;

	if (!m_bUpgradedFromNotify)
	{
		ArxDbgUtils::alertBox(_T("This function must have been preceded by a call to upgradeFromNotify()."));
		return ;
	}
	m_bUpgradedFromNotify =false ;

    Acad::ErrorStatus es;
    es = m_obj->downgradeToNotify(m_bWasWritable);
	if (es != Acad::eOk)
        ArxDbgUtils::rxErrorAlert(es);
    else
        SetDlgItemText(ARXDBG_TXT_ERRMSG, _T("Downgraded To Notify"));

    display();
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::OnCancelObj
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjState::OnCancelObj() 
{
    if (!objIsOpen())
        return;

    Adesk::Boolean totallyClosed = m_obj->isReallyClosing();
    Adesk::Boolean wasModified = m_obj->isModified();

    Acad::ErrorStatus es;
    es = m_obj->cancel();
    if (es != Acad::eOk)
        ArxDbgUtils::rxErrorAlert(es);
    else {
        if (wasModified)
            SetDlgItemText(ARXDBG_TXT_ERRMSG, _T("Cancelled, modifications ignored"));
        else
            SetDlgItemText(ARXDBG_TXT_ERRMSG, _T("Cancelled"));
    }

    if (totallyClosed)
        m_obj = NULL;

    display();
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::OnCloseObj
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjState::OnCloseObj() 
{
    if (!objIsOpen())
        return;

	Adesk::Boolean totallyClosed = m_obj->isReallyClosing();
    Adesk::Boolean wasModified = m_obj->isModified();

    Acad::ErrorStatus es;
    es = m_obj->close();
    if (es != Acad::eOk)
        ArxDbgUtils::rxErrorAlert(es);
    else {
        if (wasModified)
            SetDlgItemText(ARXDBG_TXT_ERRMSG, _T("Closed, modifications written to database"));
        else
            SetDlgItemText(ARXDBG_TXT_ERRMSG, _T("Closed"));
    }

    if (totallyClosed)
        m_obj = NULL;

    display();
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::OnCloseAndPageObj
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjState::OnCloseAndPageObj() 
{
    if (!objIsOpen())
        return;

	Adesk::Boolean totallyClosed = m_obj->isReallyClosing();
    Adesk::Boolean wasModified = m_obj->isModified();

    Acad::ErrorStatus es;
    es = m_obj->closeAndPage();
    if (es != Acad::eOk)
        ArxDbgUtils::rxErrorAlert(es);
    else {
        if (wasModified)
            SetDlgItemText(ARXDBG_TXT_ERRMSG, _T("Closed, modifications written to database"));
        else
            SetDlgItemText(ARXDBG_TXT_ERRMSG, _T("Closed"));
    }

    if (totallyClosed)
        m_obj = NULL;

    display();
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::OnEraseObj
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjState::OnEraseObj() 
{
    doErase(true);
}

/****************************************************************************
**
**  ArxDbgUiDlgObjState::OnUneraseObj
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjState::OnUneraseObj() 
{
    doErase(false);
}



