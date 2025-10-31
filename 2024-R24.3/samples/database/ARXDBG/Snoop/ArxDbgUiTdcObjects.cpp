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
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxDbgUiTdcObjects.h"
#include "ArxDbgUtils.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgUiTdcObjects::ArxDbgUiTdcObjects
**
**  **jma
**
*************************************/

ArxDbgUiTdcObjects::ArxDbgUiTdcObjects(const AcDbObjectIdArray& objList)
:   m_objList(objList)
{
    //{{AFX_DATA_INIT(ArxDbgUiTdcObjects)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiTdcObjects::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcObjects::DoDataExchange(CDataExchange* pDX)
{
    ArxDbgUiTdcDbObjectBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdcObjects)
    DDX_Control(pDX, ARXDBG_TXT_ERASE_STATUS, m_txtErased);
    DDX_Control(pDX, ARXDBG_LC_DATA, m_dataList);
	DDX_Control(pDX, ARXDBG_LB_OBJS, m_lbObjList);

    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcObjects message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdcObjects, ArxDbgUiTdcDbObjectBase)
    //{{AFX_MSG_MAP(ArxDbgUiTdcObjects)
    ON_LBN_SELCHANGE(ARXDBG_LB_OBJS, OnSelchangedObjs)
    ON_BN_CLICKED(ARXDBG_BN_DATABASE, OnDatabase)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcObjects message handlers

/****************************************************************************
**
**  ArxDbgUiTdcObjects::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdcObjects::OnInitDialog() 
{
    ArxDbgUiTdcDbObjectBase::OnInitDialog();

	m_lbObjList.ResetContent();

	AcDbObject* obj;
	CString str;
	Acad::ErrorStatus es;

	int len = m_objList.length();
	for (int i=0; i<len; i++) {
		es = acdbOpenAcDbObject(obj, m_objList[i], AcDb::kForRead, true);		// might have passed in erased ones
		if (es == Acad::eOk) {
			ArxDbgUtils::objToClassAndHandleStr(obj, str);
			m_lbObjList.AddString(str);
			obj->close();
		}
	}

	m_lbObjList.SetCurSel(0);

    buildColumns(m_dataList);
    displayCurrent(0);

    return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiTdcObjects::OnSelchangedObjs
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcObjects::OnSelchangedObjs() 
{
	int index = m_lbObjList.GetCurSel();
	if (index != LB_ERR) {
		displayCurrent(index);
	}
}

/****************************************************************************
**
**  ArxDbgUiTdcObjects::displayCurrent
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcObjects::displayCurrent(int index)
{
	// remove any previous entries
    m_fieldStrList.RemoveAll();
    m_valueStrList.RemoveAll();

    ASSERT((index >= 0) && (index < m_objList.length()));
    if(m_objList.length()==0)
		return;//done


	m_currentObjId = m_objList[index];

    CString str;

    AcDbObject* obj = NULL;
    Acad::ErrorStatus es = acdbOpenObject(obj, m_currentObjId, AcDb::kForRead, true);	// might want to show erased
    setExtensionButtons(obj);

    if (es == Acad::eOk) {
		display(obj);

		    // hide or show the erased entity message
		if (obj->isErased())
			m_txtErased.ShowWindow(SW_SHOW);
		else
			m_txtErased.ShowWindow(SW_HIDE);

        obj->close();
    }

	drawPropsList(m_dataList);
}
