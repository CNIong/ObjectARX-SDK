//////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1994-2002 by Autodesk, Inc.
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
//////////////////////////////////////////////////////////////////////////////

#ifndef _aduiTabCtrl_h
#define _aduiTabCtrl_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
/*
USAGE TIPS:
  * For the most logical tab ordering w/r/t added tabs, make sure that the tab
    control itself is last in the tab order of the Main Frame dialog.  Don't
    worry, this isn't really a constraint!  (If you really must know the gory
    details, SetActiveTab() automatically sets focus to one of the controls 
    within the newly activated tabs, so the main frame dialog's tab order is
    important in determining the tab *cycle*, not which control will receive
    focus at dialog initialization...)

*/

/////////////////////////////////////////////////////////////////////////////
// CAdUiTab window
#pragma warning(push)
#pragma warning(disable : 4275)
class ADUI_PORT CAdUiTab : public CTabCtrl {
friend class CAdUiTabMainDialog;
friend class CAdUiTabChildDialog;

    DECLARE_DYNAMIC(CAdUiTab);

public:
	            CAdUiTab ();
virtual         ~CAdUiTab ();

// Operations
private:
        BOOL    m_bDirty;
        HWND    m_hwndFocus;
        int     m_iActiveTab;
        UINT    m_uApplyButtonID;

        BOOL    BringTabToFront(int iPos);
        void    PositionTabDialog (CAdUiTabChildDialog *pDialog);
public:
        BOOL    AddTab (
                    int iPos, CString const& sTabname,
                    UINT uTemplateID, CAdUiTabChildDialog *pDialog
                );
        BOOL    AddTab (
                    int iPos, UINT uTabStringID,
                    UINT uTemplateID, CAdUiTabChildDialog *pDialog
                );

        // Don't use CTabCtrl::DeleteItem!  Use CAdUiTab::RemoveTab() instead!
        BOOL    DeleteItem (int iPos);

        // Removes tab, destroys child. Only updates if child IsDirty().
        BOOL    DestroyTab (int iPos, BOOL bUpdateData=FALSE);

        int     GetActiveTab ();
        CAdUiTabMainDialog *GetMainDialog ();
        int     GetTabIndex (CAdUiTabChildDialog *pDialog);
        CAdUiTabChildDialog *GetDialogPointer (int iPos);
        BOOL    IsDirty ();

        // Removes tab (hiding it) Doesn't destroy child dialog.    
        BOOL    RemoveTab (int iPos);

        int     SetActiveTab (int iPos);
        void    SetApplyButtonID (UINT uID);

        // Focuses on the child of the currently active tab.
        void    SetChildFocus ();

        void    SetDirty (BOOL bDirty=TRUE);
        void    SetValidationInfo (CDataExchange* pDX);

// Data Exchange methods.
public:
        BOOL    DisplayData ();
        BOOL    ExchangeData (BOOL bSaveAndValidate);
        BOOL    ValidateData ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAdUiTab)
	protected:
	virtual void PreSubclassWindow();    // INTERNAL USE ONLY
	//}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiTab)
    afx_msg BOOL OnSelChange(NMHDR* pNMHDR, LRESULT* pResult);    // INTERNAL USE ONLY
    afx_msg BOOL OnSelChanging(NMHDR* pNMHDR, LRESULT* pResult);  // INTERNAL USE ONLY
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};
#pragma warning(pop)
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

//////////////////////////////////////////////////////////////////////////////
