//////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////
//
// Includes
//
#include "StdAfx.h"
//////////////////////////////////////////////////////////////
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <aced.h>       // AcEdUIContext
#include <rxmfcapi.h>
#include "cmdarx.h"     // command mode.
#include <acdocman.h>
#include "resource.h"



extern HINSTANCE _hdllInstance ;

cmCommandContext::cmCommandContext()
{
    acDocManager->pushResourceHandle(_hdllInstance);

    m_pMenu = new CMenu();
    m_pMenu->LoadMenu(IDR_CMD_MENU);

	acDocManager->popResourceHandle();
}

cmCommandContext::~cmCommandContext()
{
    if(m_pMenu) 
        delete m_pMenu;
}

// Change the state of the menu items here. This function is
// called by AutoCAD just before querying the app for the context menu
void cmCommandContext::OnUpdateMenu()
{
    m_pMenu->CheckMenuItem(ID_CMD_SUB_ITEM1,MF_CHECKED);
    m_pMenu->EnableMenuItem(ID_CMD_ITEM1,MF_GRAYED);
}

// This function should return pointer to the HMENU that is to
// be added to AutoCAD context menu.
void* cmCommandContext::getMenuContext(const AcRxClass*, const AcDbObjectIdArray&)
{
    m_tempHMenu = m_pMenu->GetSubMenu(0)->GetSafeHmenu();
    return &m_tempHMenu;
}

// This function is called when user selects a ARX added item
// The cmdIndex is the ID of the menu item as supplied by ARX app.
void cmCommandContext::onCommand(Adesk::UInt32 cmdIndex)
{
    acDocManager->pushResourceHandle(_hdllInstance);

    CString str1,str2;
    m_pMenu->GetMenuString(cmdIndex,str1,MF_BYCOMMAND);
    str2.Format(IDS_CMDARX_SELECTION,str1);
    acutPrintf(str2);

    // Again put up the command prompt.
    CString str;
    str.LoadString(IDS_CMDARX_PROMPT);
    str = _T('\n') + str;
    acutPrintf(str);

    acDocManager->popResourceHandle();
}

// This function is called when the user types "sample"
void cm()
{
    acDocManager->pushResourceHandle(_hdllInstance);

    TCHAR buf[100];
    CString str;
    str.LoadString(IDS_CMDARX_PROMPT);
    // wait for user input.
    acedGetString(0, str, buf);

    acDocManager->popResourceHandle();
}

//////////////////////////////////////////////////////////////////////////////////
