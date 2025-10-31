//
// (C) Copyright 2002-2007 by Autodesk, Inc. 
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

// BarsWorkspace.cpp : Initialization functions
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "StdArx.h"
#include "resource.h"
#include <afxdllx.h>
#include "trayitem.h"



HINSTANCE _hdllInstance =NULL ;

// This command registers an ARX command.
void AddCommand(const TCHAR* cmdGroup, const TCHAR* cmdInt, const TCHAR* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal = -1);

// Document Manager Reactor
// asdkDocManagerReactor *pReactor;


// We can't rely on the index of the tray items to be constant, so we
// need to keep an independent map of the first tray item for each document.
CMap<AcApDocument*,AcApDocument*,CTrayItem*,CTrayItem*> documentTrayMap;

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_MSG
void InitApplication();
void UnloadApplication();
//}}AFX_ARX_MSG

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_ADDIN_FUNCS
//}}AFX_ARX_ADDIN_FUNCS


////////////////////////////////////////////////////////////////////////////
//
// Define the sole extension module object.
AC_IMPLEMENT_EXTENSION_MODULE(BarsWorkspaceDLL);

// Now you can use the CAcModuleResourceOverride class in
// your application to switch to the correct resource instance.
// Please see the ObjectARX Documentation for more details

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
        _hdllInstance = hInstance;
		// Extension DLL one time initialization
		BarsWorkspaceDLL.AttachInstance(hInstance);
		InitAcUiDLL();
	} else if (dwReason == DLL_PROCESS_DETACH) {
		// Terminate the library before destructors are called
		BarsWorkspaceDLL.DetachInstance();

	}
	return TRUE;    // ok
}



void CreateDocumentWorkspace(AcApDocument* pDoc);
void DestroyDocumentWorkspace(AcApDocument *pDoc);

/////////////////////////////////////////////////////////////////////////////
// ObjectARX EntryPoint
extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	switch (msg) {
	case AcRx::kInitAppMsg:
		// Comment out the following line if your
		// application should be locked into memory
		acrxDynamicLinker->unlockApplication(pkt);
		acrxDynamicLinker->registerAppMDIAware(pkt);
		InitApplication();
		break;
	case AcRx::kUnloadAppMsg:
		UnloadApplication();
		break;

		// add or remove items to/from document status 
		// bar here because all databases are active at this point. 
	case AcRx::kLoadDwgMsg:
		CreateDocumentWorkspace(curDoc());
		break;
	case AcRx::kUnloadDwgMsg:
		DestroyDocumentWorkspace(curDoc());
		break;
	}
	return AcRx::kRetOK;
}

// Create the tray items for the passed document.
void CreateDocumentWorkspace(AcApDocument* pDoc)
{
	// Create the tray items:
	CTrayItem *pTray=new CTrayItem;
	// Create World Tray Item:
	HICON hIcon = (HICON)::LoadImage(_hdllInstance, MAKEINTRESOURCE(IDI_WORLD), IMAGE_ICON, 16, 16, 0);
    int result=pTray->SetIcon(hIcon);
    result=pTray->SetToolTipText(_T("World Icon ToolTip"));
    pTray->Enable(TRUE);
    pTray->SetVisible(TRUE);
	result=pDoc->drawingStatusBar()->Add(pTray);

	// Set this document to map to the first tray item.
	documentTrayMap.SetAt(pDoc,pTray);

    // Create Pie Tray Item:
	pTray=new CTrayItem;
	hIcon = (HICON)::LoadImage(_hdllInstance, MAKEINTRESOURCE(IDI_PIE), IMAGE_ICON, 16, 16, 0);
    result=pTray->SetIcon(hIcon);
    result=pTray->SetToolTipText(_T("Pie Icon ToolTip"));
    pTray->Enable(TRUE);
    pTray->SetVisible(TRUE);
	result=pDoc->drawingStatusBar()->Add(pTray);

    // Create Tree Tray Item:
	pTray=new CTrayItem;
	hIcon = (HICON)::LoadImage(_hdllInstance, MAKEINTRESOURCE(IDI_TREE), IMAGE_ICON, 16, 16, 0);
    result=pTray->SetIcon(hIcon);
    result=pTray->SetToolTipText(_T("Tree Icon ToolTip"));
    pTray->Enable(TRUE);
    pTray->SetVisible(TRUE);
	result=pDoc->drawingStatusBar()->Add(pTray);

	// Create a Pane Item with Text...
	CPaneItem *pPane=new CPaneItem;
	result=pPane->SetToolTipText(_T("Pane Item Tooltip"));
	pPane->Enable(TRUE);
	pPane->SetVisible(TRUE);
	result=pPane->SetStyle(ACSB_POPOUT);
	result=pPane->SetText(_T("Pane Item"));
	result=pPane->SetMinWidth(pDoc->drawingStatusBar()->GetTextWidth(_T("Pane Item")));
	result=pDoc->drawingStatusBar()->Add(pPane);
    
	// Create a Pane Item with an Icon...
	pPane=new CPaneItem;
	result=pPane->SetToolTipText(_T("Pane Icon Item Tooltip"));
	pPane->Enable(TRUE);
	result=pPane->SetStyle(ACSB_POPOUT);
	pPane->SetVisible(TRUE);
	hIcon = (HICON)::LoadImage(_hdllInstance, MAKEINTRESOURCE(IDI_WORLD), IMAGE_ICON, 16, 16, 0);
    result=pPane->SetIcon(hIcon);
	result=pDoc->drawingStatusBar()->Add(pPane);
	
	// Create a status bar menu item...this replaces the default menu item (the small black triangle on the lower right of the doc window).
	CMenuPaneItem *pMenuPane=new CMenuPaneItem;
	result=pDoc->drawingStatusBar()->SetStatusBarMenuItem(pMenuPane);
}

// Cleanup the tray items for the passed document.
void DestroyDocumentWorkspace(AcApDocument *pDoc)
{
	if(!documentTrayMap.RemoveKey(pDoc))
		AfxMessageBox(_T("Couldn't remove tray item from the document map"));
    	
	AcApStatusBar *pStatusBar=pDoc->drawingStatusBar();
    AcTrayItem* pTrayItem = NULL;
	if(pStatusBar)
	{
		// Remove all tray items that we added in this sample.
		int count = pStatusBar->GetTrayItemCount();	
		int iPos = 0;
		for(int i = 0; i<count; i++)	
		{
			pTrayItem = pStatusBar->GetTrayItem(iPos);
			if(pTrayItem)
			{
				CString ttt;
				pTrayItem->GetToolTipText(ttt);
				if(	ttt.Compare(_T("World Icon ToolTip")) == 0 ||
					ttt.Compare(_T("Pie Icon ToolTip")) == 0 ||
					ttt.Compare(_T("Tree Icon ToolTip")) == 0 
					)
				{
					pStatusBar->Remove(pTrayItem);
					delete pTrayItem;
				}
				else
					iPos++;
			}
		}
	
		// Remove all pane items from the status bar.
	    AcPane *pPane=NULL;
		count = pStatusBar->GetPaneCount(); 
		iPos = 0;
		for(int i=0;i<count; i++)
		{
			pPane=pStatusBar->GetPane(iPos);
			if(pPane)
			{
				CString ttt;
				pPane->GetToolTipText(ttt);
				if(	ttt.Compare(_T("Pane Item Tooltip")) == 0 ||
					ttt.Compare(_T("Pane Icon Item Tooltip")) == 0 
					)
				{
					pStatusBar->Remove(pPane);
					delete pPane;
				}
				else
					iPos++;
			}
		}
		// Remove the context menu pane.
		// Note this will make the context menu empty and there is no way to recover the previous 
		// default menu. Therefore, a better way is to make this app as unloadable (lock it). 
		// If the app is locked, there is no need to remove it with the line below as
		// AutoCAD will clean up when it quits.
		pStatusBar->SetStatusBarMenuItem(NULL);
	}
}

// Called when a bubble notification is closed.  
// The return code indicates the close condition.  
// You can customize the pData argument to suit your needs as well.
void BubbleWindowCallback(void *pData,int nReturnCode)
{
    CString strMsg;
	switch(nReturnCode)
    {
    case AcTrayItemBubbleWindowControl::BUBBLE_WINDOW_ERROR_NO_CREATE:
        AfxMessageBox(_T("Couldn't Create the Bubble Window!"));
        break;
    case AcTrayItemBubbleWindowControl::BUBBLE_WINDOW_ERROR_NO_ICONS:
        AfxMessageBox(_T("No Tray Area for the Bubble Window!"));
        break;
    case AcTrayItemBubbleWindowControl::BUBBLE_WINDOW_ERROR_NO_NOTIFICATIONS:
        AfxMessageBox(_T("No Bubble Window Notifications!"));
        break;
    case AcTrayItemBubbleWindowControl::BUBBLE_WINDOW_CLOSE:
        acutPrintf(_T("\nNotification Closed...\n"));
		break;
    case AcTrayItemBubbleWindowControl::BUBBLE_WINDOW_TIME_OUT:
		acutPrintf(_T("\nNotification Timed Out...\n"));
        break;
    case AcTrayItemBubbleWindowControl::BUBBLE_WINDOW_HYPERLINK_CLICK:
        acutPrintf(_T("\nHyperlink Selected...\n"));
        break;
	}
	acedPostCommandPrompt();
}

// This is the command 'NOTIFY'
void asdkBubble()
{
	// Create the bubble notification message, and callbacks.
	int result;
	AcApDocument *pDoc=acDocManager->curDocument();
	CString strMsg((CString)_T("Document ")+pDoc->docTitle()+_T(" Notification"));
	AcTrayItemBubbleWindowControl bwControl(_T("Attention!"), strMsg, _T("HyperText Here"), _T("www.autodesk.com"));
	bwControl.SetIconType(AcTrayItemBubbleWindowControl::BUBBLE_WINDOW_ICON_INFORMATION);
	bwControl.SetCallback(BubbleWindowCallback, pDoc);
	
	// Display the notification at the first of our icons - kept as a pointer in the map.
	CTrayItem *pFirstTrayItem=NULL;
	documentTrayMap.Lookup(acDocManager->curDocument(),pFirstTrayItem);
	if(pFirstTrayItem)
		result=pFirstTrayItem->ShowBubbleWindow(&bwControl);
}


// Init this application. Register your
// commands, reactors...
void InitApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_INIT
	AddCommand(_T("ADSK"), _T("NOTIFY"), _T("NOTIFY"), ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, asdkBubble);
	//}}AFX_ARX_INIT

	// Enable tray items on the document windows.
	acedShowDrawingStatusBars();
    
}

// Unload this application. Unregister all objects
// registered in InitApplication.
void UnloadApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_EXIT
	//}}AFX_ARX_EXIT
	
	acedRegCmds->removeGroup(_T("ADSK"));

	documentTrayMap.RemoveAll();
}

// This functions registers an ARX command.
// It can be used to read the localized command name
// from a string table stored in the resources.
void AddCommand(const TCHAR* cmdGroup, const TCHAR* cmdInt, const TCHAR* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal)
{
	TCHAR cmdLocRes[65];

	// If idLocal is not -1, it's treated as an ID for
	// a string stored in the resources.
	if (idLocal != -1) {

		// Load strings from the string table and register the command.
		::LoadString(_hdllInstance, idLocal, cmdLocRes, 64);
		acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLocRes, cmdFlags, cmdProc);

	} else
		// idLocal is -1, so the 'hard coded'
		// localized function name is used.
		acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLoc, cmdFlags, cmdProc);
}
