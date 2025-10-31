//
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

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "trayitem.h"
#include "resource.h"




extern HINSTANCE _hdllInstance;

CTrayItem::CTrayItem(void)
{
}

CTrayItem::~CTrayItem(void)
{
}

void CTrayItem::OnLButtonDown(UINT nFlags, CPoint point)
{
    AfxMessageBox(_T("Tray Item Clicked"));
}

void CTrayItem::OnRButtonDown(UINT nFlags, CPoint point)
{
    CMenu menu;
    if(!menu.LoadMenu(IDR_TRAYITEM_MENU))
        return;

    UINT nID = DisplayContextMenu(menu, point);

    CString strMsg(_T("No menu item selected"));
    if(nID != 0)
    {
         switch (nID) {  

            case ID_TRAYITEMMENU_TRAYITEM1:
                strMsg = _T("Tray Menu item 1 selected");
                break;

            case ID_TRAYITEMMENU_TRAYITEM2:
                strMsg = _T("Tray Menu item 2 selected");
                break;

            case ID_TRAYITEMMENU_TRAYITEM3:
                strMsg = _T("Tray Menu item 3 selected");
                break;
        }
        AfxMessageBox(strMsg);
    }
}

void CTrayItem::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    AfxMessageBox(_T("Tray Item Double Click"));
}


// CPaneItem
CPaneItem::CPaneItem(void)
: m_Enable(false)
{
}

CPaneItem::~CPaneItem(void)
{
}

void CPaneItem::OnLButtonDown(UINT nFlags, CPoint point)
{
    m_Enable=!m_Enable;
	if(m_Enable)
	{
		SetStyle(ACSB_NORMAL);	
		AfxMessageBox(_T("Pane Item Enabled"));
	}
	else
	{
		SetStyle(ACSB_POPOUT);	
		AfxMessageBox(_T("Pane Item Disabled"));
	}
	acDocManager->curDocument()->drawingStatusBar()->Update();
	
	

}

void CPaneItem::OnRButtonDown(UINT nFlags, CPoint point)
{
    CMenu menu;
    if(!menu.LoadMenu(IDR_MENU1))
        return;

    UINT nID = DisplayContextMenu(menu, point);

    CString strMsg(_T("No menu item selected"));
    if(nID != 0)
    {
         switch (nID) {  

            case ID_TRAYITEMMENU_TRAYITEM1:
                strMsg = _T("Pane Menu item 1 selected");
                break;

            case ID_TRAYITEMMENU_TRAYITEM2:
                strMsg = _T("Pane Menu item 2 selected");
                break;

            case ID_TRAYITEMMENU_TRAYITEM3:
                strMsg = _T("Pane Menu item 3 selected");
                break;
        }
        AfxMessageBox(strMsg);
    }
}

void CPaneItem::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    AfxMessageBox(_T("Pane Item Double Click"));
}

// CMenuPaneItem
CMenuPaneItem::CMenuPaneItem(void)
{
}

CMenuPaneItem::~CMenuPaneItem(void)
{
}

void CMenuPaneItem::OnLButtonDown(UINT nFlags, CPoint point)
{
    OnRButtonDown(nFlags, point);
}

void CMenuPaneItem::OnRButtonDown(UINT nFlags, CPoint point)
{
    CMenu menu;
    if(!menu.LoadMenu(IDR_STATUSBAR_MENU))
        return;

    UINT nID = DisplayContextMenu(menu, point);

    CString strMsg(_T("No menu item selected"));
    if(nID != 0)
    {
         switch (nID) {  

            case ID_STATUSBARMENU_STATUSBARITEM1:
                {
                    strMsg = _T("SB Menu Item 1");
                }
                break;
            case ID_STATUSBARMENU_STATUSBARITEM2:
                {
                    strMsg = _T("SB Menu Item 2");
                }
                break;

            case ID_STATUSBARMENU_STATUSBARITEM3:
                {
                    strMsg = _T("SB Menu Item 3");
                }
                break;
        }

        AfxMessageBox(strMsg);
    }

 
}

void CMenuPaneItem::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    AfxMessageBox(_T("Left Button Double Click"));
}

