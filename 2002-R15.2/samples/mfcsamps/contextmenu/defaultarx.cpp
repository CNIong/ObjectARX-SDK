//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 1998 by Autodesk, Inc. 
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
//////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <aced.h>       // AcEdUIContext
#include <rxmfcapi.h>
#include "defaultarx.h" // default mode.
#include <acdocman.h>
#include "resource.h"

//extern "C" HINSTANCE _hdllInstance;
extern HINSTANCE _hdllInstance;



defaultContext::defaultContext()
{
    acDocManager->pushResourceHandle(_hdllInstance);

    m_pMenu = new CMenu;
    m_pMenu->LoadMenu(IDR_DEFAULT_MENU); 

	acDocManager->popResourceHandle();
}

defaultContext::~defaultContext()
{
    if (m_pMenu) 
        delete m_pMenu;
}

// This function should return pointer to the HMENU that is to
// be added to AutoCAD context menu.
void* defaultContext::getMenuContext(const AcRxClass*, const AcDbObjectIdArray&)
{ 
    m_tempHMenu = m_pMenu->GetSubMenu(0)->GetSafeHmenu();   
    return &m_tempHMenu;
}

// This function is called when user selects a ARX added item
// The cmdIndex is the ID of the menu item as supplied by ARX app.
void defaultContext::onCommand(Adesk::UInt32 cmdIndex)
{
    acDocManager->pushResourceHandle(_hdllInstance);

    CString str1, str2;
    m_pMenu->GetMenuString(cmdIndex,str1,MF_BYCOMMAND);
    str2.Format(IDS_DEFAULTARX_SELECTION,str1);
    acutPrintf(str2);

    // display the command prompt again.
    acedPostCommandPrompt();

    acDocManager->popResourceHandle();
}

// Change the state of the menu items here. This function is
// called by AutoCAD just before querying the app for the context menu
void defaultContext::OnUpdateMenu()
{
    m_pMenu->EnableMenuItem(ID_DEFAULT_ITEM1,MF_ENABLED);
    m_pMenu->EnableMenuItem(ID_DEFAULT_SUB_ITEM1,MF_GRAYED);
    
}

///////////////////////////////////////////////////////////////////////////////////