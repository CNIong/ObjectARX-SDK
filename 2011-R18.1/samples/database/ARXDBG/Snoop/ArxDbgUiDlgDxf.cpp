//
// (C) Copyright 1998-2007 by Autodesk, Inc. 
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

#include "ArxDbgUiDlgDxf.h"
#include "ArxDbgUtils.h"
#include "ArxDbgApp.h"
#include "ArxDbgRbList.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgUiDlgDxf::ArxDbgUiDlgDxf
**
**  **jma
**
*************************************/

ArxDbgUiDlgDxf::ArxDbgUiDlgDxf(CWnd* parent, AcDbObject* obj)
:	CAcUiDialog(ArxDbgUiDlgDxf::IDD, parent, ArxDbgApp::getApp()->dllInstance())
{
    ASSERT(obj != NULL);
    m_objPtr = obj;

    //{{AFX_DATA_INIT(ArxDbgUiDlgDxf)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiDlgDxf::ArxDbgUiDlgDxf
**
**  **jma
**
*************************************/

ArxDbgUiDlgDxf::ArxDbgUiDlgDxf(CWnd* parent, AcDbObject* obj, UINT dlgResId)
:	CAcUiDialog(dlgResId, parent, ArxDbgApp::getApp()->dllInstance())
{
    ASSERT(obj != NULL);
    m_objPtr = obj;
}

/****************************************************************************
**
**  ArxDbgUiDlgDxf::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgDxf::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiDlgDxf)
    DDX_Control(pDX, ARXDBG_LC_DXF, m_dxfList);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgDxf message map

BEGIN_MESSAGE_MAP(ArxDbgUiDlgDxf, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxDbgUiDlgDxf)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgDxf message handlers

/****************************************************************************
**
**  ArxDbgUiDlgDxf::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiDlgDxf::OnInitDialog() 
{
    CAcUiDialog::OnInitDialog();
    
    ads_name ent;
    acdbGetAdsName(ent, m_objPtr->objectId());

        // get entity data the ADS way (as DXF codes)
    resbuf* apps = acutNewRb(RTSTR);
	acutNewString(_T("*"),apps->resval.rstring);    
    resbuf* entdata = acdbEntGetX(ent, apps);
    acutRelRb(apps);

    buildColumns();
    displayRbChain(entdata);

    acutRelRb(entdata);
    
    return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiDlgDxf::buildColumns
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgDxf::buildColumns()
{
        // get the width of the window
    CRect lvRect;
    int col1_width, col2_width;
    m_dxfList.GetClientRect(lvRect);
    col1_width = lvRect.Width() / 5;
    col2_width = lvRect.Width() - col1_width - ::GetSystemMetrics(SM_CXVSCROLL);

        // initialize the columns
    LV_COLUMN lvc;
    lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvc.cx = col1_width;
    lvc.iSubItem = 0;
    lvc.pszText = _T("DXF Code");
    m_dxfList.InsertColumn(0, &lvc);

    lvc.cx = col2_width;
    lvc.iSubItem = 1;
    lvc.pszText = _T("Value");
    m_dxfList.InsertColumn(1, &lvc);
}

/****************************************************************************
**
**  ArxDbgUiDlgDxf::displayRbChain
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgDxf::displayRbChain(resbuf* dxfData)
{
    m_dxfList.DeleteAllItems();    // remove any existing items

        // build up the list view control
    LV_ITEM lvi;
    lvi.mask = LVIF_TEXT;
    CString dxfCodeStr, valueStr;
    dxfCodeStr.GetBuffer(512);    //increase size of internal buffer from 128 to 512
    valueStr.GetBuffer(512);

    resbuf* tmp = dxfData;
    int row = 0;
    while (tmp) {
        dxfToStr(tmp, dxfCodeStr, valueStr);
        lvi.iItem = row;
        lvi.iSubItem = 0;
        lvi.pszText = dxfCodeStr.GetBuffer(0);    // requires non-const char*
        m_dxfList.InsertItem(&lvi);
        m_dxfList.SetItemText(row++, 1, valueStr);
        tmp = tmp->rbnext;
    }
}
