//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//      arxsdk/acuiNavDialog.h
//
// Name:    AutoCAD file navigation dialog header file
//
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "anav.h"
#include "acui_port.h"

// Forward class declarations.
class CAcUiNavPreviewButton;

typedef enum
{
    // Open with no template flags
    acUiOpenNoTemplateNone      =   0x0000,
    acUiOpenNoTemplateImperail  =   0x0001,
    acUiOpenNoTemplateMetric    =   0x0002
} AcUiOpenNoTemplateFlag;

/////////////////////////////////////////////////////////////////////////////
// File Navigation dialog - this is the AutoCAD file navigation dialog.
class ACUI_PORT CAcUiNavDialog : public CNavDialog {
    DECLARE_DYNAMIC(CAcUiNavDialog)

    public:

        // Constructor and destructor.
        CAcUiNavDialog (
            CNavDataArray& dataArray,           // For results of the dialog.
            CNavFilterArray& filterArray,       // Files of type.
            UINT idd=0,                         // Template id, 0 means use the default template for AutoCAD dialog.
            CWnd *pParent=NULL,                 // Dialog parent. NULL means the desktop.
            HINSTANCE hDialogResource=NULL      // Resource ID where template is found. NULL means use the default.
        );
        ~CAcUiNavDialog ();

        // Dialog initialization.
        BOOL OnInitDialog () override;

        // Get the "Recent" directory under the "Application Data"
        // directory of the OS for use with the "History" places item.
        BOOL GetRecentDirectory(CString& strRecent) override;

        // Locate a file in a search path for use with the "Locate" tools menu item.
        BOOL FindInSearchPath(LPCTSTR sBase, CString* pFullPath) override;

        // Get the default URL to use in the web browser when the web button is selected.
        void GetDefaultBrowserStartURL(CString& strStartPage) override;

        // Launch a browser and get a URL. Called when the web button is selected.
        BOOL LaunchBrowserDialog(CString& strSelectedURL, LPCTSTR strDialogCaption,
            LPCTSTR strOk, LPCTSTR strStartPage) override;
        
        // Display an error in trying to locate a file in the search path when the "Locate"
        // tools menu item is selected.
        void DisplaySearchError(LPCTSTR sBase) override;

        // Called when the user choses "Locate" form tools menu.
        void OnDoLocate() override;

        // Return the product name to be used when registering extensions.
        BOOL GetProductName(CString& strProduct) override;

        // Called at the start of a remote file download operation.        
        BOOL BeginDownloadFiles(CStringArray& strURLs, CDWordArray& dwActionCodes) override;

        // Callback to get additional action code bits for a remote download.
        DWORD GetDownloadActionCodes(CString& strURL) override;

        // Called when the preview needs painting after it has been erased.
        virtual void OnPaintPreview(LPCTSTR strFullPath, CWnd* previewWnd);
        
        // Called when the help button is selected.
        void OnDialogHelp() override;
        void OnDialogHelp(LPCTSTR pTag) override;

        BOOL GetPreviewPresent();              // Does the dialog have an AutoCAD preview window?
        void SetPreviewPresent(BOOL preview);  // Set the AutoCAD preview window as present.
        BOOL GetPreviewVisible();              // Is the AutoCAD preview window visible?
        void SetPreviewVisible(BOOL visible);  // Set the AutoCAD preview window visible.
        BOOL GetInitialViewButtonChecked();    // Is the initial view checkbox checked?
        void ConvertFlagsToState(int nFlags);  // Sets up dialog internal state. FOR INTERNAL USE ONLY.
        
        AcUiOpenNoTemplateFlag GetOpenNoTemplateSelection();

        short GetUpdateThumbnailOverride();      // Get the override value for the UPDATETHUMBNAIL sysvar


        // REMEMBERFOLDERS support
        void SetUseRememberFolders(bool bUseRememberFolders);
        bool GetUseRememberFolders() const;

public:
        //CAdUiBaseDialog overrides

        void EnableFloatingWindows (BOOL allow) override;
        int IsMultiDocumentActivationEnabled() override;
        int EnableMultiDocumentActivation(BOOL bEnable) override;

    protected:
        void OnFolderItemChange() override;    // Called when the selection changes.
        void OnFilterChange() override;        // Called when the filter changes.
        BOOL OnFileNameOK () override;         // Called when the commit button is clicked.
        void OnFileNameChange () override;     // Called when thetext changes in the file name editbox.
        void PrepareOkMenu(CMenu* pMenu) override;// Possibly alter the base ok menu.
        void PrepareViewsMenu(CMenu* pMenu) override;// Possibly alter the base views menu.
        void PrepareToolsMenu(CMenu* pMenu) override;// Possibly alter the base tools menu.
        void OnURLDownloadSuccess(CString& strURL) override;// Called when checking for errors after downloading files.
        virtual BOOL GetOptionsState();        // Check for a tab in the options dialog for the current combination of filetype and get/put file..
        void OnCancel() override;
        void OnOK() override;

        void Do3DDwfOptionsDialog();           // Display the 3D Dwf option dialog.
        void InitPreviewState();               // Initialize the preview control.
 
    protected:
    //{{AFX_MSG(CAcUiNavDialog)
        afx_msg void OnOpenNoTemplateImperial();  // Called when "open with no template - Imperial" item is selected.
        afx_msg void OnOpenNoTemplateMetric();  // Called when "open with no template - Metric" item is selected.
        afx_msg void OnOpenMenuPartialOpen();  // Called when the partial open item is selected.
        afx_msg void OnOpenMenuPartialOpenReadOnly();// Called when the partial open read only item is selected.
        afx_msg void OnViewsMenuPreview();     // Called when the preview item is selected from the view menu.
        afx_msg void OnToolsMenuOptions();     // Called when the options item is selected from the view menu.
        afx_msg void OnToolsMenuSecurity();     // Called when the security item is selected from the tools menu.
        afx_msg void OnDestroy();    
        afx_msg void OnUpdateThumbnailCheck();  // Called when the update thumbnail checkbox is selected.
        afx_msg void OnOnlineOptions();         // Fire up the Preferences dialog Online tab
        afx_msg void OnShowReferenceFiles();    // Show cloud reference files
    //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:

        // These members are used by AutoCAD's dialogs.
        short m_CmdInProgress;
        short m_nUpdateThumbnailOverride;      // The override value for the UPDATETHUMBNAIL sysvar.
        BOOL m_bIsOpen;                        // This is the AutoCAD file OPEN dialog.
        BOOL m_bIsSaveAs;                      // This is the AutoCAD file SAVEAS dialog.
        BOOL m_bIsRecover;                     // We are doing a RECOVER.
        BOOL m_bPartialOpenAlwaysDisabled;     // Set by OEM.
        BOOL m_bInitialViewButtonPresent;      // There is an initial view checkbox.
        BOOL m_bInitialViewButtonChecked;      // Initial view checkbox is checked.
        BOOL m_bPartialOpenPresent;            // There is a partial open button.
        BOOL m_bOptionsPresent;                // There is an OPTIONS menu item.
        BOOL m_bPreviewPresent;                // There is a preview.
        BOOL m_bPreviewVisible;                // Preview is visible.
        BOOL m_bOpenNoTemplate;        // DLFNOTEMPIPR, Open with no Template - Imperial or Metric
        AcUiOpenNoTemplateFlag m_nOpenNoTemplateSelection;
        CAcUiNavPreviewButton* m_previewButton;
        BOOL m_bIsExport;                       // This is the AutoCAD file Export dialog.
        BOOL CanPartiallyOpen(LPCTSTR szfullPath);// Can the file be partially opened?
        bool ApplyRememberFoldersInitialization(int rememberFolders);
        bool ApplyRememberFoldersOnOk();
        bool m_bUseRememberFolders;
        void HideControls();
        void UpdateInitialFolder(); // Called to adjust the initial folder if necessary
        int  CheckSharedFilePrivileges(const CString & filename);

        //use static variable instead of to avoid binary compatibility.
        static BOOL m_bOriginalMultiSelAllowed;        // Log original multi-selection setting
        BOOL m_bOpenSample;

};

