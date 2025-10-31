//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//      arxsdk/acuiDialogWorksheet.h
//

#pragma once
#include "aduiListCtrl.h"

#pragma pack (push, 8)

/////////////////////////////////////////////////////////////////////////////
// CAcUiListCtrl window

/*
class ACUI_PORT CAcUiListCtrl : public CAdUiListCtrl {
//    DECLARE_DYNAMIC(CAcUiListCtrl);

public:
                CAcUiListCtrl ();
virtual         ~CAcUiListCtrl ();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiListCtrl)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiListCtrl)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
*/

using CAcUiListCtrl = CAdUiListCtrl;

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)

/////////////////////////////////////////////////////////////////////////////
