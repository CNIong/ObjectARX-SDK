/////////////////////////////////////////////////////////////////////////////
//
//
// (C) Copyright 2008-2009 Autodesk, Inc. All rights reserved.
//
// **** CONFIDENTIAL MATERIAL ****
//
// The information contained herein is confidential, proprietary to
// Autodesk, Inc., and considered a trade secret. Use of this information
// by anyone other than authorized employees of Autodesk, Inc. is granted
// only under a written nondisclosure agreement, expressly prescribing
// the scope and manner of such use.
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AdExportDef.h"

class AdImpMenuBar;

/// <summary>
/// LPFNADMENUCALLBACK is a callback for Menu.
/// </summary>
typedef bool (CALLBACK *LPFNADMENUCALLBACK)(unsigned int nItemId);

//////////////////////////////////////////////////////////////////
// MenuBar

/// <summary>
/// The application frame menu bar. 
/// </summary>                      
class ADAF_PORT AdMenuBar
{
    friend class AdApplicationFrame;

public:
    virtual ~AdMenuBar();

    bool GetMenuItemHelpString(UINT nItemID, const wchar_t **wszHelpString);
    bool RemoveMenuItem(HMENU hMenu, UINT nMenuItemId);
    bool AddMenuItem(HMENU hMenu, UINT nPos, const MENUITEMINFO& menuItem, 
        LPFNADMENUCALLBACK pfnCallback, const wchar_t *wszHelpString);
    bool SetMenuHandle(HMENU hMenu);
    void UpdateMenu();
    HMENU GetMenuHandle();
    bool TrackingPopup();
    void SetChildWindowMenuPopup(bool bShow);
    bool GetChildWindowMenuPopup(void);

private:
    AdMenuBar(AdImpMenuBar* pImpMenuBar);
    AdMenuBar();

    /// <summary>
    /// Member pointer to the implementation class of the class
    /// AdMenuBar. 
    /// </summary>                                             
    AdImpMenuBar *mpImpMenuBar;
};