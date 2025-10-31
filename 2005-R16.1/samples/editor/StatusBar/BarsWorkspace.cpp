//
// (C) Copyright 2002 by Autodesk, Inc. 
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
#include "StdArx.h"
#include "resource.h"
#include <afxdllx.h>
#include "trayitem.h"

HINSTANCE _hdllInstance =NULL ;

// This command registers an ARX command.
void AddCommand(const char* cmdGroup, const char* cmdInt, const char* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal = -1);
// Document Manager Reactor
asdkDocManagerReactor *pReactor;


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
	result=pPane->SetToolTipText("Pane Item Tooltip");
	pPane->Enable(TRUE);
	pPane->SetVisible(TRUE);
	result=pPane->SetStyle(ACSB_POPOUT);
	result=pPane->SetText("Pane Item");
	result=pPane->SetMinWidth(pDoc->drawingStatusBar()->GetTextWidth("Pane Item"));
	result=pDoc->drawingStatusBar()->Add(pPane);
    
	// Create a Pane Item with an Icon...
	pPane=new CPaneItem;
	result=pPane->SetToolTipText("Pane Icon Item Tooltip");
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
		AfxMessageBox("Couldn't remove tray item from the document map");
    	
	AcApStatusBar *pStatusBar=pDoc->drawingStatusBar();
    AcTrayItem* pTrayItem = NULL;
	if(pStatusBar)
	{
		for(int i = 0; i < pStatusBar->GetTrayItemCount(); i++)
		{
			pTrayItem = pStatusBar->GetTrayItem(0);
			if(pTrayItem)
			{
				pStatusBar->Remove(pTrayItem);
				delete pTrayItem;
			}
		}
	
	    AcPane *pPane=NULL;
		for(i=0;i<pStatusBar->GetPaneCount();i++)
		{
			pPane=pStatusBar->GetPane(i);
			if(pPane)
			{
				pStatusBar->Remove(i);
				delete pPane;
			}
		}
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
        AfxMessageBox("Couldn't Create the Bubble Window!");
        break;
    case AcTrayItemBubbleWindowControl::BUBBLE_WINDOW_ERROR_NO_ICONS:
        AfxMessageBox("No Tray Area for the Bubble Window!");
        break;
    case AcTrayItemBubbleWindowControl::BUBBLE_WINDOW_ERROR_NO_NOTIFICATIONS:
        AfxMessageBox("No Bubble Window Notifications!");
        break;
    case AcTrayItemBubbleWindowControl::BUBBLE_WINDOW_CLOSE:
        acutPrintf("\nNotification Closed...\n");
		break;
    case AcTrayItemBubbleWindowControl::BUBBLE_WINDOW_TIME_OUT:
		acutPrintf("\nNotification Timed Out...\n");
        break;
    case AcTrayItemBubbleWindowControl::BUBBLE_WINDOW_HYPERLINK_CLICK:
        acutPrintf("\nHyperlink Selected...\n");
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
	AcTrayItemBubbleWindowControl bwControl("Attention!", strMsg, "HyperText Here", "www.autodesk.com");
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
	AddCommand("ADSK", "NOTIFY", "NOTIFY", ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, asdkBubble);
	//}}AFX_ARX_INIT

	// Enable tray items on the document windows.
	acedShowDrawingStatusBars();
    
	// For each open document, create a document workspace.
	AcApDocumentIterator *pItr=acDocManager->newAcApDocumentIterator();
	for(;!pItr->done();pItr->step())
		CreateDocumentWorkspace(pItr->document());
	delete pItr;

	// Instantiate the document manager reactor, and attach it so we can be notified of document events.
	pReactor=new asdkDocManagerReactor;
}

// Unload this application. Unregister all objects
// registered in InitApplication.
void UnloadApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_EXIT
	//}}AFX_ARX_EXIT

	// Cleanup each workspace, and delete the doc manager reactor.
	AcApDocumentIterator *pItr=acDocManager->newAcApDocumentIterator();
	for(;!pItr->done();pItr->step())
		DestroyDocumentWorkspace(pItr->document());
	delete pItr;
	
	delete pReactor;
	documentTrayMap.RemoveAll();
}

// This functions registers an ARX command.
// It can be used to read the localized command name
// from a string table stored in the resources.
void AddCommand(const char* cmdGroup, const char* cmdInt, const char* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal)
{
	char cmdLocRes[65];

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
