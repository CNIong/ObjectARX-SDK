//
// (C) Copyright 1998-2007 by Autodesk, Inc. 
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
//
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif




// global per app
CSampDialog* gpDlg = NULL;
bool gbDisplayDialog = false;
//
//	AutoCAD command linked function to watch database modifications.
//
//
void DisplayDialog()
{
    if(getYorN(_T("Start watching entity modifications")))
	{
		gbDisplayDialog = true;
        attachDbReactor(CUR_DB);

		gpEdReactor = new CEdReactor();
		acedEditor->addReactor(gpEdReactor);

		startDlg();
	}
    else
	{
		gbDisplayDialog = false;
		DetachEdReactor();
        detachDbReactor(CUR_DB);
		endDlg();
	}
}

void DetachEdReactor()
{
	if ( gpEdReactor )
	{
		acedEditor->removeReactor(gpEdReactor);
		delete gpEdReactor ;
		gpEdReactor =NULL ;
	}
}
//
//	Get a boolean from the user.
//
//
Adesk::Boolean getYorN(const TCHAR* pStr)
{
    TCHAR yorn_str[132];
    
    yorn_str[0] = _T('Y');
    yorn_str[1] = _T('\0');
    acutPrintf(_T("\n%s"), pStr);
    acedInitGet(0, _T("No Yes"));
    acedGetKword( _T(" -- No/<Yes>:  "), yorn_str);
    
    return yorn_str[0] != _T('N');
}
//
//	Start up the modeless dialog.
//
//
BOOL startDlg()
{
	BOOL b = TRUE;
	if(!gpDlg)
	{
		CAcModuleResourceOverride resOverride;
		gpDlg = new CSampDialog(acedGetAcadFrame());
		b = gpDlg->Create(ID_SAMPDIALOG);
	}
    
    return b;
}
//
//
//
BOOL endDlg()
{
    if(!gpDlg)
        return TRUE;
    
    BOOL b = gpDlg->DestroyWindow();
    if(b)
        gpDlg = NULL;
    return b;
}
/////////////////////////////////////////////////////////////////////////////////
//
//
//
CSampDialog::CSampDialog (CWnd* pParent) : CDialog(CSampDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSampDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
//	When AutoCAD asks your dialog if it is willing to give up input
//	focus, return true to keep the focus and false to give it up.
//
#ifndef WM_ACAD_MFC_BASE
#define WM_ACAD_MFC_BASE        (1000)
#endif

#ifndef WM_ACAD_KEEPFOCUS
#define WM_ACAD_KEEPFOCUS       (WM_ACAD_MFC_BASE + 1)
#endif

BEGIN_MESSAGE_MAP(CSampDialog, CDialog)
	//{{AFX_MSG_MAP(CSampDialog)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, onAcadKeepFocus)
	ON_BN_CLICKED(IDUNDO, OnUndo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



void CSampDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSampDialog)
	DDX_Control(pDX, IDUNDO, m_undoBtn);
	//}}AFX_DATA_MAP
}

//
//
//	Because the dialog is about to close, disconnect the database reactor.
//  It is not called when a user click on the cross box.
//
void CSampDialog::OnClose()
{
	gbDisplayDialog = false;
    if(CUR_DB)
		detachDbReactor(CUR_DB);
	CDialog::OnClose();
	endDlg();
}
//
//	This function gets called repeatedly whenever the mouse is moved over
//	the AutoCAD window.
//
LRESULT CSampDialog::onAcadKeepFocus(WPARAM, LPARAM)
{
    return TRUE;
}

void CSampDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	gbDisplayDialog = false;
    if(CUR_DB)
		detachDbReactor(CUR_DB);
	
	CDialog::OnCancel();
	endDlg();
}

void CSampDialog::OnUndo() 
{
	acDocManager->sendStringToExecute(acDocManager->curDocument(), _T("_UNDO 1 "),false, true);	
}
