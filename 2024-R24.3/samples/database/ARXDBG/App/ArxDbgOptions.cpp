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

#include "ArxDbgOptions.h"



ArxDbgOptions	ArxDbgOptions::m_instance;	// declare single static instance of this

/****************************************************************************
**
**  ArxDbgOptions::ArxDbgOptions
**
**  **jma
**
*************************************/

ArxDbgOptions::ArxDbgOptions()
:	m_showDwgFilerMessages(false),
	m_showWblockCloneDetails(false),
	m_showDeepCloneDetails(false),
	m_doDictRecordInsertByHand(true)
{
}