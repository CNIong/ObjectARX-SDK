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
