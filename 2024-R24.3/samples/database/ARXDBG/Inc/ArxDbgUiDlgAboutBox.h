//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//

#ifndef ARXDBGUIDLGABOUTBOX_H
#define ARXDBGUIDLGABOUTBOX_H

#include "Res_ArxDbg.h"

/****************************************************************************
**
**	CLASS ArxDbgUiDlgAboutBox:
**
**	**jma
**
*************************************/

class ArxDbgUiDlgAboutBox : public CAcUiDialog {

public:
    ArxDbgUiDlgAboutBox(CWnd* pParent);

    //{{AFX_DATA(ArxDbgUiDlgAboutBox)
    enum { IDD = ARXDBG_DLG_ABOUT };
    //}}AFX_DATA


    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiDlgAboutBox)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiDlgAboutBox)
        // NOTE: the ClassWizard will add member functions here
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


#endif // ARXDBGUIDLGABOUTBOX_H
