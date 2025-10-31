//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//      arxsdk/acuiTabCtrl.h
//

#pragma once
#include "acui_port.h"
#include "aduiTabCtrl.h"        // CAdUiTab

#pragma pack (push, 8)

/////////////////////////////////////////////////////////////////////////////
// CAdUiTab window

class ACUI_PORT CAcUiTab : public CAdUiTab {
    DECLARE_DYNAMIC(CAcUiTab);

public:
                CAcUiTab ();
                ~CAcUiTab ();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiTab)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiTab)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)

//////////////////////////////////////////////////////////////////////////////
