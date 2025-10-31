//
// (C) Copyright 1998-2002 by Autodesk, Inc. 
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

#ifndef ARXDBGUIDLGOBJSTATE_H
#define ARXDBGUIDLGOBJSTATE_H

#include "Res_ArxDbg.h"


/****************************************************************************
**
**  CLASS ArxDbgUiDlgObjState:
**      used as a test for how open/close/cancel work.
**
**  **jma
**
*************************************/

class ArxDbgUiDlgObjState : public CAcUiDialog {

public:
                ArxDbgUiDlgObjState(CWnd* parent, const AcDbObjectId& objId, LPCTSTR dboxTitle = NULL);
                ArxDbgUiDlgObjState(CWnd* parent, AcDbObject* obj, LPCTSTR dboxTitle = NULL);
    virtual     ~ArxDbgUiDlgObjState();

    //{{AFX_DATA(ArxDbgUiDlgObjState)
    enum { IDD = ARXDBG_DLG_RXSTATE };
    //}}AFX_DATA


    //{{AFX_VIRTUAL(ArxDbgUiDlgObjState)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(ArxDbgUiDlgObjState)
    afx_msg void OnCancelObj();
    afx_msg void OnCloseObj();
    afx_msg void OnCloseAndPageObj();
    afx_msg void OnDowngradeToNotify();
    afx_msg void OnDowngradeWrite();
    afx_msg void OnEraseObj();
    afx_msg void OnUneraseObj();
    afx_msg void OnModifyObj();
    afx_msg void OnOpenForNotify();
    afx_msg void OnOpenForRead();
    afx_msg void OnUpgradeFromNotify();
    afx_msg void OnUpgradeToWrite();
    afx_msg void OnOpenForWrite();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    AcDbObject*     m_obj;
    AcDbObjectId    m_objId;
    bool            m_wasOpenOnConstruct;
    LPCTSTR         m_dboxTitle;
	bool			m_bUpgradedFromNotify;
	Adesk::Boolean	m_bWasWritable;

    bool    objIsOpen();
    bool    objIsOpenForWrite();
    void    open(AcDb::OpenMode openMode);
    void    doErase(bool reallyErase);
    void    display();
};

#endif // ARXDBGUIDLGOBJSTATE_H
