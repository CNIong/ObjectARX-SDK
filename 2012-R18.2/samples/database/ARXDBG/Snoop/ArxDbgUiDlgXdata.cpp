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