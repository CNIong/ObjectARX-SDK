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

#include "ArxDbgUiDlgWorldDraw.h"
#include "ArxDbgApp.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgUiDlgWorldDraw::ArxDbgUiDlgWorldDraw
**
**  **jma
**
*************************************/

ArxDbgUiDlgWorldDraw::ArxDbgUiDlgWorldDraw(ArxDbgGiWorldDraw& wd, CWnd* parent)
:	CAcUiDialog(ArxDbgUiDlgWorldDraw::IDD, parent, ArxDbgApp::getApp()->dllInstance()),
    m_wd(wd)
{
    //{{AFX_DATA_INIT(ArxDbgUiDlgWorldDraw)
    m_cbDragging = FALSE;
    m_ebDeviation = 0.5;
    m_ebIsolines = 16;
    m_rgRegenType = 0;
    m_cbShowWorldDraw = ArxDbgGiWorldDraw::m_showWorldDrawMsg;
    m_cbShowGeom = ArxDbgGiWorldDraw::m_showGeomMsg;
    m_cbShowSubents = ArxDbgGiWorldDraw::m_showSubentsMsg;
    m_cbShowDetail = ArxDbgGiWorldDraw::m_showDetailsMsg;
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiDlgWorldDraw::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgWorldDraw::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiDlgWorldDraw)
    DDX_Check(pDX, ARXDBG_CB_DRAGGING, m_cbDragging);
    DDX_Text(pDX, ARXDBG_EB_DEVIATION, m_ebDeviation);
    DDV_MinMaxDouble(pDX, m_ebDeviation, 0.1, 10.);
    DDX_Text(pDX, ARXDBG_EB_ISOLINES, m_ebIsolines);
    DDV_MinMaxInt(pDX, m_ebIsolines, 1, 50);
    DDX_Radio(pDX, ARXDBG_RB_STANDARD, m_rgRegenType);
    DDX_Check(pDX, ARXDBG_CB_SHOW_GEOM, m_cbShowGeom);
    DDX_Check(pDX, ARXDBG_CB_SHOW_PRAMS, m_cbShowDetail);
    DDX_Check(pDX, ARXDBG_CB_SHOW_SUBENT, m_cbShowSubents);
    DDX_Check(pDX, ARXDBG_CB_SHOW_WORLDRAW, m_cbShowWorldDraw);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgWorldDraw message map

BEGIN_MESSAGE_MAP(ArxDbgUiDlgWorldDraw, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxDbgUiDlgWorldDraw)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgWorldDraw message handlers

/****************************************************************************
**
**  ArxDbgUiDlgWorldDraw::regenType
**
**  **jma
**
*************************************/

AcGiRegenType
ArxDbgUiDlgWorldDraw::regenType() const
{
    if (m_rgRegenType == 0)
        return kAcGiStandardDisplay;
    else if (m_rgRegenType == 1)
        return kAcGiHideOrShadeCommand;
    else if (m_rgRegenType == 2)
        return kAcGiShadedDisplay;
    else if (m_rgRegenType == 3)
        return kAcGiSaveWorldDrawForR12;
    else if (m_rgRegenType == 4)
        return kAcGiSaveWorldDrawForProxy;
    else {
        ASSERT(0);
        return kAcGiStandardDisplay;
    }
}

/****************************************************************************
**
**  ArxDbgUiDlgWorldDraw::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiDlgWorldDraw::OnInitDialog() 
{
    CAcUiDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    
    return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiDlgWorldDraw::OnOK
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgWorldDraw::OnOK() 
{
    CAcUiDialog::OnOK();

    m_wd.setIsDragging(!!m_cbDragging);
    m_wd.setDeviation(m_ebDeviation);
    m_wd.setIsolines(m_ebIsolines);
    m_wd.setRegenType(regenType());

        // set global statics that control messages
    ArxDbgGiWorldDraw::m_showWorldDrawMsg = m_cbShowWorldDraw;
    ArxDbgGiWorldDraw::m_showGeomMsg = m_cbShowGeom;
    ArxDbgGiWorldDraw::m_showSubentsMsg = m_cbShowSubents;
    ArxDbgGiWorldDraw::m_showDetailsMsg = m_cbShowDetail;
}
