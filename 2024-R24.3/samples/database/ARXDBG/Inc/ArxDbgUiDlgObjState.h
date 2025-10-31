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
