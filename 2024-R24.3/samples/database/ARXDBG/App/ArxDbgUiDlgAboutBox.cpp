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

#include "ArxDbgUiDlgAboutBox.h"
#include "ArxDbgApp.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  cmdAboutBox
**
**  **jma
**
*************************************/

void
cmdAboutBox()
{
    ArxDbgUiDlgAboutBox dbox(acedGetAcadDwgView());
    dbox.DoModal();
}


/****************************************************************************
**
**  ArxDbgUiDlgAboutBox::ArxDbgUiDlgAboutBox
**
**  **jma
**
*************************************/

ArxDbgUiDlgAboutBox::ArxDbgUiDlgAboutBox(CWnd* parent)
:	CAcUiDialog(ArxDbgUiDlgAboutBox::IDD, parent, ArxDbgApp::getApp()->dllInstance())
{
    //{{AFX_DATA_INIT(ArxDbgUiDlgAboutBox)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiDlgAboutBox::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgAboutBox::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiDlgAboutBox)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgAboutBox message map

BEGIN_MESSAGE_MAP(ArxDbgUiDlgAboutBox, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxDbgUiDlgAboutBox)
        // NOTE: the ClassWizard will add message map macros here
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgAboutBox message handlers
