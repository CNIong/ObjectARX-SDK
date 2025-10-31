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

#include "ArxDbgUiTdcIdMap.h"
#include "ArxDbgUtils.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgUiTdcIdMap::ArxDbgUiTdcIdMap
**
**  **jma
**
*************************************/

ArxDbgUiTdcIdMap::ArxDbgUiTdcIdMap(AcDbIdMapping* idMap)
:   m_idMap(idMap)
{
    //{{AFX_DATA_INIT(ArxDbgUiTdcIdMap)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiTdcIdMap::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcIdMap::DoDataExchange(CDataExchange* pDX)
{
    ArxDbgUiTdcRxObjectBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdcIdMap)
    DDX_Control(pDX, ARXDBG_LC_VALUES, m_dataList);
	DDX_Control(pDX, ARXDBG_LC_MAPVALUES, m_lcObjList);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcIdMap message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdcIdMap, ArxDbgUiTdcRxObjectBase)
    //{{AFX_MSG_MAP(ArxDbgUiTdcIdMap)
    //ON_LBN_SELCHANGE(ARXDBG_LC_MAPVALUES, OnSelchangedObjs)
    //ON_BN_CLICKED(ARXDBG_BN_DATABASE, OnDatabase)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcIdMap message handlers

/****************************************************************************
**
**  ArxDbgUiTdcIdMap::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdcIdMap::OnInitDialog() 
{
    ArxDbgUiTdcRxObjectBase::OnInitDialog();

    buildColumns(m_dataList);
    displayCurrent();

	buildMapItemColumns();
	displayMapItems();

    return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiTdcIdMap::OnMainDialogOK
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcIdMap::OnMainDialogOK()
{
	GetMainDialog()->SaveColumnSizes(&m_lcObjList);

    ArxDbgUiTdcRxObjectBase::OnMainDialogOK();
}

/****************************************************************************
**
**  ArxDbgUiTdcIdMap::displayCurrent
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcIdMap::displayCurrent()
{
		// remove any previous entries
    m_fieldStrList.RemoveAll();
    m_valueStrList.RemoveAll();

	CString str;
	Acad::ErrorStatus es;
	AcDbDatabase* destDb = NULL;
	AcDbDatabase* origDb = NULL;
	
	es = m_idMap->destDb(destDb);
	if (es == Acad::eOk)
		ArxDbgUtils::dbToStr(destDb, str);
	else
		str = ArxDbgUtils::rxErrorStr(es);

	addToDataList(_T("Destination Database"), str);

	es = m_idMap->origDb(origDb);
	if (es == Acad::eOk)
		ArxDbgUtils::dbToStr(origDb, str);
	else
		str = ArxDbgUtils::rxErrorStr(es);

	addToDataList(_T("Original Database"), str);

	addToDataList(_T("Deep Clone Context"), ArxDbgUtils::deepCloneContextToStr(m_idMap->deepCloneContext(), str));
	addToDataList(_T("Duplicate Record Cloning"), ArxDbgUtils::mergeStyleToStr(m_idMap->duplicateRecordCloning(), str));

	drawPropsList(m_dataList);
}

/****************************************************************************
**
**  ArxDbgUiTdcIdMap::displayMapItems
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcIdMap::displayMapItems()
{
	this->LockWindowUpdate();		// suppress redraw events

    m_lcObjList.DeleteAllItems();		// remove any existing items from the control
	m_objIds.setLogicalLength(0);

        // build up the list view control
    LV_ITEM lvi;
    lvi.mask = 0;
    int row = 0;

    AcDbObject* obj;
    Acad::ErrorStatus es;

	CString str;

    AcDbIdPair idPair;
    AcDbIdMappingIter mapIter(*m_idMap);
    for (mapIter.start(); !mapIter.done(); mapIter.next()) {
        if (mapIter.getMap(idPair)) {
			m_objIds.append(idPair.key());	// record this in case we later add ability to open and inspect

			lvi.iItem = row;
			lvi.iSubItem = 0;
			m_lcObjList.InsertItem(&lvi);

            es = acdbOpenObject(obj, idPair.value(), AcDb::kForRead);
            if (es == Acad::eOk) {
				m_lcObjList.SetItemText(row, 0, ArxDbgUtils::objToClassStr(obj));
				m_lcObjList.SetItemText(row, 1, ArxDbgUtils::objToHandleStr(obj, str));

				obj->close();
            }
			else {
				m_lcObjList.SetItemText(row, 0, _T("** Failed Open **"));
				m_lcObjList.SetItemText(row, 1, ArxDbgUtils::rxErrorStr(es));
			}

			m_lcObjList.SetItemText(row, 2, ArxDbgUtils::intDbIdToStr(idPair.key().asOldId(), str));
			m_lcObjList.SetItemText(row, 3, ArxDbgUtils::intDbIdToStr(idPair.value().asOldId(), str));
			m_lcObjList.SetItemText(row, 4, ArxDbgUtils::booleanToStr(idPair.isCloned(), str));
			m_lcObjList.SetItemText(row, 5, ArxDbgUtils::booleanToStr(idPair.isPrimary(), str));
			m_lcObjList.SetItemText(row, 6, ArxDbgUtils::booleanToStr(idPair.isOwnerXlated(), str));

			row++;
        }
    }

	this->UnlockWindowUpdate();		// flushes redraw events
}

/****************************************************************************
**
**  ArxDbgUiTdcIdMap::buildMapItemColumns
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcIdMap::buildMapItemColumns()
{
        // get the width of the window
    CRect lvRect;
    int col1_width, col2_width, col3_width, col4_width, col5_width, col6_width, col7_width;
    m_lcObjList.GetClientRect(lvRect);
    int controlWidth = lvRect.Width() - ::GetSystemMetrics(SM_CXVSCROLL);

    col1_width = static_cast<int>(controlWidth * 0.30);
    col2_width = static_cast<int>(controlWidth * 0.10);
    col2_width = static_cast<int>(controlWidth * 0.10);
    col3_width = static_cast<int>(controlWidth * 0.10);
    col4_width = static_cast<int>(controlWidth * 0.10);
    col5_width = static_cast<int>(controlWidth * 0.10);
    col6_width = static_cast<int>(controlWidth * 0.10);
    col7_width = static_cast<int>(controlWidth * 0.10);

        // initialize the columns
    LV_COLUMN lvc;
    lvc.mask = LVCF_WIDTH | LVCF_SUBITEM | LVCF_TEXT;
    lvc.cx = col1_width;
    lvc.pszText = _T("Object");
    lvc.iSubItem = 0;
    m_lcObjList.InsertColumn(0, &lvc);

    lvc.cx = col2_width;
    lvc.iSubItem = 1;
    lvc.pszText = _T("Handle");
    m_lcObjList.InsertColumn(1, &lvc);

    lvc.cx = col3_width;
    lvc.iSubItem = 2;
    lvc.pszText = _T("Key");
    m_lcObjList.InsertColumn(2, &lvc);

    lvc.cx = col4_width;
    lvc.iSubItem = 3;
    lvc.pszText = _T("Value");
    m_lcObjList.InsertColumn(3, &lvc);

	lvc.cx = col5_width;
    lvc.iSubItem = 4;
    lvc.pszText = _T("Cloned");
    m_lcObjList.InsertColumn(4, &lvc);

	lvc.cx = col6_width;
    lvc.iSubItem = 5;
    lvc.pszText = _T("Primary");
    m_lcObjList.InsertColumn(5, &lvc);

	lvc.cx = col7_width;
    lvc.iSubItem = 6;
    lvc.pszText = _T("Owner Xlated");
    m_lcObjList.InsertColumn(6, &lvc);

	GetMainDialog()->GetColumnSizes(&m_lcObjList);
}

