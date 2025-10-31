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

#ifndef ARXDBGUIDLGGENERICDEFID_H
#define ARXDBGUIDLGGENERICDEFID_H

#include "Res_ArxDbg.h"
#include "SdStrObjId.h"

/****************************************************************************
**
**	CLASS ArxDbgUiDlgGenericDefId:
**
**	**jma
**
*************************************/

class ArxDbgUiDlgGenericDefId : public CAcUiDialog {

public:
				ArxDbgUiDlgGenericDefId(CWnd* pParent,
								SdStrObjIdList& entries,
                                const AcDbObjectId& currentValue,
                                bool allowNone);

                ArxDbgUiDlgGenericDefId(CWnd* pParent,
                                SdStrObjIdList& entries,
                                const AcDbObjectIdArray& currentValues,
                                bool allowNone);

    virtual     ~ArxDbgUiDlgGenericDefId();

        // must be called before DoModal()
    void            setDboxTitle(const CString& title) { m_title = title; }
    void            setPrompt(const CString& prompt)   { m_prompt = prompt; }

        // use these after DoModal() call to find out what was selected
    LPCTSTR         getSelectedName (CString& name) const;
    AcDbObjectId    getSelectedId() const;

    bool            isVaries() const;
    bool            isNone() const;

    //{{AFX_DATA(ArxDbgUiDlgGenericDefId)
    enum { IDD = ARXDBG_DLG_GENERIC_DEF_ID };
    CListCtrl    m_lcDefIds;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiDlgGenericDefId)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:

    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiDlgGenericDefId)
    afx_msg void OnListItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
    virtual BOOL OnInitDialog();
    afx_msg void OnDblclickList(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
    SdStrObjIdList&	m_entries;
    int             m_curIndex;
    bool            m_hasVaries;
    bool            m_hasNone;
    CString         m_title;
    CString         m_prompt;

        // helper functions
    void            buildColumns();
    void            fillList();

};

#endif    // ARXDBGUIDLGGENERICDEFID_H
