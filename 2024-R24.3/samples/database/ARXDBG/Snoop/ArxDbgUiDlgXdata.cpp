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

#include "ArxDbgUiDlgXdata.h"
#include "ArxDbgUtils.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgUiDlgXdata::ArxDbgUiDlgXdata
**
**  **jma
**
*************************************/

ArxDbgUiDlgXdata::ArxDbgUiDlgXdata(CWnd* parent, AcDbObject* obj)
:   ArxDbgUiDlgDxf(parent, obj, ArxDbgUiDlgXdata::IDD),
    m_xdata(obj)
{
    //{{AFX_DATA_INIT(ArxDbgUiDlgXdata)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


/****************************************************************************
**
**  ArxDbgUiDlgXdata::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgXdata::DoDataExchange(CDataExchange* pDX)
{
    ArxDbgUiDlgDxf::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiDlgXdata)
    DDX_Control(pDX, ARXDBG_POPUP_APPS, m_appPopUp);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgXdata message map

BEGIN_MESSAGE_MAP(ArxDbgUiDlgXdata, ArxDbgUiDlgDxf)
    //{{AFX_MSG_MAP(ArxDbgUiDlgXdata)
    ON_CBN_SELENDOK(ARXDBG_POPUP_APPS, OnAppNameSelected)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgXdata message handlers

/****************************************************************************
**
**  ArxDbgUiDlgXdata::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiDlgXdata::OnInitDialog() 
{
    CAcUiDialog::OnInitDialog();	// purposely bypass base class

    buildColumns();        // insert list control columns
    
        // build up list of app names for pop up list
    ArxDbgAppXdataListIterator iter(m_xdata);
    m_appPopUp.AddString(_T("*  (All Applications)"));
    for (; !iter.done(); iter.next()) {
        m_appPopUp.AddString(iter.item()->getAppName());
    }
    m_appPopUp.SetCurSel(0);
    OnAppNameSelected();    // fake out selection of item 0
    
    return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiDlgXdata::OnAppNameSelected
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgXdata::OnAppNameSelected() 
{
    resbuf* tmpXdata;
    int index = m_appPopUp.GetCurSel();

    if (index == CB_ERR)
        index = 0;

    if (index == 0) {    // iterate through all apps
        ArxDbgRbList allXdata, singleAppXdata;
        ArxDbgAppXdataListIterator iter(m_xdata);
        for (; !iter.done(); iter.next()) {
            singleAppXdata.adoptData(iter.item()->allocResbufChain());
            allXdata.append(singleAppXdata);
        }
        displayRbChain(allXdata.data());    // display one big list
    }
    else {
            // look up this specific app
        ArxDbgAppXdata* xdPtr = m_xdata.at(index-1);
        tmpXdata = xdPtr->allocResbufChain();
        displayRbChain(tmpXdata);
        acutRelRb(tmpXdata);
    }
}