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

#include "ArxDbgUiDlgFilerTest.h"
#include "ArxDbgUtils.h"
#include "ArxDbgDwgFiler.h"
#include "ArxDbgApp.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgUiDlgFilerTest::ArxDbgUiDlgFilerTest
**
**  **jma
**
*************************************/

ArxDbgUiDlgFilerTest::ArxDbgUiDlgFilerTest(CWnd* parent)
:	CAcUiDialog(ArxDbgUiDlgFilerTest::IDD, parent, ArxDbgApp::getApp()->dllInstance())
{
    //{{AFX_DATA_INIT(ArxDbgUiDlgFilerTest)
    m_puFilerTypeIndex = 1;		// default to CopyFiler
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiDlgFilerTest::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgFilerTest::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiDlgFilerTest)
    DDX_CBIndex(pDX, ARXDBG_PU_FILER_TYPE, m_puFilerTypeIndex);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgFilerTest message map

BEGIN_MESSAGE_MAP(ArxDbgUiDlgFilerTest, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxDbgUiDlgFilerTest)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgFilerTest message handlers

/****************************************************************************
**
**  ArxDbgUiDlgFilerTest::indexToFilerType
**
**  **jma
**
*************************************/

AcDb::FilerType
ArxDbgUiDlgFilerTest::indexToFilerType(int index)
{
    if (index == 0)
        return AcDb::kFileFiler;
    else if (index == 1)
        return AcDb::kCopyFiler;
    else if (index == 2)
        return AcDb::kUndoFiler;
    else if (index == 3)
        return AcDb::kIdFiler;
    else if (index == 4)
        return AcDb::kIdXlateFiler;
    else if (index == 5)
        return AcDb::kPageFiler;
    else if (index == 6)
        return AcDb::kDeepCloneFiler;
    else if (index == 7)
        return AcDb::kWblockCloneFiler;
    else if (index == 8)
        return AcDb::kPurgeFiler;
    else {
        ASSERT(0);
        return AcDb::kFileFiler;
    }
}
