// (C) Copyright 1993-2007 by Autodesk, Inc.
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

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "CurvetextHelper.h"
#include "resource.h"
#include "..\CurveText_DB\CurveText.h"

#include <acdocman.h>

#include "ContextMenu.h"


extern  HINSTANCE _hdllInstance ;

curvetextContextMenu::curvetextContextMenu()
{
   	acDocManager->pushResourceHandle(_hdllInstance);

	m_pMenu = new CMenu;
	m_pMenu->LoadMenu(IDR_EDIT_CURVETEXT);
	uniqueEntity = false;
	acDocManager->popResourceHandle();
}


curvetextContextMenu::~curvetextContextMenu()
{
	if(m_pMenu)
		delete m_pMenu;
}

void*
curvetextContextMenu::getMenuContext(const AcRxClass *pClass, const AcDbObjectIdArray& ids)
{
	if(ids.length() == 1)
		uniqueEntity = true;
	else
		uniqueEntity = false;

	if(uniqueEntity)
	{
		m_pMenu->EnableMenuItem(ID_CURVETEXT_SETTEXTSTARTPOINT,MF_ENABLED);
		m_pMenu->EnableMenuItem(ID_CURVETEXT_SETTEXTENDPOINT,MF_ENABLED);
	}
	else
	{
		m_pMenu->EnableMenuItem(ID_CURVETEXT_SETTEXTSTARTPOINT,MF_GRAYED);
		m_pMenu->EnableMenuItem(ID_CURVETEXT_SETTEXTENDPOINT,MF_GRAYED);
	}
	m_pMenu->EnableMenuItem(ID_CURVETEXT_REVERSE,MF_ENABLED);

    m_HMenu = m_pMenu->GetSubMenu(0)->GetSafeHmenu();
    return &m_HMenu;
}


void
curvetextContextMenu::onCommand(Adesk::UInt32 cmdIndex)
{

	switch(cmdIndex)
	{
	case ID_CURVETEXT_REVERSE:
		acDocManager->sendStringToExecute(curDoc(), _T("ASDK_CURVETEXT.reverse "));
		break;

	case ID_CURVETEXT_CURVE_SHOW:
		acDocManager->sendStringToExecute(curDoc(), _T("ASDK_CURVETEXT.showCurve "));
		break;

	case ID_CURVETEXT_CURVE_HIDE:
		acDocManager->sendStringToExecute(curDoc(), _T("ASDK_CURVETEXT.hideCurve "));
		break;

	case ID_CURVETEXT_TEXT_SHOW:
		acDocManager->sendStringToExecute(curDoc(), _T("ASDK_CURVETEXT.ShowText "));
		break;

	case ID_CURVETEXT_TEXT_HIDE:
		acDocManager->sendStringToExecute(curDoc(), _T("ASDK_CURVETEXT.HideText "));
		break;

	case ID_CURVETEXT_FITTEXT_YES:
		acDocManager->sendStringToExecute(curDoc(), _T("ASDK_CURVETEXT.fit "));
		break;

	case ID_CURVETEXT_FITTEXT_NO:
		acDocManager->sendStringToExecute(curDoc(), _T("ASDK_CURVETEXT.noFit "));
		break;

	case ID_CURVETEXT_REPEATTEXT_YES:
		acDocManager->sendStringToExecute(curDoc(), _T("ASDK_CURVETEXT.repeatText "));
		break;

	case ID_CURVETEXT_REPEATTEXT_NO:
		acDocManager->sendStringToExecute(curDoc(), _T("ASDK_CURVETEXT.noTextRepetition "));
		break;

	case ID_CURVETEXT_SETTEXTSTARTPOINT:
		acDocManager->sendStringToExecute(curDoc(), _T("ASDK_CURVETEXT.ssp "));
		break;

	case ID_CURVETEXT_SETTEXTENDPOINT:
		acDocManager->sendStringToExecute(curDoc(), _T("ASDK_CURVETEXT.sep "));
		break;
	}
}

void
curvetextContextMenu::OnUpdateMenu()
{
}

///////////////////////////////////////////////////////////////////////////////
//
curveContextMenu::curveContextMenu()
{
	acDocManager->pushResourceHandle(_hdllInstance);
	m_pMenu = new CMenu;
	m_pMenu->LoadMenu(IDR_EDIT_CURVES);
	
	acDocManager->popResourceHandle();	
}


curveContextMenu::~curveContextMenu()
{
	if(m_pMenu)
		delete m_pMenu;
}

void*
curveContextMenu::getMenuContext(const AcRxClass *pClass, const AcDbObjectIdArray& ids)
{
    m_HMenu = m_pMenu->GetSubMenu(0)->GetSafeHmenu();
    return &m_HMenu;
}

void
curveContextMenu::onCommand(Adesk::UInt32 cmdIndex)
{

	switch(cmdIndex)
	{
	case ID_CURVES_CURVETEXT:
		acDocManager->sendStringToExecute(curDoc(), _T("ASDK_CURVETEXT.ct"));
		break;
	}
}

void
curveContextMenu::OnUpdateMenu()
{
	m_pMenu->EnableMenuItem(ID_CURVES_CURVETEXT,MF_ENABLED);
}