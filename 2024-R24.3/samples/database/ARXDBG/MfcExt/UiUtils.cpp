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

#include "ArxDbgUtils.h"



/****************************************************************************
**
**  ArxDbgUtils::alertBox
**
**  **jma
**
*************************************/

void
ArxDbgUtils::alertBox(LPCTSTR msg)
{
    AfxMessageBox(msg, MB_OK | MB_ICONEXCLAMATION);
}

/****************************************************************************
**
**  ArxDbgUtils::stopAlertBox
**
**  **jma
**
*************************************/

void
ArxDbgUtils::stopAlertBox(LPCTSTR msg)
{
    AfxMessageBox(msg, MB_OK | MB_ICONSTOP);
}

/****************************************************************************
**
**  ArxDbgUtils::infoAlertBox
**
**  **jma
**
*************************************/

void
ArxDbgUtils::infoAlertBox(LPCTSTR msg)
{
    AfxMessageBox(msg, MB_OK | MB_ICONINFORMATION);
}

/****************************************************************************
**
**  ArxDbgUtils::stubAlert
**
**  **jma
**
*************************************/

void
ArxDbgUtils::stubAlert(LPCTSTR msg)
{
    CString str;
    str.Format(_T("Not Implemented Yet: %s"), msg);
    AfxMessageBox(str, MB_OK | MB_ICONINFORMATION);
}

/****************************************************************************
**
**  ArxDbgUtils::yesNoAlert
**      use when you have a yes/no question.  Pass in the default
**  button(which is No by default).
**
**  **jma
**
*************************************/

UINT
ArxDbgUtils::yesNoAlert(LPCTSTR msg, UINT defButton /*=no*/)
{
    UINT theDefault =(defButton == IDYES)? MB_DEFBUTTON1 : MB_DEFBUTTON2;
    return(AfxMessageBox(msg, MB_YESNO | MB_ICONQUESTION | theDefault));
}

/****************************************************************************
**
**  ArxDbgUtils::yesNoCancelAlert
**      use when you have a yes/no/cancel question.  Pass in the default
**  button(which is Cancel by default).
**
**  **jma
**
*************************************/

UINT
ArxDbgUtils::yesNoCancelAlert(LPCTSTR msg, UINT defButton /*=cancel*/)
{
    UINT theDefault;

    if (defButton == IDYES)
        theDefault = MB_DEFBUTTON1;
    else if(defButton == IDNO)
        theDefault = MB_DEFBUTTON2;
    else
        theDefault = MB_DEFBUTTON3;

    return(AfxMessageBox(msg, MB_YESNOCANCEL | MB_ICONQUESTION | theDefault));
}

/****************************************************************************
**
**  ArxDbgUtils::fillListBox
**
**  **jma
**
*************************************/

void
ArxDbgUtils::fillListBox(const SdStrList& slist, CListBox& lb, int defIndex)
{
    BOOL addedOne = FALSE;

    lb.ResetContent();
    SdStrListIterator iter(slist);
    for(; !iter.done(); iter.next()) {
        addedOne = TRUE;
        lb.AddString(iter.item());
    }

    if ( addedOne )
        lb.SetCurSel(defIndex);
}

/****************************************************************************
**
**  ArxDbgUtils::fillListBox
**
**  **jma
**
*************************************/

void
ArxDbgUtils::fillListBox(const SdStrObjIdList& slist, CListBox& lb, int defIndex)
{
    lb.ResetContent();
    SdStrObjIdListIterator iter(slist);

    CString str;
    AcDbObjectId objId;
    for(; !iter.done(); iter.next()){
        iter.item(str, objId);
        lb.AddString(str);
    }

    int retCode = lb.SetCurSel(defIndex);
    ASSERT(retCode != LB_ERR);
}

/****************************************************************************
**
**  ArxDbgUtils::fillListBox
**
**  **jma
**
*************************************/

void
ArxDbgUtils::fillListBox(const SdStrObjIdList& slist, CComboBox& cb, int defIndex)
{
    cb.ResetContent();
    SdStrObjIdListIterator iter(slist);

    CString str;
    AcDbObjectId objId;
    for(; !iter.done(); iter.next()){
        iter.item(str, objId);
        cb.AddString(str);
    }

    int retCode = cb.SetCurSel(defIndex);
    ASSERT(retCode != CB_ERR);
}

/****************************************************************************
**
**  ArxDbgUtils::enableDlgItem
**
**  **jma
**
*************************************/

void
ArxDbgUtils::enableDlgItem(CWnd* parentWnd, UINT resId, BOOL enableIt)
{
    CWnd* dlgItem = parentWnd->GetDlgItem(resId);
    ASSERT(dlgItem != NULL);
    if (dlgItem)
        dlgItem->EnableWindow(enableIt);
}

/****************************************************************************
**
**  ArxDbgUtils::hideDlgItem
**
**  **jma
**
*************************************/

void
ArxDbgUtils::hideDlgItem(CWnd* parentWnd, UINT resId, BOOL hideIt)
{
    CWnd* dlgItem = parentWnd->GetDlgItem(resId);
    ASSERT(dlgItem != NULL);
    if (dlgItem) {
        if (hideIt)
            dlgItem->ShowWindow(SW_HIDE);
        else
            dlgItem->ShowWindow(SW_SHOW);
    }
}

/****************************************************************************
**
**  ArxDbgUtils::getCurSel
**      returns -1 if not successful
**
**  **jma
**
*************************************/

int
ArxDbgUtils::getCurSel(const CListCtrl& listCtrl)
{
    return listCtrl.GetNextItem(-1, LVNI_SELECTED);
}

/****************************************************************************
**
**  ArxDbgUtils::setCurSel
**
**  **jma
**
*************************************/

BOOL
ArxDbgUtils::setCurSel(CListCtrl& listCtrl, int index)
{
    if (index == -1) {
        for (int row = 0; row < listCtrl.GetItemCount(); row++) {
                // turn off any currently selected items
            if (listCtrl.GetItemState(row, LVIS_SELECTED) & LVIS_SELECTED)
                listCtrl.SetItemState(row, 0, LVIS_SELECTED | LVIS_FOCUSED);
        }
        return TRUE;
    }
    else {
        listCtrl.EnsureVisible(index, TRUE);
        return listCtrl.SetItemState(index, (LVIS_SELECTED | LVIS_FOCUSED), (LVIS_SELECTED | LVIS_FOCUSED));
    }
}

/****************************************************************************
**
**  ArxDbgUtils::getFname
**      wrapper around MFC CFileDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUtils::getFname(LPCTSTR title, LPCTSTR ext, LPCTSTR defFname, CString& fname)
{
    CFileDialog dbox(TRUE, ext, defFname);

        // add title if one was specified
    if (title != NULL)
        dbox.m_ofn.lpstrTitle = title;

    if (dbox.DoModal() == IDOK) {
        fname = dbox.GetPathName();
        return(TRUE);
    }
    else
        return(FALSE);
}
