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

#include "ArxDbgCmdReactors.h"
#include "ArxDbgUiTdmReactors.h"



/****************************************************************************
**
**  ArxDbgCmdReactors::registerCommandLineFunctions
**
**  **jma
**
*************************************/

void
ArxDbgCmdReactors::registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname)
{
	cmdStack->addCommand(appname, _T("ArxDbgReactors"), _T("Reactors"), ACRX_CMD_MODAL, &reactors);
}

/****************************************************************************
**
**  ArxDbgCmdReactors::reactors
**
**  **jma
**
*************************************/

void
ArxDbgCmdReactors::reactors()
{
    ArxDbgUiTdmReactors dbox(acedGetAcadDwgView());
    dbox.DoModal();
}

