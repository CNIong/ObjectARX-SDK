// (C) Copyright 2002-2006 by Autodesk, Inc. 
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
#include "StdAfx.h"
#include "resource.h"
#include ".\asdkuicontext.h"
#include "..\\SliderCrankDb\AsdkSliderCrank.h"
#include "axlock.h"

AsdkUIContext::AsdkUIContext(void)
{
    CAcModuleResourceOverride override;

    m_pMenu = new CMenu();
    m_pMenu->LoadMenu(IDR_MENU_SLIDERCRANK);
}

AsdkUIContext::~AsdkUIContext(void)
{
    delete m_pMenu;
}

void* AsdkUIContext::getMenuContext(const AcRxClass * type, const AcDbObjectIdArray& entities)
{
    if(entities.length() > 1) return NULL;

    m_id = entities.at(0);
    m_tempHMenu = m_pMenu->GetSubMenu(0)->GetSafeHmenu();	
    return &m_tempHMenu;
}

void * AsdkUIContext::getMenuContext(const AcRxClass* pClass,const AcDbObjectIdArray& entities,const AcArray<AcDbFullSubentPathArray, AcArrayObjectCopyReallocator<AcDbFullSubentPathArray> >& subentIds)
{
    if((0 == entities.length()) || (pClass != AsdkSliderCrank::desc())
        ||(0 == subentIds.length()) || (0 == subentIds.at(0).length())) return NULL;

    m_id = entities.at(0);

    switch(subentIds.at(0).at(0).subentId().index()) 
    {
    case LINK:
        m_tempHMenu = m_pMenu->GetSubMenu(1)->GetSafeHmenu();	
        return &m_tempHMenu;	
    case PISTON:
        m_tempHMenu = m_pMenu->GetSubMenu(2)->GetSafeHmenu();	
        return &m_tempHMenu;
    case CRANK:
        m_tempHMenu = m_pMenu->GetSubMenu(3)->GetSafeHmenu();	
        return &m_tempHMenu;
    }
    return NULL;
}

void  AsdkUIContext::onCommand(Adesk::UInt32 cmdIndex)
{
    acDocManager->pushResourceHandle(_hdllInstance);

    if (m_id.isNull()) return;

    AcAxDocLock loc;

    AcDbEntityPointer pEnt(m_id, AcDb::kForWrite);
    if(Acad::eOk != pEnt.openStatus()) return;
    AsdkSliderCrank *pSC = AsdkSliderCrank::cast(pEnt);

    AcCmColor col;
    AcCmColor curcol;
    acedSetColorDialogTrueColor(col, true, curcol);

    AcCmEntityColor entcol;
    entcol.setColor(col.color());

    switch(cmdIndex) 
    {
    case ID_SLIDERCRANK_CRANKCOLOR:
    case ID_CRANK_CRANKCOLOR:
        pSC->setCrankColor(entcol);
        break;
    case ID_SLIDERCRANK_PISTONCOLOR:
    case ID_PISTON_PISTONCOLOR:
        pSC->setPistonColor(entcol);
        break;
    case ID_SLIDERCRANK_LINKCOLOR:
    case ID_LINK_LINKCOLOR:
        pSC->setConnectingLinkColor(entcol);
        break;
    }

    // display the command prompt again.
    acedPostCommandPrompt();

    acDocManager->popResourceHandle();
}