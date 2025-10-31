//////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1994-2004 by Autodesk, Inc.
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
// DESCRIPTION
//
//   Include file for classes dealing with extended tabs.
//                  
/////////////////////////////////////////////////////////////////////////////

#ifndef _aduiTabExtension_h
#define _aduiTabExtension_h
#pragma pack (push, 8)

/////////////////////////////////////////////////////////////////////////////
// This class manages extended tabs in a tab extensible dialog.
// A tab extensible dialog has one instance of this class in the
// dialog object which is initialized in the dialog's constructor.

class ADUI_PORT CAdUiTabExtensionManager {
public:
                CAdUiTabExtensionManager ();
virtual         ~CAdUiTabExtensionManager ();    

// Tab Extension Manager
private:
        CString m_dlgName;              // Buffer for GetDialogName().
        CAdUiTabMainDialog *m_pDlg;     // The tab extensible dialog.
        CAdUiTab *m_pTabCtrl;           // The tab control in the dialog.

        // Adds tabs to a dialog that have been registered by a particular application.
        BOOL    AddApplicationTabs (LPCTSTR pszAppName);
public:
        // This function in called in the OnInitDialog() of a tab extensible
        // dialog to add extended tabs to itself.
        int     AddExtendedTabs ();

        // Actually adds an extended tab.
virtual BOOL    AddTab (
                    HINSTANCE hInstRes,
                    UINT uTemplateID,
                    LPCTSTR pszTabName,         // since templates don't have captions...
                    CAdUiTabChildDialog *pDialog
                );

        // Return the dialog name used as a registry key for extended tabs.
virtual LPCTSTR GetDialogName ();
    
        // Initialize the manager.
        void    Initialize (CAdUiTab *pTabCtrl, CAdUiTabMainDialog *pDlg);

        CAdUiTab* GetTabControl() const {return m_pTabCtrl;}
};

/////////////////////////////////////////////////////////////////////////////

#pragma pack (pop)
#endif

/////////////////////////////////////////////////////////////////////////////
