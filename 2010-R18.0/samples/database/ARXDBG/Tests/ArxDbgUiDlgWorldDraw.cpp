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

    m_wd.setIsDragging(m_cbDragging);
    m_wd.setDeviation(m_ebDeviation);
    m_wd.setIsolines(m_ebIsolines);
    m_wd.setRegenType(regenType());

        // set global statics that control messages
    ArxDbgGiWorldDraw::m_showWorldDrawMsg = m_cbShowWorldDraw;
    ArxDbgGiWorldDraw::m_showGeomMsg = m_cbShowGeom;
    ArxDbgGiWorldDraw::m_showSubentsMsg = m_cbShowSubents;
    ArxDbgGiWorldDraw::m_showDetailsMsg = m_cbShowDetail;
}
