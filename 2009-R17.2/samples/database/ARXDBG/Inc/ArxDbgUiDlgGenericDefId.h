//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
