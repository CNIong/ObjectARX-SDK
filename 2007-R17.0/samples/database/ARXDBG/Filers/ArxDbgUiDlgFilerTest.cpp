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
