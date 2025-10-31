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

