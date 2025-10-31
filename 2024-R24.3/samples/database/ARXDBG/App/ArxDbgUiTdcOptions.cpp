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

#include "ArxDbgUiTdcOptions.h"
#include "ArxDbgOptions.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgUiTdcOptions::ArxDbgUiTdcOptions
**
**  **jma
**
*************************************/

ArxDbgUiTdcOptions::ArxDbgUiTdcOptions(CWnd* pParent)
:	CAcUiTabChildDialog(pParent)
{
	//{{AFX_DATA_INIT(ArxDbgUiTdcOptions)
	//}}AFX_DATA_INIT

		// get the initial values from our global object
	m_showDwgFilerMsgs =       ArxDbgOptions::m_instance.m_showDwgFilerMessages;
	m_showWblockCloneDetails = ArxDbgOptions::m_instance.m_showWblockCloneDetails;
	m_showDeepCloneDetails =   ArxDbgOptions::m_instance.m_showDeepCloneDetails;
	m_doDictInsertByHand =     ArxDbgOptions::m_instance.m_doDictRecordInsertByHand;
}

/****************************************************************************
**
**  ArxDbgUiTdcOptions::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcOptions::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabChildDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ArxDbgUiTdcOptions)
	DDX_Check(pDX, ARXDBG_CB_DWG_FILER_MESSAGES, m_showDwgFilerMsgs);
	DDX_Check(pDX, ARXDBG_CB_DEEP_CLONE_DETAILS, m_showDeepCloneDetails);
	DDX_Check(pDX, ARXDBG_CB_WBLOCK_CLONE_DETAILS, m_showWblockCloneDetails);
	DDX_Check(pDX, ARXDBG_CB_USE_DICT_MERGESTYLE, m_doDictInsertByHand);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcOptions message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdcOptions, CAcUiTabChildDialog)
	//{{AFX_MSG_MAP(ArxDbgUiTdcOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcOptions message handlers

/****************************************************************************
**
**  ArxDbgUiTdcOptions::OnMainDialogOK
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcOptions::OnMainDialogOK()
{
    CAcUiTabChildDialog::OnMainDialogOK();

		// set the final values on our global object. NOTE: can't just
		// put these directly in the DDX map since MFC doesn't map anything
		// to type "bool", only to type "BOOL"
	ArxDbgOptions::m_instance.m_showDwgFilerMessages     = intToBool(m_showDwgFilerMsgs);
	ArxDbgOptions::m_instance.m_showWblockCloneDetails   = intToBool(m_showWblockCloneDetails);
	ArxDbgOptions::m_instance.m_showDeepCloneDetails     = intToBool(m_showDeepCloneDetails);
	ArxDbgOptions::m_instance.m_doDictRecordInsertByHand = intToBool(m_doDictInsertByHand);
}

