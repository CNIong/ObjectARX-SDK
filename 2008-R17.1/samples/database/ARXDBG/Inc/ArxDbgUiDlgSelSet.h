//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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

#ifndef ARXDBGUIDLGSELSET_H
#define ARXDBGUIDLGSELSET_H

#include "Res_ArxDbg.h"
#include "ArxDbgRbList.h"

/****************************************************************************
**
**	CLASS ArxDbgUiDlgSelSet:
**
**	**jma
**
*************************************/

class ArxDbgUiDlgSelSet : public CAcUiDialog {

public:
                ArxDbgUiDlgSelSet(CWnd* pParent);

    //{{AFX_DATA(ArxDbgUiDlgSelSet)
    enum { IDD = ARXDBG_DLG_SSGET };
    int					m_puMainSelectTypeIndex;
	CComboBox			m_puMainSelectType;
    BOOL				m_filterLockedLayers;
    BOOL				m_rejectNonCurrent;
    BOOL				m_rejectPaperSpaceViewport;
    BOOL				m_allowDuplicates;
    BOOL				m_allowSingleOnly;
    BOOL				m_useKwordCallback;
    BOOL				m_useOtherCallback;
    BOOL				m_useSelectPrompt;
    BOOL				m_useRemovePrompt;
    CString				m_selectPrompt;
    CString				m_removePrompt;
    CAcUiSelectButton	m_selectButton;
	BOOL				m_useFilter;
	CComboBox			m_puClassType;
	int					m_puClassTypeIndex;
	BOOL				m_doIsKindOfTest;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiDlgSelSet)
	virtual BOOL OnInitDialog();
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiDlgSelSet)
    afx_msg void OnSelectObjects();
    afx_msg void OnPromptToggle();
    afx_msg void OnFilterToggle();
	afx_msg void OnSelendokSelectType();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
	bool		getBoxPoints(AcGePoint3d& pt1, AcGePoint3d& pt2, bool useDash);
	void		getClassesDerivedFrom(AcRxClass* searchClassType,
								AcDbVoidPtrArray& derivedClasses);
	void		getFilter(ArxDbgRbList& rbList);

	void		setFlagModes(bool allowed);
	void		setKeywordModes(bool allowed);
	void		setPromptModes(bool allowed);
	void		setFilterModes(bool allowed);

    static struct resbuf*       keywordCallback(const TCHAR* str);
    static struct resbuf*       otherCallback(const TCHAR* str);

};

#endif // ARXDBGUIDLGSELSET_H
